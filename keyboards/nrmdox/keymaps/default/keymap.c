#include "nrmdox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbol layer
#define NUM 2 // number layer

enum {  // for macro
    M_DEBUG = 0,
    M_4SPC,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |ESC| q | w | e | r | t |            | y | u | i | o | p |B S|
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |CTL| a | s | d | f | g |            | h | j | k | l |: ;|RET|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 * |TAB|SFT| z | x | c | v |<E>|    |<J>| b | n | m |, <|. >|/ ?|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 *             |ALT|SYM|SPC|NUM|    |NUM|SPC|SYM|GUI|
 *             +---+---+---+---+    +---+---+---+---+
 *
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
            KC_ESC   , KC_Q    , KC_W    , KC_E    , KC_R   , KC_T   ,
            KC_LCTRL , KC_A    , KC_S    , KC_D    , KC_F   , KC_G   ,
            SFT_T(KC_TAB), KC_LSFT  , KC_Z    , KC_X    , KC_C    , KC_V   , KC_LANG2 ,
                                           KC_LALT ,MO(SYMB), KC_SPC , MO(NUM),
        // right hand
                      KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
                      KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_ENT  ,
            KC_LANG1 , KC_B   , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH ,
            MO(NUM), KC_SPC , MO(SYMB) , KC_LGUI
    ),

/* Keymap 1: Symbol layer
 *
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |   | ! | @ | # | $ | % |            | ^ | & | * | ( | ) |DEL|
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |   | _ | \ | | | ' | " |            |A_L|A_D|A_U|A_R|INS|   |
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 * |   |   | + | - | = | ` |   |    |   |CAP| { | } | [ | ] |4SP|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 *             |ALT|   |SPC|NUM|    |NUM|SPC|   |GUI|
 *             +---+---+---+---+    +---+---+---+---+
 *
 */
[SYMB] = KEYMAP(  // layer 1 : symbol
        // left hand
            KC_TRNS  , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC       ,
            KC_TRNS , KC_UNDS , KC_BSLS , KC_PIPE , KC_QUOT , LSFT(KC_QUOT) ,
            KC_TRNS  , KC_TRNS , KC_PLUS , KC_MINS , KC_EQL  , KC_GRV        , KC_TRNS ,
                                           KC_LALT , KC_TRNS,  KC_SPC ,KC_TRNS,
        // right hand
                      KC_CIRC , KC_AMPR , KC_ASTR      , KC_LPRN  , KC_RPRN , KC_DEL    ,
                      KC_LEFT , KC_DOWN , KC_UP        , KC_RIGHT , KC_INS  , KC_TRNS   ,
            KC_TRNS , KC_CAPS , KC_LCBR , KC_RCBR      , KC_LBRC  , KC_RBRC , M(M_4SPC) ,
             KC_TRNS ,KC_SPC  , KC_TRNS  , KC_LGUI
    ),


/* Keymap 2: Number layer
 *
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |F 1|F 2|F 3|F 4|F 5|F 6|            |F 7|F 8|F 9|F10|F11|F12|
 * +---+---+---+---+---+---+            +---+---+---+---+---+---+
 * |   | 1 | 2 | 3 | 4 | 5 |            | 6 | 7 | 8 | 9 | 0 |RET|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 * |   |   |NOP|NOP|NOP|NOP|   |    |   |HOM|PGD|PGU|END|DBG|RST|
 * +---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+
 *             |ALT|SYM|SPC|   |    |   |SPC|SYM|GUI|
 *             +---+---+---+---+    +---+---+---+---+
 *
 */
[NUM] = KEYMAP(  // layer 2 : number
        // left hand
            KC_F1    , KC_F2  , KC_F3  , KC_F4   , KC_F5  , KC_F6  ,
            KC_TRNS , KC_1   , KC_2   , KC_3    , KC_4   , KC_5   ,
            KC_TRNS  , KC_TRNS  , KC_NO  , KC_NO   , KC_NO  , KC_NO  , KC_TRNS ,
                                         KC_LALT , KC_TRNS, KC_SPC , KC_TRNS ,
        // right hand
                       KC_F7   , KC_F8   , KC_F9        , KC_F10 , KC_F11     , KC_F12 ,
                       KC_6    , KC_7    , KC_8         , KC_9   , KC_0       , KC_ENT ,
            KC_TRNS , KC_HOME , KC_PGDN , KC_PGUP      , KC_END , M(M_DEBUG)  , RESET  ,
            KC_TRNS , KC_SPC  , KC_TRNS , KC_LGUI
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

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),
    [2] = ACTION_LAYER_TAP_TOGGLE(NUM)
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
