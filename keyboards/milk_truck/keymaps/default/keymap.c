/* Copyright 2022 rjboone
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

enum layers{
  _BASE,
  _NUM_SYM,
  _FKEY_RGB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
      KC_P7,   KC_P8,   KC_P9,            KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,    KC_BSPC,
      KC_P4,   KC_P5,   KC_P6,            KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,  KC_G,  KC_H,  KC_J,  KC_K,     KC_L,    KC_SCLN, KC_ENT,
      KC_P1,   KC_P2,   KC_P3,   KC_UP,   KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, MO(_FKEY_RGB),
      KC_P0,   KC_PENT, KC_LEFT, KC_DOWN, KC_RIGHT,  KC_LCTL, KC_LALT,    MO(_NUM_SYM),      KC_SPC,        KC_RALT,  KC_RGUI, KC_RCTL, KC_BSLS
    ),

    [_NUM_SYM] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS,          KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_MINS, KC_EQL,  KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUOT,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_NAV] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_UP,    KC_TRNS,    KC_TRNS,    KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_RSFT,        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_FKEY_RGB] = LAYOUT(
      RGB_TOG, RGB_RMOD, RGB_MOD,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      RGB_HUI, RGB_SAI,  RGB_VAI,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      RGB_HUD, RGB_SAD,  RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#ifdef OLED_ENABLE  //Special thanks to Sickbabies for this great OLED widget!
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  // rotates for proper orientation
}

void render_milktruck_logo(void) {
    static const char PROGMEM milktruck_logo[] = {
	// 'milktruck_logo', 32x20px
  0xdf, 0x10, 0x10, 0x00, 0x9f, 0x40, 0x8f, 0x10, 0xcf, 0x00, 0xdf, 0x15, 0xd1, 0x40, 0x40, 0x00,
0xc0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x34, 0x04, 0x04, 0x34, 0xc8, 0x00, 0x00, 0x00,
0xf7, 0x24, 0x44, 0x20, 0xf7, 0x02, 0x17, 0xf0, 0x17, 0x04, 0xf7, 0x00, 0x07, 0x04, 0xf7, 0x80,
0x47, 0x31, 0x07, 0x00, 0x00, 0x00, 0xff, 0x00, 0xf0, 0xf8, 0xfc, 0xfe, 0x00, 0xff, 0x00, 0x00,
0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x08, 0x0f, 0x08, 0x00, 0x0f, 0x08, 0x08, 0x00, 0x0f, 0x00,
0x01, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00
};

  oled_write_raw_P(milktruck_logo, sizeof(milktruck_logo));
}

static void render_layer_status(void) {
    oled_write_P(PSTR("-----"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _NUM_SYM:
            oled_write_ln_P(PSTR("NUM"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("NAV"), false);
            break;
        case _FKEY_RGB:
            oled_write_ln_P(PSTR("FUNC"), false);
            break;
        default:
            oled_write_ln_P(PSTR(" "), false);
    }
}

#    define KEYLOG_LEN 11
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

//Text only renders
void render_keylogger_status(void) {
    oled_write_P(PSTR("-----"), false);
    oled_write(keylog_str, false);
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("C"), led_state.caps_lock);
	oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
	oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), led_state.scroll_lock);
    //oled_write_ln_P(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
       oled_write_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("SHFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_ln_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("CTRL"), (modifiers & MOD_MASK_CTRL));
    oled_write_ln_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

bool oled_task_user(void) {
    render_milktruck_logo();
    oled_set_cursor(0,3);
    render_layer_status();	// Renders the current keyboard state (layer, lock, caps, scroll, etc)
	render_mod_status(get_mods()|get_oneshot_mods());
	render_keylock_status(host_keyboard_led_state());
	render_keylogger_status();

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
      add_keylog(keycode);
    }
    return true;
  }
#endif
