#include QMK_KEYBOARD_H


enum layers{
  _BASE,
  _FN,
  _NUM
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
           KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,     KC_DEL, KC_MUTE,
           KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,      KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
           KC_LSHIFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, KC_RSFT,                       KC_UP,
           KC_LCTRL,  KC_LGUI, KC_LALT,          KC_SPC,  KC_SPC,  KC_SPC,           KC_RALT,   MO(2), KC_RCTRL,                        KC_LEFT, KC_DOWN, KC_RIGHT
           ),
  [_FN] = LAYOUT(
           KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,      KC_9,    KC_0,    KC_MINS, KC_EQL, KC_DEL,     KC_PGDN, KC_PGUP,
           KC_CAPS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_TRNS,
           KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS,
           RESET,     KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          MO(3),  KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS
           ),
  [_NUM] = LAYOUT(
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_1,
           KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS,                                KC_2, KC_3, KC_4
           ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return false;

}

#ifdef OLED_ENABLE

// Used to draw on to the oled screen
bool oled_task_user(void) {
    oled_set_cursor(0, 0);                              // sets cursor to (row, column) using charactar spacing (5 rows on 128x32 screen, anything more will overflow back to the top)
   switch (get_highest_layer(layer_state)) {            // gets layer information and prints layer
    case _BASE:
      oled_write_P(PSTR("Layer:Default\n"), false);
      break;
    case _FN:
      oled_write_P(PSTR("Layer:Function\n"), false);
      break;
    case _NUM:
      oled_write_P(PSTR("Layer: Numbers\n"), false);
    default:
      oled_write_P(PSTR("huh\n"), false);
    };

    led_t led_state = host_keyboard_led_state();        // caps lock stuff, prints CAPS on new line if caps led is on
    oled_set_cursor(0, 1);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("       "), false);
    uint8_t mod_state = get_mods();
    oled_set_cursor(0,2);

    oled_write_P(PSTR("S"), mod_state & MOD_MASK_SHIFT);
    oled_advance_char();
    oled_write_P(PSTR("C"), mod_state & MOD_MASK_CTRL);
    oled_advance_char();
    oled_write_P(PSTR("A"), mod_state & MOD_MASK_ALT);
    oled_advance_char();
    oled_write_P(PSTR("G"), mod_state & MOD_MASK_GUI);
    oled_advance_char();

    return false;
}
#endif
