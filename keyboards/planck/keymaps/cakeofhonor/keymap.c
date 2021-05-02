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

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float music_song[][2]      = SONG(MUSIC_ON_SOUND);
  float music_gb_song[][2]   = SONG(MUSIC_OFF_SOUND);
#endif

enum planck_layers {
  /*Default Layers*/
  _QWERTY,
  _COLEMAK,
  _DVORAK,

  /*Modes*/
  _MUSIC,
  _PLOVER,

  /*Mods*/
  _LOWER,
  _RAISE,
  _LEFT,
  _RIGHT,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,

  /*Personal*/
  CAKE_MUSIC,
  CAKE_EXT_MSC,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | MUSIC|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Lower|    Space    |    Space    |Raise | Left |Right | Down |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
              CAKE_MUSIC,    KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,   KC_BSPC,
       LT(_LEFT, KC_TAB),    KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_H,    KC_J,    KC_K,     KC_L, KC_SCLN,   KC_QUOT,
    MT(MOD_LSFT, KC_ESC),    KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M, KC_COMM,   KC_DOT, KC_SLSH,    KC_ENT,
                 KC_LCTL, KC_LGUI, KC_LALT,   LOWER,  KC_SPC,   KC_SPC,  KC_SPC,  KC_SPC,   RAISE,  KC_DOWN,   KC_UP,   KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | MUSIC|   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Lower|    Space    |    Space    |Raise | Left |Right | Down |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
              CAKE_MUSIC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
       LT(_LEFT, KC_TAB),    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
    MT(MOD_LSFT, KC_ESC),    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
                 KC_LCTL, KC_LGUI, KC_LALT,   LOWER,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,   RAISE, KC_DOWN,   KC_UP, KC_RGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | MUSIC|   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    CAKE_MUSIC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
    KC_LCTL, KC_LGUI, KC_LALT,   LOWER,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,   RAISE, KC_DOWN,   KC_UP, KC_RGHT
),

/* Music
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      | Play |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Mute |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |     Prev    |     Next    |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MUSIC] = LAYOUT_planck_grid(
    CAKE_EXT_MSC, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______, _______, _______,
    _______, _______, _______,   LOWER, KC_MPRV, KC_MPRV, KC_MNXT, KC_MNXT,   RAISE, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |    LBrac    |    RBrac    | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
     KC_TILD,   KC_EXLM,     KC_AT,   KC_HASH,    KC_DLR,   KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN,    KC_DEL,
      KC_ESC,     KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,   KC_UNDS,   KC_PLUS,   KC_LCBR,   KC_RCBR,   KC_PIPE,
     _______,     KC_F7,     KC_F8,     KC_F9,    KC_F10,    KC_F11,    KC_F12,S(KC_NUHS),S(KC_NUBS),   KC_HOME,    KC_END,   _______,
     _______,   _______,   _______,   _______,   KC_LBRC,   KC_LBRC,   KC_RBRC,   KC_RBRC,   _______,   _______,   _______,   _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |    SColon    |    Quote   |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
     KC_GRV,    KC_1,    KC_2,    KC_3,     KC_4,     KC_5,     KC_6,     KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
    _______,   KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,    KC_F6,  KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
    _______,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, KC_MINUS, KC_MINUS, KC_EQUAL, KC_EQUAL, _______, _______, _______, _______
),

/* Left
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  UP  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | LEFT | DOWN | RIGHT|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |    SColon   |    Quote    |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LEFT] = LAYOUT_planck_grid(
    _______, _______,   KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,KC_MINUS,KC_MINUS,KC_EQUAL,KC_EQUAL, _______, _______, _______, _______
),

/* Right
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |    Space    |    Space    |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RIGHT] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |   A  |   O  |             |             |   E  |   U  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, KC_C,    KC_V, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_N,    KC_M, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * | Reset|      |Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |    Space    |    Space    |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
         RESET,   _______,     DEBUG,   RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_HUD,   RGB_SAI,   RGB_SAD,   RGB_VAI,   RGB_VAD,    KC_DEL,
       _______,   _______,    MU_MOD,     AU_ON,    AU_OFF,   AG_NORM,   AG_SWAP,    QWERTY,   COLEMAK,    DVORAK,    PLOVER,   _______,
       _______,    MUV_DE,    MUV_IN,     MU_ON,    MU_OFF,     MI_ON,    MI_OFF,   TERM_ON,  TERM_OFF,   _______,   _______,   _______,
       _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______
)

};

/////////////////
//  Functions  //
/////////////////
void CAKE_RGBL_check(layer_state_t state) {
/*Cycles through layers and toggles RGB Lighting Layers based on state*/
  int i;
  for (i = 0; i <= sizeof(rgblight_layers); ++i) {
    rgblight_set_layer_state(i, layer_state_cmp(state, i));
  }
}

