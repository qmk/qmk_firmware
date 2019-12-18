/*
 * GHERKIN - Gaming mini-mouse
 * Keymap by @bbaserdem
 * Check qmk_firmware/users/bbaserdem for the main part of the code
 */

#include QMK_KEYBOARD_H
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Game pad
 * ,-----------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  | Ctl | Alt |  ~  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | Tab |  Q  |  W  |  E  |  R  |  T  | |^| |  ;  |  '  |  /  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | Shf |  A  |  S  |  D  |  F  | <-- | |v| | --> |  ,  |  .  |
 * `-----------------------------------------------------------'
 */
    LAYOUT_ortho_3x10(
        KC_ESCAPE, KC_1, KC_2, KC_3, KC_4, KC_5,    KC_6,    KC_LCTRL, KC_LALT,  KC_GRAVE,
        KC_TAB,    KC_Q, KC_W, KC_E, KC_R, KC_T,    KC_UP,   KC_SCLN,  KC_QUOTE, KC_SLASH,
        KC_LSHIFT, KC_A, KC_S, KC_D, KC_F, KC_LEFT, KC_DOWN, KC_RIGHT, KC_COMMA, KC_DOT
    )
};

void keyboard_post_init_keymap(void) {
    // Set RGB to rainbow mood light
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(6);
    rgblight_sethsv_noeeprom(120,255,255);
    rgblight_mode_noeeprom(6);
#endif
}
