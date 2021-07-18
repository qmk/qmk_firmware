#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define ETC  2 // etc

enum macro_id {
    TEENSY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_ergodox(
    KC_NO,          KC_NO,         KC_NO,   KC_NO,    KC_NO,          KC_NO,  KC_NO,
    KC_TAB,         KC_Q,          KC_W,    KC_D,     KC_F,           KC_K,   KC_PGUP,
    CTL_T(KC_ESC),  LT(ETC,KC_A),  KC_S,    KC_E,     KC_T,           KC_G,
    KC_LSFT,        KC_Z,          KC_X,    KC_C,     KC_V,           KC_B,   KC_PGDN,
    KC_GRV,         KC_DEL,        KC_DEL,  KC_LALT,  GUI_T(KC_TAB),
                                                                      KC_NO,  KC_NO,
                                                                              KC_NO,
                                           LT(SYMB,KC_BSPC),  CTL_T(KC_ESC),  KC_NO,

    KC_NO,    KC_NO,  KC_NO,          KC_NO,           KC_NO,    KC_NO,    KC_NO,
    KC_VOLU,  KC_J,   KC_U,           KC_R,            KC_L,     KC_SCLN,  KC_BSLS,
              KC_Y,   KC_N,           KC_I,            KC_O,     KC_H,     KC_QUOT,
    KC_VOLD,  KC_P,   KC_M,           KC_COMM,         KC_DOT,   KC_SLSH,  KC_RSFT,
                      GUI_T(KC_TAB),  ALT_T(KC_LEFT),  KC_DOWN,  KC_UP,    LCAG_T(KC_RGHT),
    KC_WAKE,  KC_PWR,
    KC_NO,
    KC_NO,    SFT_T(KC_ENT),  LT(SYMB,KC_SPC)
),

[SYMB] = LAYOUT_ergodox(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_TRNS,  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_TRNS,
    KC_TRNS,  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_BSLS,
    KC_TRNS,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_ASTR,  KC_TRNS,
    KC_TILD,  KC_AMPR,  KC_AMPR,  KC_TRNS,  KC_TRNS,
                                                      KC_TRNS,  KC_TRNS,
                                                                KC_TRNS,
                                              KC_TRNS, KC_TRNS, KC_TRNS,

    KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO,   KC_NO,    KC_NO,
    KC_TRNS,  KC_EQL,   KC_7,   KC_8,   KC_9,    KC_PLUS,  KC_NO,
              KC_MINS,  KC_4,   KC_5,   KC_6,    KC_QUOT,  KC_NO,
    KC_TRNS,  KC_UNDS,  KC_1,   KC_2,   KC_3,    KC_DQUO,  KC_TRNS,
                        KC_0,   KC_NO,  KC_DOT,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,
    KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS
),

[ETC] = LAYOUT_ergodox(
    RESET,    KC_NO,         KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_TRNS,  KC_NO,         KC_NO,  KC_NO,    KC_NO,    KC_PGUP,  KC_TRNS,
    KC_TRNS,  LT(ETC,KC_A),  KC_NO,  KC_NO,    KC_NO,    KC_PGDN,
    KC_TRNS,  KC_NO,         KC_NO,  KC_NO,    KC_NO,    KC_DEL,   KC_TRNS,
    KC_TRNS,  KC_TRNS,       KC_NO,  KC_TRNS,  KC_TRNS,
                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                                 KC_TRNS, KC_TRNS, KC_TRNS,

    KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO,   KC_NO,    KC_NO,
    KC_TRNS,  KC_VOLU,  KC_F7,  KC_F8,  KC_F9,   KC_HOME,  KC_NO,
              KC_VOLD,  KC_F4,  KC_F5,  KC_F6,   KC_END,   KC_NO,
    KC_TRNS,  KC_MUTE,  KC_F1,  KC_F2,  KC_F3,   KC_INS,   KC_TRNS,
                        KC_NO,  KC_NO,  KC_NO,   KC_NO,    KC_NO,
    KC_TRNS,  KC_TRNS,
    KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case TEENSY:
      break;
  }
  return MACRO_NONE;
};

void matrix_init_user(void) {
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            break;
    }
};
