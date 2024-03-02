#include QMK_KEYBOARD_H


#define KC_____ KC_TRNS
#define KC_FN MO(1) // Fn
#define KC_FNLK TG(1) // Fn lock
#define KC_HOME LGUI(KC_LEFT) // Home, or cmd-left
#define KC_END LGUI(KC_RGHT) // End, or cmd-right
#define KC_SLP LGUI(LALT(KC_PWR)) // sleep, or cmd-option-power
#define KC_SCLK LCTL(LSFT(KC_PWR)) // lock screen, or ctrl-shift-power

// Mark I keyboard layout for GH60 Satan
// http://www.keyboard-layout-editor.com/#/gists/e1cde292bd2094cc3b763206d4d2cfb5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // 0: qwerty
  [0] = LAYOUT_all(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_NO,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO,   KC_ENT,
    KC_LSFT, KC_FN,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_FN,
    KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                      KC_RGUI, KC_RALT, KC_RCTL, KC_FNLK
  ),
  // 1: fn layer
  [1] = LAYOUT_all(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______,
    _______, KC_VOLU, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______,
    _______, KC_VOLD, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, _______,
    _______, _______, KC_MUTE, _______, _______, _______, _______, _______, _______, KC_SCLK, KC_SLP,  _______, _______, _______,
    _______, _______, _______,                   _______,                                     _______, _______, _______, _______
  )
};