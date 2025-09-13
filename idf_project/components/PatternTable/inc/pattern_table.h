

#pragma once

#include "app_config.h"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "sdmmc_cmd.h"
#include "led_def.h"

#define MAX_PARTS 40
// MAX_PARTS : MAX total num of led stripes + OFs

#define MAX_COLOR_VALUES 4096 
// MAX_PARTS : total num of leds 

#define MAX_FRAMES 2048
// MAX_PARTS : MAX total num of Frames

typedef struct {
    bool fade;
    uint8_t colors[MAX_COLOR_VALUES][4]; // RGBA
} FrameData;

typedef struct {
    FILE *data_fp;
    FILE *time_fp;

    int total_parts;
    int part_lengths[MAX_PARTS];
    int total_leds;
    int fps;
    int total_frames;
    int index; //current Frame in read
    uint32_t frame_times[MAX_FRAMES];       // in milliseconds
    int frame_offsets[MAX_FRAMES];       // byte offset of each frame

    const char *mount_point;
    sdmmc_card_t *card;

    led_config_t led_config_arr[LED_CONFIG_NUM];
    
} PatternTable;


void print_framedata(const FrameData *frame_data);

void PatternTable_init(PatternTable *self, const char *mount_point);
esp_err_t PatternTable_load_times(PatternTable *self);
esp_err_t PatternTable_index_frames(PatternTable *self);
esp_err_t PatternTable_read_frame_at( PatternTable *self, const int index,FrameData *framedata);
esp_err_t PatternTable_read_frame_go_through( PatternTable *self,FrameData *framedata);

void PatternTable_construct_led_config(PatternTable *self);

const uint32_t *PatternTable_get_time_array(const PatternTable *self);
int PatternTable_get_total_frames(const PatternTable *self);
int PatternTable_get_total_leds(const PatternTable *self);

#ifdef __cplusplus
}
#endif