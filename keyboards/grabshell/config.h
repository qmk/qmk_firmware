/* Copyright 2024 @ Grabshell (https://grabshell.site/)
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

#define WEAR_LEVELING_LOGICAL_SIZE (2*1024)
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE*2)
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 20

#ifdef NKRO_ENABLE
    #define FORCE_NKRO
#endif

#define MIDI_BASIC
#define MIDI_ADVANCED

#define RGB_MATRIX_LED_FLUSH_LIMIT 25

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE  FAST_DUTY_CYCLE_2

/*
grabshell has no externally accessible physical reset button.
Connecting the USB while pressing the following key code will jump to the bootloader.
*/
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 5

#define NO_USB_STARTUP_CHECK

#define USB_COMM_MODE   2
#define BT_COMM_MODE    0

#ifdef DIP_SWITCH_ENABLE
    #define DIP_ACTIVE_STA    0
    #define DIP_SWITCH_PINS { C13 , C15}
#endif

#ifdef NO_JTAG_DISABLE
    #undef NO_JTAG_DISABLE
#endif
#ifdef ENCODER_ENABLE
    #define ENCODERS_PAD_A { B5 }
    #define ENCODERS_PAD_B { B4 }
    #define ENCODER_RESOLUTION 1
#endif

#ifdef POINTING_DEVICE_ENABLE
   #define ANALOG_JOYSTICK_X_AXIS_PIN C0
   #define ANALOG_JOYSTICK_Y_AXIS_PIN C1
   #define ANALOG_JOYSTICK_AXIS_MIN 0
   #define ANALOG_JOYSTICK_AXIS_MAX 4095
   #define ANALOG_JOYSTICK_CLICK_PIN C2
#endif

#ifdef JOYSTICK_ENABLE
    #undef JOYSTICK_BUTTON_COUNT
    #define JOYSTICK_BUTTON_COUNT 1

    #undef JOYSTICK_AXIS_COUNT
    #define JOYSTICK_AXIS_COUNT 2

    #undef JOYSTICK_AXIS_RESOLUTION
    #define JOYSTICK_AXIS_RESOLUTION 10

#endif

#define MATRIX_ROWS 6
#define MATRIX_COLS 22
#define DIODE_DIRECTION     ROW2COL

#define EECONFIG_MAGIC_NUMBER   0x036
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define DRIVER_ADDR_1 0b1010011 // Left
#define DRIVER_ADDR_2 0b1010000 // Center
#define DRIVER_ADDR_3 0b1011100 // Right

#define DRIVER_SYNC_1 0
#define DRIVER_SYNC_2 0
#define DRIVER_SYNC_3 0

#define DRIVER_COUNT 3

#define DRIVER_1_LED_TOTAL 23
#define DRIVER_2_LED_TOTAL 40
#define DRIVER_3_LED_TOTAL 23
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL+DRIVER_2_LED_TOTAL+DRIVER_3_LED_TOTAL)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_DEFAULT_VAL 180
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_ALL // Default Effect

#define ENABLE_RGB_MATRIX_SOLID_COLOR         // Static single color
#define ENABLE_RGB_MATRIX_ALPHAS_MODS         // Static dual hue, speed is hue for secondary hue
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN    // Static gradient top to bottom, speed controls how much gradient changes
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT // Static gradient left to right, speed controls how much gradient changes
#define ENABLE_RGB_MATRIX_BREATHING           // Single hue brightness cycling animation
#define ENABLE_RGB_MATRIX_BAND_SAT            // Single hue band fading saturation scrolling left to right
#define ENABLE_RGB_MATRIX_BAND_VAL            // Single hue band fading brightness scrolling left to right
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // Single hue spinning spiral fades brightness
#define ENABLE_RGB_MATRIX_CYCLE_ALL           // Full keyboard solid hue cycling through full gradient
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // Full gradient scrolling left to right
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN       // Full gradient scrolling top to bottom
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN        // Full gradient scrolling out to in
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL   // Full dual gradients scrolling out to in
