#include "infinity60.h"
#include "backlight.h"

//Helpful Defines
#define _______ KC_TRNS

//Define Layer Names
#define _BASE 0
#define _NUMPAD 1
#define _FNAV 2
#define _MEDIA 3
#define _TILDE 4

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backs|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shif|   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |         Space    |Alt |Gui |  FN  | Ctrl   |
     * `-----------------------------------------------------------'
     */
    /* default */
    [_BASE] = KEYMAP( \
        KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_NO,\
        KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,   \
        TT(_FNAV), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,         \
        F(1),   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,KC_NO,          \
        KC_LCTL,   KC_LGUI,KC_LALT,               KC_SPC,          KC_RALT,TG(_NUMPAD),MO(_MEDIA), KC_RCTL         \
    ),

    /* F-, arrow, and media keys */
    [_FNAV] = KEYMAP( \
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_NO,\
        KC_CAPS,_______,_______,_______,_______,_______,_______,KC_PGUP,KC_UP,KC_PGDN,KC_PSCR,_______,_______,KC_DEL,  \
        _______,M(0),KC_BTN2,_______,_______,_______,KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_INS,_______,_______,     \
        _______,KC_APP,KC_BTN1,KC_CALC,_______,_______,KC_END,_______,_______,_______,_______,_______,KC_NO,         \
        _______,_______,_______,               _______,             F(0),KC_NLCK,_______,_______   \
    ),

    /* numpad */
    [_NUMPAD] = KEYMAP( \
        _______,_______,_______,_______,_______,_______,_______, KC_P7, KC_P8, KC_P9, KC_PSLS, _______,_______,_______,KC_NO,\
        _______,_______,_______,_______,_______,_______,_______, KC_P4, KC_P5, KC_P6, KC_PAST, _______,_______,_______, \
        MO(_FNAV),_______,_______,_______,_______,_______,_______, KC_P1, KC_P2, KC_P3, KC_PMNS, _______,_______,      \
        _______,_______,_______,_______,_______,_______,_______, KC_P0,KC_COMM,KC_PDOT,KC_PPLS, _______,KC_NO,      \
        _______,_______,_______,               MO(_BASE),           _______,_______,_______,_______   \
    ),

    /* media */
    [_MEDIA] = KEYMAP( \
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,KC_MUTE, KC_VOLD, KC_VOLU,_______,KC_NO,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,     \
        _______,_______,F(2),M(1),_______,_______,_______, _______, KC_MPRV, KC_MNXT,KC_MSTP, _______,KC_NO,       \
        _______,_______,_______,               KC_MPLY,             _______,_______, _______,_______      \
    ),
    /* ~ */
    [_TILDE] = KEYMAP( \
        KC_GRV,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,KC_NO,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,     \
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,KC_NO,       \
        _______,_______,_______,               _______,             _______,_______, _______,_______      \
    ),
    /* template */
    [5] = KEYMAP( \
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,KC_NO,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,     \
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,KC_NO,       \
        _______,_______,_______,               _______,             _______,_______, _______,_______      \
    ),
};

//id for user defined functions and macros
enum function_id {
    NONE,
};

enum macro_id {
    ACTION_LEDS_ALL,
};

const uint16_t fn_actions[] = {
    [0] = ACTION_KEY(LALT(LCTL(KC_DEL))),
    [1] = ACTION_LAYER_MODS(_TILDE, MOD_LSFT),
    [2] = ACTION_BACKLIGHT_TOGGLE()
/*    [1] = ACTION_FUNCTION(ACTION_LEDS_GAME),

    [4] = ACTION_USAGE_CONSUMER(0x1B4),
    [5] = ACTION_USAGE_CONSUMER(0x196),
    [6] = ACTION_USAGE_CONSUMER(0x1A6),
    [7] = ACTION_USAGE_CONSUMER(0x1A0)
*/
};

/* custom action function */
/*
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  (void)opt;
  switch(id) {
    case 1:
        if(record->event.pressed) {
          // signal the LED controller thread
          chMBPost(&led_mailbox, LED_MSG_GAME_TOGGLE, TIME_IMMEDIATE);
        }
        break;
    }

}
*/

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case 0: 
            if (record->event.pressed) {
            }
            break;
        case 1:
            if (record->event.pressed) {
                backlight_step();
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

};

