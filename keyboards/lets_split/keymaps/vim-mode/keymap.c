#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// keys in multiple locations:
//  - parenteses in both raise and lower
//  - asterix in raise and twice on lower (normal and numpad)
//  - minus/plus twice on lower (normal and numpad)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| PrtSc| GUI  | Alt  |Lower | Tab  |Space |Raise | VolDn| VolUp| Pl/Ps| Next |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTRL,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  ADJUST,  KC_PSCR, KC_LGUI, KC_LALT, LOWER,   KC_TAB,  KC_SPC,  RAISE,   KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |   *  |   (  |   )  |      |      |   7  |   8  |   9  |   *  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |   _  |   +  |   {  |   }  |      |      |   4  |   5  |   6  |   -  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NumLk|   -  |   =  |   [  |   ]  |      |      |   1  |   2  |   3  |   +  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | Alt  |      |             |      |   0  |   .  | Enter|      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, _______, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_DEL,  \
  KC_DEL,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_BSLS, \
  KC_NLCK, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______, \
  _______, _______, _______, KC_LALT, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PENT, _______  \
),

/* Raise: featuring vim-style hjkl arrow keys
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  | Left | Down |  Up  |Right |      |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 | Home | PgUp | PgDn | End  |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F11 |  F12 |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______, KC_PIPE, \
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______, _______, \
  _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      | Prev | Pl/Ps| Next |      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Mute | VolDn| VolUp|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  _______, RESET,   _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_DEL,  \
  _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    // case COLEMAK:
    //   if (record->event.pressed) {
    //     #ifdef AUDIO_ENABLE
    //       PLAY_SONG(tone_colemak);
    //     #endif
    //     persistent_default_layer_set(1UL<<_COLEMAK);
    //   }
    //   return false;
    //   break;
    // case DVORAK:
    //   if (record->event.pressed) {
    //     #ifdef AUDIO_ENABLE
    //       PLAY_SONG(tone_dvorak);
    //     #endif
    //     persistent_default_layer_set(1UL<<_DVORAK);
    //   }
    //   return false;
    //   break;
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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

