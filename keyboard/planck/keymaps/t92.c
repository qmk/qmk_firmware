//Author: tong92 <tong92power@gmail.com>

#include "keymap_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //MIT Layout
   /* 0: Qwerty layer
    * ,-----------------------------------------------------------------------.
    * |Tab  | q   | w   | e   | r   | t   | y   | u   | i   | o   | p   | BS  |
    * |-----------------------------------------------------------------------|
    * |Ctrl | a   | s   | d   | f   | g   | h   | j   | k   | l   | ;   |enter|
    * |-----------------------------------------------------------------------|
    * |Shift| z   | x   | c   | v   | b   | n   | m   |  ,  |  .  |  /  |  '  |
    * |-----------------------------------------------------------------------|
    * | fn  | win | Alt |  \  |Lower|   Space   |Upper| Alt |  [  |  ]  |Shift|
    * `-----------------------------------------------------------------------'
    */
[0] ={
{KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
{KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT},
{KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_QUOT},
{FUNC(4), KC_LGUI, KC_LALT, KC_BSLS, FUNC(1),    KC_SPC    ,   FUNC(2),  KC_RALT, KC_LBRC, KC_RBRC, KC_RSFT}
    },
   /* 1: Lower layer
    * ,-----------------------------------------------------------------------.
    * |Tab  |  7  |  8  |  9  |  +  | BS  | F1  | F2  | F3  | F4  | F5  | F6  |
    * |-----------------------------------------------------------------------|
    * |  `  |  4  |  5  |  6  |  -  | DEL | F7  | F8  | F9  | F10 | F11 | F12 |
    * |-----------------------------------------------------------------------|
    * |Shift|  1  |  2  |  3  |  *  |ENTER|     |     | HOME| PgUp|  UP | PgDo|
    * |-----------------------------------------------------------------------|
    * | fn  |  0  |  .  |  /  |  =  |   Space   |QWERT| END | LEFT| DOWN|RIGHT|
    * `-----------------------------------------------------------------------'
    */
[1] ={
{KC_TAB ,  KC_7,    KC_8,    KC_9, KC_PLUS, KC_BSPC, KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6   },
{KC_GRV , KC_4,    KC_5,    KC_6,  KC_MINS, KC_DELT, KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12  },
{KC_LSFT, KC_1,    KC_2,    KC_3,  KC_ASTR, KC_ENT,  KC_TRNS,KC_TRNS,KC_HOME,KC_PGUP,KC_UP,KC_PGDN},
{FUNC(4), KC_0,    KC_DOT, KC_SLSH, KC_EQL ,    KC_SPC    ,   FUNC(0),KC_END,KC_LEFT,KC_DOWN,KC_RIGHT }
    },
  /* 2: Upper layer
    * ,-----------------------------------------------------------------------.
    * |Tab  |  &  |  *  |  (  |  )  | BS  | F1  | F2  | F3  | F4  | F5  | F6  |
    * |-----------------------------------------------------------------------|
    * |  ~  |  $  |  %  |  ^  |  _  | DEL | F7  | F8  | F9  | F10 | F11 | F12 |
    * |-----------------------------------------------------------------------|
    * |     |  !  |  @  |  #  |     |ENTER|     |     | HOME| PgUp|  UP | PgDo|
    * |-----------------------------------------------------------------------|
    * | fn  |  {   |  }  |  | |     |   Space   |QWERT| END | LEFT| DOWN|RIGHT|
    * `-----------------------------------------------------------------------'
    */
[2] ={
{KC_TAB ,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSPC,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  },
{KC_TILD,KC_DLR ,KC_PERC,KC_CIRC,KC_UNDS,KC_DELT,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 },
{KC_TRNS,KC_EXLM,KC_AT  ,KC_HASH,KC_TRNS,KC_ENT ,KC_TRNS,KC_TRNS,KC_HOME,KC_PGUP,KC_UP,KC_PGDN},
{FUNC(4),KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,    KC_SPC     ,FUNC(0),KC_END,KC_LEFT,KC_DOWN,KC_RIGHT}
    },
      /* 3: FUNC layer
    * ,-----------------------------------------------------------------------.
    * | ESC |AltF4|Win+U|     |Ct+F5|Sh+Ca|PrtSc| PgUp| UP  | PgDo|     | DEL |
    * |-----------------------------------------------------------------------|
    * |     |Win+L|Win+D|Win+R|     |Al+Ca|CapsL| LEFT| DOWN|RIGHT|     |     |
    * |-----------------------------------------------------------------------|
    * |Shift|W+S+L|W+S+R|     |     |Ct+Ca|ScroL| HOME|     | END |     |     |
    * |-----------------------------------------------------------------------|
    * |     |W+C+L|W+C+R|W+C+4|     | Win+Space |     |     |     |     |     |
    * `-----------------------------------------------------------------------'
    */
[4] ={
{KC_ESC ,LALT(KC_F4),LGUI(KC_UP),KC_TRNS,LCTL(KC_F5)                       ,S(KC_CAPS),KC_PSCR   ,   KC_PGUP,  KC_UP,   KC_PGDN,   KC_TRNS,   KC_DELT},
{KC_TRNS,LGUI(KC_LEFT),LGUI(KC_DOWN),LGUI(KC_RIGHT),KC_TRNS                ,LALT(KC_CAPS),KC_CAPS,   KC_LEFT,  KC_DOWN,   KC_RIGHT,  KC_TRNS,  KC_TRNS  },
{KC_LSFT,LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RIGHT)),KC_TRNS,KC_TNRS          ,LCTL(KC_CAPS),KC_SLCK,KC_HOME,KC_TRNS,KC_END, KC_TRNS, KC_TRNS },
{KC_TRNS,LGUI(LCTL(KC_LEFT)),LGUI(LCTL(KC_RIGHT)),LGUI(LCTL(KC_F4)),KC_TRNS,    LGUI(KC_SPC)    ,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS}
    },
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_DEFAULT_LAYER_SET(0),
    [1] = ACTION_DEFAULT_LAYER_SET(1),
    [2] = ACTION_DEFAULT_LAYER_SET(2),

    //[3] = ACTION_LAYER_MOMENTARY(3),  // to Fn overlay
    [4] = ACTION_LAYER_MOMENTARY(4),  // to Fn overlay

};