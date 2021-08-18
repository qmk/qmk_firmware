/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _ARROWS 1
#define _SYMBOLS 2
#define _FUNPAD 3
#define _NUMPAD 4
#define _META 5
#define _MACRO 6

/*****************************
* Tap Dance Begin
*****************************/

// enum tap_dance_codes {
//   TD_W,
//   TD_R,
//   TD_T,
//   TD_A,
//   TD_S,
//   TD_D,
//   TD_F,
//   TD_G,
//   TD_Z,
//   TD_X,
//   TD_C,
//   TD_V,
//   TD_B,

//   TD_Y,
//   TD_P,
//   TD_K,
//   TD_COMM,
//   TD_DOT,
//   TD_SLSH,
// };

/*****************************
* Tap Dance End
*****************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                         ,-----------------------------------------------------.
LT(_MACRO, KC_ESC),  KC_Q,    KC_W,   KC_E,  KC_R,  KC_T,                                                           KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINUS,
  //|--------+--------+--------+--------+--------+--------|                                                         |--------+--------+--------+--------+--------+--------|
      OSM(MOD_LSFT),  KC_A, KC_S, KC_D, LT(_NUMPAD, KC_F), KC_G,                                                    KC_H,    LT(_MACRO, KC_J), KC_K, KC_L, KC_SCLN, OSM(MOD_RSFT),
  //|--------+--------+--------+--------+--------+--------|                                                         |--------+--------+--------+--------+--------+--------|
      KC_CAPSLOCK, KC_Z, KC_X, LGUI_T(KC_C), KC_V, KC_B,                                                KC_N,   KC_M, RGUI_T(KC_COMM),  KC_DOT, KC_SLSH,  KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|                                                |--------+--------+--------+--------+--------+--------+--------|
                                LT(_FUNPAD, KC_DEL), LCTL_T(KC_TAB), LT(_ARROWS, KC_ENT),                    LT(_SYMBOLS, KC_SPC), RCTL_T(KC_BSPC), LT(_META, KC_QUOT)
                                      //`--------------------------'                                                `--------------------------'

  ),

  [_ARROWS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                                                            _______, KC_HOME, KC_UP, KC_END, KC_LCBR, KC_LABK,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL,    KC_LSFT,   KC_LALT,   KC_LGUI, _______,                                                     _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_RCBR, KC_RABK,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, KC_1,   KC_2,     KC_3,    _______,                                                          _______, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_LBRACKET, KC_RBRACKET, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      KC_TILDE, KC_GRAVE,    KC_PERCENT,  KC_PIPE,   KC_AMPR, KC_EQUAL,                                                  _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_EXCLAIM,    KC_AT,  KC_HASH,   KC_DOLLAR, KC_RABK,                                                    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_CIRC,    KC_ASTR,  KC_UNDERSCORE,   KC_PLUS, KC_MINUS,                                                _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_FUNPAD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______,  _______, _______, _______, _______,                                                            _______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                                                            _______, KC_F4, KC_F5, KC_F6, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      RGB_RMOD, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,                                                             _______, KC_F1, KC_F2, KC_F3, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_NUMPAD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      RESET, _______, _______, _______, _______, _______,                                                            _______, KC_7, KC_8, KC_9, SGUI(KC_S), _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                                            _______, KC_4, KC_5, KC_6, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                                            _______, KC_1, KC_2, KC_3, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          KC_MINUS, KC_KP_0, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_META] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, KC_BRIU,                                                             _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID,                                                             _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, KC_VOLD, KC_VOLU, _______,                                                             _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_MACRO] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                                                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, DM_REC1, DM_RSTP, DM_PLY1, _______,                                                            _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, DM_REC2, DM_RSTP, DM_PLY2, _______,                                                           RGB_RMOD, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),
};

/*****************************
* Tap Dance Begin
*****************************/

// extern bool g_suspend_state;

// typedef struct {
//     bool is_press_action;
//     uint8_t step;
// } tap;

// enum {
//     SINGLE_TAP = 1,
//     SINGLE_HOLD,
//     MORE_TAPS
// };

// static tap dance_state = {
//     .is_press_action = true,
//     .step = 0
// };

// void on_dance_w(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_w_dance_step(qk_tap_dance_state_t *state);
// void dance_w_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_w_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_w(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_W);
//         tap_code16(KC_W);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_W);
//     }
// }

// uint8_t dance_w_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_w_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_w_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_W); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_W)); break;
//     }
// }

