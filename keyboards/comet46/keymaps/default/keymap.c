// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum comet46_layers
{
    _QWERTY,
    _LOWER,
    _RAISE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------+                    +-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * | Ctl  |   A  |   S  |   D  |   F  |   G  | Esc  |      | Del  |   H  |   J  |   K  |   L  |   ;  |   "  |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   {  |      |   }  |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             | GUI  | Lower| Space|      | Enter| Raise| Alt  |
   *                             +--------------------/      \--------------------+
   */
  [_QWERTY] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_ESC,         KC_DEL,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCBR,        KC_RCBR, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                        KC_LGUI, LOWER,   KC_SPC,         KC_ENT,  RAISE,   KC_LALT
  ),

  /* Lower
   * ,-----------------------------------------+                    +-----------------------------------------.
   * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |   `  |   \  |   -  |   =  |   [  |   ]  |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |   ~  |   |  |   _  |   +  |   {  |   }  |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             |      |      |      |      |      |      |      |
   *                             +--------------------/      \--------------------+
   */
  [_LOWER] = LAYOUT(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, _______, _______, _______, _______, _______, _______,        KC_GRV,  KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
    _______, _______, _______, _______, _______, _______, _______,        KC_TILD, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
                                        _______, _______, _______,        _______, _______, _______
  ),

  /* Raise
   * ,-----------------------------------------+                    +-----------------------------------------.
   * |      |   1  |   2  |   3  |   4  |   5  |                    |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      | Left | Down |  Up  |Right | End  |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | Home |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             |      |      |      |      |      |      |      |
   *                             +--------------------/      \--------------------+
   */
  [_RAISE] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  _______,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,         KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                        _______, _______, _______,        _______, _______, _______
  )
};


void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
    	case _QWERTY:
    	    set_led_green;
    	    break;
        case _RAISE:
            set_led_blue;
            break;
        case _LOWER:
            set_led_red;
            break;
        default:
            set_led_green;
            break;
    }
}
