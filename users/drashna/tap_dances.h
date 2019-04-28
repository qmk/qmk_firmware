#pragma once
#include "drashna.h"

//define diablo macro timer variables
extern uint8_t diablo_times[];
typedef struct {
    uint16_t timer;
    uint8_t key_time;
} diablo_timer_t;

extern diablo_timer_t diablo_timer[4];

void run_diablo_macro_check(void);

#ifdef TAP_DANCE_ENABLE
enum {
    TD_D3_1 = 0,
    TD_D3_2,
    TD_D3_3,
    TD_D3_4
};
#endif // TAP_DANCE_ENABLE
