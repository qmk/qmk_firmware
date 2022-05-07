/*
Copyright 2020 Purdea Andrei
Copyright 2022 Matthew J Wolf

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x0481
#define PRODUCT_ID 0x0002
#define DEVICE_VER 0x0001
#define MANUFACTURER Tom Wong-Cornall/Purdea Andrei/kmnov2017/listofoptions
#define PRODUCT IBM Displaywriter
#define DESCRIPTION QMK firmware for the IBM Displaywriter keyboards using a 'universal' xwhatsit controller PCB

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 12

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
//#define MATRIX_ROW_PINS { D0, D5 }
//#define MATRIX_COL_PINS { B2, B1, B0 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
//#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

// #define BACKLIGHT_PIN B7
// #define BACKLIGHT_BREATHING
// #define BACKLIGHT_LEVELS 3

// #define RGB_DI_PIN E2
// #ifdef RGB_DI_PIN
//   #define RGBLED_NUM 16
//   #define RGBLIGHT_HUE_STEP 8
//   #define RGBLIGHT_SAT_STEP 8
//   #define RGBLIGHT_VAL_STEP 8
//   #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
//   #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
// /*== all animations enable ==*/
//   #define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
//   #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//   #define RGBLIGHT_EFFECT_SNAKE
//   #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
// /*== customize breathing effect ==*/
//   /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//   #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
//   /*==== use exp() and sin() ====*/
//   #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//   #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
// #endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is userful for the Windows task manager shortcut (ctrl+shift+esc).
 */
// #define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

/*
 * Magic Key Options
 *
 * Magic keys are hotkey commands that allow control over firmware functions of
 * the keyboard. They are best used in combination with the HID Listen program,
 * found here: https://www.pjrc.com/teensy/hid_listen.html
 *
 * The options below allow the magic key functionality to be changed. This is
 * useful if your keyboard/keypad is missing keys and you want magic key support.
 *
 */

/* key combination for magic key command */
/* defined by default; to change, uncomment and set to the combination you want */
// #define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)

/* control how magic key switches layers */
//#define MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS  true
//#define MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS  true
//#define MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM false

/* override magic key keymap */
//#define MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS
//#define MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS
//#define MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM
//#define MAGIC_KEY_HELP           H
//#define MAGIC_KEY_HELP_ALT       SLASH
//#define MAGIC_KEY_DEBUG          D
//#define MAGIC_KEY_DEBUG_MATRIX   X
//#define MAGIC_KEY_DEBUG_KBD      K
//#define MAGIC_KEY_DEBUG_MOUSE    M
//#define MAGIC_KEY_VERSION        V
//#define MAGIC_KEY_STATUS         S
//#define MAGIC_KEY_CONSOLE        C
//#define MAGIC_KEY_LAYER0         0
//#define MAGIC_KEY_LAYER0_ALT     GRAVE
//#define MAGIC_KEY_LAYER1         1
//#define MAGIC_KEY_LAYER2         2
//#define MAGIC_KEY_LAYER3         3
//#define MAGIC_KEY_LAYER4         4
//#define MAGIC_KEY_LAYER5         5
//#define MAGIC_KEY_LAYER6         6
//#define MAGIC_KEY_LAYER7         7
//#define MAGIC_KEY_LAYER8         8
//#define MAGIC_KEY_LAYER9         9
//#define MAGIC_KEY_BOOTLOADER     B
//#define MAGIC_KEY_BOOTLOADER_ALT ESC
//#define MAGIC_KEY_LOCK           CAPS
//#define MAGIC_KEY_EEPROM         E
//#define MAGIC_KEY_EEPROM_CLEAR   BSPACE
//#define MAGIC_KEY_NKRO           N
//#define MAGIC_KEY_SLEEP_LED      Z

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION
#endif
/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
//#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 1

/*
 * HD44780 LCD Display Configuration
 */
/*
#define LCD_LINES           2     //< number of visible lines of the display
#define LCD_DISP_LENGTH    16     //< visibles characters per line of the display

#define LCD_IO_MODE      1            //< 0: memory mapped mode, 1: IO port mode

#if LCD_IO_MODE
#define LCD_PORT         PORTB        //< port for the LCD lines
#define LCD_DATA0_PORT   LCD_PORT     //< port for 4bit data bit 0
#define LCD_DATA1_PORT   LCD_PORT     //< port for 4bit data bit 1
#define LCD_DATA2_PORT   LCD_PORT     //< port for 4bit data bit 2
#define LCD_DATA3_PORT   LCD_PORT     //< port for 4bit data bit 3
#define LCD_DATA0_PIN    4            //< pin for 4bit data bit 0
#define LCD_DATA1_PIN    5            //< pin for 4bit data bit 1
#define LCD_DATA2_PIN    6            //< pin for 4bit data bit 2
#define LCD_DATA3_PIN    7            //< pin for 4bit data bit 3
#define LCD_RS_PORT      LCD_PORT     //< port for RS line
#define LCD_RS_PIN       3            //< pin  for RS line
#define LCD_RW_PORT      LCD_PORT     //< port for RW line
#define LCD_RW_PIN       2            //< pin  for RW line
#define LCD_E_PORT       LCD_PORT     //< port for Enable line
#define LCD_E_PIN        1            //< pin  for Enable line
#endif
*/

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0

