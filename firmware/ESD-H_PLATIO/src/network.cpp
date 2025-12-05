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
        [this](AsyncWebServerRequest *request)
        {
            request->send(200, "text/html", http_main_page);
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
    
    server.on("/sd", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        if (!request->hasParam("f")) {
            request->send(400, "text/plain", "Missing filename");
            return;
        }

        String filename = "/" + request->getParam("f")->value();

        if (!SD.exists(filename)) {
            request->send(404, "text/plain", "File not found");
            return;
        }

        File file = SD.open(filename, "r");
        if (!file) {
            request->send(500, "text/plain", "Open failed");
            return;
        }

        const char* type = "application/octet-stream";  // force download
        request->send(file, filename, type, true);      // <- true = download
    });
}
