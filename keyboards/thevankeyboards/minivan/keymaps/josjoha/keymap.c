
/*
 * License (GPL):
  
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include QMK_KEYBOARD_H

// Layer switch TT(layer) tapping amount to make it toggle
//#define TAPPING_TOGGLE 2

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
     * - There are two layers that allow typing this layout when the computer
     *   is already set to Dvorak. One descrambles the letters, the other 
     *   some remaining symbols on the numbers and remaining symbols layer.
     *   On the _FUN layer are keys that switch between either. 
     *
     * */

// Notice this order in layer_state_set_user as well, regarding the led indicators.
// Defines the internal order of the layers. The normal base layer starts at 
// default 0.  The Dvorak descramble BASE _DDL needs to
// have a low order number, so that the other layers can be accessed on top of it.
// The rest of the order does not matter, but to keep the code easier the descramble
// layers are near the layer they descramble. F-keys is on top because it is the 
// layers hub, although that should not matter either.
// It seems that setting the 'default' layer is not needed. It is enough to merely toggle
// to either _LTR or _DDL, no need for DF(layer).
// The source lines order is as on the keyboard (_FUN top row). The order of the layers
// in the source file follows layer precedence order in reverse (0-11).

#define _LTR 0  // letters (Dvorak)
#define _NSY 2  // numbers and symbols
#define _FUN 11 // function keys, layer switcher, given highest order precedence just in case
#define _MOV 4  // movement arrows and mouse
#define _RAR 5  // strange keys never used
#define _REV 6  // Reversing: numbers right, navigation left (mirrored.)
#define _ACC 7  // Accented letters and unusual symbols
#define _DRA 9  // Accented letters and unusual symbols
#define _DDD 10 // Descramble version of _DRA
#define _DDA 8  // Descramble version of _ACC
#define _DDN 3  // Descramble version of _NSY
#define _DDL 1  // Descramble version of _LTR

bool descramble = 0 ; // boolean to remember if we are in descramble mode for 'escape'ing out of layers to the right base
bool shift_ison = 0 ; // keep track of the state of shift (Capslock is ignored). There may be more elegant code for this in
                      //   QMK (a function seems to do it?), but this is simple and keeps the issue isolated to this file.

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
    [CS_THDN] = 0x1f44e         //      ''              ''          "THDN"  for <thumb down>  👎 
};


// Macros, allowing the upper left button to switch to either _LTR base layer, or the _DDL descramble base layer.
// That way the whole board works the same, with the use of descramble or not.
// Descramble is set on/off in the _FUN layer. The word "base" is used to avoid "default," because the default
// layer system call DF()is not being used.
enum custom_keycodes {
    CTO_BASE = SAFE_RANGE, // 'C' for costum, "TO" for to, "BASE" for chosen base layer
    BASE_LTR,              // "BASE" for base layer, "_LTR" for that layer
    BASE_DDL,              //         ''             "_DDL" for that layer
    CUNI_ADIA,             // 'C' for costum' "UNI" for Unicode, 'A' for a, "DIA" for diaereses
};

// Activates only the major layer, either the normal or the descramble one
void activate_major_layer(int mode_descr) { 
    if ( mode_descr ) {
        layer_on ( _DDL ) ;
    } else { // normal mode
        layer_on ( _LTR ) ;
    }
}
// De-activates layers
void deactivate_other_layer(int mode_descr) {
    if ( mode_descr ) {
        //layer_off ( _LTR ) ; // maybe better not de-activate lowest default layer, it is covered up anyway
        layer_off ( _NSY ) ;
        layer_off ( _FUN ) ;
        layer_off ( _MOV ) ;
        layer_off ( _RAR ) ;
        layer_off ( _REV ) ;
        layer_off ( _ACC ) ;
        layer_off ( _DRA ) ;
        layer_off ( _DDD ) ;
        layer_off ( _DDA ) ;
        layer_off ( _DDN ) ;
        //layer_off ( _DDL ) ; // the descramble base layer
    } else { // normal mode
        //layer_off ( _LTR ) ; // normal base layer
        layer_off ( _NSY ) ;
        layer_off ( _FUN ) ;
        layer_off ( _MOV ) ;
        layer_off ( _RAR ) ;
        layer_off ( _REV ) ;
        layer_off ( _ACC ) ;
        layer_off ( _DRA ) ;
        layer_off ( _DDD ) ;
        layer_off ( _DDA ) ;
        layer_off ( _DDN ) ;
        layer_off ( _DDL ) ;
    }
}

