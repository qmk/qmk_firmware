#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER  1
#define _GAMING 2
#define _RAISE  3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  GAMING,
  RAISE,
};

/*****************/
/***   IDEAS   ***/
/*****************/
/*
 * -have a combo that allows you to switch the base layer between base & gaming layers
 * -add another symbol layer where the arrow keys are combined with ctrl
 * -add another symbol layer where the arrow keys are combined with ctrl + shift
 * -add combos that allow me to switch to ANY layer from the base layer and back quickly
 */

/*****************/
/*** TAPDANCES ***/
/*****************/
enum custom_tapdances {
   TD_SHFT_CAPS = 0,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS), //shift if pressed 1x, caps lock if pressed 2x
};

/*****************/
/***  COMBOS   ***/
/*****************/
// const uint16_t PROGMEM raiseToLayer2[] = {_______, _______, COMBO_END};
// const uint16_t PROGMEM raiseToLayer3[] = {_______, _______, COMBO_END};
// const uint16_t PROGMEM raiseToLayer4[] = {_______, _______, COMBO_END};

// const uint16_t PROGMEM lowerToLayer3[] = {_______, _______, COMBO_END};
// const uint16_t PROGMEM lowerToLayer2[] = {_______, _______, COMBO_END};
// const uint16_t PROGMEM lowerToLayer1[] = {_______, _______, COMBO_END};

// combo_t key_combos[COMBO_COUNT] = {
//     COMBO(raiseToLayer1, KC_ESC),
//     COMBO(raiseToLayer2, LCTL(KC_Z)),
// };

/*****************/
/***  KEYMAPS  ***/
/*****************/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   // layout for everyday use
  [_QWERTY] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
     TD(TD_SHFT_CAPS), KC_A,    KC_S,    KC_D,    KC_F,  KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_DEL,              KC_ENT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                        KC_RALT, KC_LGUI, KC_BSPC,         KC_SPC, TT(_LOWER), _______
  ),

  [_LOWER] = LAYOUT(
     KC_GRAVE, KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PEQL,
     KC_F11,  KC_F12,  KC_UP,  _______, _______, KC_LPRN,                            KC_RPRN,  KC_7,    KC_8,    KC_9,   KC_PSLS, KC_PAST,
     KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_LCBR,                           KC_RCBR,  KC_4,    KC_5,    KC_6,   KC_PMNS, KC_PPLS,
     KC_LCTL, _______, _______, _______, _______, KC_LBRC, KC_DEL,            KC_ENT, KC_RBRC,  KC_1,    KC_2,    KC_3,   KC_PDOT, _______,
                                       _______, TO(_QWERTY), KC_BSPC,         KC_SPC, TG(_GAMING), KC_0
  ),

  //makes gaming easier, adding a space for jumping closer to the movement keys
  [_GAMING] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
     KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_DEL,             KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                        KC_RALT, KC_SPC, KC_BSPC,           KC_SPC, TG(_RAISE), TO(_LOWER) 
  ),

  //used for editing rgb settings, sound, and misc commands
  [_RAISE] = LAYOUT(
     RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                            KC_MUTE, KC_VOLU, KC_MNXT, _______, KC_BRIU, KC_CALC,
    _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,                            KC_MSTP, KC_VOLD, KC_MPRV, _______, KC_BRID, KC_MYCM,
     DM_REC1, DM_REC2, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, KC_WSCH,
     DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______,         _______, _______, _______,  _______, _______, _______, _______,
                                       DM_RSTP, TO(_GAMING), _______,        _______, _______, _______
  )
};

//switch between layers?
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
        layer_off(_LOWER);
      }
      return false;
      break;

      case GAMING:
      if (record->event.pressed) {
        layer_on(_GAMING);
      } else {
        layer_off(_GAMING);
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
      
  }
  return true;
}

//rotary encoder function
// bool encoder_update_user(uint8_t index, bool clockwise) {
//     if (index == 0) {
//         if (clockwise) {
//             tap_code(KC_VOLU);
//         } else {
//             tap_code(KC_VOLD);
//         }
//     }
//     else if (index == 1) {
//         if (clockwise) {
//             tap_code(KC_PGDN);
//         } else {
//             tap_code(KC_PGUP);
//         }
//     }
//     return false;
// }