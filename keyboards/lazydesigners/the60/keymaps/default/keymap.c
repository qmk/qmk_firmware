#include QMK_KEYBOARD_H

enum custom_layers {
  _QWERTY,
  _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,--------------------------------------------------------------------------.
 * |Esc | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  | -  | =  |Home|Del |
 * |--------------------------------------------------------------------------|
 * |  Tab  | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  | BsPc | [  | ]  |
 * |--------------------------------------------------------------------------|
 * |CapsLock | A  | S  | D  | F  | G  | H  | J  | K  | L  |  Enter  | ;  | '  |
 * |--------------------------------------------------------------------------|
 * |  Shift    | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | Shift | Up | /  |
 * |--------------------------------------------------------------------------|
 * | Ctrl | Gui  | Alt  |  Space  |   Space   | Alt  |Menu| Fn |Left|Down|Rght|
 * `--------------------------------------------------------------------------'
 */

[_QWERTY] = LAYOUT_split_spc_split_bspc(
KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_HOME, KC_DEL,
KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,          KC_LBRC, KC_RBRC,
KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,                    KC_SCLN, KC_QUOT,
KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,                   KC_UP,   KC_SLSH,
KC_LCTL, KC_LGUI, KC_LALT,       KC_SPACE,              KC_SPACE,                 KC_RALT, KC_APP, MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT
),

/* FN
 * ,--------------------------------------------------------------------------.
 * |RST |    |    |    |    |    |    |    |    |    |    |    |    |End |Ins |
 * |--------------------------------------------------------------------------|
 * |       |    |    |    |    |    |    |    |    |    |    |      |PgUp|PgDn|
 * |--------------------------------------------------------------------------|
 * |         |    |Prev|Play|Next|    |VolD|Mute|VolU|    |         |    |    |
 * |--------------------------------------------------------------------------|
 * |           |    |    |    |    |    |    |    |    |    |       |    |    |
 * |--------------------------------------------------------------------------|
 * |EEPRST|      |      |         |           |      |    |    |    |    |    |
 * `--------------------------------------------------------------------------'
 */

[_FN] = LAYOUT_split_spc_split_bspc(
RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_END,  KC_INS,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_PGUP, KC_PGDN,
XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,
EEP_RST, XXXXXXX, XXXXXXX,       XXXXXXX,              XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)
};

