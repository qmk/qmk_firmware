#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Default Layer
    * ------------------------------------------------------------------------------------------------------------------------------
    * | Tab   || Q     || W     || E     || R     || T     ||       || Y     || U     || I     || O     || P     || [     || ]     |
    * |----------------------------------------------------------------------------------------------------------------------------|
    * | ESC   || A     || S     || D     || F     || G     ||       || H     || J     || K     || L     || ;     || Enter ||       |
    * |----------------------------------------------------------------------------------------------------------------------------|
    * | Shift || Z     || X     || C     || V     || B     ||       || N     || M     || ,     || .     || /     || "     || Shift |
    * |----------------------------------------------------------------------------------------------------------------------------|
    * | Ctrl  || Super ||       ||       || Alt   || Bkspc ||       || Space || MO(1) ||       ||       ||       || Alt   || Ctrl  |
    * ------------------------------------------------------------------------------------------------------------------------------
    */
    LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT, KC_RSFT,
        KC_LCTL, KC_LWIN,                   KC_LALT, KC_BSPC,          KC_SPC,  MO(1),                              KC_RALT, KC_RCTL
    ),

    /* Secondary Layer
    * ------------------------------------------------------------------------------------------------------------------------------
    * | `     || 1     || 2     || 3     || 4     || 5     ||       || 6     || 7     || 8     || 9     || 0     || -     || =     |
    * |----------------------------------------------------------------------------------------------------------------------------|
    * |       ||       ||       ||       ||       || \     ||       || Left  || Down  || Up    || Right || Del     || Enter ||       |
    * |----------------------------------------------------------------------------------------------------------------------------|
    * |       || Z     || X     || C     || V     || B     ||       || N     || M     || ,     || .     || /     || "     || Shift |
    * |----------------------------------------------------------------------------------------------------------------------------|
    * |       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       |
    * ------------------------------------------------------------------------------------------------------------------------------
    */
    LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_TRNS,
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS
    )
};
