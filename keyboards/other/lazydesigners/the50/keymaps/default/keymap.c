#include QMK_KEYBOARD_H

enum custom_layers {
  _QWERTY,
  _FN
};

// Act as Shift on hold and as CapsLock on tap
#define SFT_CPS LSFT_T(KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *  ,-----------------------------------------------------------. ,--------------.
 *  |Esc | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  |Bspc| | 7  | 8  | 9  |
 *  |-----------------------------------------------------------| |--------------|
 *  | Tab  | A  | S  | D  | F  | G  | H  | J  | K  | L  | Enter | | 4  | 5  | 6  |
 *  |-----------------------------------------------------------| |--------------|
 *  | Shift  | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | FN  | | 1  | 2  | 3  |
 *  |-----------------------------------------------------------| |--------------|
 *  | Ctrl |Gui | Alt  |  Space  |    Space   | RAlt |RGui|RCtrl| | 0  | .  |Entr|
 *  `-----------------------------------------------------------' `--------------'
 */

[_QWERTY] = LAYOUT(
KC_GESC, KC_Q,    KC_W,    KC_E,     KC_R,   KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,     KC_7, KC_8,   KC_9,
KC_TAB,  KC_A,    KC_S,    KC_D,     KC_F,   KC_G,    KC_H,    KC_J,    KC_K,    KC_L,        KC_ENT,           KC_4, KC_5,   KC_6,
SFT_CPS, KC_Z,    KC_X,    KC_C,     KC_V,   KC_B,    KC_N,    KC_M,             KC_COMM, KC_DOT,  MO(_FN),     KC_1, KC_2,   KC_3,
KC_LCTL, KC_LGUI, KC_LALT,       KC_SPC,            KC_SPC,                      KC_RALT, KC_RGUI, KC_RCTL,     KC_0, KC_DOT, KC_ENT
),

/* FN
 *  ,-----------------------------------------------------------. ,--------------.
 *  |RST |    |    |    |    |    |    |    |    |    |Ins |Del | |Home|PgUp|    |
 *  |-----------------------------------------------------------| |--------------|
 *  |      |Prev|Play|Next|    |    |    |VolD|Mute|VolU|       | |End |PgDn|    |
 *  |-----------------------------------------------------------| |--------------|
 *  |        |    |    |    |    |    |    |    |    |    |     | |    |    |    |
 *  |-----------------------------------------------------------| |--------------|
 *  |EEPRST|    |      |         |            |      |    |     | |    |    |    |
 *  `-----------------------------------------------------------' `--------------'
 */

[_FN] = LAYOUT(
RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,   KC_DEL,     KC_HOME, KC_PGUP, _______,
_______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, KC_VOLD, KC_MUTE, KC_VOLU,          _______,     KC_END,  KC_PGDN, _______,
_______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,     _______, _______, _______,
EEP_RST, _______, _______,          _______,            _______,                 _______, _______, _______,     _______, _______, _______
)
};

void led_set_user(uint8_t usb_led) {
  // Turn LED On/Off for Caps Lock
  if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
    the50_led_on();
  } else {
    the50_led_off();
  }
}
