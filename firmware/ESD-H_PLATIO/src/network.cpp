#include "network.h"

extern SDinterface* instance;
extern HTTP_server* serverAP;

HTTP_server::HTTP_server(const char* ssid_, const char* password_)
    : ssid(ssid_), password(password_), server(80)
{
    logs = logger::create();
    logs->addLog("HTTP_server", "initialization");
    Serial.println("HTTP server : initialization");

    WiFi.softAP(ssid, password);

    IP = WiFi.softAPIP();
    logs->addLog("WIFI SOFT IP PASS:", "192.168.4.1");
    Serial.printf("WIFI SOFT IP PASS\n");
    Serial.print(IP);
    
    server_addroutes();
    server.begin();
}

void HTTP_server::server_addroutes() {
    logs->addLog("HTTP_server", "adding routes");

    server.on("/", HTTP_GET,
              [this](AsyncWebServerRequest *request)
              {
                request->send(200, "text/html", http_main_page);
                Serial.printf("Requested home-page\n");
              });

    server.on("/log", HTTP_GET,
              [this](AsyncWebServerRequest *request)
              {
                  Serial.printf("Requested log-file\n");
                  sys_fs.FileOpen("index_log.html", "r");
                  sys_fs.FileRead();

                  String page(sys_fs.bufferPtr());
                  page.replace("%log%", logs->getLogs());

                  request->send(200, "text/html", page);
              });

    server.on("/sd", HTTP_GET, [](AsyncWebServerRequest *request)
        {

        Serial.printf("Requested file download\n");
        if (!request->hasParam("f")) {
            request->send(400, "text/plain", "Missing filename");
            return;
        }

        if (instance->canWeTakeBus() == false) {
            request->send(503, "text/plain", "SPI bus busy");
            return;
        }

        String filename = "/" + request->getParam("f")->value();
        instance->takeBusControl();
        if (!SD.begin(SD_CS)){
            Serial.println("SD.begin claim failed");
            request->send(404, "text/plain", "failed to claim the bus");
            return;
        } else {
            instance->_weTookBus = true;
        } 

        if (!SD.exists(filename)) {
            instance->_weTookBus = false;
            request->send(404, "text/plain", "File not found");
            return;
        }

        File file = SD.open(filename, "r");
        if (!file) {
            instance->_weTookBus = false;
            request->send(500, "text/plain", "Open failed");
            return;
        }

        const char* type = "application/octet-stream";

        request->onDisconnect([]() {
            SD.end();
            instance->relinquishBusControl();
        });
        // Give ownership of 'file' to AsyncWebServer.
        request->send(file, filename, type, true);
        });
}
