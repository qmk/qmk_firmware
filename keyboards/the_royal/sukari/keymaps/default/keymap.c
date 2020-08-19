#include QMK_KEYBOARD_H

// START - Layer & Basic Declarations ----------
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _OTHER,
    _GAME
};



// START - Tap Dance Declarations ----------
enum {
  TD_RST = 0
};

void dance_rst_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

//All tap dance functions would go here.
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_RST] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, NULL, dance_rst_reset)
};


#ifdef DIP_SWITCH_ENABLE
// DIP Switch Configurations
void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: { // DIP PIN #1 - If in "ON" Position:
            if (active) {
                layer_on(_GAME);
            } else {
                layer_off(_GAME);
            }
            break;
        }
        case 1: { // DIP PIN #2 - If in "ON" Position:
            if (active) {
              keymap_config.capslock_to_control = true;
            } else {
              keymap_config.capslock_to_control = false;
            }
            break;
        }
    }
}
#endif


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define OTHER MO(_OTHER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default Layer
     * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
     * │ESC │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │ -  │
     * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
     * │TAB │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │BKSP│
     * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
     * │CAPS│ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │ '  │
     * ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
     * │LSFT│ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │ENTR│
     * ├────┼────┴──┬─┴────┴────┴────┴────┴────┴────┴─┬──┴────┼────┤
     * │LCTL│ LGUI  │   Tap = SPACE // Hold = LOWER   │ RAISE │OTHR│
     * └────┴───────┴─────────────────────────────────┴───────┴────┘
     */

[_QWERTY] = LAYOUT_true(
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,     KC_0,      KC_MINUS,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,      KC_BSPC,
    KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,   KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,   KC_ENTER,
    KC_LCTL,      KC_LALT,                      LT(_LOWER, KC_SPACE),                        RAISE,         OTHER
),


[_LOWER] = LAYOUT_true(
    KC_GRAVE,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_TILD,
    KC_TILD,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      _______,
    _______,    KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN,   KC_DQT,
    _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,          _______,                                    _______,                                    _______,        _______
),


[_RAISE] = LAYOUT_true(
    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,
    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
    KC_CAPS,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_LCBR,   KC_RCBR,   KC_PIPE,   KC_PLUS,
    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_LBRC,   KC_RBRC,   KC_BSLS,   KC_EQUAL,
    _______,         _______,                                    _______,                                    _______,        _______
),


[_OTHER] = LAYOUT_true(
    TD(TD_RST),   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,
    _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,
    _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_UP,     _______,    _______,
    _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_LEFT,   KC_DOWN,   KC_RIGHT,   _______,
    KC_PSCR,            KC_LGUI,                                    _______,                                    _______,         _______
),


[_GAME] = LAYOUT_true(
    KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,      KC_9,     KC_0,      KC_MINUS,
    KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,      KC_O,     KC_P,      KC_BSPC,
    KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,      KC_L,     KC_SCLN,   KC_QUOT,
    KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT,   KC_SLSH,   KC_ENTER,
    KC_DEL,       KC_LALT,                       KC_SPACE,                             KC_LEFT,        KC_RIGHT
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
void keyboard_post_init_user(void) {
    layer_state_set_user(0);
}

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
    case _GAME:
        rgblight_setrgb (RGB_PURPLE);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (RGB_CORAL);
        break;
    }
  return state;
}
#endif
