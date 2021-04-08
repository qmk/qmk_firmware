/* Copyright 2020 Harrison Chan (Xelus)
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap BASE: (Base Layer) Default Layer
   * ,-------------------.  ,-------------------------------------------------------------------.
   * |-   | *  | /  |NmLK|  |Esc| 1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|pipe| ~  | Pscr|
   * |-------------------|  |-------------------------------------------------------------------|
   * |    | 9  | 8  | 7  |  |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| BSPC  | Del |
   * |  + |--------------|  |-------------------------------------------------------------------|
   * |    | 6  | 5  | 4  |  |Caps   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return   | Pgup|
   * |-------------------|  |-------------------------------------------------------------------|
   * |    | 3  | 2  | 1  |  |Shift    |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up | Pgdn|
   * | ENT|-------------------------------------------------------------------------------------|
   * |    | .  | 0       |  | Ctrl | Win | Alt |    Space        | FN | Ctrl |  |Left| Dn | Rght|
   * `------------------------------------------------------------------------------------------'
   */
  [0] = LAYOUT_ext65(
    KC_PMNS, KC_PAST, KC_PSLS, KC_NLCK, KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSLS, KC_GRV , KC_PSCR,
    KC_PPLS, KC_P9  , KC_P8  , KC_P7  , KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSPC,          KC_DEL ,
    KC_PPLS, KC_P6  , KC_P5  , KC_P4  , KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,                   KC_PGUP,
    KC_PENT, KC_P3  , KC_P2  , KC_P1  , KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,                   KC_UP  , KC_PGDN,
    KC_PENT, KC_PDOT, KC_P0  , KC_P0  , KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC ,                   MO(1)  , KC_RCTL,                   KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [1] = LAYOUT_ext65(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
    KC_TRNS, RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          EEP_RST,
    KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   DEBUG,
    KC_TRNS, RGB_HUD, RGB_SAD, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT_ext65(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [3] = LAYOUT_ext65(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
  )
};

#ifdef OLED_DRIVER_ENABLE

void render_layer_state(void) {
    oled_write_ln(PSTR("LAYER"), false);
    oled_write_ln(PSTR("L1"), layer_state_is(1));
    oled_write_ln(PSTR("L2"), layer_state_is(2));
    oled_write_ln(PSTR("L3"), layer_state_is(3));
    oled_write_ln(PSTR(" "), false);
}

void render_keylock_status(led_t led_state) {
    oled_write_ln(PSTR("Lock:"), false);
    oled_write(PSTR("N"), led_state.num_lock);
    oled_write(PSTR("C"), led_state.caps_lock);
    oled_write_ln(PSTR("S"), led_state.scroll_lock);
    oled_write_ln(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln(PSTR("Mods:"), false);
    oled_write(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_ln(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_ln(PSTR(" "), false);
}

void oled_task_user(void) {
    render_layer_state();
    render_keylock_status(host_keyboard_led_state());
    render_mod_status(get_mods()|get_oneshot_mods());
}

#endif
