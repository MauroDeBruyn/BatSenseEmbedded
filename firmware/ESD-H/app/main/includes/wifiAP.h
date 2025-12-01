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
//#include "esp_spi_flash.h"
//#include "nvs.h"
//#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define AP_WIFI_SSID        CONFIG_AP_WIFI_SSID
#define AP_WIFI_PASS        CONFIG_AP_WIFI_PASSWORD
#define AP_MAX_CONN         CONFIG_AP_MAX_STA_CONN

#define STA_WIFI_SSID       CONFIG_STA_WIFI_SSID
#define STA_WIFI_PASS       CONFIG_STA_WIFI_PASSWORD
#define STA_TIMEOUT         CONFIG_STA_CONNECT_TIMEOUT

static const char *TAG_WIFI_AP = "WIFI_AP";
static const char *TAG_WIFI_STA = "WIFI_STA";

void wifi_init( void );
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);
#endif