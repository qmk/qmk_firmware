#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _FN1 1
#define _FN2 2
#define KC_ KC_TRNS
#define KC_X0 LT(_FN2, KC_CAPS)
#define KC_X1 MO(_FN1)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* Default layer */
  [_QWERTY] = LAYOUT_kc(
 /*,----+----+----+----+----+----+----+----+----+----+----+----+----+--------.  ,----+----. */
     GESC , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,MINS,EQL , BSPC ,   INS ,PGUP,
 /*|----`----`----`----`----`----`----`----`----`----`----`----`----`--------|  |----`----| */
    TAB   , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,LBRC,RBRC, BSLS ,   DEL ,PGDN,
 /*|------`----`----`----`----`----`----`----`----`----`----`----`----`------|  `----`----' */
    X0     , A  , S  , D  , F  , G  , H  , J  , K  , L  ,SCLN,QUOT,    ENTER ,
 /*|-------`----`----`----`----`----`----`----`----`----`----`----`----------|  ,----. */
    LSFT     , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH,       RSFT  ,    UP ,
 /*|---------`----`----`----`----`----`----`----`----`----`----`-------------.--|----|----. */
    LCTL ,LALT ,LGUI ,            SPACE             ,  X1  ,RALT ,RCTL ,    LEFT,DOWN,RGHT
 /*`-----+-----+-----+------------------------------+------+-----+-----'   `----+----+----' */
  ),
 /* FN Layer */
  [_FN1] = LAYOUT_kc(
 /*,----+----+----+----+----+----+----+----+----+----+----+----+----+--------.  ,----+----. */
    GRV , F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,   BSPC ,       ,HOME,
 /*|esc-`-1--`-2--`-3--`-4--`-5--`-6--`-7--`-8--`-9--`-0--`mnus`plus`--bksp--|  |ins-`pgup| */
          ,    ,    ,    ,    ,    ,    ,    ,    ,    ,PSCR,SLCK,PAUS,      ,       ,END,
 /*|tab---`-q--`-w--`-e--`-r--`-t--`-y--`-u--`-i--`-o--`-p--`-{--`-}--`--|---|  `del-`pgdn' */
     X0    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,MRWD,MFFD,          ,
 /*|caps---`-a--`-s--`-d--`-f--`-g--`-h--`-j--`-k--`-l--`-;--`-'--`----enter-|  ,----. */
             ,    ,MPLY,MSTP,MPRV,MNXT,VOLD,VOLU,MUTE,    ,    ,             ,       ,
 /*|shift----`-z--`-x--`-c--`-v--`-b--`-n--`-m--`-,--`-.--`-/--`-------shift-.--|-up-|----. */
         ,     ,     ,                              ,      ,     ,     ,        ,    ,   
 /*`ctrl-+-gui-+-alt-+----------space---------------+-fn---+-alt-+ctrl-'   `left+down+rght' */
  ),

 /* CAPS LOCK layer */
  [_FN2] = LAYOUT_kc(
 /*,----+----+----+----+----+----+----+----+----+----+----+----+----+--------.  ,----+----. */
    GRV , F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,   BSPC ,   VOLU,HOME,
 /*|esc-`-1--`-2--`-3--`-4--`-5--`-6--`-7--`-8--`-9--`-0--`mnus`plus`--bksp--|  |ins-`pgup| */
          ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,   VOLD,END,
 /*|tab---`-q--`-w--`-e--`-r--`-t--`-y--`-u--`-i--`-o--`-p--`-{--`-}--`--|---|  `del-`pgdn' */
           ,    ,    ,    ,    ,    ,LEFT,DOWN, UP ,RGHT,    ,    ,          ,
 /*|caps---`-a--`-s--`-d--`-f--`-g--`-h--`-j--`-k--`-l--`-;--`-'--`----enter-|  ,----. */
             ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,             ,   MUTE,
 /*|shift----`-z--`-x--`-c--`-v--`-b--`-n--`-m--`-,--`-.--`-/--`-------shift-.--|-up-|----. */
         ,     ,     ,                              ,      ,     ,     ,    MPRV,MPLY,MNXT
 /*`ctrl-+-gui-+-alt-+----------space---------------+-fn---+-alt-+ctrl-'   `left+down+rght' */
  )
};



void led_set_user(uint8_t usb_led){
    //turn on the Pro Micro's on board LEDs for CAPS LOCK
    if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)){
        //set led pins to low
        setPinOutput(B0);
        writePinLow(B0);
        setPinOutput(B5);
        writePinLow(B5);
    } else {
        //set to Hi-Z
        setPinInput(B0);
        writePinLow(B0);
        setPinInput(B5);  
        writePinLow(B5);
    }
}
