/* Copyright 2019 ashpil
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

enum layers {
    _BL0,
    _BL1,
    _FL,
    _MS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL0] = LAYOUT( /* Base layer - Windows key instead of CapsLock, hold ESC for special functions */
    LT(_FL,KC_ESC),   KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10,  KC_F11 , KC_F12 , KC_PSCR, KC_SLCK, KC_PAUS,
    KC_GRV , KC_1,    KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_INS , KC_HOME, KC_PGUP, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB , KC_Q,    KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL , KC_END , KC_PGDN, KC_P7,   KC_P8  , KC_P9  , KC_PPLS,
    KC_LWIN, KC_A,    KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT ,                            KC_P4,   KC_P5  , KC_P6  ,
    KC_LSFT, KC_NUBS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT,          KC_UP  ,          KC_P1,   KC_P2  , KC_P3  , KC_PENT,
    KC_LCTL,          KC_LALT,                            KC_SPC ,                                     KC_RALT,          KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,            KC_PDOT
  ),

  [_BL1] = LAYOUT( /* Base layer - standard layout without any special functions */
    KC_ESC ,          KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PSCR, KC_SLCK, KC_PAUS,
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_INS , KC_HOME, KC_PGUP, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL , KC_END , KC_PGDN, KC_P7,   KC_P8  , KC_P9  , KC_PPLS,
    KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT ,                            KC_P4,   KC_P5  , KC_P6  ,
    KC_LSFT, KC_NUBS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT,          KC_UP  ,          KC_P1,   KC_P2  , KC_P3  , KC_PENT,
    KC_LCTL,          KC_LALT,                            KC_SPC ,                                     KC_RALT,          KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,            KC_PDOT
  ),

  [_FL] = LAYOUT( /* special functions layer */
    // F1: dyn. macro 1 play
    // F2: dyn. macro 2 play
    // F3: dyn. macro 1 record
    // F4: dyn. macro 2 record
    // F5: dyn. macro record stop
    // Capslock: CapsLock (really!)
    // ~: Key Lock
    // Cursor: Media Pref / Next / Volume Up / Volume Down
    // Space:  Media Play / Pause
    // m: enter mouse layer
    _______,          DM_PLY1, DM_PLY2, DM_REC1, DM_REC2, DM_RSTP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_LOCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, TG(_MS), _______, _______, _______,          _______,          KC_VOLU,          _______, _______, _______, _______,
    _______,          _______,                            KC_MPLY,                                     _______,          _______, KC_MPRV, KC_VOLD, KC_MNXT, _______,          _______
  ),

  [_MS] = LAYOUT( /* mouse key layer */
  // Cursor: mouse, INS/HOME/PgUp: Mouse Accel, Del, End, PageDn: mouse buttons
    TG(_MS),          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_MS_U,          _______, _______, _______, _______,
    _______,          _______,                            _______,                                     _______,          _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,          _______
  )
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
    dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    return true;
}
