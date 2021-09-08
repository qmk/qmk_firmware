/* Copyright 2015-2017 Jack Humbert
 * Copyright 2021 Jakob Weickmann
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
#include "muse.h"
#include "quantum.h"


enum planck_layers {
  _COLEMAK,
  _HRCOLEMAK,
	_HRWIDECOLEMAK,
  _GAMING,
  _WIDECOLEMAK, 
  _LOWER,
  _RAISE,
  _LOWER2,
  _RAISE2,
  _ADJUST,
  _NAV,
  _NAV2,
  _NUM,
  _NUM2,
  _MOUSE,
  _PLOVER
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
	HRCOLEMAK,
  HRWIDECOLEMAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  GAMING,
  WIDECOLEMAK,
  TG_COLEMAK, 
  VIM_O,
	VIM_V,
  KC_SVD_BD,
  KC_SVU_BU, 
  KC_TAB_MPLY,
	ALT_TAB,
  CTL_TAB,
  DE_AE,
  DE_OE,
  DE_UE,
  DE_SZ,
	DE_EGRAVE,
  DE_EAIGU,
  KC_CURRENCY,
  KC_UE_SWITCH,
  LANG_SWITCH
};

// Tap Dance declarations
enum tap_dance_codes{
    TD_PRN,	// round brackets (parentheses)
		TD_BRC,	// square brackets
		TD_CBR,	// curly brackets
		TD_ESC_CAPS, // double tap for caps lock
		TD_QUO_BRC, // double function on quotes to enable typing ü in german layout
    TD_COMM_SLSH, // comma that doubles as a slash
    TD_MPLY, // play/pause, double for next, triple for previous song
    TD_Q_TAB // double tap q to register tab
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
[_COLEMAK] = LAYOUT_planck_grid(
		LT(_NUM,KC_TAB),	KC_Q,	KC_W,	KC_F,	KC_P,	KC_B,	KC_J,	KC_L,		KC_U,		KC_Y,		KC_SCLN,	KC_BSPC,
		LCTL_T(KC_ESC),	KC_A,	KC_R,	KC_S,	KC_T,	KC_G,	KC_M,	KC_N,	KC_E,		KC_I,		KC_O,		TD(TD_QUO_BRC),
		OSM(MOD_LSFT), KC_Z,	KC_X,	KC_C,	KC_D,	KC_V,	KC_K,	KC_H,	KC_COMM, KC_DOT,	KC_SLSH,	RSFT_T(KC_ENT),
		LCTL_T(KC_CAPS),	RALT_T(KC_APP),	LGUI_T(KC_TAB),	LT(_MOUSE, KC_ESC),	LT(_LOWER,KC_BSPC),	LT(_NAV,KC_SPC),	LT(_NAV,KC_SPC),	LT(_RAISE,KC_DEL),	RCTL_T(KC_ENT),	TG(_NAV),	RALT_T(KC_UP),	CTL_T(KC_CAPS)
),

[_HRCOLEMAK] = LAYOUT_planck_grid(
		LT(_NUM,KC_TAB),	LGUI_T(KC_Q),	LALT_T(KC_W),	LT(_NUM, KC_F),	KC_P,	KC_B,	KC_J,	KC_L,		LT(_NUM,KC_U),	LALT_T(KC_Y),		RGUI_T(KC_SCLN),	KC_LBRC, 
		TD(TD_ESC_CAPS), KC_A, KC_R, LSFT_T(KC_S), LCTL_T(KC_T), KC_G, KC_M, RCTL_T(KC_N), RSFT_T(KC_E), KC_I, KC_O, KC_QUOT, 
		OSM(MOD_LSFT), KC_Z,	KC_X,	KC_C,	KC_D,	KC_V,	KC_K,	KC_H,	KC_COMM, KC_DOT,	KC_SLSH,	RSFT_T(KC_ENT),
		LCTL_T(KC_CAPS),	RALT_T(KC_APP),	LGUI_T(KC_TAB),	LT(_MOUSE, KC_ESC),	LT(_LOWER,KC_BSPC),	LT(_NAV,KC_SPC),	LT(_NAV,KC_SPC),	LT(_RAISE,KC_DEL),	RCTL_T(KC_ENT),	TG(_NAV),	RALT_T(KC_UP),	CTL_T(KC_CAPS)
),

[_HRWIDECOLEMAK] = LAYOUT_planck_grid(
		LGUI_T(KC_Q), LALT_T(KC_W), LSFT_T(KC_F), LCTL_T(KC_P), LT(_NUM2,KC_B), KC_SVU_BU,  LT(_NUM2,KC_J), RCTL_T(KC_L), RSFT_T(KC_U), 	 LALT_T(KC_Y),	 RGUI_T(KC_SCLN), DE_UE,
		KC_A, KC_R, KC_S, KC_T, KC_G, KC_TAB_MPLY,	 KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT,   
		LT(_MOUSE,KC_Z), KC_X, KC_C, KC_D, KC_V, KC_SVD_BD,  KC_K, KC_H, KC_COMM, KC_DOT, LT(_MOUSE,KC_SLSH), KC_MINS, 
    KC_CAPS, LT(_NUM,KC_TAB), LGUI_T(KC_ESC), LT(_LOWER2, KC_BSPC), OSM(MOD_LSFT), LT(_NAV2,KC_SPC), LT(_NAV2,KC_SPC), LT(_RAISE2, KC_DEL), RCTL_T(KC_ENT), KC_LALT, KC_LEFT, KC_RIGHT
),

[_GAMING] = LAYOUT_planck_grid(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_F5, KC_F8, KC_F9, KC_VOLU, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_VOLD, 
		KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_Z, KC_M, KC_SCLN, TG_COLEMAK, 
		KC_LCTL, KC_NUBS, KC_B, KC_X, KC_C, KC_SPC, KC_SPC, KC_LALT, KC_TRNS, KC_TRNS, ALT_TAB, GAMING
),

/* WIDECOLEMAK
 * ,-----------------------------------------------------------------------------------.
 * |_NUM(Tab)|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |CTL(Esc)|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_WIDECOLEMAK] = LAYOUT_planck_grid(
		TD(TD_Q_TAB), KC_W, KC_F, KC_P, KC_B, KC_SVU_BU,  KC_J, KC_L, KC_U, 	 KC_Y,	 KC_SCLN, DE_UE,
		KC_A, KC_R, KC_S, KC_T, KC_G, KC_TAB_MPLY,	 KC_M, KC_N, KC_E, 	 KC_I,	 KC_O, KC_QUOT,
		KC_Z, KC_X, KC_C, KC_D, KC_V, KC_SVD_BD,  KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, TG_COLEMAK,
    KC_CAPS, LT(_NUM,KC_TAB), LGUI_T(KC_ESC), LT(_LOWER2, KC_BSPC), OSM(MOD_LSFT), LT(_NAV2,KC_SPC), LT(_NAV2,KC_SPC), LT(_RAISE2, KC_DEL), RCTL_T(KC_ENT), KC_LALT, KC_LEFT, KC_RIGHT
),                                                               

[_LOWER] = LAYOUT_planck_grid(
  KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, TD(TD_PRN), KC_RPRN, KC_DEL, 
  KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, TD(TD_CBR), KC_RCBR, KC_PIPE, 
  KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LSFT(KC_NUHS), LSFT(KC_BSLS), KC_JYEN, KC_EQL, KC_TRNS, 
  TG(_MOUSE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_VOLD, KC_VOLU, KC_MPLY
),

[_RAISE] = LAYOUT_planck_grid(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
		KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_MINS, KC_EQL, TD(TD_BRC), KC_RBRC,KC_BSLS, 
		KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NUHS, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, 
		TG(_MOUSE), KC_TRNS, KC_BSPC, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_LOWER2] = LAYOUT_planck_grid(
		KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TILD, KC_CIRC, KC_AMPR, KC_ASTR, TD(TD_PRN), KC_RPRN, DE_AE, 
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, DE_SZ, KC_UNDS, KC_PLUS, TD(TD_CBR), KC_RCBR, KC_PIPE, 
		KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, LSFT(KC_NUHS), LSFT(KC_BSLS), KC_NUBS, KC_CURRENCY, DE_EGRAVE, 
		TG(_MOUSE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_VOLD, KC_VOLU, KC_MPLY
),

[_RAISE2] = LAYOUT_planck_grid(
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV, KC_6, KC_7, KC_8, KC_9, KC_0, DE_OE, 
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, DE_SZ, KC_MINS, KC_EQL, TD(TD_BRC), KC_RBRC,KC_BSLS, 
		KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_NUHS, KC_COMM, KC_DOT, KC_SLSH, DE_EAIGU, 
		TG(_MOUSE), KC_TRNS, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_ADJUST] = LAYOUT_planck_grid(
		LALT(KC_LSFT), RESET, DEBUG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_INS, 
		LALT(KC_GRV), EEP_RST, MU_MOD, AU_ON, AU_OFF, AG_NORM, AG_SWAP, COLEMAK, HRCOLEMAK, WIDECOLEMAK, HRWIDECOLEMAK, GAMING, 
		KC_TRNS, MUV_DE, MUV_IN, MU_ON, MU_OFF, MI_ON, MI_OFF, KC_SVD_BD, KC_MPLY, KC_SVU_BU, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_NAV] = LAYOUT_planck_grid(
		LALT(KC_LSFT), KC_NO, LCTL(KC_RGHT), KC_MS_U, LCTL(KC_V), LCTL(KC_LEFT), LCTL(KC_V), KC_RIGHT, KC_PGUP, LCTL(KC_C), KC_NO, KC_NO, 
		LALT(KC_GRV), KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_END, VIM_O, 
		KC_TRNS, KC_NO, LCTL(KC_X), LCTL(KC_X), KC_BTN2, VIM_V, KC_NO, KC_PGDN, TG(_NAV), KC_NO, LCTL(KC_F), KC_TRNS, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
),

[_NAV2] = LAYOUT_planck_grid(
    ALT_TAB, LCTL(KC_RGHT), LANG_SWITCH, LALT(KC_GRV), LCTL(KC_LEFT), KC_BRIU, KC_DOWN, KC_RIGHT, KC_PGUP, LCTL(KC_C), KC_NO, KC_UE_SWITCH, 
		CTL_TAB, KC_TAB, KC_ESC, LT(_NUM2,KC_ENT), KC_TAB, KC_MUTE, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_END, VIM_O, 
		KC_LSFT, KC_NO, LCTL(KC_X), TD(TD_ESC_CAPS), VIM_V, KC_BRID, KC_HOME, KC_PGDN, KC_NO, KC_NO, LCTL(KC_F), KC_TRNS, 
		KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, LT(_NAV2,KC_SPC), LT(_NAV2,KC_SPC), KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
),

[_NUM] = LAYOUT_planck_grid(
		KC_TAB, KC_F1, KC_F2, LT(_NUM,KC_F3), KC_F4, KC_SVU_BU, KC_NLCK, KC_P7, LT(_NUM,KC_P8), KC_P9, KC_PMNS, KC_TRNS, 
		KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_MPLY, KC_ENT, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_TRNS, 
		KC_TRNS, KC_F9,KC_F10,KC_F11,KC_F12, KC_SVD_BD, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_PSLS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_DOT, KC_COMM, KC_EQL, KC_TRNS
),

[_NUM2] = LAYOUT_planck_grid(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_MPRV, KC_NLCK, KC_MNXT, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_TRNS, 
		KC_F5, KC_F6, KC_F7, KC_F8, KC_VOLU, KC_MPLY, KC_BRIU, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_TRNS, 
		KC_F9,KC_F10,KC_F11,KC_F12, KC_VOLD, KC_MUTE, KC_BRID, KC_P1, KC_P2, KC_P3, KC_PSLS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_DOT, KC_COMM, KC_EQL, KC_TRNS
),

[_MOUSE] = LAYOUT_planck_grid(
		KC_NO, KC_NO, KC_BTN4, KC_BTN5, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_MS_U, KC_WH_U, KC_NO, KC_NO, 
		KC_NO, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, 
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_NO, KC_NO, KC_TRNS, KC_NO, 
		TG(_MOUSE), KC_NO, KC_NO, KC_TRNS, KC_NO, KC_ACL2, KC_ACL2, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
)

};

// define the tap dance functions
void dance_prn(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_LPRN);
    } else {
        tap_code16(KC_LPRN);
				tap_code16(KC_RPRN);
				tap_code(KC_LEFT);
    }
}
void dance_brc(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_LBRC);
    } else {
        tap_code(KC_LBRC);
				tap_code(KC_RBRC);
				tap_code(KC_LEFT);
    }
}
void dance_cbr(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_LCBR);
    } else {
        tap_code16(KC_LCBR);
				tap_code16(KC_RCBR);
				tap_code(KC_LEFT);
		}
}

qk_tap_dance_action_t tap_dance_actions[] = {
	// declare tap dance actions here
	[TD_PRN] = ACTION_TAP_DANCE_FN(dance_prn), 
	[TD_BRC] = ACTION_TAP_DANCE_FN(dance_brc),
	[TD_CBR] = ACTION_TAP_DANCE_FN(dance_cbr),
  [TD_MPLY] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
	[TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
	[TD_QUO_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_LBRC),
  [TD_COMM_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, KC_SLSH),
  [TD_Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB)
};

// TD(TD_ESC_CAPS), LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G, KC_M, RCTL_T(KC_N), RSFT_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_TRNS, 
// define the per_key_tapping_term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_ESC_CAPS):
            return TAPPING_TERM * 1.5;
        case LGUI_T(KC_A):
            return TAPPING_TERM * 1.4;
        case LGUI_T(KC_Q):
            return TAPPING_TERM * 1.1;
        case RGUI_T(KC_O):
            return TAPPING_TERM * 1.45;
        case RGUI_T(KC_SCLN):
            return TAPPING_TERM * 1.1;
        case LALT_T(KC_R):
            return TAPPING_TERM * 1.3;
        case LALT_T(KC_W):
            return TAPPING_TERM * 1.25;
        case LALT_T(KC_I):
            return TAPPING_TERM * 1.35;
        case LALT_T(KC_Y):
            return TAPPING_TERM * 1.25;
        case LCTL_T(KC_T):
            return TAPPING_TERM * 1.1;
        case LCTL_T(KC_P):
            return TAPPING_TERM * 1.1;
        case RCTL_T(KC_N):
            return TAPPING_TERM * 1.1;
        case RCTL_T(KC_L):
            return TAPPING_TERM * 1.1;
        case LSFT_T(KC_S):
            return TAPPING_TERM * 1.1;
        case LSFT_T(KC_F):
            return TAPPING_TERM * 1.2;
        case RSFT_T(KC_E):
            return TAPPING_TERM * 1.1;
        case RSFT_T(KC_U):
            return TAPPING_TERM * 1.2;
        case LT(_NUM, KC_F):
            return TAPPING_TERM * 1.2;
        case LT(_NUM2, KC_B):
            return TAPPING_TERM * 1.1;
        case LT(_NUM2, KC_J):
            return TAPPING_TERM * 1.1;
        case LT(_MOUSE, KC_Z):
            return TAPPING_TERM * 1.15;
        case LT(_MOUSE, KC_SLSH):
            return TAPPING_TERM * 1.15;
        case TD(TD_QUO_BRC):
            return TAPPING_TERM * 1.1;
        case TD(TD_Q_TAB):
            return TAPPING_TERM * 1.1;
        default:
            return TAPPING_TERM;
    }
}

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

// alt tab function setup
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool is_ctl_tab_active = false;
uint16_t ctl_tab_timer = 0;
bool de_layout_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case WIDECOLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WIDECOLEMAK);
      }
      return false;
      break;
		case HRCOLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_HRCOLEMAK);
      }
      return false;
      break;
		case HRWIDECOLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_HRWIDECOLEMAK);
      }
      return false;
      break;	
    case GAMING:
      if (record->event.pressed) {
        layer_invert(_GAMING);
      }
      return false;
      break;
    case TG_COLEMAK:
      if (record->event.pressed) {
        tap_code(KC_ENT);
        layer_invert(_WIDECOLEMAK);
      }
      return false;
      break;
		case VIM_O:
			if (record->event.pressed) {
				tap_code(KC_END);
				tap_code(KC_ENT);
			}
			return false;
			break;
		case VIM_V:
			if (record->event.pressed) {
				if (get_mods() & MOD_BIT(KC_LSFT)) {
					unregister_code(KC_LSFT);
				}	else {
					register_code(KC_LSFT);
				}
			}
			return false;
			break;
    case KC_SVU_BU: // increase backlight when pressing shift and vol up
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
          register_code(KC_BRIU);
        } else if (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL)){
					register_code(KC_MNXT);
				} else {
          register_code(KC_VOLU);
        }
      } else {
        unregister_code(KC_BRIU);
				unregister_code(KC_MNXT);
        unregister_code(KC_VOLU);
      }
      return false;
    case KC_SVD_BD: // decrease backlight when pressing shift and vol up
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
          register_code(KC_BRID);
				} else if (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL)){
					register_code(KC_MPRV);
        } else {
          register_code(KC_VOLD);
        }
      } else {
        unregister_code(KC_BRID);
        unregister_code(KC_MPRV);
        unregister_code(KC_VOLD);
      }
      return false;
    case KC_TAB_MPLY: // press tab or play/pause when ctrl is pressed 
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL)){
					register_code(KC_MPLY);
				} else {
          register_code(KC_TAB);
        }
      } else {
        unregister_code(KC_MPLY);
				unregister_code(KC_TAB);
      }
      return false;
		case ALT_TAB:
			if (record->event.pressed) {
				if (!is_alt_tab_active) {
					is_alt_tab_active = true;
					register_code(KC_LALT);
				}
				alt_tab_timer = timer_read();
				register_code(KC_TAB);
			} else {
				unregister_code(KC_TAB);
			}
			break;
    case CTL_TAB:
			if (record->event.pressed) {
				if (!is_ctl_tab_active) {
					is_ctl_tab_active = true;
					register_code(KC_LCTL);
				}
				ctl_tab_timer = timer_read();
				register_code(KC_TAB);
			} else {
				unregister_code(KC_TAB);
			}
			break;
    case DE_AE:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();
        if (temp_mod & MODS_SHIFT_MASK) {
          if (!de_layout_active) {
            clear_mods();
            register_code(KC_LALT);
            tap_code(KC_P0); tap_code(KC_P1); tap_code(KC_P9); tap_code(KC_P6); // Ä
            unregister_code(KC_LALT);
          } else {
            register_code(KC_QUOT);
          }
				} else {
          if (!de_layout_active) {
            clear_mods();
            register_code(KC_LALT);
					  tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P2); tap_code(KC_P8); // ä
            unregister_code(KC_LALT);
				  } else {
            register_code(KC_QUOT);
          }
        }
      unregister_code(KC_QUOT);
			return false;
			}
			break;
		case DE_OE:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();
        if (temp_mod & MODS_SHIFT_MASK) {
          if (!de_layout_active) {
            clear_mods();
            register_code(KC_LALT);
            tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P1); tap_code(KC_P4); // Ö
            unregister_code(KC_LALT);
          } else {
            register_code(KC_SCLN);
          }
				} else {
          if (!de_layout_active) {
            clear_mods();
            register_code(KC_LALT);
					  tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P4); tap_code(KC_P6); // ö
            unregister_code(KC_LALT);
				  } else {
            register_code(KC_SCLN);
          }
        }
      unregister_code(KC_SCLN);
			return false;
			}
			break;
    case DE_UE:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();
        if (temp_mod & MODS_SHIFT_MASK) {
          if (!de_layout_active) {
            clear_mods();
            register_code(KC_LALT);
            tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P2); tap_code(KC_P0); // Ü
            unregister_code(KC_LALT);
          } else {
            register_code(KC_LBRC);
          }
				} else {
          if (!de_layout_active) {
            clear_mods();
            register_code(KC_LALT);
					  tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P5); tap_code(KC_P2); // ü
            unregister_code(KC_LALT);
				  } else {
            register_code(KC_LBRC);
          }
        }
      unregister_code(KC_LBRC);
			return false;
			}
			break;
    case KC_UE_SWITCH:
      if (record->event.pressed) {
        if (de_layout_active) {
          de_layout_active = false;// deactivate ü if it was active
				} else {
				  de_layout_active = true; // activate ü if it was deactivated
				}
			return false;
			}
			break;
    case LANG_SWITCH:  
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_LSFT);
        unregister_code(KC_LALT);
        if (de_layout_active) {
          de_layout_active = false;// deactivate ü if it was active
				} else {
				  de_layout_active = true; // activate ü if it was deactivated
				}
      return false;
      }
      break;
    case DE_SZ:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        register_code(KC_LALT);
        if (temp_mod & MODS_SHIFT_MASK) {
          tap_code(KC_P0); tap_code(KC_P1); tap_code(KC_P7); tap_code(KC_P6); // °
				} else {
					tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P2); tap_code(KC_P3); // ß
				}
			unregister_code(KC_LALT);
			return false;
			}
			break;
    case DE_EGRAVE:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        register_code(KC_LALT);
        if (temp_mod & MODS_SHIFT_MASK) {
          tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P0); tap_code(KC_P0); // È
				} else {
					tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P3); tap_code(KC_P2); // è 
				}
			unregister_code(KC_LALT);
			return false;
			}
			break;			
    case DE_EAIGU:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        register_code(KC_LALT);
        if (temp_mod & MODS_SHIFT_MASK) {
          tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P0); tap_code(KC_P1); // É
				} else {
					tap_code(KC_P0); tap_code(KC_P2); tap_code(KC_P3); tap_code(KC_P3); // é
				}
			unregister_code(KC_LALT);
			return false;
			}
			break;			
    case KC_CURRENCY:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        register_code(KC_LALT);
        if (temp_mod & MODS_SHIFT_MASK) {
          tap_code(KC_P1); tap_code(KC_P5); tap_code(KC_P7); // ¥
				} else {
          tap_code(KC_P0); tap_code(KC_P1); tap_code(KC_P2); tap_code(KC_P8); // €
				}
			unregister_code(KC_LALT);
			return false;
			}
			break;			
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
  // set the timeout for the alt-tab function
	if (is_alt_tab_active) {
		if (timer_elapsed(alt_tab_timer) > 700) {
			unregister_code(KC_LALT);
			is_alt_tab_active = false;
		}
	}
	if (is_ctl_tab_active) {
		if (timer_elapsed(ctl_tab_timer) > 700) {
			unregister_code(KC_LCTL);
			is_ctl_tab_active = false;
		}
	}
	#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
			case LSFT_T(KC_S):
					return true;
			case RSFT_T(KC_E):
					return true;
			case LSFT_T(KC_D):
					return true;
			case RSFT_T(KC_K):
					return true;
			case LSFT_T(KC_F):
					return true;
			case RSFT_T(KC_U):
					return true;
			default:
					return false;
	}
}

// Set RGB to change with layer changes
#define HSV_DARKORANGE 10, 255, 255
#define HSV_DARKPINK 150, 100, 255

// Light LEDs 1 to 9 in darkorange when HRCOLEMAK is active
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_DARKORANGE}
);
// Light LEDs 1 to 9 in green when HRWIDECOLEMAK is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_CYAN}
);
// Light LEDs 1 to 9 in red when GAMING layer is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_RED}
);
// Light LEDs 1 to 9 in white when WIDECOLEMAK is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_WHITE}
);
// Light bottom LEDs in purple when ADJUST layer is active
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_PURPLE},
		{7, 3, HSV_PURPLE}
);
// Light LEDs 1 to 9 in darkorange when de_layout_active is true
const rgblight_segment_t PROGMEM my_de_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 4, HSV_DARKORANGE}
);
// Light bottom LEDs in red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_RED},      
    {7, 3, HSV_RED}
);
// Light LEDs 1 to 9 in white when NAVIGATION is active
const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_WHITE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
		my_layer0_layer,    // hrcolemak
		my_layer1_layer, 		// hrwidecolemak
		my_layer2_layer,    // gaming
		my_layer3_layer,    // widecolemak
		my_layer4_layer,    // adjust
		my_nav_layer,				// nav
		my_de_layer,        // de_layout
		my_capslock_layer 	// capslock
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(7, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));
	rgblight_set_layer_state(2, layer_state_cmp(state, _GAMING));
	rgblight_set_layer_state(5, layer_state_cmp(state, _NAV));
	rgblight_set_layer_state(3, layer_state_cmp(state, _WIDECOLEMAK));
  rgblight_set_layer_state(6, de_layout_active);
	if (                                                                          
      ( layer_state_cmp(state, _LOWER) && layer_state_cmp(state, _RAISE ) ) ||
      ( layer_state_cmp(state, _LOWER2) && layer_state_cmp(state, _RAISE2 ) ) ) {
    return state | (1UL<<_ADJUST);                                              
  } else {                                                                      
    return state & ~(1UL<<_ADJUST);                                             
  }

	//state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  //return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
		rgblight_set_layer_state(3, layer_state_cmp(state, _WIDECOLEMAK));
		rgblight_set_layer_state(0, layer_state_cmp(state, _HRCOLEMAK));
		rgblight_set_layer_state(1, layer_state_cmp(state, _HRWIDECOLEMAK));
    return state;
}

