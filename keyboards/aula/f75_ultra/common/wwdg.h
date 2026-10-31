// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "wb32fq95xx.h"

#include <stdbool.h>
#include "quantum.h"

#define CR_WDGA_Set ((uint32_t)0x00000080)
#define CFR_WDGTB_Mask ((uint32_t)0xFFFFFE7F)
#define CFR_W_Mask ((uint32_t)0xFFFFFF80)
#define BIT_Mask ((uint8_t)0x7F)
#define WWDG_Prescaler_1 ((uint32_t)0x00000000)
#define WWDG_Prescaler_2 ((uint32_t)0x00000080)
#define WWDG_Prescaler_4 ((uint32_t)0x00000100)
#define WWDG_Prescaler_8 ((uint32_t)0x00000180)

void WWDG_SetCounter(uint8_t Counter);
void WWDG_Enable(uint8_t Counter);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_Init(void);
void WWDG_Deinit(void);
void Init_WWDG(void);
void Disable_WWDG(void);

// Watchdog pause/resume helpers for long blocking operations (e.g., EEPROM, sleep)
extern bool     feed_dog;
extern uint16_t wwdg_time;

static inline void wwdg_pause(void) {
    extern bool wwdg_saved_feed_dog;
    wwdg_saved_feed_dog = feed_dog;
    // Only disable if watchdog is actually running
    if (feed_dog) {
        feed_dog = false;
        Disable_WWDG();
    }
}

static inline void wwdg_resume(void) {
    extern bool wwdg_saved_feed_dog;
    // Only re-enable if watchdog was running before pause
    if (wwdg_saved_feed_dog) {
        feed_dog = true;
        Init_WWDG();
        WWDG_Enable(127);
        wwdg_time = timer_read(); // Reset timer so watchdog gets fed immediately
    }
}

// Feed watchdog without disabling it - use before long operations that don't need full pause
static inline void wwdg_feed(void) {
    if (feed_dog) {
        WWDG_SetCounter(127);
        wwdg_time = timer_read();
    }
}

// void wwdg_init(void);
