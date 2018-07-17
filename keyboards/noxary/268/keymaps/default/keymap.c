#include "268.h"

// Helpful defines
#define _______ KC_TRNS

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL1 1
#define _FL2 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _BL: Base Layer(Default) - For ISO enter use ANSI enter
    * ,----------------------------------------------------------------.
    * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| \|BSpc| Grv|
    * |----------------------------------------------------------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | Del|
    * |----------------------------------------------------------------|
    * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| #| Ent|PgUp|
    * |----------------------------------------------------------------|
    * |Shift| \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
    * |----------------------------------------------------------------|
    * |Ctrl|Win |Alt |        Space        |Alt|Mo(1)|Ctrl|Lef|Dow|Rght|
    * `----------------------------------------------------------------'
    */
    [_BL] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSLS, KC_BSPC, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,           KC_BSLS,  KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,           KC_ENT,  KC_PGUP,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,   KC_C,    KC_V,  KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                         KC_SPC,                             KC_RALT, MO(_FL1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    /* _FL1: Function Layer 1 - For ISO enter use ANSI enter
    * ,----------------------------------------------------------------.
    * |  `|F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |PScr|    |
    * |----------------------------------------------------------------|
    * |     |   |   |   |RST|   |   |   |   |   |   |   |   |     | Ins|
    * |----------------------------------------------------------------|
    * |       |   |   |   |   |   |   |   |   |   |   |   |  |    |Home|
    * |----------------------------------------------------------------|
    * |     |   |   |   |   |   |   |   |   |Bl-|Bl+|   |Mute|Vol+| End|
    * |----------------------------------------------------------------|
    * |    |    |    |      BL_Toggle       |   |   |   |    |Vol-|    |
    * `----------------------------------------------------------------'
    */
    [_FL1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_PSCR, _______,
        _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_DEC,  BL_INC,  _______, KC_MUTE, KC_MUTE, KC_VOLU, KC_END,
        _______, _______, _______,                            BL_TOGG,                            _______, _______, _______, _______, KC_VOLD, _______),
    /* _FL2: Function Layer 2 - For ISO enter use ANSI enter
    * ,----------------------------------------------------------------.
    * |   |  |   |   |   |   |   |   |   |   |   |   |   |    |   |    |
    * |----------------------------------------------------------------|
    * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
    * |----------------------------------------------------------------|
    * |       |   |   |   |   |   |   |   |   |   |   |   |  |    |    |
    * |----------------------------------------------------------------|
    * |     |   |   |   |   |   |   |   |   |   |   |   |    |    |    |
    * |----------------------------------------------------------------|
    * |    |    |    |                      |   |   |   |    |    |    |
    * `----------------------------------------------------------------'
    */
    [_FL2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______),


};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void led_set_user(uint8_t usb_led) {

    if (usb_led & (1 << USB_LED_NUM_LOCK)) {

    }
    else {

    }

    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRB |= (1 << 6); PORTB |= (1 << 6);
    }
    else {
        DDRB &= ~(1 << 6); PORTB &= ~(1 << 6);
    }

    if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

    }
    else {

    }

    if (usb_led & (1 << USB_LED_COMPOSE)) {

    }
    else {

    }

    if (usb_led & (1 << USB_LED_KANA)) {

    }
    else {

    }

}
