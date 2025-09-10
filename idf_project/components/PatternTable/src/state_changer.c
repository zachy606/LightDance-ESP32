#include "state_changer.h"
#include "app_config.h"
#include "esp_log_level.h"
#include "sdcard.h"          // for un/mount helpers
#include "esp_log.h"
#include "testing.h"

#include <stdio.h>           // fgets, printf
#include <string.h>          // strtok, strcmp, strcspn
#include <stdlib.h>          // atoi

#define TAG "state"


void state_init(player *p){

    player_reader_init(p,MOUNT_POINT,TIME_DATA,FRAME_DATA);
    player_var_init(p);
    ESP_LOGI(TAG,"start init");
    PatternTable_read_frame_at(&p->Reader,p->reader_index,&p->fd_test[p->reader_index%2]);
    PatternTable_read_frame_go_through(&p->Reader,&p->fd_test[(p->reader_index+1)%2]);
    
    
    timer_init(p);
}

void state_start(player *p, PlayerState *state){

    if(*state == STATE_IDLE||*state == STATE_STOPPED){
        *state = STATE_RUNNING;
        // p->reader_index = start_frame_index;
        player_start(p);
    }
    else{
        ESP_LOGI(TAG,"wonrg state not allow to start");
    }

}


void state_pause(player *p, PlayerState *state){

    if(*state == STATE_RUNNING){
        player_pause(p);
        *state = STATE_PAUSED;

    }
    else{
        ESP_LOGI(TAG,"wonrg state not allow to paused");
        ESP_LOGI(TAG,"now state %d",*state );
    }

}


void state_resume(player *p, PlayerState *state){
    
    if(*state == STATE_PAUSED){
        player_resume(p);
        *state = STATE_RUNNING;

    }
    else{
        ESP_LOGI(TAG,"wonrg state not allow to resume");
        ESP_LOGI(TAG,"now state %d",*state );
    }
}

void state_stop(player *p, PlayerState *state){

    if(*state == STATE_RUNNING){

        *state = STATE_STOPPED;
        player_pause(p);
        player_stop(p);

    }
    else if(*state == STATE_PAUSED){
        *state = STATE_STOPPED;
        player_stop(p);
    }
    else{
        ESP_LOGI(TAG,"wonrg state not allow to stop");
        ESP_LOGI(TAG,"now state %d",*state );
    }
}

void state_exit(player *p, PlayerState *state){
    
    
    if(*state == STATE_STOPPED){

        *state = STATE_EXITING;
        fclose(p->Reader.data_fp);
        unmount_sdcard(&p->Reader.card);
        ESP_LOGI(TAG, "Main exits.");

    }
    else{
        ESP_LOGI(TAG,"wonrg state not allow to exit");
        ESP_LOGI(TAG,"now state %d",*state );
    }
}
    
void state_delay(player *p, PlayerState *state,int delaytime,int delaylight){

    if(*state == STATE_STOPPED ||*state == STATE_IDLE){
        delaytime = 0;
        delaylight = 0;
        int64_t delay = perf_timer_start();
        while(!perf_timer_cnt(delay,delaytime,"DELAY", "DELAYTIME")){
            
            if(perf_timer_cnt(delay,delaylight,"DELAY", "DELAYlight")){

            }
            vTaskDelay(10);
        }
    
    }
    else{
        ESP_LOGI(TAG,"wonrg state not allow to delay");
        ESP_LOGI(TAG,"now state %d",*state );
    }
    
        
}

void get_state(PlayerState *state){
    
    if(*state == STATE_IDLE ){
        ESP_LOGI(TAG,"now is STATE_IDLE ");
    }
    else if(*state == STATE_RUNNING ){
        ESP_LOGI(TAG,"now is STATE_RUNNING ");
    }
    else if(*state == STATE_PAUSED ){
        ESP_LOGI(TAG,"now is STATE_PAUSED ");
    }
    else if(*state == STATE_STOPPED ){
        ESP_LOGI(TAG,"now is STATE_STOPPED ");
    }
    else if(*state == STATE_EXITING ){
        ESP_LOGI(TAG,"now is STATE_EXITING ");
    }
    else if(*state == STATE_DELAY ){
        ESP_LOGI(TAG,"now is STATE_DELAY ");
    }
}