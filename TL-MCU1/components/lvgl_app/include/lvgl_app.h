#pragma once

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demos.h"
#include "lvgl_helpers.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

void user_ui_init(void);

lv_obj_t* mcu2_CO2;
lv_obj_t* mcu2_T;
lv_obj_t* mcu2_H;
lv_obj_t* mcu3_T;
lv_obj_t* mcu3_H;
