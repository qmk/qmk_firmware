#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;


    /* Dvorak keymap for Minivan default layout (44 keys)
     *
     * - Basic layers are: letters, numbers and remaining symbols, movement.
     * - 'Escape' always goes back to default layer.
     * - All other layers are through the _FUN layer on toggle.
     * - A lot of the modifiers, Del/Esc, alt-arrows repeat on layers.
     * - Layer switching by thumb hold keys (except _FUN).
     *
     * */

#define _LTR 0 // letters (Dvorak)
#define _NSY 1 // numbers and symbols
#define _FUN 2 // function keys, layer switcher
#define _MOV 3 // movement arrows and mouse
#define _RAR 4 // strange keys never used
#define _REV 5 // Reversing: numbers right, navigation left (mirrored.)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 
    /* Layer 0: Dvorak
     *
     * - Dual use keys create a delay in the key (tap/hold keys), therefore
     *   space is not dual use (most used key), neither is hyphen.
     */ 

    [ _LTR ] = LAYOUT (

        /*  Esc      '"   ,<  .>  pP  yY  fF  gG  cC  rR  lL         Bksp
         *  Tab+LCtl  aA   oO  eE  uU  iI  dD  hH  tT  nN  sS          -_
         *  LSht       ;:   qQ  jJ  kK  xX  bB  mM  wW  vV  zZ       RSht
         *  Left+LAlt   Del _MOV  Enter+_NSY Space  _NSY _FUN  Right+RAlt
         *                  hold      hold          hold toggle 
         */

        KC_ESC           , KC_QUOT , KC_COMM     , KC_DOT               , KC_P   , KC_Y        , KC_F        , KC_G     , KC_C     , KC_R , KC_L , KC_BSPC ,
        LCTL_T ( KC_TAB ) , KC_A    , KC_O        , KC_E                 , KC_U   , KC_I        , KC_D        , KC_H     , KC_T     , KC_N , KC_S , KC_MINS ,
        KC_LSFT            , KC_SCLN , KC_Q        , KC_J                 , KC_K   , KC_X        , KC_B        , KC_M     , KC_W     , KC_V , KC_Z , KC_RSFT ,
        LALT_T ( KC_LEFT )  , KC_DEL  , MO ( _MOV ) , LT ( _NSY , KC_ENT ) , KC_SPC , MO ( _NSY ) , TG ( _FUN ) , RALT_T ( KC_RIGHT )
                      ) ,


    /* Layer 1: Numbers and symbols.
     *          Off hand Number input (-.Bksp ent (shft)tab).
     */
    // KC_TILD does not work there, because of some limitation with shifted keys.

    [ _NSY ] = LAYOUT (
       
        /* _LTR      !   @   #   $   %   ^   &   *   (   )           Bspc
         * -+LCtl     1   2   3   4   5   \|  =+  /?  [{  ]}      `~+RCtl
         * .+LSht      0   9   8   7   6    |   +   ?   {   }      ~+RSht
         * Left+LAlt   Del   Sht(tab) ___      tab   ___  Ent  Right+RAlt
         * */
                
        TO ( _LTR )       , KC_EXLM , KC_AT        , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR  , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_MINS ) , KC_1    , KC_2         , KC_3    , KC_4    , KC_5    , KC_BSLS , KC_EQL  , KC_SLSH  , KC_LBRC , KC_RBRC , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_DOT )   , KC_0    , KC_9         , KC_8    , KC_7    , KC_6    , KC_PIPE , KC_PLUS , KC_QUES  , KC_LCBR , KC_RCBR , RSFT_T ( KC_TILD ) ,  
        LALT_T ( KC_LEFT )   , KC_DEL  , S ( KC_TAB ) , _______ , KC_TAB  , _______ , KC_ENT  , RALT_T ( KC_RGHT )
                      ) ,

    /* Layer 2: Function keys,
     *          Toward any layer by toggle.
     */

    [ _FUN ] = LAYOUT (
    
        /* _LTR _NSY _FUN _MOV _RAR  xxx  xxx  F24 F23  F22  F21     xxx
         * LCtl   F1   F2   F3   F4   F5   F15  F14  F13  F12  F11  RCtl
         * LSht    F10  F9   F8   F7   F6   F16  F17  F18  F19  F20 RSht
         * LAlt  ___     ___     ___      ___      ___       ___    RAlt
         */
        
        TO ( _LTR ) , TO ( _NSY ) , TO ( _FUN ) , TO ( _MOV ) , TO ( _RAR ) , TO ( _REV ) , XXXXXXX , KC_F24  , KC_F23 , KC_F22 , KC_F21 , XXXXXXX ,
        KC_LCTL      , KC_F1       , KC_F2       , KC_F3       , KC_F4       , KC_F5       , KC_F15  , KC_F14  , KC_F13 , KC_F12 , KC_F11 , KC_RCTL ,
        KC_LSFT       , KC_F10      , KC_F9       , KC_F8       , KC_F7       , KC_F6       , KC_F16  , KC_F17  , KC_F18 , KC_F19 , KC_F20 , KC_RSFT ,
        KC_LALT        , _______     , _______     , _______     , _______     , _______     , _______ , KC_RALT
                      ) ,


    /* Layer 3: Movement layer: mouse and hands on navigation
     *          Also delete/backspace, to navigate and delete together.
     */

    [ _MOV ] = LAYOUT (

        /* _LTR    WLft WDn  WUp  WRht  xxx  Btn3 Home PgUp PgDn End    Bksp
         * LCtl     MLft MDn  MUp  MRht  xxx  Btn1 Left Up   Down Right RCtl
         * LSht      Btn5 Btn4 Btn3 Butn2 Btn1 Btn2 Acc0 Acc1 Acc2 xxx  RSht
         * Left+LAlt  Del      ___  Sht(tab)  tab    ___    ___   Right+RAlt
         */
                
        TO ( _LTR )     , KC_WH_L , KC_WH_D , KC_WH_U      , KC_WH_R , XXXXXXX , KC_BTN3 , KC_HOME , KC_PGUP  , KC_PGDN , KC_END  , KC_BSPC ,
        KC_LCTL          , KC_MS_L , KC_MS_D , KC_MS_U      , KC_MS_R , KC_BTN1 , KC_BTN1 , KC_LEFT , KC_UP    , KC_DOWN , KC_RGHT , KC_RCTL ,
        KC_LSFT           , KC_BTN5 , KC_BTN4 , KC_BTN3      , KC_BTN2 , XXXXXXX , KC_BTN2 , KC_ACL0 , KC_ACL1  , KC_ACL2 , XXXXXXX , KC_RSFT ,
        LALT_T ( KC_LEFT ) , KC_DEL  , _______ , S ( KC_TAB ) , KC_TAB  , _______ , _______ , RALT_T ( KC_RGHT )
                      ) ,

    /* Layer 4: Dump for various unused keys. Media keys on 2nd row.
     *   
     */

    [ _RAR ] = LAYOUT (

        /*  _LTR CapL NumL Pause ScrLk PrtSc xxx  xxx  Power Sleep Wake    xxx   
         *  tab   xxx  xxx   xxx   xxx  xxx   xxx  xxx  xxx  xxx    xxx Insert
         *  xxx    Stop Play  Prev  Next Vol-  Vol+ Mute xxx  xxx   xxx    xxx
         *  xxx    ___     ___      ___       ___      ___      ___        App
         */

        TO ( _LTR ) , KC_CAPS , KC_NLCK , KC_PAUS , KC_SLCK , KC_PSCR , XXXXXXX , XXXXXXX , KC_PWR  , KC_SLEP , KC_WAKE , XXXXXXX ,
        KC_TAB       , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_INS  ,
        XXXXXXX       , KC_MSTP , KC_MPLY , KC_MPRV , KC_MNXT , KC_VOLD , KC_VOLU , KC_MUTE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        XXXXXXX        , _______ , _______ , _______ , _______ , _______ , _______ , KC_APP  
                      )  ,


    /* Layer 5: Reversing hands layer numbers and navigation, for one hand on keyboard use.
     *          Generally follows numbers layer.
     */

    [ _REV ] = LAYOUT (

        /* _LTR    End  PgDn PgUp Home  xxx  xxx  xxx  xxx  xxx  xxx     Bspc
         * -+LCtl    Left Down Up   Right xxx  5    4    3    2    1     RCtl
         * .+LSht     xxx  xxx  xxx  xxx   xxx  6    7    8    9    0    RSht
         * Left+LAlt Del    Sht(Tab)  ___      Tab    ___     Ent   Right+Alt
         */
                
        TO ( _LTR )       , KC_END  , KC_PGDN      , KC_PGUP , KC_HOME , XXXXXXX , XXXXXXX , XXXXXXX            , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC ,
        LCTL_T ( KC_MINS ) , KC_LEFT , KC_DOWN      , KC_UP   , KC_RGHT , XXXXXXX , KC_5    , KC_4               , KC_3    , KC_2    , KC_1    , KC_RCTL ,
        LSFT_T ( KC_DOT )   , XXXXXXX , XXXXXXX      , XXXXXXX , XXXXXXX , XXXXXXX , KC_6    , KC_7               , KC_8    , KC_9    , KC_0    , KC_RSFT ,
        LALT_T ( KC_LEFT )   , KC_DEL  , S ( KC_TAB ) , _______ , KC_TAB  , _______ , KC_ENT  , RALT_T ( KC_RGHT )
                      ) ,
};