// void dance_w_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_W); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_W)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_r(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_r_dance_step(qk_tap_dance_state_t *state);
// void dance_r_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_r_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_r(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_R);
//         tap_code16(KC_R);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_R);
//     }
// }

// uint8_t dance_r_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_r_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_r_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_R); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_R)); break;
//     }
// }

// void dance_r_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_R); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_R)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_t(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_t_dance_step(qk_tap_dance_state_t *state);
// void dance_t_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_t_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_t(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_T);
//         tap_code16(KC_T);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_T);
//     }
// }

// uint8_t dance_t_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_t_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_t_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_T); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_T)); break;
//     }
// }

// void dance_t_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_T); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_T)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_a(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_a_dance_step(qk_tap_dance_state_t *state);
// void dance_a_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_a_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_a(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_A);
//         tap_code16(KC_A);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_A);
//     }
// }

// uint8_t dance_a_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_a_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_a_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_A); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_A)); break;
//     }
// }

// void dance_a_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_A); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_A)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_s(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_s_dance_step(qk_tap_dance_state_t *state);
// void dance_s_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_s_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_s(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_S);
//         tap_code16(KC_S);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_S);
//     }
// }

// uint8_t dance_s_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_s_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_s_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_S); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_S)); break;
//     }
// }

// void dance_s_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_S); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_S)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_d(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_d_dance_step(qk_tap_dance_state_t *state);
// void dance_d_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_d_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_d(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_D);
//         tap_code16(KC_D);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_D);
//     }
// }

// uint8_t dance_d_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_d_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_d_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_D); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_D)); break;
//     }
// }

// void dance_d_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_D); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_D)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_f(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_f_dance_step(qk_tap_dance_state_t *state);
// void dance_f_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_f_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_f(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_F);
//         tap_code16(KC_F);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_F);
//     }
// }

// uint8_t dance_f_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_f_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_f_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_F); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_F)); break;
//     }
// }

// void dance_f_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_F); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_F)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_g(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_g_dance_step(qk_tap_dance_state_t *state);
// void dance_g_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_g_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_g(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_G);
//         tap_code16(KC_G);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_G);
//     }
// }

// uint8_t dance_g_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_g_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_g_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_G); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_G)); break;
//     }
// }

// void dance_g_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_G); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_G)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_z(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_z_dance_step(qk_tap_dance_state_t *state);
// void dance_z_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_z_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_z(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_Z);
//         tap_code16(KC_Z);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_Z);
//     }
// }

// uint8_t dance_z_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_z_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_z_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_Z); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_Z)); break;
//     }
// }

// void dance_z_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_Z); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_Z)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_x(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_x_dance_step(qk_tap_dance_state_t *state);
// void dance_x_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_x_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_x(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_X);
//         tap_code16(KC_X);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_X);
//     }
// }

// uint8_t dance_x_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_x_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_x_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_X); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_X)); break;
//     }
// }

// void dance_x_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_X); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_X)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_c(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_c_dance_step(qk_tap_dance_state_t *state);
// void dance_c_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_c_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_c(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_C);
//         tap_code16(KC_C);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_C);
//     }
// }

// uint8_t dance_c_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_c_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_c_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_C); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_C)); break;
//     }
// }

// void dance_c_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_C); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_C)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_v(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_v_dance_step(qk_tap_dance_state_t *state);
// void dance_v_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_v_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_v(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_V);
//         tap_code16(KC_V);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_V);
//     }
// }

// uint8_t dance_v_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_v_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_v_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_V); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_V)); break;
//     }
// }

// void dance_v_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_V); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_V)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_b(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_b_dance_step(qk_tap_dance_state_t *state);
// void dance_b_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_b_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_b(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_B);
//         tap_code16(KC_B);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_B);
//     }
// }

// uint8_t dance_b_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_b_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_b_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_B); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_B)); break;
//     }
// }

// void dance_b_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_B); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_B)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_y(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_y_dance_step(qk_tap_dance_state_t *state);
// void dance_y_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_y_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_y(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_Y);
//         tap_code16(KC_Y);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_Y);
//     }
// }

// uint8_t dance_y_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_y_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_y_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_Y); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_Y)); break;
//     }
// }

// void dance_y_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_Y); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_Y)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_p(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_p_dance_step(qk_tap_dance_state_t *state);
// void dance_p_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_p_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_p(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_P);
//         tap_code16(KC_P);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_P);
//     }
// }

// uint8_t dance_p_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_p_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_p_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_P); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_P)); break;
//     }
// }

// void dance_p_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_P); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_P)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_k(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_k_dance_step(qk_tap_dance_state_t *state);
// void dance_k_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_k_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_k(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_K);
//         tap_code16(KC_K);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_K);
//     }
// }

