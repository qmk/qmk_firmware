#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_neo2.h"

// Layer names
#define BASE 0 // default layer
#define MDIA 1 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ^    |   1  |   2  |   3  |   4  |   5  | Play |           | Next |   6  |   7  |   8  |   9  |   0  |BackSpce|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Del   |   X  |   V  |   L  |   C  |   W  |  L1  |           |  L1  |   K  |   H  |   G  |   F  |   Q  |   ß    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Caps  |   U  |   I  |   A  |   E  |   O  |------|           |------|   S  |   N  |   R  |   T  |   D  |   Y    |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Ü/Ctrl| Ö/C-S| Ä/Alt|   P  |   Z  |      |           |      |   B  |   M  |   ,  |   .  |   J  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  | Home | PgDn | PgUp | End  |                                       | Right| Down |  Up  | Left |  Esc  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      |NeoL2 |       |NeoL2 |        |      |
 *                                 | Tab  |Backsp|------|       |------|  Space |Enter |
 *                                 |      |ace   |NeoL1 |       |NeoL1 |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_CIRC,         KC_1,          KC_2,          KC_3,          KC_4,    KC_5,    KC_MPLY,
        KC_DELT,         NEO_X,         NEO_V,         NEO_L,         NEO_C,   NEO_W,   TG(1),
        KC_CAPS,         NEO_U,         NEO_I,         NEO_A,         NEO_E,   NEO_O,
        KC_LSFT,         CTL_T(NEO_UE), C_S_T(NEO_OE), ALT_T(NEO_AE), NEO_P,   NEO_Z,   ALL_T(KC_NO),
        DE_LESS,         KC_HOME,       KC_PGDN,        KC_PGUP,        KC_END,
                                                ALT_T(KC_APP),KC_LGUI,
                                                              NEO_L2_L,
                                               KC_TAB,KC_BSPC,NEO_L1_L,
        // right hand
        KC_MNXT,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        TG(1),       NEO_K,   NEO_H,   NEO_G,   NEO_F,   NEO_Q,   NEO_SS,
                     NEO_S,   NEO_N,   NEO_R,   NEO_T,   NEO_D,   NEO_Y,
        MEH_T(KC_NO),NEO_B,   NEO_M,   KC_COMM, KC_DOT,  NEO_J,   KC_RSFT,
                              KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ESC,
        KC_LALT,CTL_T(KC_ESC),
        NEO_L2_R,
        NEO_L1_R,KC_SPC, KC_ENT
    ),
/* Keymap 1: Media and mouse keys
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
    /* [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols) */
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
        case MDIA:
            ergodox_right_led_2_on();
            break;
        default:
            ergodox_board_led_off();
            break;
    }

};
