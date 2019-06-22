#include QMK_KEYBOARD_H

#include "open_close_parenthese.c"
#include "open_close_parenthese_mods.c"
#include "sendstring_french.h"
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
  MAIL1,
  MAIL2,
  MAKE

};
enum {
  ARO = 0,
  WLESS = 1,


};

qk_tap_dance_action_t tap_dance_actions[] = {

  [ARO]  = ACTION_TAP_DANCE_DOUBLE(FR_A, LCA(KC_0)),
  [WLESS]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, FR_LESS),
//   [OPEN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,open_finished, open_reset),
//  [CLOSE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,close_finished, close_reset),
  [TD_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,td_a_finished, td_a_reset),
  [TD_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,td_e_finished, td_e_reset),
[SHIFT_PAR_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,shift_o_finished, shift_o_reset),
[CTRL_BRACK_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctrl_o_o_finished, ctrl_o_o_reset),
[ALT_CURL_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_o_finished, alt_o_reset),
[SHIFT_PAR_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,shift_c_finished, shift_c_reset),
[CTRL_BRACK_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctrl_c_c_finished, ctrl_c_c_reset),
[ALT_CURL_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_c_finished, alt_c_reset)
// Other declarations would go here, separated by commas, if you have KCeZ
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   A  |   Z  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   Q  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   M  | ENT  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   W  |   X  |   C  |   V  |   B  |   N  |   ,  |   ;  |   :  |  Up  |   !  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | GUI  | Alt  | Lower |Space |Space |Raise | AltGR| Left | Down |Right|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_TAB,  TD(TD_A),     KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,           KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,         KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,           KC_L,    KC_SCLN, KC_SLSH, \
  KC_LSFT, KC_Z,         KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM,        KC_DOT,  KC_UP,   KC_ENT, \
  ADJUST,  KC_LCTL,      KC_LGUI, KC_LALT,  LOWER,  KC_SPC,           KC_SPC,  RAISE,   TD(ALT_CURL_C), KC_LEFT, KC_DOWN, KC_RGHT \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_LOWER] = LAYOUT_ortho_4x12( \
  KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          KC_KP_MINUS, KC_KP_7, KC_KP_8, KC_KP_9,    KC_KP_DOT,   KC_KP_SLASH,  \
  MAIL1,     MAIL2,   _______, _______, _______, _______,        KC_KP_PLUS,  KC_KP_4, KC_KP_5, KC_KP_6,    KC_KP_EQUAL, _______,    \
  KC_LSHIFT, FR_LESS, _______, _______, _______, _______,        KC_KP_0,     KC_KP_1, KC_KP_2, KC_KP_3,    KC_KP_COMMA, _______, \
  _______,   _______, _______, _______, _______, _______,        _______,     _______, _______, _______,    _______,     _______

),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,       KC_7,          KC_8,         KC_9,    KC_0,    KC_MPLY, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_5,       KC_MINS,       ALGR(KC_4),   KC_LBRC, KC_RBRC,   KC_MNXT, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,          ALGR(KC_5), ALGR(KC_MINS), ALGR(KC_EQL), KC_QUOT, KC_PGUP,   KC_MPRV, \
  _______, _______, _______, _______, _______, _______,         _______,    _______,       _______,      KC_HOME, KC_PGDN,   KC_END \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,     KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  MAKE,    RESET,   _______, AU_ON,   AU_OFF,  AG_NORM,          KC_INSERT, KC_HOME, KC_PGUP, KC_MINS, KC_EQL,  KC_MNXT, \
  _______, _______, _______, _______, _______, _______,          KC_DEL,    KC_END,  KC_PGDN, _______, _______, KC_MPRV, \
  _______, _______, _______, _______, _______, _______,          _______,   _______, KC_RALT, KC_VOLD, KC_VOLU, _______ \
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
       case MAIL1:
     if (record->event.pressed) {
        SEND_STRING("sydneywriter@gmail.com" );

      } else {
        // when keycode QMKURL is released
      }
      break;

      case MAIL2:
     if (record->event.pressed) {
        SEND_STRING("adrienlefalher.pro@gmail.com");

      } else {
        // when keycode QMKURL is released
      }
      break;

     case MAKE:
     if (record->event.pressed) {
        SEND_STRING("make keebio/êlevinson:adrienLF_french:dfu");

      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}
