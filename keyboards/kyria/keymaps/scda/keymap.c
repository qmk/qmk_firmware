#include QMK_KEYBOARD_H
#include "keymap_german_osx.h"

enum layers { _LETTERS = 0, _SYMBOLS, _NUMBERS, _MEDIA, _KBD_CTRL };

// Left-hand home row mods
#define HOMEROW_H CTL_T(KC_H)
#define HOMEROW_A ALT_T(KC_A)
#define HOMEROW_E GUI_T(KC_E)
#define HOMEROW_I SFT_T(KC_I)

// Right-hand home row mods
#define HOMEROW_T SFT_T(KC_T)
#define HOMEROW_R GUI_T(KC_R)
#define HOMEROW_N ALT_T(KC_N)
#define HOMEROW_S CTL_T(KC_S)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LETTERS] = LAYOUT(
        G(KC_TAB), KC_X, DE_DOT, KC_O, DE_COMM, KC_Y,
        KC_V, KC_G, KC_C, KC_L, KC_J, G(KC_SPC),
        LT(4,KC_ESC), HOMEROW_H, HOMEROW_A, HOMEROW_E, HOMEROW_I, KC_U,
        KC_D, HOMEROW_T, HOMEROW_R, HOMEROW_N, HOMEROW_S, KC_F,
        KC_NO, KC_K, KC_Q, DE_ADIA, DE_UDIA, DE_ODIA, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_B, KC_P, KC_W, KC_M, KC_Z, DE_SS,
        KC_HOME, KC_BSPC, LT(_SYMBOLS,KC_TAB), LT(_NUMBERS,KC_SPC), LT(_MEDIA,KC_ENT),
        LT(_MEDIA,KC_ENT), LT(_NUMBERS,KC_SPC), LT(_SYMBOLS,KC_TAB), KC_DEL, KC_END),
    [_SYMBOLS] = LAYOUT(
        KC_TRNS, DE_AT, DE_PERC, DE_LCBR, DE_RCBR, DE_PIPE,
        DE_EXLM, KC_GRV, S(KC_GRV), DE_EQL, DE_AMPR, KC_TRNS,
        KC_TRNS, KC_NUBS, DE_TILD, DE_LPRN, DE_RPRN, DE_ASTR,
        DE_QUES, DE_SLSH, DE_COLN, DE_MINS, DE_UNDS, KC_NO,
        KC_TRNS, DE_EURO, DE_DLR, DE_LBRC, DE_RBRC, DE_HASH, KC_NO, KC_NO,
        KC_NO, KC_NO, DE_GRV, DE_BSLS, DE_SCLN, DE_PLUS, DE_DQUO, DE_QUOT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_NUMBERS] = LAYOUT(
        KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_TRNS, DE_1, DE_2, DE_3, DE_4, DE_5,
        DE_6, DE_7, DE_8, DE_9, DE_0, KC_F12,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_BTN1, KC_BTN2, KC_WH_U, KC_WH_D, KC_TRNS),
    [_MEDIA] = LAYOUT(
        KC_TRNS, KC_NO, KC_MUTE, KC_NO, KC_NO, KC_NO,
        KC_NO, G(KC_X), G(KC_R), KC_NO, C(KC_LEFT), KC_TRNS,
        KC_TRNS, KC_BRIU, KC_VOLU, KC_MPLY, KC_MNXT, KC_NO,
        G(C(KC_SPACE)), G(KC_C), G(KC_Z), G(KC_F), C(KC_UP), KC_NO,
        KC_TRNS, KC_BRID, KC_VOLD, KC_NO, KC_MPRV, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, G(KC_V), G(KC_Z), KC_NO, C(KC_RGHT), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_KBD_CTRL] = LAYOUT(
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_NO, RGB_SAI, RGB_HUI, RGB_VAI, KC_NO,
        KC_NO, RGB_TOG, RGB_MOD, RGB_SPI, KC_NO, KC_NO,
        KC_TRNS, KC_NO, RGB_SAD, RGB_HUD, RGB_VAD, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_SPD, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
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
            oled_write_P(PSTR("KBD_CTRL\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // if (get_mods() & MOD_MASK_SHIFT) {

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

static void render_modifiers(void) {
    // TODO: missing
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_modifiers();
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
            rgblight_sethsv_noeeprom(165, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
            break;
        case _KBD_CTRL:
            rgblight_sethsv_noeeprom(246, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
            break;
        default:  //  for any other layers, or the default layer
            rgblight_sethsv_noeeprom(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
            break;
    }
    return state;
}
#endif
