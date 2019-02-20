#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY   0
#define _LOWER    1
#define _RAISE    2
#define _FUNCTION 3

enum planck_keycodes {
  BACKLIT = SAFE_RANGE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNCT LT(_FUNCTION, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |   esc  |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |  bksp  |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |  func  |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |   del  |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * | lshift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |   up   |  enter |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |  lctrl |  lgui  |  lalt  |  ralt  |  lower |  space |  space |  raise |    /   |  left  |  down  |  right | 
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 */
[_QWERTY] = LAYOUT_ortho_4x12 ( 
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    FUNCT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_DEL,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Lower
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |        |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |        |  vol-  |  mute  |  vol+  |        |        |    `   |    -   |    =   |    [   |    ]   |        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |        |  prev  |  play  |  next  |        |        |    \   |    '   |        |        |        |        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 */
[_LOWER] = LAYOUT_ortho_4x12 (
     _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
     _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, KC_GRV,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
     _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_BSLS, KC_QUOT, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |        |    !   |    @   |    #   |    $   |    %   |    ^   |    &   |    *   |    (   |    )   |        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |        |        |        |        |        |        |    ~   |    _   |    +   |    {   |    }   |        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |        |        |        |        |        |        |    |   |    "   |        |        |  pgup  |        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 * |        |        |        |        |        |        |        |        |        |  home  |  pgdn  |   end  |
 * +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 */
[_RAISE] = LAYOUT_ortho_4x12 (
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, _______, _______, _______, _______, _______, KC_TILD, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
    _______, _______, _______, _______, _______, _______, KC_PIPE, KC_DQUO, _______, _______, KC_PGUP, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
),

/*
 * Function
 */
[_FUNCTION] = LAYOUT_ortho_4x12 (
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  BACKLIT, _______, KC_CAPS, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
};

void matrix_init_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
                #ifdef BACKLIGHT_ENABLE
                backlight_step();
                #endif
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
	    break;

	default:
	    return true;

    }
}
