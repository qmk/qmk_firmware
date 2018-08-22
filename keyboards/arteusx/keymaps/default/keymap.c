// Note: this is a modification of that_canadian's config, albeit heavily modified.
// this layout turns your left thumb cluster into something more familiar.

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16
#define LAYOUT( \
  L00, L01, L02, L03, L04, L05,      L06,   L07, L08, L09, L10, L11, L12, \
  L13, L14, L15, L16, L17, L18,      L19,   L20, L21, L22, L23, L24, L25, \
  L26, L27, L28, L29, L30, L31,      L32,   L33, L34, L35, L36, L37, L38, \
                      L39, L40,      L41,   L42, L43 \
  ) \
  { \
    {      L00, L01, L02, L03, L04, L05,        L06,    L07, L08, L09, L10, L11, L12 }, \
    {      L13, L14, L15, L16, L17, L18,        L19,    L20, L21, L22, L23, L24, L25 }, \
    {      L26, L27, L28, L29, L30, L31,        L32,    L33, L34, L35, L36, L37, L38 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, L39, L40,     L41,    L42, L43} \
  }

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define ESC KC_ESC


// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------------.     ,------.     ,-----------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R   |  T  |    | PLY  |     |   Y  |   U  |   I  |   O  |   P  | BSP  |
 * |------+------+------+------+------+------|    |--++--'     |------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   D  |   F  |  G   |    | MUTE |     |   H  |   J  |   K  |   L  |   ;  | ENT  |
 * |------+------+------+------+------+------|    `------'     |------+------+------+------+------+------|
 * | LSFT |   Z  |   X  |   C  |   V  |  B   |          ||     |   N  |   M  |   ,  |   .  |   /  | RSFT |
 * `----------------------------------------',0---------------.`----------------------------------+------'
 *                                           | GUI/Tab | RAISE |
 *                                           `-----------------'
 *                               ,---------------.         ,---------------.
 *                               |SFT/ESC | BKSPC|         | RAISE | LOWER |
 *                               `---------------'         `---------------.
 */
[_QWERTY] = LAYOUT( \
  ESC,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_MPLY,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  GUI_T(KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_MUTE,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
  KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_BSPC,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                          SFT_T(KC_ESC),    KC_LGUI,              RAISE,   KC_SPC,  LOWER                                    \
),
/* RAISE
 *
 * ,----------------------------------------.     ,------.     ,-----------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R   |  T  |    | PLY  |     |   Y  |   U  |   I  |   O  |   P  | BSP  |
 * |------+------+------+------+------+------|    |--++--'     |------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   D  |   F  |  G   |    | MUTE |     |   H  |   J  |   K  |   L  |   ;  | ENT  |
 * |------+------+------+------+------+------|    `------'     |------+------+------+------+------+------|
 * | LSFT |   Z  |   X  |   C  |   V  |  B   |          ||     |   N  |   M  |   ,  |   .  |   /  | RSFT |
 * `----------------------------------------',0---------------.`----------------------------------+------'
 *                                           | GUI/Tab | RAISE |
 *                                           `-----------------'
 *                               ,---------------.         ,---------------.
 *                               |SFT/ESC | BKSPC|         | RAISE | LOWER |
 *                               `---------------'         `---------------.
 */
[_RAISE] = LAYOUT( \
	_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      _______,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
	_______, KC_TAB,  KC_VOLD, KC_VOLU, KC_MPLY, KC_MFFD,   _______,   KC_MUTE, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
	_______, _______, KC_GRV,  KC_LGUI, KC_LALT, KC_MRWD,   KC_ENT,   _______, _______, _______, KC_BSLS, KC_QUOT, _______, \
										KC_LCTL, KC_BSPC, _______,                        _______, _______

),

/* LOWER
 *
 * ,----------------------------------------.     ,------.     ,-----------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R   |  T  |    | PLY  |     |   Y  |   U  |   I  |   O  |   P  | BSP  |
 * |------+------+------+------+------+------|    |--++--'     |------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   D  |   F  |  G   |    | MUTE |     |   H  |   J  |   K  |   L  |   ;  | ENT  |
 * |------+------+------+------+------+------|    `------'     |------+------+------+------+------+------|
 * | LSFT |   Z  |   X  |   C  |   V  |  B   |          ||     |   N  |   M  |   ,  |   .  |   /  | RSFT |
 * `----------------------------------------',0---------------.`----------------------------------+------'
 *                                           | GUI/Tab | RAISE |
 *                                           `-----------------'
 *                               ,---------------.         ,---------------.
 *                               |SFT/ESC | BKSPC|         | RAISE | LOWER |
 *                               `---------------'         `---------------.
 */
[_LOWER] = LAYOUT( \
	_______, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC,  _______,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,\
	_______, KC_ESC,  KC_VOLD,  KC_VOLU, KC_MPLY, KC_MFFD,  _______,    KC_MUTE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,\
	_______, KC_CAPS, KC_TILD,  _______, _______, KC_MRWD,  _______,    _______, _______, _______, KC_PIPE, KC_DQT,  _______,\
										RAISE, KC_DEL,  _______,                          _______,  _______                                    \
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------------.     ,------.     ,-----------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R   |  T  |    | PLY  |     |   Y  |   U  |   I  |   O  |   P  | BSP  |
 * |------+------+------+------+------+------|    |--++--'     |------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   D  |   F  |  G   |    | MUTE |     |   H  |   J  |   K  |   L  |   ;  | ENT  |
 * |------+------+------+------+------+------|    `------'     |------+------+------+------+------+------|
 * | LSFT |   Z  |   X  |   C  |   V  |  B   |          ||     |   N  |   M  |   ,  |   .  |   /  | RSFT |
 * `----------------------------------------',0---------------.`----------------------------------+------'
 *                                           | GUI/Tab | RAISE |
 *                                           `-----------------'
 *                               ,---------------.         ,---------------.
 *                               |SFT/ESC | BKSPC|         | RAISE | LOWER |
 *                               `---------------'         `---------------.
 */
[_ADJUST] =  LAYOUT( \
	_______, KC_F1,  KC_F2,   KC_F3,    KC_F4,   KC_F5,    _______,    KC_F6,   KC_F7,   KC_UP,   KC_F9,    KC_F10,  _______,\
	_______, KC_F11, KC_F12,  RGB_RMOD, RGB_SAI, RGB_SAD,  _______,    _______, KC_LEFT, KC_DOWN, KC_RGHT,  _______, _______,\
	_______, RESET,  RGB_TOG, RGB_MOD,  RGB_HUI, RGB_HUD,  _______,    RGB_VAI, RGB_VAD, KC_F8,   _______,  KC_RSFT, _______,\
										_______, _______, _______,      _______,  _______                                                      \
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
