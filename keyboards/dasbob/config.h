// Copyright 2024 moonwellprogrammer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// From Dasbob Default Config ----------------------------------------------------------------

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define DIRECT_PINS { \
    { GP13, GP28, GP12, GP29, GP0 }, \
    { GP22, GP14, GP26, GP4,  GP27}, \
    { GP21, GP23, GP7, GP20, GP6 }, \
    { GP16, GP9, GP8, NO_PIN, NO_PIN } \
}

#define DIRECT_PINS_RIGHT {  \
    { GP0, GP29, GP12, GP28, GP13 }, \
    { GP27, GP4, GP26, GP14, GP22}, \
    { GP6, GP20, GP7, GP23, GP21 }, \
    { GP8, GP9, GP16, NO_PIN, NO_PIN } \
}

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Serial Config */
#define USE_SERIAL
#define SERIAL_USART_TX_PIN GP1
#define MASTER_LEFT

#define USB_VBUS_PIN 19
#define AUDIO_PWM_DRIVER PWMD2
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4
#define AUDIO_PIN GP5
#ifdef AUDIO_ENABLE
    #define AUDIO_INIT_DELAY
    #define AUDIO_CLICKY
    #define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f
    #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

#define STARTUP_SOUND E__NOTE(_E6), E__NOTE(_A6), ED_NOTE(_E7),


// From Ben Vallack's Custom Config -----------------------------------------------------------


#undef TAPPING_TERM
#define TAPPING_TERM 240

#define RETRO_TAPPING

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 5

#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 16

#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 1

#undef MOUSEKEY_INITIAL_SPEED 
#define MOUSEKEY_INITIAL_SPEED 1

#undef MOUSEKEY_DECELERATED_SPEED
#define MOUSEKEY_DECELERATED_SPEED 12

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 22

#define USB_SUSPEND_WAKEUP_DELAY 0

#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 83

#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 83

#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 3