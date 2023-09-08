/* Copyright 2022 MIIIW <www.miiiw.com>
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

// Defines names for use in layer keycodes and the keymap
enum keymap_layers {
    WIN_BL,
    WIN_FL,
    MAC_BL,
    MAC_FL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap WIN_BL: Win Base Layer (Default Layer)
   */
    [WIN_BL] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_DEL,  KC_INS,  KC_PGUP, KC_PGDN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_P7,   KC_P8,   KC_P9,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,             KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,      KC_UP,         KC_P1,   KC_P2,   KC_P3,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, MO(WIN_FL), KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT,       KC_P0,   KC_PDOT, KC_PENT
    ),

  /* Keymap WIN_FL: Win Function Layer
   */
    [WIN_FL] = LAYOUT(
        RGB_RST,          KC_BRID, KC_BRIU, ALT_TAB, G(KC_D), KC_WBAK, KC_WSCH, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,   _______, KC_PSCR, KC_HOME, KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,    _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      RGB_VAI,       _______, _______, _______,
        _______, _______, _______,                   _______,                   _______, _______, _______,     RGB_RMOD, RGB_VAD, RGB_MOD,       _______, _______, _______
    ),

  /* Keymap MAC_BL: Mac Base Layer
   */
    [MAC_BL] = LAYOUT(
        KC_ESC,           KC_BRID, KC_BRIU,C(KC_UP),C(KC_DOWN),KC_F11,G(KC_SPC),KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,   KC_DEL,  KC_INS,  KC_PGUP, KC_PGDN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_P7,   KC_P8,   KC_P9,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,             KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,      KC_UP,         KC_P1,   KC_P2,   KC_P3,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                    KC_RGUI, MO(MAC_FL), KC_RALT,   KC_LEFT, KC_DOWN, KC_RGHT,       KC_P0,   KC_PDOT, KC_PENT
    ),

  /* Keymap MAC_FL: Mac Function Layer
   */
    [MAC_FL] = LAYOUT(
        RGB_RST,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    _______, KC_PSCR, KC_HOME, KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,    _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      RGB_VAI,       _______, _______, _______,
        _______, _______, _______,                   _______,                   _______, _______, _______,     RGB_RMOD, RGB_VAD, RGB_MOD,       _______, _______, _______
    ),
};

// Implement Super-alt↯tab
// See https://docs.qmk.fm/#/feature_macros?id=super-alt↯tab
static bool is_alt_tab_active = false;
static uint32_t alt_tab_timer = 0;

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
    case 2:
        default_layer_set(1UL << (active ? WIN_BL : MAC_BL));
        break;
   }
   return true;
}
#endif

// Processing all the key pressed.
// Alt+tab.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t shift_mods = get_mods() & MOD_MASK_SHIFT;
    switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read32();
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        return false;
    case RGB_RST:
        if (record->event.pressed) {
            eeconfig_update_rgb_matrix_default();
        }
        return false;
    case RGB_VAI:
        if(shift_mods) {
            if (record->event.pressed) rgb_matrix_increase_speed();
            return false;
        }
        break;
    case RGB_VAD:
        if(shift_mods) {
            if (record->event.pressed && rgb_matrix_get_speed() >= RGB_MATRIX_SPD_STEP) rgb_matrix_decrease_speed();
            return false;
        }
        break;
    case RGB_MOD:
        if(shift_mods) {
            if (record->event.pressed) rgb_matrix_increase_hue();
            return false;
        }
        break;
    case RGB_RMOD:
        if(shift_mods) {
            if (record->event.pressed) rgb_matrix_decrease_hue();
            return false;
        }
        break;
    }

    return true;
}

void matrix_scan_user(void) {     // The very important timer.
    if (is_alt_tab_active && timer_elapsed32(alt_tab_timer) > 750) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
}