void CAKE_RGBL_checkself(void) {
/*Cycles through layers and toggles RGB Lighting Layers*/
  int i;
  for (i = 0; i <= sizeof(rgblight_layers); ++i) {
    if (layer_state_cmp(default_layer_state, i)) {
    //Do nothing if on default layer
    } else {
      rgblight_set_layer_state(i, layer_state_is(i));
    }
  }
}

////////////
//  MUSE  //
////////////
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

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

/////////////////
//  Key-Press  //
/////////////////
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /*QWERTY*/
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    /*COLEMAK*/
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;

    /*DVORAK*/
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;

    /*BACKLIT*/
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

    /*PLOVER*/
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_off(_MUSIC);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);

        CAKE_RGBL_checkself();
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);

        CAKE_RGBL_checkself();
      }
      return false;
      break;

    /*MUSIC*/
    case CAKE_MUSIC:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(music_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_off(_PLOVER);
        layer_on(_MUSIC);

        CAKE_RGBL_checkself();
      }
      return false;
      break;
    case CAKE_EXT_MSC:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(music_gb_song);
        #endif
        layer_off(_MUSIC);

        CAKE_RGBL_checkself();
      }
      return false;
      break;
  }
  return true;
}

///////////////
//  Encoder  //
///////////////
void encoder_update(bool clockwise) {
  /*Muse Mode*/
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

  /*Music Layer*/
  } else if (IS_LAYER_ON(_MUSIC)) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }

  /*Default Layer*/
  } else {
    if (clockwise) {
      if ((get_mods() & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
        /*Redo*/
        register_code(KC_LSFT);
        tap_code(KC_Z);
        unregister_code(KC_LSFT);

      } else {
        /*Scroll*/
        #ifdef MOUSEKEY_ENABLE
          tap_code(KC_MS_WH_DOWN);
        #else
          tap_code(KC_PGDN);
        #endif

      }
    } else {
      if ((get_mods() & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
        /*Undo*/
        tap_code(KC_Z);

      } else {
        /*Scroll*/
        #ifdef MOUSEKEY_ENABLE
          tap_code(KC_MS_WH_UP);
        #else
          tap_code(KC_PGUP);
        #endif

      }
    }
  }
}

///////////
//  RGB  //
///////////
const uint8_t CAKE_HSV_Value = 130;
#define CAKE_HSV_WHITE        0, 0, CAKE_HSV_Value
#define CAKE_HSV_PURPLE       191, 255, CAKE_HSV_Value
#define CAKE_HSV_BLUE         170, 255, CAKE_HSV_Value
#define CAKE_HSV_CORAL        11, 176, CAKE_HSV_Value
#define CAKE_HSV_CHARTREUSE   64, 255, CAKE_HSV_Value

const rgblight_segment_t PROGMEM CAKE_RGBL_QWERTY[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, CAKE_HSV_WHITE}
);

const rgblight_segment_t PROGMEM CAKE_RGBL_COLEMAK[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, CAKE_HSV_PURPLE}
);

const rgblight_segment_t PROGMEM CAKE_RGBL_DVORAK[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, CAKE_HSV_BLUE}
);

const rgblight_segment_t PROGMEM CAKE_RGBL_MUSIC[] = RGBLIGHT_LAYER_SEGMENTS(
/*Lights 9 LEDs starting at LED 0 chartreuse on _MUSIC layer*/
    {0, 9, CAKE_HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM CAKE_RGBL_PLOVER[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, CAKE_HSV_CORAL}
);

const rgblight_segment_t* const PROGMEM CAKE_RGBL_LAYERS[] = RGBLIGHT_LAYERS_LIST(
/*Define the array of layers. Later layers take precedence*/
    CAKE_RGBL_QWERTY, //Lowest Layer
    CAKE_RGBL_COLEMAK,
    CAKE_RGBL_DVORAK,
    CAKE_RGBL_MUSIC,
    CAKE_RGBL_PLOVER
);

//bool led_update_user(led_t led_state) {
//Called every time LED changes.
//rgblight_set_layer_state(0, led_state.caps_lock);
//return true;
//}

layer_state_t default_layer_state_set_user(layer_state_t state) {
/*Changes everytime the Default Layer is called.*/
  CAKE_RGBL_check(state);
  return state;
}

//////////////////
//  Initiation  //
//////////////////
void matrix_init_user(void) {
}

void keyboard_post_init_user(void) {
  rgblight_layers = CAKE_RGBL_LAYERS; //Enables LED Layers
  CAKE_RGBL_check(default_layer_state);
}

/////////////////////////
// Layer State Change  //
/////////////////////////
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return state;
}
