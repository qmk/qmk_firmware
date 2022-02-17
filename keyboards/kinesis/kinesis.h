#pragma once

#if defined(KEYBOARD_kinesis_alvicstep)
#    include "alvicstep.h"
#elif defined(KEYBOARD_kinesis_stapelberg)
#    include "stapelberg.h"
#elif defined(KEYBOARD_kinesis_kint2pp)
#    include "kint2pp.h"
#elif defined(KEYBOARD_kinesis_nguyenvietyen)
#    include "nguyenvietyen.h"
#elif defined(KEYBOARD_kinesis_kint36)
#    include "kint36.h"
#elif defined(KEYBOARD_kinesis_kint41)
#    include "kint41.h"
#endif

#include "quantum.h"

void all_led_off(void);
void all_led_on(void);
void num_lock_led_on(void);
void caps_lock_led_on(void);
void scroll_lock_led_on(void);
void keypad_led_on(void);
