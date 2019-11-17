#include QMK_KEYBOARD_H

// Layer switch TT(layer) tapping amount to make it toggle
#define TAPPING_TOGGLE 2

extern keymap_config_t keymap_config;


    /* Dvorak keymap for Minivan default layout (44 keys)
     *
     * - Basic layers are: letters, numbers and remaining symbols, movement.
     * - 'Escape' always goes back to default layer.
     * - All other layers are through the _FUN layer on toggle.
     * - A lot of the modifiers, Del/Esc, alt-arrows repeat on layers.
     * - Layer switching by thumbs, hold keys except _FUN which is one-shot.
     * - Rather than AltGr or Compose (which for some reason did not work here
     *   at the moment), RAlt position switches to a symbols layer.
     * - There are two layers that allow typing this layout, when the computer
     *   is already set to Dvorak, one descrambles the letters, the other 
     *   some remaining symbols on the numbers and remaining symbols layer.
     *
     *   The _FUN layer acts as the layer toggle hub from where to fall into the
     *   descramble system by activating _QDL, or in the normal mode by
     *   activating _LTR (those set default layer).
     *
     * */

// Defines the internal order of the layers. The Dvorak descramble mode needs to
// have a low order number, so that the other layers can be accessed on top of it.
// The sorting of these lines of code here is the same as the button order in
// the _FUN layer for them.

#define _LTR 0 // letters (Dvorak)
#define _NSY 3 // numbers and symbols
#define _FUN 4 // function keys, layer switcher
#define _MOV 5 // movement arrows and mouse
#define _RAR 6 // strange keys never used
#define _REV 7 // Reversing: numbers right, navigation left (mirrored.)
#define _ACC 8 // Accented letters and unusual symbols
#define _DRA 9 // Accented letters and unusual symbols
#define _QDN 2 // Unmapping Qwerty-to-Dvorak computer side remapping, numbers/symbols
#define _QDL 1 // Unmapping Qwerty-to-Dvorak computer side remapping, letters



    /* These are some rarely but existing letters in Dutch, and some other additions.
     * Using the Unicode input system
     */

enum unicode_names { // See below for meaning
    CAEL_,
    CAEU_,
    CAL_ACU,
    CAL_CAR,
    CAL_DIA,
    CAL_GRA,
    CAL_RNG,
    CAU_ACU,
    CAU_CAR,
    CAU_DIA,
    CAU_GRA,
    CAU_RNG,
    CCL_CDL,
    CCU_CDL,
    CEL_ACU,
    CEL_CAR,
    CEL_DIA,
    CEL_GRA,
    CEU_ACU,
    CEU_CAR,
    CEU_DIA,
    CEU_GRA,
    CEX_INV,
    CIL_ACU,
    CIL_CAR, 
    CIL_DIA,
    CIL_GRA,
    CIU_ACU,
    CIU_CAR,
    CIU_DIA,
    CIU_GRA,
    CNL_TLD,
    CNU_TLD,
    COEL_,
    COEU_,
    COL_ACU,
    COL_CAR,
    COL_DIA,
    COL_GRA,
    COL_STK,
    COU_ACU,
    COU_CAR,
    COU_DIA,
    COU_GRA,
    COU_STK,
    CQU_INV,
    CSL_SHP,
    CS_SAD_,
    CS_SMIL,
    CS_SQIG,
    CS_THDN,
    CS_THUP,
    CS_YAYS,
    CUL_ACU,
    CUL_CAR,
    CUL_DIA,
    CUL_GRA,
    CUU_ACU,
    CUU_CAR,
    CUU_DIA,
    CUU_GRA,
    CYL_ACU,
    CYL_DIA,
    CYU_ACU,
    CYU_DIA,
};

