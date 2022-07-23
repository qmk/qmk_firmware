#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _OTHER
};


//Tap Dance Declarations
enum {
  TD_RST,
  TD_DBQT
};

void dance_rst_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_RST] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, NULL, dance_rst_reset),
 [TD_DBQT] = ACTION_TAP_DANCE_DOUBLE (KC_QUOTE, KC_DQT)
};

enum custom_keycodes {
  M_PAR = SAFE_RANGE,
  M_BKT
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_PAR:
      if (record->event.pressed) {
        SEND_STRING("()" SS_TAP(X_LEFT));
      }
      break;
    case M_BKT:
      if (record->event.pressed) {
        SEND_STRING("[]" SS_TAP(X_LEFT));
      }
      break;
  }
  return true;

};

#define OTHER MO(_OTHER)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Default layer
   * ┌─────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬──────┐
   * │ Esc │Tab │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │ -  │ BsPc │
   * ├─────┼────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴──────┤
   * │PgUp │Caps │ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │  Enter   │
   * ├─────┼─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────────┤
   * │PgDn │LShift │ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │ Other  │
   * ├─────┼────┬──┴─┬──┴─┬──┴────┴────┴────┴────┴────┴───┬┴────┴┬───┴─┬──────┤
   * │ END │Del │Gui │Alt │      Right KC = 7u/2.25u      │Raise │Menu │ Lower│
   * └─────┴────┴────┴────┴───────────────────────────────┴──────┴─────┴──────┘
   */
  [_QWERTY] = LAYOUT_base_kit_all(
    KC_ESC,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS, KC_BSPC,
    KC_PGUP, KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOTE, KC_ENT,
    KC_PGDN, KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  OTHER,
    KC_END,  KC_DEL,  KC_LGUI, KC_LALT,              LOWER,           KC_SPACE,               KC_CAPS, RAISE,   KC_RGUI,  LOWER
  ),

  /* LOWER layer
   * ┌─────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬──────┐
   * │  `  │    │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 0  │ _  │      │
   * ├─────┼────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴──────┤
   * │  ~  │     │ !  │ @  │ #  │ $  │ %  │ ^  │ &  │ *  │(..)│[..]│ ' and "  │
   * ├─────┼─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────────┤
   * │     │       │    │    │    │    │    │    │    │    │    │    │        │
   * ├─────┼────┬──┴─┬──┴─┬──┴────┴────┴────┴────┴────┴───┬┴────┴┬───┴─┬──────┤
   * │     │    │    │    │                               │      │     │      │
   * └─────┴────┴────┴────┴───────────────────────────────┴──────┴─────┴──────┘
   */
  [_LOWER] = LAYOUT_base_kit_all(
    KC_GRAVE,  _______,  KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,     KC_0,       KC_UNDS,    _______,
    KC_TILD,   _______,  KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,   M_PAR,    M_BKT,      _______,    TD(TD_DBQT),
    _______,   _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,    _______,    _______,
    _______,   _______,  _______,   _______,                    _______,               _______,                  _______,  _______,    _______,    _______
  ),

  /* RAISE layer
   * ┌─────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬──────┐
   * │  \  │    │    │    │    │    │    │    │    │    │    │    │ =  │      │
   * ├─────┼────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴──────┤
   * │  |  │CAPS │    │    │    │    │    │    │    │    │    │    │    +     │
   * ├─────┼─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────────┤
   * │     │       │    │    │    │    │    │    │    │    │ [  │ ]  │        │
   * ├─────┼────┬──┴─┬──┴─┬──┴────┴────┴────┴────┴────┴───┬┴────┴┬───┴─┬──────┤
   * │     │    │    │    │                               │      │     │      │
   * └─────┴────┴────┴────┴───────────────────────────────┴──────┴─────┴──────┘
   */
  [_RAISE] = LAYOUT_base_kit_all(
    KC_BSLS,  _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   KC_EQUAL,   _______,
    KC_PIPE, KC_CAPS,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,    KC_PLUS,
    _______,  _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_LBRC,   KC_RBRC,    _______,
    _______,  _______,  _______,    _______,                      _______,                _______,                      _______,    _______,   _______,    _______
  ),

  /* OTHER layer
   * ┌─────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬──────┐
   * │HOME │    │    │    │    │    │    │    │    │    │    │ UP │    │      │
   * ├─────┼────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴──────┤
   * │END  │     │    │    │    │    │    │    │    │    │LEFT│RGHT│          │
   * ├─────┼─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────────┤
   * │     │       │    │    │    │    │    │    │    │    │DOWN│    │        │
   * ├─────┼────┬──┴─┬──┴─┬──┴────┴────┴────┴────┴────┴───┬┴────┴┬───┴─┬──────┤
   * │QK_BOOT│    │    │    │                               │      │     │      │
   * └─────┴────┴────┴────┴───────────────────────────────┴──────┴─────┴──────┘
   */
  [_OTHER] = LAYOUT_base_kit_all(
    _______,    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_UP,     _______,   _______,
    _______,    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_LEFT,    KC_RIGHT,  _______,   _______,
    _______,    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   KC_DOWN,    _______,   _______,
    TD(TD_RST), _______,  _______,    _______,                      _______,               _______,                       _______,   _______,    _______,   _______
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(_LOWER, KC_SPACE):
      return 160;
    case TD(TD_DBQT):
      return 230;
    default:
#ifndef TAPPING_TERM
      return 200;
#else
      return TAPPING_TERM;
#endif
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _LOWER:
      rgblight_setrgb (RGB_CORAL);
      break;
    case _RAISE:
      rgblight_setrgb (RGB_RED);
      break;
    case _OTHER:
      rgblight_setrgb (RGB_BLUE);
      break;
    default: //  for any other layers, or the default layer
      rgblight_setrgb (RGB_GREEN);
      break;
  }
  return state;
}
