/* Copyright 2021 Paul Ewers
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

enum alt_keycodes {
    ALT_DEL = SAFE_RANGE, // Map left alt + backspace to delete
    LED_TOG               // Toggle LED modes
};

// Friendly layer names
enum alt_layers {
    DEF = 0,
    ALT,
    MAC,
    FUNC,
    SUPR
};

// EEPROM storage mode
enum alt_led_mode {
    LED_MODE_ALL = 0,
    LED_MODE_LOGO,
    LED_MODE_UNDERGLOW,
    LED_MODE_OFF,
    LED_MODE_TOTAL
};

// EEPROM storage type
typedef union {
    uint32_t raw;
    struct {
        uint8_t led_mode: 8;
    };
} user_config_t;

user_config_t user_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,    KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, MO(SUPR),         KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT, MO(FUNC),KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [ALT] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______, _______, KC_LALT,          _______,          _______,          _______,          _______, _______, _______,             _______, _______, _______
    ),
    [MAC] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______, KC_LALT, KC_LGUI,          _______,          _______,          _______,          KC_RGUI, _______, KC_RALT,             _______, _______, _______
    ),
    [FUNC] = LAYOUT_all(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,    KC_END,  KC_VOLU,
        _______, RGB_HUD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_M_P, _______, _______, _______, KC_BRIU, KC_PAUS, KC_PSCR, _______, _______,             KC_MUTE, KC_VOLD,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_SAD, RGB_M_B, _______, _______, _______, KC_BRID, _______, _______,          _______,
        _______, _______, RGB_TOG, LED_TOG, _______, EEP_RST, RESET,   _______, _______, TG(MAC), TG(ALT), _______, _______, _______,             KC_PGUP,
        _______, _______, KC_LALT,          _______,          _______,          _______,          _______, _______, _______,             KC_HOME, KC_PGDN, KC_END
    ),
    [SUPR] = LAYOUT_all(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ALT_DEL, ALT_DEL,    KC_END,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______, _______, _______,          _______,          _______,          _______,          _______, _______, _______,             KC_HOME, _______, KC_END
    )
};

// If the super alt layer is the active layer
bool super_alt_layer_active = false;

// If we need to unregister alt when leaving the super alt layer
bool need_to_unregister_alt = false;

// This runs code every time that the layers get changed
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case DEF:
            // When returning to the default layer, check if we need to unregister the left alt key
            if (super_alt_layer_active && need_to_unregister_alt) {
                unregister_code(KC_LALT);
            }
            super_alt_layer_active = false;
            need_to_unregister_alt = false;
            break;
        case SUPR:
            super_alt_layer_active = true;
            break;
    }
    return state;
}

// There is a total of 20 LEDs on the board; the 4 logo LEDs have indices 16, 17, 18, 19
void update_led_mode(void) {
    rgblight_setrgb(0, 0, 0);
    switch (user_config.led_mode) {
        case LED_MODE_ALL:
            rgblight_set_effect_range(0, RGBLED_NUM);
            rgblight_enable_noeeprom();
            break;
        case LED_MODE_LOGO: 
            rgblight_set_effect_range(16, 4);
            rgblight_enable_noeeprom();
            break;
        case LED_MODE_UNDERGLOW:
            rgblight_set_effect_range(0, 16);
            rgblight_enable_noeeprom();
            break;
        case LED_MODE_OFF:
            rgblight_disable_noeeprom();
            break;
    }
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    update_led_mode();
}

void eeconfig_init_user(void) {
    user_config.raw      = 0;
    user_config.led_mode = LED_MODE_ALL;
    eeconfig_update_user(user_config.raw);
    rgblight_enable();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        // These are the keys we want to 'fall though' and behave as usual when pressed with the alt modifier
        case KC_A ... KC_Z:
        case KC_TAB:
        case KC_DEL:
        case KC_UP:
        case KC_DOWN:
        case KC_ENT:
        case KC_SPC:
        case MO(FUNC):
            if (super_alt_layer_active && record->event.pressed) {
                // Only activate the alt modifier for the first key press
                if ((get_mods() & MOD_BIT(KC_LALT)) == false) {
                    register_code(KC_LALT);
                    need_to_unregister_alt = true;
                }
            }
            // We still want to process the keycode normally
            return true;
        case KC_F4:
            // Map alt+shift+4 to alt+f4
            if (super_alt_layer_active && (get_mods() & MOD_BIT(KC_LSHIFT))) {
                if (record->event.pressed) {
                    register_code(KC_LALT);
                } else {
                    unregister_code(KC_LALT);
                }
            }
            return true;
        case ALT_DEL:
            if (record->event.pressed) {
                register_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
            }
            return false;
        case LED_TOG:
            if (record->event.pressed) {
                user_config.led_mode = (user_config.led_mode + 1) % LED_MODE_TOTAL;
                update_led_mode();
                eeconfig_update_user(user_config.raw);
            }
            return false;
        case RESET:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case EEP_RST:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    eeconfig_init();
                }
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}
