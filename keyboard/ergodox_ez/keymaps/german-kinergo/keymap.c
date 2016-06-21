// German keymap derived from "german", but more closely resembling the German layout of the Kinesis Ergo Elan.
//
// chschmitz, 2016-01-27
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_german.h"

// Layer names
#define BASE 0 // default layer
#define SYMB 1 // symbol layer
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * X'es mark the spots where this is different from the "german" layout which it is based on.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |X Esc  X|   1  |   2  |   3  |   4  |   5  |X `  X|           |XPRSCX|   6  |   7  |   8  |   9  |   0  |   ß    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |X Tab  X|   Q  |   W  |   E  |   R  |   T  |X L1 X|           |X L1 X|   Z  |   U  |   I  |   O  |   P  |   Ü    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Caps  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ö  |  Ä/L2  |
 * |--------+------+------+------+------+------|X L2 X|           |X L2 X|------+------+------+------+------+--------|
 * | LShift |   Y  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |X -  X| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |XLGuiX|X  ^ X|X  < X|XLEFTX|XRIGHT|                                       |XDownX|X Up X|X #  X|X  + X|XRGuiX|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |XCTRLX|XALTX |       | Alt  |Ctrl/Esc|
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |XXX   |XXX   | Home |       | PgUp |XXX     |XXX   |
 *                                 | Bkspc|Del   |------|       |------|  Enter | Space|
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,           KC_2,     KC_3,     KC_4,     KC_5,   DE_ACUT,
        KC_TAB,         KC_Q,           KC_W,     KC_E,     KC_R,     KC_T,   MO(1),
        KC_CAPS,         KC_A,           KC_S,     KC_D,     KC_F,     KC_G,
        KC_LSFT,         DE_Y,           KC_X,     KC_C,     KC_V,     KC_B,   MO(2),
        KC_LGUI,      DE_CIRC, DE_LESS,  KC_LEFT,  KC_RIGHT,
                                               KC_LCTRL, KC_LALT,
                                                              KC_HOME,
                                               KC_BSPC,KC_DELT,KC_END,
        // right hand
        KC_PSCREEN,  KC_6,   KC_7,    KC_8,    KC_9,   KC_0,             KC_MINS,
        MO(1),       DE_Z,   KC_U,    KC_I,    KC_O,   KC_P,             DE_UE,
                     KC_H,   KC_J,    KC_K,    KC_L,   DE_OE,            LT(MDIA,DE_AE),
        MO(2),       KC_N,   KC_M,    KC_COMM, KC_DOT, DE_MINS,          KC_RSFT,
                             KC_DOWN, KC_UP,   DE_HASH,  DE_PLUS,          KC_RGUI,
        KC_RALT, KC_RCTRL,
        KC_PGUP,
        KC_PGDN, KC_ENT, KC_SPC
    ),
// [BASE] = KEYMAP(  // layer 0 : default
//         // left hand
//         KC_CIRC,         KC_1,           KC_2,     KC_3,     KC_4,     KC_5,   KC_MPLY,
//         KC_DELT,         KC_Q,           KC_W,     KC_E,     KC_R,     KC_T,   TG(1),
//         KC_CAPS,         KC_A,           KC_S,     KC_D,     KC_F,     KC_G,
//         KC_LSFT,         DE_Y,           KC_X,     KC_C,     KC_V,     KC_B,   ALL_T(KC_NO),
//         LT(SYMB,DE_LESS),CTL_T(DE_HASH), DE_ACUT,  DE_MINS,  DE_PLUS,
//                                                ALT_T(KC_APP), KC_LGUI,
//                                                               KC_HOME,
//                                                KC_SPC,KC_BSPC,KC_END,
//         // right hand
//         KC_MNXT,     KC_6,   KC_7,    KC_8,    KC_9,   KC_0,             KC_MINS,
//         TG(2),       DE_Z,   KC_U,    KC_I,    KC_O,   KC_P,             DE_UE,
//                      KC_H,   KC_J,    KC_K,    KC_L,   DE_OE,            LT(MDIA,DE_AE),
//         MEH_T(KC_NO),KC_N,   KC_M,    KC_COMM, KC_DOT, CTL_T(DE_MINS),   KC_RSFT,
//                              KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,          KC_FN1,
//         KC_LALT,CTL_T(KC_ESC),
//         KC_PGUP,
//         KC_PGDN,KC_TAB, KC_ENT
//     ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
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
       KC_TRNS,DE_EXLM,DE_AT,  DE_LCBR,DE_RCBR,DE_PIPE,KC_TRNS,
       KC_TRNS,DE_HASH,DE_DLR, DE_LPRN,DE_RPRN,DE_GRV,
       KC_TRNS,DE_PERC,DE_CIRC,DE_LBRC,DE_RBRC,DE_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    DE_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    DE_PLUS, KC_TRNS,
       KC_TRNS, DE_AMPR, KC_1,   KC_2,    KC_3,    DE_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    DE_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      |VolDwn| Mute |VolUp |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Btn4 |MsLeft|MsDown|MsRght| Btn5 |------|           |------|      | Prev | Stop | Play | Next |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |WhRght|WhDown| WhUp |WhLeft|WhClk |      |           |      |BwSrch|BwBack|BwHome|BwRefr|BwFwd |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |MsAcl0|MsAcl1|MsAcl2|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |Brwser|Brwser|
 *                                 | Lclk | Rclk |------|       |------|Back  |Forwd |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5,
       KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_BTN3, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,
       KC_TRNS, KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_F12,
                KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS,
       KC_TRNS, KC_WSCH, KC_WBAK, KC_WHOM, KC_WREF, KC_WFWD, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_WBAK, KC_WFWD
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
        case SYMB:
            ergodox_right_led_1_on();
            break;
        case MDIA:
            ergodox_right_led_2_on();
            break;
        default:
            ergodox_board_led_off();
            break;
    }

};
