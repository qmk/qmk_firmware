#include "MiniVan20191030092705.h"
enum custom_keycodes {
M_IME = SAFE_RANGE
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
if (record->event.pressed) {
switch(keycode) {
case M_IME:
SEND_STRING(SS_DOWN(X_LSHIFT)SS_DOWN(X_LALT));
return false;
}
}
else {
switch(keycode) {
case M_IME:
SEND_STRING(SS_UP(X_LSHIFT)SS_UP(X_LALT));
return false;
}
}
return true;
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(KC_ESC, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, LCTL_T(KC_TAB), KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, RCTL_T(KC_MINS), KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT, KC_LALT, KC_LEFT, TT(3), KC_NO, LT(1, KC_ENT), LT(1, KC_SPC), TG(2), KC_RIGHT, KC_NO, KC_RALT),
[1] = KEYMAP(TO(0), KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, LCTL_T(KC_MINS), KC_1, KC_2, KC_3, KC_4, KC_5, KC_BSLS, KC_EQL, KC_SLSH, KC_LBRC, KC_RBRC, RCTL_T(KC_GRV), LSFT_T(KC_DOT), KC_0, KC_9, KC_8, KC_7, KC_6, KC_PIPE, KC_PLUS, KC_QUES, KC_LCBR, KC_RCBR, RSFT_T(KC_TILD), LALT_T(KC_BSPC), KC_LEFT, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_RIGHT, KC_NO, RALT_T(KC_ENT)),
[2] = KEYMAP(TO(0), TO(1), TO(2), TO(3), TO(4), TO(5), KC_NO, KC_F24, KC_F23, KC_F22, KC_F21, KC_NO, KC_LCTL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F15, KC_F14, KC_F13, KC_F12, KC_F11, KC_RCTL, KC_LSFT, KC_F10, KC_F9, KC_F8, KC_F7, KC_F6, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_RSFT, KC_LALT, KC_LEFT, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_RIGHT, KC_NO, KC_RALT),
[3] = KEYMAP(TO(0), KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO, KC_BTN3, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_NO, KC_LCTL, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_BTN1, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT, KC_RCTL, KC_LSFT, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN2, KC_ACL0, KC_ACL1, KC_ACL2, KC_TILD, KC_RSFT, KC_LALT, KC_LEFT, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_RIGHT, KC_NO, KC_RALT),
[4] = KEYMAP(TO(0), KC_POWER, KC_PWR, KC_SLEP, KC_WAKE, KC_NO, KC_NO, KC_NO, KC_NO, KC_PAUS, KC_SLCK, KC_PSCR, KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_NO, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_RIGHT, KC_NO, KC_NO),
[5] = KEYMAP(TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), KC_P, KC_PAUS, TO(0), TO(0), KC_NO, KC_NO, KC_R, RESET, KC_NO, KC_NO, TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), KC_LSFT, TO(0), TO(0), TO(0), TO(0), TO(0), KC_B, TO(0), TO(0), TO(0), TO(0), KC_RSFT, TO(0), KC_LEFT, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_RIGHT, KC_NO, TO(0)),
};
void matrix_init_user(void) {
rgblight_init();
};
void rgblight_init_leds(void) {
process_indicator_update(layer_state, host_keyboard_leds());
};
void led_set_user(uint8_t usb_led) {
process_indicator_update(layer_state, usb_led);
};
uint32_t layer_state_set_user(uint32_t state) {
process_indicator_update(state, host_keyboard_leds());
return state;
};
void process_indicator_update(uint32_t state, uint8_t usb_led) {
LED_TYPE indicators[3] = {
{.r = 0, .g = 0, .b = 0},
{.r = 0, .g = 0, .b = 0},
{.r = 0, .g = 0, .b = 0}
};
uint8_t indexes[3] = {
0,
1,
2
};
if (state & (1<<1)){
indicators[0].r = 0;
indicators[0].g = 0;
indicators[0].b = 255;
}
if (state & (1<<4)){
indicators[0].r = 255;
indicators[0].g = 255;
indicators[0].b = 0;
}
if (state & (1<<2)){
indicators[1].r = 204;
indicators[1].g = 0;
indicators[1].b = 255;
}
if (state & (1<<5)){
indicators[1].r = 255;
indicators[1].g = 0;
indicators[1].b = 0;
}
if (state & (1<<3)){
indicators[2].r = 0;
indicators[2].g = 255;
indicators[2].b = 30;
}
rgblight_setrgb_many(indicators, indexes, 3);
};