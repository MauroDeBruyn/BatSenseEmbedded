#include "wifiAP.h"

static const char *TAG_WIFI_AP = "WIFI_AP";
static const char *TAG_WIFI_STA = "WIFI_STA";
static const char *TAG_HTTP = "WIFI_HTTP";
static int s_retry_num = 0;
wifi_config_t wifiAP_config = { 0 };
/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    /*==== wifi AP events ====*/
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG_WIFI_AP, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG_WIFI_AP, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }

    /*==== wifi sta events ====*/
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < STA_TIMEOUT) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG_WIFI_STA, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG_WIFI_STA,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG_WIFI_STA, "got ip:%s",
                 ip4addr_ntoa(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_init( void ){

     s_wifi_event_group = xEventGroupCreate();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL) );

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_start());

    strcpy((char *)wifiAP_config.ap.ssid, AP_WIFI_SSID);
    strcpy((char *)wifiAP_config.ap.password, AP_WIFI_PASS);
    wifiAP_config.ap.ssid_len = strlen(AP_WIFI_SSID);
    wifiAP_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    wifiAP_config.ap.max_connection = AP_MAX_CONN;
    wifiAP_config.ap.channel = 1; // replace magic number
    
    if (strlen(AP_WIFI_PASS) == 0) {
        wifiAP_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP) );
	ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_AP, &wifiAP_config) );
	ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_LOGI(TAG_WIFI_AP, "wifi_init_apsta finished. SSID:%s password:%s",
             AP_WIFI_SSID, AP_WIFI_PASS);
}

esp_err_t send_web_page(httpd_req_t *req)
{
    int response;
    append_err(errbuffer, "-- From inside send_web_page --");
    sprintf(response_data, PAGE_HTML, "testing if this works");

    response = httpd_resp_send(req, response_data, HTTPD_MAX_URI_LEN);
    return response;
}

esp_err_t send_errors(httpd_req_t *req)
{
    int response;
    append_err(errbuffer, "-- From inside send_errors --");
    sprintf(response_data, PAGE_ERR_HTML, errbuffer);

    response = httpd_resp_send(req, response_data, HTTPD_MAX_URI_LEN);
    return response;
}


esp_err_t favicon_handler(httpd_req_t *req)
{
    httpd_resp_set_status(req, "204 No Content");
    return httpd_resp_send(req, NULL, 0);
}

httpd_uri_t uri_get = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = send_web_page,
    .user_ctx = NULL
};

httpd_uri_t uri_get_err = {
    .uri = "/err",
    .method = HTTP_GET,
    .handler = send_errors,
    .user_ctx = NULL
};

httpd_uri_t uri_favicon = {
    .uri = "/favicon.ico",
    .method = HTTP_GET,
    .handler = favicon_handler,
    .user_ctx = NULL
};

void Server_init(){
    append_err(errbuffer, "-- From inside Server_init --");
    fs_init();

    memset((void *)errbuffer, 0, sizeof(errbuffer));
    
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_get_err);
        httpd_register_uri_handler(server, &uri_favicon);
    }
}





