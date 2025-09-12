#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include "player_content.h"
#include "sdmmc_cmd.h"

void player_init(player *p);
void player_start(player *p);
void player_resume(player *p);
void player_pause(player *p);
void player_stop(player *p);
void player_delay(player *p,int delaytime,int delaylight);
void player_exit(player *p);

void player_get_state(player *p);

#ifdef __cplusplus
}
#endif
