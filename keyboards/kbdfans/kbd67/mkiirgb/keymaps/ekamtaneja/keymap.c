#include QMK_KEYBOARD_H
#include <stdint.h>

#define _DEF 0
#define _GAM 1
#define _ENG 2
#define _FN 3

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _DEF:
                rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
                break;
            case _GAM:
                rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                break;
            case _ENG:
                rgb_matrix_mode(RGB_MATRIX_CYCLE_OUT_IN_DUAL);
                break;
            case _FN:
                rgb_matrix_mode(RGB_MATRIX_PIXEL_FRACTAL);
                break;
            default:
                rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
                break;
        }
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[_DEF] = LAYOUT_65_ansi_blocker( /* Base */
			QK_GESC, KC_1,    KC_2,          KC_3,          KC_4,          KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_TRNS,
			KC_TAB,  KC_Q,    KC_W,          KC_E,          KC_R,          KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_TRNS,
			MO(_FN), KC_A,    KC_S,          KC_D,          KC_F,          KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  DF(_ENG),
			KC_LSFT, KC_Z,    KC_X,          KC_C,          KC_V,          KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   TG(_GAM),
			KC_LCTL, KC_LGUI, KC_LALT,                                     KC_SPC,                    KC_CAPS,          KC_RALT, KC_LEFT,          KC_DOWN, KC_RIGHT
		),
		[_GAM] = LAYOUT_65_ansi_blocker( /* 5xFN */
			KC_ESC,  KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
			KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
			MO(_FN), KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
			KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, TG(_GAM),
			KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_SPC,                    KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS
		),
        [_ENG] = LAYOUT_65_ansi_blocker( /* Engrammer */
			QK_GESC, KC_1,    KC_2,          KC_3,          KC_4,          KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, KC_TRNS,
			KC_TAB,  KC_B,    KC_Y,          KC_O,          KC_U,          KC_QUOT, KC_SCLN, KC_L,    KC_D,    KC_W,    KC_V,    KC_Z,    KC_EQL,  KC_BSLS, KC_TRNS,
			MO(_FN), KC_C,    KC_I,          KC_E,          KC_A,          KC_COMM, KC_DOT,  KC_H,    KC_T,    KC_S,    KC_N,    KC_Q,             KC_ENT,  DF(_DEF),
			KC_LSFT, KC_G,    KC_X,          KC_J,          KC_K,          KC_MINS, KC_SLSH, KC_R,    KC_M,    KC_F,    KC_P,    KC_RSFT,          KC_UP,   TG(_GAM),
			KC_LCTL, KC_LGUI, KC_LALT,                                     KC_SPC,                    KC_CAPS,          KC_RALT, KC_LEFT,          KC_DOWN, KC_RIGHT
		),
		[_FN] = LAYOUT_65_ansi_blocker( /* FN */
			KC_TRNS, KC_F1,   KC_F2,         KC_F3,         KC_F4,         KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_PSCR,
			KC_TRNS, KC_TRNS, KC_TRNS,       KC_WBAK,       KC_WFWD,       KC_TRNS, KC_TRNS, KC_PGDN, KC_UP,   KC_PGUP, KC_INS,  KC_SCRL, KC_PAUS, QK_BOOT, KC_PAUS,
			KC_TRNS, KC_TRNS, OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_TRNS,          EE_CLR,  KC_PGDN,
			KC_TRNS, KC_TRNS, KC_TRNS,       RGB_TOG,       RGB_MOD,       RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS,          KC_VOLU, KC_MUTE,
			KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS,                   KC_TRNS,          KC_TRNS, KC_MPRV,          KC_VOLD, KC_MNXT
		),

};
