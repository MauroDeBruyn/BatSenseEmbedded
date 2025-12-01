#ifndef WIFIAP_H
#define WIFIAP_H

#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
//#include "esp_spi_flash.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define EXAMPLE_ESP_WIFI_SSID      "Milenda"
#define EXAMPLE_ESP_WIFI_PASS      "sY!$6&F&cRC"
#define EXAMPLE_MAX_STA_CONN       100

static const char *TAG_WIFI = "wifi";

void wifi_init( void );
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data);
#endif