/* Copyright 2020 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* USB Device descriptor parameter */
#undef VENDOR_ID
#define VENDOR_ID 0x1209
#undef PRODUCT_ID
#define PRODUCT_ID 0x345C
#undef DEVICE_VER
#define DEVICE_VER 0x0001
#undef MANUFACTURER
#define MANUFACTURER "https://github.com/stapelberg"
#undef PRODUCT
#define PRODUCT "kinT (kint41)"

/* key matrix size */
#define MATRIX_ROWS 15
#define MATRIX_COLS 7

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS               \
    {                                 \
        LINE_PIN8,      /* ROW_EQL */ \
            LINE_PIN9,  /* ROW_1 */   \
            LINE_PIN10, /* ROW_2 */   \
            LINE_PIN11, /* ROW_3 */   \
            LINE_PIN7,  /* ROW_4 */   \
            LINE_PIN16, /* ROW_5 */   \
            LINE_PIN5,  /* ROW_6 */   \
            LINE_PIN3,  /* ROW_7 */   \
            LINE_PIN4,  /* ROW_8 */   \
            LINE_PIN1,  /* ROW_9 */   \
            LINE_PIN0,  /* ROW_0 */   \
            LINE_PIN2,  /* ROW_MIN */ \
            LINE_PIN17, /* ROW_ESC */ \
            LINE_PIN23, /* ROW_F1 */  \
            LINE_PIN21 /* ROW_F2 */  \
    }

#define MATRIX_COL_PINS             \
    {                               \
        LINE_PIN18,     /* COL_0 */ \
            LINE_PIN14, /* COL_1 */ \
            LINE_PIN15, /* COL_2 */ \
            LINE_PIN20, /* COL_3 */ \
            LINE_PIN22, /* COL_4 */ \
            LINE_PIN19, /* COL_5 */ \
            LINE_PIN6   /* COL_6 */ \
    }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Well-worn Cherry MX key switches can bounce for up to 20ms, despite the
 * Cherry data sheet specifying 5ms. Because we use the sym_eager_pk debounce
 * algorithm, this debounce latency only affects key releases (not key
 * presses). */
#undef DEBOUNCE
#define DEBOUNCE 20

#define IGNORE_MOD_TAP_INTERRUPT

// The Teensy 4.1 consumes about 100 mA of current at its full speed of 600 MHz
// as per https://www.pjrc.com/store/teensy41.html
#define USB_MAX_POWER_CONSUMPTION 100

/* We use the i.MX RT1060 high-speed GPIOs (GPIO6-9) which are connected to the
 * AHB bus (AHB_CLK_ROOT), which runs at the same speed as the ARM Core Clock,
 * i.e. 600 MHz. See MIMXRT1062, page 949, 12.1 Chip-specific GPIO information.
 * No additional delay is necessary. */

// in clock cycles
#define GPIO_INPUT_PIN_DELAY 0

#define LED_PIN_ON_STATE 0
#define LED_NUM_LOCK_PIN LINE_PIN26
#define LED_CAPS_LOCK_PIN LINE_PIN12
#define LED_SCROLL_LOCK_PIN LINE_PIN25
#define LED_COMPOSE_PIN LINE_PIN24
