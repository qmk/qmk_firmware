/* Copyright 2015-2021 Jack Humbert
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
  _COLEMAKDH,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _MOUSE,
  _ADJUST
};

enum planck_keycodes {
  COLEMAKDH = SAFE_RANGE
};

// Raycast shortcuts
#define MICTGL LGUI(LALT(LSFT(KC_F12))) // mic toggle, does not work
#define WRH LGUI(LALT(LSFT(KC_F13))) // window right half
#define WLH LGUI(LALT(LSFT(KC_F14))) // window left half
#define WLT LGUI(LALT(KC_F13)) // window left third
#define WRT LGUI(LALT(KC_F14)) // window right two thirds
#define WAM LGUI(LSFT(KC_F13)) // window almost maximize
#define WCH LGUI(LSFT(KC_F14)) // window center half


// Layers
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNCT MO(_FUNCTION)
#define MOUSE MO(_MOUSE)

// Layer switching
#define LOWBSP LT(_LOWER, KC_BSPC)
#define RAISENT LT(_RAISE, KC_ENT)
#define MS_ESC LT(_MOUSE, KC_ESC)
#define FN_TAB LT(_FUNCTION, KC_TAB)

// Modified Alphas
#define CTLA CTL_T(KC_A)
#define CTLO CTL_T(KC_O)
#define GUIR GUI_T(KC_R)
#define GUII GUI_T(KC_I)
#define ALTS ALT_T(KC_S)
#define ALTE ALT_T(KC_E)
#define SFTT SFT_T(KC_T)
#define SFTN SFT_T(KC_N)

// Modifiers on lower layer
#define SF4 SFT_T(KC_4)
#define AL5 ALT_T(KC_5)
#define GUI6 GUI_T(KC_6)
#define CMIN CTL_T(KC_MINUS)
#define ALLP ALT_T(KC_LBRC)
#define SFRP SFT_T(KC_RBRC)

// KC_NO synonim
#define xxxxx KC_NO


//Tap Dance Declarations
enum {
  TD_S_BSL = 0, // slash/backslash
  TD_PL_NX, // play/next
  TD_XX_PR, // xxxxx/previous
  TD_C_SCL, // comma/semicolon
  TD_D_CL, // period/colon
  TD_WLH_WLT, // window left half / window left third
  TD_WRH_WRT // window right half / window right twho thirds
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_S_BSL]  = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_BACKSLASH),
  [TD_PL_NX]  = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
  [TD_XX_PR]  = ACTION_TAP_DANCE_DOUBLE(xxxxx, KC_MPRV),
  [TD_C_SCL]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_SCLN),
  [TD_D_CL]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, LSFT(KC_SCLN)),
  [TD_WLH_WLT] = ACTION_TAP_DANCE_DOUBLE(WLH, WLT),
  [TD_WRH_WRT] = ACTION_TAP_DANCE_DOUBLE(WRH, WRT)
// Other declarations would go here, separated by commas, if you have them
};

// Tapdance defines
#define TDSLBS TD(TD_S_BSL)
#define TDPLNX TD(TD_PL_NX)
#define TDXXPR TD(TD_XX_PR)
#define TDCSCL TD(TD_C_SCL)
#define TDDCL TD(TD_D_CL)
#define TDWL TD(TD_WLH_WLT) // tapdance window left
#define TDWR TD(TD_WRH_WRT) // tapdance window right

// brightness up/down shortcut in Raycast
#define BUP KC_BRIU
#define BDN KC_BRID

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* TODO Colemak-dh
 * ,-----------------------------------------------------------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |      | Play |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAKDH] = LAYOUT_planck_grid(
  KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     TDXXPR,                    TDPLNX,   KC_J,     KC_L,      KC_U,     KC_Y,     KC_QUOT, \
  CTLA,     GUIR,     ALTS,     SFTT,     KC_G,     TDWL,                      TDWR,     KC_M,     SFTN,      ALTE,     GUII,     CTLO, \
  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,     KC_VOLD,                   KC_VOLU,  KC_K,     KC_H,      TDCSCL,   TDDCL,    TDSLBS, \
  BDN,      xxxxx,    MS_ESC,   LOWBSP,   KC_LSFT,  KC_DEL,                    KC_TAB,   KC_SPC,   RAISENT,   FN_TAB,   xxxxx,    BUP \
),

/* TODO Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  KC_GRV,   KC_F18,   KC_LPRN,  KC_RPRN,  xxxxx,    xxxxx,                    xxxxx,    xxxxx,    KC_7,     KC_8,     KC_9,     KC_EQL, \
  KC_LCTL, 	KC_LWIN,  ALLP,     SFRP,     KC_TAB,   xxxxx,                    xxxxx,    xxxxx,    SF4,      AL5,      GUI6,     CMIN, \
  KC_F19,   xxxxx,    KC_F17,   KC_F16,   KC_F13,   xxxxx,                    xxxxx,    xxxxx,    KC_1,     KC_2,     KC_3,     KC_SLSH,  \
  xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,                    xxxxx,    KC_SPC,   KC_0,     xxxxx,    KC_DOT,   xxxxx  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
	xxxxx ,   xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,                    xxxxx,    KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   xxxxx,  \
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,                    xxxxx,    KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,	KC_INS,  \
	xxxxx,  	KC_X,     xxxxx,    xxxxx,    xxxxx,    xxxxx,                    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,   	xxxxx,    \
	xxxxx,  	xxxxx,    _______,  _______,  _______,  KC_TAB,                   xxxxx,  	KC_SPC,   xxxxx,    xxxxx,    xxxxx,  	xxxxx  \
),

/* TODO Function layer
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT_planck_grid(
	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,                    xxxxx,    xxxxx,    KC_F7,    KC_F8,    KC_F9,    KC_F10,	\
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,                    xxxxx,    xxxxx,    KC_F4,    KC_F5,    KC_F6,    KC_F11,	\
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,                    xxxxx,    xxxxx,    KC_F1,    KC_F2,    KC_F3,    KC_F12,	\
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,                    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx	\
),

/* TODO Mouse layer
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	KC_WH_U,  KC_WH_L,  KC_MS_U,  KC_WH_R,  xxxxx,   \
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,    xxxxx,  	KC_WH_D,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_LCTL, \
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,   \
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_BTN1,  KC_BTN2,  xxxxx,    xxxxx,    xxxxx \
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, COLEMAKDH,  _______, _______,  _______,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
    case COLEMAKDH:
      if (record->event.pressed) {
        print("mode just switched to colemak-dh and this is a huge string\n");
        set_single_persistent_default_layer(_COLEMAKDH);
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

bool encoder_update_user(uint8_t index, bool clockwise) {
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

bool dip_switch_update_user(uint8_t index, bool active) {
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
    return true;
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
