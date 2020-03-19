/* Copyright 2015-2017 Jack Humbert
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

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _FUNCT,
  _MOUSE,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

//Tap Dance Declarations
enum {
  TD_Q_MIN = 0,
  TD_S_BSL,
  TD_PL_NX,
  TD_ST_PR,
  TD_LC_CA,
  TD_F4_ALTF4,
  TD_C_SCL,
  TD_D_CL,
  TD_TOGGL
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_Q_MIN]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_MINS),
  [TD_S_BSL]  = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_BSLASH),
  [TD_PL_NX]  = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
  [TD_ST_PR]  = ACTION_TAP_DANCE_DOUBLE(KC_MSTP, KC_MPRV),
  [TD_LC_CA]  = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, LCTL(KC_A)),
  [TD_C_SCL]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_SCLN),
  [TD_D_CL]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, LSFT(KC_SCLN)),
  [TD_F4_ALTF4]  = ACTION_TAP_DANCE_DOUBLE(KC_F4, LALT(KC_F4)),
  [TD_TOGGL] = ACTION_TAP_DANCE_DOUBLE(LCTL(LWIN(LSFT(LALT(KC_H)))), LCTL(LWIN(LSFT(LALT(KC_K)))))
// Other declarations would go here, separated by commas, if you have them
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNCT MO(_FUNCT)
#define MOUSE MO(_MOUSE)
#define LOWBSP LT(_LOWER, KC_BSPC)
#define RAISENT LT(_RAISE, KC_ENT)
#define MSESC LT(_MOUSE, KC_ESC)
#define FNTAB LT(_FUNCT, KC_TAB)
#define SHT_BSP LSFT_T(KC_BSPC)
#define CMD_BSP LGUI_T(KC_BSPC)
#define CMD_SPC LGUI_T(KC_SPC)  // unused atm
#define CMD_LEFT LGUI_T(KC_LEFT)
#define SHT_SPC LSFT_T(KC_SPC)
#define DIVVY LALT(LGUI(LSFT(KC_D)))
#define F_CHR LALT(LSFT(KC_E))
#define F_WIN LALT(LGUI(LSFT(KC_W)))
#define CTLA CTL_T(KC_A)
#define CTLQ CTL_T(KC_Q)
#define CTLO CTL_T(KC_O)
#define CTLQUOT CTL_T(KC_QUOT)
#define GUIR GUI_T(KC_R)
#define GUIW GUI_T(KC_W)
#define GUII GUI_T(KC_I)
#define GUIY GUI_T(KC_Y)
#define ALTS ALT_T(KC_S)
#define ALTF ALT_T(KC_F)
#define ALTE ALT_T(KC_E)
#define ALTU ALT_T(KC_U)
#define SFTT SFT_T(KC_T)
#define SFTP SFT_T(KC_P)
#define SFTN SFT_T(KC_N)
#define SFTL SFT_T(KC_L)

#define ALLP ALT_T(KC_LBRC)
#define SFRP SFT_T(KC_RBRC)

#define SF4 SFT_T(KC_4)
#define AL5 ALT_T(KC_5)
#define GUI6 GUI_T(KC_6)
#define CMIN CTL_T(KC_MINUS)
#define CZ LCTL(KC_Z)
#define CX LCTL(KC_X)
#define CC LCTL(KC_C)
#define CV LCTL(KC_V)
#define TDQMIN TD(TD_Q_MIN)
#define TDSLBS TD(TD_S_BSL)
#define TDPLNX TD(TD_PL_NX)
#define TDSTPR TD(TD_ST_PR)
#define TDLCCA TD(TD_LC_CA)
#define TDF4AF4 TD(TD_F4_ALTF4)
#define TDCSCL TD(TD_C_SCL)
#define TDDCL TD(TD_D_CL)
#define TOGGLE TD(TD_TOGGL)
#define VD_RGHT LGUI(LCTL(KC_RGHT))
#define VD_LEFT LGUI(LCTL(KC_LEFT))
#define xxxxx KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
  KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     TDSTPR,   TDPLNX,   KC_J,     KC_L,      KC_U,     KC_Y,     TDQMIN, \
  CTLA,     GUIR,     ALTS,     SFTT,     KC_G,     KC_BRID,  KC_BRIU,  KC_M,     SFTN,      ALTE,     GUII,     CTLO, \
  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,     KC_VOLD,  KC_VOLU,  KC_K,     KC_H,      TDCSCL,   TDDCL,    TDSLBS, \
  VD_LEFT,    xxxxx,    MSESC,    LOWBSP,   KC_LSFT,  KC_DEL,   KC_TAB,   KC_SPC,   RAISENT,   FNTAB,    xxxxx,    VD_RGHT \
),

[_LOWER] = LAYOUT_planck_grid(
  KC_GRV,   xxxxx,    KC_LPRN,  KC_RPRN,  xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_7,     KC_8,     KC_9,     KC_EQL, \
  TDLCCA, 	KC_LWIN,  ALLP,     SFRP,     KC_TAB,   xxxxx,    xxxxx,    xxxxx,    SF4,      AL5,      GUI6,     CMIN, \
  CZ,       CX,       CC,       KC_PSCR,  CV,       xxxxx,    xxxxx,    xxxxx,    KC_1,     KC_2,     KC_3,     KC_SLSH,  \
  xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_0,     xxxxx,    KC_DOT,   xxxxx  \
),

[_RAISE] = LAYOUT_planck_grid(
	DIVVY,    F_CHR,    F_WIN,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_PGUP,	KC_HOME,  KC_UP,    KC_END,   xxxxx,  \
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,    xxxxx,    KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,	KC_INS,  \
	xxxxx,  	KC_X,     xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,   	xxxxx,    \
	xxxxx,  	xxxxx,    _______,  _______,  xxxxx,    KC_TAB,   xxxxx,  	KC_SPC,    xxxxx,    xxxxx,    xxxxx,  	xxxxx  \
),

[_FUNCT] = LAYOUT_planck_grid(
	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_F7,    KC_F8,    KC_F9,    KC_F10,	\
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,  	xxxxx,    xxxxx,    TDF4AF4,  KC_F5,    KC_F6,    KC_F11,	\
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    KC_F1,    KC_F2,    KC_F3,    KC_F12,	\
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx	\
),

[_MOUSE] = LAYOUT_planck_grid(
	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	KC_WH_U,  KC_WH_L,  KC_MS_U,  KC_WH_R,  xxxxx,   \
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,    xxxxx,  	KC_WH_D,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_LCTL, \
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,   \
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_BTN1,  KC_BTN2,  xxxxx,    xxxxx,    xxxxx \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    QWERTY,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  xxxxx,  xxxxx,  xxxxx,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
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
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
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

void encoder_update(bool clockwise) {
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
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
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
