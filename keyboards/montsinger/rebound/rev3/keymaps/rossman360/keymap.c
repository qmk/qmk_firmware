#include QMK_KEYBOARD_H
#include "rossman360.h"

#define PGMOD LT(_NUM, KC_PGDN)
#define TABMOD LT(_FN1, KC_TAB)
#define SPCMOD LT(_FN1, KC_SPACE)
#define ENTMOD LT(_FN2, KC_ENTER)
#define ESCMOD LT(_NUM, KC_ESC)
#define RSMOD LT(_FN1, KC_RSHIFT)

enum layer_names {
  _BASE,
  _DEL,
  _FN1,
  _FN2,
  _NUM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_all(
    KC_ESC  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , NTAB  ,
    JUMPBACK, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,MO(_DEL), KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , LM(_FN1, MOD_LALT), KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_MINS,
    CMDBSP  , ALTDEL , KC_NO  , CTRLSP , KC_TAB , PGMOD  , QUIT   , ENTMOD , SPCMOD , MO(_DEL),KC_NO  , KC_BSPC, KC_DEL
  ),

[_FN1] = LAYOUT_all(
    _______, TAB1   , TAB2   , TAB3   , TAB4   , _______,          _______, UNDO   , _______, _______, _______, CTAB   ,
    KC_CAPS, _______, _______, _______, _______, _______, _______, KC_HOME, KC_LEFT, KC_UP  , KC_RIGHT,KC_END , KC_NO  ,
    _______, _______, XPANDR , _______, _______, _______, _______, _______, PMERGE , KC_DOWN, _______, _______, EMDASH ,
    WREFRESH,_______, _______, _______, LWORD  , RWORD  , _______, KC_NO  , _______, KC_NO  , _______, _______, _______
  ),

[_FN2] = LAYOUT_all(
    _______, SPEAK1 , SPEAK2 , SPEAK3 , SPEAK4 , _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, PARADOWN, CSPEAK, _______, _______, KC_NO  , KC_NO  , _______, _______, _______
  ),

[_DEL] = LAYOUT_all(
    RESET,   _______, _______, _______, _______, _______,          _______, UNDO   , _______, _______, _______, CTAB   ,
    REMCAPS, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_UP  ,KC_RIGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOWN, _______, _______, _______,
    _______, _______, _______, KC_DEL , KC_BSPC, BWORD  , _______, KC_NO  , KC_NO  , _______, _______, _______, _______
  ),

[_NUM] = LAYOUT_all(
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_6   , KC_7   , KC_8   , KC_9   , KC_MINS, KC_EQL,
    KC_CAPS, _______, _______, _______, _______, _______, _______, KC_MINS, KC_4   , KC_5   , KC_6   , KC_COLN, _______,
    _______, _______, _______, _______, _______, KC_LBRC, _______, KC_RBRC, KC_1   , KC_2   , KC_3   , KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_NO  , KC_NO  , KC_0   , _______, _______, _______
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
   switch(get_highest_layer(layer_state)){
case _BASE:
    if (clockwise) {
      tap_code16(KC_VOLD);
    } else {
      tap_code16(KC_VOLU);
    }
   break;
 case _FN1:
    if (clockwise) {
      tap_code16(S(KC_TAB));
    } else {
      tap_code16(KC_TAB);
    }
   break;
}
    return true;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR(""), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Rebound\n"), false);
            oled_write_P(PSTR("Rev3.1\n"), false);
	    break;
        case _FN1:
            oled_write_P(PSTR("Fn\n"), false);
            break;
        case _FN2:
            oled_write_P(PSTR("Para\n"), false);
            break;
            case _NUM:
            oled_write_P(PSTR("Num\n"), false);
            break;
            case _DEL:
            oled_write_P(PSTR("Del\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
}

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}

#endif
