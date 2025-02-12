#include QMK_KEYBOARD_H

// For controlling the power LED
#include "gpio.h"

/*
 * Main keymapping
 *
 */

// Use enum for layer sorting, as done in:
// https://github.com/qmk/qmk_firmware/blob/fa98117a3e10afed347f16b2614e4e8a9e26cd32/keyboards/planck/rev7/keymaps/default/keymap.c
enum nilscc_layers {
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

#define COLEMAK PDF(_COLEMAK)

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
        KC_TAB,     KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,                               KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    KC_DEL,
        KC_GRV,     KC_A,       KC_R,       KC_S,       KC_T,       KC_G,                               KC_M,       KC_N,       KC_E,       KC_I,       KC_O,       KC_QUOT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,       XXXXXXX,    XXXXXXX,    KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                                KC_LGUI,    KC_LALT,    KC_LCTL,    LOWER,      KC_ENT,     KC_SPC,     RAISE,      KC_RCTL,    KC_RALT,    KC_RGUI
    ),

    /* Lower layer */
    [_LOWER] = LAYOUT(
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                              KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
        _______,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_F12,
        _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,                            KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_PIPE,
        _______,    KC_EQL,     KC_MINS,    KC_PLUS,    KC_LCBR,    KC_RCBR,    _______,    _______,    KC_LBRC,    KC_RBRC,    KC_SCLN,    KC_COLN,    KC_BSLS,    _______,
                                _______,    _______,    _______,    _______,    _______,    _______,    ADJUST,      _______,    _______,    _______
    ),

    /* Raised layer */
    [_RAISE] = LAYOUT(
        _______,    _______,    _______,    _______,    _______,    _______,                            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    KC_INS,     KC_PSCR,    KC_APP,     XXXXXXX,    KC_SCRL,                            KC_PGUP,    C(KC_LEFT), KC_UP,      C(KC_RGHT), C(KC_BSPC), KC_BSPC,
        _______,    KC_LALT,    KC_LCTL,    KC_LSFT,    XXXXXXX,    KC_CAPS,                            KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_DEL,     KC_BSPC,
        _______,    C(KC_Z),    C(KC_X),    C(KC_C),    C(KC_V),    XXXXXXX,    _______,    _______,    XXXXXXX,    KC_HOME,    XXXXXXX,    KC_END,     XXXXXXX,    _______,
                                _______,    _______,    _______,    ADJUST,     _______,    _______,    _______,    _______,    _______,    _______
    ),

    /* Adjustment layer */
    [_ADJUST] = LAYOUT(
        XXXXXXX,    COLEMAK,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    RM_TOGG,    RM_HUEU,    RM_SATU,    RM_VALU,    XXXXXXX,                            XXXXXXX,    KC_VOLD,    KC_MUTE,    KC_VOLU,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    RM_NEXT,    RM_HUED,    RM_SATD,    RM_VALD,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_MPRV,    KC_MPLY,    KC_MNXT,    XXXXXXX,    XXXXXXX,
                                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    )

};

// Define encoder mapping
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(MS_WHLU, MS_WHLD)  },
    [1] = { ENCODER_CCW_CW(UG_HUED, UG_HUEU),  ENCODER_CCW_CW(UG_SATD, UG_SATU)  },
    [2] = { ENCODER_CCW_CW(UG_VALD, UG_VALU),  ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  },
    [3] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT),  ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif
/* clang-format on */


// Disable power LED of liatris board
void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}
