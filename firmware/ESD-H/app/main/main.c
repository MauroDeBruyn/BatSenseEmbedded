/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "wifiAP.h"

void app_main()
{
    printf("=== System Booted up ===\n");
    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init();
}