idf_component_register(SRCS 
                            "src/player.c"
                            "src/pattern_table.c"
                            "src/sdcard.c"
                            "src/state_changer.c"
                            "src/testing.c"
                    INCLUDE_DIRS "inc"
                    REQUIRES fatfs driver esp_timer)
