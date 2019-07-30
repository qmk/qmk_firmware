/*
Copyright 2011, 2012, 2013 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include "keyboard.h"
#include "matrix.h"
#include "keymap.h"
#include "host.h"
#include "led.h"
#include "keycode.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#include "util.h"
#include "sendchar.h"
#include "eeconfig.h"
#include "backlight.h"
#include "action_layer.h"
#ifdef BOOTMAGIC_ENABLE
#   include "bootmagic.h"
#else
#   include "magic.h"
#endif
#ifdef MOUSEKEY_ENABLE
#   include "mousekey.h"
#endif
#ifdef PS2_MOUSE_ENABLE
#   include "ps2_mouse.h"
#endif
#ifdef SERIAL_MOUSE_ENABLE
#   include "serial_mouse.h"
#endif
#ifdef ADB_MOUSE_ENABLE
#   include "adb.h"
#endif
#ifdef RGBLIGHT_ENABLE
#   include "rgblight.h"
#endif
#ifdef STENO_ENABLE
#   include "process_steno.h"
#endif
#ifdef FAUXCLICKY_ENABLE
#   include "fauxclicky.h"
#endif
#ifdef SERIAL_LINK_ENABLE
#   include "serial_link/system/serial_link.h"
#endif
#ifdef VISUALIZER_ENABLE
#   include "visualizer/visualizer.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#   include "pointing_device.h"
#endif
#ifdef MIDI_ENABLE
#   include "process_midi.h"
#endif
#ifdef HD44780_ENABLE
#   include "hd44780.h"
#endif
#ifdef QWIIC_ENABLE
#   include "qwiic.h"
#endif
#ifdef OLED_DRIVER_ENABLE
    #include "oled_driver.h"
#endif
#ifdef VELOCIKEY_ENABLE
  #include "velocikey.h"
#endif

#ifdef MATRIX_HAS_GHOST
extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
static matrix_row_t get_real_keys(uint8_t row, matrix_row_t rowdata){
    matrix_row_t out = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        //read each key in the row data and check if the keymap defines it as a real key
        if (pgm_read_byte(&keymaps[0][row][col]) && (rowdata & (1<<col))){
            //this creates new row data, if a key is defined in the keymap, it will be set here
            out |= 1<<col;
        }
    }
    return out;
}

static inline bool popcount_more_than_one(matrix_row_t rowdata)
{
    rowdata &= rowdata-1; //if there are less than two bits (keys) set, rowdata will become zero
    return rowdata;
}

static inline bool has_ghost_in_row(uint8_t row, matrix_row_t rowdata)
{
    /* No ghost exists when less than 2 keys are down on the row.
    If there are "active" blanks in the matrix, the key can't be pressed by the user,
    there is no doubt as to which keys are really being pressed.
    The ghosts will be ignored, they are KC_NO.   */
    rowdata = get_real_keys(row, rowdata);
    if ((popcount_more_than_one(rowdata)) == 0){
        return false;
    }
    /* Ghost occurs when the row shares a column line with other row,
    and two columns are read on each row. Blanks in the matrix don't matter,
    so they are filtered out.
    If there are two or more real keys pressed and they match columns with
    at least two of another row's real keys, the row will be ignored. Keep in mind,
    we are checking one row at a time, not all of them at once.
    */
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && popcount_more_than_one(get_real_keys(i, matrix_get_row(i)) & rowdata)){
            return true;
        }
    }
    return false;
}

#endif

void disable_jtag(void) {
// To use PORTF disable JTAG with writing JTD bit twice within four cycles.
#if (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega32U4__))
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);
#endif
}

/** \brief matrix_setup
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void matrix_setup(void) {
}

/** \brief keyboard_pre_init_user
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void keyboard_pre_init_user(void) { }

/** \brief keyboard_pre_init_kb
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void keyboard_pre_init_kb(void) {
  keyboard_pre_init_user();
}

/** \brief keyboard_post_init_user
 *
 * FIXME: needs doc
 */

__attribute__ ((weak))
void keyboard_post_init_user() {}

/** \brief keyboard_post_init_kb
 *
 * FIXME: needs doc
 */

__attribute__ ((weak))
void keyboard_post_init_kb(void) {
  keyboard_post_init_user();
}

/** \brief keyboard_setup
 *
 * FIXME: needs doc
 */
void keyboard_setup(void) {
    disable_jtag();
    matrix_setup();
    keyboard_pre_init_kb();
}

/** \brief is_keyboard_master
 *
 * FIXME: needs doc
 */
__attribute__((weak))
bool is_keyboard_master(void) {
    return true;
}

/** \brief keyboard_init
 *
 * FIXME: needs doc
 */
