// Copyright 2022 Andrew Dunai (@and3rson)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Andrew Dunai
#define PRODUCT         Endgame48 (v2)
#define DESCRIPTION     A 12x4 split ortholinear keyboard with encoder

/*
                 ┌────────┐
          ╭──────┤        ├──────╮
     RGB> ┿ D3   │        │  RAW ┿
          │      │        │      │
    PS2D> ┿ D2   └────────┘  GND ┿
          │                      │
          ┿ GND              RST ┿
          │      []      []      │
          ┿ GND              VCC ┿
          │                      │
     I2C> ┿ D1   ||| ||  ||   F4 ┿ <ROW5
          │                      │
     I2C> ┿ D0                F5 ┿ <COL1
          │          ╱╲          │
    ROW1> ┿ D4      ╱  ╲      F6 ┿ <COL2
          │        ╱    ╲        │
    ROW3> ┿ C6     ╲    ╱     F7 ┿ <COL3
          │         ╲  ╱         │
    COL7> ┿ D7       ╲╱       B1 ┿ <COL4
          │                      │
    ENCA> ┿ E6                B3 ┿ <COL5
          │                      │
    ENCB> ┿ B4                B2 ┿ <COL6
          │                      │
    ROW2> │ B5 B7 D5 C7 F1 F0 B6 ┿ <ROW6
          ╰────╂──╂──╂──╂──╂─────╯
               ┃  ┃     ┃  ┃
          ROW4 ┛  ┃     ┃  ┗ ROW8
                  ┃     ┃
             PS2C ┛     ┗ ROW7
 */

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 7

/* key matrix pins */
#define MATRIX_ROW_PINS { \
    D4, B5, C6, B7, \
    F4, B6, F1, F0 \
}

#define MATRIX_COL_PINS { \
    F5, F6, F7, B1, B3, B2, \
    D7 \
}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 20

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

/* RGB underglow */
#define RGB_DI_PIN D3

#ifdef RGB_DI_PIN
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_DEFAULT_VAL 0
#endif

/* Encoders */
#define ENCODERS_PAD_A { E6 }
#define ENCODERS_PAD_B { B4 }
#define ENCODER_RESOLUTION 4

/* Tapping config */
#define TAPPING_TERM 90
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

/* Reduce firmware size */
#define NO_ACTION_ONESHOT

/* Font */
#define OLED_FONT_H "glcdfont_48_v2.c"

/* Trackpoint */
#define PS2_MOUSE_INIT_DELAY 200

#ifdef PS2_USE_USART
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#endif

#ifdef PS2_USE_INT
/* Note: pins are swapped, so re-soldering is needed to test both modes */
#define PS2_CLOCK_PIN   D2
#define PS2_DATA_PIN    D5

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC21) |      \
              (0<<ISC20));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT2);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT2);        \
} while (0)
#define PS2_INT_VECT   INT2_vect
#endif
#endif
