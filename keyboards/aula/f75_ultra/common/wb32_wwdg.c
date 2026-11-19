// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include <stdlib.h>
#include "wwdg.h"

bool     feed_dog            = false;
bool     wwdg_saved_feed_dog = false;
bool     enable_dog          = false;
uint16_t wwdg_time           = 0;

bool process_record_kb_dg(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_Q: {
            if (record->event.pressed) {
                Disable_WWDG();
                feed_dog = false;
            }
            return false;
        }
        case KC_T: {
            if (record->event.pressed) {
                enable_dog = true;
                return false;
            }
        }
        case KC_R: {
            if (record->event.pressed) {
                RCC->CLRRSTSTAT = RCC_CLRRSTSTAT_CLR;

                setPinOutputOpenDrain(C15);
                writePinLow(C15);
                wait_ms(1);
                writePinHigh(C15);
                wait_ms(20);

                WWDG_SetCounter(127);
                // time = timer_read();

                rgb_matrix_init();
                // uprintf("snled27351 reset!!\n");

                // uprintf("%ld\n", RCC->RSTSTAT);
                // for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++) {
                //     // snled27351_sw_return_normal(i);
                //     snled27351_init(i);
                // }

                return false;
            }
        }
        case KC_Y: {
            if (record->event.pressed) {
                // rgb_matrix_init();
                uprintf("%ld\n", RCC->RSTSTAT);
                // for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++) {
                //     // snled27351_sw_return_normal(i);
                //     snled27351_init(i);
                // }

                return true;
            }
        }
        case KC_U: {
            if (record->event.pressed) {
                // RCC->CLRRSTSTAT = RCC_CLRRSTSTAT_CLR;

                return true;
            }
        }

        default:
            break;
    }
    return true;
}

void wwdg_init(void) {
    feed_dog = true;
    Init_WWDG();
    WWDG_Enable(127);
    wwdg_time = timer_read();
}

#if 0
void housekeeping_task_kb(void) {
    if (enable_dog) {
        enable_dog = false;
        feed_dog   = true;
        Init_WWDG();
        WWDG_Enable(127);
        wwdg_time = timer_read();
    }
    if (timer_elapsed(wwdg_time) > 10) {
        wwdg_time = timer_read();
        if (feed_dog) {
            WWDG_SetCounter(127);
        }
    }
}
#endif

void snled27351_reset(void) {
    setPinOutputOpenDrain(C11);
    writePinLow(C11);
    wait_ms(1);
    writePinHigh(C11);
    wait_ms(20);

    WWDG_SetCounter(127);
    wwdg_time = timer_read();

    rgb_matrix_init();
}
