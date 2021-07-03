#include QMK_KEYBOARD_H

enum layer_names {
    _BASE_DVORAK,
    _RAISE,
    _KEYPAD,
};

// Mac-specific macros
#define MACCOPY LGUI(KC_C)
#define MACPAST LGUI(KC_V)
#define MACUNDO LGUI(KC_Z)
#define MACREDO LGUI(KC_Y)
#define MACLOCK LGUI(LCTL(KC_Q))

#define LSA_ LSA(KC_NO)
#define SFT_ESC SFT_T(KC_ESC)
#define S_TRNS S(KC_TRNS)
#define KEYPAD TG(_KEYPAD)
#define RAISE MO(_RAISE)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE_DVORAK] = LAYOUT (
           // Left Hand
           MACLOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_PIPE, KC_PLUS, KC_LBRC, KC_LCBR, KC_LPRN, KC_AMPR,
           KC_TAB,  KC_SCLN, KC_COMM, KC_DOT,  KC_P,    KC_Y,
           SFT_ESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
           KC_LCTL, KC_QUOT, KC_Q,    KC_J,    KC_K,    KC_X,
                    KC_DLR,  KC_BSLS, KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LGUI, KC_LALT,
                             MACPAST,
           KC_BSPC, KC_SPC,  MACCOPY,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KEYPAD,  RESET,
           KC_EQL,  KC_RPRN, KC_RCBR, KC_RBRC, KC_ASTR, KC_EXLM,
           KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS,
           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                    KC_DOWN, KC_UP,   KC_SLSH, KC_AT,
           // Right Thumb
           KEYPAD,  LSA_,
           MACUNDO,
           MACREDO, RAISE, KC_ENT
    ),

[_RAISE] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           _______, S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,
           _______, S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,
           _______, S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,
                    KC_TILD, S_TRNS,  _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PERC,
           S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  KC_HASH,
           S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,
           S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  S_TRNS,  _______,
                    _______, _______, S_TRNS,  KC_CIRC,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),

[_KEYPAD] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST, _______,
           _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
           _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
           _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                    _______, _______, KC_PDOT, KC_PENT,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, KC_P0
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _KEYPAD:
        writePinLow(LED_COMPOSE_PIN);
        break;
    case _RAISE:
        writePinLow(LED_CAPS_LOCK_PIN);
        break;
    default: //  for any other layers, or the default layer
        writePinHigh(LED_NUM_LOCK_PIN);
        writePinHigh(LED_CAPS_LOCK_PIN);
        writePinHigh(LED_SCROLL_LOCK_PIN);
        writePinHigh(LED_COMPOSE_PIN);
        break;
    }
  return state;
}

bool led_update_user(led_t led_state) {
    // Disable led_update_kb() so that layer indication code doesn't get overridden.
    return false;
}
