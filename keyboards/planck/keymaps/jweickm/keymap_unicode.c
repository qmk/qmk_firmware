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

enum planck_layers {
  _QWERTY,
  _COLEMAK,
	_DVORAK,
  _WIDEQWERTY,
  _WIDECOLEMAK, 
  _HRQWERTY,
  _HRCOLEMAK,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NAV,
  _NAV2,
  _NUM,	
  _MEDIA,
  _MOUSE,
  _PLOVER
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  WIDECOLEMAK,
  WIDEQWERTY
};

enum unicode_names {
  KC_DE_EUR,
  KC_DE_AE,
  KC_DE_ae,
  KC_DE_OE,
  KC_DE_oe,
  KC_DE_UE,
  KC_DE_ue,
  KC_DE_SZ
};

const uint32_t PROGMEM unicode_map[] = {
    [KC_DE_EUR]  = 0x20AC,  // €
    [KC_DE_AE]   = 0x00C4,  // Ä
    [KC_DE_ae]   = 0x00E4, // ä
    [KC_DE_OE]   = 0x00D6, // Ö
    [KC_DE_oe]   = 0x00F6, // ö
    [KC_DE_UE]   = 0x00DC, // Ü 
    [KC_DE_ue]   = 0x00FC, // ü
    [KC_DE_SZ]   = 0x00DF, // ß
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
/* Qwerty
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
[_QWERTY] = LAYOUT_planck_grid(
		LT(_NUM,KC_TAB),	KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,		KC_BSPC,	
		LCTL_T(KC_ESC),		KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_H,  KC_J,	KC_K,	KC_L,		KC_SCLN,	RSFT_T(KC_QUOT),	
		OSM(MOD_LSFT),		KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC_N,	KC_M,	KC_COMM, KC_DOT,	KC_SLSH,	KC_SFTENT,
		LCTL_T(KC_CAPS),	RALT_T(KC_APP),	KC_LGUI,	KC_LALT,	LT(_LOWER,KC_BSPC),	LT(_NAV,KC_SPC),	LT(_NAV,KC_SPC),	LT(_RAISE,KC_DEL),	RCTL_T(KC_LEFT),	LT(_MEDIA,KC_DOWN),	RALT_T(KC_UP),	RCTL_T(KC_RGHT)
),

	
[_COLEMAK] = LAYOUT_planck_grid(
		KC_TRNS,	KC_Q,	KC_W,	KC_F,	KC_P,	KC_B,	KC_J,	KC_L,		KC_U,		KC_Y,		KC_SCLN,	KC_TRNS,
		KC_TRNS,	KC_A,	KC_R,	KC_S,	KC_T,	KC_G,	KC_M,	KC_N,	KC_E,		KC_I,		KC_O,		KC_TRNS,
		KC_TRNS, KC_Z,	KC_X,	KC_C,	KC_D,	KC_V,	KC_K,	KC_H,	KC_COMM, KC_DOT,	KC_SLSH,	KC_TRNS,
		KC_TRNS, KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
),
	
[_WIDEQWERTY] = LAYOUT_planck_grid(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, KC_RBRC, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G, KC_GRV, KC_QUOT, KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), 
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LPRN, KC_RPRN, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, 
		KC_TRNS, KC_TRNS, LCTL_T(KC_ESC), OSM(MOD_LSFT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT_T(KC_SPC), LCTL_T(KC_TAB), KC_TRNS, KC_TRNS
),
	
[_WIDECOLEMAK] = LAYOUT_planck_grid(
		KC_Q, KC_W, KC_F, KC_P, KC_B, KC_LBRC, KC_RBRC, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, 
		LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G, KC_GRV, KC_QUOT, KC_M, RCTL_T(KC_N), RSFT_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O),
		KC_Z, KC_X, KC_C, KC_D, KC_V, KC_LPRN, KC_RPRN, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, 
		KC_TRNS, KC_TRNS, LCTL_T(KC_ESC), OSM(MOD_LSFT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT_T(KC_SPC), LCTL_T(KC_TAB), KC_TRNS, KC_TRNS
),
	
[_HRQWERTY] = LAYOUT_planck_grid(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_TRNS, KC_TRNS, RCTL_T(KC_J), RSFT_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN), KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_HRCOLEMAK] = LAYOUT_planck_grid(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_TRNS, KC_TRNS, RCTL_T(KC_N), RSFT_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_GAMING] = LAYOUT_planck_grid(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, TG(_GAMING), 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TRNS, 
		KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_Z, KC_M, KC_SCLN, KC_QUOT, 
		KC_LCTL, KC_NUBS, KC_B, KC_X, KC_C, KC_SPC, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_LOWER] = LAYOUT_planck_grid(
		KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, 
		KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, 
		KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LSFT(KC_NUHS), LSFT(KC_BSLS), KC_JYEN, KC_EQL, KC_TRNS, 
		TG(_MOUSE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_RAISE] = LAYOUT_planck_grid(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
		KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, 
		KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NUHS, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, 
		TG(_MOUSE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_ADJUST] = LAYOUT_planck_grid(
		LALT(KC_LSFT), RESET, DEBUG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_INS, 
		LALT(KC_GRV), EEP_RST, MU_MOD, AU_ON, AU_OFF, AG_NORM, AG_SWAP, QWERTY, COLEMAK, WIDEQWERTY, WIDECOLEMAK, TG(_GAMING), 
		KC_TRNS, MUV_DE, MUV_IN, MU_ON, MU_OFF, MI_ON, MI_OFF, TG(_HRQWERTY), TG(_HRCOLEMAK), TERM_ON, TERM_OFF, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_NAV] = LAYOUT_planck_grid(
		LALT(KC_LSFT), KC_NO, LCTL(KC_RGHT), LCTL(KC_RGHT), LCTL(KC_Y), KC_NO, LCTL(KC_C), LCTL(KC_Z), KC_PGUP, XP(KC_DE_ue,KC_DE_UE), LCTL(KC_V), XP(KC_DE_ue,KC_DE_UE), 
		LALT(KC_GRV), XP(KC_DE_ae,KC_DE_AE), X(KC_DE_SZ), X(KC_DE_SZ), KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XP(KC_DE_oe, KC_DE_OE), XP(KC_DE_ae, KC_DE_AE), 
		MO(_NAV2), KC_NO, KC_DEL, LCTL(KC_X), KC_NO, LCTL(KC_LEFT), KC_NO, KC_PGDN, KC_NO, KC_NO, LCTL(KC_F), KC_TRNS, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
),

[_NAV2] = LAYOUT_planck_grid(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_NO, 
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
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
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_NO, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_NO, KC_NO, KC_NO, 
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_ACL2, KC_ACL2, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
)
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
		case WIDEQWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WIDEQWERTY);
      }
      return false;
      break;
    case WIDECOLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WIDECOLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
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
			case LT(_HRQWERTY, LGUI_T(KC_A)):
					return true;
			case LT(_HRQWERTY, LALT_T(KC_S)):
					return true;
			case LT(_HRQWERTY, LSFT_T(KC_D)):
					return true;
			case LT(_HRQWERTY, LCTL_T(KC_F)):
					return true;
			case LT(_HRQWERTY, RCTL_T(KC_J)):
					return true;
			case LT(_HRQWERTY, RSFT_T(KC_K)):
					return true;
			case LT(_HRQWERTY, LALT_T(KC_L)):
					return true;
			case LT(_HRQWERTY, RGUI_T(KC_SCOLON)):
					return true;
			case LT(_HRCOLEMAK, LGUI_T(KC_A)):
					return true;
			case LT(_HRCOLEMAK, LALT_T(KC_R)):
					return true;
			case LT(_HRCOLEMAK, LSFT_T(KC_S)):
					return true;
			case LT(_HRCOLEMAK, LCTL_T(KC_T)):
					return true;
			case LT(_HRCOLEMAK, RCTL_T(KC_N)):
					return true;
			case LT(_HRCOLEMAK, RSFT_T(KC_E)):
					return true;
			case LT(_HRCOLEMAK, LALT_T(KC_I)):
					return true;
			case LT(_HRCOLEMAK, RGUI_T(KC_O)):
					return true;
			default:
					return false;
	}
}
