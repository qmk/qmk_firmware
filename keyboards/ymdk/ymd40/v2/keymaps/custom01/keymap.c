/* Copyright 2021 James Young (@noroadsleft)
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

void led_set_user(uint8_t usb_led) {
  if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
    tap_code(KC_NLCK);
  }
}

// FUNCIONES TAP DANCE
void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_N);
    } else {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_N));
        clear_keyboard();
    }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_N);
    }
}

//NOMBRES TAP DANCE
enum {
    TD_ENE,
    TD_SIFT_CAPSLOCK
};

// Tap Dance DEFINICIONES
qk_tap_dance_action_t tap_dance_actions[] = {
    // 1 TOQUE PARA OPC 1 DOS PARA OPC 2
    [TD_ENE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
    [TD_SIFT_CAPSLOCK]  = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_SHIFT, KC_CAPS_LOCK)
};



enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOV,
  _NUM_PAD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_TAB,					KC_Q,		KC_W,		KC_E,		KC_R,					KC_T,		KC_Y,		KC_U,				KC_I,				KC_O,		KC_P,		KC_BSPC,
        LT(_MOV,KC_ESC),		KC_A,		KC_S,		KC_D,		KC_F,					KC_G,		KC_H,		KC_J,				KC_K,				KC_L,		KC_SCLN,	KC_QUOT,
        TD(TD_SIFT_CAPSLOCK),	KC_Z,		KC_X,		KC_C,		KC_V,					KC_B,		TD(TD_ENE),	KC_M,				KC_COMM,			KC_DOT,		KC_SLSH,	KC_SFTENT,
        KC_LCTL,				TT(5),		KC_LGUI,	KC_LALT,	LT(_LOWER, KC_BSPC),	KC_SPACE,	KC_SPACE,	LT(_RAISE,KC_ENT),	KC_RALT,			KC_RIGHT_GUI,		KC_MENU,		KC_LEAD
    ),

    [_LOWER] = LAYOUT_ortho_4x12(
        KC_TILD,	KC_EXLM,	KC_AT,	KC_HASH,	KC_DLR,		KC_PERC,	KC_CIRC,	KC_AMPR,	KC_ASTR,	KC_LPRN,	KC_RPRN,	KC_BSPC,
        KC_GRV,		KC_F1,		KC_F2,	KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_NO,		KC_NO,		KC_LCBR,	KC_RCBR,	KC_PIPE,
        KC_NO,		KC_F7,		KC_F8,	KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_NO,		KC_NO,		KC_NO,		KC_RBRC,	KC_BSLS,
        KC_NO,		KC_NO,		KC_NO,	KC_NO,		KC_TRNS,	KC_SPC,		KC_SPC,		KC_ENT,		KC_NO,		KC_MRWD,	KC_MPLY,	KC_MFFD
    ),

    [_RAISE] = LAYOUT_ortho_4x12(
		KC_1,		KC_2,		KC_3,		KC_4,	KC_5,		KC_6,	KC_7,	KC_8,		KC_9,	KC_0,	KC_UNDS,	KC_PLUS,
		KC_ESC,		KC_F1,		KC_F2,		KC_F3,	KC_F4,		KC_F5,	KC_F6,	KC_NO,		KC_NO,	KC_NO,	KC_MINS,	KC_EQL,
		KC_NO,		KC_F7,		KC_F8,		KC_F9,	KC_F10,		KC_F11,	KC_F12,	KC_NO,		KC_NO,	KC_NO,	KC_NO,		KC_NO,
		KC_MUTE,	KC_VOLD,	KC_VOLU,	KC_NO,	KC_BSPC,	KC_SPC,	KC_SPC,	KC_TRNS,	KC_NO,	KC_NO,	TG(3),		RESET
    ),

    [_ADJUST] = LAYOUT_ortho_4x12(
		RESET,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		DEBUG,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	TO(_QWERTY)
    ),

    [_MOV] = LAYOUT_ortho_4x12(
		KC_TAB,		KC_NO,	KC_NO,		KC_NO,		KC_NO,				KC_NO,		KC_NO,		KC_PGUP,	KC_INS,	KC_PSCR,	KC_SLCK,	KC_PAUS,
		KC_TRNS,	KC_NO,	KC_LCTL,	KC_LALT,	KC_LSFT,			KC_HOME,	KC_LEFT,	KC_DOWN,	KC_UP,	KC_RGHT,	KC_NO,		KC_NO,
		KC_NO,		KC_NO,	KC_DEL,		KC_NO,		LCTL(KC_LEFT_GUI),	KC_END,		KC_END,		KC_PGDN,	KC_NO,	KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_NO,	KC_NO,		KC_NO,		KC_BSPC,			KC_TRNS,	KC_TRNS,	KC_ENT,		KC_NO,	KC_NO,		KC_NO,		KC_NO
    ),

    [_NUM_PAD] = LAYOUT_ortho_4x12(
        KC_TAB,   		KC_7, 		KC_8,	KC_9, 		KC_NO, 		KC_NO,		KC_PSLS, 	KC_P7, 	KC_P8, 	KC_P9, 		KC_PPLS, KC_PAST,
        LM(0,MOD_LCTL), KC_4, 		KC_5, 	KC_6, 		KC_NO,		KC_BSPC,	KC_BSPC, 	KC_P4, 	KC_P5, 	KC_P6, 		KC_PPLS, KC_PPLS,
        LM(0,MOD_LCTL), KC_1, 		KC_2, 	KC_3,   	KC_NO, 		KC_NO, 		KC_NO, 		KC_P1, 	KC_P2, 	KC_P3, 		KC_PENT, KC_NO,
        LM(0,MOD_LCTL),	KC_TRNS, 	KC_0,  	KC_LALT, 	KC_0, 		KC_ENT, 	KC_ENT, 	KC_P0, 	KC_P0, 	KC_PDOT, 	KC_PENT, KC_NO
    )

};

/*layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
*/

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_THREE_KEYS(KC_C, KC_A, KC_S) {
      SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DELETE))));
    }

  }
}


