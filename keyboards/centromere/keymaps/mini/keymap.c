#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum centromere_layers
{
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

// Defines for layer movement
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Defines for task manager
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl | LOWER|      |    |      | RAISE| Shift|
 *                  `-------------| Space|    |BckSpc|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = LAYOUT( \
  KC_NO,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,       KC_NO, \
  KC_NO,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_NO, \
  KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_NO, \
                    KC_LCTL, LOWER, KC_SPC,         KC_BSPC, RAISE, OSM(MOD_LSFT)                 \
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab | Left | Down |  Up  | Right|           |      |   -  |   =  |   [  |   ]  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Ctrl|   `  |  GUI |  Alt |      |           |      |      |      |   \  |   '  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_RAISE] = LAYOUT( \
  KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    	KC_NO,    \
  KC_NO,   KC_TAB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,	KC_NO,    \
  KC_NO,   KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, _______,      _______, _______, _______, KC_BSLS,  KC_QUOT,	KC_NO,    \
                    _______, _______, _______,      _______, _______, _______                    \
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Esc |      |      |      |      |           |      |   _  |   +  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|   ~  |      |      |      |           |      |      |      |   |  |   "  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|  Del |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_LOWER] = LAYOUT(
  KC_NO,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_NO,
  KC_NO,   KC_ESC,  _______, _______, _______, _______,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_NO,
  KC_NO,   KC_CAPS, KC_TILD, _______, _______, _______,      _______, _______, _______, KC_PIPE,  KC_DQT, KC_NO,
                    _______, _______, _______,      KC_ENT,  _______, KC_DEL
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |      |      |           |      |      |      |Taskmg|caltde|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] =  LAYOUT( \
  KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_NO,   \
  KC_NO,   KC_F11,  KC_F12,  _______, _______, _______,      _______, _______, _______, TSKMGR, CALTDEL,   KC_NO,   \
  KC_NO,   RESET,   _______, _______, _______, _______,      _______, _______, _______, _______,  _______, KC_NO,   \
                    _______, _______, _______,      _______,  _______, _______                    \
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
