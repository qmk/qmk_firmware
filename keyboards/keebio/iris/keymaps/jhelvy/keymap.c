#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT( \
                  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_EQL, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,  KC_ENT, \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_NO,            KC_NO,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, \
                                    LALT(KC_A),KC_LGUI,    MO(1),                    KC_SPC,  MO(2),     KC_PGDN),

[_LOWER] = LAYOUT( \
                  KC_ESC,LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),                            KC_SCLN, KC_PIPE, KC_COLN,LCTL(KC_9),LCTL(KC_0),     KC_F12, \
  LCTL(KC_TAB),LGUI(KC_Q),LGUI(KC_W),  KC_ESC,LGUI(KC_R),LGUI(KC_T),                         LCTL(KC_Y),LGUI(KC_LEFT),   KC_UP,LGUI(KC_RGHT), KC_TILD,     KC_F11, \
  LGUI(KC_BSPC),MO(2),LGUI(KC_S),LGUI(KC_C),LGUI(KC_V),LGUI(KC_X),                             KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT,     KC_GRV,  KC_ENT, \
         KC_F15,LGUI(KC_A),LGUI(KC_D),  KC_F13,LGUI(KC_Z),LGUI(KC_Y),     KC_NO,            KC_NO,KC_BSPC,LGUI(KC_F), SGUI(KC_G),LGUI(KC_G),  KC_BSLS,  KC_F23, \
                                       KC_LALT,KC_LGUI,  KC_TRNS,                    KC_SPC,KC_RGUI,     KC_PGUP),

[_RAISE] = LAYOUT( \
                 KC_VOLU,LGUI(LALT(KC_1)),LGUI(LALT(KC_2)),   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,    KC_PLUS, \
       KC_VOLD, KC_NO,   KC_NO,   KC_NO,SGUI(KC_R),  KC_F14,                         SGUI(KC_K),SGUI(KC_LEFT),LSFT(KC_UP),SGUI(KC_RGHT),  KC_F18,    KC_UNDS, \
        KC_MUTE,KC_TRNS,   KC_NO, KC_LBRC, KC_RBRC,  KC_TAB,                             KC_F21,LSFT(KC_LEFT),LSFT(KC_DOWN),LSFT(KC_RGHT),     KC_F20,  KC_F16, \
        KC_LSPO,KC_ASTG,   KC_NO, KC_LCBR, KC_RCBR,LCTL(KC_U),     KC_NO,            KC_NO,KC_F22,LCTL(LGUI(KC_A)),LALT(LSFT(KC_LEFT)),LALT(LSFT(KC_RIGHT)),   KC_F17,  KC_F19, \
                                       KC_CAPS,LALT(KC_SPC),  KC_LGUI,                    KC_SPC,KC_TRNS,       KC_NO)

};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
