/*
Copyright 2020 Purdea Andrei
Copyright 2021-2023 Matthew J Wolf

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 9
// Note: physical column are 16, but only 11 are ever used. Column 0..9 match the physical column. Column 10 is physical column 15.

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

#define HOLD_ON_OTHER_KEY_PRESS

/* XWHATSIT CONTROLLER TYPE */
#define CONTROLLER_IS_XWHATSIT_MODEL_F_OR_WCASS_MODEL_F

#define CAPSENSE_KEYBOARD_SETTLE_TIME_US 8
#define CAPSENSE_DAC_SETTLE_TIME_US 8
#define CAPSENSE_HARDCODED_SAMPLE_TIME 4

#define CAPSENSE_CAL_ENABLED 1
#define CAPSENSE_CAL_DEBUG 0
#define CAPSENSE_CAL_INIT_REPS 16
#define CAPSENSE_CAL_EACHKEY_REPS 16
#define CAPSENSE_CAL_BINS 5
#define CAPSENSE_CAL_THRESHOLD_OFFSET 24

#if !CAPSENSE_CAL_ENABLED
#define CAPSENSE_HARDCODED_THRESHOLD 142
#endif

#define CAPSENSE_KEYMAP_COL_TO_PHYSICAL_COL(col) (((col) == 8)?15:(col))

// By default we set up for support of xwhatsit's solenoid driver board.
// Comment out HAPTIC_ENABLE_PIN if you don't have an enable pin:
#define HAPTIC_ENABLE_PIN B7
// We disable haptic feedbeck during USB low power conditions:
#define HAPTIC_OFF_IN_LOW_POWER 1
// Change this if you are using a different pin for the solenoid:
#define SOLENOID_PIN B6
// If you are not using a solenoid then comment out the above, and also in rules.mk, remove "HAPTIC_ENABLE += SOLENOID"
// You can also tune the following for your solenoid:
#define SOLENOID_DEFAULT_DWELL 4
#define SOLENOID_MIN_DWELL 4
#define NO_HAPTIC_MOD

// ----- xwhatsit hardware configuration (type_f) -----

#define CAPSENSE_DAC_SCLK   B1
#define CAPSENSE_DAC_DIN    B2
#define CAPSENSE_DAC_SYNC_N B0
#define CAPSENSE_DAC_MAX    1023

#define CAPSENSE_SHIFT_DIN  D4
#define CAPSENSE_SHIFT_OE   D5
#define CAPSENSE_SHIFT_SHCP D7
#define CAPSENSE_SHIFT_STCP D6
#define CAPSENSE_SHIFT_STCP_IO _SFR_IO_ADDR(PORTD)
#define CAPSENSE_SHIFT_STCP_BIT 6

#define SETUP_ROW_GPIOS() \
        do { \
            PORTC |= 0xF0; \
            PORTD |= 0x0F; \
        } while (0)

#define SETUP_UNUSED_PINS() do {} while (0)

#define CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE 2
#define CAPSENSE_READ_ROWS_PIN_1 _SFR_IO_ADDR(PINC)
#define CAPSENSE_READ_ROWS_PIN_2 _SFR_IO_ADDR(PIND)
#define CAPSENSE_READ_ROWS_ASM_INSTRUCTIONS "in %[dest_row_1], %[ioreg_row_1]\n\tin %[dest_row_2], %[ioreg_row_2]"
#define CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS \
        "st %a[arr]+, %[dest_row_1]"       "\n\t" \
        "st %a[arr]+, %[dest_row_2]"
#define CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS_FAKE \
        "st %a[arr], %[dest_row_1]"       "\n\t" \
        "st %a[arr], %[dest_row_2]"
#define CAPSENSE_READ_ROWS_OUTPUT_CONSTRAINTS [dest_row_1] "=&r" (dest_row_1), [dest_row_2] "=&r" (dest_row_2)
#define CAPSENSE_READ_ROWS_INPUT_CONSTRAINTS [ioreg_row_1] "I" (CAPSENSE_READ_ROWS_PIN_1), [ioreg_row_2] "I" (CAPSENSE_READ_ROWS_PIN_2)
#define CAPSENSE_READ_ROWS_LOCAL_VARS uint8_t dest_row_1, dest_row_2
#define CAPSENSE_READ_ROWS_EXTRACT_FROM_ARRAY do { dest_row_1 = array[p0++]; dest_row_2 = array[p0++]; } while (0)

#if (!defined(CAPSENSE_CONDUCTIVE_PLASTIC_IS_PUSHED_DOWN_ON_KEYPRESS)) && (!defined(CAPSENSE_CONDUCTIVE_PLASTIC_IS_PULLED_UP_ON_KEYPRESS))
  #define CAPSENSE_CONDUCTIVE_PLASTIC_IS_PUSHED_DOWN_ON_KEYPRESS
#endif
#define CAPSENSE_KEYMAP_ROW_TO_PHYSICAL_ROW(row) (7-(row))
#define CAPSENSE_PHYSICAL_ROW_TO_KEYMAP_ROW(row) (7-(row))
#define CAPSENSE_READ_ROWS_VALUE ((dest_row_1 >> 4) | (dest_row_2 << 4))
