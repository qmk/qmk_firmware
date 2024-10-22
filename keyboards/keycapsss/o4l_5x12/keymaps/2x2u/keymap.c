#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _LOWER
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | ESC  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BSPC |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | Alt  | GUI  |Lower |    Enter    |    Space    | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_ortho_5x12_2x2u(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        QK_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL, KC_LALT, KC_LGUI, LOWER,      KC_ENT,           KC_SPC,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |RGBPLA|   {  |   [  |   (  |      |      |   )  |   ]  |   }  |      |      |  |   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |RGBMOD|      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |UGlow | Reset|      |      |             |             | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_ortho_5x12_2x2u(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, KC_DEL,
        RGB_M_P, KC_LCBR, KC_LBRC, KC_LPRN, KC_SLSH, KC_BSLS, KC_RPRN, KC_RBRC, KC_RCBR, _______, _______, KC_PIPE,
        UG_NEXT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        UG_TOGG, QK_BOOT, _______, _______,     _______,          _______,      KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
    }
    return true;
};