// Copied from ../jetpacktuxedo/ (for LEDs)

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    // Set up RGB effects on _only_ the third LED (index 2)
    rgblight_set_effect_range(2, 1);
    // Set LED effects to breathing mode in a tealish blue color
    rgblight_sethsv_noeeprom(185, 255, 255);
    rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING + 2);

    // Init the first two LEDs to a static color
    setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
    setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
}

uint32_t layer_state_set_user(uint32_t state){
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;

    if (layer_state_cmp(state, 1)) { // symbols and numbers
      led1b = 255; // blue for symbols, like ink (writing)
      led0b = 255;
    }
    if (layer_state_cmp(state, 2)) { // F-keys, and layer toggles
      led1r = 255; // F-keys is red, because it can mean anything, "be careful"
      led0r = 255;
    } 
    if (layer_state_cmp(state, 3)) { // movement layer
      led1g = 255; // movement is green, "go forward"
      led0g = 255;
    }
    if (layer_state_cmp(state, 4)) { // weird layer
      led1b = 100; // some off color for strange keys
      led1r = 100;
      led0r = 100;
      led0b = 100;
    }
    if (layer_state_cmp(state, 5)) { // reverse hands layer
      led0g = 255; // green for nagivation left hand
      led1b = 255; // blue for symbols right hand
    }

    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
    setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
  return state;
}
