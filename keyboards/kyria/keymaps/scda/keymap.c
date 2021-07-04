#include QMK_KEYBOARD_H
#include "keymap_german_osx.h"

enum layers { _LETTERS = 0, _SYMBOLS, _NUMBERS, _CODE, _NAV, _FN, _MEDIA, _KBD_CTRL };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LETTERS] = LAYOUT(
        C(KC_LEFT), KC_X,        DE_DOT,      KC_O,          DE_COMM,     DE_Y,                                                                           KC_V,         KC_G,        KC_C,        KC_L,        KC_J,        C(KC_RGHT),
        KC_ESC,     CTL_T(KC_H), ALT_T(KC_A), GUI_T(KC_E),   SFT_T(KC_I), KC_U,                                                                           KC_D,         SFT_T(KC_T), GUI_T(KC_R), ALT_T(KC_N), CTL_T(KC_S), KC_F,
        C(KC_UP),   KC_K,        KC_Q,        DE_ADIA,       DE_UDIA,     DE_ODIA,      KC_NO,        KC_NO,                  KC_NO,        KC_NO,        KC_B,         KC_P,        KC_W,        KC_M,        DE_Z,        DE_SS,
                                              LT(7,KC_HOME), KC_BSPC,     LT(2,KC_TAB), LT(3,KC_SPC), LT(4,KC_ENT),           LT(6,KC_ENT), LT(5,KC_SPC), LT(1,KC_TAB), KC_DEL,      KC_END),
    [_SYMBOLS] = LAYOUT(
        KC_NO, DE_AT,   DE_PERC, DE_LCBR, DE_RCBR, DE_PIPE,                                                  DE_EXLM, KC_GRV,  S(KC_GRV), DE_EQL,  DE_AMPR, KC_NO,
        KC_NO, KC_NUBS, DE_TILD, DE_LPRN, DE_RPRN, DE_ASTR,                                                  DE_QUES, DE_SLSH, DE_COLN,   DE_MINS, DE_UNDS, KC_NO,
        KC_NO, DE_EURO, DE_DLR,  DE_LBRC, DE_RBRC, DE_HASH, KC_NO,   KC_NO,                KC_NO,   KC_NO,   DE_GRV,  DE_BSLS, DE_SCLN,   DE_PLUS, DE_DQUO, DE_QUOT,
                                 KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO),
    [_NUMBERS] = LAYOUT(
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                    KC_NO,   DE_7,  DE_8, DE_9, KC_NO, KC_NO,
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                                    DE_0,    DE_4,  DE_5, DE_6, KC_NO, KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                KC_NO,   KC_NO,   KC_NO,   DE_1,  DE_2, DE_3, KC_NO, KC_NO,
                                 KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO),
    [_CODE] = LAYOUT(
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                    KC_NO,      G(KC_X),  KC_NO,      KC_NO,      KC_NO,   KC_NO,
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                                    G(DE_Z),    G(KC_C),  G(S(DE_D)), G(KC_UP),   G(KC_F), KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                KC_NO,   KC_NO,   G(S(DE_Z)), G(KC_V),  G(DE_Y),    G(KC_DOWN), G(KC_R), KC_NO,
                                 KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS,    KC_NO,    KC_NO),
    [_NAV] = LAYOUT(
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                    G(A(KC_RGHT)), KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                                    G(A(KC_UP)),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                KC_NO,   KC_NO,   G(A(KC_LEFT)), KC_BTN1, KC_BTN2, KC_WH_D, KC_WH_U, KC_PGDN,
                                 KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS,       KC_NO,   KC_NO),
    [_FN] = LAYOUT(
        KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,                                                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_NO,                                                         KC_NO,   KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,
        KC_NO, KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                              KC_NO,  KC_NO,  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO),
    [_MEDIA] = LAYOUT(
        KC_NO, KC_NO,   KC_VOLU, KC_NO,   KC_NO,   KC_NO,                                                    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, KC_BRIU, KC_MUTE, KC_MPLY, KC_MNXT, G(C(KC_SPACE)),                                           KC_NO,   KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,
        KC_NO, KC_BRID, KC_VOLD, KC_NO,   KC_MPRV, KC_NO,          KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                 KC_NO,   KC_NO,   KC_TRNS,        KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO),
    [_KBD_CTRL] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                                            KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,                                                          KC_NO,   RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   RGB_TOG)
    // [_TEMPLATE] = LAYOUT(
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
};
// clang-format on

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_status(void) {
    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case _LETTERS:
            oled_write_P(PSTR("Letters\n###\n"), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Symbols\n###\n"), false);
            break;
        case _NUMBERS:
            oled_write_P(PSTR("Numbers\n>>>\n"), false);
            break;
        case _CODE:
            oled_write_P(PSTR("Code\n>>>\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Nav\n>>>\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Fn\n<<<\n"), false);
            break;
        case _MEDIA:
            oled_write_P(PSTR("Media\n<<<\n"), false);
            break;
        case _KBD_CTRL:
            oled_write_P(PSTR("Keeb Ctrl\n"), false);
            break;
        default:
            oled_write_P(PSTR("\n"), false);
            break;
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_left()) {
        render_status();
    }
}
#endif

#ifdef RGBLIGHT_ENABLE
// called post init on every "boot"
// will set the initial lightings
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();  // enables Rgb, without saving settings
    rgblight_mode_noeeprom(RGBLIGHT_DEFAULT_MODE);
    rgblight_sethsv_noeeprom(HSV_CHARTREUSE);
}

void sethsv_master(uint8_t hue, uint8_t sat, uint8_t val) { rgblight_sethsv_range(hue, sat, val, 0, (uint8_t)RGBLED_NUM / 2); }

// called on every layer change
// set the colour according to active layer
layer_state_t layer_state_set_user(layer_state_t state) {
    // setrgb, sethsv_noeeprom, setrgb_range do not write to eeprom
    switch (get_highest_layer(state)) {
        case _LETTERS:
            rgblight_sethsv_noeeprom(HSV_CHARTREUSE);
            break;
        case _SYMBOLS:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case _NUMBERS:
            rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
            sethsv_master(HSV_OFF);
            break;
        case _CODE:
            rgblight_sethsv_noeeprom(HSV_PINK);
            sethsv_master(HSV_OFF);
            break;
        case _NAV:
            rgblight_sethsv_noeeprom(HSV_CYAN);
            sethsv_master(HSV_OFF);
            break;
        case _FN:
            rgblight_sethsv_noeeprom(HSV_OFF);
            sethsv_master(HSV_PURPLE);
            break;
        case _MEDIA:
            rgblight_sethsv_noeeprom(HSV_OFF);
            sethsv_master(HSV_TEAL);
            break;
        case _KBD_CTRL:
            rgblight_sethsv_noeeprom_white();
            break;
        default:  //  for any other layers (that should not exist/be accessible)
            rgblight_setrgb(HSV_RED);
            break;
    }
    return state;
}
#endif