//#define CONTROLLER_IS_XWHATSIT_MODEL_F_OR_WCASS_MODEL_F
//#define CONTROLLER_IS_XWHATSIT_BEAMSPRING_REV_4
#define CONTROLLER_IS_THROUGH_HOLE_BEAMSPRING
//#define CONTROLLER_IS_THROUGH_HOLE_MODEL_F

#define CAPSENSE_KEYBOARD_SETTLE_TIME_US 8
#define CAPSENSE_DAC_SETTLE_TIME_US 8
#define CAPSENSE_HARDCODED_SAMPLE_TIME 4

#define CAPSENSE_CAL_ENABLED 1
// #define CAPSENSE_CAL_ENABLED 0
#define CAPSENSE_CAL_DEBUG 1
// #define CAPSENSE_CAL_DEBUG 0
#define CAPSENSE_CAL_INIT_REPS 16
#define CAPSENSE_CAL_EACHKEY_REPS 16
#define CAPSENSE_CAL_BINS 15
#define CAPSENSE_CAL_THRESHOLD_OFFSET 120

#if !CAPSENSE_CAL_ENABLED
#define CAPSENSE_HARDCODED_THRESHOLD 142
#endif

#define CAPSENSE_KEYMAP_COL_TO_PHYSICAL_COL(col) (col)

// By default we set up for support of xwhatsit's solenoid driver board.
// Comment out HAPTIC_ENABLE_PIN if you don't have an enable pin:
#define HAPTIC_ENABLE_PIN D3
// We disable haptic feedbeck during USB low power conditions:
#define HAPTIC_OFF_IN_LOW_POWER 1
// Change this if you are using a different pin for the solenoid:
#define SOLENOID_PIN D2
// If you are not using a solenoid then comment out the above, and also in rules.mk, remove "HAPTIC_ENABLE += SOLENOID"
// You can also tune the following for your solenoid:
#define SOLENOID_DEFAULT_DWELL 4
#define SOLENOID_MIN_DWELL 4
//#define SOLENOID_MAX_DWELL 100
#define NO_HAPTIC_MOD

// If the lock lights are not used, then please don't define the below pins,
// or leave them set as unused pins:

// The following definitions are compatible with the Model F SMD controllers
// from here: https://deskthority.net/viewtopic.php?f=7&t=24597 supporting the
// AT lock lights header
#define LED_NUM_LOCK_PIN D7
#define LED_CAPS_LOCK_PIN E6
#define LED_SCROLL_LOCK_PIN B6

// The following definitions match the lock lights as used by the original
// xwhatsit firmware, but enabling all three of these is not compatible with
// solenoid support
//#define LED_NUM_LOCK_PIN E6
//#define LED_CAPS_LOCK_PIN D2
//#define LED_SCROLL_LOCK_PIN D7

// Uncomment below if the leds are on when the pin is driving zero:
//#define LED_NUM_LOCK_ACTIVE_LOW
//#define LED_CAPS_LOCK_ACTIVE_LOW
//#define LED_SCROLL_LOCK_ACTIVE_LOW

#include "keyboards/ibm/xwhatsit/post_config.h"

// ----- xwhatsit hardware configuration (through_hole) -----

#define CAPSENSE_DAC_MCP4921
#define CAPSENSE_DAC_NCS F6
#define CAPSENSE_DAC_SCK B1
#define CAPSENSE_DAC_SDI B2
#define CAPSENSE_DAC_MAX 4095

#define CAPSENSE_SHIFT_DIN  B2
#define CAPSENSE_SHIFT_OE   B6
#define CAPSENSE_SHIFT_SHCP B1
#define CAPSENSE_SHIFT_STCP F7
#define CAPSENSE_SHIFT_STCP_IO _SFR_IO_ADDR(PORTF)
#define CAPSENSE_SHIFT_STCP_BIT 7

// Rows:
// Physical position from left to right: (only the right-most are used for beamspring)
// 1    2    3    4    5    6    7    8
// TH schematic numbering (sense/row lines)
// 8    6    7    5    4    3    2    1
// F5,  B5,  F4,  B4,  D4,  C6,  D1,  D0

// pull-ups are only necessary for some variants of the TH controller design:
#if MATRIX_CAPSENSE_ROWS > 4
  #define SETUP_ROW_GPIOS() \
        do { \
            PORTF |= (1 << 5) | (1 << 4); \
            PORTB |= (1 << 5) | (1 << 4); \
            PORTD |= (1 << 4) | (1 << 1) | (1 << 0); \
            PORTC |= (1 << 6); \
        } while (0)
#else
  #define SETUP_ROW_GPIOS() \
        do { \
            PORTD |= (1 << 4) | (1 << 1) | (1 << 0); \
            PORTC |= (1 << 6); \
        } while (0)
#endif

