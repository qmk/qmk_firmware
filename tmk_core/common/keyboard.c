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
#ifdef FAUXCLICKY_ENABLE
#   include "fauxclicky.h"
#endif
#ifdef SERIAL_LINK_ENABLE
#   include "serial_link/system/serial_link.h"
#endif
#ifdef VISUALIZER_ENABLE
#   include "visualizer/visualizer.h"
#endif


#ifdef MATRIX_HAS_GHOST
extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
// bit map of true keys and empty spots in matrix, each row is reversed
static uint16_t get_row_ghost_check(uint16_t row){
    for (int col = 0; col < MATRIX_COLS; col++) {
        if (keymaps[0][row][col])
            row &= 1<<col;
        else
            row &= 0<<col;
    }
    return row;
}
static bool has_ghost_in_row(uint8_t row)
{
    matrix_row_t matrix_row = (get_row_ghost_check(matrix_get_row(row)));
    /* No ghost exists when less than 2 keys are down on the row.
    If there are "active" blanks in the matrix, the key can't be pressed by the user,
    there is no doubt as to which keys are really being pressed.
    The ghosts will be ignored, they are KC_NO.   */
    if (((matrix_row - 1) & matrix_row) == 0){
        return false;
    }
    // Ghost occurs when the row shares column line with other row, blanks in the matrix don't matter
    // If there are two or more real keys pressed and they match another row's real keys, the row will be ignored.
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && __builtin_popcount(
        get_row_ghost_check(matrix_get_row(i)) & matrix_row
        ) > 1){
            return true;
        }
    }
    return false;
}
#endif

__attribute__ ((weak))
void matrix_setup(void) {
}

void keyboard_setup(void) {
    matrix_setup();
}

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
#ifdef FAUXCLICKY_ENABLE
    fauxclicky_init();
#endif
#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 1;
#endif
}

/*
 * Do keyboard routine jobs: scan mantrix, light LEDs, ...
 * This is repeatedly called as fast as possible.
 */
void keyboard_task(void)
{
    static matrix_row_t matrix_prev[MATRIX_ROWS];
#ifdef MATRIX_HAS_GHOST
    static matrix_row_t matrix_ghost[MATRIX_ROWS];
#endif
    static uint8_t led_status = 0;
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;

    matrix_scan();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row = matrix_get_row(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
#ifdef MATRIX_HAS_GHOST
            if (has_ghost_in_row(r)) {
                /* Keep track of whether ghosted status has changed for
                 * debugging. But don't update matrix_prev until un-ghosted, or
                 * the last key would be lost.
                 */
                if (debug_matrix && matrix_ghost[r] != matrix_row) {
                    matrix_print();
                }
                matrix_ghost[r] = matrix_row;
                continue;
            }
            matrix_ghost[r] = matrix_row;
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
                    // process a key per task call
                    goto MATRIX_LOOP_END;
                }
            }
        }
    }
    // call with pseudo tick event when no real key event.
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

    // update LED
    if (led_status != host_keyboard_leds()) {
        led_status = host_keyboard_leds();
        keyboard_set_leds(led_status);
    }
}

void keyboard_set_leds(uint8_t leds)
{
    if (debug_keyboard) { debug("keyboard_set_led: "); debug_hex8(leds); debug("\n"); }
    led_set(leds);
}
