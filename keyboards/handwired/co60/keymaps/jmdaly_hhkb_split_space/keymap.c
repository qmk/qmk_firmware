/* Copyright 2019 John M Daly <jmdaly@gmail.com>
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

enum co60_layers {
  _L1,
  _L2,
  _L3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default base layer. Except for the bottom row, this
  // is close to a standard HHKB layout.
  [_L1] = LAYOUT_60_hhkb_split_625u_space( /* Base */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7, KC_8,    KC_9,    KC_0,    KC_MINS,    KC_EQL,  KC_BSLS, KC_GRV,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC,    KC_RBRC, KC_BSPC,
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_ENT,
    SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, MO(_L3),
             KC_LALT, KC_LGUI,       KC_ENT,              MO(_L3),       KC_SPC,  QK_LEAD, KC_RGUI, KC_RALT
  ),
  // My preferred base layout. This doesn't match the caps
  // on my boards, so I don't make it default.
  [_L2] = LAYOUT_60_hhkb_split_625u_space( /* Base */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7, KC_8,    KC_9,    KC_0,    KC_MINS,    KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC,    KC_RBRC, KC_BSPC,
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_ENT,
    SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, MO(_L3),
             KC_LALT, KC_LGUI,       KC_ENT,              MO(_L3),       KC_SPC,  QK_LEAD, KC_RGUI, KC_RALT
  ),
  [_L3] = LAYOUT_60_hhkb_split_625u_space( /* Function */
    QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,     KC_F10,    KC_F11,     KC_F12,   _______, _______,
    BL_BRTG, BL_TOGG, BL_UP,   BL_DOWN,BL_ON, BL_OFF, _______, _______, _______, _______,   _______,   KC_PGUP,    KC_INSERT,  KC_DEL,
    _______, RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,  KC_HOME,   KC_END,     _______,
    _______, BL_DOWN, _______, _______, _______, _______, _______, DF(_L1), DF(_L2), _______,   KC_PGDN,   _______, _______,
             _______, _______,          _______,          _______,          _______, _______,   _______,   _______
  )
};

void leader_end_user() {
  // Close a program in i3wm
  if (leader_sequence_one_key(KC_Q)) {
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    register_code(KC_Q);
    unregister_code(KC_Q);
    unregister_code(KC_LSFT);
    unregister_code(KC_LGUI);
  }
  // Exit i3wm
  if (leader_sequence_one_key(KC_E)) {
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    register_code(KC_E);
    unregister_code(KC_E);
    unregister_code(KC_LSFT);
    unregister_code(KC_LGUI);
  }
  // Copy selected text in suckless terminal
  if (leader_sequence_one_key(KC_C)) {
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
  }
  // Paste text in suckless terminal
  if (leader_sequence_one_key(KC_V)) {
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_V);
    unregister_code(KC_V);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
  }
  // FZF shortcut to fuzzy switch directories
  if (leader_sequence_one_key(KC_D)) {
    register_code(KC_LALT);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LALT);
  }
  // Send keys to bring up fuzzy process kill
  if (leader_sequence_one_key(KC_K)) {
    SEND_STRING("kill " SS_TAP(X_TAB));
  }
  // Send keys to start neovim and fuzzy search for filename
  if (leader_sequence_one_key(KC_T)) {
    SEND_STRING("nvim ");
    register_code(KC_LCTL);
    register_code(KC_T);
    unregister_code(KC_T);
    unregister_code(KC_LCTL);
  }
  // Switch between windows in tmux
  if (leader_sequence_one_key(KC_L)) {
    register_code(KC_LCTL);
    register_code(KC_B);
    unregister_code(KC_B);
    unregister_code(KC_LCTL);
    register_code(KC_L);
    unregister_code(KC_L);
  }
}
