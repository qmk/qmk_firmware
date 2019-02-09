#include QMK_KEYBOARD_H
#include "muse.h"


//mod tap keys
#define SHFZ MT(MOD_LSFT, KC_Z)
#define SHFS MT(MOD_RSFT, KC_SLSH)

enum preonic_layers {
  _QWERTY,
  _SYMBOLS,
  _NAVIG,
  _GAME,
  _ADJUST
};

enum preonic_keycodes {
  //layer keycodes
  QWERTY = SAFE_RANGE,
  SYMBOLS,
  NAVIG,
  GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |Delete|Delete|   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |* Q   |   W  |   E  |   R  |   T  |   [  |   ]  |   Y  |   U  |   I  |   O  |  P   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  A   |   S  |   D  |   F  |   G  |   (  |   )  |   H  |   J  |   K  |   L  |* ;   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Z   |   X  |   C  |   V  |   B  |   {  |   }  |   N  |   M  |   ,  |   .  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |NAVIG |   Backspace |    Space    |SYMBL |VOL-  |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_2x2u( \
  KC_1   , KC_2   , KC_3   , KC_4 , KC_5   , KC_DEL ,  KC_DEL ,  KC_6  , KC_7   , KC_8,    KC_9   , KC_0   , \
  KC_Q   , KC_W   , KC_E   , KC_R , KC_T   , KC_LBRC,  KC_RBRC,  KC_Y  , KC_U   , KC_I,    KC_O   , KC_P   , \
  KC_A   , KC_S   , KC_D   , KC_F , KC_G   , KC_LPRN,  KC_RPRN,  KC_H  , KC_J   , KC_K,    KC_L   , KC_SCLN, \
  SHFZ   , KC_X   , KC_C   , KC_V , KC_B   , KC_LCBR,  KC_RCBR,  KC_N  , KC_M   , KC_COMM, KC_DOT , SHFS   , \
  KC_LCTL, KC_LGUI, KC_LALT, NAVIG,      KC_BSPC    ,       KC_SPC     , SYMBOLS, KC_VOLD, KC_VOLU, KC_ESC   \
),

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |  `   |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  ~   |   @  |   #  |   *  |   %  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  !   |      |   -  |   =  |   +  |   ^  |   $  |   |  |   &  |   `  |   '  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  \   |      |      |   _  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |   Enter     |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = LAYOUT_preonic_2x2u( \
  KC_GRV , KC_EXLM, KC_AT,   KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TILD, KC_AT  , KC_HASH, KC_ASTR, KC_PERC, _______, _______, _______, _______, _______, _______, _______, \
  KC_EXLM, _______, KC_MINS, KC_EQL , KC_PLUS, KC_CIRC, KC_DLR , KC_PIPE, KC_AMPR, KC_GRV , KC_QUOT, KC_DQUO, \
  KC_BSLS, _______, _______, KC_UNDS, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, KC_ENT          , _______         , _______, _______, _______, _______  \
),

/* Navigation
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | PGdn | PGup |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Left | Down |  Up  | Right|Caps  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |     Tab     |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVIG] = LAYOUT_preonic_2x2u( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_CAPS, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______         , KC_TAB          , _______, _______, _______, _______  \
),

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  Q   |  W   |  E   |  R   |  T   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  A   |  S   |  D   |  F   |  G   |      |      |      |      |  up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |  Z   |  X   |  C   |  V   |  B   |      |      |      | left | down |right |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |     Space   |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_preonic_2x2u( \
  KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , XXXXXXX, \
  XXXXXXX, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP  , KC_ENT , \
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, \
  KC_RCTL, XXXXXXX, KC_RALT, NAVIG  , KC_SPC          , XXXXXXX         , SYMBOLS, XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Gaming|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_2x2u( \
  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9,   KC_F10 , KC_F11 , KC_F12 , \
  _______, RESET  , DEBUG  , _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL , \
  _______, _______, MU_MOD , AU_ON  , AU_OFF , AG_NORM, AG_SWAP, QWERTY , GAME   , _______, _______, _______, \
  _______, MUV_DE , MUV_IN , MU_ON  , MU_OFF , MI_ON  , MI_OFF , _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______         , _______         , _______, _______, _______, _______  \
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case GAME:
            if (record-> event.pressed) {
                set_single_persistent_default_layer(_GAME);
            }
            return false;
            break;
        case SYMBOLS:
          if (record->event.pressed) {
            layer_on(_SYMBOLS);
            update_tri_layer(_SYMBOLS, _NAVIG, _ADJUST);
          } else {
            layer_off(_SYMBOLS);
            update_tri_layer(_SYMBOLS, _NAVIG, _ADJUST);
          }
          return false;
          break;
        case NAVIG:
          if (record->event.pressed) {
            layer_on(_NAVIG);
            update_tri_layer(_SYMBOLS, _NAVIG, _ADJUST);
          } else {
            layer_off(_NAVIG);
            update_tri_layer(_SYMBOLS, _NAVIG, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_NAVIG)) {
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
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
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
    case NAVIG:
    case SYMBOLS:
      return false;
    default:
      return true;
  }
}
