/* Copyright 2020 jagdpietr
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


bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// Super ALT-TAB macro tied to rotary function
void encoder_update_user(uint8_t index, bool clockwise) {
        if (clockwise) {
          if (!is_alt_tab_active) {
            is_alt_tab_active = true;
              register_code(KC_LALT);
              }
              alt_tab_timer = timer_read();
              tap_code(KC_TAB);
        } else {
          if (!is_alt_tab_active) {
            is_alt_tab_active = true;
              register_code(KC_LALT);
              }
              alt_tab_timer = timer_read();
              tap_code16(S(KC_TAB));
    }
}


void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {  // wait 750ms
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

// this is the mod mask you wish to use to toggle the "spongebob mocking text"
// credit to u/synmuffin on reddit - reddit.com/r/MechanicalKeyboards/kj031g/
#define MODS_MASK (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LCTRL))

// bool that holds the current state on or off
bool is_sponge_active = false;

// random bool
bool random_bool(void) {
    bool rbool = rand() & 1;
    return rbool;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {	
	case KC_A ... KC_Z: {
            if (is_sponge_active && record->event.pressed) {
                if (random_bool()) {
                    register_code(KC_LSHIFT);
                }
            }
        break;
        }
        case KC_RSFT:
            if ((keyboard_report->mods & MODS_MASK) && record->event.pressed) is_sponge_active = !is_sponge_active;
        break;
    }
    return true;
	
	
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_A ... KC_Z: {
            if (is_sponge_active && record->event.pressed) {
                unregister_code(KC_LSHIFT);
            }
        }
    }

}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ansi(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,            KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,           KC_MPRV, KC_TRNS, KC_MNXT,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                     KC_MPLY,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                                               KC_APP,  MO(1),          KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [1] = LAYOUT_ansi(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_TRNS,           KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                    KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                              KC_TRNS, KC_TRNS,          KC_HOME, KC_PGDN, KC_END
    ),

    [2] = LAYOUT_ansi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                    KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                              KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    ),   
    [3] = LAYOUT_ansi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                    KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                              KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    ),     
};
