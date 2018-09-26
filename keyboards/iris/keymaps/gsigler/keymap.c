#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum iris_layers {
  _QWERTY,
  _LOWER, 
  _RAISE
};

// Momentary Hold
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define CANCEL_LOWER XXXXXXX
#define CANCEL_RAISE XXXXXXX

// One Shot
//#define LOWER OSL(_LOWER)
//#define RAISE OSL(_RAISE)
//#define CANCEL_LOWER XXXXXXX
//#define CANCEL_RAISE XXXXXXX

// Toggle
//#define LOWER TG(_LOWER)
//#define RAISE TG(_RAISE)
//#define CANCEL_LOWER KC_TRNS
//#define CANCEL_RAISE KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|ESC/`/~ |   1    |   2    |   3    |    4   |    5   |                          |    6   |   7    |   8    |   9    |   0    |   _/-  |
     KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|  TAB   |   Q    |   W    |   E    |    R   |    T   |                          |    Y   |   U    |   I    |   O    |   P    |   +/=  |
     KC_TAB,   KC_Q,     KC_W,     KC_E,   KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|  {/[   |   A    |   S    |   D    |    F   |    G   |                          |    H   |   J    |   K    |   L    |   :/;  |   "/'  |
     KC_LBRC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|  }/]   |   Z    |   X    |   C    |    V   |    B     LOWER              RAISE |    N   |   M    |   </,  |  >/.   |  ?-/   |   |-\  | 
     KC_RBRC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LOWER,             RAISE,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |  CTRL  | COMMAND| SPACE                    | BKSPACE|  ENTER |   ALT 
                                    KC_LCTL, KC_LGUI,  KC_SPC,                   KC_BSPC,  KC_ENT,  KC_LALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|        |   F1   |   F2   |   F3   |    F4  |   F5   |                          |   F6   |   F7   |   F8   |   F9   |   F10  |   F11  |
     KC_TRNS,  KC_F1,    KC_F2,  KC_F3,   KC_F4,   KC_F5,                              KC_F6,    KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |    !   |    @   |   {    |   }    |    |   |                          |        |        |   ↑    |        |        |   F12  |
     KC_TRNS, KC_EXLM,   KC_AT,  KC_LCBR, KC_RCBR, KC_PIPE,                           XXXXXXX, XXXXXXX,  KC_UP,  XXXXXXX, XXXXXXX, KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |    #   |    $   |   (    |   )    |    `   |                          |        |    ←   |   ↓    |    →   |        |        | 
     XXXXXXX,  KC_HASH, KC_DLR, KC_LPRN, KC_RPRN,   KC_GRV,                            XXXXXXX, KC_LEFT,KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|    &   |    %   |    ^   |   [    |   ]    |    ~   |                          |        |  MUTE  | VOLUP  | VOLDOWN|        |        |    
     KC_AMPR, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, CANCEL_LOWER,          XXXXXXX, XXXXXXX, KC__MUTE, KC__VOLUP, KC__VOLDOWN, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |  CTRL  | COMMAND| SPACE                    | BKSPACE|  ENTER |   ALT 
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,  KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|        |        |        |        |        |        |                          |        |   7    |    8   |    9   |    *   |    /   | 
     XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX,   KC_P7,   KC_P8,   KC_P9,  KC_PAST, KC_PSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    4   |    5   |    6   |    +   |    -    | 
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                            XXXXXXX,  KC_P4,   KC_P5,   KC_P6,  KC_PPLS, KC_PMNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    1   |    2   |    3   |        |        | 
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX,  KC_P1,   KC_P2,   KC_P3,  XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |   0    |    .   | ENTER  |   =    |        | 
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          CANCEL_RAISE, XXXXXXX, KC_P0,   KC_PDOT, KC_PENT, KC_PEQL, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |  CTRL  | COMMAND| SPACE                    | BKSPACE|  ENTER |   ALT 
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

};
