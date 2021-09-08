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
  _WIDECOLEMAK, 
  _HRCOLEMAK,
	_HRWIDECOLEMAK,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NAV,
  _NAV2,
  _NUM,
	_FN,
  _MEDIA,
  _MOUSE,
  _PLOVER
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  WIDECOLEMAK,
	HRCOLEMAK,
	HRWIDECOLEMAK,
  GAMING,
	VIM_O,
	VIM_V,
  KC_SVD_BD,
  KC_SVU_BU
};

// Tap Dance declarations
enum {
    TD_PRN,	// round brackets (parentheses)
		TD_BRC,	// square brackets
		TD_CBR,	// curly brackets
		TD_ESC_CAPS, // double tap for caps lock
		TD_QUO_BRC, // double function on quotes to enable typing ü in german layout
    TD_COMM_SLSH, // comma that doubles as a slash
    TD_MPLY_MNXT_MPRV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
[_COLEMAK] = LAYOUT_planck_grid(
		LT(_NUM,KC_TAB),	KC_Q,	KC_W,	KC_F,	KC_P,	KC_B,	KC_J,	KC_L,		KC_U,		KC_Y,		KC_SCLN,	KC_BSPC,
		LCTL_T(KC_ESC),	KC_A,	KC_R,	KC_S,	KC_T,	KC_G,	KC_M,	KC_N,	KC_E,		KC_I,		KC_O,		TD(TD_QUO_BRC),
		OSM(MOD_LSFT), KC_Z,	KC_X,	KC_C,	KC_D,	KC_V,	KC_K,	KC_H,	KC_COMM, KC_DOT,	KC_SLSH,	RSFT_T(KC_ENT),
		LCTL_T(KC_CAPS),	RALT_T(KC_APP),	LGUI_T(KC_TAB),	LT(_MOUSE, KC_ESC),	LT(_LOWER,KC_BSPC),	LT(_NAV,KC_SPC),	LT(_NAV,KC_SPC),	LT(_RAISE,KC_DEL),	LT(_MEDIA, KC_ENT),	TG(_NAV),	RALT_T(KC_UP),	CTL_T(KC_CAPS)
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
		KC_Q, KC_W, KC_F, KC_P, KC_B, KC_SVU_BU,  KC_J, KC_L, KC_U, 	 KC_Y,	 KC_SCLN, KC_LBRC,
		KC_A, KC_R, KC_S, KC_T, KC_G, TD(TD_MPLY_MNXT_MPRV),	 KC_M, KC_N, KC_E, 	 KC_I,	 KC_O, KC_QUOT,
		KC_Z, KC_X, KC_C, KC_D, KC_V, KC_SVD_BD,  KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_MINS, 
    TG(_MOUSE), LT(_NUM,KC_TAB), LCTL_T(KC_ESC), OSM(MOD_LSFT), LT(_LOWER, KC_BSPC), LT(_NAV2,KC_ENT), LT(_NAV2,KC_ENT), LT(_RAISE, KC_SPC), RCTL_T(KC_TAB), RGUI_T(KC_LALT), KC_LEFT, KC_RIGHT
),

[_HRCOLEMAK] = LAYOUT_planck_grid(
		KC_TRNS,	KC_Q,	KC_W,	LT(_NUM, KC_F),	KC_P,	KC_B,	KC_J,	KC_L,		LT(_FN, KC_U),		KC_Y,		KC_SCLN,	KC_LBRC, 
		TD(TD_ESC_CAPS), LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G, KC_M, RCTL_T(KC_N), RSFT_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_QUOT, 
		KC_TRNS, KC_Z,	KC_X,	KC_C,	KC_D,	KC_V,	KC_K,	KC_H,	KC_COMM, KC_DOT,	KC_SLSH,	KC_MINS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_HRWIDECOLEMAK] = LAYOUT_planck_grid(
		KC_Q, KC_W, LT(_NUM,KC_F), KC_P, KC_B, KC_SVU_BU,  KC_J, KC_L, LT(_FN,KC_U), 	 KC_Y,	 KC_SCLN, KC_LBRC,
		LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G, TD(TD_MPLY_MNXT_MPRV),	 KC_M, RCTL_T(KC_N), RSFT_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_QUOT,
		KC_Z, KC_X, KC_C, KC_D, KC_V, KC_SVD_BD,  KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_MINS, 
    TG(_MOUSE), LT(_NUM,KC_TAB), LCTL_T(KC_ESC), OSM(MOD_LSFT), LT(_LOWER, KC_BSPC), LT(_NAV2,KC_ENT), LT(_NAV2,KC_ENT), LT(_RAISE, KC_SPC), RCTL_T(KC_TAB), RGUI_T(KC_LALT), KC_LEFT, KC_RIGHT
),

[_GAMING] = LAYOUT_planck_grid(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, GAMING, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_QUOT, 
		KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_Z, KC_M, KC_SCLN, KC_SFTENT, 
		KC_LCTL, KC_NUBS, KC_B, KC_X, KC_C, KC_SPC, KC_SPC, KC_LALT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_LOWER] = LAYOUT_planck_grid(
		KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TILD, KC_CIRC, KC_AMPR, KC_ASTR, TD(TD_PRN), KC_RPRN, KC_DEL, 
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_DEL, KC_UNDS, KC_PLUS, TD(TD_CBR), KC_RCBR, KC_PIPE, 
		KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, LSFT(KC_NUHS), LSFT(KC_BSLS), KC_JYEN, KC_EQL, KC_TRNS, 
		TG(_MOUSE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_VOLD, KC_VOLU, KC_MPLY
),

[_RAISE] = LAYOUT_planck_grid(
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_DEL, KC_MINS, KC_EQL, TD(TD_BRC), KC_RBRC,KC_BSLS, 
		KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_NUHS, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, 
		TG(_MOUSE), KC_TRNS, KC_BSPC, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_ADJUST] = LAYOUT_planck_grid(
		LALT(KC_LSFT), RESET, DEBUG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_INS, 
		LALT(KC_GRV), EEP_RST, MU_MOD, AU_ON, AU_OFF, AG_NORM, AG_SWAP, COLEMAK, HRCOLEMAK, WIDECOLEMAK, HRWIDECOLEMAK, GAMING, 
		KC_TRNS, MUV_DE, MUV_IN, MU_ON, MU_OFF, MI_ON, MI_OFF, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_NAV] = LAYOUT_planck_grid(
		LALT(KC_LSFT), KC_NO, LCTL(KC_RGHT), KC_MS_U, LCTL(KC_V), LCTL(KC_LEFT), LCTL(KC_V), KC_RIGHT, KC_PGUP, LCTL(KC_C), KC_NO, KC_NO, 
		LALT(KC_GRV), KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_END, VIM_O, 
		KC_TRNS, KC_NO, LCTL(KC_X), LCTL(KC_X), KC_BTN2, VIM_V, KC_NO, KC_PGDN, TG(_NAV), KC_NO, LCTL(KC_F), KC_TRNS, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
),

[_NAV2] = LAYOUT_planck_grid(
    KC_TAB, LCTL(KC_RGHT), LALT(KC_LSFT), LALT(KC_GRV), LCTL(KC_LEFT), KC_BRIU, KC_CAPS, KC_RIGHT, KC_PGUP, LCTL(KC_C), KC_NO, KC_BSPC, 
		OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), KC_TAB, KC_MUTE, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_END, VIM_O, 
		KC_TRNS, KC_NO, LALT(KC_LSFT), TD(TD_ESC_CAPS), VIM_V, KC_BRID, KC_HOME, KC_PGDN, KC_NO, KC_NO, LCTL(KC_F), KC_TRNS, 
		KC_NO, KC_NO, KC_NO, KC_TRNS, KC_DEL, LT(_NAV2,KC_ENT), LT(_NAV2,KC_ENT), KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
),

[_NUM] = LAYOUT_planck_grid(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NLCK, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAST, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_PSLS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_PCMM, KC_PEQL, KC_TRNS
),

[_MEDIA] = LAYOUT_planck_grid(
		LALT(KC_LSFT), KC_NO, KC_NO, KC_NO, KC_NO, KC_BRID, KC_BRIU, KC_MUTE, KC_MPLY, KC_NO, KC_NO, KC_NO, 
		LALT(KC_GRV), KC_NO, KC_NO, KC_BRID, KC_BRIU, KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO, KC_TRNS, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
),

[_MOUSE] = LAYOUT_planck_grid(
		KC_NO, KC_NO, KC_BTN4, KC_BTN5, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_MS_U, KC_WH_U, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_NO, KC_NO, KC_NO, KC_NO, 
		TG(_MOUSE), KC_NO, KC_NO, KC_TRNS, KC_NO, KC_ACL2, KC_ACL2, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
),

[_FN] = LAYOUT_planck_grid(
		KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_NO, KC_F9,KC_F10,KC_F11,KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
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
void dance_mply_mnxt_mprv(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_MPLY);
    } if (state->count == 2) {
        tap_code(KC_MNXT);
    } else {
        tap_code(KC_MPRV);   
		}
}

