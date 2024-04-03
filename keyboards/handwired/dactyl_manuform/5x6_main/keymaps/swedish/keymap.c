/* A Swedish XMonad layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

// typedef struct {
//   bool is_press_action;
//   int state;
// } tap;

// enum {
//   SINGLE_TAP = 1,
//   SINGLE_HOLD = 2,
//   DOUBLE_TAP = 3
// };

enum dactyl_layers {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _MOUSE
};

// // Tap Dance declarations
// enum {
//   TD_GUIS = 0,
//   TD_CEPS,
//   TD_LEFT,
//   TD_RGHT,
//   TD_MUS
// };

#define RAISE  MO(_RAISE)
#define LOWER  MO(_LOWER)
#define TGLOW TG(_LOWER)
#define WINTAB LGUI(KC_TAB)
#define LEFTCTR_1 LCTL(KC_LEFT)
#define RGHTCTR_1 LCTL(KC_RIGHT)
#define LEFTCTR_2 LSFT(LCTL(KC_LEFT))
#define RGHTCTR_2 LSFT(LCTL(KC_RIGHT))

// //Function associated with all tap dances
// int cur_dance (tap_dance_state_t *state);

// //Functions associated with individual tap dances
// void ql_finished (tap_dance_state_t *state, void *user_data);
// void ql_reset (tap_dance_state_t *state, void *user_data);

// void left_finished (tap_dance_state_t *state, void *user_data);
// void left_reset (tap_dance_state_t *state, void *user_data);

// void right_finished (tap_dance_state_t *state, void *user_data);
// void right_reset (tap_dance_state_t *state, void *user_data);

// tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for WinTab, twice for Ctrl WinTab
//     [TD_GUIS] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, WINTAB),
//     [TD_CEPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
//     [TD_RGHT] = ACTION_TAP_DANCE_DOUBLE(RGHTCTR_1, RGHTCTR_2),
//     [TD_MUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),
//     [TD_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_finished, left_reset),
//     [TD_RGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_finished, right_reset)
// };

// #define TD_GUI TD(TD_GUIS)
// #define TD_EPS TD(TD_CEPS)
// #define TD_LFT TD(TD_LEFT)
// #define TD_RGT TD(TD_RGHT)
// #define TD_MSE TD(TD_MUS)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT(
     _______ , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , SE_QUOT,
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,
     KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                          KC_H   , KC_J   , KC_K   , KC_L   , SE_ODIA, SE_ADIA,
     KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                                          KC_N   , KC_M   , KC_COMM, KC_DOT , _______, SE_MINS,
                       _______, KC_BSPC, RAISE  , KC_SPC , _______  , _______ ,     TGLOW  , KC_BSPC, KC_ENT , LOWER  , SE_PLUS, SE_EQL,                             
                                         KC_HOME, KC_END ,                                         KC_LALT, KC_LSFT
  ),
  
  [_LOWER] = LAYOUT(
     KC_GRV , KC_EXLM,  SE_AT , KC_HASH, SE_DLR , KC_PERC,                                          SE_CIRC, SE_AMPR, SE_ASTR, SE_SLSH, SE_LPRN, SE_RPRN,
     SE_TILD, _______, _______, _______, _______, _______,                                          _______, KC_7   , KC_8   , KC_9   , SE_LCBR, SE_RCBR,
     KC_TILD, _______, _______, _______, _______, _______,                                          _______, KC_4   , KC_5   , KC_6   , SE_LBRC, SE_RBRC,
     _______, _______, _______, _______, _______, _______,                                          _______, KC_1   , KC_2   , KC_3   , SE_LABK, SE_RABK,
                       _______, _______, _______, _______, _______, _______,      _______, KC_DEL , _______, _______, KC_0   , KC_CALC,
                                         KC_PGUP, KC_PGDN,                                          KC_DOT , KC_COMM
  ),

  [_RAISE] = LAYOUT(
     KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                          KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
     KC_ENT , _______, KC_UP  , _______, _______, _______,                                          QK_BOOT, _______, _______, _______, KC_MUTE, SE_PIPE,
     _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                                          _______, _______, _______, _______, KC_VOLU, SE_BSLS,
     _______, _______, _______, _______, _______, _______,                                          _______, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, _______,
                       _______, KC_DEL , _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
                                         _______ ,  _______,                                          _______, _______
  ),

  [_MOUSE] = LAYOUT(
     _______, KC_BTN4, KC_BTN5, _______, _______, _______,                                          _______, _______, _______, _______, _______, _______,
     _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______,                                          _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______,
     _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,                                          _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,
     _______, _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
                                         _______, _______,                                          _______, _______
  ),
};

// //Determine the current tap dance state
// int cur_dance (tap_dance_state_t *state) {
//   if (state->count == 1) {
//     if (!state->pressed) {
//       return SINGLE_TAP;
//     } else {
//       return SINGLE_HOLD;
//     }
//   } else if (state->count == 2) {
//     return DOUBLE_TAP;
//   }
//   else return 8;
// }

// //Initialize tap structure associated with example tap dance key
// static tap ql_tap_state = {
//   .is_press_action = true,
//   .state = 0
// };

// static tap left_tap_state = {
//     .is_press_action = true,
//     .state           = 0
// };

// static tap right_tap_state = {
//     .is_press_action = true,
//     .state           = 0
// };

// //Functions that control what our tap dance key does
// void ql_finished (tap_dance_state_t *state, void *user_data) {
//   ql_tap_state.state = cur_dance(state);
//   switch (ql_tap_state.state) {
//     case SINGLE_TAP: 
//       //check to see if the layer is already set
//       if (layer_state_is(_MOUSE)) {
//         //if already set, then switch it off
//         layer_off(_MOUSE);
//       } else { 
//         //if not already set, then switch the layer on
//         layer_on(_MOUSE);
//       } 
//       break;
//     case SINGLE_HOLD: 
//       register_code(KC_LALT);
//       break;
//     case DOUBLE_TAP:
//       tap_code(KC_A);
//       break;
//   }
// }

// void ql_reset (tap_dance_state_t *state, void *user_data) {
//   //if the key was held down and now is released then switch off the layer
//   if (ql_tap_state.state==SINGLE_HOLD) {
//     unregister_code(KC_LALT);
//   }
//   ql_tap_state.state = 0;
// }

// void left_finished (tap_dance_state_t *state, void *user_data) {
//   left_tap_state.state = cur_dance(state);
//   switch (left_tap_state.state) {
//     case SINGLE_TAP: 
//       register_code(KC_LCTL);
//       register_code(KC_LEFT);
//       break;
//     case SINGLE_HOLD:
//       register_code(KC_LSFT);
//       register_code(KC_LCTL);
//       register_code(KC_LEFT);
//       break;
//   }
// }

// void left_reset (tap_dance_state_t *state, void *user_data) {
//   //if the key was held down and now is released then switch off the layer
//   switch (left_tap_state.state) {
//     case SINGLE_TAP:
//       unregister_code(KC_LCTL);
//       unregister_code(KC_LEFT);
//       break;
//     case SINGLE_HOLD:
//       unregister_code(KC_LSFT);
//       unregister_code(KC_LCTL);
//       unregister_code(KC_LEFT);
//       break;
//   }
//   left_tap_state.state = 0;
// }

// void right_finished (tap_dance_state_t *state, void *user_data) {
//   right_tap_state.state = cur_dance(state);
//   switch (right_tap_state.state) {
//     case SINGLE_TAP: 
//       register_code(KC_LCTL);
//       register_code(KC_RGHT);
//       break;
//     case SINGLE_HOLD:
//       register_code(KC_LSFT);
//       register_code(KC_LCTL);
//       register_code(KC_RGHT);
//       break;
//   }
// }

// void right_reset (tap_dance_state_t *state, void *user_data) {
//   //if the key was held down and now is released then switch off the layer
//   switch (right_tap_state.state) {
//     case SINGLE_TAP:
//       unregister_code(KC_LCTL);
//       unregister_code(KC_RGHT);
//       break;
//     case SINGLE_HOLD:
//       unregister_code(KC_LSFT);
//       unregister_code(KC_LCTL);
//       unregister_code(KC_RGHT);
//       break;
//   }
//   right_tap_state.state = 0;
// }



// #ifdef POINTING_DEVICE_ENABLE
// #include "analog.h"
// #include "pointing_device.h"

// int xPin = B4; // VRx
// int yPin = B5; // VRy
// int swPin = C4; // SW

// // Set Parameters
// // uint16_t minAxisValue = 200;
// // uint16_t maxAxisValue = 820;
// uint16_t minAxisValue = 0;
// uint16_t maxAxisValue = 1023;

// // uint8_t maxCursorSpeed = 2;
// // uint8_t precisionSpeed = 1;
// // uint8_t speedRegulator = 24;  // Lower Values Create Faster Movement
// uint8_t maxCursorSpeed = 4;
// uint8_t precisionSpeed = 1;
// uint8_t speedRegulator = 20;  // Lower Values Create Faster Movement

// int8_t xPolarity = -1;
// int8_t yPolarity = -1;

// uint8_t cursorTimeout = 5;

// int16_t xOrigin, yOrigin;

// uint16_t lastCursor = 0;

// int16_t axisCoordinate(uint8_t pin, uint16_t origin) {
//     int8_t  direction;
//     int16_t distanceFromOrigin;
//     int16_t range;

//     int16_t position = analogReadPin(pin);

//     if (origin == position) {
//         return 0;
//     } else if (origin > position) {
//         distanceFromOrigin = origin - position;
//         range              = origin - minAxisValue;
//         direction          = -1;
//     } else {
//         distanceFromOrigin = position - origin;
//         range              = maxAxisValue - origin;
//         direction          = 1;
//     }

//     float   percent    = (float)distanceFromOrigin / range;
//     int16_t coordinate = (int16_t)(percent * 100);
//     if (coordinate < 0) {
//         return 0;
//     } else if (coordinate > 100) {
//         return 100 * direction;
//     } else {
//         return coordinate * direction;
//     }
// }

// // int8_t axisToMouseComponent(uint8_t pin, int16_t origin, uint8_t maxSpeed, int8_t polarity) {
// //     int coordinate = axisCoordinate(pin, origin);
// //     if (coordinate != 0) {
// //         float percent = (float)coordinate / 100;
// //         if (get_mods() & MOD_BIT(KC_LSFT)) {
// //             return percent * precisionSpeed * polarity * (abs(coordinate) / speedRegulator);
// //         } else {
// //             return percent * maxCursorSpeed * polarity * (abs(coordinate) / speedRegulator);
// //         }
// //     } else {
// //         return 0;
// //     }
// // }
// int axisToMouseComponent(int pin, int origin, int maxSpeed, int polarity) {
//   int coordinate = axisCoordinate(pin, origin);
//   if (coordinate == 0) {
//     return 0;
//   }
//   else {
//     float percent = (float)coordinate / 100;
//     if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
//       return percent * precisionSpeed * polarity * (abs(coordinate)/speedRegulator);
//     }
//     else {
//       return percent * maxCursorSpeed * polarity * (abs(coordinate)/speedRegulator);
//     }
//   }
// }

// void pointing_device_init(void) {
//     // init pin? Is needed?
//     // setPinInputHigh(E6);
//     // Account for drift
//     xOrigin = analogReadPin(xPin);
//     yOrigin = analogReadPin(yPin);
// }

// void pointing_device_task(void) {
//     report_mouse_t report = pointing_device_get_report();

//     // todo read as one vector
//     if (timer_elapsed(lastCursor) > cursorTimeout) {
//         lastCursor = timer_read();
//         report.x   = axisToMouseComponent(xPin, xOrigin, maxCursorSpeed, xPolarity);
//         report.y   = axisToMouseComponent(yPin, yOrigin, maxCursorSpeed, yPolarity);
//     }

//     //
// /*
//     if (!readPin(E6)) {
//         report.buttons |= MOUSE_BTN1;
//     } else {
//         report.buttons &= ~MOUSE_BTN1;
//     }
// */

//     pointing_device_set_report(report);
//     pointing_device_send();
// }

// #endif