void keyboard_init(void) {
    timer_init();
    matrix_init();
#ifdef QWIIC_ENABLE
    qwiic_init();
#endif
#ifdef OLED_DRIVER_ENABLE
    oled_init(OLED_ROTATION_0);
#endif
#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_init();
#endif
#ifdef SERIAL_MOUSE_ENABLE
    serial_mouse_init();
#endif
#ifdef ADB_MOUSE_ENABLE
    adb_mouse_init();
#endif
#ifdef BOOTMAGIC_ENABLE
    bootmagic();
#else
    magic();
#endif
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_init();
#endif
#ifdef STENO_ENABLE
    steno_init();
#endif
#ifdef FAUXCLICKY_ENABLE
    fauxclicky_init();
#endif
#ifdef POINTING_DEVICE_ENABLE
    pointing_device_init();
#endif
#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 1;
#endif
    keyboard_post_init_kb(); /* Always keep this last */
}

/** \brief Keyboard task: Do keyboard routine jobs
 *
 * Do routine keyboard jobs:
 *
 * * scan matrix
 * * handle mouse movements
 * * run visualizer code
 * * handle midi commands
 * * light LEDs
 *
 * This is repeatedly called as fast as possible.
 */
void keyboard_task(void)
{
    static matrix_row_t matrix_prev[MATRIX_ROWS];
    static uint8_t led_status = 0;
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;
#ifdef QMK_KEYS_PER_SCAN
    uint8_t keys_processed = 0;
#endif

#if defined(OLED_DRIVER_ENABLE) && !defined(OLED_DISABLE_TIMEOUT)
    uint8_t ret = matrix_scan();
#else
    matrix_scan();
#endif

    if (is_keyboard_master()) {
        for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
            matrix_row = matrix_get_row(r);
            matrix_change = matrix_row ^ matrix_prev[r];
            if (matrix_change) {
#ifdef MATRIX_HAS_GHOST
                if (has_ghost_in_row(r, matrix_row)) { continue; }
#endif
                if (debug_matrix) matrix_print();
                for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                    if (matrix_change & ((matrix_row_t)1<<c)) {
                        action_exec((keyevent_t){
                            .key = (keypos_t){ .row = r, .col = c },
                            .pressed = (matrix_row & ((matrix_row_t)1<<c)),
                            .time = (timer_read() | 1) /* time should not be 0 */
                        });
                        // record a processed key
                        matrix_prev[r] ^= ((matrix_row_t)1<<c);
#ifdef QMK_KEYS_PER_SCAN
                        // only jump out if we have processed "enough" keys.
                        if (++keys_processed >= QMK_KEYS_PER_SCAN)
#endif
                        // process a key per task call
                        goto MATRIX_LOOP_END;
                    }
                }
            }
        }
    }
    // call with pseudo tick event when no real key event.
#ifdef QMK_KEYS_PER_SCAN
    // we can get here with some keys processed now.
    if (!keys_processed)
#endif
    action_exec(TICK);

MATRIX_LOOP_END:

#ifdef QWIIC_ENABLE
    qwiic_task();
#endif

#ifdef OLED_DRIVER_ENABLE
    oled_task();
#ifndef OLED_DISABLE_TIMEOUT
    // Wake up oled if user is using those fabulous keys!
    if (ret)
        oled_on();
#endif
#endif

#ifdef MOUSEKEY_ENABLE
    // mousekey repeat & acceleration
    mousekey_task();
#endif

#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_task();
#endif

#ifdef SERIAL_MOUSE_ENABLE
    serial_mouse_task();
#endif

#ifdef ADB_MOUSE_ENABLE
    adb_mouse_task();
#endif

#ifdef SERIAL_LINK_ENABLE
	serial_link_update();
#endif

#ifdef VISUALIZER_ENABLE
    visualizer_update(default_layer_state, layer_state, visualizer_get_mods(), host_keyboard_leds());
#endif

#ifdef POINTING_DEVICE_ENABLE
    pointing_device_task();
#endif

#ifdef MIDI_ENABLE
    midi_task();
#endif

#ifdef VELOCIKEY_ENABLE
    if (velocikey_enabled()) { velocikey_decelerate();  }
#endif

    // update LED
    if (led_status != host_keyboard_leds()) {
        led_status = host_keyboard_leds();
        keyboard_set_leds(led_status);
    }
}

/** \brief keyboard set leds
 *
 * FIXME: needs doc
 */
void keyboard_set_leds(uint8_t leds)
{
    if (debug_keyboard) { debug("keyboard_set_led: "); debug_hex8(leds); debug("\n"); }
    led_set(leds);
}
