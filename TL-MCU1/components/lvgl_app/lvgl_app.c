#include <stdio.h>
#include "lvgl_app.h"

void user_ui_init(void){
    
#if 0
    //开机动画
    lv_obj_t* label_start = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_start, 120, 30);
    lv_obj_set_pos(label_start, 140, 100);
    lv_label_set_text(label_start, "Starting.....");

    lv_obj_t* label_VER = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_VER, 180, 20);
    lv_obj_set_pos(label_VER, 0, 220);
    lv_label_set_text(label_VER, "LVGL-DEMO(FengLE)");

    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, 50, 5);
    lv_obj_align_to(obj, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, 2000);
    lv_anim_set_values(&a, 0, 270);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_start(&a);
    vTaskDelay(pdMS_TO_TICKS(1700));
    lv_obj_del(obj);
    lv_obj_del(label_start);
    lv_obj_del(label_VER);

#endif

    //标题 框
    static lv_point_t line_points[] = {{10, 5},{310, 5}, {310, 30}, {10, 30}, {10, 5}};
    lv_obj_t* line1 = lv_line_create(lv_scr_act());  
    lv_line_set_points(line1, line_points, 5);

    // //RGB 框
    // static lv_point_t line_points_2[] = {{310, 40},{310, 200}, {270, 200}, {270, 40}, {310, 40}};
    // lv_obj_t* line2 = lv_line_create(lv_scr_act());  
    // lv_line_set_points(line2, line_points_2, 5);

    //信息 框
    static lv_point_t line_points_3[] = {{10, 40}, {310, 40}, {310, 230}, {10, 230}, {10, 40}};
    lv_obj_t* line3 = lv_line_create(lv_scr_act());  
    lv_line_set_points(line3, line_points_3, 5);
    static lv_point_t line_points_4[] = {{160, 40}, {160, 230}};
    lv_obj_t* line4 = lv_line_create(lv_scr_act());  
    lv_line_set_points(line4, line_points_4, 2);
    vTaskDelay(pdMS_TO_TICKS(10));
    //
    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_obj_set_size(label, 200, 30);
    lv_obj_set_pos(label, 80, 10);
    lv_label_set_text(label, "Intelligent greenhouse system");
    vTaskDelay(pdMS_TO_TICKS(10));
    // mcu2 text
    lv_obj_t* label_mcu_text = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu_text, 50, 30);
    lv_obj_set_pos(label_mcu_text, 20, 60);
    lv_label_set_text(label_mcu_text, "MCU2:");
    vTaskDelay(pdMS_TO_TICKS(10));
    //mcu2 co2
    lv_obj_t* label_mcu_co2 = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu_co2, 50, 30);
    lv_obj_set_pos(label_mcu_co2, 20, 100);
    lv_label_set_text(label_mcu_co2, "CO2:");
    vTaskDelay(pdMS_TO_TICKS(10));
    //mcu2 h
    lv_obj_t* label_mcu_t = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu_t, 50, 30);
    lv_obj_set_pos(label_mcu_t, 20, 140);
    lv_label_set_text(label_mcu_t, "T:");
    vTaskDelay(pdMS_TO_TICKS(10));
    //mcu2 t
    lv_obj_t* label_mcu_h = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu_h, 50, 30);
    lv_obj_set_pos(label_mcu_h, 20, 180);
    lv_label_set_text(label_mcu_h, "H:");
    vTaskDelay(pdMS_TO_TICKS(10));

    // mcu3 text
    lv_obj_t* label_mcu3_text = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu3_text, 50, 30);
    lv_obj_set_pos(label_mcu3_text, 170, 60);
    lv_label_set_text(label_mcu3_text, "MCU3:");
    vTaskDelay(pdMS_TO_TICKS(10));
    // mcu3 t
    lv_obj_t* label_mcu3_t = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu3_t, 50, 30);
    lv_obj_set_pos(label_mcu3_t, 170, 100 );
    lv_label_set_text(label_mcu3_t, "T:");
    vTaskDelay(pdMS_TO_TICKS(10));
    // mcu3 h
    lv_obj_t* label_mcu3_h = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu3_h, 50, 30);
    lv_obj_set_pos(label_mcu3_h, 170, 140);
    lv_label_set_text(label_mcu3_h, "H:");
    vTaskDelay(pdMS_TO_TICKS(10));
    //mcu2 data
    lv_obj_t* label_mcu_co2_data = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu_co2_data, 50, 30);
    lv_obj_set_pos(label_mcu_co2_data, 70, 100);
    lv_label_set_text(label_mcu_co2_data, "None");
    mcu2_CO2 = label_mcu_co2_data;
    vTaskDelay(pdMS_TO_TICKS(10));
    lv_obj_t* label_mcu_t_data = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu_t_data, 50, 30);
    lv_obj_set_pos(label_mcu_t_data, 70, 140);
    lv_label_set_text(label_mcu_t_data, "None");
    mcu2_T = label_mcu_t_data;
    vTaskDelay(pdMS_TO_TICKS(10));
    lv_obj_t* label_mcu_h_data = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu_h_data, 50, 30);
    lv_obj_set_pos(label_mcu_h_data, 70, 180);
    lv_label_set_text(label_mcu_h_data, "None");
    mcu2_H = label_mcu_h_data;
    vTaskDelay(pdMS_TO_TICKS(10));
    //mcu3 data
    lv_obj_t* label_mcu3_t_data = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu3_t_data, 50, 30);
    lv_obj_set_pos(label_mcu3_t_data, 220, 100);
    lv_label_set_text(label_mcu3_t_data, "None");
    mcu3_T = label_mcu3_t_data;
    vTaskDelay(pdMS_TO_TICKS(10));
    lv_obj_t* label_mcu3_h_data = lv_label_create(lv_scr_act());
    lv_obj_set_size(label_mcu3_h_data, 50, 30);
    lv_obj_set_pos(label_mcu3_h_data, 220, 140);
    lv_label_set_text(label_mcu3_h_data, "None");
    mcu3_H = label_mcu3_h_data;
    vTaskDelay(pdMS_TO_TICKS(10));
}
