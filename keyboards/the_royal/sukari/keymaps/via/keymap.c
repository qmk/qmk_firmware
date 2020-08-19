#include QMK_KEYBOARD_H

// START - Layer & Basic Declarations ----------
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _OTHER
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define OTHER MO(_OTHER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* VIA
     * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
     * │Tab │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │ -  │
     * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
     * │Tab │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │BkSp│
     * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
     * │LCtl│ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │ '  │
     * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
     * │LSft│ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │Entr│
     * ├────┼────┴──┬─┴────┴────┴────┴────┴────┴────┴─┬──┴────┼────┤
     * │Del │ LGui  │             "SPACE"             │ Raise │Lowr│
     * └────┴───────┴─────────────────────────────────┴───────┴────┘
     */

[_QWERTY] = LAYOUT_true(
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,     KC_0,      KC_MINUS,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,      KC_BSPC,
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,   KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,   KC_ENT,
    KC_DEL,      KC_LALT,                            KC_SPACE,                               RAISE,         LOWER
),



[_LOWER] = LAYOUT_true(
    KC_GRAVE,   KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_PIPE,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_UP,      _______,    KC_DQT,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   _______,
    _______,          _______,                                        _______,                                        _______,          _______
),



[_RAISE] = LAYOUT_true(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_TILD,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_LCBR,    KC_RCBR,    _______,    KC_PLUS,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_EQUAL,
    _______,           _______,                                      _______,                                         _______,          _______
),



[_OTHER] = LAYOUT_true(
    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    KC_CAPS,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    KC_PSCR,          KC_LGUI,                                        _______,                                        _______,          _______
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

#ifdef RGBLIGHT_ENABLE
// START - RGB Indicator LED Declarations ----------
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        rgblight_setrgb (RGB_GREEN);
        break;
    case _RAISE:
        rgblight_setrgb (RGB_CYAN);
        break;
    case _OTHER:
        rgblight_setrgb (RGB_RED);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (RGB_WHITE);
        break;
    }
  return state;
}
#endif
