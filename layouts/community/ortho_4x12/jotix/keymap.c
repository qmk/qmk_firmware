#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define LOWER   TT(_LOWER)
#define RAISE   TT(_RAISE)
#define TAB_ADJ LT(_ADJUST, KC_TAB)

#define FN_LAYER LAYOUT_ortho_4x12 (\
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,\
    KC_CAPS, KC_VOLD, KC_MUTE, KC_VOLU, KC_HOME, KC_PGUP, KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, _______, _______,\
    _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_END,  KC_PGDN, KC_MINS, KC_EQL,  _______, _______, _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
),

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* qwerty
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |   esc  |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |  bksp  |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |tab/adj |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |  enter |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * | lshift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |   up   |    /   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |  lctrl |  lgui  |  lalt  |  ralt  |  lower |  space |  space |  raise |   del  |  right |  down  |  right | 
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 */
[_QWERTY] = LAYOUT_ortho_4x12 ( 
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    TAB_ADJ, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,
    KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT
),

[_LOWER] = FN_LAYER

[_RAISE] = FN_LAYER

/* 
 * Adjust 
 */
[_ADJUST] = LAYOUT_ortho_4x12 (
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, RESET,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),     
};

uint32_t layer_state_set_user(uint32_t state) {

  #ifdef JOTANCK_LEDS
  switch (biton32(state)) { 
  case _LOWER:
    writePinHigh(JOTANCK_LED1);
    writePinLow(JOTANCK_LED2);
    break;
  case _RAISE:
    writePinLow(JOTANCK_LED1);
    writePinHigh(JOTANCK_LED2);
    break;
  case _ADJUST:
    writePinHigh(JOTANCK_LED1);
    writePinHigh(JOTANCK_LED2);
    break; 
  default:
    writePinLow(JOTANCK_LED1);
    writePinLow(JOTANCK_LED2);
    break; 
  };
  #endif
  return state;
}

void matrix_init_user(void) {
}
