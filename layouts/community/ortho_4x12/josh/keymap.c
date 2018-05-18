// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include QMK_KEYBOARD_H

#include "action_layer.h"
#include "eeconfig.h"

#ifdef AUDIO_ENABLE
#include "audio.h"
#include "clicky.h"
#endif

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

// keycodes custom to this keymap:
enum planck_keycodes {
  QWERTY = SAFE_RANGE
};

// clicky state:
#ifdef AUDIO_ENABLE
bool clicky_enable = false;
const float clicky_freq_default = 440.0f; // standard A tuning
const float clicky_freq_min = 65.0f; // freqs below 60 are buggy?
const float clicky_freq_max = 2500.0f; // arbitrary
const float clicky_freq_factor = 1.18921f; // 2^(4/12), a major third
const float clicky_freq_randomness = 0.15f; // arbitrary
float clicky_freq = 440.0f;
float clicky_song[][2]  = {{440.0f, 3}, {440.0f, 1}}; // 3 and 1 --> durations
#endif

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | '    |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | Del  | GUI  | Alt  |Lower |HyprSp|Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_ESC,  KC_DEL,  KC_LGUI, KC_LALT, LOWER, MT(MOD_HYPR, KC_SPC), KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY  \
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |Clicky|ClkDn |ClkUp |ClkRst|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,                  \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,                 \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, BL_TOGG, BL_DEC,  BL_INC,  BL_BRTG,                 \
  _______, _______, _______, _______, _______, _______, _______, _______, CLICKY_TOGGLE, CLICKY_DOWN, CLICKY_UP, CLICKY_RESET \
),

}; // end keymaps

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  return MACRO_NONE;
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // handle the _ADJUST layer and custom keycodes:
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

#ifdef AUDIO_ENABLE
    case CLICKY_TOGGLE:
      if (record->event.pressed) {
        clicky_toggle();
      }
      return false;
      break;
    case CLICKY_DOWN:
      if (record->event.pressed) {
        clicky_down();
      }
      return false;
      break;
    case CLICKY_UP:
      if (record->event.pressed) {
        clicky_up();
      }
      return false;
      break;
    case CLICKY_RESET:
      if (record->event.pressed) {
        clicky_reset();
      }
      return false;
      break;
#endif
  } // end switch case over custom keycodes

#ifdef AUDIO_ENABLE
  if (record->event.pressed) {
    clicky_play();
  }
#endif

  return true;
}


// clicky implementation:
#ifdef AUDIO_ENABLE
void clicky_play(void) {
  if (!clicky_enable) {
    return;
  }

  clicky_song[0][0] = 2.0f * clicky_freq * (1.0f + clicky_freq_randomness * ( ((float)rand()) / ((float)(RAND_MAX)) ) );
  clicky_song[1][0] = clicky_freq * (1.0f + clicky_freq_randomness * ( ((float)rand()) / ((float)(RAND_MAX)) ) );
  #ifdef AUDIO_ENABLE
    PLAY_SONG(clicky_song);
  #endif
}

void clicky_toggle(void) {
  clicky_enable = !clicky_enable;
  clicky_play();
}

void clicky_reset(void) {
  clicky_freq = clicky_freq_default;
  clicky_play();
}

void clicky_up(void) {
  float new_freq = clicky_freq * clicky_freq_factor;
  if (new_freq < clicky_freq_max) {
    clicky_freq = new_freq;
  }
  clicky_play();
}

void clicky_down(void) {
  float new_freq = clicky_freq / clicky_freq_factor;
  if (new_freq > clicky_freq_min) {
    clicky_freq = new_freq;
  }
  clicky_play();
}
#endif
