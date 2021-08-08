/* Copyright 2021 QMK
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

#include "process_swap_hands.h"
#include "quantum_keycodes.h"
#include "action_tapping.h"
#include "matrix.h"

extern const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS];

static matrix_row_t swap_state[MATRIX_ROWS];

static bool     swap_hands_enabled = false;
static bool     oneshot_enabled    = false;
static uint16_t oneshot_expiry     = 0;

#if defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0)
static inline bool has_oneshot_swaphands_timed_out(void) {
    return (oneshot_expiry && timer_expired(timer_read(), oneshot_expiry));
}
#endif

static inline void swap_hands_task(void) {
#if defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0)
    if (has_oneshot_swaphands_timed_out()) {
        clear_oneshot_swaphands();
    }
#endif
}

void clear_oneshot_swaphands(void) {
    oneshot_expiry     = 0;
    swap_hands_enabled = false;
    oneshot_enabled    = false;
}

void preprocess_swap_hands(keyrecord_t *record) {
    // TODO: implement a "real" swap_hands_task called from matrix_scan_quantum?
    swap_hands_task();

    keypos_t     pos     = record->event.key;
    matrix_row_t col_bit = MATRIX_ROW_SHIFTER << pos.col;
    bool         do_swap = record->event.pressed ? swap_hands_enabled : swap_state[pos.row] & (col_bit);

    if (do_swap) {
        record->event.key.row = pgm_read_byte(&hand_swap_config[pos.row][pos.col].row);
        record->event.key.col = pgm_read_byte(&hand_swap_config[pos.row][pos.col].col);
        swap_state[pos.row] |= col_bit;
    } else {
        swap_state[pos.row] &= ~(col_bit);
    }
}

bool process_swap_hands(uint16_t keycode, keyrecord_t *record) {
    static uint16_t last_keycode = 0;

    bool pressed = record->event.pressed;

    uint16_t previous_keycode = last_keycode;
    last_keycode              = keycode;

    bool interupted = (previous_keycode != keycode);

    switch (keycode) {
        case SH_TG:
            if (pressed) {
                swap_hands_enabled = !swap_hands_enabled;
            }
            break;
        case SH_MON:
            swap_hands_enabled = pressed;
            break;
        case SH_MOFF:
            swap_hands_enabled = !pressed;
            break;
        case SH_ON:
            if (!pressed) {
                swap_hands_enabled = true;
            }
            break;
        case SH_OFF:
            if (!pressed) {
                swap_hands_enabled = false;
            }
            break;
        case SH_TT: {
            static uint8_t start_state = 0xFF;
            if (pressed && (start_state == 0xFF)) {
                start_state = swap_hands_enabled;
            }

            static int tap_count = 0;
            if (interupted) {
                tap_count   = 0;
                start_state = 0xFF;
            } else {
                tap_count++;
                if (tap_count >= TAPPING_TOGGLE) {
                    swap_hands_enabled = !start_state;
                    start_state        = 0xFF;
                    tap_count          = 0;
                }
            }

            swap_hands_enabled = !swap_hands_enabled;
            break;
        }
        case SH_OS:
            if (pressed) {
                swap_hands_enabled = true;
            } else if (!interupted) {
                oneshot_enabled = true;
#ifdef ONESHOT_TIMEOUT
                oneshot_expiry = timer_read() + ONESHOT_TIMEOUT;
#endif
            } else {
                swap_hands_enabled = false;
            }
            break;
        case SH_T(0x00)... SH_T(0xEF):
            swap_hands_enabled = pressed;

            static uint16_t tap_expiry = 0;
            if (pressed) {
                tap_expiry = timer_read() + TAPPING_TERM;
            } else if (!timer_expired(timer_read(), tap_expiry)) {
                tap_code(keycode & 0xFF);
            }
            break;
        default:
            if (oneshot_enabled && !pressed) {
                clear_oneshot_swaphands();
            }
            return true;
    }
    return false;
}

bool is_swap_hands_enabled(void) { return swap_hands_enabled; }
void swap_hands_enable(void) { swap_hands_enabled = true; }
void swap_hands_disable(void) { swap_hands_enabled = false; }
void swap_hands_toggle(void) { swap_hands_enabled = !swap_hands_enabled; }
