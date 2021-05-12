/* Copyright 2021 Jessica Sullivan and Don Kjer 
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

#include "dgk6x.h"

/* Private Functions */
void off_all_leds(void) {
    writePinHigh(LED_CAPS_LOCK_PIN);
    writePinHigh(LED_WIN_LOCK_PIN);
    writePinHigh(LED_MR_LOCK_PIN);
}

void on_all_leds(void) {
    writePinLow(LED_CAPS_LOCK_PIN);
    writePinLow(LED_WIN_LOCK_PIN);
    writePinLow(LED_MR_LOCK_PIN);
}

/* WinLock and MR LEDs are non-standard. Need to override led init */
void led_init_ports(void) {
    setPinOutput(LED_CAPS_LOCK_PIN);
    setPinOutput(LED_WIN_LOCK_PIN);
    setPinOutput(LED_MR_LOCK_PIN);
    off_all_leds();
}


#ifndef WINLOCK_DISABLED
static bool win_key_locked = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TGUI:
            if (record->event.pressed) {
                // Toggle GUI lock on key press
                win_key_locked = !win_key_locked;
                writePin(LED_WIN_LOCK_PIN, !win_key_locked);
            }
            break;
        case KC_LGUI:
            if (win_key_locked) { return false; }
            break;
    }
    return process_record_user(keycode, record);
}
#endif /* WINLOCK_DISABLED */

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */

   {0, C_1,   B_1,   A_1},  // Esc
   {0, C_2,   B_2,   A_2},  // 1
   {0, C_3,   B_3,   A_3},  // 2
   {0, C_4,   B_4,   A_4},  // 3
   {0, C_5,   B_5,   A_5},  // 4
   {0, C_6,   B_6,   A_6},  // 5
   {0, C_7,   B_7,   A_7},  // 6
   {0, C_8,   B_8,   A_8},  // 7
   {0, C_9,   B_9,   A_9},  // 8
   {0, C_10,  B_10,  A_10}, // 9
   {0, C_11,  B_11,  A_11}, // 0
   {0, C_12,  B_12,  A_12}, // -
   {0, C_13,  B_13,  A_13}, // =
   {0, C_14,  B_14,  A_14}, // Bksp
#ifdef KEYBOARD_durgod_dgk6x_hades   
   {0, C_15,  B_15,  A_15}, // Del 
#endif

   {0, F_1,   E_1,   D_1},  // Tab
   {0, F_2,   E_2,   D_2},  // Q
   {0, F_3,   E_3,   D_3},  // W
   {0, F_4,   E_4,   D_4},  // E
   {0, F_5,   E_5,   D_5},  // R
   {0, F_6,   E_6,   D_6},  // T
   {0, F_7,   E_7,   D_7},  // Y
   {0, F_8,   E_8,   D_8},  // U
   {0, F_9,   E_9,   D_9},  // I
   {0, F_10,  E_10,  D_10}, // O
   {0, F_11,  E_11,  D_11}, // P
   {0, F_12,  E_12,  D_12}, // [
   {0, F_13,  E_13,  D_13}, // ]
   {0, F_14,  E_14,  D_14}, // Pipe
#ifdef KEYBOARD_durgod_dgk6x_hades   
   {0, F_15,  E_15,  D_15}, // Home
#endif

   {0, I_1,   H_1,   G_1},  // Caps
   {0, I_2,   H_2,   G_2},  // A
   {0, I_3,   H_3,   G_3},  // S
   {0, I_4,   H_4,   G_4},  // D
   {0, I_5,   H_5,   G_5},  // F
   {0, I_6,   H_6,   G_6},  // G
   {0, I_7,   H_7,   G_7},  // H
   {0, I_8,   H_8,   G_8},  // J
   {0, I_9,   H_9,   G_9},  // K
   {0, I_10,  H_10,  G_10}, // L
   {0, I_11,  H_11,  G_11}, // :
   {0, I_12,  H_12,  G_12}, // '
   {0, I_14,  H_14,  G_14}, // Enter
#ifdef KEYBOARD_durgod_dgk6x_hades   
   {0, I_15,  H_15,  G_15}, // PgUp
#endif

   {0, L_1,   K_1,   J_1},  // LShift
   {0, L_2,   K_2,   J_2},  // Z
   {0, L_3,   K_3,   J_3},  // X
   {0, L_4,   K_4,   J_4},  // C
   {0, L_5,   K_5,   J_5},  // V
   {0, L_6,   K_6,   J_6},  // B
   {0, L_7,   K_7,   J_7},  // N
   {0, L_8,   K_8,   J_8},  // M
   {0, L_9,   K_9,   J_9},  // <
   {0, L_10,  K_10,  J_10}, // >
   {0, L_11,  K_11,  J_11}, // ?
   {0, L_12,  K_12,  J_12}, // RShift
#ifdef KEYBOARD_durgod_dgk6x_hades   
   {0, L_14,  K_14,  J_14}, // Up
   {0, L_15,  K_15,  J_15}, // PgOn
#endif

   {1, C_1,   B_1,   A_1},  // LCtrl
   {1, C_2,   B_2,   A_2},  // LAlt
   {1, C_3,   B_3,   A_3},  // Windows
   {1, C_6,   B_6,   A_6},  // Space
   {1, C_10,  B_10,  A_10}, // Fn1/RAlt hades/venus
   {1, C_11,  B_11,  A_11}, // Fn2/Fn1
   {1, C_12,  B_12,  A_12}, // RCtrl/Fn2
   {1, C_13,  B_13,  A_13}, // LEFT/RCtrl
#ifdef KEYBOARD_durgod_dgk6x_hades   
   {1, C_14,  B_14,  A_14}, // DOWN
   {1, C_15,  B_15,  A_15}  // RIGHT
#endif
};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

__attribute__ ((weak))
void rgb_matrix_indicators_user(void)
{
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(CAPS_LED, 0xFF, 0xFF, 0xFF);
    }
}
#endif /* RGB_MATRIX_ENABLE */