qk_tap_dance_action_t tap_dance_actions[] = {
	// declare tap dance actions here
	[TD_PRN] = ACTION_TAP_DANCE_FN(dance_prn), 
	[TD_BRC] = ACTION_TAP_DANCE_FN(dance_brc),
	[TD_CBR] = ACTION_TAP_DANCE_FN(dance_cbr),
	[TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
	[TD_QUO_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_LBRC),
  [TD_COMM_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, KC_SLSH),
  [TD_MPLY_MNXT_MPRV] = ACTION_TAP_DANCE_FN(dance_mply_mnxt_mprv)
};

// TD(TD_ESC_CAPS), LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G, KC_M, RCTL_T(KC_N), RSFT_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_TRNS, 
// define the per_key_tapping_term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_ESC_CAPS):
            return TAPPING_TERM * 1.5;
        case LGUI_T(KC_A):
            return TAPPING_TERM * 1.4;
        case RGUI(KC_O):
            return TAPPING_TERM * 1.45;
        case LALT_T(KC_R):
            return TAPPING_TERM * 1.3;
        case LALT_T(KC_I):
            return TAPPING_TERM * 1.35;
        case LCTL_T(KC_T):
            return TAPPING_TERM * 1.1;
        case LCTL_T(KC_N):
            return TAPPING_TERM * 1.1;
        case LSFT_T(KC_S):
            return TAPPING_TERM * 1.0;
        case RSFT_T(KC_E):
            return TAPPING_TERM * 1.0;
        case LT(_NUM, KC_F):
            return TAPPING_TERM * 1.2;
        case LT(_FN, KC_U):
            return TAPPING_TERM * 1.2;
        case TD(TD_QUO_BRC):
            return TAPPING_TERM * 1.2;
        default:
            return TAPPING_TERM;
    }
}

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif


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
        } else {
          register_code(KC_VOLU);
        }
      } else {
        unregister_code(KC_BRIU);
        unregister_code(KC_VOLU);
      }
      return false;
    case KC_SVD_BD: // increase backlight when pressing shift and vol up
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
          register_code(KC_BRID);
        } else {
          register_code(KC_VOLD);
        }
      } else {
        unregister_code(KC_BRID);
        unregister_code(KC_VOLD);
      }
      return false;
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
			default:
					return false;
	}
}

