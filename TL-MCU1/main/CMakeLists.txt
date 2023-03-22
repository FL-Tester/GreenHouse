idf_component_register( SRCS "main.c"
                             "lora.c"
                             "lvgl_user.c"
                             "wifi_mqtt.c"
                             "task.c"
                    INCLUDE_DIRS "./" 
                    "./include/"
                    )
