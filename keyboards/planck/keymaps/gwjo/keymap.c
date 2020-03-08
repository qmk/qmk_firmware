/* Copyright 2020 Gareth Owen
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
  _LOWER,
  _RAISE,
  _PLOVER,
  _NAV,
  _GUI,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  NAV,
  GUI,
  EXT_PLV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define GUI_L LT(_GUI, KC_LCBR)
#define GUI_R LT(_GUI, KC_RCBR)
#define NAV_SEM LT(_NAV, KC_SCLN)

#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_ENT RCTL_T(KC_ENT)
#define MEH_L   MEH_T(KC_RBRC)
#define MEH_R   MEH_T(KC_LBRC)

/* Command/Window left/right/up/down */
#define G_LEFT  LGUI(KC_LEFT)
#define G_RIGHT LGUI(KC_RIGHT)
#define G_UP    LGUI(KC_UP)
#define G_DOWN  LGUI(KC_DOWN)

/* Alt left/right/up/down */
#define A_LEFT  LALT(KC_LEFT)
#define A_RIGHT LALT(KC_RGHT)
#define A_DOWN  LALT(KC_DOWN)
#define A_UP    LALT(KC_UP)

// Window manager keys
#define WM_FULL LALT(LGUI(KC_F))
#define WM_NEXT LCTL(LALT(LGUI(KC_RGHT)))
#define WM_PREV LCTL(LALT(LGUI(KC_LEFT)))
#define WM_NW   LCTL(LGUI(KC_LEFT))
#define WM_N    LALT(LGUI(KC_UP))
#define WM_NE   LCTL(LGUI(KC_RGHT))
#define WM_E    LALT(LGUI(KC_RGHT))
#define WM_SE   S(LCTL(LGUI(KC_RGHT)))
#define WM_S    LALT(LGUI(KC_DOWN))
#define WM_SW   S(LCTL(LGUI(KC_LEFT)))
#define WM_W    LALT(LGUI(KC_LEFT))
#define WM_CNTR LALT(LGUI(KC_C))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *                ,-----------------------------------------------------------------------------------.
 *                | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  "   |
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 * Tap for Esc -- | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | NAV  | Ctrl | -- Tap for Enter, NAV tap for ;
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *   Tap for ( -- | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift | -- Tap for )
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *   Tap for [ -- |  GUI | Meh  | Alt  | Win  |LOWER |    Space    |RAISE | Win  | Alt  | Meh  | GUI  | -- Tap for ]
 *                `-----------------------------------------------------------------------------------'
 *                          /                                                             /
 *     Tap for ] [ --------'-------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
    CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NAV_SEM, CTL_ENT,
    KC_LSPO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
    GUI_L,      MEH_L,   KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, MEH_R,   GUI_R
),


/* Colemak
 *                ,-----------------------------------------------------------------------------------.
 *                | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  | NAV  |  "   | -- Tap NAV for ;
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 * Tap for Esc -- | Ctrl |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  | Ctrl | -- Tap for Enter
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *   Tap for ( -- | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Shift | -- Tap for )
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *   Tap for [ -- |  GUI | Meh  | Alt  | Win  |LOWER |    Space    |RAISE | Win  | Alt  | Meh  | GUI  | -- Tap for ]
 *                `-----------------------------------------------------------------------------------'
 *                          /                                                             /
 *     Tap for ] [ --------'-------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    NAV_SEM, KC_QUOT,
    CTL_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    CTL_ENT,
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
    GUI_L,   MEH_L,   KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, MEH_R,   GUI_R
),

/* Dvorak
 *                ,-----------------------------------------------------------------------------------.
 *                | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 * Tap for Esc -  | Ctrl |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  | Ctrl | -- Tap for Enter
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *   Tap for ( -- | Shift| NAV  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift | -- Tap for )
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *   Tap for [ -- |  GUI | Meh  | Alt  | Win  |LOWER |    Space    |RAISE | Win  | Alt  | Meh  | GUI  | -- Tap for ]
 *                `-----------------------------------------------------------------------------------'
 *                          /                                                             /
 *     Tap for ] [ --------'-------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    CTL_ESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    CTL_ENT,
    KC_LSPO, NAV_SEM, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSPC,
    GUI_L,   MEH_L,   KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, MEH_R,   GUI_R
),

/* Lower - numeric layer
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  #   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   -  |   =  |   `  |   \  |   :  |      |      |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |  Backspace  |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_HASH,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_MINS, KC_EQL,  KC_GRV,  KC_BSLS, KC_COLN, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, _______,
    _______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______
),


/* Raise - symbol layer
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F11 |  F12 |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |  #   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   _  |   +  |   ~  |   |  |   :  |      |      |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |   Delete    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_HASH,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_UNDS, KC_PLUS, KC_TILD, KC_PIPE, KC_COLN, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, _______,
    _______, _______, _______, _______, _______, KC_DEL,  KC_DEL,  _______, _______, _______, _______, _______
),

/* Plover layer (http://opensteno.org)
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
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Navigation layer
 *                ,-----------------------------------------------------------------------------------.
 *                |      |      |      |      |      |      |      |      |      |      |      |      |
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *                |      |      | Home | PgUp | PgDn |  End | Left | Down |  Up  |Right |      |      |
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *                |      |      |G-Left| G-Up |G-Down|G-Rght|A-Left|A-Down| A-Up |A-Rght|      |      |
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *                |      |      |      |      |      |             |      |      |      |      |      |
 *                `-----------------------------------------------------------------------------------'
 */
  [_NAV] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
    _______, XXXXXXX, G_LEFT,  G_UP,    G_DOWN,  G_RIGHT, A_LEFT,  A_DOWN,  A_UP,    A_RIGHT, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

/* GUI (window management/mouse/media controls) layer
 *
 *         Mouse keys -----/```````````````````\                       /```````````````````\----- Window manager
 *                ,-----------------------------------------------------------------------------------.
 *                |      | MsB2 | MsUp | MsB1 | MsWU |      |      | Prev |  NW  |  N   |  NE  |      |
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *                |      | Ms L | Ms D | Ms R | MsWD |      |      | Full |   W  |Center|   E  |      |
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *                |      | Undo |  Cut | Copy | Paste| Ins  |      | Next |  SW  |  S   |  SE  |      |
 *                |------+------+------+------+------+------+------+------+------+------+------+------|
 *                |      | Prev | Play | Next | Brig-|    Sleep    |Brig+ | Mute | Vol- | Vol+ |      |
 *                `-----------------------------------------------------------------------------------'
 *                           \___ Media ___/      \___ Screen/sleep __/       \___ Volume __/
 */
  [_GUI] = LAYOUT_planck_grid(
    _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_D, XXXXXXX, XXXXXXX, WM_PREV, WM_NW,   WM_N,    WM_NE,   _______,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, XXXXXXX, XXXXXXX, WM_FULL, WM_W,    WM_CNTR, WM_E,    _______,
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_INS,  XXXXXXX, WM_NEXT, WM_SW,   WM_S,    WM_SE,   _______,
    _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_SLEP, KC_SLEP, KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, _______
  ),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |Brite |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, BACKLIT, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
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
