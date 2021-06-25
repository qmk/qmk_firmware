#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum layers { _LETTERS = 0, _SYMBOLS, _NUMBERS, _MEDIA, _KBD_CTRL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LETTERS] = LAYOUT(LGUI(KC_TAB), KC_X, KC_DOT, KC_O, KC_COMM, KC_Y, KC_V, KC_G, KC_C, KC_L, KC_J, LGUI(KC_SPC), LT(4, KC_ESC), LSFT_T(KC_H), LCTL_T(KC_A), LALT_T(KC_E), LGUI_T(KC_I), KC_U, KC_D, RGUI_T(KC_T), RALT_T(KC_R), RCTL_T(KC_N), RSFT_T(KC_S), KC_F, KC_NO, KC_K, KC_Q, DE_ADIA, DE_UDIA, DE_ODIA, KC_NO, KC_NO, KC_NO, KC_NO, KC_B, KC_P, KC_W, KC_M, KC_Z, DE_SS, KC_HOME, KC_BSPC, LT(3, KC_TAB), LT(2, KC_SPC), LT(1, KC_ENT), LT(1, KC_ENT), LT(2, KC_SPC), LT(3, KC_TAB), KC_DEL, KC_END),

  [_SYMBOLS] = LAYOUT(KC_TRNS, KC_AT, KC_PERC, KC_LCBR, KC_RCBR, KC_PIPE, KC_EXLM, KC_LT, KC_GT, KC_EQL, KC_AMPR, KC_TRNS, KC_TRNS, LSFT_T(KC_CIRC), LCTL_T(KC_TILD), LALT_T(KC_LPRN), LGUI_T(KC_RPRN), KC_ASTR, KC_QUES, RGUI_T(KC_SLSH), RALT_T(KC_COLN), RCTL_T(KC_MINS), RSFT_T(KC_UNDS), KC_NO, KC_TRNS, DE_EURO, KC_DLR, KC_LBRC, KC_RBRC, KC_HASH, KC_NO, KC_NO, KC_NO, KC_NO, KC_GRV, KC_RO, KC_SCLN, KC_PLUS, KC_DQUO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [_NUMBERS] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, LSFT_T(KC_1), LCTL_T(KC_2), LALT_T(KC_3), LGUI_T(KC_4), KC_5, KC_6, RGUI_T(KC_7), RALT_T(KC_8), RCTL_T(KC_9), RSFT_T(KC_0), KC_F12, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_WH_U, KC_WH_D, KC_TRNS),

  [_MEDIA] = LAYOUT(KC_TRNS, KC_NO, KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, RGUI(KC_X), RGUI(KC_R), KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_BRIU, KC_VOLU, KC_MPLY, KC_MNXT, KC_NO, G(C(KC_SPACE)), RGUI(KC_C), RGUI(KC_Z), RGUI(KC_F), G(S(KC_T)), KC_NO, KC_TRNS, KC_BRID, KC_VOLD, KC_NO, KC_MPRV, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGUI(KC_V), SGUI(KC_Z), KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [_KBD_CTRL] = LAYOUT(KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, RGB_SAI, RGB_HUI, RGB_VAI, KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_SPI, KC_NO, KC_NO, KC_TRNS, KC_NO, RGB_SAD, RGB_HUD, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_SPD, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

/*
// not fully understood yet, see https://docs.qmk.fm/#/ref_functions?id=update_tri_layer_statestate-x-y-z
// seems like layer 3 can only be accessed from layer 1 and 2 or something like that?
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _MEDIA);
}
*/

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_status(void) {
    // Host Keyboard Layer Status
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

    //if (get_mods() & MOD_MASK_SHIFT) {

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
