#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _FNMS,
};

#define FNMS MO(_FNMS)

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ( │ ) │ \ │ \ │HOM│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┼───┼───┤
 * │ TAB │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │BKSPC│PGU│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │   `  │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ ENTER  │PGD│
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │ SHIFT  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │SHIFT │UP │END│
 * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴──┬───┼───┼───┤
 * │CTRL │GUI│ ALT │      SPACE (6.25u)    │ ALT │CTRL │LFT│DWN│RGT│
 * └─────┴───┴─────┴───────────────────────┴─────┴─────┴───┴───┴───┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_65_ansi_split_bs(
    KC_GESC, KC_1,   KC_2,   KC_3,  KC_4, KC_5,  KC_6,  KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSLS, KC_HOME,
    KC_TAB,  KC_Q,   KC_W,   KC_E,  KC_R, KC_T,  KC_Y,  KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,          KC_BSPC, KC_PGUP,
    KC_GRV,  KC_A,   KC_S,   KC_D,  KC_F, KC_G,  KC_H,  KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
    KC_LSFT, KC_Z,   KC_X,   KC_C,  KC_V, KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT, KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
    KC_LCTL, KC_LGUI,KC_LALT,                    KC_SPC,                       FNMS,             KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FNMS] = LAYOUT_65_ansi_split_bs(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, KC_DEL,  KC_MPLY,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         QK_BOOT, KC_VOLU,
    AG_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          EEP_RST,         KC_VOLD,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_BTN1, KC_MS_U,KC_MNXT,
    _______, _______, _______,                            _______,                   _______,          _______,          KC_MS_L,KC_MS_D, KC_MS_R
  ),
};

// layer_state_t layer_state_set_user(layer_state_t state) {
//   switch(get_highest_layer(state)) {
//   case _FNMS:
//     led_off();
//     rgb_on();
//     break;
//   default:
//     led_off();
//     rgb_off();
//     break;
//   }
//   return state;
// }