// uint8_t dance_k_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_k_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_k_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_K); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_K)); break;
//     }
// }

// void dance_k_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_K); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_K)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_comma(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_comma_dance_step(qk_tap_dance_state_t *state);
// void dance_comma_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_comma_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_comma(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_COMM);
//         tap_code16(KC_COMM);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_COMM);
//     }
// }

// uint8_t dance_comma_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_comma_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_comma_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_COMM); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_COMM)); break;
//     }
// }

// void dance_comma_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_COMM); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_COMM)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_dot(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_dot_dance_step(qk_tap_dance_state_t *state);
// void dance_dot_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_dot_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_dot(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_DOT);
//         tap_code16(KC_DOT);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_DOT);
//     }
// }

// uint8_t dance_dot_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_dot_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_dot_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_DOT); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_DOT)); break;
//     }
// }

// void dance_dot_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_DOT); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_DOT)); break;
//     }
//     dance_state.step = 0;
// }

// void on_dance_slash(qk_tap_dance_state_t *state, void *user_data);
// uint8_t dance_slash_dance_step(qk_tap_dance_state_t *state);
// void dance_slash_finished(qk_tap_dance_state_t *state, void *user_data);
// void dance_slash_reset(qk_tap_dance_state_t *state, void *user_data);

// void on_dance_slash(qk_tap_dance_state_t *state, void *user_data) {
//     if(state->count == 2) {
//         tap_code16(KC_SLSH);
//         tap_code16(KC_SLSH);
//     }
//     if(state->count > 2) {
//         tap_code16(KC_SLSH);
//     }
// }

// uint8_t dance_slash_dance_step(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     } 
//     return MORE_TAPS;
// }
// void dance_slash_finished(qk_tap_dance_state_t *state, void *user_data) {
//     dance_state.step = dance_slash_dance_step(state);
//     switch (dance_state.step) {
//         case SINGLE_TAP: register_code16(KC_SLSH); break;
//         case SINGLE_HOLD: register_code16(LCTL(KC_SLSH)); break;
//     }
// }

// void dance_slash_reset(qk_tap_dance_state_t *state, void *user_data) {
//     wait_ms(10);
//     switch (dance_state.step) {
//         case SINGLE_TAP: unregister_code16(KC_SLSH); break;
//         case SINGLE_HOLD: unregister_code16(LCTL(KC_SLSH)); break;
//     }
//     dance_state.step = 0;
// }

// qk_tap_dance_action_t tap_dance_actions[] = {
//         [TD_W] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_w, dance_w_finished, dance_w_reset),
//         [TD_R] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_r, dance_r_finished, dance_r_reset),
//         [TD_T] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_t, dance_t_finished, dance_t_reset),
//         [TD_A] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_a, dance_a_finished, dance_a_reset),
//         [TD_S] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_s, dance_s_finished, dance_s_reset),
//         [TD_D] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_d, dance_d_finished, dance_d_reset),
//         [TD_F] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_f, dance_f_finished, dance_f_reset),
//         [TD_G] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_g, dance_g_finished, dance_g_reset),
//         [TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_z, dance_z_finished, dance_z_reset),
//         [TD_X] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_x, dance_x_finished, dance_x_reset),
//         [TD_C] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_c, dance_c_finished, dance_c_reset),
//         [TD_V] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_v, dance_v_finished, dance_v_reset),
//         [TD_B] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_b, dance_b_finished, dance_b_reset),
//         [TD_Y] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_y, dance_y_finished, dance_y_reset),
//         [TD_P] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_p, dance_p_finished, dance_p_reset),
//         [TD_K] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_k, dance_k_finished, dance_k_reset),
//         [TD_COMM] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_comma, dance_comma_finished, dance_comma_reset),
//         [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_dot, dance_dot_finished, dance_dot_reset),
//         [TD_SLSH] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_slash, dance_slash_finished, dance_slash_reset),
// };

/*****************************
* Tap Dance End
*****************************/

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Do work, son"), false);
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
      switch (keycode) {
         case LT(_ARROWS, KC_ENT):
         case LT(_NUMPAD, KC_F):
         case LT(_MACRO, KC_J):
         case RGUI_T(KC_COMM):
         case LT(_SYMBOLS, KC_SPC):
         case RCTL_T(KC_BSPC):
         case LT(_META, KC_QUOT):
         case LGUI_T(KC_C):
         case LCTL_T(KC_TAB):
            return true;
         default:
            return false;
      }
}