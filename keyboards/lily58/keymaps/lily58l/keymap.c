 /* Copyright 2017 F_YUUCHI
  * Copyright 2020 Drashna Jaelre <@drashna>
  * Copyright 2020 Ben Roesner (keycapsss.com)
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


extern uint8_t is_master;

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                             KC_LALT, KC_LGUI,LOWER, KC_SPC,   KC_ENT,   RAISE,   KC_BSPC, KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, UG_TOGG, UG_HUEU, UG_SATU, UG_VALU,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UG_NEXT, UG_HUED, UG_SATD, UG_VALD,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_0;
    }
}

void render_lily58_logo(void) {
    static const char PROGMEM lily58_logo[] = {
    // 'logo', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x40, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00,
    0x80, 0xe0, 0x70, 0x3c, 0x0e, 0x06, 0x0e, 0x3c, 0x70, 0xe0, 0x80, 0x00, 0x00, 0xc0, 0xc0, 0x00,
    0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x80,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0xc0, 0x80, 0x80, 0x80, 0x81, 0x83, 0x83,
    0x07, 0x07, 0x0c, 0x18, 0x70, 0xe0, 0x80, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x80, 0xb6, 0xb6, 0x80,
    0xb0, 0xb0, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf1, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0x00, 0x00, 0x00, 0x30, 0xf0, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xf0,
    0x30, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xe1, 0x71, 0x71, 0xf1, 0xf1, 0xe1, 0xc1, 0x81, 0x00, 0x00,
    0x00, 0x00, 0x0c, 0x3f, 0xff, 0xf3, 0xe1, 0xc1, 0xc1, 0x81, 0x81, 0xc3, 0xff, 0x7f, 0x1c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x70, 0x78, 0xdc, 0xcc, 0x86, 0x06, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x03, 0x02, 0x06, 0x84, 0xe1, 0xfb, 0x38, 0x1c, 0x0c, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x03, 0x03, 0x06, 0x86, 0xcc, 0xdc, 0x78, 0x70, 0x20, 0x00, 0xff, 0xff, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x7e, 0xf8, 0xe0, 0xf0, 0x7e, 0x1f, 0x03, 0x00,
    0x00, 0x00, 0x00, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xe1, 0xff, 0x7f, 0x3f, 0x00,
    0x00, 0x00, 0x3e, 0xff, 0xff, 0xc1, 0xc0, 0x80, 0x81, 0x81, 0xc3, 0xc3, 0xff, 0xfe, 0x3c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04, 0x06,
    0x06, 0x02, 0x03, 0x01, 0x01, 0x00, 0x01, 0x01, 0x03, 0x02, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04,
    0x06, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x01, 0x00, 0x00, 0x60, 0x60, 0x70, 0x38, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
};
    oled_write_raw_P(lily58_logo, sizeof(lily58_logo));
}


#    define KEYLOG_LEN 6
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    oled_write_P(PSTR(" "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QRTY"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("LOW"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("HIGH"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("ADJ"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

void render_keylock_status(led_t led_state) {
    oled_write_ln_P(PSTR("Lock"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_ln_P(PSTR("S"), led_state.scroll_lock);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln_P(PSTR("Mods"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_status_main(void) {
    // Show keyboard layout
    render_default_layer_state();
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    // Show host keyboard led status
    render_keylock_status(host_keyboard_led_state());
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    // Show modifier status
    render_mod_status(get_mods());
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    render_keylogger_status();
}

bool oled_task_user(void) {
  update_log();
  if (is_keyboard_master()) {
    render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_lily58_logo();
  }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
    }
    return true;
}
#endif // OLED_ENABLE


// Rotary encoder related code
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // Encoder on master side
    if(IS_LAYER_ON(_RAISE)) { // on Raise layer
      // Cursor control
      if (clockwise) {
          tap_code(KC_MNXT);
      } else {
          tap_code(KC_MPRV);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_VOLU);
      } else {
          tap_code(KC_VOLD);
      }
    }
  }
  else if (index == 1) { // Encoder on slave side
    if(IS_LAYER_ON(_LOWER)) { // on Lower layer
      //
      if (clockwise) {
          tap_code(KC_RIGHT);
      } else {
          tap_code(KC_LEFT);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_DOWN);
      } else {
          tap_code(KC_UP);
      }
    }
  }
    return true;
}
#endif
