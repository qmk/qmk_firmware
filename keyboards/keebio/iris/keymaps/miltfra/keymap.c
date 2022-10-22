#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_LBK KC_LBRACKET
#define KC_RBK KC_RBRACKET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
      //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX,
      //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, KC_A,    KC_S,   KC_D,    KC_F,     KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, XXXXXXX,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,          XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
      //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                        KC_LCTL, LOWER,   KC_SPC,                    KC_LSFT,RAISE,   KC_LALT
      //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      ),

  [_LOWER] = LAYOUT(
      //┌────────┬───────┬────────┬────────┬────────┬─────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
      //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, KC_GRAVE,KC_EQUAL,KC_ESC,  KC_LBK,  KC_RBK,                             KC_BSLS, KC_ENT,  KC_TAB, KC_MINUS,KC_QUOT, XXXXXXX,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX,
      //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                        XXXXXXX, XXXXXXX, XXXXXXX,                   KC_LSFT, XXXXXXX, LSFT(KC_LALT)
      //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      ),

  [_RAISE] = LAYOUT(
      //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
      //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, KC_F12,  XXXXXXX, KC_BSPC, KC_DEL, XXXXXXX,                             KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_F11,  XXXXXXX,
      //├────────┼────────┼────────┼─────-──┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,LCA(KC_DEL),XXXXXXX,        XXXXXXX, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
      //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                        KC_LCTL, KC_LWIN, KC_SPC,                   XXXXXXX, XXXXXXX, XXXXXXX
      // -                             └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      ),

  [_ADJUST] = LAYOUT(
      //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
      //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
      //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
      //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
      _______, _______, _______,                   _______, _______, _______
      // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      )
};

#undef KC_LBK
#undef KC_RBK

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  }
  else if (index == 1) {
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
  }
  return true;
}
