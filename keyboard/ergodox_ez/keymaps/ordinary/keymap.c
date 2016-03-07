#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

/*
 * Ordinary Ergodox EZ keyboard layout, v1
 * modifications from default by Nicholas Keene ergodoxez@nicholaskeene.com
 * Details: http://nicholas.rinard.us/2016/03/ergodox-ez-layout.html
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Grv   |   1  |   2  |   3  |   4  |   5  | ESC  |           |  =   |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   \  |           |   /  |   Y  |   U  |   I  |   O  |   P  |  ~L2   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ~L1    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|  ~L1   |
 * |--------+------+------+------+------+------|  [   |           |  ]   |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |'/Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl | Meh  |Hyper | LAlt | LGui |                                       | RGui | RAlt | Hyper|  Meh |RCtrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,---------------.       ,---------------.
 *                                      | Home   | End  |       | Left | Right  |
 *                               ,------|--------|------|       |------+--------+------.
 *                               |      |        | PgUp |       |  Up  |        |      |
 *                               |Backsp|   Del  |------|       |------| Enter  | Space|
 *                               |      |        | PgDn |       | Down |        |      |;
 *                               `----------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV, KC_1,        KC_2,  KC_3, KC_4, KC_5, KC_ESC,
        KC_TAB, KC_Q,        KC_W,  KC_E, KC_R, KC_T, KC_BSLS,
        KC_FN1, KC_A,        KC_S,  KC_D, KC_F, KC_G,
        KC_LSFT,CTL_T(KC_Z), KC_X,  KC_C, KC_V, KC_B, KC_LBRC,
        KC_LCTL,MEH_T(KC_NO),ALL_T(KC_NO),KC_LALT,KC_LGUI,
                                             KC_HOME, KC_END,
                                                      KC_PGUP,
                                    KC_BSPC, KC_DEL,  KC_PGDN,
                                                                // right hand
                                                                KC_EQL,  KC_6, KC_7,    KC_8,    KC_9,        KC_0,          KC_MINS,
                                                                KC_SLSH, KC_Y, KC_U,    KC_I,    KC_O,        KC_P,          LT(MDIA, KC_SLSH),
                                                                         KC_H, KC_J,    KC_K,    KC_L,        KC_SCLN,       KC_FN1,
                                                                KC_RBRC, KC_N, KC_M,    KC_COMM, KC_DOT,      CTL_T(KC_QUOT),KC_RSFT,
                                                                               KC_RGUI, KC_RALT, ALL_T(KC_NO),MEH_T(KC_NO),  KC_RCTL,
                                                                KC_LEFT, KC_RGHT,
                                                                KC_UP,
                                                                KC_DOWN, KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CAPS   |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |  CAPS  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
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
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_CAPS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                               KC_TRNS,KC_TRNS,
                                                       KC_TRNS,
                                       KC_TRNS,KC_TRNS,KC_TRNS,
                                                                     // right hand
                                                                     KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
                                                                     KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                                                                              KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
                                                                     KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_CAPS,
                                                                                       KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
                                                                     KC_TRNS, KC_TRNS,
                                                                     KC_TRNS,
                                                                     KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      | Sleep|           |      |      |      |      |MyComp| Mail |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |ScrlUp|      |ScrlUp|           |ScrlUp|      |      |      |      | Mute |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |MsDown|ScrlDn|      |ScrlDn|           |ScrlDn|      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Stop |Refrsh|       | Prev | Next |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Brwser|Brwser| Home |       |VolUp |      |      |
 *                                 |Back  | Fwd  |------|       |------| Stop | Play |
 *                                 |      |      |Search|       |VolDn |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLEP,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_WH_U, KC_TRNS, KC_WH_U,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_D, KC_TRNS, KC_TRNS, KC_WH_D,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_WH_D,
                                                    KC_WSTP, KC_WREF,
                                                             KC_WHOM,
                                           KC_WBAK, KC_TRNS, KC_WSCH,
                                                                     // right hand
                                                                     KC_WSCH,  KC_TRNS, KC_TRNS, KC_TRNS, KC_MYCM, KC_MAIL, KC_TRNS,
                                                                     KC_WH_U,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS,
                                                                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                                     KC_WH_D,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                                     KC_MPRV, KC_MNXT,
                                                                     KC_VOLU,
                                                                     KC_VOLD, KC_MSTP, KC_MPLY
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
