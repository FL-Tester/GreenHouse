#include <stdio.h>
#include "sdkconfig.h"  
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl_helpers.h"

//static const char *TAG = "main_tag";

void init_task(void *pvParameter);              // 初始化任务     
void data_process_task(void *pvParameter);      //数据处理任务 mqttpush setobj

TaskHandle_t    init_task_handle = NULL,
                lvgl_task_handle = NULL, 
                lora_task_handle = NULL,
                data_process_task_handle = NULL;

uint8_t* recv_data;                    //数据指针

