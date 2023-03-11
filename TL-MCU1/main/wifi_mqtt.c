#include "wifi_mqtt.h"

static wifi_sta_config_t wifi_sta_config = {
        .ssid = "FengLE",
        .password = "987654321",
};

//mqtt config
static esp_mqtt_client_config_t mqtt_config = {
        .uri = "mqtt://175.178.79.144",
        .username = "admin",
        .password = "password",
        .port = 1883,
};


void wifi_init(void){
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    //2
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_config(WIFI_IF_STA, (wifi_config_t *) &wifi_sta_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL, NULL);
    esp_wifi_start();
    
    client_task = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_start(client_task);
}

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    }

    if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI("TEST_ESP32", "Got IP: " IPSTR,  IP2STR(&event->ip_info.ip));
    }
}