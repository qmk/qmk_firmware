#include QMK_KEYBOARD_H

#include "chrisgve.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY_MAC] = LAYOUT_60_tsangan_hhkb(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		CPS_CTL, KC_A,    KC_S,    M_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   R_SHIFT, ADJUST,
		XXXXXXX, KC_LALT, KC_LGUI,                                     KC_SPC,                                      KC_RGUI, KC_RALT, XXXXXXX
	),

	[_MAC_NAV_1] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, M_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, A_SHIFT, S_SHIFT, _______, M_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
		_______, _______, _______, _______, _______, M_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_MAC_NAV_2] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_QWERTY_LINUX] = LAYOUT_60_tsangan_hhkb(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		CPS_CTL, KC_A,    KC_S,    L_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   R_SHIFT, ADJUST,
		XXXXXXX, KC_LGUI, KC_LALT,                                     KC_SPC,                                      KC_RALT, KC_RGUI, XXXXXXX
	),

	[_LINUX_NAV_1] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, L_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, A_SHIFT, S_SHIFT, _______, L_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
		_______, _______, _______, _______, _______, L_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_LINUX_NAV_2] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_QWERTY_WIN] = LAYOUT_60_tsangan_hhkb(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		CPS_CTL, KC_A,    KC_S,    W_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   R_SHIFT, ADJUST,
		XXXXXXX, KC_LGUI, KC_LALT,                                     KC_SPC,                                      KC_RALT, KC_RGUI, XXXXXXX
	),

	[_WIN_NAV_1] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, W_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, A_SHIFT, S_SHIFT, _______, W_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
		_______, _______, _______, _______, _______, W_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_WIN_NAV_2] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_ADJUST] = LAYOUT_60_tsangan_hhkb(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
		RESET,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,          _______,
		_______, DF_MAC,  DF_LNX,  DF_WIN,  _______, _______, _______, KC_MUTE, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     KC_MPLY,                                     _______, _______, _______
	),

};

extern rgblight_config_t rgblight_config;

bool caps_lock = false;  // Indicator if caps lock is on
bool def_layer = true;   // Indicates if the board is on a default layer

void reset_rgb(void) {
    rgblight_disable_noeeprom();
}

void set_rgb(uint8_t red, uint8_t green, uint8_t blue) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb(red, green, blue);
}

void keyboard_post_init_user() {
    reset_rgb();
}

void set_nav_1_rgb(void) {
    set_rgb(RGB_NAV1_R, RGB_NAV1_B, RGB_NAV1_G);
}

void set_nav_2_rgb(void) {
    set_rgb(RGB_NAV2_R, RGB_NAV2_B, RGB_NAV2_G);
}

void set_caps_rgb(void) {
    set_rgb(RGB_CAPS_R, RGB_CAPS_B, RGB_CAPS_G); // Warm white
}

void set_adj_rgb(void) {
    set_rgb(RGB_ADJ_R, RGB_ADJ_B, RGB_ADJ_G);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (caps_lock) {
        set_caps_rgb();
    } else {
        reset_rgb();
    }
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
        case _MAC_NAV_1:
        case _LINUX_NAV_1:
        case _WIN_NAV_1:
            set_nav_1_rgb();
            def_layer = false;
            break;
        case _MAC_NAV_2:
        case _LINUX_NAV_2:
        case _WIN_NAV_2:
            set_nav_2_rgb();
            def_layer = false;
            break;
        case _ADJUST:
            set_adj_rgb();
            def_layer = false;
            break;
        default:
            def_layer = true;
            if (caps_lock) {
                set_caps_rgb();
            } else {
                reset_rgb();
            } break;
    }
    return state;
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        set_caps_rgb();
        caps_lock = true;
    } else {
        if (def_layer) {
            reset_rgb();
        }
        caps_lock = false;
    }
}
