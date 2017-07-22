#include "ergodox.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * MEH:   Alt+Control+Shift
 * HYPER: Alt+Control+Shift+Gui
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ` ~  |  1 ! | 2 @  | 3 #  | 4 $  | 5 %  |  6 ^ |           | 7 &  |  8 * | 9 (  |  0 ) | - _  | = +  | Backsp |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   TAB  |   Q  |   W  |   F  |   P  |   G  |TG(3) |           |TG(4) |   J  |   L  |   U  |   Y  |  ; : |  ' "   |
 * |--------+------+------+------+------+------|F-lck |           |N-lck |------+------+------+------+------+--------|
 * |  CAPS  |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |  ENT   |
 * |--------+------+------+------+------+------| MEH  |           | MEH  |------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |  , < |  . > |  UP  | Shift  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCTL | LCTL | LGUI | LALT | LGUI |                                       | RALT | RCTL | LEFT | DOWN | RIGHT|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,--------------.
 *                                        |  Esc | App   |       | Ins  | Del   |
 *                                 ,------|------|-------|       |------+-------+------.
 *                                 |      |      | Home  |       | PgUp |       |      |
 *                                 | MO(2)| MO(4)|-------|       |------| Space |Space |
 *                                 |symbol|N-Lock| End   |       | PgDn |       |      |
 *                                 `---------------------'       `---------------------'
 */
[0] = KEYMAP(  // layer 0 : default 
        // left hand
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,        KC_5,        KC_6,
        KC_TAB,     KC_Q,       KC_W,       KC_F,       KC_P,        KC_G,        TG(3),
        KC_CAPS,    KC_A,       KC_R,       KC_S,       KC_T,        KC_D,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,        KC_B,        KC_MEH,
        KC_LCTL,    KC_LCTL,    KC_LGUI,    KC_LALT,    KC_LGUI,

                    KC_ESC,     KC_APP,
                    KC_HOME,
        MO(2),      MO(4),      KC_END,

        // right hand
        KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,     KC_EQL,      KC_BSPC,
        TG(4),      KC_J,       KC_L,       KC_U,       KC_Y,        KC_SCLN,     KC_QUOT,
                    KC_H,       KC_N,       KC_E,       KC_I,        KC_O,        KC_ENT,
        KC_MEH,     KC_K,       KC_M,       KC_COMM,    KC_DOT,      KC_UP,       KC_RSFT,
                                KC_RALT,    KC_RCTL,    KC_LEFT,     KC_DOWN,     KC_RIGHT,

        KC_INS,     KC_DEL,
        KC_PGUP,
        KC_PGDN,    KC_SPC,     KC_SPC
    ),

