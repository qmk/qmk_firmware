/* Copyright 2022 Cameron Larsen <@cameronjlarsen>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include <stdio.h>
#include "features/oneshot.h"

enum layers {
    _QWERTY = 0,
    SYM,
    NAV,
    FUN,
};
//  Aliases for readability
#define QWERTY DF(_QWERTY)
#define LA_SYM LT(SYM, KC_TAB)
#define LA_NAV MO(NAV)

// One shot mods
enum keycodes {
    OS_SHFT = QK_USER,    
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * Inspiration:
 *
 * https://github.com/serebrov/qmk_firmware/blob/custom/keyboards/kyria/keymaps/kyria-mini/keymap.c
 *
 * Notes:
 * - F & J enables CAPSWORD, disables after 5 seconds
 * - Left thumb CTRL and SHIFT are one shot
 * - Enter is moved to ; location and ; is moved to Sym layer
 * - ESC can be accessed by NAV and G
 * - BKSP is accessed by NAV and Enter
 * - Tab is accessed by tapping SYM layer
 * - FUN layer is accessed by holding NAV and SYM layers at the same time
 *
 * ,----------------------------------.                       ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |                       |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|                       |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |                       |   H  |   J  |   K  |   L  | Enter|
 * |------+------+------+------+------.                       ,------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |                       |   N  |   M  | ,  < | . >  | /  ? |
 * `------+------+------+------+------+------.         ,------+------+------+------+-------------'
 *                     |  OSM  |  OSM | Nav  |         | Sym  | Space| GUI  |
 *                     |  Ctrl | Shift|      |         | Tab  |      |      |
 *                     `---------------------'         `--------------------'
 */
    [_QWERTY] = LAYOUT_split_3x5_3(
      KC_Q  ,  KC_W  ,  KC_E  ,   KC_R ,   KC_T ,                           KC_Y,  KC_U ,  KC_I ,   KC_O ,   KC_P ,
      KC_A  ,  KC_S  ,  KC_D  ,   KC_F ,   KC_G ,                           KC_H,  KC_J ,  KC_K ,   KC_L , KC_ENT ,
      KC_Z  ,  KC_X  ,  KC_C  ,   KC_V ,   KC_B ,                           KC_N,  KC_M ,KC_COMM, KC_DOT , KC_SLSH,
                                OS_CTRL, OS_SHFT, LA_NAV ,       LA_SYM , KC_SPC, OS_GUI
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * Notes:
 * - Symbols are grouped together and shifted symbols from middle row are on bottom row
 * - Exception is angle brackets
 *
 * ,----------------------------------.                       ,----------------------------------.
 * |  1 ! |  2 @ |  3 # |  4 $ |  5 % |                       |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |
 * |------+------+------+------+------|                       |------+------+------+------+------|
 * |  `   |  (   |  )   |  '   |  =   |                       |   \  |  -   |  [   |  ]   |  ;   |
 * |------+------+------+------+------+                       +------+------+------+------+------|
 * |  ~   |  <   |  >   |  "   |  +   |                       |   |  |  _   |  {   |  }   |  :   |
 * `-------------+------+------+------+------.         ,------+------+------+------+-------------'
 *                      |      |      |      |         |      |      |      |
 *                      |      |      |      |         |      |      |      |
 *                      `--------------------'         `--------------------'
 */
    [SYM] = LAYOUT_split_3x5_3(
        KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                          KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 ,
      KC_GRV , KC_LPRN, KC_RPRN, KC_QUOT, KC_EQL ,                        KC_BSLS, KC_MINS, KC_LBRC, KC_RBRC, KC_SCLN,
      KC_TILD, KC_LABK, KC_RABK, KC_DQUO, KC_PLUS,                        KC_PIPE, KC_UNDS, KC_LCBR, KC_RCBR, KC_COLN,
                                 _______, _______, _______,      _______, _______, _______
    ),

/*
 * Nav Layer: Navigation, Media
 *
 * Notes:
 * - Vim style navigation keys
 * - Volume and Media Keys
 * - BKSP on Enter
 * - DEL on /
 * - Esc on G
 *
 * ,----------------------------------.                       ,----------------------------------.
 * |      |      |      | BriUp| BriDn|                       | Home | PgDn | PgUp | End  |PrtScr|
 * |------+------+------+------+------|                       |------+------+------+------+------|
 * |  GUI |  Alt | Ctrl | Shift| Esc  |                       |   ←  |  ↓   |   ↑  |   →  | Bksp |
 * |------+------+------+------+------+                       +------+------+------+------+------|
 * |      | Vol- | Mute | Vol+ |NumLck|                       | MPrev| MPlay| MStop| MNext|Delete|
 * `-------------+------+------+------+------.         ,------+------+------+------+-------------'
 *                      |      |      |      |         |      |      |      |
 *                      |      |      |      |         |      |      |      |
 *                      `--------------------'         `--------------------'
 */
    [NAV] = LAYOUT_split_3x5_3(
       _______, _______, _______, KC_BRIU, KC_BRID,                       KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_PSCR,
       OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, KC_ESC ,                       KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_BSPC,
       _______, KC_VOLD, KC_MUTE, KC_VOLU, KC_NUM ,                       KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_DEL ,
                                  _______, _______, _______,     _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * Notes:
 * - F1-F10 on bottom row
 * - F11-F12 on index finger inner row
 * - Homerow mods
 * - Num keys on top row
 *
 * ,----------------------------------.                       ,----------------------------------.
 * |  1 ! |  2 @ |  3 # |  4 $ |  5 % |                       |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |
 * |------+------+------+------+------|                       |------+------+------+------+------|
 * |  GUI |  Alt | Ctrl | Shift| F11  |                       | F12  | Shift| Ctrl |  Alt |  GUI |
 * |------+------+------+------+------+                       +------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |                       |  F6  |  F7  |  F8 |  F9  | F10  |
 * `-------------+------+------+------+------.         ,------+------+------+------+-------------'
 *                      |      |      |      |         |      |      |      |
 *                      |      |      |      |         |      |      |      |
 *                      `--------------------'         `--------------------'
 */
    [FUN] = LAYOUT_split_3x5_3(
         KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                         KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 ,
       OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, KC_F11 ,                       KC_F12 , OS_SHFT, OS_CTRL, OS_ALT , OS_GUI ,
        KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,                        KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 ,
                                 _______, _______, _______,     _______, _______, _______
    ),

};

enum combo_events {
    CAPS_COMBO,
    // Other combos...
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM caps_combo[] = {KC_F, KC_J, COMBO_END};

combo_t key_combos[] = {
  [CAPS_COMBO] = COMBO_ACTION(caps_combo),
  // Other combos...C
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CAPS_COMBO:
      if (pressed) {
        caps_word_on();  // Activate Caps Word!
      }
      break;

    // Other combos...
  }
}

bool is_oneshot_cancel_key(uint16_t keycode){
  switch (keycode) {
    case LA_NAV:
      return true;
    default:
      return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode){
  switch (keycode) {
    case LA_NAV:
    case LA_SYM:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
      return true;
    default:
      return false;
  }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;



bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
    case KC_MINS:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}


layer_state_t layer_state_set_user(layer_state_t state){
  return update_tri_layer_state(state, SYM, NAV, FUN);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Sym"), false);
            break;
        case NAV:
            oled_write_ln_P(PSTR("Nav"), false);
            break;
        case FUN:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_caps_word(keycode, record)) { return false; }
  // Your macros ...
  update_oneshot(
      &os_shft_state, KC_LSFT, OS_SHFT,
      keycode, record
    );

  update_oneshot(
      &os_ctrl_state, KC_LCTL, OS_CTRL,
      keycode, record
    );

  update_oneshot(
      &os_alt_state, KC_LALT, OS_ALT,
      keycode, record
    );

  update_oneshot(
      &os_cmd_state, KC_LGUI, OS_GUI,
      keycode, record
    );
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}

#endif
