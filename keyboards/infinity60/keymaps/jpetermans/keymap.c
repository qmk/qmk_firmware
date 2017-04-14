#include "infinity60.h"
#include "led_controller.h"
#include "keymap_jpetermans.h"

//Helpful Defines
#define _______ KC_TRNS

//Define Layer Names
#define _BASE 0
#define _NUMPAD 1
#define _FNAV 2
#define _MEDIA 3
#define _TILDE 4

/* ==================================
 *             KEYMAPS 
 * ==================================*/

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
        _______,_______,F(2),F(3),F(4),F(5),F(6),F(7), KC_MPRV, KC_MNXT,KC_MSTP, _______,KC_NO,       \
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
    ACTION_LEDS_GAME,
    ACTION_LEDS_NAV,
    ACTION_LEDS_MEDIA,
    ACTION_LEDS_NUMPAD,
    ACTION_LEDS_TEST
};
        
/* ==================================
 *          LED MAPPING 
 * ==================================*/

/*
   Configuring led control can be done as
   1. full keyboard at a time - define led array, or
   2. individual led - send specific led address (defined in keymap.h)

    Infinity60 LED MAP
    11 12 13 14 15 16 17 18 21 22 23 24 25  26 27*
     28 31 32 33 34 35 36 37 38 41 42 43 44 45
     46 47 48 51 52 53 54 55 56 57 58 61    62
      63 64 65 66 67 68 71 72 73 74 75      76 77*
    78  81  82       83         84  85  86  87
    *Unused in Alphabet Layout

    The full keyboard arrays map to the mcu's LED pages 
    (8 available) desribed in led_controller.c
   
    0x24 (pcb row 1) is first byte of PWM portion of LED page
    0x34 (pcb row 2) is 17th byte of PWM portion of LED page
    array translates to row and column positions
*/

//LED Layer indicator (1 per layer 3-7)
const uint8_t led_single_layer[5] = {
  12,13,14,15,16
};
//LED Page 1 - All off
//LED Page 2 - All on
//LED Page 3 - _Nav
const uint8_t led_nav[33] = {
  11,12,13,14,15,16,17,18,21,22,23,24,25,
  28,                   37,38,41,42,45,
  46,47,48,            54,55,56,57,58,
     64,65,66,      71,
                                  84,85
};
//LED Page 4 - _Numpad
const uint8_t led_numpad[17] = {
  18,21,22,23,
  37,38,41,42,
  55,56,57,58,
  72,73,74,75,
           85
};
//LED Page 5 - _Media
const uint8_t led_media[12] = {
             23,24,25,
     38,
  55,56,57,
      73,74,75,
  83,          86
};
//LED Page 6 - _Game
const uint8_t led_game[5] = {
  //row 1
  11,
  //row 2
  //row 3
  32,
  //row 4
  47, 48,
  //row 5
  51
  //row 6
  //row 7
  //row 8
};

const uint16_t fn_actions[] = {
    [0] = ACTION_KEY(LALT(LCTL(KC_DEL))),
    [1] = ACTION_LAYER_MODS(_TILDE, MOD_LSFT),
    [2] = ACTION_FUNCTION(ACTION_LEDS_ALL),
    [3] = ACTION_FUNCTION(ACTION_LEDS_GAME),
    [4] = ACTION_FUNCTION(ACTION_LEDS_MEDIA),
    [5] = ACTION_FUNCTION(ACTION_LEDS_NAV),
    [6] = ACTION_FUNCTION(ACTION_LEDS_NUMPAD),
    [7] = ACTION_FUNCTION(ACTION_LEDS_TEST)


};

/* custom action function */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  (void)opt;
  msg_t msg;
  switch(id) {
    case ACTION_LEDS_ALL:
      if(record->event.pressed) {
        // signal the LED controller thread
        msg=(TOGGLE_ALL << 8) | 0;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;
    case ACTION_LEDS_GAME:
      if(record->event.pressed) {
        // signal the LED controller thread
        msg=(TOGGLE_LAYER_LEDS << 8) | 6;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;
    case ACTION_LEDS_MEDIA:
      if(record->event.pressed) {
        // signal the LED controller thread
        msg=(TOGGLE_LAYER_LEDS << 8) | 5;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;
    case ACTION_LEDS_NAV:
      if(record->event.pressed) {
        // signal the LED controller thread
        msg=(OFF_LED << 8) | 12;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;
    case ACTION_LEDS_NUMPAD:
      if(record->event.pressed) {
        // signal the LED controller thread
        msg=(ON_LED << 8) | 12;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;
    case ACTION_LEDS_TEST:
      if(record->event.pressed) {
        // signal the LED controller thread
        msg=(TOGGLE_LED << 8) | 12;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
      case 0: 
        if (record->event.pressed) {
        }
        break;
      case 1:
        if (record->event.pressed) {
        }
        break;
    }
    return MACRO_NONE;
};


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    xprintf("init start");

    led_controller_init();

//TODO: do pages need to be written at init or ok on demand?
/* Write pages */
    write_led_page(3, led_nav, 33);
    chThdSleepMilliseconds(5);

    write_led_page(4, led_numpad, 17);
    chThdSleepMilliseconds(5);

    write_led_page(5, led_media, 12);
    chThdSleepMilliseconds(5);

    write_led_page(6, led_game, 5);
    chThdSleepMilliseconds(5);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

