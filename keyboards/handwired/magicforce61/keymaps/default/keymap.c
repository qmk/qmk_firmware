#include "magicforce61.h"

#define _QWERTY 0
#define _FN1 1
#define _FN2 2
#define KC_ KC_TRNS
#define KC_X0 LT(_FN2, KC_GRV)
#define KC_X1 MO(_FN1)
#define KC_NAV_ESC LT(_FN1, KC_ESC)
#define KC_GUI MAGIC_UNNO_GUI

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = KEYMAP(
 /*,----+----+----+----+----+----+----+----+----+----+----+----+----+--------. */
    GRV , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,MINS,EQL ,  BSPC  ,
 /*|----`----`----`----`----`----`----`----`----`----`----`----`----`--------| */
    TAB   , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,LBRC,RBRC, BSLS ,
 /*|------`----`----`----`----`----`----`----`----`----`----`----`----`------| */
    NAV_ESC    , A  , S  , D  , F  , G  , H  , J  , K  , L  ,SCLN,QUOT,  ENTER ,
 /*|-------`----`----`----`----`----`----`----`----`----`----`----`----------| */
    LSPO   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH,     RSPC  ,
 /*|---------`----`----`----`----`----`----`----`----`----`----`-------------. */
    LCTL , RGUI ,LALT ,            SPACE             ,  X1  ,RALT ,RCTL ,    X1
 /*`-----+-----+-----+------------------------------+------+-----+-----' ANY   */
  ),

  [_FN1] = KEYMAP(
 /*,----+----+----+----+----+----+----+----+----+----+----+----+----+--------. */
    GRV , F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,   BSPC ,
 /*|esc-`-1--`-2--`-3--`-4--`-5--`-6--`-7--`-8--`-9--`-0--`mnus`plus`--bksp--| */
          ,    , UP ,    ,    ,    ,    ,    ,INS ,PSCR,    ,    ,    ,      ,
 /*|tab---`-q--`-w--`-e--`-r--`-t--`-y--`-u--`-i--`-o--`-p--`-{--`-}--`--|---| */
           ,LEFT,DOWN,RGHT,    ,    ,    , PGDN , PGUP ,    ,    ,    ,      ,
 /*|caps---`-a--`-s--`-d--`-f--`-g--`-h--`-j--`-k--`-l--`-;--`-'--`----enter-| */
             ,    ,    ,    ,    ,    ,VOLD,VOLU,MUTE,    ,    ,             ,
 /*|shift----`-z--`-x--`-c--`-v--`-b--`-n--`-m--`-,--`-.--`-/--`-------shift-. */
         ,     ,     ,                              ,      ,     ,     , MPLY
 /*`ctrl-+-gui-+-alt-+----------space---------------+-fn---+-alt-+ctrl-' ANY   */
  ),

  [_FN2] = KEYMAP(
 /*,----+----+----+----+----+----+----+----+----+----+----+----+----+--------. */
    GRV , F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,   BSPC ,
 /*|esc-`-1--`-2--`-3--`-4--`-5--`-6--`-7--`-8--`-9--`-0--`mnus`plus`--bksp--| */
          ,    ,    ,    ,    ,    ,    , 7  , 8  , 9  ,    ,    ,    ,      ,
 /*|tab---`-q--`-w--`-e--`-r--`-t--`-y--`-u--`-i--`-o--`-p--`-{--`-}--`--|---| */
           ,    ,    ,    ,    ,    ,    , 4  , 5  , 6  ,    ,    ,          ,
 /*|caps---`-a--`-s--`-d--`-f--`-g--`-h--`-j--`-k--`-l--`-;--`-'--`----enter-| */
             ,    ,    ,    ,    ,    , 0  , 1  , 2  , 3  ,    ,             ,
 /*|shift----`-z--`-x--`-c--`-v--`-b--`-n--`-m--`-,--`-.--`-/--`-------shift-. */
         ,     ,     ,                              ,      ,     ,     ,
 /*`ctrl-+-gui-+-alt-+----------space---------------+-fn---+-alt-+ctrl-' ANY   */
  )
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