const uint32_t PROGMEM unicode_map[] = {

    // a lower case variants
    [CAL_ACU] = 0x00e1, // 'C' for Costum 'A' for a, 'L' for lower, "ACU" for acute: á
    [CAL_CAR] = 0x00e2, //      ''              ''        ''        "CAR" for caret: â
    [CAL_DIA] = 0x00e4, //      ''              ''        ''        "DIA" for diaereses: ä
    [CAL_GRA] = 0x00e0, //      ''              ''        ''        "GRA" for grave: à
      // A upper case variants
    [CAU_ACU] = 0x00c1, //      ''              ''   'U' for upper, "ACU" for acute: Á
    [CAU_CAR] = 0x00c2, //      ''              ''        ''        "CAR" for caret: Â
    [CAU_DIA] = 0x00c4, //      ''              ''        ''        "DIA" for diaereses: Ä
    [CAU_GRA] = 0x00c0, //      ''              ''        ''        "GRA" for grave: À

    // e lower case variants
    [CEL_ACU] = 0x00e9, // 'C' for Costum 'E' for e, 'L' for lower, "ACU" for acute: é
    [CEL_CAR] = 0x00ea, //      ''              ''        ''        "CAR" for caret: ê
    [CEL_DIA] = 0x00eb, //      ''              ''        ''        "DIA" for diaereses: ë
    [CEL_GRA] = 0x00e8, //      ''              ''        ''        "GRA" for grave: è
      // E upper case variants
    [CEU_ACU] = 0x00c9, //      ''              ''   'U' for uuper, "ACU" for acute: É
    [CEU_CAR] = 0x00ca, //      ''              ''        ''        "CAR" for caret: Ê
    [CEU_DIA] = 0x00cb, //      ''              ''        ''        "DIA" for diaereses: Ë
    [CEU_GRA] = 0x00c8, //      ''              ''        ''        "GRA" for grave: È
    
    // i lower case variants
    [CIL_ACU] = 0x00ed, //      ''         'I' for i, 'L' for lower, "ACU" for acute: í
    [CIL_CAR] = 0x00ee, //      ''              ''         ''        "CAR" for caret: î
    [CIL_DIA] = 0x00ef, //      ''              ''         ''        "DIA" for diaereses: ï
    [CIL_GRA] = 0x00ec, //      ''              ''         ''        "GRA" for grave: ì
      // I upper case variants
    [CIU_ACU] = 0x00cd, //      ''              ''    'U' for upper, "ACU" for acute: Í
    [CIU_CAR] = 0x00ce, //      ''              ''         ''        "CAR" for caret: Î
    [CIU_DIA] = 0x00cf, //      ''              ''         ''        "DIA" for diaereses: Ï
    [CIU_GRA] = 0x00cc, //      ''              ''         ''        "GRA" for grave: Ì
    
    // o lower case variants
    [COL_ACU] = 0x00f3, // 'C' for Costum 'O' for a, 'L' for lower, "ACU" for acute: ó
    [COL_CAR] = 0x00f4, //      ''              ''        ''        "CAR" for caret: ô
    [COL_DIA] = 0x00f6, //      ''              ''        ''        "DIA" for diaereses: ö
    [COL_GRA] = 0x00f2, //      ''              ''        ''        "GRA" for grave: ò
      // O upper case variants
    [COU_ACU] = 0x00d3, //      ''              ''   'U' for upper, "ACU" for acute: Ó
    [COU_CAR] = 0x00d4, //      ''              ''        ''        "CAR" for caret: Ô
    [COU_DIA] = 0x00d6, //      ''              ''        ''        "DIA" for diaereses: Ö
    [COU_GRA] = 0x00d2, //      ''              ''        ''        "GRA" for grave: Ò

    // u lower case variants
    [CUL_ACU] = 0x00fa, // 'C' for Costum 'U' for a, 'L' for lower, "ACU" for acute: ú
    [CUL_CAR] = 0x00fb, //      ''              ''        ''        "CAR" for caret: û
    [CUL_DIA] = 0x00fc, //      ''              ''        ''        "DIA" for diaereses: ü
    [CUL_GRA] = 0x00f9, //      ''              ''        ''        "GRA" for grave: ù
      // U upper case variants
    [CUU_ACU] = 0x00da, //      ''              ''   'U' for upper, "ACU" for acute: Ú
    [CUU_CAR] = 0x00db, //      ''              ''        ''        "CAR" for caret: Û
    [CUU_DIA] = 0x00dc, //      ''              ''        ''        "DIA" for diaereses: Ü
    [CUU_GRA] = 0x00d9, //      ''              ''        ''        "GRA" for grave: Ù

    // N with tilde
    [CNL_TLD] = 0x00f1, //      ''        'N' for n, 'L' for lower, "TLD" for tilde: ñ
    [CNU_TLD] = 0x00d1, //      ''             ''    'U' for upper,        ''      : Ñ

    // C with cedilla
    [CCL_CDL] = 0x00e7, //      ''        'C' for c, 'L' for lower, "CDL" for cedilla: ç 
    [CCU_CDL] = 0x00c7, //      ''             ''    'U' for upper,        ''        : Ç

    // Y with acute
    [CYL_ACU] = 0x00fd, //      ''        'Y' for y, 'L' for lower, "ACU" for Acute:
    [CYU_ACU] = 0x00dd, //      ''             ''    'U' for upper,        ''      :
    // Y with diaereses
    [CYL_DIA] = 0x00ff, //      ''        'Y' for y, 'L' for lower, "DIA" for Diareses: ÿ
    [CYU_DIA] = 0x0178, //      ''             ''    'U' for upper,        ''         : Ÿ

    // OE (French)
    [COEL_] = 0x0153, //        ''        'AO' for ao, 'L' for lower: œ
    [COEU_] = 0x0152, //        ''              ''     'U' for upper: Œ
                            
    // AE (French)          
    [CAEL_] = 0x00e6, //        ''        'AE' for ae, 'L' for lower: æ
    [CAEU_] = 0x00c6, //        ''              ''     'U' for upper: Æ

    // O with stroke (Scandinavia)
    [COL_STK] = 0x00f8, //      ''        'O' for o, 'L' for lower, "STK" for Stroke: ø
    [COU_STK] = 0x00d8, //      ''             ''    'U' for upper,        ''       : Ø

    // A with ring (Scandinavia)
    [CAL_RNG] = 0x00e5, //      ''        'A' for a, 'L' for lower, "RNG" for Ring: å
    [CAU_RNG] = 0x00c5, //      ''             ''    'U' for upper,        ''     : Å

    //German:
     // sharp s 
    [CSL_SHP] = 0x00df, //      ''         'S' for s, 'L' for lower, "SHP" for sharp: ß

    //Spanish additional symbols:
    [CEX_INV] = 0x00a1, //      ''        "EX" for exclamation mark, "INV" for inverted: 
    [CQU_INV] = 0x00bf, //      ''        "QU" for question mark,           ''         :
  
    // Some Unicode symbols that might be handy
      // Happy symbols:
    [CS_THUP] = 0x1f44d, //      ''         'S' for symbol,  "THUP"  for <thumb up> 👍 
    [CS_SMIL] = 0x1f642, //      ''              ''          "SMIL"  for <smile> 🙂 
    [CS_YAYS] = 0x1f603, //      ''              ''          "YAYS"  for <big smile>  😃 
  
      //Sad symbols
    [CS_SAD_] = 0x1f641, //      ''              ''          "SAD_"   for  <sad face>  🙁 
    [CS_SQIG] = 0x2368,  //      ''              ''          "SQIG"  for "Squiggly" face <sad>  ⍨
    [CS_THDN] = 0x1f44e	 //      ''              ''          "THDN"  for <thumb down>  👎 
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 
    /* Layer 0: Dvorak
     *
     * - Dual use keys create a delay in the key (tap/hold keys), therefore
     *   space is not dual use (most used key), neither is hyphen.
     *
     * - If _ACC right hand or _RAR is much used, an obvious choice is to 
     *   change the layer switched to by the Delete key, or copy the more
     *   used keys to the _DRA layer, etc. Perhaps ;: could be a layer
     *   switch key as well, if not much used; or space as many do.
     */ 

    [ _LTR ] = LAYOUT (

//                                        | Right hand
// <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>   // Keys by finger
// -*-                                   <|>                                       // Access from all other layers -*- there
// Esc      '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL    Bksp     //" ((syntax highlighting fix))
// Tab+LCtl aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS      -_
// LSht     ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht
// ---------------------------------------------------------------------
// Left+LAlt   Del+_DRA _MOV  Enter+_NSY| Space  _NSY _FUN    Right+_ACC           // _XYZ are layer switches
//                                     <|>
//             hold     hold  hold      |        hold oneshot hold                 // Type of layer switch
// <1          <2       <3    <4        | 4>     3>   2>      1>                   // Keys by number
//
//
//      <pink2            , <pinky  , <ring   , <middl , <indx, <ind|, indx>, inde>, midd>, ring>, pink>, pink2>  ,
//      -*-               ,         ,         ,        ,      ,    <|,>     ,      ,      ,      ,      ,         ,
        KC_ESC            , KC_QUOT , KC_COMM , KC_DOT , KC_P , KC_Y , KC_F , KC_G , KC_C , KC_R , KC_L , KC_BSPC ,
        LCTL_T ( KC_TAB ) , KC_A    , KC_O    , KC_E   , KC_U , KC_I , KC_D , KC_H , KC_T , KC_N , KC_S , KC_MINS ,
        KC_LSFT           , KC_SCLN , KC_Q    , KC_J   , KC_K , KC_X , KC_B , KC_M , KC_W , KC_V , KC_Z , KC_RSFT ,
//      ---------------------------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , LT ( _DRA , KC_DEL ) , MO ( _MOV ) , LT ( _NSY , KC_ENT ) , KC_SPC , MO ( _NSY ) , OSL ( _FUN ) , LT ( _ACC , KC_RIGHT )
//                         ,                      ,             ,                    <|,>       ,             ,              ,
//      <1                 , <2                   , <3          , <4                  |, 4>     , 3>          , 2>           , 1>
                      ),

	/**/


    /* Layer 1: Numbers and symbols.
     *          Off hand Number input (-.Bksp ent (shft)tab).
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _NSY ] = LAYOUT (

// <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//        -*-                          <|>                                       // Layer access from _FUN -*-
// _LTR   !     @     #     $     %     | ^     &     *     (     )        Bspc
// -+LCtl 1!    2@    3#    4$    5%    | \|    =+    /?    [{    ]}    `~+RCtl
// .+LSht 0)    9(    8*    7&    6^    | |     +     ?     {     }      `+RSht  // QMK limitation prevents ~
// --------------------------------------------------------
// Left+LAlt Del   Sht(tab) ___  | tab   ___   Ent   Right+RAlt
//                          -*- <|>      -*-                                     // Layer access from _LTR -*-
// <1        <2    <3       <4   | 4>    3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring , <middl  , <index , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,       ,         ,        ,       <|,>        ,         ,         ,         ,         ,                    ,
        TO ( _LTR )        , KC_EXLM , KC_AT , KC_HASH , KC_DLR , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_MINS ) , KC_1    , KC_2  , KC_3    , KC_4   , KC_5    , KC_BSLS , KC_EQL  , KC_SLSH , KC_LBRC , KC_RBRC , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_DOT )  , KC_0    , KC_9  , KC_8    , KC_7   , KC_6    , KC_PIPE , KC_PLUS , KC_QUES , KC_LCBR , KC_RCBR , RSFT_T ( KC_TILD ) ,  
//      -----------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , S ( KC_TAB ) , _______ , KC_TAB , _______ , KC_ENT , RALT_T ( KC_RGHT )
//                         ,        ,              , -*-   <|,>       , -*-     ,        ,
//      <1                 , <2     , <3           , <4     |, 4>     , 3>      , 2>     , 1>
                      ),

	/**/


    /* Layer 2: Function keys, on the right side with Control+Alt (switch virtual consoles in Linux)
     *          Toward any layer by toggle.
     */

    [ _FUN ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
// base  toggl toggl toggl toggl toggl | toggl toggl             toggl base       // Type of layer switch
//             -*-                    <|>                                         // Access -*- _FUN
// _LTR  _NSY  _FUN  _MOV  _RAR  _REV  | _ACC  _DRA  F12   F11   _QDN  _QDL
// LCtl  CAF1  CAF2  CAF3  CAF4  CAF5  | F5    F4    F3    F2    F1    RCtl
// LSht  CAF10 CAF9  CAF8  CAF7  CAF6  | F6    F7    F8    F9    F10   RSht
// -----------------------------------------------
// LAlt  xxx   xxx   xxx  | xxx   xxx   xxx   RAlt
//                       <|>            -*-                                       // Acces -*- _LTR
// <1    <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky         , <ring         , <middl        , <index        , <indx2       |, indx2>      , index>      , middl> , ring>  , pinky>      , pink2>      ,
//                  ,                , -*-           ,               ,               ,             <|,>            ,             ,        ,        ,             ,             ,
        DF ( _LTR ) , TO ( _NSY )    , TO ( _FUN )   , TO ( _MOV )   , TO ( _RAR )   , TO ( _REV )   , TO ( _ACC ) , TO ( _DRA ) , KC_F12 , KC_F11 , TO ( _QDN ) , DF ( _QDL ) ,
        KC_LCTL     , LCA ( KC_F1 )  , LCA ( KC_F2 ) , LCA ( KC_F3 ) , LCA ( KC_F4 ) , LCA ( KC_F5 ) , KC_F5       , KC_F4       , KC_F3  , KC_F2  , KC_F1       , KC_RCTL     ,
        KC_LSFT     , LCA ( KC_F10 ) , LCA ( KC_F9 ) , LCA ( KC_F8 ) , LCA ( KC_F7 ) , LCA ( KC_F6 ) , KC_F6       , KC_F7       , KC_F8  , KC_F9  , KC_F10      , KC_RSFT     ,
//      -----------------------------------------------------------------------------
        KC_LALT , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RALT
//              ,         ,         ,       <|,>        ,         , -*-     ,
//      <1      , <2      , <3      , <4     |, 4>      , 3>      , 2>      , 1>
                      ),

	/**/


    /* Layer 3: Movement layer: mouse and hands on navigation
     *          Also delete/backspace, to navigate and delete together.
     */

    [ _MOV ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                   -*-              <|>
// _LTR  WLft  WDn   WUp   WRht  xxx   | Btn3  Home  PgUp  PgDn  End   Bksp
// LCtl  MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
// LSht  Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSht
// -------------------------------------------------------------
// Left+LAlt Del   ___   Sht(tab) | tab   xxx   xxx   Right+RAlt
//                 -*-           <|>
// <1        <2    <3    <4       | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                  ,         ,         , -*-     ,         ,       <|,>        ,         ,         ,         ,         ,         ,
        TO ( _LTR ) , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , XXXXXXX , KC_BTN3 , KC_HOME , KC_PGUP , KC_PGDN , KC_END  , KC_BSPC ,
        KC_LCTL     , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , KC_BTN1 , KC_BTN1 , KC_LEFT , KC_UP   , KC_DOWN , KC_RGHT , KC_RCTL ,
        KC_LSFT     , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN2 , XXXXXXX , KC_BTN2 , KC_ACL0 , KC_ACL1 , KC_ACL2 , XXXXXXX , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL  , _______ , S ( KC_TAB ) , KC_TAB  , XXXXXXX , XXXXXXX , RALT_T ( KC_RGHT )
//                         ,         , -*-     ,            <|,>        ,         ,         ,
//      <1                 , <2      , <3      , <4          |, 4>      , 3>      , 2>      , 1>
                      ),

	/**/


    /* Layer 4: Dump for various unused keys. Media keys on 2nd row.
     *   
     */

    [ _RAR ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                         -*-        <|>
// _LTR  CapL  NumL  Pause ScrLk PrtSc | xxx   xxx   Power Sleep Wake   xxx   
// Tab   uLNX  uBSD  uOSX  uWIN  uWNC  | xxx   xxx   xxx   xxx   xxx Insert
// xxx   Stop  Play  Prev  Next  Vol-  | Vol+  Mute  xxx   xxx   xxx    xxx
// ------------------------------------------------
// xxx    xxx     xxx   xxx  | xxx  xxx   xxx   App
//                          <|>
// <1     <2      <3    <4   | 4>   3>    2>    1>  
//
//
//      <pink2      , <pinky           , <ring            , <middl           , <index           , <indx2           |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                  ,                  ,                  ,                  , -*-              ,                 <|,>        ,         ,         ,         ,         ,         ,
        TO ( _LTR ) , KC_CAPS          , KC_NLCK          , KC_PAUS          , KC_SLCK          , KC_PSCR           , XXXXXXX , XXXXXXX , KC_PWR  , KC_SLEP , KC_WAKE , XXXXXXX ,
        KC_TAB      , UNICODE_MODE_LNX , UNICODE_MODE_BSD , UNICODE_MODE_OSX , UNICODE_MODE_WIN , UNICODE_MODE_WINC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_INS  ,
        XXXXXXX     , KC_MSTP          , KC_MPLY          , KC_MPRV          , KC_MNXT          , KC_VOLD           , KC_VOLU , KC_MUTE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//      ----------------------------------------------------------------------------
        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_APP  
//              ,         ,         ,       <|,>        ,         ,         ,
//      <1      , <2      , <3      , <4     |, 4>      , 3>      , 2>      , 1>
                      ),

	/**/


    /* Layer 5: Reversing hands layer numbers and navigation, for one hand on keyboard use.
     *          Generally follows numbers layer.
     */

    [ _REV ] = LAYOUT (

// <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                -*-  <|>
// _LTR   End   PgDn  PgUp  Home  xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
// -+LCtl Left  Down  Up    Right xxx   | 5%    4$    3#    2@    1!    RCtl
// .+LSht xxx   xxx   xxx   xxx   xxx   | 6^    7&    8*    9(    0)    RSht
// ----------------------------------------------------------
// Left+LAlt Del   Sht(Tab) xxx  | Tab  xxx   Ent   Right+Alt
//                              <|>
// <1        <2    <3       <4   | 4>   3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                         ,         ,         ,         ,         , -*-   <|,>        ,         ,         ,         ,         ,         ,
        TO ( _LTR )        , KC_END  , KC_PGDN , KC_PGUP , KC_HOME , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC ,
        LCTL_T ( KC_MINS ) , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , XXXXXXX , KC_5    , KC_4    , KC_3    , KC_2    , KC_1    , KC_RCTL ,
        LSFT_T ( KC_DOT )  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_RSFT ,
//      -------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , S ( KC_TAB ) , XXXXXXX , KC_TAB  , XXXXXXX , KC_ENT  , RALT_T ( KC_RGHT )
//                         ,        ,              ,       <|,>        ,         ,         ,
//      <1                 , <2     , <3           , <4     |, 4>      , 3>      , 2>      , 1>
                      ),

	/**/


    /* Layer 6: Accented and other unusual characters. It seems this would
     *             cover Dutch, German, French, Scandinavia, Italy and Spain.
     *             There is room enough, so why not.
     *          It should helps with remembering what keys are where, if one
     *             knows the logic behind it (however flawed it might be).
     *
     *          The logic is ... Versions of the vowels with accents are
     *                              widened vertically on the board, from their
     *                              normal position.
     *                           Grave is a line going up, thus on upper row. é
     *                           Acute is a line going down, thus on lower row. è
     *                           Diaereses is dots going horizontal, thus middle. ë
     *                           Diareses is umlaut which is most frequent if
     *                              including German, thus home row. ë
     *                           There is no room for Caret on the left, thus it is
     *                              on the right, following same-finger logic (O 
     *                              is ring finger, etc).
     *                           Caret is on the lower row to make room for versions 
     *                              of 'n' and 'c' near their normal position.
     *                           There is no room for ÿŸ on the normal y, because
     *                              íÍ is on it, which is more important, and to
     *                              keep the logic of that block, therefore it is
     *                              as close to it as can be.
     *                           øØ and åÅ follow the same-finger logic (a is left
     *                              hand pinky, etc), and are on remaining spots.
     *                           œŒ and æÆ are also no remaining spots, both close
     *                              to êÊ for the e in there, the œŒ being further
     *                              to the left to follow the same finger logic on
     *                              that right hand side: a on the right, o on the left.
     *                           ¡ and ¿ had no more room on this layer, therefore,
     *                              and because they are unusual, they are on the 
     *                              _DRA(wings) layer. They are located under the keys
     *                              that also have ! and ?, respectively.
     *
     *       As the time of this writing it seems a one-shot layer cannot
     *       be combined with a tap/toggle, thus this layer is on a
     *       hold key.  It also seems that a one-shot shift key cannot
     *       be combined with the below XP ( ... ), hence it results in
     *       three key combinations.  At least right shift (on both layers)
     *       is close to the layer hold, and the most important ones are
     *       on the left.  That the shift is on both layers seems to matter,
     *       so that the order of pressing the shift and the layer does not
     *       matter anymore. It is an option to make _ACC on the _FUN layer
     *       a one shot if this is a problem, but it breaks the overall
     *       logic on that _FUN layer with its toggles.  It seems overall
     *       this will be doable like it is.
     */ 

    [ _ACC ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                    <|>-*-
// _LTR  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    xxx   çÇ    øØ    åÅ    Bspc
// LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
// LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
// ---------------------------------------------------------
// LAlt+Left Del   xxx   Ent  | Spc   xxx   xxx   ___
//                           <|>                  -*-
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky                   , <ring                    , <middl                   , <index                   , <indx2                  |, indx2>                   , index>                   , middl>                   , ring>                    , pinky>                   , pink2>  ,
//                  ,                          ,                          ,                          ,                          ,                        <|,>-*-                      ,                          ,                          ,                          ,                          ,         ,
        TO ( _LTR ) , XP ( CAL_ACU , CAU_ACU ) , XP ( COL_ACU , COU_ACU ) , XP ( CEL_ACU , CEU_ACU ) , XP ( CUL_ACU , CUU_ACU ) , XP ( CIL_ACU , CIU_ACU ) , XP ( CYL_ACU , CYU_ACU ) , XXXXXXX                  , XP ( CCL_CDL , CCU_CDL ) , XP ( COL_STK , COU_STK ) , XP ( CAL_RNG , CAU_RNG ) , KC_BSPC ,
        KC_LCTL     , XP ( CAL_DIA , CAU_DIA ) , XP ( COL_DIA , COU_DIA ) , XP ( CEL_DIA , CEU_DIA ) , XP ( CUL_DIA , CUU_DIA ) , XP ( CIL_DIA , CIU_DIA ) , XP ( CYL_DIA , CYU_DIA ) , XP ( COEL_ , COEU_ )     , XP ( CAEL_ , CAEU_ )     , XP ( CNL_TLD , CNU_TLD ) , X ( CSL_SHP )            , KC_RCTL ,
        KC_LSFT     , XP ( CAL_GRA , CAU_GRA ) , XP ( COL_GRA , COU_GRA ) , XP ( CEL_GRA , CEU_GRA ) , XP ( CUL_GRA , CUU_GRA ) , XP ( CIL_GRA , CIU_GRA ) , XP ( CIL_CAR , CIU_CAR ) , XP ( CUL_CAR , CUU_CAR ) , XP ( CEL_CAR , CEU_CAR ) , XP ( COL_CAR , COU_CAR ) , XP ( CAL_CAR , CAU_CAR ) , KC_RSFT ,
//      ------------------------------------------------------------------------------------
        KC_LALT , KC_DEL , XXXXXXX , KC_ENT , KC_SPC , XXXXXXX , XXXXXXX , _______ 
//	        ,        ,         ,      <|,>       ,         ,         , -*-
//     <1       ,<2      ,<3       ,<4     |, 4>     , 3>      , 2>      , 1>
                      ),

	/**/


    /* Layer 7: Drawings, like various Unicode symbols, and whatever else.
     *          The emoticons follow the "logic" of the movement layer.
     *          The symbols ¡ and ¿ are placed on top of ! and ?.
     *   
     */

    [ _DRA ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                    <|>                              -*-
// _LTR  ¡     xxx   xxx   xxx   xxx   | xxx  🙂😃   👍    👎    ⍨🙁   Bspc
// LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   ¿     xxx   xxx   RCtl
// LSht  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSht
// ---------------------------------------------------------
// LAlt+Left ___   xxx   Ent  | Spc   xxx   xxx   RAlt+Right
//           -*-             <|>
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky        , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>                   , middl>        , ring>         , pinky>                   , pink2>  ,
//                  ,               ,         ,         ,         ,       <|,>        ,                          ,               ,               ,                          ,         ,
        TO ( _LTR ) , X ( CEX_INV ) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XP ( CS_SMIL , CS_YAYS ) , X ( CS_THUP ) , X ( CS_THDN ) , XP ( CS_SQIG , CS_SAD_ ) , KC_BSPC ,
        KC_LCTL     , XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX                  , X ( CQU_INV ) , XXXXXXX       , XXXXXXX                  , KC_RCTL ,
        KC_LSFT     , XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX                  , XXXXXXX       , XXXXXXX       , XXXXXXX                  , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , _______ , XXXXXXX , KC_ENT  , KC_SPC  , XXXXXXX , XXXXXXX , RALT_T ( KC_RGHT )
//                         ,         ,         ,       <|,>        ,         ,         ,
//      <1                 , <2      , <3      , <4     |, 4>      , 3>      , 2>      , 1>
                      ),

	/**/


    /* Layers 9 and 10: Descramble basic layers if the computer itself is
     *                  applying Dvorak remapping.
     *
     *          When a computer is already set to Dvorak, connecting a
     *          keyboard which is natively Dvorak results in garbage.
     *          The computer side general keycodes to Dvorak remapping goes
     *          on top of the wrong input, resulting in the following being
     *          effective:
     *
     *          _LTR layer:        |
     *          Esc  -  w  v  l  f   u  i  j  p  n  Bspc
     *          Tab  a  r  .  g  c   e  d  y  b  o  [
     *          Sft  s  '  h  t  q   x  m  ,  k  ;  Sft
     *                     Enter  Space
     *          _NSY layer:        |
     *          _LTR !  @  #  $  %   ^  &  *  (  )  Bspc
     *          [    1  2  3  4  5   \  ]  z  /  =  `
     *          Sft  0  9  8  7  6   |  }  Z  ?  +  `
     *                     Enter  Space
     *
     *          To solve this results in the strange layout given below.
     *          The result is a Qwerty layout, however it will not be ideal
     *          for Qwerty typers because the symbols are not arranged that
     *          well if typed with the intent of it being Qwerty.
     */ 

    /* Layer 9: Descrambled _NSY layer for a computer already set to Dvorak (see just above).
     *
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _QDN ] = LAYOUT (

// <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                     <|>                        -*-            // Layer access from _FUN -*-
// _LTR   !     @     #     $     %     | ^     &     *     (     )        Bspc
// -+LCtl 1!    2@    3#    4$    5%    | \|    ]}    [{    =+    '"    `~+RCtl
// .+LSht 0)    9(    8*    7&    6^    | |     }     {     +     "      `+RSht  // QMK limitation prevents ~
// --------------------------------------------------------
// Left+LAlt Del   Sht(tab) ___  | tab   ___   Ent   Right+RAlt
//                          -*- <|>      -*-                                     // Layer access from _LTR -*-
// <1        <2    <3       <4   | 4>    3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring , <middl  , <index , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,       ,         ,        ,       <|,>        ,         ,         ,         ,         ,                    ,
        TO ( _LTR )        , KC_EXLM , KC_AT , KC_HASH , KC_DLR , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_MINS ) , KC_1    , KC_2  , KC_3    , KC_4   , KC_5    , KC_BSLS , KC_RBRC , KC_LBRC , KC_MINS , KC_EQL  , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_DOT )  , KC_0    , KC_9  , KC_8    , KC_7   , KC_6    , KC_PIPE , KC_RCBR , KC_LCBR , KC_UNDS , KC_PLUS , RSFT_T ( KC_TILD ) ,  
//      -----------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , S ( KC_TAB ) , _______ , KC_TAB , _______ , KC_ENT , RALT_T ( KC_RGHT )
//                         ,        ,              , -*-   <|,>       , -*-     ,        ,
//      <1                 , <2     , <3           , <4     |, 4>     , 3>      , 2>     , 1>
                      ),

	/**/

    /* Layer 10: Descrambled _LTR layer for a computer already set to Dvorak (see above).
     *           It is a copy of _LTR, with moved around stuff, and points to _QDN instead
     *           of _NSY, because that too has some descrambled symbols. The rest is the same.
     *
     */

    [ _QDL ] = LAYOUT (

//                                        | Right hand
// <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>   // Keys by finger
//                                       <|>                              -!-      // Access from _FUN -!- there
// Esc      qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP    Bksp     //" ((syntax highlighting fix))
// Tab+LCtl aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:      '"
// LSht     zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSht
// ---------------------------------------------------------------------
// Left+LAlt   Del+_DRA _MOV  Enter+_QDN| Space  _QDN _FUN    Right+_ACC           // _XYZ are layer switches
//                                     <|>
//             hold     hold  hold      |        hold oneshot hold                 // Type of layer switch
// <1          <2       <3    <4        | 4>     3>   2>      1>                   // Keys by number
//                                                   
//
//      <pink2            , <pink, <ring, <midd, <indx, <ind|, indx>, inde>, middle> , ring>  , pink>   , pink2>  ,
//      -*-               ,      ,      ,      ,      ,    <|,>     ,      ,         ,        ,         ,         ,
        KC_ESC            , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I    , KC_O   , KC_P    , KC_BSPC ,
        LCTL_T ( KC_TAB ) , KC_A , KC_S , KC_D , KC_F , KC_G , KC_H , KC_J , KC_K    , KC_L   , KC_SCLN , KC_QUOT ,
        KC_LSFT           , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_N , KC_M , KC_COMM , KC_DOT , KC_SLSH , KC_RSFT ,
//      ---------------------------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , LT ( _DRA , KC_DEL ) , MO ( _MOV ) , LT ( _QDN , KC_ENT ) , KC_SPC , MO ( _QDN ) , OSL ( _FUN ) , LT ( _ACC , KC_RIGHT )
//                         ,                      ,             ,                    <|,>       ,             ,              ,
//      <1                 , <2                   , <3          , <4                  |, 4>     , 3>          , 2>           , 1>
                      ),

	/**/




/*
 * New layer template. Includes left/right movement arrows, deletion, modifiers.
 *
    [ _??? ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                    <|>
// _LTR  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
// LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RCtl
// LSht  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSht
// ---------------------------------------------------------
// LAlt+Left Del   ___   ___  | ___   ___   ___   RAlt+Right
//                           <|>
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                  ,         ,         ,         ,         ,       <|,>        ,         ,         ,         ,         ,         ,
        TO ( _LTR ) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC ,
        KC_LCTL     , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RCTL ,
        KC_LSFT     , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , RALT_T ( KC_RGHT )
//                         ,        ,         ,       <|,>        ,         ,         ,
//      <1                 , <2     , <3      , <4     |, 4>      , 3>      , 2>      , 1>
                      ),
*/

};

