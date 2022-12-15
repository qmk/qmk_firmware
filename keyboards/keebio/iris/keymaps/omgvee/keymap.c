#include QMK_KEYBOARD_H
#include <print.h>

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MOUSE 3
#define _ADJUST 4
#define _HWCT 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MOUSE,
  ADJUST,
  HWCT,
};

#define KC_MOUS TT(_MOUSE) // double tab toggle mouse layer
#define KC_HWCT TT(_HWCT) // double tab toggle hardware control layer
#define MS_L KC_MS_LEFT
#define MS_R KC_MS_RIGHT
#define MS_U KC_MS_UP 
#define MS_D KC_MS_DOWN 
#define MS_B1 KC_MS_BTN1 
#define MS_B2 KC_MS_BTN2
#define MW_U KC_MS_WH_UP 
#define MW_D KC_MS_WH_DOWN 
#define MW_L KC_MS_WH_LEFT 
#define MW_R KC_MS_WH_RIGHT

//// only uncomment the below line when you enable leader key in rules.mk
//LEADER_EXTERNS();

//Tap Dance Declarations
enum {
  TD_SCL = 0
};
//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Shift, twice for Caps Lock
  [TD_SCL]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};
enum {
  TD_EBT = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MOUS,          KC_HWCT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,TD(TD_SCL),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI,  LOWER,   KC_ENT,                    KC_SPC,  RAISE,   KC_LALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  _______, _______, _______, _______, _______,                            _______, _______, _______, KC_MINS, KC_EQL,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,                            _______, KC_HOME, KC_END,  KC_LBRC, KC_RBRC, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, _______, _______, KC_LT,   KC_LCBR, KC_LBRC, KC_LPRN,          KC_RPRN, KC_RBRC, KC_RCBR, KC_GT,   _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                    KC_DEL, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
 
  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, KC_PGUP, _______,                            _______, _______, _______, _______, _______, KC_INS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, KC_PGDN, _______,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_MENU, KC_PENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, KC_MINS, KC_F11,           KC_F12,  KC_MINS, KC_EQL,  KC_VOLD, KC_VOLU, KC_PSCR, KC_EJCT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, MS_B1,   MS_U,    MS_B2,   MW_U,    _______,                            _______, MS_B1,   MS_B2,   _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, MS_L,    MS_D,    MS_R,    MW_D,    _______,                            MS_L,    MS_D   , MS_U,    MS_R    ,_______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, MW_L,    MW_R,    _______, _______,          _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     BL_BRTG, _______, _______, _______, DB_TOGG, QK_BOOT,                            QK_BOOT, DB_TOGG, _______, RGB_HUI, RGB_SAI, RGB_VAI,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      BL_UP,  _______, _______, _______, _______, EE_CLR,                             EE_CLR,  _______, _______, RGB_HUD, RGB_SAD, RGB_VAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      BL_DOWN,KC_MPRV, KC_MNXT, KC_MFFD, KC_MRWD, KC_MPLY,                            KC_MPRV, KC_MNXT, KC_MFFD, KC_MRWD, KC_MPLY, RGB_MOD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BL_TOGG, _______, _______, _______, _______, _______, _______,          _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, RGB_TOG,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_HWCT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     BL_BRTG, _______, _______, _______, _______,   QK_BOOT,                            QK_BOOT, _______, _______, RGB_HUI, RGB_SAI, RGB_VAI,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      BL_UP,  _______, _______, _______, _______, _______,                            _______, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      BL_DOWN,KC_MPRV, KC_MNXT, KC_MFFD, KC_MRWD, KC_MPLY,                            KC_MPRV, KC_MNXT, KC_MFFD, KC_MRWD, KC_MPLY, RGB_MOD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BL_TOGG, _______, _______, _______, _______, _______, KC_EJCT,          _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, RGB_TOG,
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
        dprintf("Got on layer %s ", LOWER);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      } else {
        layer_off(_LOWER);
        dprintf("Got off layer %s ", LOWER);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        dprintf("Got on layer %s ", RAISE);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      } else {
        layer_off(_RAISE);
        dprintf("Got off layer %s ", RAISE);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
        dprintf("Got on layer %s ", MOUSE);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      } else {
        layer_off(_MOUSE);
        dprintf("Got off layer %s ", MOUSE);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      }
      return false;
      break;
    case HWCT:
      if (record->event.pressed) {
        layer_on(_HWCT);
        dprintf("Got on layer %s ", HWCT);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      } else {
        layer_off(_HWCT);
        dprintf("Got off layer %s ", HWCT);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
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
