#include "kb.h"
#include "stdio.h"

enum layers {
    _QWERTY = 0,
    _NUMPAD,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = KEYMAP(
        KC_MUTE, KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,   KC_Y,   KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,       KC_G,   KC_H,   KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,   KC_N,   KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_BSPC, KC_LCTL, KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_SPC, MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),

    [_NUMPAD] = KEYMAP(
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7, KC_P8,   KC_P9,   KC_PSLS,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4, KC_P5,   KC_P6,   KC_PAST,
        KC_TRNS, TG(_NUMPAD), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1, KC_P2,   KC_P3,   KC_PENT,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_PMNS, KC_PPLS),

    [_LOWER] = KEYMAP(
        KC_VOLD, KC_EXLM,       KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,      KC_RPRN,       KC_INS,
        KC_NLCK, KC_F7,         KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_LCBR, KC_RCBR, KC_UNDS,      KC_PLUS,       LSFT(KC_NUHS),
        KC_TRNS, LSFT(KC_NUBS), KC_GRAVE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_GRV), LSFT(KC_NUBS), KC_TRNS,
        KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN,      KC_PGUP,       KC_END),

    [_RAISE] = KEYMAP(
        KC_VOLU, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_NUHS,
        KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV,  KC_NUBS, KC_TRNS,
        KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT),

    [_ADJUST] = KEYMAP(
        KC_TRNS, RGB_TOG,     RGB_MOD, RGB_HUD, RGB_HUI,  RGB_SAD,  RGB_SAI, RGB_VAD, RGB_VAI, KC_TRNS, KC_TRNS, RESET,
        KC_TRNS, RGB_M_P,     RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, KC_TRNS, KC_TRNS,
        KC_TRNS, TG(_NUMPAD), KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST))) {
    case _RAISE:
        setrgb (0x6E,  0x19, 0x17, (LED_TYPE *)&led[7]);
        break;
    case _LOWER:
        setrgb (0x15,  0x50, 0x4C, (LED_TYPE *)&led[7]);
        break;
    case _ADJUST:
        setrgb (0x7E,  0x7B, 0x71, (LED_TYPE *)&led[7]);
        break;
    case _NUMPAD:
        setrgb (0x00,  0x00, 0xFF, (LED_TYPE *)&led[7]);
        break;
    default: //  for any other layers, or the default layer
        setrgb (0x00,  0x00, 0x00, (LED_TYPE *)&led[7]);
        break;
    }

    rgblight_set();

    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

// Uncomment this function if debug mode is needed
/* void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
} */

#ifdef OLED_DRIVER_ENABLE

static void render_status(void) {
    oled_write_P(PSTR("Tau.4 v1.0\n\n"), false);
    oled_write_P(PSTR("Layer:\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default  "), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Numpad   "), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower    "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise    "), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust   "), false);
            break;
        default:
            oled_write_P(PSTR("Undefined"), false);
    }
}

void oled_task_user(void) {
    render_status();
}
#endif
