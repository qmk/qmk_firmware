#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _FUNC,
    _NUMPAD
};

enum keycodes {
    QWERTY = SAFE_RANGE,
    FUNC,
    NUMPAD,
    MACRO1,
    MACRO2,
    MACROTAB,
    DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ansi_1u(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL, KC_PSCR,
        LT(_NUMPAD, KC_GRV), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(_FUNC), KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FUNC] = LAYOUT_ansi_1u(
        RESET, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLCK, KC_PAUS,
        KC_TRNS, MACRO1, MACRO2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        MACROTAB, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NUBS, KC_TRNS,
        KC_TRNS, VLK_TOG, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, DYN_REC_START2, DYN_MACRO_PLAY2, KC_TRNS, KC_TRNS,
        KC_TRNS, BL_TOGG, BL_DEC, BL_INC, BL_BRTG, KC_TRNS, KC_TRNS, KC_TRNS, DYN_REC_STOP, DYN_REC_START1, DYN_MACRO_PLAY1, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, LCA(KC_DEL), KC_TRNS, KC_TRNS, KC_APP, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_NUMPAD] = LAYOUT_ansi_1u(
        KC_NUMLOCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, KC_KP_SLASH, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS, KC_TRNS, KC_KP_ENTER, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0, KC_COMM, KC_DOT, KC_KP_PLUS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    
    switch (keycode) {
        case MACRO1:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("c") SS_DOWN(X_LALT) SS_TAP(X_TAB) SS_UP(X_LALT) SS_LCTRL("v") SS_TAP(X_TAB));
                _delay_ms(50);
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_TAB) SS_UP(X_LALT) SS_TAP(X_TAB));
            } else {
                
            }
            break;
        case MACRO2:
            if (record->event.pressed) {
                SEND_STRING("GGWP");
            } else {
                
            }
            break;
        case MACROTAB:
            if (record->event.pressed) {
                SEND_STRING("    ");
            } else {
                
            }
            break;
    }
    
    return true;
}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        setPinOutput(B2);
        writePinLow(B2);
    } else {
        setPinInput(B2);
    }
}
