idf_component_register(SRCS "lvgl_app.c"
                    INCLUDE_DIRS "./include/"

                    REQUIRES  lvgl
                              lvgl_esp32_drivers
                              lvgl_porting
                        )

                    