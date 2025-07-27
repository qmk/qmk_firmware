// Copyright 2022 grooovebob (@grooovebob)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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

/* I2C Pin mapping */
//#define I2C1_SDA_PIN GP7
//#define I2C1_SCL_PIN GP6
//#define I2C1_CLOCK_SPEED 400000
//#define I2C_DRIVER I2CD2

// Set the mouse settings to a comfortable speed/accuracy trade-off,
// assuming a screen refresh rate of 60 Htz or higher
// The default is 50. This makes the mouse ~3 times faster and more accurate
#define MOUSEKEY_INTERVAL 16
// The default is 20. Since we made the mouse about 3 times faster with the previous setting,
// give it more time to accelerate to max speed to retain precise control over short distances.
#define MOUSEKEY_TIME_TO_MAX 40
// The default is 300. Let's try and make this as low as possible while keeping the cursor responsive
#define MOUSEKEY_DELAY 100
// It makes sense to use the same delay for the mouseweel
#define MOUSEKEY_WHEEL_DELAY 100
// The default is 100
#define MOUSEKEY_WHEEL_INTERVAL 50
// The default is 40
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
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
