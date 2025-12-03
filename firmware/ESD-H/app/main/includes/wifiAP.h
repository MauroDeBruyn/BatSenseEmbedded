#ifndef WIFIAP_H
#define WIFIAP_H

#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h" 
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_http_server.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "FileSYS.h"
#include "Webdata.h"
#include "debug.h"

//Acces Point setup
#define AP_WIFI_SSID        CONFIG_AP_WIFI_SSID
#define AP_WIFI_PASS        CONFIG_AP_WIFI_PASSWORD
#define AP_MAX_CONN         CONFIG_AP_MAX_STA_CONN

#define STA_WIFI_SSID       CONFIG_STA_WIFI_SSID
#define STA_WIFI_PASS       CONFIG_STA_WIFI_PASSWORD
#define STA_TIMEOUT         CONFIG_STA_CONNECT_TIMEOUT

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

void wifi_init( void );

//HTML Server setup
#define INDEX_HTML_PATH "/spiffs/index.html"
char errbuffer[20480]; //20kb
char response_data[22480];

void Server_init();

#endif