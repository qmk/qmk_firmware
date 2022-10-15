/* Copyright 2021 Zhi Quan
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
#include QMK_KEYBOARD_H

enum custom_keycodes {
    KC_P00 = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_all( /* Base */
    KC_F1,   KC_F2,      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,     TG(2),   KC_PSLS, KC_PAST, KC_PMNS,
    KC_F3,   KC_F4,      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_F5,   KC_F6,      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,              KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_F7,   KC_F8,      KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_F9,   KC_F10,     KC_LCTL,          KC_LCMD,                            KC_SPC,                                      KC_ROPT,          MO(1),               KC_P0,   KC_P00,  KC_PDOT, KC_PENT),

[1] = LAYOUT_all( /* FN */
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_TRNS,    KC_TRNS, KC_MPRV, KC_MNXT, KC_VOLD,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, QK_BOOT,             KC_HOME, KC_UP,   KC_PGUP, KC_VOLU,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,             KC_LEFT, KC_MUTE, KC_RGHT, KC_VOLU,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_END,  KC_DOWN, KC_PGDN, KC_MPLY,
    KC_TRNS, KC_TRNS,    KC_TRNS,          KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY),

[2] = LAYOUT_all( /* Numpad */
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_HOME, KC_UP,   KC_PGUP, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,             KC_LEFT, XXXXXXX, KC_RGHT, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_END,  KC_DOWN, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS,          KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

[3] = LAYOUT_all( /* Empty for dynamic keymaps */
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS,          KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_P00:
            if (record->event.pressed) {
                tap_code(KC_P0);
                tap_code(KC_P0);
            }
            return false;
            break;
        case KC_ESC:
            if (record->event.pressed) {
                // Turn on capslock indicator.
                writePin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
            } else {
                // Turn off capslock indicator.
                writePin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
            }
    }
    return true;
}

// Customized function so that numlock and capslock indicator are no longer controlled by the host.
bool led_update_user(led_t led_state) {
#if defined(LED_NUM_LOCK_PIN) || defined(LED_CAPS_LOCK_PIN) || defined(LED_SCROLL_LOCK_PIN) || defined(LED_COMPOSE_PIN) || defined(LED_KANA_PIN)
#    if LED_PIN_ON_STATE == 0
        // invert the whole thing to avoid having to conditionally !led_state.x later
        led_state.raw = ~led_state.raw;
#    endif

// #    ifdef LED_NUM_LOCK_PIN
//         writePin(LED_NUM_LOCK_PIN, led_state.num_lock);
// #    endif
// #    ifdef LED_CAPS_LOCK_PIN
//         writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
// #    endif
#    ifdef LED_SCROLL_LOCK_PIN
        writePin(LED_SCROLL_LOCK_PIN, led_state.scroll_lock);
#    endif
#    ifdef LED_COMPOSE_PIN
        writePin(LED_COMPOSE_PIN, led_state.compose);
#    endif
#    ifdef LED_KANA_PIN
        writePin(LED_KANA_PIN, led_state.kana);
#    endif
#endif

    // Return false to let led_update_kb fall through.
    return false;
}

// Customized function to manage numlock indicator based on layer.
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        // Base layer
        case 0:
            // Turn on numlock indicator.
            writePin(LED_NUM_LOCK_PIN, LED_PIN_ON_STATE);
            break;

        // Numpad navigation layer
        case 2:
            // Turn off numlock indicator.
            writePin(LED_NUM_LOCK_PIN, !LED_PIN_ON_STATE);
            break;
    }

    return state;
}