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
#ifdef QWIIC_KEYBOARD_ENABLE
#   include "qwiic/qwiic_keyboard.h"
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

/** \brief matrix_setup
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void matrix_setup(void) {
}

/** \brief keyboard_setup
 *
 * FIXME: needs doc
 */
void keyboard_setup(void) {
    matrix_setup();
}

/** \brief is_keyboard_master
 *
 * FIXME: needs doc
 */
__attribute__((weak))
bool is_keyboard_master(void) {
    return true;
}

__attribute__((weak))
uint8_t multimatrix_get_num_matrices(void) {
    return 0;
}

__attribute__((weak))
uint8_t multimatrix_get_num_cols(uint8_t matrix) {
    return 0;
}

__attribute__((weak))
uint8_t multimatrix_get_num_rows(uint8_t matrix) {
    return 0;
}

__attribute__((weak))
uint32_t multimatrix_get_row(uint8_t matrix, uint8_t row) {
    return 0;
}

__attribute__((weak))
uint32_t multimatrix_get_row_cache(uint8_t matrix, uint8_t row) {
    return 0;
}

__attribute__((weak))
void multimatrix_set_row_cache(uint8_t matrix, uint8_t row, uint32_t value) {
}

static uint8_t get_num_matrices(void) {
    return 1 + multimatrix_get_num_matrices();
}

uint8_t keyboard_get_num_cols(uint8_t matrix) {
    if (matrix == 0) {
      return MATRIX_COLS;
    } else {
      return multimatrix_get_num_cols(matrix - 1);
    }
}

uint8_t keyboard_get_num_rows(uint8_t matrix) {
    if (matrix == 0) {
      return MATRIX_ROWS;
    } else {
      return multimatrix_get_num_rows(matrix - 1);
    }
}

static uint32_t get_row(uint8_t matrix, uint8_t row) {
    if (matrix == 0) {
      return matrix_get_row(row);
    } else {
      return multimatrix_get_row(matrix - 1, row);
    }
}

static matrix_row_t matrix_prev[MATRIX_ROWS];

static uint32_t get_row_cache(uint8_t matrix, uint8_t row) {
    if (matrix == 0) {
      return matrix_prev[row];
    } else {
      return multimatrix_get_row_cache(matrix - 1, row);
    }
}

static void set_row_cache(uint8_t matrix, uint8_t row, uint32_t value) {
    if (matrix == 0) {
      matrix_prev[row] = value;
    } else {
      return multimatrix_set_row_cache(matrix - 1, row, value);
    }
}


/** \brief keyboard_init
 *
 * FIXME: needs doc
 */
void keyboard_init(void) {
    timer_init();
    matrix_init();
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
#ifdef QWIIC_KEYBOARD_ENABLE
    qwiic_keyboard_init();
#endif
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
    static uint8_t led_status = 0;
    uint32_t matrix_row = 0;
    uint32_t matrix_change = 0;
#ifdef QMK_KEYS_PER_SCAN
    uint8_t keys_processed = 0;
#endif

    matrix_scan();
    if (is_keyboard_master()) {
        for (uint8_t m = 0; m < get_num_matrices(); m++) {
            uint8_t num_cols = keyboard_get_num_cols(m);
            uint8_t num_rows = keyboard_get_num_rows(m);
            for (uint8_t r = 0; r < num_rows; r++) {
                matrix_row = get_row(m, r);
                uint32_t row_cache = get_row_cache(m, r);
                matrix_change = matrix_row ^ row_cache;
                if (matrix_change) {
#ifdef MATRIX_HAS_GHOST
                    //NOTE: The we support ghosting only for the main matrix, since it's only useful for old keyboards without diodes
                    if (has_ghost_in_row(r, matrix_row)) {
                        /* Keep track of whether ghosted status has changed for
                        * debugging. But don't update matrix_prev until un-ghosted, or
                        * the last key would be lost.
                        */
                        //if (debug_matrix && matrix_ghost[r] != matrix_row) {
                        //    matrix_print();
                        //}
                        //matrix_ghost[r] = matrix_row;
                        continue;
                    }
                    //matrix_ghost[r] = matrix_row;
#endif
                    if (debug_matrix) matrix_print();
                    for (uint8_t c = 0; c < num_cols; c++) {
                        if (matrix_change & (uint32_t)(1u<<c)) {
                            action_exec((keyevent_t){
                                // The main matrix is always 0
                                .key = (keymatrix_t){.pos = (keypos_t){ .row = r, .col = c }, .matrix = m},
                                .pressed = (matrix_row & ((uint32_t)1u<<c)),
                                .time = (timer_read() | 1) /* time should not be 0 */
                            });
                            // record a processed key
                            row_cache ^= (uint32_t)(1u<<c);
                            set_row_cache(m, r, row_cache);
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
    }
    // call with pseudo tick event when no real key event.
#ifdef QMK_KEYS_PER_SCAN
    // we can get here with some keys processed now.
    if (!keys_processed)
#endif
    action_exec(TICK);

MATRIX_LOOP_END:

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

#ifdef QWIIC_KEYBOARD_ENABLE
    qwiic_keyboard_task();
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