// Copied from ../jetpacktuxedo/ (for LEDs)
// Code and comments edited to use different leds.

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    // Set up RGB effects on _only_ the first LED 
    rgblight_set_effect_range(1, 1); // Takes a range: 1st arg is start, 2nd how many
    // Purple
    rgblight_sethsv_noeeprom(210, 255, 20);
    // Set LED effects to breathing mode
    rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING + 2);

    // Init the first and last LEDs to a static color.
    setrgb(0, 0, 0, (LED_TYPE *)&led[0]); // Led[0] is led 0
    setrgb(0, 0, 0, (LED_TYPE *)&led[2]); // 2nd led
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
}

uint32_t layer_state_set_user(uint32_t state){
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;

    if (layer_state_cmp(state, _NSY)) { // symbols and numbers
      led1b = 255; // blue for symbols, like ink (writing)
      led0b = 255;
    }
    if (layer_state_cmp(state, _FUN)) { // F-keys, and layer toggles
      led1r = 255; // F-keys is red, because it can mean anything, "be careful"
      led0r = 255;
    } 
    if (layer_state_cmp(state, _MOV)) { // movement layer
      led1g = 255; // movement is green, "go forward"
      led0g = 255;
    }
    if (layer_state_cmp(state, _RAR)) { // weird layer
      led1b = 100; // some color for strange keys
      led1r = 100;
      led0r = 100;
      led0b = 100;
    }
    if (layer_state_cmp(state, _REV)) { // reverse hands layer
      led0g = 255; // green for nagivation left hand
      led1b = 255; // blue for symbols right hand
    }
    if (layer_state_cmp(state, _ACC)) { // Accented letters (Unicode input layer)
      led1b = 100; // With some blue, because it is also a symbol 
      led1g = 100;
      led0b = 100;
      led0g = 100;
    }
    if (layer_state_cmp(state, _DRA)) { // Unicode drawings and unusual things
      led0g = 200; // Bit of a white/yellowish color
      led0b = 50; //
      led0r = 250; //
      led1g = 200; //
      led1b = 50; //
      led1r = 250; //
    }
    if (layer_state_cmp(state, _QDN)) { // double Dvorak descramble, numbers/symbols 
      led0g = 155; // Orange only left led indicates descramble mode
      led0r = 255; //
      led1b = 255; //  Third led follows the layer being descrambled (_NSY) 
    }
    if (layer_state_cmp(state, _QDL)) { // double Dvorak descramble, letters
      led0g = 155; // Orange only left led indicates descramble mode
      led0r = 255; //
                   // Third led follows the layer being descrambled (_LTR)
      // It seems that this does not work, perhaps because internally the layer
      // is renamed layer 0 when activated as the base layer. To detect this
      // layer one could activate the _NSY / _QDN layer key.
    }

    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[2]); // Led 2
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
  return state;
}
