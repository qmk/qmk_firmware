#include QMK_KEYBOARD_H
#include "version.h"

enum custom_keycodes {
    SHR_LOD = SAFE_RANGE,
    VRSN
};

enum unicode_name {
    IBNG
};

const uint32_t PROGMEM unicode_map[] = {
    [IBNG]  = 0x203D,  // ‽
};

#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: (Base Layer) Default Layer
     * ,----------------------------------------------------------------.
     * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
     * |----------------------------------------------------------------|
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
     * |----------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
     * |----------------------------------------------------------------|
     * |Ctrl|Alt |Cmd |        Space          | Fn|Alt|Ctrl|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    [_BL] = LAYOUT_65_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    MO(_FL), KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Keymap _FL: Function Layer
     * ,----------------------------------------------------------------.
     * |LoD| F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
     * |----------------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |Hme |
     * |----------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |End |
     * |----------------------------------------------------------------|
     * |RShift  |   |Brt|Bl-|BL |BL+|   |MUT|VU-|VU+|Ibg|   McL|MsU|McR |
     * |----------------------------------------------------------------|
     * |RCtl|RAlt|RGui|                       |   |   |    |MsL|MsD|MsR |
     * `----------------------------------------------------------------'
     */
    [_FL] = LAYOUT_65_ansi(
        SHR_LOD,       KC_F1,         KC_F2,         KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______,       VRSN,          _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
        _______,       _______,       _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_END,
        OSM(MOD_RSFT),                _______,       BL_BRTG, BL_DEC,  BL_TOGG, BL_INC,  _______, KC_MUTE, KC_VOLD, KC_VOLU, X(IBNG), KC_BTN1, KC_MS_U, KC_BTN2,
        OSM(MOD_RCTL), OSM(MOD_RALT), OSM(MOD_RGUI),                            _______,                   _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
    ),
};

void unicode_s(const char plain[], const char shifted[]) {
    if (get_mods()&MOD_MASK_SHIFT) {
        send_unicode_string(shifted);
    } else {
        send_unicode_string(plain);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case SHR_LOD:
            if (record->event.pressed) {
                unicode_s("¯\\_(ツ)_/¯", "ಠ_ಠ");
            }
            return false;
        case VRSN:  // Prints firmware version
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR("# " QMK_KEYBOARD "/" QMK_KEYMAP ":" QMK_VERSION " " QMK_BUILDDATE "\n"), TAP_CODE_DELAY);
            }
            return false;
        default:
            return true;
    }
}
