#include QMK_KEYBOARD_H

/* Add the stings you want to send as macros, see
 * https://docs.qmk.fm/#/feature_macros for what all can be used
 */
#define MACRO_0 "zero"
#define MACRO_1 "one"
#define MACRO_2 "two"
#define MACRO_3 "three"
#define MACRO_4 "four"
#define MACRO_5 "five"
#define MACRO_6 "six"
#define MACRO_7 "seven"
#define MACRO_8 "eight"
#define MACRO_9 "nine"

enum macro_keycodes {
    M0 = SAFE_RANGE,
    M1,
    M2,
    M3,
    M4,
    M5,
    M6,
    M7,
    M8,
    M9
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |   0  |   1  |   4  |   7  | BkSp |OSL(1)|      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ,  |   2  |   5  |   8  |   /  | Down |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   .  |   3  |   6  |   9  |   *  | Up   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |    Enter    |   +  |   -  |   =  | MO(1)|      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[0] = LAYOUT_ortho_4x12(
    KC_KP_0,     KC_KP_1, KC_KP_4,    KC_KP_7,     KC_BSPACE,      OSL(1),  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_COMMA,    KC_KP_2, KC_KP_5,    KC_KP_8,     KC_KP_SLASH,    KC_DOWN, KC_NO, KC_A,  KC_B,  KC_C,  KC_D,  KC_NO,
    KC_KP_DOT,   KC_KP_3, KC_KP_6,    KC_KP_9,     KC_KP_ASTERISK, KC_UP,   KC_NO, KC_E,  KC_F,  KC_G,  KC_H,  KC_NO,
    KC_KP_ENTER, KC_NO,   KC_KP_PLUS, KC_KP_MINUS, KC_KP_EQUAL,    MO(1),  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
),
/* Macro layer - the number keys are macros,
 * other functions on remaining keys
 * ,-----------------------------------------.
 * | M(0) | M(1) | M(4) | M(7) |      | Esc  |
 * |------+------+------+------+------+------|
 * | Left | M(2) | M(5) | M(8) |      |      |
 * |------+------+------+------+------+------|
 * | Right| M(3) | M(6) | M(9) |      |      |
 * |------+------+------+------+------+------|
 * |   NumLock   | RESET|      |      | Calc |
 * `-----------------------------------------'
 */
[1] = LAYOUT_ortho_4x12(
    M0,         M1, M4, M7, KC_NO, KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_LEFT,    M2, M5, M8, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_RIGHT,   M3, M6, M8, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NUMLOCK, RESET, KC_NO, KC_NO, KC_CALC, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M0:
            if (record->event.pressed) {
                SEND_STRING(MACRO_0);
            }
            break;
        case M1:
            if (record->event.pressed) {
                SEND_STRING(MACRO_1);
            }
            break;
        case M2:
            if (record->event.pressed) {
                SEND_STRING(MACRO_2);
            }
            break;
        case M3:
            if (record->event.pressed) {
                SEND_STRING(MACRO_3);
            }
            break;
        case M4:
            if (record->event.pressed) {
                SEND_STRING(MACRO_4);
            }
            break;
        case M5:
            if (record->event.pressed) {
                SEND_STRING(MACRO_5);
            }
            break;
        case M6:
            if (record->event.pressed) {
                SEND_STRING(MACRO_6);
            }
            break;
        case M7:
            if (record->event.pressed) {
                SEND_STRING(MACRO_7);
            }
            break;
        case M8:
            if (record->event.pressed) {
                SEND_STRING(MACRO_8);
            }
            break;
        case M9:
            if (record->event.pressed) {
                SEND_STRING(MACRO_9);
            }
            break;
    }
    return true;
};
