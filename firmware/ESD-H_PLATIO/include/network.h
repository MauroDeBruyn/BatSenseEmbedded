#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FSinterface.h"

class HTTP_server {
    const char* ssid;
    const char* password;
    IPAddress IP;
    AsyncWebServer server;
    FS_navigator sys_fs;

    void server_addroutes();
    String process_root_request(const String& var);

public:
    HTTP_server(const char* ssid_, const char* password_);
    ~HTTP_server() {}
};
