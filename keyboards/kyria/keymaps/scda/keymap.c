#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum layers { _LETTERS = 0, _SYMBOLS, _NUMBERS, _MEDIA, _KBD_CTRL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LETTERS] = LAYOUT(LGUI(KC_TAB), KC_X, KC_DOT, KC_O, KC_COMM, KC_Y, KC_V, KC_G, KC_C, KC_L, KC_J, LGUI(KC_SPC), LT(4,KC_ESC), LSFT_T(KC_H), LCTL_T(KC_A), LALT_T(KC_E), LGUI_T(KC_I), KC_U, KC_D, RGUI_T(KC_T), RALT_T(KC_R), RCTL_T(KC_N), RSFT_T(KC_S), KC_F, KC_NO, KC_K, KC_Q, DE_ADIA, DE_UDIA, DE_ODIA, KC_NO, KC_NO, KC_NO, KC_NO, KC_B, KC_P, KC_W, KC_M, KC_Z, DE_SS, KC_HOME, KC_BSPC, LT(3,KC_TAB), LT(2,KC_SPC), LT(1,KC_ENT), LT(1,KC_ENT), LT(2,KC_SPC), LT(3,KC_TAB), KC_DEL, KC_END),
    
    [_SYMBOLS] = LAYOUT(KC_TRNS, KC_AT, KC_PERC, KC_LCBR, KC_RCBR, KC_PIPE, KC_EXLM, KC_LT, KC_GT, KC_EQL, KC_AMPR, KC_TRNS, KC_TRNS, LSFT_T(KC_CIRC), LCTL_T(KC_TILD), LALT_T(KC_LPRN), LGUI_T(KC_RPRN), KC_ASTR, KC_QUES, RGUI_T(KC_SLSH), RALT_T(KC_COLN), RCTL_T(KC_MINS), RSFT_T(KC_UNDS), KC_NO, KC_TRNS, DE_EURO, KC_DLR, KC_LBRC, KC_RBRC, KC_HASH, KC_NO, KC_NO, KC_NO, KC_NO, KC_GRV, KC_RO, KC_SCLN, KC_PLUS, KC_DQUO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    
    [_NUMBERS] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, LSFT_T(KC_1), LCTL_T(KC_2), LALT_T(KC_3), LGUI_T(KC_4), KC_5, KC_6, RGUI_T(KC_7), RALT_T(KC_8), RCTL_T(KC_9), RSFT_T(KC_0), KC_F12, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_WH_U, KC_WH_D, KC_TRNS),
    
    [_MEDIA] = LAYOUT(KC_TRNS, KC_NO, KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, RGUI(KC_X), RGUI(KC_R), KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_BRIU, KC_VOLU, KC_MPLY, KC_MNXT, KC_NO, G(C(KC_SPACE)), RGUI(KC_C), RGUI(KC_Z), RGUI(KC_F), G(S(KC_T)), KC_NO, KC_TRNS, KC_BRID, KC_VOLD, KC_NO, KC_MPRV, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGUI(KC_V), SGUI(KC_Z), KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    
    [_KBD_CTRL] = LAYOUT(KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, RGB_SAI, RGB_HUI, RGB_VAI, KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_SPI, KC_NO, KC_NO, KC_TRNS, KC_NO, RGB_SAD, RGB_HUD, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_SPD, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

/*
// not fully understood yet, see https://docs.qmk.fm/#/ref_functions?id=update_tri_layer_statestate-x-y-z
// seems like layer 3 can only be accessed from layer 1 and 2 or something like that?
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _MEDIA);
}
*/

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 128, 192, 224, 240, 112, 120, 56,  60,  28, 30, 14, 14, 14, 7,  7,   7,   7,   7,  7, 7,   7,   7, 7,  7,   7,   7,   7,  7,  7,  14, 14, 14,  30,  28,  60,  56,  120, 112, 240, 224, 192, 128, 128, 0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   192, 224, 240, 124, 62,  31,  15,  7,   3,   1,   128, 192, 224, 240, 120, 56,  60, 28, 30, 14, 14, 7,   7,   135, 231, 127, 31,  255, 255, 31,  127, 231, 135, 7,  7,  14,
    14, 30, 28,  60,  56,  120, 240, 224, 192, 128, 1,   3,   7,   15,  31,  62,  124, 240, 224, 192, 0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   240, 252, 255, 31,  7,   1,  0,   0,   192, 240, 252, 254, 255, 247, 243, 177, 176, 48,  48,  48,  48,  48,  48,  48,  120, 254, 135, 1,   0,   0,   255, 255, 0,   0,   1,   135, 254, 120, 48,  48,  48, 48, 48,  48,  48,  176, 177, 243, 247, 255, 254, 252, 240, 192, 0,   0,   1,   7,   31,  255, 252, 240, 0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,
    0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  255, 255, 255, 0,   0,   0,   0,   0,   254, 255, 255, 1,   1,   7,  30, 120, 225, 129, 131, 131, 134, 134, 140, 140, 152, 152, 177, 183, 254, 248, 224, 255, 255, 224, 248, 254, 183, 177, 152, 152, 140, 140, 134, 134, 131, 131, 129, 225, 120, 30, 7,   1,   1,   255, 255, 254, 0,   0,   0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   255, 255, 0,   0,   192, 192, 48,  48,  0,   0,   240, 240, 0,   0,   0,   0,   0,  0,  240, 240, 0,   0,   240, 240, 192, 192, 48,  48,  48,  48,  192, 192, 0,   0,   48,  48,  243, 243, 0,  0,  0,  0,  0,  0,   48,  48,  48,  48,  48,  48,  192, 192, 0,   0,   0,   0,  0,  0,
    0,  0,  255, 255, 255, 0,   0,   0,   0,   0,   127, 255, 255, 128, 128, 224, 120, 30,  135, 129, 193, 193, 97, 97, 49, 49, 25, 25, 141, 237, 127, 31, 7, 255, 255, 7, 31, 127, 237, 141, 25, 25, 49, 49, 97, 97,  193, 193, 129, 135, 30,  120, 224, 128, 128, 255, 255, 127, 0,  0,  0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   63,  63,  3,   3,   12,  12,  48,  48,  0,   0,   0,   0,   51,  51,  51,  51,  51,  51,  15,  15,  0,   0,   63,  63,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   48,  48,  63,  63,  48,  48,  0,   0,   12,  12,  51,  51,  51,  51,  51,  51,  63,  63,  0,   0,   0,   0,   0,   0,   0,   0,  0,  15,  63,  255, 248, 224, 128, 0,   0,   3,   15,  63,  127, 255, 239, 207, 141, 13,  12,  12,  12,  12, 12, 12, 12, 30, 127, 225, 128, 0,   0,   255, 255, 0,   0,   128, 225, 127, 30, 12, 12,
    12, 12, 12,  12,  12,  13,  141, 207, 239, 255, 127, 63,  15,  3,   0,   0,   128, 224, 248, 255, 63,  15,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   7,   15,  62, 124, 248, 240, 224, 192, 128, 1,   3,   7,   15,  30,  28,  60,  56,  120, 112, 112, 224, 224, 225, 231, 254, 248, 255, 255, 248, 254, 231, 225, 224, 224, 112, 112, 120, 56, 60, 28,  30,  15,  7,   3,   1,   128, 192, 224, 240, 248, 124, 62,  15,  7,   3,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,
    0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   3,   7,   15, 14, 30,  28,  60,  56,  120, 112, 112, 112, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 112, 112, 112, 120, 56,  60,  28,  30,  14,  15,  7,  3,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};

    oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _LETTERS:
            oled_write_P(PSTR("Letters\n"), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Signs\n"), false);
            break;
        case _NUMBERS:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case _MEDIA:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case _KBD_CTRL:
            oled_write_P(PSTR("KBD_CTRL\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif
