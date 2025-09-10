#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include "player.h"
#include "sdmmc_cmd.h"

typedef enum {
    STATE_IDLE = 0,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED,
    STATE_DELAY,
    STATE_EXITING
} PlayerState;

void state_init(player *p);
void state_start(player *p, PlayerState *state);
void state_pause(player *p, PlayerState *state);
void state_resume(player *p, PlayerState *state);
void state_stop(player *p, PlayerState *state);
void state_exit(player *p, PlayerState *state);
void state_delay(player *p, PlayerState *state,int delaytime,int delaylight);
void get_state(PlayerState *state);

#ifdef __cplusplus
}
#endif
