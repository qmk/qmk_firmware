#include QMK_KEYBOARD_H
#include "keymap_german_osx.h"

enum layers { _LETTERS = 0, _SYMBOLS, _NUMBERS, _MEDIA, _KBD_CTRL };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LETTERS] = LAYOUT(
        C(KC_LEFT), KC_X, DE_DOT, KC_O, DE_COMM, DE_Y,                                          KC_V, KC_G, KC_C, KC_L, KC_J, C(KC_RGHT),
        LT(4,KC_ESC), CTL_T(KC_H), ALT_T(KC_A), GUI_T(KC_E), SFT_T(KC_I), KC_U,                 KC_D, SFT_T(KC_T), GUI_T(KC_R), ALT_T(KC_N), CTL_T(KC_S), KC_F,
        KC_NO, KC_K, KC_Q, DE_ADIA, DE_UDIA, DE_ODIA, KC_NO, KC_NO,                             KC_NO, KC_NO, KC_B, KC_P, KC_W, KC_M, DE_Z, DE_SS,
        KC_HOME, KC_BSPC, LT(1,KC_TAB), LT(2,KC_SPC), LT(3,KC_ENT),                             LT(3,KC_ENT), LT(2,KC_SPC), LT(1,KC_TAB), KC_DEL, KC_END),
        // LT(_LAYER_NAME, KC_XY) will break the json import in the configurator, so use numbers
    [_SYMBOLS] = LAYOUT(
        KC_TRNS, DE_AT, DE_PERC, DE_LCBR, DE_RCBR, DE_PIPE,                                     DE_EXLM, KC_GRV, S(KC_GRV), DE_EQL, DE_AMPR, KC_TRNS,
        KC_TRNS, CTL_T(KC_NUBS), ALT_T(DE_TILD), GUI_T(DE_LPRN), SFT_T(DE_RPRN), DE_ASTR,       DE_QUES, SFT_T(DE_SLSH), GUI_T(DE_COLN), ALT_T(DE_MINS), CTL_T(DE_UNDS), KC_NO,
        KC_TRNS, DE_EURO, DE_DLR, DE_LBRC, DE_RBRC, DE_HASH, KC_NO, KC_NO,                      KC_NO, KC_NO, DE_GRV, DE_BSLS, DE_SCLN, DE_PLUS, DE_DQUO, DE_QUOT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_NUMBERS] = LAYOUT(
        KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                             KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_TRNS, CTL_T(DE_1), ALT_T(DE_2), GUI_T(DE_3), SFT_T(DE_4), DE_5,                      DE_6, SFT_T(DE_7), GUI_T(DE_8), ALT_T(DE_9), CTL_T(DE_0), KC_F12,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_NO,                         KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                            KC_BTN1, KC_BTN2, KC_WH_D, KC_WH_U, KC_TRNS), // scrolling reversed (due to natural scrolling?)
    [_MEDIA] = LAYOUT(
        KC_TRNS, KC_NO, KC_VOLU, KC_NO, KC_NO, KC_NO,                                           KC_NO, G(KC_X), G(KC_R), KC_NO, C(KC_LEFT), KC_TRNS,
        KC_TRNS, KC_BRIU, KC_MUTE, KC_MPLY, KC_MNXT, KC_NO,                                     G(C(KC_SPACE)), G(KC_C), G(DE_Z), G(KC_F), C(KC_UP), KC_NO,
        KC_TRNS, KC_BRID, KC_VOLD, KC_NO, KC_MPRV, KC_NO, KC_NO, KC_NO,                         KC_NO, KC_NO, KC_NO, G(KC_V), G(S(DE_Z)), KC_NO, C(KC_RGHT), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_KBD_CTRL] = LAYOUT(
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                             KC_NO, RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
// clang-format on

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_status(void) {
    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case _LETTERS:
            oled_write_P(PSTR("Letters\n"), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case _NUMBERS:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case _MEDIA:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case _KBD_CTRL:
            oled_write_P(PSTR("Ctrl\n"), false);
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
        render_status();  // Renders the current keyboard state (layers and locks)
    }
}
#endif

#ifdef RGBLIGHT_ENABLE
// called post init on every "boot"
// will set the initial lightings
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();  // enables Rgb, without saving settings
    rgblight_mode_noeeprom(RGBLIGHT_DEFAULT_MODE);
    rgblight_sethsv_noeeprom(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
}

// called on every layer change
// set the colour according to active layer
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _LETTERS:
            rgblight_sethsv_noeeprom(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
            break;
        case _SYMBOLS:
            rgblight_sethsv_noeeprom(23, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
            break;
        case _NUMBERS:
            rgblight_sethsv_noeeprom(121, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
            break;
        case _MEDIA:
            rgblight_sethsv_noeeprom(246, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
            break;
        case _KBD_CTRL:
            rgblight_sethsv_noeeprom_white();
            break;
        default:  //  for any other layers, or the default layer
            rgblight_sethsv_noeeprom(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
            break;
    }
    return state;
}
#endif
