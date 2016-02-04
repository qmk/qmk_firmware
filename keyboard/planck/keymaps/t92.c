//Author: tong92 <tong92power@gmail.com>

#include "planck.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //MIT Layout
   /* 0: Qwerty layer
    * ,-----------------------------------------------------------------------.
    * |Tab  | q   | w   | e   | r   | t   | y   | u   | i   | o   | p   | BS  |
    * |-----------------------------------------------------------------------|
    * |Ctrl | a   | s   | d   | f   | g   | h   | j   | k   | l   | ;   |enter|
    * |-----------------------------------------------------------------------|
    * |Shift| z   | x   | c   | v   | b   | n   | m   |  ,  |  .  |  /  |Shift|
    * |-----------------------------------------------------------------------|
    * | fn  | win | Alt |  \  |Lower|   Space   |Upper|  '  |  [  |  ]  | Alt |
    * `-----------------------------------------------------------------------'
    */
[0] ={
{KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
{KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT},
{KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT},
{MO(4), KC_LGUI, KC_LALT, KC_BSLS, MO(1),KC_SPC,KC_SPC    ,   MO(2),  KC_QUOT, KC_LBRC, KC_RBRC, KC_RALT}
    },
   /* 1: Lower layer
 * ,-----------------------------------------------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  BS |
 * |-----------------------------------------------------------------------|
 * |     | F1  | F2  | F3  | F4  | F5  | F6  |  -  |  +  |  [  |  ]  |  \  |
 * |-----------------------------------------------------------------------|
 * |     | F7  | F8  | F9  | F10 | F11 | F12 |     | HOME| PgUp|  UP | PgDo|
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |    SPACE  |     | END | LEFT| DOWN|RIGHT|
 * `-----------------------------------------------------------------------'
    */
[1] ={
{KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
{KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS},
{KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,KC_HOME,KC_PGUP ,KC_UP  ,KC_PGDN},
{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_SPC,  KC_SPC , KC_TRNS, KC_END,KC_LEFT,KC_DOWN,KC_RIGHT}
    },
  /* 2: Upper layer
 * ,-----------------------------------------------------------------------.
 * |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |  BS |
 * |-----------------------------------------------------------------------|
 * |     | F1  | F2  | F3  | F4  | F5  | F6  |  _  |  =  |  {  |  }  |  |  |
 * |-----------------------------------------------------------------------|
 * |     | F7  | F8  | F9  | F10 | F11 | F12 |     | HOME| PgUp|  UP | PgDo|
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |    SPACE  |     | END | LEFT| DOWN|RIGHT|
 * `-----------------------------------------------------------------------'
    */
[2] ={
{KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
{KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE},
{KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,KC_HOME,KC_PGUP ,KC_UP  ,KC_PGDN},
{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,KC_SPC  , KC_TRNS, KC_END,KC_LEFT,KC_DOWN,KC_RIGHT}
    },
      /* 4: fn layer
    * ,-----------------------------------------------------------------------.
    * | ESC |AltF4|Win+U|     |Ct+F5|Sh+Ca|     |     |     |     |PrtSc| DEL |
    * |-----------------------------------------------------------------------|
    * |     |Win+L|Win+D|Win+R|     |Al+Ca|CapsL|     |     |     |     | LED |
    * |-----------------------------------------------------------------------|
    * |Shift|W+S+L|W+S+R|     |     |Ct+Ca|ScroL|     | HOME| PgUp|  UP | PgDo|
    * |-----------------------------------------------------------------------|
    * |     |W+C+L|W+C+R|W+C+4|C+A+D| Win+Space |     | END | LEFT| DOWN|RIGHT|
    * `-----------------------------------------------------------------------'
    */
[4] ={
{KC_ESC ,LALT(KC_F4)        ,LGUI(KC_UP)         ,KC_TRNS          ,LCTL(KC_F5),S(KC_CAPS)   ,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_DELT},
{KC_TRNS,LGUI(KC_LEFT)      ,LGUI(KC_DOWN)       ,LGUI(KC_RIGHT)   ,KC_TRNS    ,LALT(KC_CAPS),KC_CAPS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,M(0)   },
{KC_LSFT,LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RIGHT)),KC_TRNS          ,KC_TRNS    ,LCTL(KC_CAPS),KC_SLCK,KC_TRNS,KC_HOME,KC_PGUP ,KC_UP  ,KC_PGDN},
{KC_TRNS,LGUI(LCTL(KC_LEFT)),LGUI(LCTL(KC_RIGHT)),LGUI(LCTL(KC_F4)),LCTL(LALT(KC_DELT)),LGUI(KC_SPC),LGUI(KC_SPC) ,KC_TRNS,KC_END,KC_LEFT,KC_DOWN,KC_RIGHT}
    }
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};