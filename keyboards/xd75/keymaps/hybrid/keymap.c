/* Copyright 2020 Hybrid
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H


enum layers {
    _MAIN = 0,
    _LY1,
    _LY2,
};

enum {
  TD_A,
  TD_E,
  TD_I,
  TD_O,
  TD_U,
  TD_SLASH,
  TD_UNDER,
  TD_OP_ACCOL,
  TD_CL_ACCOL,
  TD_QUESTION,
  TD_CEDILLE,
  TD_DOT,
};



void dance_a_accent (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_0);
  }
  else {
    tap_code (KC_Q);
  }
}
void dance_e_accent (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_2);
  }
  else if (state->count == 3) {
    tap_code (KC_7);
  }
  else {
    tap_code (KC_E);
  }
}
void dance_i_accent (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P2);
    tap_code (KC_P3);
    tap_code (KC_P8);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else {
    tap_code (KC_I);

  }
}
void dance_o_accent (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P2);
    tap_code (KC_P4);
    tap_code (KC_P4);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else {
    tap_code (KC_O);
  }
}
void dance_u_accent (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P2);
    tap_code (KC_P4);
    tap_code (KC_P9);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else {
    tap_code (KC_U);
  }

}
void dance_slash (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P9);
    tap_code (KC_P2);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else {
    tap_code (KC_PSLS);
  }
}
void dance_under (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P9);
    tap_code (KC_P5);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else {
    tap_code (KC_6);
  }
}
void dance_open_accol (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P1);
    tap_code (KC_P2);
    tap_code (KC_P3);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else if (state->count == 3) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P9);
    tap_code (KC_P1);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else {
    tap_code (KC_5);
  }
}
void dance_close_accol (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P1);
    tap_code (KC_P2);
    tap_code (KC_P5);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);

  }
  else if (state->count == 3) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P9);
    tap_code (KC_P3);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else {
    tap_code (KC_MINS);
  }
}
void dance_question (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P0);
    tap_code (KC_P3);
    tap_code (KC_P3);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);

  }
  else {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P0);
    tap_code (KC_P6);
    tap_code (KC_P3);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);

  }
}
void dance_cedille (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_9);
  }
  else {
    tap_code (KC_C);
  }
}
void dance_dot (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P4);
    tap_code (KC_P4);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
  else {
    tap_code (KC_NLCK);
    register_code (KC_LALT);
    tap_code (KC_P0);
    tap_code (KC_P4);
    tap_code (KC_P6);
    unregister_code (KC_LALT);
    tap_code (KC_NLCK);
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_A] = ACTION_TAP_DANCE_FN(dance_a_accent),
  [TD_E] = ACTION_TAP_DANCE_FN(dance_e_accent),
  [TD_I] = ACTION_TAP_DANCE_FN(dance_i_accent),
  [TD_O] = ACTION_TAP_DANCE_FN(dance_o_accent),
  [TD_U] = ACTION_TAP_DANCE_FN(dance_u_accent),
  [TD_SLASH] = ACTION_TAP_DANCE_FN(dance_slash),
  [TD_UNDER] = ACTION_TAP_DANCE_FN(dance_under),
  [TD_OP_ACCOL] = ACTION_TAP_DANCE_FN(dance_open_accol),
  [TD_CL_ACCOL] = ACTION_TAP_DANCE_FN(dance_close_accol),
  [TD_QUESTION] = ACTION_TAP_DANCE_FN(dance_question),
  [TD_CEDILLE] = ACTION_TAP_DANCE_FN(dance_cedille),
  [TD_DOT] = ACTION_TAP_DANCE_FN(dance_dot),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// red led layout
  [_MAIN] = LAYOUT_ortho_5x15(
    KC_ESC, KC_RBRC, KC_1, KC_2, KC_3, KC_4, KC_5, TD(TD_DOT), KC_6, KC_7, KC_8, KC_9, KC_0, DF(_LY1), KC_NO,
    KC_TAB, TD(TD_A), KC_W, TD(TD_E), KC_R, KC_T, KC_Y, KC_ENT, TD(TD_U), TD(TD_I), TD(TD_O), KC_P, KC_NO, TD(TD_OP_ACCOL), TD(TD_CL_ACCOL),
    KC_PGUP, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_ENT, KC_J, KC_K, KC_L, KC_SCLN, KC_UP, KC_NO, KC_NO,
    KC_PGDN, KC_Z, KC_X, TD(TD_CEDILLE), KC_V, KC_B, KC_N, KC_DOT, TD(TD_QUESTION), TD(TD_UNDER), TD(TD_SLASH), KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
    KC_NO, KC_NO, KC_LALT, KC_LCTL, KC_LSFT, KC_SPC, KC_HOME, KC_LGUI, KC_END, KC_BSPC, KC_RALT, KC_DEL, KC_PMNS, KC_NO, MO(1)
    ),

// green led layout
  [_LY1] = LAYOUT_ortho_5x15(
    KC_ESC, RGB_TOG, RGB_RMOD, RGB_M_P, RGB_M_B, RGB_M_SW, RGB_M_K, RGB_M_G, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, DF(_LY2), DF(_MAIN),
    DEBUG, KC_PSCR, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    RESET, KC_NO, KC_S, KC_D, KC_F, KC_G, KC_Z, KC_J, KC_K, KC_L, KC_M, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_LSFT,
    KC_NO, KC_X, KC_C, KC_V, KC_B, KC_N, KC_COMM, KC_SCLN, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PEQL, KC_LCBR,
    KC_NO, KC_NO, KC_NO, KC_SPC, KC_SPC, KC_SPC, KC_TRNS, KC_NO, KC_TRNS, KC_P0,  KC_P1, KC_P2, KC_P3, KC_TRNS
    ),

// blue led layout
  [_LY2] = LAYOUT_ortho_5x15(
    KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_NO, BL_ON, BL_OFF, KC_NO, KC_NO, KC_NO, RGB_TOG, RGB_RMOD, RGB_MOD, KC_NO, DF(_LY1),
    KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, BL_TOGG, BL_STEP, KC_NO, KC_NO, KC_NO, KC_NO, RGB_HUD, RGB_HUI, RGB_M_P, RGB_M_B,
    KC_MPLY, KC_MSTP, KC_MUTE, KC_NO, KC_NO, BL_DEC, BL_INC, KC_NO, KC_NO, KC_NO, KC_NO, RGB_SAD, RGB_SAI, RGB_M_R, RGB_M_SW,
    KC_MRWD, KC_MFFD, KC_NO, KC_NO, KC_NO, BL_BRTG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_VAD, RGB_VAI, RGB_M_SN, RGB_M_K,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, RGB_SPD, RGB_SPI, RGB_M_X, RGB_M_G
    )

};


//Define layer colors
#define rgblight_setrgb_user_MAIN()  rgblight_sethsv_red()
#define rgblight_setrgb_user_LY1()  rgblight_sethsv_green()
#define rgblight_setrgb_user_LY2() rgblight_sethsv_blue()

void matrix_init_user(void) {
  rgblight_enable();
  rgblight_mode(1);
  rgblight_setrgb_user_MAIN();
}


//Set a color based on the layer
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _LY1:
      rgblight_setrgb_user_LY1();
      break;
    case _LY2:
      rgblight_setrgb_user_LY2();
      break;
    default:
      rgblight_setrgb_user_MAIN();
      break;
  }
  return state;
}
