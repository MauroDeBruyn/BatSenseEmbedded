#include "network.h"

HTTP_server::HTTP_server(const char* ssid_, const char* password_)
    : ssid(ssid_), password(password_), server(80)
{
    WiFi.softAP(ssid, password);

    IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    Serial.println(WiFi.localIP());

    server_addroutes();
    server.begin();

}

void HTTP_server::server_addroutes() {
    sys_fs.FileOpen("index.html","r");
    sys_fs.FileRead();

    server.on("/", HTTP_GET,
        [this](AsyncWebServerRequest *request) {
            request->send(200, "text/html", sys_fs.bufferPtr(),
                [this](const String& var) {
                    return this->process_root_request(var);
                }
            );
        }
    );
}

String HTTP_server::process_root_request(const String& var) {
    return String();   // MUST return a String
}
