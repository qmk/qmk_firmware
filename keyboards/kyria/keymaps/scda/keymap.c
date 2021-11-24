#include QMK_KEYBOARD_H
#include "mykeys.h"

enum layers { _LETTERS = 0, _SYMBOLS, _NUMBERS, _NAV, _MEDIA_CODE, _KBD_CTRL };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LETTERS] = LAYOUT(
        TO(_NAV), KC_X,        KC_DOT,      KC_O,        KC_COMM,      KC_Y,                                                              KC_V,   KC_G,         KC_C,            KC_L,        KC_J,        TO(_MEDIA_CODE),
        KC_ESC,   CTL_T(KC_H), ALT_T(KC_A), GUI_T(KC_E), SFT_T(KC_I),  KC_U,                                                              KC_D,   SFT_T(KC_T),  GUI_T(KC_R),     ALT_T(KC_N), CTL_T(KC_S), KC_F,
        G(KC_Z),  KC_K,        KC_Q,        DE_AE,       DE_UE,        DE_OE,  KC_NO,                 KC_NO,            KC_NO,   KC_NO,   KC_B,   KC_P,         KC_W,            KC_M,        KC_Z,        DE_SS,
                                            TO(_NAV),    TO(_SYMBOLS), KC_TAB, MT(MOD_MEH, KC_SPACE), KC_ENT,           KC_BSPC, KC_LSFT, KC_DEL, TO(_NUMBERS), TO(_MEDIA_CODE)),
    [_SYMBOLS] = LAYOUT(
        KC_TRNS,      KC_NO,   KC_AT,   KC_LT,   KC_GT,    KC_CIRC,                                                   KC_PERC, KC_LCBR, KC_RCBR, KC_PLUS, KC_DQT,  KC_TRNS,
        TO(_LETTERS), KC_DLR,  KC_EQL,  KC_QUES, KC_EXLM,  KC_HASH,                                                   KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS, KC_QUOT, KC_NO,
        KC_TRNS,      DE_EURO, KC_AMPR, KC_TILD, KC_SLASH, KC_PIPE, KC_NO,   KC_NO,                 KC_NO,   KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_UNDS, KC_GRV,  KC_NO,
                                        KC_NO,   TO(_NAV), KC_TRNS, KC_TRNS, KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_NUMBERS] = LAYOUT(
        KC_TRNS,      KC_NO, KC_F7, KC_F8, KC_F9,   KC_F12,                                                           KC_NO,   KC_7,            KC_8,     KC_9, KC_NO, KC_TRNS,
        TO(_LETTERS), KC_NO, KC_F4, KC_F5, KC_F6,   KC_F11,                                                           KC_NO,   KC_4,            KC_5,     KC_6, KC_NO, KC_NO,
        KC_TRNS,      KC_NO, KC_F1, KC_F2, KC_F3,   KC_F10,  KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_0,    KC_1,            KC_2,     KC_3, KC_NO, KC_NO,
                                KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, TO(_MEDIA_CODE), KC_TRNS),
    [_NAV] = LAYOUT(
        KC_TRNS,      KC_ACL2, KC_WH_R, KC_NO,      KC_WH_L, G(KC_PLUS),                                              C(KC_LEFT), G(A(KC_LEFT)), C(KC_UP), G(A(KC_RIGHT)), C(KC_RIGHT), KC_TRNS,
        TO(_LETTERS), KC_ACL1, KC_MS_L, KC_MS_UP,   KC_MS_R, G(KC_0),                                                 KC_HOME,    KC_LEFT,       KC_UP,    KC_RIGHT,       KC_END,      KC_PGUP,
        KC_TRNS,      KC_ACL0, KC_WH_D, KC_MS_DOWN, KC_WH_U, G(KC_MINS), KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,      C(S(KC_TAB)),  KC_DOWN,  C(KC_TAB),      KC_NO,       KC_NO,
                                        KC_TRNS,    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,       KC_TRNS),
    [_MEDIA_CODE] = LAYOUT(
        KC_TRNS,      KC_NO, KC_BRIU, KC_VOLU, KC_MNXT, KC_NO,                                                        KC_NO,   G(KC_X),    G(KC_C),    G(KC_V), KC_NO, KC_TRNS,
        TO(_LETTERS), KC_NO, KC_NO,   KC_MUTE, KC_MPLY, G(C(KC_SPACE)),                                               KC_NO,   G(S(KC_D)), G(KC_UP),   G(KC_Y), KC_NO, KC_NO,
        KC_TRNS,      KC_NO, KC_BRID, KC_VOLD, KC_MPRV, KC_NO,          KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   G(KC_F),    G(KC_DOWN), G(KC_H), KC_NO, KC_NO,
                                    KC_TRNS,   KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS),
    [_KBD_CTRL] = LAYOUT(
        KC_TRNS,      KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,                                                        KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO, KC_TRNS,
        TO(_LETTERS), KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,                                                        KC_NO, RGB_VAI, RGB_TOG, KC_NO, KC_NO, KC_NO,
        KC_TRNS,      KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,                            KC_NO, KC_NO, KC_NO, RGB_VAD, KC_NO,   KC_NO, KC_NO, KC_NO,
                                KC_TRNS,   KC_TRNS, KC_NO, KC_NO, KC_NO,                            KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS)
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
            oled_write_P(PSTR("\n\nLetters"), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("\n\nSymbols"), false);
            break;
        case _NUMBERS:
            oled_write_P(PSTR("\n\nNumbers"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("\n\nNav"), false);
            break;
        case _MEDIA_CODE:
            oled_write_P(PSTR("<-- Media \n\n Code -->"), false);
            break;
        case _KBD_CTRL:
            oled_write_P(PSTR("\n\nKeeb Ctrl"), false);
            break;
        default:
            oled_write_P(PSTR("\n\nFallback"), false);
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
    rgblight_sethsv_noeeprom(HSV_OFF);
}

void sethsv_master(uint8_t hue, uint8_t sat, uint8_t val) { rgblight_sethsv_range(hue, sat, val, 0, (uint8_t)RGBLED_NUM / 2); }

// called on every layer change
// set the colour according to active layer
layer_state_t layer_state_set_user(layer_state_t state) {
    // setrgb, sethsv_noeeprom, setrgb_range do not write to eeprom
    switch (get_highest_layer(state)) {
        case _LETTERS:
            rgblight_sethsv_noeeprom(HSV_OFF);
            break;
        case _SYMBOLS:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case _NUMBERS:
            rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
            break;
        case _NAV:
            rgblight_sethsv_noeeprom(HSV_CHARTREUSE);
            break;
        case _MEDIA_CODE:
            rgblight_sethsv_noeeprom(235, 249, 186);
            sethsv_master(HSV_WHITE);
            break;
        case _KBD_CTRL:
            rgblight_sethsv_noeeprom_red();
            break;
        default:  //  for any other layers (that should not exist/be accessible)
            rgblight_setrgb(HSV_RED);
            break;
    }
    return state;
}
#endif
