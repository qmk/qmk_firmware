/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

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
#include "bootloader.h"
#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#endif


void keyboard_init(void)
{
    // TODO: to enable debug print magic key bind on boot time

    // TODO: configuration of sendchar impl
    print_sendchar_func = sendchar;

    timer_init();
    matrix_init();

    /* boot magic keys goes here */
    matrix_scan();
#ifdef IS_BOOTMAGIC_BOOTLOADER
    /* kick up bootloader */
    if (IS_BOOTMAGIC_BOOTLOADER()) bootloader_jump();
#endif
#ifdef IS_BOOTMAGIC_DEBUG
    if (IS_BOOTMAGIC_DEBUG()) debug_enable = true;
#endif

#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_init();
#endif
}

/*
 * Do keyboard routine jobs: scan mantrix, light LEDs, ...
 * This is repeatedly called as fast as possible.
 */
void keyboard_task(void)
{
    static matrix_row_t matrix_prev[MATRIX_ROWS];
    static uint8_t led_status = 0;
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;

    matrix_scan();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row = matrix_get_row(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
            if (debug_matrix) matrix_print();

            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                if (matrix_change & ((matrix_row_t)1<<c)) {
                    action_exec((keyevent_t){
                        .key.pos  = (keypos_t){ .row = r, .col = c },
                        .pressed = (matrix_row & (1<<c)),
                        .time = timer_read()
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

    // update LED
    if (led_status != host_keyboard_leds()) {
        led_status = host_keyboard_leds();
        keyboard_set_leds(led_status);
    }

    return;
}

void keyboard_set_leds(uint8_t leds)
{
    led_set(leds);
}