/* Keymap 1: QWERTY layer (games)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[1] = KEYMAP(  // layer 1: QWERTY layer (games) 
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,        KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_TRNS,
       KC_TRNS,        KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
       KC_TRNS,        KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

                       KC_TRNS,    KC_TRNS,
                                   KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,
       
    // right hand
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,        KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_TRNS,
                       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_TRNS,
       KC_TRNS,        KC_N,       KC_M,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,        KC_TRNS,
       KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS
    ),

/* Keymap 2: Symbol Layer
*
* ,--------------------------------------------------.           ,--------------------------------------------------.
* |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  | F12  |        |
* |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
* |        |   |  |   +  |  <   |   %  |  #   | DF(1)|           |      |  &   |   [  |   ]  |   \  |  :   |   "    |
* |--------+------+------+------+------+------|QWERTY|           |      |------+------+------+------+------+--------|
* |        |   !  |   -  |  >   |   =  |  @   |------|           |------|  *   |   {  |   }  |   /  |  ?   |        |
* |--------+------+------+------+------+------| DF(0)|           |      |------+------+------+------+------+--------|
* |        | NUBS | NUHS |  /   |   $  |  ^   |COLEMAK           |      |  |   |   (  |   )  |      |      |        |
* `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
*   |      |      |      |      |      |                                       |      |      |      |      |      |
*   `----------------------------------'                                       `----------------------------------'
*                                        ,-------------.       ,-------------.
*                                        |      |      |       |      |      |
*                                 ,------|------|------|       |------+------+------.
*                                 |      |      |      |       |      |      |      |
*                                 |      |      |------|       |------|      |      |
*                                 |      |      |      |       |      |      |      |
*                                 `--------------------'       `--------------------'
*/
// SYMBOLS
[2] = KEYMAP(
       // left hand
       KC_TRNS,        KC_F1,        KC_F2,       KC_F3,      KC_F4,       KC_F5,      KC_F6,
       KC_TRNS,        KC_PIPE,      KC_PLUS,     KC_LT,      KC_PERC,     KC_HASH,    DF(1),
       KC_LBRC,        KC_EXCLAIM,   KC_MINUS,    KC_GT,      KC_EQUAL,    KC_AT,
       KC_TRNS,        KC_NUBS,      KC_NUHS,     KC_SLSH,    KC_DOLLAR,   KC_CIRC,    DF(0),
       KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,

                       KC_TRNS,      KC_TRNS,
                                     KC_TRNS,
       KC_TRNS,        KC_TRNS,      KC_TRNS,

       // right hand
       KC_F7,          KC_F8,        KC_F9,        KC_F10,     KC_F11,      KC_F12,     KC_TRNS,
       KC_TRNS,        KC_AMPERSAND, KC_LBRC,      KC_RBRC,    KC_BSLS,     KC_COLN,    KC_DQT,
                       KC_ASTERISK,  KC_LCBR,      KC_RCBR,    KC_SLSH,     KC_QUES,    KC_TRNS,
       KC_TRNS,        KC_PIPE,      KC_LPRN,      KC_RPRN,    KC_TRNS,     KC_TRNS,    KC_TRNS,
                                     KC_TRNS,      KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,

       KC_TRNS,        KC_TRNS,
       KC_TRNS,
       KC_TRNS,        KC_TRNS,      KC_TRNS
),

/* Keymap 3:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      | HYPR |           | HYPR |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------        |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// F-keys
[3] = KEYMAP(
       KC_TRNS,        KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_HYPR,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

                       KC_TRNS,    KC_TRNS,
                                   KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,

       // right hand
       KC_F7,          KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_HYPR,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

       KC_TRNS,        KC_TRNS,
       KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS
),
/* Keymap 4: Numlock
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |      |      |      |P-SCRE|S-LOCK|PAUSE |           |NLOCK | CALC |  =   |  /   |  *   |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | Vol+ |  7   |  8   |  9   |  -   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| Vol- |  4   |  5   |  6   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      | HYPR |           | HYPR | Mute |  1   |  2   |  3   |Enter |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |  0   |  .   | RCTL | RCTL |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------        |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[4] = KEYMAP(
       RESET,          KC_LSFT,    KC_LSFT,    KC_SYSREQ,  KC_PSCR,    KC_SLCK,    KC_PAUSE,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_HYPR,
       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

                       KC_TRNS,    KC_TRNS,
                                   KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS,

       // right hand
       KC_NLCK,        KC_CALC,    KC_PEQL,    KC_PSLS,    KC_PAST,    KC_LSFT,    KC_TRNS,
       KC_TRNS,        KC_VOLU,    KC_P7,      KC_P8,      KC_P9,      KC_PMNS,    KC_TRNS,
                       KC_VOLD,    KC_P4,      KC_P5,      KC_P6,      KC_PPLS,    KC_TRNS,
       KC_HYPR,        KC_MUTE,    KC_P1,      KC_P2,      KC_P3,      KC_PENT,    KC_TRNS,
                                   KC_TRNS,    KC_P0,      KC_PDOT,    KC_RCTL,    KC_RCTL,

       KC_TRNS,        KC_TRNS,
       KC_TRNS,
       KC_TRNS,        KC_TRNS,    KC_TRNS
),

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    static uint8_t state;

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    //reduce LED on time to 1/6th because LEDs are too strong
    if (++state < 6) return;
    state = 0;

    //bit 1: default layer 1 - QWERTY
    if (default_layer_state & (1UL << 1)) ergodox_right_led_1_on();

    uint8_t layer = biton32(layer_state);

    //layer 2 : Symbols (& Fs)
    //if (layer == 2) ergodox_right_led_2_on();

    //layer 3 : F-lock
    if (layer == 3) ergodox_right_led_2_on();

    //layer 4 : Num-lock
    if (layer == 4) ergodox_right_led_3_on();
};
