#pragma once 

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_compiler.h"
#include "esp_netif_ip_addr.h"
#include "mqtt_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"

esp_mqtt_client_handle_t client_task;  //mqtt句柄


void wifi_init(void);                           //wifi初始化                    
void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
