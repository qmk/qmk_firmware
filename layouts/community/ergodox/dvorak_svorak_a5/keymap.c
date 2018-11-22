#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_swedish.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MOUS 2 // mouse keys
#define QWRT 3 // qwerty layout

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  | ~MOUS|           | QWRT |   6  |   7  |   8  |   9  |   0  |    +   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Å  |   Ä  |   Ö  |   P  |   Y  |      |           |  Del |   F  |   G  |   C  |   R  |   L  |   ,    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Escape |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  |  -/_   |
 * |--------+------+------+------+------+------|      |           | RCTRL|------+------+------+------+------+--------|
 * | LShift |   .  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *  | LCTRL |      |      | LAlt | Super|                                       | ~SYMB| Left | Down |  Up  | Right |
 *  `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  Ins |  Del |       | HOME |  END |
 *                                 ,------|------|------|       |------+--------+-------.
 *                                 |      |      |      |       | PgUp |        |       |
 *                                 | BSP  | Tab  |------|       |------|  Enter | Space |
 *                                 |      |      |      |       | PgDn |        |       |
 *                                 `--------------------'       `-----------------------'
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_NO,    KC_1,   KC_2,     KC_3,    KC_4,    KC_5,      MO(MOUS),
        KC_TAB,   NO_AA,  NO_AE,    NO_OSLH, KC_P,    KC_Y,      KC_NO,
        KC_ESC,   KC_A,   KC_O,     KC_E,    KC_U,    KC_I,
        KC_LSFT,  KC_DOT, KC_Q,     KC_J,    KC_K,    KC_X,      KC_NO,
        KC_LCTRL, KC_NO,  KC_NO,    KC_LALT, KC_LCMD,
                                                      KC_INSERT, KC_DEL,
                                                                 KC_NO,
                                             KC_BSPC, KC_TAB,    KC_NO,
        // right hand
        TG(QWRT), KC_6,   KC_7,     KC_8,    KC_9,    KC_0,      NO_PLUS,
        KC_DEL,   KC_F,   KC_G,     KC_C,    KC_R,    KC_L,      KC_COMM,
                  KC_D,   KC_H,     KC_T,    KC_N,    KC_S,      NO_MINS,
        KC_RCTRL, KC_B,   KC_M,     KC_W,    KC_V,    KC_Z,      KC_RSFT,
                          MO(SYMB), KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT,
        KC_HOME,  KC_END,
        KC_PGUP,
        KC_PGDN,  KC_ENT, KC_SPACE
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   {  |   }  |   [  |   ]  |   $  |      |           |      |   "  |   ?  |   &  |   <  |   >  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   ;  |   /  |   (  |   )  |   |  |------|           |------|   #  |   ^  |   #  |   "  |   ~  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   :  |   =  |   @  |   !  |   \  |      |           |      |   %  |   ´  |   '  |   *  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |       |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |  BSP |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_NO, KC_NO,         KC_NO,       KC_NO,      KC_NO,      KC_NO,            KC_NO,
       KC_NO, ALGR(KC_7),    ALGR(KC_0),  ALGR(KC_8), ALGR(KC_9), ALGR(KC_4),       KC_NO,
       KC_NO, LSFT(KC_COMM), KC_KP_SLASH, LSFT(KC_8), LSFT(KC_9), ALGR(KC_NUBS),
       KC_NO, LSFT(KC_DOT),  LSFT(KC_0),  ALGR(KC_2), KC_EXLM,    ALGR(KC_MINS),    KC_NO,
       KC_NO, KC_NO,         KC_NO,       KC_NO,      KC_NO,
                                                      KC_NO,   KC_NO,
                                                               KC_NO,
                                             KC_TRNS, KC_NO,   KC_NO,
       // right hand
       KC_NO, KC_NO,         KC_NO,       KC_NO,       KC_NO,       KC_NO,   KC_NO,
       KC_NO, LSFT(KC_2),    NO_QUES,     LSFT(KC_6),  NO_LESS,     NO_GRTR, KC_NO,
              KC_HASH,       NO_CIRC,     KC_HASH,     LSFT(KC_2),  NO_TILD, KC_NO,
       KC_NO, KC_PERC,       NO_ACUT,     NO_APOS,     NO_ASTR,     NO_GRV,  KC_NO,
                             KC_NO,       KC_NO,       KC_NO,       KC_NO,   KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO,         KC_NO
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | F11  | F12  |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      | Vol Up |
 * |--------+------+------+------+------+------|      |           | RCTRL|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |  B1  |  B2  |Vol Down|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCTRL|      |      | LALT |      |                                       |      |  M_L |  M_D |  M_U |  M_R  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      | Play |
 *                                 |      |      |      |       |      |      | Pause|
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MOUS] = LAYOUT_ergodox(
       KC_NO,   KC_F1,  KC_F2, KC_F3,   KC_F4, KC_F5, KC_NO,
       KC_NO,   KC_F11, KC_F12, KC_NO,  KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO,  KC_NO, KC_NO,   KC_NO, KC_NO,
       KC_NO,   KC_NO,  KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_NO,  KC_NO, KC_TRNS, KC_NO,
                                                KC_NO, KC_NO,
                                                       KC_NO,
                                       KC_NO,   KC_NO, KC_NO,
    // right hand
       KC_NO,    KC_F6, KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_NO,
       KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
                KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_VOLU,
       KC_TRNS, KC_NO, KC_NO, KC_NO,   KC_BTN1, KC_BTN2, KC_VOLD,
                      KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
       KC_NO,   KC_NO,
       KC_NO,
       KC_NO,   KC_NO, KC_MPLY
),
/* Keymap 3: QWERTY Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Print  |   !  |  "   |  #   |  #   |  %   |      |           |Middle|   &  |  /   |  (   |  )   |  =   |  ?     |
 * | Screen |   1  |  2 @ |  3 £ |  4 $ |  5   | F11  |           |Mouse |   6  |  7 { |  8 [ |  9 ] |  0 } |  + \   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    | Q    | W    | E    | R    | T    |      |           |      | Y    | U    | I    | O    | P    | Å      |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CapsLk | A    | S    | D    | F    | G    |------|           |------| H    | J    | K    | L    | Ö    | Ä      |
 * |--------+------+------+------+------+------| `    |           | Del  |------+------+------+------+------+--------|
 * | LShft  | Z    | X    | C    | V    | B    |  '   |           |      | N    | M    | ,    | .    | -    | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtl |  ^   | *    | LAlt | LGui |                                       | AltGr| Down |  Up  | Left | Right|
 *   | (')  |  " ~ | '  ´ |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,--------------.
 *                                        | LCtl | LAlt |       | Home |   End  |
 *                                 ,------|------|------|       |------+-------+------.
 *                                 |      |      |  ~   |       | PgUp |       |      |
 *                                 | BSP  |  TAB |------|       |------| Enter | Space|
 *                                 |      |      | Esc  |       | PgDn |       |      |
 *                                 `--------------------'       `---------------------'
 */
[QWRT] = LAYOUT_ergodox(
    // left hand
    KC_PSCR,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_TRNS,
    KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_TRNS,
    KC_CAPS,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
    KC_LSFT,        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     NO_ACUT,
    CTL_T(NO_APOS), NO_CIRC, NO_ASTR, KC_LALT, KC_LGUI,
                                                        KC_LCTRL, KC_LALT,
                                                                  NO_TILD,
                                               KC_BSPC, KC_TAB,   KC_ESC,
    // right hand
    KC_TRNS,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     NO_PLUS,
    KC_TRNS,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     NO_AA,
                    KC_H,    KC_J,    KC_K,    KC_L,    NO_OSLH,  NO_AE,
    KC_DELT,        KC_N,    KC_M,    KC_COMM, KC_DOT,  NO_MINS,  KC_RSFT,
                             NO_ALGR, KC_DOWN, KC_UP,   KC_LEFT,  KC_RGHT,
    KC_HOME,        KC_END,
    KC_PGUP,
    KC_PGDN,        KC_ENT, KC_SPACE
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
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
        case 3:
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
