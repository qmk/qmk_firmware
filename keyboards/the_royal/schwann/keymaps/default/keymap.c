#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _OTHER
};

enum schwann_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

//Tap Dance Declarations
enum {
  TD_RST
};

void dance_rst_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

//All tap dance functions would go here. Only showing this one.
tap_dance_action_t tap_dance_actions[] = {
  [TD_RST] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, NULL, dance_rst_reset)
};


#define XXXXX KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Default Layer
   * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
   * │Tab │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │BkSp│
   * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
   * │LCtl│ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │ '  │
   * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
   * │LSft│ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │Entr│
   * └────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┘
   *      │Del │Gui │Alt │Lwr │         │Rse │Alt │Menu│Ctrl│
   *      └────┴────┴────┴────┴─────────┴────┴────┴────┴────┘
   */

  [_QWERTY] = LAYOUT_mit(
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,    KC_BSPC,
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, KC_ENT,
              KC_DEL,  KC_LGUI, KC_LALT, LOWER,     KC_SPACE,       RAISE,   KC_RALT,  KC_MENU,  KC_RCTL
  ),

  /* Lower Layer
   * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
   * │Esc │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 0  │    │
   * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
   * │ ~  │ !  │ @  │ #  │ $  │ %  │ ^  │ &  │ *  │ (  │ )  │ "  │
   * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
   * │    │    │    │    │    │    │    │    │ `  │ [  │ ]  │ .  │
   * └────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┘
   *      │    │    │    │    │         │    │    │    │    │
   *      └────┴────┴────┴────┴─────────┴────┴────┴────┴────┘
   */
  [_LOWER] = LAYOUT_mit(
    KC_ESC,     KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,     KC_8,     KC_9,     KC_0,     _______,
    KC_TILD,    KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,   KC_CIRC,   KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_DQT,
    _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______,  KC_GRAVE, KC_LBRC,  KC_RBRC,  KC_DOT,
                _______,   _______,   _______,   _______,         _______,        _______,  _______,  _______,  _______
  ),

  /* Raise Layer
   * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
   * │    │    │    │    │    │    │    │    │    │    │ -  │    │
   * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
   * │CAPS│    │    │    │    │    │    │    │    │    │ _  │ \  │
   * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
   * │PrSc│    │    │    │    │    │    │    │    │ UP │    │ =  │
   * └────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┘
   *      │    │    │    │    │         │    │Left│Down│Rght│
   *      └────┴────┴────┴────┴─────────┴────┴────┴────┴────┘
   */
  [_RAISE] = LAYOUT_mit(
    _______,    _______,   _______,    _______,   _______,   _______,   _______,   _______,  _______,  _______,  KC_MINS,  _______,
    KC_CAPS,    _______,   _______,    _______,   _______,   _______,   _______,   _______,  _______,  _______,  KC_UNDS,  KC_BSLS,
    KC_PSCR,    _______,   _______,    _______,   _______,   _______,   _______,   _______,  _______,   KC_UP,   _______,  KC_EQUAL,
                 _______,   _______,    _______,   _______,         _______,       _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT
),

  /* Other Layer
   * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
   * │RSET│    │    │    │    │    │    │    │    │SAT+│Hue+│Brt+│
   * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
   * │    │    │    │    │    │    │    │    │    │SAT-│Hue-│Brt-│
   * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
   * │    │    │    │    │    │    │    │    │    │    │    │RGB!│
   * └────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┘
   *      │    │    │    │    │         │    │    │    │    │
   *      └────┴────┴────┴────┴─────────┴────┴────┴────┴────┘
   */
  [_OTHER] = LAYOUT_mit(
    TD(TD_RST), _______,   _______,    _______,   _______,   _______,   _______,   _______,  _______,  UG_SATU,  UG_HUEU,  UG_VALU,
    _______,    _______,   _______,    _______,   _______,   _______,   _______,   _______,  _______,  UG_SATD,  UG_HUED,  UG_VALD,
    _______,    _______,   _______,    _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  UG_NEXT,
                _______,   _______,    _______,   _______,         _______,        _______,  _______,  _______,  _______
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _OTHER);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _OTHER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _OTHER);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _OTHER);
      }
      return false;
      break;
  }
  return true;
};