// help user with leds
void indicate_scramble ( int mode_descr )
{
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
    // See also below under _FUN layer led
    if ( mode_descr ) { // descramble mode, 1
        led0r = 255; //  shine only right led, since _DDL is on the right furthest key
        led0g = 0; 
        led0b = 0; 
        led2r = 255;
        led2g = 255;
        led2b = 255;
    } else { // normal mode, 0
        led0r = 255; //  shine only left led, since _LTR is on the left furthest key
        led0g = 255;
        led0b = 255;
        led2r = 255;
        led2g = 0; 
        led2b = 0; 
    }
    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb(led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2
    rgblight_set();
}

// Process the user input, as far as special costumization within this source file is concerned.
// The special layer switching keys.
// The Unicode system to work with descramble.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Layer switching:
        // User wants to switch to normal input BASE key pointing 
        case BASE_LTR: // All upper/left buttons switch to _LTR
            if (record->event.pressed) {
                
            } else { // key up
                descramble = 0 ; // off  
                indicate_scramble ( descramble ) ; // Help user with indicator
       
            }
            break;           
        // User wants to switch to descramble BASE key pointing
        case BASE_DDL:// All upper/left buttons switch to _DDL 
            if (record->event.pressed) {
       
            } else { // key up
                descramble = 1 ;// on
                indicate_scramble ( descramble ) ; // Help user with indicator
       
            }
            break; 
        // User pressed upper/left button (escape from a layer to BASE layer)
        case CTO_BASE:
            if (record->event.pressed) { // key down
                activate_major_layer ( descramble ) ; // makes respective base layer active
                // set leds accordingly
                if ( descramble ) {
                    layer_state_set_user(_DDL);
                } else {
                    layer_state_set_user(_LTR);
                }
            } else { // key up
                deactivate_other_layer ( descramble ) ; // deactivates all else
            }
            break;
    }
    // Unicode input. We will keep track of shift by way of a variable shift_ison.
    //  Then when we get a Unicode character, we will assemble a string to send,
    //  depending on the setting of descramble, and shift.
    // User gave 'a' with diacreses key
    switch (keycode) {
        case CUNI_ADIA:
            if (record->event.pressed) { // key down
    	    //char leadin[] = "u" ;
    	    if ( shift_ison ) {
    		SEND_STRING ( SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT)) ;
    	        if ( descramble ) {
    	             SEND_STRING ( "f" ) ; // pre-scrambled
    	        } else {
    	             SEND_STRING ( "u" ) ;
    	        }
    		SEND_STRING ( SS_UP(X_LSHIFT) SS_UP(X_LCTRL) ) ;
    	        if ( descramble ) {
                        SEND_STRING ( "00d4 " ) ; // pre-scrambled
    	        } else {
                        SEND_STRING ( "00e4 " ) ; // test
    	        }
    	    } else {
                    SEND_STRING ( "ccc" ) ; // test
    	    }
            } else { // key up
            }
            break;
        // Record state of shift
        // ... left shift
        case KC_LSFT:
        // ... right shift
        case KC_RSFT:
            if (record->event.pressed) { // key down
                shift_ison = 1 ; // shift depressed
            } else { // key up
                shift_ison = 0 ; // shift released
            }
          break;
     }
     return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 
    /* Layer _LTR: Dvorak, normal BASE layer and 'default' layer
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
// -*-                                   <|>                                       // Access from all other layers -*!- there
// Esc      '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL    Bksp     //" ((syntax highlighting fix))
// Tab+LCtl aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS      -_
// LSft     ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSft
// ------------------------------------------------------------------
// Left+LAlt Del+_ACC _MOV  Enter+_NSY| Space _NSY _FUN    Right+_ACC             // _XYZ are layer switches
//                                   <|>                                  
//           hold     hold  hold      |       hold toggl   hold                   // Type of layer switch
// <1        <2       <3    <4        | 4>    3>   2>      1>                     // Keys by number
//
//
//      <pink2            , <pinky  , <ring   , <middl , <indx, <ind|, indx>, inde>, midd>, ring>, pink>, pink2>  ,
//      -*!-              ,         ,         ,        ,      ,    <|,>     ,      ,      ,      ,      ,         ,
        KC_ESC            , KC_QUOT , KC_COMM , KC_DOT , KC_P , KC_Y , KC_F , KC_G , KC_C , KC_R , KC_L , KC_BSPC ,
        LCTL_T ( KC_TAB ) , KC_A    , KC_O    , KC_E   , KC_U , KC_I , KC_D , KC_H , KC_T , KC_N , KC_S , KC_MINS ,
        KC_LSFT           , KC_SCLN , KC_Q    , KC_J   , KC_K , KC_X , KC_B , KC_M , KC_W , KC_V , KC_Z , KC_RSFT ,
//      ---------------------------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , LT ( _ACC , KC_DEL ) , MO ( _MOV ) , LT ( _NSY , KC_ENT ) , KC_SPC , MO ( _NSY ) , TO ( _FUN ) , LT ( _ACC , KC_RIGHT )
//                         ,                      ,             ,                    <|,>       ,             ,              ,
//      <1                 , <2                   , <3          , <4                  |, 4>     , 3>          , 2>           , 1>
                      ),

        /**/

    /* Layers _DDL, _DDN, _DDA and _DDD: Descramble basic layers if the computer itself is
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
     *          _ACC layer:        |
     *          <just semi-random character strings>
     *
     *          _DRA layer:        |
     *          <just semi-random character strings>
     *
     *          To solve this results in the strange layout given below.
     *          The result is a Qwerty layout, however it will not be ideal
     *          for Qwerty typers because the symbols are not arranged that
     *          well if typed with the intent of it being Qwerty.
     */ 


    /* Layer _DDL: Descrambled _LTR layer for a computer already set to Dvorak (see above).
     *           It is a copy of _LTR, with moved around stuff, and points to _DDN instead
     *           of _NSY, because that too has some descrambled symbols. The rest is the same.
     *
     */

    [ _DDL ] = LAYOUT (

//                                        | Right hand
// <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>   // Keys by finger
//                                       <|>                              -*-      // Access from _FUN -*- there
// Esc      qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP    Bksp
// Tab+LCtl aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:      '"
// LSft     zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSft
// -------------------------------------------------------------------
// Left+LAlt Del+_ACC _MOV  Enter+_DDN| Space  _DDN _FUN    Right+_ACC           // _XYZ are layer switches
//                                   <|>
//           hold     hold  hold      |        hold toggl   hold                 // Type of layer switch
// <1        <2       <3    <4        | 4>     3>   2>      1>                   // Keys by number
//                                                   
//
//      <pink2            , <pink, <ring, <midd, <indx, <ind|, indx>, inde>, middle> , ring>  , pink>   , pink2>  ,
//      -*-               ,      ,      ,      ,      ,    <|,>     ,      ,         ,        ,         , -!-     ,
        KC_ESC            , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I    , KC_O   , KC_P    , KC_BSPC ,
        LCTL_T ( KC_TAB ) , KC_A , KC_S , KC_D , KC_F , KC_G , KC_H , KC_J , KC_K    , KC_L   , KC_SCLN , KC_QUOT ,
        KC_LSFT           , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_N , KC_M , KC_COMM , KC_DOT , KC_SLSH , KC_RSFT ,
//      ---------------------------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , LT ( _DDA , KC_DEL ) , MO ( _MOV ) , LT ( _DDN , KC_ENT ) , KC_SPC , MO ( _DDN ) , TO ( _FUN ) , LT ( _DDA , KC_RIGHT )
//                         ,                      ,             ,                    <|,>       ,             ,              ,
//      <1                 , <2                   , <3          , <4                  |, 4>     , 3>          , 2>           , 1>
                      ),

        /**/

    /* Layer _NSY: Numbers and symbols.
     *          Off hand Number input (-.Bksp ent (shft)tab).
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _NSY ] = LAYOUT (

// <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//        -*-                          <|>                                       // Layer access from _FUN -*-
// BASE   !     @     #     $     %     | ^     &     *     (     )        Bspc
// -+LCtl 1!    2@    3#    4$    5%    | \|    =+    /?    [{    ]}    `~+RCtl
// .+LSft 0)    9(    8*    7&    6^    | |     +     ?     {     }      `+RSft  // QMK limitation prevents ~
// -------------------------------------------------------------
// Left+LAlt Del   Sft(tab) ___  | tab   ___   Ent   Right+RAlt
//                          -*- <|>      -*-                                     // Layer access from _LTR -*-
// <1        <2    <3       <4   | 4>    3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring , <middl  , <index , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,       ,         ,        ,       <|,>        ,         ,         ,         ,         ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT , KC_HASH , KC_DLR , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_MINS ) , KC_1    , KC_2  , KC_3    , KC_4   , KC_5    , KC_BSLS , KC_EQL  , KC_SLSH , KC_LBRC , KC_RBRC , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_DOT )  , KC_0    , KC_9  , KC_8    , KC_7   , KC_6    , KC_PIPE , KC_PLUS , KC_QUES , KC_LCBR , KC_RCBR , RSFT_T ( KC_TILD ) ,  
//      -----------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , S ( KC_TAB ) , _______ , KC_TAB , _______ , KC_ENT , RALT_T ( KC_RGHT )
//                         ,        ,              , -*-   <|,>       , -*-     ,        ,
//      <1                 , <2     , <3           , <4     |, 4>     , 3>      , 2>     , 1>
                      ),

        /**/


    /* Layer _DDN: Descrambled _NSY layer for a computer already set to Dvorak (see just above).
     *
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _DDN ] = LAYOUT (

// <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                     <|>                        -*-            // Layer access from _FUN -*-
// BASE   !     @     #     $     %     | ^     &     *     (     )        Bspc
// -+LCtl 1!    2@    3#    4$    5%    | \|    ]}    [{    -_    =+    `~+RCtl
// .+LSft 0)    9(    8*    7&    6^    | |     }     {     _     +      `+RSft  // QMK limitation prevents ~
// ------------------------------------------------------------
// Left+LAlt Del   Sft(tab) ___  | tab   ___   Ent   Right+RAlt
//                          -*- <|>      -*-                                     // Layer access from _DDL -*-
// <1        <2    <3       <4   | 4>    3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring , <middl  , <index , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,       ,         ,        ,       <|,>        ,         ,         ,         , -*-     ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT , KC_HASH , KC_DLR , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_MINS ) , KC_1    , KC_2  , KC_3    , KC_4   , KC_5    , KC_BSLS , KC_RBRC , KC_LBRC , KC_MINS , KC_EQL  , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_DOT )  , KC_0    , KC_9  , KC_8    , KC_7   , KC_6    , KC_PIPE , KC_RCBR , KC_LCBR , KC_UNDS , KC_PLUS , RSFT_T ( KC_TILD ) ,  
//      -----------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , S ( KC_TAB ) , _______ , KC_TAB , _______ , KC_ENT , RALT_T ( KC_RGHT )
//                         ,        ,              , -*-   <|,>       , -*-     ,        ,
//      <1                 , <2     , <3           , <4     |, 4>     , 3>      , 2>     , 1>
                      ),

        /**/


    /* Layer _MOV: Movement layer: mouse and hands on navigation
     *          Also delete/backspace, to navigate and delete together.
     */

    [ _MOV ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                   -*-              <|>
// BASE  WLft  WDn   WUp   WRht  xxx   | Btn3  Home  PgUp  PgDn  End   Bksp
// LCtl  MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
// LSft  Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSft
// -------------------------------------------------------------
// Left+LAlt Del   ___   Sft(tab) | tab   xxx   xxx   Right+RAlt
//                 -*-           <|>
// <1        <2    <3    <4       | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                  ,         ,         , -*-     ,         ,       <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE    , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , XXXXXXX , KC_BTN3 , KC_HOME , KC_PGUP , KC_PGDN , KC_END  , KC_BSPC ,
        KC_LCTL     , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , KC_BTN1 , KC_BTN1 , KC_LEFT , KC_UP   , KC_DOWN , KC_RGHT , KC_RCTL ,
        KC_LSFT     , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN2 , XXXXXXX , KC_BTN2 , KC_ACL0 , KC_ACL1 , KC_ACL2 , XXXXXXX , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL  , _______ , S ( KC_TAB ) , KC_TAB  , XXXXXXX , XXXXXXX , RALT_T ( KC_RGHT )
//                         ,         , -*-     ,            <|,>        ,         ,         ,
//      <1                 , <2      , <3      , <4          |, 4>      , 3>      , 2>      , 1>
                      ),

        /**/


    /* Layer _RAR: Dump for various unused keys.
     *          - Media keys sortof follow navigation block logic, on those keycap colors.
     *          - Ü precedes the Unicode input modes, as indicator key and tester
     *            This block follows the numbers lower row keycap colors.
     *          - p precedes the power key (to test where it is if forgotten)
     *            This block is on top row, where the "powerful" F-keys are on _FUN layer.
     *            POWER is on the button where _FUN itself is, associating it with 'red'.
     *          - Capslock/Numlock have vague logic of being on the other side of normal
     *          - Insert sortof has to do with Capslock/Numlock (insert characters...)
     *          - GUI: They kindof belong here with the weird stuff, but if they are modifiers
     *            they need a layer that is on a hold key. Since these buttons seem common,
     *            and accented characters are also common, and there is a hold layer for it,
     *            and room, they are there.
     *          - APP (whatever it is) fakes being next to right GUI (though other layer).
     *          - The traditional obsolete button like ScrLk/PrtSc are also included, in
     *            case some program needs them suddenly.
     */

    [ _RAR ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                         -*-        <|>
// BASE  P     Power Wake  Sleep xxx   | xxx   Play  Next  Prev  Stop  NumL // P(ower) indicator
// Tab   xxx   xxx   Pause ScrLk PrtSc | xxx   xxx   Vol+  Vol-  Mute  CapL
// Ü     uLNX  uBSD  uOSX  uWIN  uWNC  | xxx   xxx   xxx   xxx   xxx Insert // Ü(nicode) tester
// ----------------------------------------------
// xxx   xxx   xxx   xxx  | xxx   xxx   xxx   App
//                       <|>     
// <1    <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2        , <pinky           , <ring            , <middl           , <index           , <indx2           |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                    ,                  ,                  ,                  , -*-              ,                 <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE      , S ( KC_P )       , KC_PWR           , KC_WAKE          , KC_SLEP          , XXXXXXX           , XXXXXXX , KC_MPLY , KC_MNXT , KC_MPRV , KC_MSTP , KC_NLCK ,
        KC_TAB        , XXXXXXX          , XXXXXXX          , KC_PAUS          , KC_SLCK          , KC_PSCR           , XXXXXXX , XXXXXXX , KC_VOLU , KC_VOLD , KC_MUTE , KC_CAPS ,
        X ( CUU_DIA ) , UNICODE_MODE_LNX , UNICODE_MODE_BSD , UNICODE_MODE_OSX , UNICODE_MODE_WIN , UNICODE_MODE_WINC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_INS  ,
//      ----------------------------------------------------------------------------
        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_APP  , XXXXXXX
//              ,         ,         ,       <|,>        ,         ,         ,
//      <1      , <2      , <3      , <4     |, 4>      , 3>      , 2>      , 1>
                      ),

        /**/


    /* Layer _REV: Reversing hands layer numbers and navigation, for one hand on keyboard use.
     *          Generally follows numbers layer.
     */

    [ _REV ] = LAYOUT (

// <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                -*-  <|>
// BASE   End   PgDn  PgUp  Home  xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
// -+LCtl Left  Down  Up    Right xxx   | 5%    4$    3#    2@    1!    RCtl
// .+LSft xxx   xxx   xxx   xxx   xxx   | 6^    7&    8*    9(    0)    RSft
// ----------------------------------------------------------
// Left+LAlt Del   Sft(Tab) xxx  | Tab  xxx   Ent   Right+Alt
//                              <|>
// <1        <2    <3       <4   | 4>   3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                         ,         ,         ,         ,         , -*-   <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE           , KC_END  , KC_PGDN , KC_PGUP , KC_HOME , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC ,
        LCTL_T ( KC_MINS ) , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , XXXXXXX , KC_5    , KC_4    , KC_3    , KC_2    , KC_1    , KC_RCTL ,
        LSFT_T ( KC_DOT )  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_RSFT ,
//      -------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , S ( KC_TAB ) , XXXXXXX , KC_TAB  , XXXXXXX , KC_ENT  , RALT_T ( KC_RGHT )
//                         ,        ,              ,       <|,>        ,         ,         ,
//      <1                 , <2     , <3           , <4     |, 4>      , 3>      , 2>      , 1>
                      ),

        /**/


    /* Layer _ACC: Accented and other unusual characters. It seems this would
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
     *       See _RAR about why GUI is here.
     */ 

    [ _ACC ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                    <|>-*-
// BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    xxx   çÇ    øØ    åÅ    Bspc
// LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
// LSft  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSft
// --------------------------------------------------
// LAlt+Left ___   LGUI  Ent  | Spc   RGUI  xxx   ___
//           -*-             <|>                  -*-
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky                   , <ring                    , <middl                   , <index                   , <indx2                  |, indx2>                   , index>                   , middl>                   , ring>                    , pinky>                   , pink2>  ,
//                  ,                          ,                          ,                          ,                          ,                        <|,>-*-                      ,                          ,                          ,                          ,                          ,         ,
        CTO_BASE    , XP ( CAL_ACU , CAU_ACU ) , XP ( COL_ACU , COU_ACU ) , XP ( CEL_ACU , CEU_ACU ) , XP ( CUL_ACU , CUU_ACU ) , XP ( CIL_ACU , CIU_ACU ) , XP ( CYL_ACU , CYU_ACU ) , XXXXXXX                  , XP ( CCL_CDL , CCU_CDL ) , XP ( COL_STK , COU_STK ) , XP ( CAL_RNG , CAU_RNG ) , KC_BSPC ,
        KC_LCTL     , XP ( CAL_DIA , CAU_DIA ) , XP ( COL_DIA , COU_DIA ) , XP ( CEL_DIA , CEU_DIA ) , XP ( CUL_DIA , CUU_DIA ) , XP ( CIL_DIA , CIU_DIA ) , XP ( CYL_DIA , CYU_DIA ) , XP ( COEL_ , COEU_ )     , XP ( CAEL_ , CAEU_ )     , XP ( CNL_TLD , CNU_TLD ) , X ( CSL_SHP )            , KC_RCTL ,
      //KC_LCTL     , CUNI_ADIA                , XP ( COL_DIA , COU_DIA ) , XP ( CEL_DIA , CEU_DIA ) , XP ( CUL_DIA , CUU_DIA ) , XP ( CIL_DIA , CIU_DIA ) , XP ( CYL_DIA , CYU_DIA ) , XP ( COEL_ , COEU_ )     , XP ( CAEL_ , CAEU_ )     , XP ( CNL_TLD , CNU_TLD ) , X ( CSL_SHP )            , KC_RCTL ,

        KC_LSFT     , XP ( CAL_GRA , CAU_GRA ) , XP ( COL_GRA , COU_GRA ) , XP ( CEL_GRA , CEU_GRA ) , XP ( CUL_GRA , CUU_GRA ) , XP ( CIL_GRA , CIU_GRA ) , XP ( CIL_CAR , CIU_CAR ) , XP ( CUL_CAR , CUU_CAR ) , XP ( CEL_CAR , CEU_CAR ) , XP ( COL_CAR , COU_CAR ) , XP ( CAL_CAR , CAU_CAR ) , KC_RSFT ,
//      ------------------------------------------------------------------------------------
        KC_LALT , _______ , KC_LGUI , KC_ENT , KC_SPC , KC_RGUI , XXXXXXX , _______ 
//                , -*-     ,         ,      <|,>       ,         ,         , -*-
//     <1       ,<2       ,<3       ,<4     |, 4>     , 3>      , 2>      , 1>
                      ),

        /**/


    /* Layer _DDA: Descrambled _ACC layer for a computer already set to Dvorak (see just above).
     *
     */

    [ _DDA ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                    <|>-*-
// BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    xxx   çÇ    øØ    åÅ    Bspc
// LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
// LSft  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSft
// --------------------------------------------------
// LAlt+Left ___   LGUI  Ent  | Spc   RGUI  xxx   ___
//           -*-             <|>                  -*-
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky                   , <ring                    , <middl                   , <index                   , <indx2                  |, indx2>                   , index>                   , middl>                   , ring>                    , pinky>                   , pink2>  ,
//                  ,                          ,                          ,                          ,                          ,                        <|,>-*-                      ,                          ,                          ,                          ,                          ,         ,
        CTO_BASE    , XP ( CAL_ACU , CAU_ACU ) , XP ( COL_ACU , COU_ACU ) , XP ( CEL_ACU , CEU_ACU ) , XP ( CUL_ACU , CUU_ACU ) , XP ( CIL_ACU , CIU_ACU ) , XP ( CYL_ACU , CYU_ACU ) , XXXXXXX                  , XP ( CCL_CDL , CCU_CDL ) , XP ( COL_STK , COU_STK ) , XP ( CAL_RNG , CAU_RNG ) , KC_BSPC ,
     // KC_LCTL     , XP ( CAL_DIA , CAU_DIA ) , XP ( COL_DIA , COU_DIA ) , XP ( CEL_DIA , CEU_DIA ) , XP ( CUL_DIA , CUU_DIA ) , XP ( CIL_DIA , CIU_DIA ) , XP ( CYL_DIA , CYU_DIA ) , XP ( COEL_ , COEU_ )     , XP ( CAEL_ , CAEU_ )     , XP ( CNL_TLD , CNU_TLD ) , X ( CSL_SHP )            , KC_RCTL ,
        KC_LCTL     , CUNI_ADIA                , XP ( COL_DIA , COU_DIA ) , XP ( CEL_DIA , CEU_DIA ) , XP ( CUL_DIA , CUU_DIA ) , XP ( CIL_DIA , CIU_DIA ) , XP ( CYL_DIA , CYU_DIA ) , XP ( COEL_ , COEU_ )     , XP ( CAEL_ , CAEU_ )     , XP ( CNL_TLD , CNU_TLD ) , X ( CSL_SHP )            , KC_RCTL ,

        KC_LSFT     , XP ( CAL_GRA , CAU_GRA ) , XP ( COL_GRA , COU_GRA ) , XP ( CEL_GRA , CEU_GRA ) , XP ( CUL_GRA , CUU_GRA ) , XP ( CIL_GRA , CIU_GRA ) , XP ( CIL_CAR , CIU_CAR ) , XP ( CUL_CAR , CUU_CAR ) , XP ( CEL_CAR , CEU_CAR ) , XP ( COL_CAR , COU_CAR ) , XP ( CAL_CAR , CAU_CAR ) , KC_RSFT ,
//      ------------------------------------------------------------------------------------
        KC_LALT , _______ , KC_LGUI , KC_ENT , KC_SPC , KC_RGUI , XXXXXXX , _______ 
//                , -*-     ,         ,      <|,>       ,         ,         , -*-
//     <1       ,<2       ,<3       ,<4     |, 4>     , 3>      , 2>      , 1>
                      ),

        /**/

    /* Layer _DRA: Drawings, like various Unicode symbols, and whatever else.
     *          The emoticons follow the "logic" of the movement layer.
     *          The symbols ¡ and ¿ are placed on top of ! and ?.
     *   
     */

    [ _DRA ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                    <|>      -*-
// BASE  ¡     xxx   xxx   xxx   xxx   | xxx  🙂😃   👍    👎    ⍨🙁   Bspc
// LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   ¿     xxx   xxx   RCtl
// LSft  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSft
// ---------------------------------------------------------
// LAlt+Left xxx   xxx   Ent  | Spc   xxx   xxx   RAlt+Right
//                           <|>
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky        , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>                   , middl>        , ring>         , pinky>                   , pink2>  ,
//                  ,               ,         ,         ,         ,       <|,>        , -*-                      ,               ,               ,                          ,         ,
        CTO_BASE    , X ( CEX_INV ) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XP ( CS_SMIL , CS_YAYS ) , X ( CS_THUP ) , X ( CS_THDN ) , XP ( CS_SQIG , CS_SAD_ ) , KC_BSPC ,
        KC_LCTL     , XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX                  , X ( CQU_INV ) , XXXXXXX       , XXXXXXX                  , KC_RCTL ,
        KC_LSFT     , XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX                  , XXXXXXX       , XXXXXXX       , XXXXXXX                  , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , XXXXXXX , XXXXXXX , KC_ENT  , KC_SPC  , XXXXXXX , XXXXXXX , RALT_T ( KC_RGHT )
//                         ,         ,         ,       <|,>        ,         ,         ,
//      <1                 , <2      , <3      , <4     |, 4>      , 3>      , 2>      , 1>
                      ),

        /**/


    /* Layer _DDD: Drawings, like various Unicode symbols, and whatever else.
     *          The emoticons follow the "logic" of the movement layer.
     *          The symbols ¡ and ¿ are placed on top of ! and ?.
     *   
     */

    [ _DDD ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                    <|>      -*-
// BASE  ¡     xxx   xxx   xxx   xxx   | xxx  🙂😃   👍    👎    ⍨🙁   Bspc
// LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   ¿     xxx   xxx   RCtl
// LSft  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSft
// ---------------------------------------------------------
// LAlt+Left xxx   xxx   Ent  | Spc   xxx   xxx   RAlt+Right
//                           <|>
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky        , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>                   , middl>        , ring>         , pinky>                   , pink2>  ,
//                  ,               ,         ,         ,         ,       <|,>        , -*-                      ,               ,               ,                          ,         ,
        CTO_BASE    , X ( CEX_INV ) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XP ( CS_SMIL , CS_YAYS ) , X ( CS_THUP ) , X ( CS_THDN ) , XP ( CS_SQIG , CS_SAD_ ) , KC_BSPC ,
        KC_LCTL     , XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX                  , X ( CQU_INV ) , XXXXXXX       , XXXXXXX                  , KC_RCTL ,
        KC_LSFT     , XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX                  , XXXXXXX       , XXXXXXX       , XXXXXXX                  , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , XXXXXXX , XXXXXXX , KC_ENT  , KC_SPC  , XXXXXXX , XXXXXXX , RALT_T ( KC_RGHT )
//                         ,         ,         ,       <|,>        ,         ,         ,
//      <1                 , <2      , <3      , <4     |, 4>      , 3>      , 2>      , 1>
                      ),

        /**/


    /* Layer _FUN: Function keys, most on the right side, some combo modifiers control/alt/shift
     *          Toward any layer by toggle.
     *          Completes output normal / descramble on Dvorak remapping computer. This affects
     *          XXX
     *          how CTO_BASE operates on the other layers, which is all it does. De-scramble is
     *          already usable by toggling to the _DDL layer.
     */

    [ _FUN ] = LAYOUT (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
// toggl toggl toggl toggl toggl toggl | toggl toggl             toggl toggl      // Type of layer switch
//             -*-                    <|>                                         // Access -*- _FUN
// BASE  _NSY  _FUN  _MOV  _RAR  _REV  | _ACC  _DRA  _DDD  DDA   _DDN  _DDL
// LCtl  F11   F12   F13   F14   F15   | F5    F4    F3    F2    F1    RCtl
// LSft  F20   F19   F18   F17   F16   | F6    F7    F8    F9    F10   RSft
// ----------------------------------------------------------------
// LAlt  LCtl&    LCtl&    !LTR   | !DDL       LSft&    BASE   RAlt                            // ! sets base layer
//       LSft+xxx LAlt+xxx        |            LAlt+xxx                         // (Continued, multi-modifiers)
//                               <|>                    -*-                                   // Acces -*- _LTR
//                         normal | descramble                                       // Output mode (full)
// <1    <2       <3       <4     | 4>         3>       2>     1>  
//
//
//      <pink2      , <pinky      , <ring       , <middl      , <index      , <indx2     |, indx2>      , index>      , middl>      , ring>       , pinky>      , pink2>      ,
//                  ,             , -*-         ,             ,             ,           <|,>            ,             ,             ,             ,             ,             ,
        CTO_BASE    , TO ( _NSY ) , TO ( _FUN ) , TO ( _MOV ) , TO ( _RAR ) , TO ( _REV ) , TO ( _ACC ) , TO ( _DRA ) , TO ( _DDD ) , TO ( _DDA ) , TO ( _DDN ) , TO ( _DDL ) ,
        KC_LCTL     , KC_F11      , KC_F12      , KC_F13      , KC_F14      , KC_F15      , KC_F5       , KC_F4       , KC_F3       , KC_F2       , KC_F1       , KC_RCTL     ,
        KC_LSFT     , KC_F20      , KC_F19      , KC_F18      , KC_F17      , KC_F16      , KC_F6       , KC_F7       , KC_F8       , KC_F9       , KC_F10      , KC_RSFT     ,
//      -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT , MT ( MOD_LCTL | MOD_LSFT, XXXXXXX ) , MT ( MOD_LCTL | MOD_LALT , XXXXXXX ) , BASE_LTR , BASE_DDL , MT ( MOD_LSFT | MOD_LALT, XXXXXXX )  , CTO_BASE , KC_RALT
//              ,                                     ,                                      ,        <|,>         ,                                      , -*-      ,
//      <1      , <2                                  , <3                                   , <4      |, 4>       , 3>                                   , 2>       , 1>
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
// LSft  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSft
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
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
    short color_ddl = 28 ;


    // The order should be the reverse of the #defines of layer number of the layers on top
    // because higher layer number is higher priority if activated
    /* _LTR 0 _DDL 1 _NSY 2 _DDN 3 _MOV 4 _RAR 5 _REV 6 _ACC 7 _DDA 8 _DRA 9 _DDD 10 _FUN 11 */
    if (layer_state_cmp(state, _FUN)) { // F-keys, and layer toggles
        //led2r = 255; // F-keys is red, warning color because it can mean anything
        //led0r = 255;
	
	// When it enters this mode, this gets triggered, indicating the current state
	// of the (de)scramble.
        if ( descramble ) { // descramble mode, 1
            led0r = 255; //  shine only right led, since _DDL is on the right furthest key
            led0g = 0; 
            led0b = 0; 
            led2r = 255;
            led2g = 255;
            led2b = 255;
        } else { // normal mode, 0
            led0r = 255; //  shine only left led, since _LTR is on the left furthest key
            led0g = 255;
            led0b = 255;
            led2r = 255;
            led2g = 0; 
            led2b = 0; 
        }
        rgblight_sethsv_noeeprom(HSV_RED);
    } 
    //--- (pair)
    else if (layer_state_cmp(state, _DDD)) {  // double Dvorak descramble, Unicode drawings
        led0r = 255; //  first led follows the layer being descrambled: _DRA
        led0g = 128; // 
        led2r = color_ddl; // Same as DDL, to which it belongs.
        led2g = color_ddl; // 
        led2b = color_ddl; // 
        rgblight_sethsv_noeeprom(HSV_GOLDENROD); 
    }
    if (layer_state_cmp(state, _DRA)) { // Unicode drawings and unusual things
        led0r = 255; // gold red
        led0g = 128; // 
        led2r = 255; //
        led2g = 128; //
        rgblight_sethsv_noeeprom( HSV_GOLDENROD ); 
    }
    //--- (pair)
    else if (layer_state_cmp(state, _DDA)) {  // double Dvorak descramble, Accented letters
        led0g = 150; //  first led follows the layer being descrambled: _ACC
        led0b = 100;
        led2r = color_ddl; // Same as DDL, to which it belongs.
        led2g = color_ddl; // 
        led2b = color_ddl; // 
        rgblight_sethsv_noeeprom(HSV_TURQUOISE); 
    }
    else if (layer_state_cmp(state, _ACC)) { // Accented letters (Unicode input layer)
        led0g = 150; // With some blue, because it is also a symbol 
        led0b = 100;
        led2g = 150;
        led2b = 100;
        rgblight_sethsv_noeeprom(HSV_TURQUOISE); // cyan
    }
    //---
    else if (layer_state_cmp(state, _REV)) { // reverse hands layer
        led0g = 255; // green for nagivation left hand
        led2b = 255; // blue for symbols right hand
        rgblight_sethsv_noeeprom(60, 20, 100); // yellow (low saturation)
    }
    //---
    else if (layer_state_cmp(state, _RAR)) { // weird layer
        led0r = 100; // purple
        led0b = 100;
        led2r = 100;
        led2b = 100;
        rgblight_sethsv_noeeprom(HSV_PURPLE); // purple
    }
    //---
    else if (layer_state_cmp(state, _MOV)) { // movement layer
        led0g = 255;// movement is green, "go forward"
        led2g = 255; 
        rgblight_sethsv_noeeprom(HSV_GREEN);
    }
    //--- (pair)
    else if (layer_state_cmp(state, _DDN)) { // double Dvorak descramble, numbers/symbols 
        led0b = 255; //  first led follows the layer being descrambled: _NSY 
        led2r = color_ddl; // Same as DDL, to which it belongs.
        led2g = color_ddl; // 
        led2b = color_ddl; // 
        rgblight_sethsv_noeeprom(HSV_BLUE); 
    }
    else if (layer_state_cmp(state, _NSY)) { // symbols and numbers
        led0b = 255; // blue for symbols, like ink (writing)
        led2b = 255;
        rgblight_sethsv_noeeprom(HSV_BLUE);
    }
    //--- (pair)
    // Alternate BASE layer (descramble)
    else if (layer_state_cmp(state, _DDL)) { // double Dvorak descramble, letters
        led2r = color_ddl; // A bit of a white not too bright color on rightaaaa111oooonnnooo
        led2g = color_ddl; // 
        led2b = color_ddl; // 
    }
    // Default layer (generally), normal BASE layer
    else if (layer_state_cmp(state, _LTR)) { // symbols and numbers
        led0r = 28; // A bit of a weak white color on left 
        led0g = 28; // 
        led0b = 28; // 
    }
    //---

    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb(led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
  return state;
}


