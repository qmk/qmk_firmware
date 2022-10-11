#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0

#define _LOWER 3
#define _RAISE 4
#define _FUNCTION 15
#define _ADJUST 16

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |  '   |   ,  |   .  |   P  |   Y  | Tab  | Bksp |   F  |   G  |   C  |   R  |   L  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   A  |   O  |   E  |   U  |   I  | Enter| Enter|   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   ;  |   Q  |   J  |   K  |   X  | Shift| Shift|   B  |   M  |   W  |   V  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Shift|Space |Lower |Raise |Space | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT( \
  KC_QUOTE,    KC_COMMA, KC_DOT,  KC_P,    KC_Y, KC_TAB, KC_BSPC, KC_F,  KC_G,    KC_C,    KC_R,    KC_L, \
  KC_A,        KC_O,     KC_E,    KC_U,    KC_I, KC_ENT, KC_ENT,  KC_D,  KC_H,    KC_T,    KC_N,    KC_S, \
  KC_SCOLON,   KC_Q,     KC_J,    KC_K,    KC_X, OSM(MOD_LSFT), OSM(MOD_RSFT), KC_B,  KC_M,    KC_W,    KC_V,    KC_Z, \
  KC_LCTL, KC_LGUI, KC_LALT, OSM(MOD_LSFT), KC_SPC, LOWER, RAISE, KC_SPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/*[BASE] = LAYOUT(
 *   KC_QUOTE,      KC_COMMA,      KC_DOT,     KC_P,                KC_Y,                                 KC_F,       KC_G,      KC_C,    KC_R,          KC_L,
 *   KC_A,          KC_O,          KC_E,       KC_U,                KC_I,                                 KC_D,       KC_H,      KC_T,    KC_N,          KC_S,
 *   KC_SCOLON,     KC_Q,          KC_J,       KC_K,                KC_X,                                 KC_B,       KC_M,      KC_W,    KC_V,          KC_Z,
 *   OSM(MOD_LSFT), OSM(MOD_LCTL), MO(KEYSEL), MO(BROWSER_CONTROL), MO(COMBINED), MO(KEYNAV), KC_ENTER,   KC_SPACE,  KC_BSPC, RCTL(KC_BSPC), KC_CAPSLOCK, OSM(MOD_LSFT)
 * ),
 *KC_GRV,
 */
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Mute |      |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower | Bksp | Bksp |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_ESC,  KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, \
  _______, KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_MUTE, _______, KC_PIPE, \
  _______, _______,  _______, _______, KC_BSPC, _______, _______, KC_BSPC, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   4  |   5  |   6  |   +  |  F5  |  F6  |   -  |   =  |   [  |   ]  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Enter |   7  |   8  |   9  |   -  |  F11 |  F12 |ISO # |ISO / | Mute |      |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ,  |   0  |  .   |Lower | Bksp | Bksp |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_ESC,  KC_1,    KC_2,  KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  _______, KC_4,    KC_5,  KC_6,   KC_PLUS, KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
  KC_ENT,  KC_7,    KC_8,  KC_9,   KC_MINS, KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_MUTE, _______, KC_BSLS, \
  _______, KC_COMM, KC_0,  KC_DOT, _______, KC_BSPC, KC_BSPC, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Taskmg|      |      |      |      |      |      |      |RGBVAI|RGBSAI|RGBHUI|caltde|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Qwerty|RGBVAD|RGBSAD|RGBHUD|RGBTOG|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |BLSTEP|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | QK_BOOT|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT( \
  TSKMGR,  _______, _______, _______, _______, _______, KC_DEL,  _______, RGB_VAI, RGB_SAI, RGB_HUI, CALTDEL, \
  _______, _______, _______, _______, _______, _______, _______, DVORAK,  RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_STEP, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT    \
),

/* Function
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |  Up  |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
