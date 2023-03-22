#include "task.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl_helpers.h"
#include "lvgl_user.h"
#include "lora.h"
#include "wifi_mqtt.h"
#include "lvgl_app.h"
#include "cJSON.h"

//static const char *TAG = "task_tag";
void data_process_task(void *pvParameter);      //数据处理任务 mqttpush setobj

TaskHandle_t    init_task_handle = NULL,
                lvgl_task_handle = NULL, 
                lora_task_handle = NULL,
                data_process_task_handle = NULL;

uint8_t* recv_data;  //数据指针

//数据处理函数
void data_process(uint8_t *data){
    static char mqtt_buf[50];
    static char text_buf[7];
    memcpy (text_buf, data, 7);
    memset (mqtt_buf, 0, sizeof (mqtt_buf));
    cJSON *mqtt_pub = cJSON_CreateObject();
    cJSON_AddNumberToObject(mqtt_pub, "mcu2_T", text_buf[3]);
    cJSON_AddNumberToObject(mqtt_pub, "mcu2_H", text_buf[4]);
    cJSON_AddNumberToObject(mqtt_pub, "mcu2_CO2", text_buf[5]*256+ text_buf[6]);
    cJSON_AddNumberToObject(mqtt_pub, "mcu3_T", text_buf[1]);
    cJSON_AddNumberToObject(mqtt_pub, "mcu3_H", text_buf[2]);
    char *mqtt_pub_str = cJSON_Print(mqtt_pub);
    esp_mqtt_client_publish(client_task, "/IOT/TL-CD", mqtt_pub_str, strlen(mqtt_pub_str), 0, 0);   // mqtt push
    cJSON_Delete(mqtt_pub);
    lv_label_set_text_fmt (mcu2_CO2, "%dppm", recv_data[5]*256+ recv_data[6]);  // lvgl set
    lv_label_set_text_fmt (mcu2_T, "%d°C", recv_data[3]); 
    lv_label_set_text_fmt (mcu2_H, "%d%%", recv_data[4]); 
    lv_label_set_text_fmt (mcu3_T, "%d°C", recv_data[1]); 
    lv_label_set_text_fmt (mcu3_H, "%d%%", recv_data[2]); 
    //输出mqtt_pub中mcu2_CO2的值
    printf("mcu2_CO2: %d\n", cJSON_GetObjectItem(mqtt_pub, "mcu2_CO2")->valueint);
}

//数据处理任务 -- mqtt推送，lvgl显示
void data_process_task(void *pvParameter){
    vTaskDelay(pdMS_TO_TICKS(100));
    while(1){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        data_process(recv_data);
    }
}

//任务初始化函数
void init_task(void *pvParameter){
    lora_init(); 
    wifi_init();      
    xTaskCreatePinnedToCore(lvgl_init_task, "lvgl_init_task",
                            1024 * 8, NULL, 6, &lvgl_task_handle, 1);    //lvgl单独核心运行
    xTaskCreatePinnedToCore(lora_task, "lora_task", 
                            1024 * 4, NULL, 3, &lora_task_handle, 0);
    xTaskCreatePinnedToCore(data_process_task, "data_process_task", 
                            1024 * 4, NULL, 4, &data_process_task_handle, 0);
    vTaskDelete(NULL);
}


