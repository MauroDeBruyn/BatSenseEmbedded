#!/usr/bin/env python3
import socket
import struct
import sys
import time
import math
import traceback

if len(sys.argv) != 3:
    print("Usage: python3 mlx_emulator.py <ip> <port>")
    sys.exit(1)

IP = sys.argv[1]
PORT = int(sys.argv[2])

WIDTH  = 32
HEIGHT = 24
PIXELS = WIDTH * HEIGHT

FPS        = 16
TEMP_BASE  = 25.0
AMPL_X     = 5.0
AMPL_Y     = 3.0

header = b"MLX1"

print(f"[INIT] Resolving hostname: {IP}")
ip4 = socket.gethostbyname(IP)
print(f"[INIT] Using IPv4 address: {ip4}")

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print(f"[CONNECT] Attempting to connect to {ip4}:{PORT}...")
try:
    sock.connect((ip4, PORT))
    print("[CONNECT] SUCCESS")
except Exception as e:
    print("[CONNECT] FAILED:", e)
    raise

interval = 1.0 / FPS
t = 0.0
dt = 1.0 / FPS

frame_counter = 0

try:
    while True:
        body = bytearray()
        for idx in range(PIXELS):
            y, x = divmod(idx, WIDTH)
            temp = (
                TEMP_BASE
                + AMPL_X * math.sin(t + x * 0.25)
                + AMPL_Y * math.cos(t * 0.7 + y * 0.35)
            )
            value = int(temp * 100.0)
            body += struct.pack(">H", max(0, min(0xFFFF, value)))

        frame = header + body
        frame_counter += 1

        #print(f"[SEND] Sending frame #{frame_counter} ({len(frame)} bytes)...", end=" ")

        try:
            sock.sendall(frame)
            print("OK")
        except Exception as e:
            print("FAILED")
            print("[ERROR] Exception during sendall():")
            traceback.print_exc()
            break

        time.sleep(interval)
        t += dt

except KeyboardInterrupt:
    print("\n[EXIT] Keyboard interrupt")

finally:
    print("[CLOSE] Closing socket")
    sock.close()
    print("[CLOSE] Done")
