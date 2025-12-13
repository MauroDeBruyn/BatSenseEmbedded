import appdaemon.plugins.hass.hassapi as hass
import socket
import struct
import threading
import io
import time
import traceback
from queue import Queue
from PIL import Image, ImageOps
from datetime import datetime

WIDTH = 32
HEIGHT = 24
PIXELS = WIDTH * HEIGHT
FRAME_BYTES = 4 + PIXELS * 2  # "MLX1" + 1536 bytes


def TS():
    return datetime.now().strftime("[%H:%M:%S.%f]")


class ThermalReceiver(hass.Hass):

    def initialize(self):
        self.ip = "0.0.0.0"
        self.port = int(self.args["port"])
        self.output = "/share/thermal.png"

        self.frame_queue = Queue(maxsize=8)

        endpoint = self.args.get("endpoint", "thermal")
        self.register_endpoint(self.serve_image, endpoint)

        threading.Thread(target=self.receiver_loop, daemon=True).start()
        threading.Thread(target=self.writer_loop, daemon=True).start()

        self.log(f"{TS()} INIT OK — listening on {self.ip}:{self.port}, endpoint '/{endpoint}'")

    # ----------------------------------------------------------------------

    def serve_image(self, request):
        try:
            with open(self.output, "rb") as f:
                return f.read(), 200, {"Content-Type": "image/png"}
        except FileNotFoundError:
            return b"", 404, {"Content-Type": "text/plain"}

    # ----------------------------------------------------------------------

    def recv_exact(self, conn, size):
        buf = bytearray()
        while len(buf) < size:
            try:
                chunk = conn.recv(size - len(buf))
            except Exception as e:
                self.log(f"{TS()} ERROR recv(): {e}")
                self.log(traceback.format_exc())
                return None

            if not chunk:
                return None

            buf.extend(chunk)

        return bytes(buf)

    # ----------------------------------------------------------------------

    def receiver_loop(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        try:
            sock.bind((self.ip, self.port))
            sock.listen(1)
            self.log(f"{TS()} READY — Listening on {self.ip}:{self.port}")
        except Exception as e:
            self.log(f"{TS()} FATAL cannot bind socket: {e}")
            self.log(traceback.format_exc())
            return

        while True:
            conn, addr = sock.accept()
            self.log(f"{TS()} CONNECTED — {addr}")

            try:
                self.handle_client(conn, addr)
            except Exception:
                self.log(f"{TS()} ERROR in handle_client():")
                self.log(traceback.format_exc())
            finally:
                try:
                    conn.shutdown(socket.SHUT_RDWR)
                except:
                    pass
                conn.close()
                self.log(f"{TS()} CLOSED — {addr}")

    # ----------------------------------------------------------------------

    def handle_client(self, conn, addr):
        frame_count = 0

        while True:
            data = self.recv_exact(conn, FRAME_BYTES)
            if data is None:
                self.log(f"{TS()} DISCONNECT — recv_exact returned None for {addr}")
                return

            frame_count += 1

            if not data.startswith(b"MLX1"):
                self.log(f"{TS()} ERROR bad header frame {frame_count}")
                continue

            try:
                temps = struct.unpack(">" + "H" * PIXELS, data[4:])
            except Exception as e:
                self.log(f"{TS()} ERROR unpack frame {frame_count}: {e}")
                self.log(traceback.format_exc())
                continue

            try:
                self.frame_queue.put_nowait(temps)
            except:
                pass  # queue full → drop frame

            if frame_count % 10 == 0:
                self.log(f"{TS()} INFO — {frame_count} frames received")

    # ----------------------------------------------------------------------

    def writer_loop(self):
        self.log(f"{TS()} Writer loop started")

        while True:
            temps = self.frame_queue.get()

            try:
                # grayscale base image
                gray = Image.new("L", (WIDTH, HEIGHT))
                gray.putdata([min(255, t // 50) for t in temps])

                # apply heatmap: blue → yellow → red
                heat = ImageOps.colorize(gray, black="blue", mid="yellow", white="red")

                # upscale for visibility
                heat = heat.resize((WIDTH * 10, HEIGHT * 10), Image.NEAREST)

                buf = io.BytesIO()
                heat.save(buf, format="PNG")

                with open(self.output, "wb") as f:
                    f.write(buf.getvalue())

            except Exception as e:
                self.log(f"{TS()} ERROR writer(): {e}")
                self.log(traceback.format_exc())

            time.sleep(0.005)
