#include "nrmdox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbol layer
#define FNKY 2 // function layer
#define SWAP 3 // spaw layer

enum {  // for macro
    M_DEBUG = 0,
    M_4SPC,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |TAB| q | w | e | r | t |            | y | u | i | o | p |BS |
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |CTL| a | s | d | f | g |            | h | j | k | l |: ;|RET|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 * |LT1| z | x | c | v | b |ALT|    |ALT| n | m |, <|. >|/ ?|LT2|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 *             |TG3|GUI|S/S| ] |    | [ |S/S|LT1|TG1|
 *             +---+---+---+---+    +---+---+---+---+
 *
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
            KC_TAB                , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T                  ,
            KC_LCTL               , KC_A      , KC_S      , KC_D      , KC_F      , KC_G                  ,
            LT(SYMB, KC_F15)      , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B                  , KC_LALT   ,
                                                            TG(SWAP)  , KC_LGUI   , SFT_T(KC_SPC)         , KC_RBRC   ,
        // right hand
                        KC_Y                  , KC_U                  , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
                        KC_H                  , KC_J                  , KC_K      , KC_L      , KC_SCLN   , KC_ENT    ,
            KC_RALT   , KC_N                  , KC_M                  , KC_COMM   , KC_DOT    , KC_SLSH   , LT(FNKY, KC_F16)      ,
            KC_LBRC   , SFT_T(KC_SPC)         , LT(SYMB, KC_ENT)      , TG(SYMB)
    ),


/* Keymap 1: Cursor layer
 *
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * | 1 | 2 | 3 | 4 | 5 | 6 |            | 7 | 8 | 9 | 0 | - | = |
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |   |ESC|HOM|PgU|PgD|END|            |A_L|A_D|A_U|A_R|' "| ` |
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 * |LT1|   |   |   |   |   |   |    |   |   |   |   |   | \ |LT2|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 *             |TG3|   |   |   |    |   |   |LT1|TG0|
 *             +---+---+---+---+    +---+---+---+---+
 *
 */
[SYMB] = KEYMAP(  // layer 1 : symbol
        // left hand
            KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_6      ,
            KC_TRNS   , KC_ESC    , KC_HOME   , KC_PGUP   , KC_PGDN   , KC_END    ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
                                                KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
        // right hand
                        KC_7      , KC_8      , KC_9      , KC_0      , KC_MINS   , KC_EQL    ,
                        KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_QUOT   , KC_GRV    ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_BSLS   , KC_TRNS   ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS
    ),


/* Keymap 2: Function layer
 *
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |F1 |F2 |F3 |F4 |F5 |F6 |            |F7 |F8 |F9 |F10|F11|F12|
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |   |   |   |   |   |   |            |   |   |   |   |   |   |
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 * |LT1|   |   |   |   |   |   |    |RST|   |   |   |   |   |LT2|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 *             |TG3|   |   |   |    |   |   |LT1|TG1|
 *             +---+---+---+---+    +---+---+---+---+
 *
 */
[FNKY] = KEYMAP(  // layer 2 : function
        // left hand
            KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6     ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
                                                KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
        // right hand
                        KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
                        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
            RESET     , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS
    ),


/* Keymap 3: Swap layer
 *
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |   |   |   |   |   |   |            |   |   |   |   |   |   |
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |GUI|   |   |   |   |   |            |   |   |   |   |   |   |
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 * |LT1|   |   |   |   |   |   |    |   |   |   |   |   |   |LT2|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 *             |TG0|CTL|   |   |    |   |   |LT1|TG1|
 *             +---+---+---+---+    +---+---+---+---+
 *
 */
[SWAP] = KEYMAP(  // layer 3 : swap
        // left hand
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
            KC_LGUI   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
                                                KC_TRNS   , KC_LCTL   , KC_TRNS   , KC_TRNS   ,
        // right hand
                        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
                        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS
    ),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case M_DEBUG:
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            break;
        case M_4SPC:
            if (record->event.pressed) {
                return MACRO (T(SPC), T(SPC), T(SPC), T(SPC), END);
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

    nrmdox_board_led_off();
    nrmdox_right_led_1_off();
    nrmdox_right_led_2_off();
    nrmdox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            nrmdox_right_led_1_on();
            break;
        case 2:
            nrmdox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
