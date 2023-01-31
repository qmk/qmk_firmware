#include QMK_KEYBOARD_H


extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
// #define _COLEMAK 1
// #define _DVORAK 2
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16



enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  // COLEMAK,
  // DVORAK,
  LOWER,
  RAISE,
  ADJUST,
};

/*
// Tap dance declerations
enum {
  TD_GRV_TILD = 0,
};

// Tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GRV_TILD] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | ` ~  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Rshift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Lalt  | GUI | Esc  |Lower |KC_SPC |Enter |Raise | [cmd|] alt |= Hypr|   -  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, \
  KC_LCTL, KC_LALT, KC_LGUI, KC_ESC, TG(_LOWER),  LT(_ADJUST, KC_SPC),  KC_ENT,  TG(_RAISE),   MT(MOD_RGUI, KC_LBRC), MT(MOD_RALT, KC_RBRC), MT(MOD_HYPR, KC_EQL), KC_MINS \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bspc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_ESC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,_______,_______,_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MFFD, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MFFD, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |  up  |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      | left | down |right |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |   %  |   `  |   ~  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |AShftD|AShftU|REPORT|      |      |             |  [   |  ]   |   -  |   =  |  \   |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, KC_LEFT,  KC_DOWN, KC_RGHT, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PERC, KC_GRV, KC_TILD, \
  AS_DOWN, AS_UP,   AS_RPT,  _______, _______, _______, _______, KC_RBRC, KC_LBRC, KC_MINS, KC_EQL, KC_BSLS \
)


};

/* #ifdef AUDIO_ENABLE
* float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
* float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
* float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif */


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
  }
  return true;
};

#define rgblight_set_blue        rgblight_sethsv (0xFF,  0xFF, 0xFF);
#define rgblight_set_red         rgblight_sethsv (0x00,  0xFF, 0xFF);
#define rgblight_set_green       rgblight_sethsv (0x78,  0xFF, 0xFF);
#define rgblight_set_orange      rgblight_sethsv (0x1E,  0xFF, 0xFF);
#define rgblight_set_teal        rgblight_sethsv (0xC3,  0xFF, 0xFF);
#define rgblight_set_magenta     rgblight_sethsv (0x12C, 0xFF, 0xFF);
#define rgblight_set_yellow      rgblight_sethsv (0x3C,  0xFF, 0xFF);
#define rgblight_set_purple      rgblight_sethsv (0x10E, 0xFF, 0xFF);
#define rgblight_set_white       rgblight_sethsv (0x00,  0x00, 0xFF);

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();
  if (rgb_layer_change) {
    switch (get_highest_layer(state)) {
    case _RAISE:
      rgblight_set_orange;
      rgblight_mode(5);
      break;
    case _LOWER:
      rgblight_set_teal;
      rgblight_mode(5);
      break;
    case _ADJUST:
      rgblight_set_purple;
      rgblight_mode(23);
      break;
    default:
      if (default_layer & (1UL << _COLEMAK)) {
        rgblight_set_magenta;
      }
      else if (default_layer & (1UL << _DVORAK)) {
        rgblight_set_green;
      }
      else {
        rgblight_set_blue;
      }
      rgblight_mode(1);
      break;
    }
  }
#endif
  return state;
}
