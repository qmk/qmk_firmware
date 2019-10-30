#include QMK_KEYBOARD_H

    /* Escape always goes back to default layer.
     * Full set of Ctrl, Alt, Shift almost throughout.
     *
     * (TT key: tap quickly 5 times.
     *  LT key: once for character, twice then hold for repeat.
     *  Some layer switch keys need Transparent on target layer.)
     *
     * */

#define _LTR 0 // letters (Dvorak)
#define _NSY 1 // numbers and symbols
#define _FUN 2 // function keys, layer switcher
#define _MOV 3 // movement arrows and mouse
#define _RAR 4 // strange keys never used

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 
    /* Layer 0: Dvorak, layers under thumbs, two arrows (not for normal typing).
     *
     */ 

    [ _LTR ] = LAYOUT (

        /*  Esc      '"  ,<  .>  pP  yY  fF  gG  cC  rR  lL      Bksp
         *  Tab+LCtl  aA  oO  eE  uU  iI  dD  hH  tT  nN  sS  -_+RCtl
         *  LSht       ;:  qQ  jJ  kK  xX  bB  mM  wW  vV  zZ    RSht
         *  LAlt    Left _MOV  Enter+_NSY Space+_NSY _FUN  Right RAlt
         *               hold´  hold        hold    toggle 
         */

        KC_ESC           , KC_QUOT , KC_COMM     , KC_DOT               , KC_P                  , KC_Y        , KC_F    , KC_G    , KC_C , KC_R , KC_L , KC_BSPC            ,
        LCTL_T ( KC_TAB ) , KC_A    , KC_O        , KC_E                 , KC_U                  , KC_I        , KC_D    , KC_H    , KC_T , KC_N , KC_S , RCTL_T ( KC_MINS ) ,
        KC_LSFT            , KC_SCLN , KC_Q        , KC_J                 , KC_K                  , KC_X        , KC_B    , KC_M    , KC_W , KC_V , KC_Z , KC_RSFT            ,
        KC_LALT             , KC_LEFT , TT ( _MOV ) ,  LT ( _NSY , KC_ENT ) , LT ( _NSY , KC_SPC ) , TG ( _FUN ) , KC_RGHT , KC_RALT
                      ) ,


    /* Layer 1: Numbers and symbols.
     *          Numpad function (-.Bksp,ent).
     *          (Instead of ~ a ` is printed with RSht, not sure why yet.)
     */

    [ _NSY ] = LAYOUT (
       
        /* _LTR      !   @   #   $   %   ^   &   *   (   )            Del
         * -+LCtl  1   2   3   4   5   \|  =+  /?  [{  ]}         `~+RCtl
         * .+LSht      0   9   8   7   6    |   +   ?   {   }      ~+RSht
         * Bksp+LAlt    Left   ___    ___     ___     ___ Right  Ent+RAlt
         * */
                
        TO ( _LTR )       , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_DEL             ,
        LCTL_T ( KC_MINS ) , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_BSLS , KC_EQL  , KC_SLSH , KC_LBRC , KC_RBRC , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_DOT )   , KC_0    , KC_9    , KC_8    , KC_7    , KC_6    , KC_PIPE , KC_PLUS , KC_QUES , KC_LCBR , KC_RCBR , RSFT_T ( KC_TILD ) , 
        LALT_T ( KC_BSPC )   , KC_LEFT , _______ , _______ , _______ , _______ , KC_RGHT  , RALT_T ( KC_ENT )
                      ) ,

    /* Layer 2: Function keys,
     * Toward any layer by toggle.
     */

    [ _FUN ] = LAYOUT (
    
        /* _LTR _NSY _FUN _MOV _RAR  xxx  xxx  F24 F23  F22  F21     xxx
         * LCtl   F1   F2   F3   F4   F5   F15  F14  F13  F12  F11  RCtl
         * LSht    F10  F9   F8   F7   F6   F16  F17  F18  F19  F20 RSht
         * LAlt  Left    ___     ___      ___      ___       Right  RAlt
         */
        
        TO ( _LTR ) , TO ( _NSY ) , TO ( _FUN ) , TO ( _MOV ) , TO ( _RAR ) , XXXXXXX , XXXXXXX , KC_F24 , KC_F23 , KC_F22 , KC_F21 , XXXXXXX ,
        KC_LCTL      , KC_F1       , KC_F2       , KC_F3       , KC_F4       , KC_F5   , KC_F15  , KC_F14 , KC_F13 , KC_F12 , KC_F11 , KC_RCTL ,
        KC_LSFT       , KC_F10      , KC_F9       , KC_F8       , KC_F7       , KC_F6   , KC_F16  , KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_RSFT ,
        KC_LALT        , KC_LEFT     , _______     , _______     , _______     , _______ , KC_RGHT , KC_RALT
                      ) ,


    /* Layer 3: Movement layer: mouse and hands on navigation
     * Trying to avoid a three key press for ~ on layer 1.
     */

    [ _MOV ] = LAYOUT (

        /* _LTR WLft WDn  WUp  WRht  xxx  Btn3 Home PgUp PgDn End     xxx
         * LCtl  MLft MDn  MUp  MRht  xxx  Btn1 Left Up   Down Right RCtl
         * LSht   Btn5 Btn4 Btn3 Butn2 Btn1 Btn2 Acc0 Acc1 Acc2  ~   RSht
         * LAlt   Left   ___     ___      ___      ___       Right   RAlt
         */
                
        TO ( _LTR ) , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , XXXXXXX , KC_BTN3 , KC_HOME , KC_PGUP , KC_PGDN , KC_END  , XXXXXXX ,
        KC_LCTL      , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , KC_BTN1 , KC_BTN1 , KC_LEFT , KC_UP   , KC_DOWN , KC_RGHT , KC_RCTL ,
        KC_LSFT       , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN2 , XXXXXXX , KC_BTN2 , KC_ACL0 , KC_ACL1 , KC_ACL2 , KC_TILD , KC_RSFT ,
        KC_LALT        , KC_LEFT , _______ , _______ , _______ , _______ , KC_RGHT , KC_RALT
                      ) ,

    /* Layer 4: Dump for various unused keys. Media keys on 2nd row.
     *   
     */

    [ _RAR ] = LAYOUT (

        /*  _LTR Power Sleep Wake  xxx  xxx  xxx  xxx  xxx  Pause ScrLk PrtSc
         *  Caps  xxx   xxx   xxx   xxx  xxx  xxx  xxx  xxx  xxx   xxx Insert
         *  NumL   Stop  Play  Prev  Next Vol- Vol+ Mute xxx  xxx   xxx   xxx
         *  xxx    Left    ___   ___       ___      ___      Right        App
         */

        TO ( _LTR ) , KC_PWR  , KC_SLEP , KC_WAKE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PAUS , KC_SLCK , KC_PSCR , 
        KC_CAPS      , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_INS  ,
        KC_NLCK       , KC_MSTP , KC_MPLY , KC_MPRV , KC_MNXT , KC_VOLD , KC_VOLU , KC_MUTE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        XXXXXXX        , KC_LEFT , _______ , _______ , _______ , _______ , KC_RGHT , KC_APP  
                      )  ,

};
