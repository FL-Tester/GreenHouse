#include "lvgl_user.h"
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demos.h"
#include "lvgl_helpers.h"
#include "lvgl_app.h"

void lv_tick_task(void *arg){
	(void)arg;
	lv_tick_inc(LV_TICK_PERIOD_MS);
}

//lvgl task
void lvgl_init_task(void *pvParameter){
    vTaskDelay(pdMS_TO_TICKS(100));
    lv_init();
    lv_port_disp_init();  
    lv_port_indev_init();
    lv_group_t *group = lv_group_create();
    lv_indev_set_group(indev_keypad, group);

#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = touch_driver_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10 * 1000));

//user UI
    user_ui_init();
    vTaskDelay(pdMS_TO_TICKS(200)); 
    while(1){
        lv_task_handler();
        lv_tick_inc(LV_TICK_PERIOD_MS);
        vTaskDelay(pdMS_TO_TICKS(LV_TICK_PERIOD_MS));
    }
}