#if 1
#define SETUP_UNUSED_PINS() do {} while (0)
#else
// TODO ENABLE THIS ONCE TESTED
#define SETUP_UNUSED_PINS() \
    do { \
        PORTB |= ~(DDRB | 0x77); \
        PORTC |= ~(DDRC | (1 << 6)); \
        PORTD |= ~(DDRD | 0x33); \
        PORTE |= ~(DDRE); \
        PORTF |= ~(DDRF | 0xf0); \
    } while (0)
#endif

#if MATRIX_CAPSENSE_ROWS <= 4
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
  #define CAPSENSE_READ_ROWS_VALUE (((dest_row_1 >> 4) & 0x04) | (dest_row_2 & 0x03) | ((dest_row_2 >> 1) & 0x08))
  #define CAPSENSE_READ_ROWS_EXTRACT_FROM_ARRAY do { dest_row_1 = array[p0++]; dest_row_2 = array[p0++]; } while (0)
#else
  #define CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE 4
  #define CAPSENSE_READ_ROWS_PIN_1 _SFR_IO_ADDR(PINC)
  #define CAPSENSE_READ_ROWS_PIN_2 _SFR_IO_ADDR(PIND)
  #define CAPSENSE_READ_ROWS_PIN_3 _SFR_IO_ADDR(PINB)
  #define CAPSENSE_READ_ROWS_PIN_4 _SFR_IO_ADDR(PINF)
  #define CAPSENSE_READ_ROWS_ASM_INSTRUCTIONS "in %[dest_row_1], %[ioreg_row_1]\n\tin %[dest_row_2], %[ioreg_row_2]\n\tin %[dest_row_3], %[ioreg_row_3]\n\tin %[dest_row_4], %[ioreg_row_4]"
  #define CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS \
            "st %a[arr]+, %[dest_row_1]"       "\n\t" \
            "st %a[arr]+, %[dest_row_2]"       "\n\t" \
            "st %a[arr]+, %[dest_row_3]"       "\n\t" \
            "st %a[arr]+, %[dest_row_4]"
  #define CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS_FAKE \
            "st %a[arr], %[dest_row_1]"       "\n\t" \
            "st %a[arr], %[dest_row_2]"       "\n\t" \
            "st %a[arr], %[dest_row_3]"       "\n\t" \
            "st %a[arr], %[dest_row_4]"
  #define CAPSENSE_READ_ROWS_OUTPUT_CONSTRAINTS [dest_row_1] "=&r" (dest_row_1), [dest_row_2] "=&r" (dest_row_2), [dest_row_3] "=&r" (dest_row_3), [dest_row_4] "=&r" (dest_row_4)
  #define CAPSENSE_READ_ROWS_INPUT_CONSTRAINTS [ioreg_row_1] "I" (CAPSENSE_READ_ROWS_PIN_1), [ioreg_row_2] "I" (CAPSENSE_READ_ROWS_PIN_2), [ioreg_row_3] "I" (CAPSENSE_READ_ROWS_PIN_3), [ioreg_row_4] "I" (CAPSENSE_READ_ROWS_PIN_4)
  #define CAPSENSE_READ_ROWS_LOCAL_VARS uint8_t dest_row_1, dest_row_2, dest_row_3, dest_row_4
  #define CAPSENSE_READ_ROWS_VALUE (((dest_row_1 >> 4) & 0x04) | (dest_row_2 & 0x03) | ((dest_row_2 >> 1) & 0x08) | (dest_row_3 & 0x10) | ((dest_row_3 << 1) & 0x40) | ((dest_row_4 << 1) & 0x20) | ((dest_row_4 << 2) & 0x80))
  #define CAPSENSE_READ_ROWS_EXTRACT_FROM_ARRAY do { dest_row_1 = array[p0++]; dest_row_2 = array[p0++]; dest_row_3 = array[p0++]; dest_row_4 = array[p0++]; } while (0)
#endif

#define CAPSENSE_KEYMAP_ROW_TO_PHYSICAL_ROW(row) (MATRIX_CAPSENSE_ROWS-1-(row))
#define CAPSENSE_PHYSICAL_ROW_TO_KEYMAP_ROW(row) (MATRIX_CAPSENSE_ROWS-1-(row))

/*
#ifndef CAPSENSE_KEYMAP_COL_TO_PHYSICAL_COL
  #define CAPSENSE_KEYMAP_COL_TO_PHYSICAL_COL(col) (col)
#endif
*/

#if (!defined(CAPSENSE_CONDUCTIVE_PLASTIC_IS_PUSHED_DOWN_ON_KEYPRESS)) && (!defined(CAPSENSE_CONDUCTIVE_PLASTIC_IS_PULLED_UP_ON_KEYPRESS))
#  if defined(CONTROLLER_IS_THROUGH_HOLE_BEAMSPRING)
      #define CAPSENSE_CONDUCTIVE_PLASTIC_IS_PULLED_UP_ON_KEYPRESS
#  else
      #define CAPSENSE_CONDUCTIVE_PLASTIC_IS_PUSHED_DOWN_ON_KEYPRESS
#  endif
#endif
