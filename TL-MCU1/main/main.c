/*
 * @description	: 融合通信mcu1
 * @version     : 1.2
 * @author      : FengLE
*/

#include "main.h"
#include "lvgl_app.h"  
#include "lora.h"
#include "wifi_mqtt.h"
#include "lvgl_user.h"

void app_main(void){
    xTaskCreate(init_task, "init_task", 4096, NULL, 5, &init_task_handle);
}

//数据处理任务 -- mqtt推送，lvgl显示
void data_process_task(void *pvParameter){
    while(1){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        char text_buf[7];
        memcpy (text_buf, recv_data, 7);
        esp_mqtt_client_publish(client_task, "/IOT/TL-CD", text_buf, 7, 0, 0);   // mqtt push
        lv_label_set_text_fmt (mcu2_CO2, "%dppm", recv_data[5]*256+ recv_data[6]);  // lvgl set
        lv_label_set_text_fmt (mcu2_T, "%d°C", recv_data[1]); 
        lv_label_set_text_fmt (mcu2_H, "%d%%", recv_data[2]); 
        lv_label_set_text_fmt (mcu3_T, "%d°C", recv_data[3]); 
        lv_label_set_text_fmt (mcu3_H, "%d%%", recv_data[4]); 
    }
}

//任务初始化函数
void init_task(void *pvParameter){
    lora_init();   
    vTaskDelay(pdMS_TO_TICKS(50)); // 等待串口初始化完成   
    xTaskCreatePinnedToCore(lvgl_init_task, "lvgl_init_task", 1024 * 10, NULL, 3, &lvgl_task_handle,1);
    vTaskDelay(pdMS_TO_TICKS(1000)); // 等待lvgl初始化完成 
    user_ui_init();    
    vTaskDelay(pdMS_TO_TICKS(50));  // 等待UI初始化完成   
    xTaskCreatePinnedToCore(lora_task, "lora_task", 1024 * 4, NULL, 3, &lora_task_handle,0);           
    vTaskDelay(pdMS_TO_TICKS(1000));
    wifi_init();
    vTaskDelay(pdMS_TO_TICKS(2000));  
    xTaskCreatePinnedToCore(data_process_task, "data_process_task", 1024 * 4, NULL, 3, &data_process_task_handle,0);             vTaskDelay(pdMS_TO_TICKS(50));
    vTaskDelete(NULL);
}
