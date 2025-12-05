#include "network.h"

HTTP_server::HTTP_server(const char* ssid_, const char* password_)
    : ssid(ssid_), password(password_), server(80)
{
    logs = logger::create();
    logs->addLog("HTTP_server", "initialization");

    WiFi.softAP(ssid, password);

    IP = WiFi.softAPIP();
    logs->addLog("WIFI SOFT IP PASS:", "192.168.4.1");

    server_addroutes();
    server.begin();
}

void HTTP_server::server_addroutes() {
    logs->addLog("HTTP_server", "adding routes");

    server.on("/", HTTP_GET,
        [this](AsyncWebServerRequest *request) {

            sys_fs.FileOpen("index.html", "r");
            sys_fs.FileRead();

            String page(sys_fs.bufferPtr());   
            request->send(200, "text/html", page);
        }
    );

    server.on("/log", HTTP_GET,
        [this](AsyncWebServerRequest *request) {

            sys_fs.FileOpen("index_log.html", "r");
            sys_fs.FileRead();

            String page(sys_fs.bufferPtr());
            page.replace("%log%", logs->getLogs());  

            request->send(200, "text/html", page);  
        }
    );
}
