/*
 * @description	: 融合通信mcu1
 * @version     : 1.3
 * @author      : FengLE
*/
#include "stdio.h"
#include "task.h"
#include "nvs_flash.h"


void app_main(void){
    esp_err_t err = nvs_flash_init();           //nvs init
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    xTaskCreate(init_task, "init_task", 4096, NULL, 5, NULL);

}

#if 0   // psram test
#include "esp_heap_caps.h"
void psram_test(void){
    int *p = (int *)heap_caps_malloc(1000 * sizeof(int), MALLOC_CAP_SPIRAM);
    for (int i = 0; i < 1000; i++) 
        p[i] = i;
    printf ("p[100] : %d\n" , p[100]);
    if (p == NULL) 
        printf("malloc failed\n");
    else
        printf("malloc success\n");

}

#endif 
 