// Set RGB to change with layer changes
#define HSV_DARKORANGE 10, 255, 255
#define HSV_DARKPINK 150, 100, 255

// Light LEDs 1 to 9 in goldenrod when COLEMAK is active
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_GOLDENROD}
);
// Light LEDs 1 to 9 in white when WIDECOLEMAK is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_WHITE}
);
// Light LEDs 1 to 9 in darkorange when HRCOLEMAK is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_DARKORANGE}
);
// Light LEDs 1 to 9 in green when HRWIDECOLEMAK is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_GREEN}
);
// Light LEDs 1 to 9 in green when HRWIDECOLEMAK is active
const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_GREEN}
);
// Light LEDs 1 to 9 in red when GAMING layer is active
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_RED}
);
// Light bottom LEDs in purple when ADJUST layer is active
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_PURPLE},
		{7, 2, HSV_PURPLE}
);
// Light bottom LEDs in red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_DARKPINK},      
    {7, 2, HSV_DARKPINK}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
		my_layer0_layer, 		// colemak
		my_layer1_layer,    // widecolemak
		my_layer2_layer,    // hrcolemak
		my_layer3_layer, 		// hrwidecolemak
		my_layer4_layer,    // gaming
		my_layer5_layer,    // adjust
		my_capslock_layer, 	// capslock
		my_nav_layer				// nav
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(6, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
	rgblight_set_layer_state(5, layer_state_cmp(state, _ADJUST));
	rgblight_set_layer_state(4, layer_state_cmp(state, _GAMING));
	rgblight_set_layer_state(7, layer_state_cmp(state, _NAV));
	return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
   rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK));
		rgblight_set_layer_state(1, layer_state_cmp(state, _WIDECOLEMAK));
		rgblight_set_layer_state(2, layer_state_cmp(state, _HRCOLEMAK));
		rgblight_set_layer_state(3, layer_state_cmp(state, _HRWIDECOLEMAK));
    return state;
}
