#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FSinterface.h"
#include "logging.h"
#include <SPI.h>
#include "SD.h"
#include "FS.h"
#include "IOinterface.h"


class HTTP_server {
    const char* ssid;
    const char* password;
    IPAddress IP;
    AsyncWebServer server;
    FS_navigator sys_fs;
    logger * logs;
    SDinterface sd;

    void server_addroutes();

public:
    HTTP_server(const char* ssid_, const char* password_);
    ~HTTP_server() {}
    String http_main_page{""};
};
