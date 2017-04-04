// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.
//Author: tong92 <tong92power@gmail.com>

#include "tv44.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

// Fillers to make layering more clear
#define _______ KC_TRNS
#define LOWER F(1)
#define RAISE F(2)
#define FTN MO(4)
#define MOUSE M(10)
#define GO_DEFT M(99)
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,--------------------------------------------------------------------------.
 * | Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  Bksp |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * | Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  | Enter|
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | /   |Shift|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * | Ftn1 |  GUI  | Alt  | Space/LOWER | Space/RAISE |  '   |  [  |  ]  | Alt |
 * `--------------------------------------------------------------------------'
 */
[0] = {
{KC_TAB, KC_Q,   KC_W,   KC_E, KC_R,   KC_T,   KC_Y,   KC_U, KC_I,   KC_O,  KC_P,   KC_BSPC},
{KC_LCTL,KC_A,   KC_S,   KC_D, KC_F,   KC_G,   KC_H,   KC_J, KC_K,   KC_L,  KC_SCLN,KC_ENT},
{KC_LSFT,KC_Z,   KC_X,   KC_C, KC_V,   KC_B,   KC_N,   KC_M, KC_COMM,KC_DOT,KC_SLSH,KC_RSFT },
{FTN    ,KC_LGUI,KC_LALT,LOWER,XXXXXXX,XXXXXXX,XXXXXXX,RAISE,KC_QUOT,KC_LBRC,KC_RBRC,KC_RALT}
},
/* LOWER
 * ,--------------------------------------------------------------------------.
 * |  `   |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |       |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  -  |  +  |  [  |  ]  |   \  |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |  F7 |  F8 |  F9 | F10 | F11 | F12 |     | HOME| PgUp|  UP | PgDo|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |       |      |             |             |  END | LEFT| Down|RIGHT|
 * `--------------------------------------------------------------------------'
 */
[1] = {
{KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______},
{_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5, KC_F6, KC_MINS,KC_PLUS,KC_LBRC,KC_RBRC,KC_BSLS },
{_______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, XXXXXXX,KC_HOME,KC_PGUP,KC_UP  ,KC_PGDN },
{XXXXXXX,_______,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_END, KC_LEFT,KC_DOWN,KC_RIGHT}
},
/* RAISE
 * ,--------------------------------------------------------------------------.
 * |  ~   |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |       |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  _  |  =  |  {  |  }  |   |  |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |  F7 |  F8 |  F9 | F10 | F11 | F12 |     | HOME| PgUp|  UP | PgDo|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |       |      |             |             |  END | LEFT| Down|RIGHT|
 * `--------------------------------------------------------------------------'
 */
[2] ={
{KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______ },
{_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_UNDS,KC_EQL, KC_LCBR,KC_RCBR,KC_PIPE },
{_______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_HOME,KC_PGUP,KC_UP  ,KC_PGDN },
{XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,KC_END, KC_LEFT,KC_DOWN,KC_RIGHT}
},
/* FTN
 * ,--------------------------------------------------------------------------.
 * |  ESC |WinOf|WinUp|     |     |Sh+Ca|     | PgUp| UP  | PgDo|PrtSc| DELET |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |WinLe|WinDo|WinRi|     |Al+Ca|CapsL| LEFT| DOWN|RIGHT|     |      |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |WinLW|WinRW|     |     |Ct+Ca|ScroL| HOME|     | END |     | Ctrl|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      | DeskL | DeskR| Task Manager|    DeskX    | MOUSE|     |     | LED |
 * `--------------------------------------------------------------------------'
 */
[4] = {
{KC_ESC ,LALT(KC_F4)        ,LGUI(KC_UP)         ,XXXXXXX          ,XXXXXXX    ,S(KC_CAPS)   ,XXXXXXX,KC_PGUP,KC_UP,KC_PGDN,KC_PSCR,KC_DELT},
{_______,LGUI(KC_LEFT)      ,LGUI(KC_DOWN)       ,LGUI(KC_RIGHT)   ,XXXXXXX    ,LALT(KC_CAPS),KC_CAPS,KC_LEFT,KC_DOWN,KC_RIGHT,XXXXXXX,XXXXXXX},
{_______,LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RIGHT)),XXXXXXX          ,XXXXXXX    ,LCTL(KC_CAPS),KC_SLCK,KC_HOME,XXXXXXX,KC_END,XXXXXXX,KC_RCTL},
{_______,LGUI(LCTL(KC_LEFT)),LGUI(LCTL(KC_RIGHT)),LCTL(LALT(KC_DELT)),XXXXXXX,XXXXXXX,XXXXXXX,LGUI(LCTL(KC_F4)),MOUSE,XXXXXXX,XXXXXXX,M(0)}
},
/* MOUSE
 * ,--------------------------------------------------------------------------.
 * |      |     |     |Mo_Up|     |     |     |M_WhL|M_WhU|M_WhR|     | RESET |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |     |Mo_Le|Mo_Do|Mo_Ri|     |     |M_Bt1|M_WhD|M_Bt2|     |      |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |     |     |     |     |     |     |M_AC0|M_AC1|M_AC2|     |     |
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |      |      | GO_DEFAULT  |  GO_DEFAULT |       |     |     |     |
 * `--------------------------------------------------------------------------'
 */
[10] ={
{XXXXXXX,XXXXXXX,XXXXXXX,KC_MS_U,XXXXXXX,XXXXXXX,XXXXXXX,KC_WH_L,KC_WH_U,KC_WH_R,XXXXXXX,RESET},
{XXXXXXX,XXXXXXX,KC_MS_L,KC_MS_D,KC_MS_R,XXXXXXX,XXXXXXX,KC_BTN1,KC_WH_D,KC_BTN2,XXXXXXX,XXXXXXX},
{XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_ACL0,KC_ACL1,KC_ACL2,XXXXXXX,XXXXXXX},
{XXXXXXX,XXXXXXX,XXXXXXX,GO_DEFT,XXXXXXX,XXXXXXX,XXXXXXX,GO_DEFT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX}
}
};

const uint16_t PROGMEM fn_actions[] = {
 [1] = ACTION_LAYER_TAP_KEY(1, KC_SPC),
 [2] = ACTION_LAYER_TAP_KEY(2, KC_SPC)
};

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
        case 10:
            if (record->event.pressed) {
                layer_on(10);
            }
        break;
        case 99:
            if (record->event.pressed) {
                layer_off(10);
                layer_off(4);
            }
        break;
      }
    return MACRO_NONE;
};