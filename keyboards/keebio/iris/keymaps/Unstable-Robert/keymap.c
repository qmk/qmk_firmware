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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RAISE  , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    RGB_TOG,          RGB_MOD,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_PSCR,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, LOWER,   KC_SPC,                    KC_ENT,  KC_LGUI,   KC_RALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD,ROPT(KC_Y),S(KC_U),  PB_3  ,  PB_4  ,  PB_5  ,                            PB_6  ,  PB_7  ,  PB_8  ,  PB_9  ,  PB_10 , KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_U  , _______,  KC_PGUP, _______, _______, KC_LBRC,                           KC_RBRC,  KC_P7,  KC_P8  ,  KC_P9 , KC_PPLS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_HOME, KC_PGDN, KC_END,  KC_K ,   S(KC_9),                           S(KC_0), KC_P4,   KC_P5,   KC_P6,   KC_MINS, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______,  KC_PSLS,LOPT(KC_X),LOPT(KC_C),KC_N,S(KC_LBRC),_______,         _______,S(KC_RCBR), KC_P1,   KC_P2,   KC_P3,  KC_EQL, KC_P0,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, _______, _______,                    KC_PENT, _______, KC_RALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_Y  , _______, KC_UP,   _______, _______,   KC_H  ,                          _______, _______, KC_NUM, KC_INS,  KC_SCRL, KC_MUTE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT,  KC_I  ,SWIN(KC_S),                          _______,  _______, RGB_HUI, RGB_SAI, _______,_______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______,LOPT(KC_L),LOPT(KC_G),KC_M,_______,          _______, _______, _______,  RGB_HUD, RGB_SAD,_______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, _______, A(KC_INS),                C(KC_SPC), _______, KC_RALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
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

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        /* Left Hand */                                                     /* Right Hand */
        /* Switch between tabs. (Control + Tab). */                         /* Switch between open apps on Mac. (Command + Tab + timer logic) */
        [_QWERTY] = {
                        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
                        ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN)
                    },
        /* Scrolls left & right. (Shift + Mouse Wheel Up). */               /* Scrolls up and down. (Page Down & Page Up - mouse wheel scroll incraments are too small) */
        [_LOWER] =  {
                        ENCODER_CCW_CW(RGB_HUI, RGB_HUD),ENCODER_CCW_CW(RGB_HUI, RGB_HUD),
                        ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)
                    },
        /* Selects adjacent words. (Command + Shift + Right Arrow). */      /* Jumps to end/start of line. Hold shift to select. (Gui + arrow). */
        [_RAISE] =  {
                        ENCODER_CCW_CW(RGB_SAI, RGB_SAD),ENCODER_CCW_CW(RGB_SAI, RGB_SAD),
                        ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)
                    },
        /* Scroll through RGB Modes */                                      /* Right & left arrow */
        [_ADJUST] = {
                        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
                        ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_UP, KC_DOWN)
                    },
    };
#endif
