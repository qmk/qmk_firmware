// Below layout is based upon /u/That-Canadian's planck layout
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QWERTY,
    _RGB,
    _FUNC
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-------------.
     * |   1  |  2   |
     * |------+------|
     * |   3  |  4   |
     * |------+------|
     * |   5  |  6   |
     * |------+------|
     * | FUNC | RGB  |
     * `-------------'
     */
    [_QWERTY] = LAYOUT(
        KC_1,      KC_2,
        KC_3,      KC_4,
        KC_5,      KC_6,
        MO(_FUNC), TG(_RGB)
      ),

    /* RGB
     * ,-------------.
     * | Mode-| Mode+|
     * |------+------|
     * | HUE- | HUE+ |
     * |------+------|
     * | SAT- | SAT+ |
     * |------+------|
     * |RGBTOG|      |
     * `-------------'
     */
    [_RGB] = LAYOUT(
        UG_PREV,  UG_NEXT,
        UG_HUED,  UG_HUEU,
        UG_SATD,  UG_SATU,
        UG_TOGG,  KC_TRNS
      ),

    /* Function
     * ,-------------.
     * |   Q  |CALDEL|
     * |------+------|
     * |   A  |TSKMGR|
     * |------+------|
     * |   Z  |  X   |
     * |------+------|
     * |      |  C   |
     * `-------------'
     */
    [_FUNC] = LAYOUT(
        KC_Q,    CALTDEL,
        KC_A,    TSKMGR,
        KC_Z,    KC_X,
        _______, KC_C
      )

};
