#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// start timer，resturn starting time
int64_t perf_timer_start(void);

// ending countdown oupput tag message
void perf_timer_end(int64_t start_time, const char *tag, const char *msg);

bool perf_timer_cnt(int64_t start_time,int64_t end_time, const char *tag, const char *msg);

#ifdef __cplusplus
}
#endif