//Author: tong92 <tong92power@gmail.com>

#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define LOWER M(1)
#define RAISE M(2)
#define GO_DEFT M(99)
#

//MIT Layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* 0: Qwerty layer (Default)
* ,-----------------------------------------------------------------------.
* |Tab  | q   | w   | e   | r   | t   | y   | u   | i   | o   | p   | BS  |
* |-----------------------------------------------------------------------|
* |Ctrl | a   | s   | d   | f   | g   | h   | j   | k   | l   | ;   |enter|
* |-----------------------------------------------------------------------|
* |Shift| z   | x   | c   | v   | b   | n   | m   |  ,  |  .  |  /  |Shift|
* |-----------------------------------------------------------------------|
* | Fn  |Ctrl | Win | Alt |Lower|   Space   |Upper|  '  |  [  |  ]  | Alt |
* `-----------------------------------------------------------------------'
*/
[0] ={
{KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R, KC_T,  KC_Y,  KC_U, KC_I,   KC_O,   KC_P,   KC_BSPC},
{KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F, KC_G,  KC_H,  KC_J, KC_K,   KC_L,   KC_SCLN,KC_ENT },
{KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V, KC_B,  KC_N,  KC_M, KC_COMM,KC_DOT, KC_SLSH,KC_RSFT},
{MO(4),  KC_RCTL,KC_LGUI,KC_LALT,LOWER,KC_SPC,KC_SPC,RAISE,KC_QUOT,KC_LBRC,KC_RBRC,KC_RALT}
},
/* 1: Lower layer
* ,-----------------------------------------------------------------------.
* |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | BS  |
* |-----------------------------------------------------------------------|
* |     | F1  | F2  | F3  | F4  | F5  | F6  |  -  |  +  |  [  |  ]  |  \  |
* |-----------------------------------------------------------------------|
* |     | F7  | F8  | F9  | F10 | F11 | F12 |     | HOME| PgUp|  UP | PgDo|
* |-----------------------------------------------------------------------|
* |     |     |     |     |     |   SPACE   |mouse| END | LEFT| DOWN|RIGHT|
* `-----------------------------------------------------------------------'
*/
[1] ={
{KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,  KC_6,  KC_7,   KC_8,   KC_9,   KC_0,   KC_BSPC },
{_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5, KC_F6, KC_MINS,KC_PLUS,KC_LBRC,KC_RBRC,KC_BSLS },
{_______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,KC_F12,_______,KC_HOME,KC_PGUP,KC_UP  ,KC_PGDN },
{XXXXXXX,_______,_______,_______,_______,KC_SPC,KC_SPC,_______,KC_END, KC_LEFT,KC_DOWN,KC_RIGHT}
},
/* 2: Upper layer
* ,-----------------------------------------------------------------------.
* |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  | BS  |
* |-----------------------------------------------------------------------|
* |     | F1  | F2  | F3  | F4  | F5  | F6  |  _  |  =  |  {  |  }  |  |  |
* |-----------------------------------------------------------------------|
* |     | F7  | F8  | F9  | F10 | F11 | F12 |     | HOME| PgUp|  UP | PgDo|
* |-----------------------------------------------------------------------|
* |     |     |     |     |mouse|   SPACE   |     | END | LEFT| DOWN|RIGHT|
* `-----------------------------------------------------------------------'
*/
[2] ={
{KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSPC },
{_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_UNDS,KC_EQL, KC_LCBR,KC_RCBR,KC_PIPE },
{_______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_HOME,KC_PGUP,KC_UP  ,KC_PGDN },
{XXXXXXX,_______,_______,_______,_______,KC_SPC, KC_SPC, _______,KC_END, KC_LEFT,KC_DOWN,KC_RIGHT}
},
/* 4: fn layer (Window shortcuts)
* ,-----------------------------------------------------------------------.
* | ESC |WinOf|WinUp|     |     |Sh+Ca|     | PgUp| UP  | PgDo|PrtSc| DEL |
* |-----------------------------------------------------------------------|
* |     |WinLe|WinDo|WinRi|     |Al+Ca|CapsL| LEFT| DOWN|RIGHT|     |     |
* |-----------------------------------------------------------------------|
* |     |WinLW|WinRW|     |     |Ct+Ca|ScroL| HOME|     | END |     |     |
* |-----------------------------------------------------------------------|
* |     |DeskL|DeskR|DeskX|Task | ChangeLang|     |     |     |     | LED |
* `-----------------------------------------------------------------------'
*/
[4] ={
{KC_ESC ,LALT(KC_F4)        ,LGUI(KC_UP)         ,XXXXXXX          ,XXXXXXX    ,S(KC_CAPS)   ,XXXXXXX,KC_PGUP,KC_UP,KC_PGDN,KC_PSCR,KC_DELT},
{_______,LGUI(KC_LEFT)      ,LGUI(KC_DOWN)       ,LGUI(KC_RIGHT)   ,XXXXXXX    ,LALT(KC_CAPS),KC_CAPS,KC_LEFT,KC_DOWN,KC_RIGHT,XXXXXXX,XXXXXXX},
{_______,LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RIGHT)),XXXXXXX          ,XXXXXXX    ,LCTL(KC_CAPS),KC_SLCK,KC_HOME,XXXXXXX,KC_END,XXXXXXX,XXXXXXX},
{KC_TRNS,LGUI(LCTL(KC_LEFT)),LGUI(LCTL(KC_RIGHT)),LGUI(LCTL(KC_F4)),LCTL(LALT(KC_DELT)),LGUI(KC_SPC),LGUI(KC_SPC),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,M(0)}
},
/* 10: mouse layer
* ,-----------------------------------------------------------------------.
* |     |     |     |Mo_Up|     |     |     |M_WhL|M_WhU|M_WhR|     |RESET|
* |-----------------------------------------------------------------------|
* |     |     |Mo_Le|Mo_Do|Mo_Ri|     |     |M_Bt1|M_WhD|M_Bt2|     |     |
* |-----------------------------------------------------------------------|
* |     |     |     |     |     |     |     |M_AC0|M_AC1|M_AC2|     |     |
* |-----------------------------------------------------------------------|
* |     |     |     |     |     |  GO_DEFT  |     |     |     |     |     |
* `-----------------------------------------------------------------------'
*/
[10] ={
{XXXXXXX,XXXXXXX,XXXXXXX,KC_MS_U,XXXXXXX,XXXXXXX,XXXXXXX,KC_WH_L,KC_WH_U,KC_WH_R,XXXXXXX,RESET},
{XXXXXXX,XXXXXXX,KC_MS_L,KC_MS_D,KC_MS_R,XXXXXXX,XXXXXXX,KC_BTN1,KC_WH_D,KC_BTN2,XXXXXXX,XXXXXXX},
{XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_ACL0,KC_ACL1,KC_ACL2,XXXXXXX,XXXXXXX},
{XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,GO_DEFT,GO_DEFT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX}
}

};
//Layout END

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
            if (record->event.pressed) {
                #ifdef BACKLIGHT_ENABLE
                    backlight_step();
                #endif
            }
        break;
        case 1:
          if (record->event.pressed) {
            layer_on(1);
            update_tri_layer(1, 2, 10);
          } else {
            layer_off(1);
            update_tri_layer(1, 2, 10);
          }
          break;
        case 2:
          if (record->event.pressed) {
            layer_on(2);
            update_tri_layer(1, 2, 10);
          } else {
            layer_off(2);
            update_tri_layer(1, 2, 10);
          }
          break;
        case 99:
            if (record->event.pressed) {
                layer_off(10);
                layer_off(1);
                layer_off(2);
                layer_on(0);
                update_tri_layer(0 ,1 ,2);
            }
        break;
      }
    return MACRO_NONE;
};
