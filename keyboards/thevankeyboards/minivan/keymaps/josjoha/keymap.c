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

 * Authors: This QMK keymap file is a combination of the default
 * keymap, led code original copied/edited from ../jetpacktuxedo, some
 * copy/paste from QMK documentation code examples (etc).
 * Remainder: (C) 2019,2020 by Jos Boersema
 *
 */


    /* Dvorak keymap for Minivan default layout (44 keys)
     *
     * - Basic layers are: letters, numbers and remaining symbols, movement.
     * - 'Escape' always goes back to default layer.
     * - All other layers are through the _FUN layer on toggle.
     * - A lot of the modifiers, Del/Esc, alt-arrows repeat on layers.
     * - Layer switching by thumbs, hold keys except _FUN.
     * - Rather than AltGr or Compose (which for some reason did not work here
     *   at the moment), RAlt position switches to a special symbols layer.
     * - There are multiple layers that allow typing this layout when the computer
     *   is already set to Dvorak. Switchin input modes is on the _FUN layer.
     *
     * */


/* Todo:
 *       (unknown)
 */

// ----------------------------- Configuration: -------------------------------------


        /*                            Qwerty
         *
         * Here you can define if you want a pure Dvorak keyboard, also with the ability
         * to connect seamlessly with a computer which is alreaedy set to Dvorak ('descramble
         * mode'), or if you want the default keymap to be in Qwerty, and the 'descramble' keymaps
         * to be in normal Dvorak.
         * If you choose Qwerty and still want to change something, you can open qwerty_dvorak.c 
         * to edit the letters and numbers/symbols keymaps there, because those will be dropped
         * in place instead of those programmed in this file (below).
         *
         */
//#define QWERTY_DVORAK // Comment out to have Dvorak on default, and 'descramble Dvorak' on alternate.
                        // Uncomment to have Qwerty on default, and Dvorak on alternate.


        /*                           Startup layer
         *
         * Here you can define which of the two BASE layer is active when powering up the keyboard.
         * For starting up in 'descramble' for non-Linux, fix the variable in the code by hand to _HALF_.
         */
//#define STARTUP_ALTERNATE // For QWERTY_DVORAK *is* defined: comment out is startup in Qwerty, #defined is
                          //                                                              startup in Dvorak
                          // For QWERTY_DVORAK *not* defined: comment out is startup in normal Dvorak,
                          //                          #defined is startup in 'descramble' Dvorak Linux mode.


        /*       Navigation cluster configuration
         * 
         * Here you can easily define what navigation type layout you like.
         * There are two basic settings: - Arrows in a triangle, or in a row.
         * - Arrows on left or right hand (mouse on the other). 
         * Left/right hand setting affects if the less usable center column is left 
         * or right on that hand.
         * If you are uncommenting both below settings, you probably do not have
         * to edit anything. If you only use one, you may want to swap the edge 
         * columns by hand.
         *
         * By default the arrows are in a row, and on the right hand.
         * The alternative layout is configured for arrows in a triangle, on the left hand.
         *
         * Uncomment below line to use a "WASD" type layout.
         * Comment out if you prefer a flat type layout, with arrows in a row.
         */
#define ARROWS_TRIANGLE // implies mouse is also similarly in a triangle.
         /* Uncomment below line to put the arrows on the left, comment out to have arrows right. */
#define ARROWS_LEFT // implies mouse is right


        /*     GUI left/right 
         *
         * Uncomment below line to have LGUI (also called OS or Win key, etc) where RGUI is, 
         * and RGUI where LGUI is. This does not affect placement, only what that key is.
         */
#define SWITCH_GUIS // Set this if you want LGUI on the BASE layer rather than RGUI, and so consistently on all layers.


        /*      Left Shift layer to ...
         *
         * Uncomment one of the below lines, determining where L-shift tap-toggles to on the 
         * BASE layer. 
         */
//#define LSHIFT_LAYER_RAR // Be warned and don't hold it against me if you accidentally hit 'Power' at the wrong moment.
//#define LSHIFT_LAYER_MOV // Handy to have navigation on a toggle. 
                         // _MOV is the least dangerous layer to accidentally activate.
//#define LSHIFT_LAYER_DRA // _DRA is also the least easy to access layer normally, on pinky which is sortof wrong.
                         // This would help alleviate it.
//#define LSHIFT_LAYER_ACC // If typing a lot of these in a row
#define LSHIFT_LAYER_PAD // Easier Access to numpad (for default shortcuts in blender for example).


        /*      Sacrificing functionality when compiled hex file is too large
         *
         * You can cut some parts of the functionality, if device space is too small.
         * The overall QMK code sometimes changes, which causes the firmware to change
         * size. This happened once at time of this writing, hence it became necessary
         * to remove something to make it fit. The QMK code became 4 bytes larger,
         * despite nothing changing in this keymap. 
         *
         * Default (and how documentation represents the keymap): 
         *                 - no up/down arrow in either 'descramble' or normal
         *                 - dashes in all maps
         */
#define space_cut_descr_arrow_ud // Uncomment to remove up/down arrows in the 'descramble mode' Unicode layer.
                                 // This saves a couple of dozen bytes.
#define space_cut_normal_arrow_ud // Uncomment to remove up/down arrows in the 'normal mode' Unicode layers.
                                  // This saves only a few bytes, but harmonizes the keymap if 'descramble' arrows cut.
//#define space_cut_descr_dashes // Uncomment to remove dashed lines in the 'descramble mode' Unicode layer.
                               // This saves a couple of dozen bytes.

// Below here no more comfortable configuration options.....
// --------------------------------------^---------------------------------------

  /* Overview of the code
   *
   * The two compile options imply that the Qwerty-Dvorak variant re-defines
   * the two letter and the two number/symbol layers, while not compiling the
   * special Linux Unicode 'descramble' layers. The Qwerty-Dvorak letters number/
   * symbol layers are located in qwerty_dvorak.c. There is only one #define
   * dealing with this. The unicode macros needed for the special Linux Unicode
   * are also not compiled in the Qwerty-Dvorak version.
   *
   * The Unicode is in unicode_macros.c/h.
   */


// Set up user GUI choice:
#ifndef SWITCH_GUIS
    #define KC__XGUI KC_LGUI
    #define KC__YGUI KC_RGUI
#endif
#ifdef SWITCH_GUIS
    #define KC__XGUI KC_RGUI
    #define KC__YGUI KC_LGUI
#endif


// Some things from broader QMK code:
#include QMK_KEYBOARD_H
#define RGBLIGHT_SLEEP // QMK docs: "If defined, the RGB lighting will be switched off when the host goes to sleep"
extern keymap_config_t keymap_config;
// Layer switch TT(layer) tapping amount to make it toggle
#define TAPPING_TERM_HOLTAP 225 // 175 ms proved unreliable, 225 ms seems ok (personal preference)

// Notice this order in layer_state_set_user as well, regarding the led indicators.
// Below #defines the internal order of the layers.
// The layers beginning with DD are the 'Dvorak Descramble' layers (marked *)
enum {
    _LTR,  //  BASE layer (normal). letters (Dvorak)
    _DDL,  //* BASE layer. Descramble version of _LTR
    _NSY,  //  numbers and symbols
    _DDN,  //* Descramble version of _NSY
    _MOV,  //  movement arrows and mouse
    _RAR,  //  strange keys never used, Unicode config
    _PAD,  //  Numbers pad (these are different versions of the same symbols)
    _ACC,  //  Accented letters 
    _DDA,  //* Descramble version of _ACC
    _DRA,  //  Unusual symbols and whatever else
    _DDD,  //* Descramble version of _DRA
    _FUN,  //  function keys, layer switcher, given highest order precedence just in case
} ;
// The normal and Dvorak descramble BASE _DDL needs to have a low order
// number, so that the other layers can be accessed on top of it.  The rest
// of the order does not matter, but to keep the code easier the descramble
// layers are near the layer they descramble. F-keys is on top because it
// is the layers hub, although that should not matter either.
// It seems that setting the 'default' layer is not needed, no need for DF(layer).

// Descramble mode defines and variable.
enum {
    _NORMAL_, // BASE layer is _LTR
    _HALF_,   // BASE layer is _DDL, jumps to 'normal' Unicode maps
    _FULL_,   // BASE layer is _DDL, jumps to special Linux 'descramble' Unicode maps
};
#ifndef STARTUP_ALTERNATE
 short descramble = _NORMAL_; // to remember if we are in descramble mode for 'escape'ing out of layers to the right base
#endif
#ifdef STARTUP_ALTERNATE
 short descramble = _FULL_; 
#endif
                      // There are three modes: 0 for everything normal, 1 for descramble for letters and number/symbols,
                      // .. but with the normal unicode layers, and 2 for all in descramble mode, where the Unicode
                      // .. coding is for a Linux system (shift-control-U + HEX input).
                      // The 1 mode is added, for systems where the Unicode input might work the same whether or not
                      // .. the computer is already set to Dvorak. (This is untested as far as the result on  those
                      // .. systems XXX.)

//* Shift detection
bool shift_ison = 0; // keep track of the state of shift (Capslock is ignored). There may be more elegant code for this in
                     //   QMK (a function seems to do it?), but this is simple and keeps the issue isolated to this file.
#define TRUE 1
#define FALSE 0
bool _fun_stay = FALSE; // for making _FUN layer not return to BASE after pressing f-key
bool leds_on = TRUE; // toggle leds on/off
bool isolate_trigger = FALSE; // detects if _FUN layer shift was pressed and no other key 


/* This file contains mostly the Unicode and special macros.
   It contains the function: process_record_user(...)
   It has been isolated because the source file got long.
 */
#include "./unicode_macros.c"


// pre-existing function
void keyboard_post_init_user (void) {
  #ifdef RGBLIGHT_ENABLE
    // Set up RGB effects on _only_ the first LED 
    rgblight_set_effect_range (1, 1); // Takes a range: 1st arg is start, 2nd how many
    // Purple
    rgblight_sethsv_noeeprom (210, 255, 20);
    // Set LED effects to breathing mode
    rgblight_mode_noeeprom (RGBLIGHT_EFFECT_BREATHING + 2);

    // Init the first and last LEDs to a static color.
    setrgb (0, 0, 0, (LED_TYPE *)&led[0]); // Led[0] is led 0
    setrgb (0, 0, 0, (LED_TYPE *)&led[2]); // 2nd led
    rgblight_set ();
  #endif //RGBLIGHT_ENABLE
}


// De-activates all other layers than the one given. Does not activate the one given.
void deactivate_all_but (int layer) {
   //if (_LTR != layer) { layer_off ( _LTR ) ; } // maybe better never to de-activate lowest base and default layer, it is covered up anyway
   if (_NSY != layer) { layer_off ( _NSY ) ; }
   if (_FUN != layer) { layer_off ( _FUN ) ; } 
   if (_MOV != layer) { layer_off ( _MOV ) ; } 
   if (_RAR != layer) { layer_off ( _RAR ) ; } 
   if (_PAD != layer) { layer_off ( _PAD ) ; } 
   if (_ACC != layer) { layer_off ( _ACC ) ; } 
   if (_DRA != layer) { layer_off ( _DRA ) ; } 
   if (_DDD != layer) { layer_off ( _DDD ) ; } 
   if (_DDA != layer) { layer_off ( _DDA ) ; } 
   if (_DDN != layer) { layer_off ( _DDN ) ; } 
   if (_DDL != layer) { layer_off ( _DDL ) ; } 
}


// Activate the given layer
void activate_this_layer (int layer) {
    layer_on (layer) ;
}


// help user with leds
void indicate_scramble (void)
{
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
    // See also below under _FUN layer led
    if (_NORMAL_ == descramble) { // normal mode, 0 (100% normal)
        led0r = 255; //  shine white left led
        led0g = 255;
        led0b = 255;
        rgblight_sethsv_noeeprom (HSV_RED); 
        led2r = 255;
        led2g = 0; 
        led2b = 0; 
    } else if (_HALF_ == descramble) { // descramble mode, 1 (normal unicode)
        led0r = 255; //  left/right is red
        led0g = 0; 
        led0b = 0; 
        rgblight_sethsv_noeeprom (HSV_WHITE); //  shine white middle led (still breathes)
        led2r = 255;
        led2g = 0;
        led2b = 0;
    } else if (_FULL_ == descramble) { // descramble mode, 1 (normal unicode)
        led0r = 255;  //  shine white right led
        led0g = 0;
        led0b = 0;
        rgblight_sethsv_noeeprom (HSV_RED); 
        led2r = 255;
        led2g = 255; 
        led2b = 255; 
    }
    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb(led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2
    rgblight_set ();
  #endif //RGBLIGHT_ENABLE
}


// Set the leds to 'black' color
void leds_show_off (void) {
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;

    if (leds_on) { // left/right white
        led0r = 255; 
        led0g = 255; 
        led0b = 255; 
        led2r = 255; 
        led2g = 255; 
        led2b = 255; 
    } else { // left/right dark, after this they should remain at this color
        led0r = 0; 
        led0g = 0; 
        led0b = 0; 
        led2r = 0; 
        led2g = 0; 
        led2b = 0; 
    }
    setrgb (led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb (led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2
    rgblight_set ();

  #endif //RGBLIGHT_ENABLE
    return;
}


// pre-existing function
// Only deals with setting led colors.
uint32_t layer_state_set_user (uint32_t state) {
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
    short color_ddl = 28 ;

    if (!leds_on) return state; // leds are off
        

    // The order should be the reverse of the #defines of layer number of the layers on top
    // because higher layer number is higher priority if activated
    /* _LTR 0 _DDL 1 _NSY 2 _DDN 3 _MOV 4 _RAR 5 _PAD 6 _ACC 7 _DDA 8 _DRA 9 _DDD 10 _FUN 11 */
    if (layer_state_cmp (state, _FUN)) { // F-keys, and layer toggles
        indicate_scramble (); // this function already does it all
        return state; // 
    } 
    //--- (pair)
    else if (layer_state_cmp (state, _DDD)) {  // double Dvorak descramble, Unicode drawings
        led0r = 255; //  first led follows the layer being descrambled: _DRA
        led0g = 128; // 
        led2r = color_ddl; // Same as DDL, to which it belongs.
        led2g = color_ddl; // 
        led2b = color_ddl; // 
        rgblight_sethsv_noeeprom (HSV_GOLDENROD); 
    }
    else if (layer_state_cmp (state, _DRA)) { // Unicode drawings and unusual things
        led0r = 255; // gold red
        led0g = 128; // 
        led2r = 255; //
        led2g = 128; //
        rgblight_sethsv_noeeprom( HSV_GOLDENROD ); 
    }
    //--- (pair)
    else if (layer_state_cmp (state, _DDA)) {  // double Dvorak descramble, Accented letters
        led0g = 150; //  first led follows the layer being descrambled: _ACC
        led0b = 100;
        led2r = color_ddl; // Same as DDL, to which it belongs.
        led2g = color_ddl; // 
        led2b = color_ddl; // 
        rgblight_sethsv_noeeprom(HSV_TURQUOISE); 
    }
    else if (layer_state_cmp (state, _ACC)) { // Accented letters (Unicode input layer)
        led0g = 150; // With some blue, because it is also a symbol 
        led0b = 100;
        led2g = 150;
        led2b = 100;
        rgblight_sethsv_noeeprom (HSV_TURQUOISE); // cyan
    }
    //---
    else if (layer_state_cmp (state, _PAD)) { // reverse hands layer
        led0g = 255; // green for nagivation left hand
        led2b = 255; // blue for symbols right hand
        rgblight_sethsv_noeeprom (60, 20, 100); // yellow (low saturation)
    }
    //---
    else if (layer_state_cmp (state, _RAR)) { // weird layer
        led0r = 100; // purple
        led0b = 100;
        led2r = 100;
        led2b = 100;
        rgblight_sethsv_noeeprom (HSV_PURPLE); // purple
    }
    //---
    else if (layer_state_cmp (state, _MOV)) { // movement layer
        led0g = 255;// movement is green, "go forward"
        led2g = 255; 
        rgblight_sethsv_noeeprom(HSV_GREEN);
    }
    //--- (pair)
    else if (layer_state_cmp (state, _DDN)) { // double Dvorak descramble, numbers/symbols 
        led0b = 255; //  first led follows the layer being descrambled: _NSY 
        led2r = color_ddl; // Same as DDL, to which it belongs.
        led2g = color_ddl; // 
        led2b = color_ddl; // 
        rgblight_sethsv_noeeprom (HSV_BLUE); 
    }
    else if (layer_state_cmp (state, _NSY)) { // symbols and numbers
        led0b = 255; // blue for symbols, like ink (writing)
        led2b = 255;
        rgblight_sethsv_noeeprom (HSV_BLUE);
    }
    //--- (pair)
    // Alternate BASE layer (descramble)
    else if (layer_state_cmp (state, _DDL)) { // double Dvorak descramble, letters
        led2r = color_ddl; // A bit of a white not too bright color on rightaaaa111oooonnnooo
        led2g = color_ddl; // 
        led2b = color_ddl; // 
    }
    // Default layer (generally), normal BASE layer
    else if (layer_state_cmp (state, _LTR)) { // symbols and numbers
        led0r = 28; // A bit of a weak white color on left 
        led0g = 28; // 
        led0b = 28; // 
    }
    //---

    setrgb (led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb (led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2
    rgblight_set ();
  #endif //RGBLIGHT_ENABLE
  return state;
}

// -------------------------------- layouts -------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* This file contains the Qwerty + Dvorak keymaps.
 */
#ifdef QWERTY_DVORAK
        #include "./qwerty_dvorak.c"
#endif
#ifndef QWERTY_DVORAK // Cut out all the letters and numbers/symbols maps (4).
       // .... v .... v .... v .... v .... v .... v .... v .... v .... v .... v 

    /* Layer _LTR: Dvorak, normal BASE layer and 'default' layer
     *
     * - Dual use keys create a delay in the key (tap/hold keys), therefore
     *   space is not dual use (most ued key), neither is hyphen.
     */ 

    [ _LTR ] = LAYOUT (

/*
     Layer _LTR (LeTteRs, standard Dvorak)
                                             | Right hand
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>    // Keys by finger
     -o-                                    <|>                                    ... // -o- BASE access
     Esc       '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
     Tab+LCtl  aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
     LSht+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN   // _FUN _MOV tap
     -------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY(_DRA)  Enter+_MOV| Space  _NSY(_DRA) LGUI    Right;_RAR  // _XYZ is to layer
               hold     hold₍₂₎     hold      |        hold₍₂₎    hold    hold       // Layer switch type
                        ^---------------------+--------^                              // both hold = _DRA
     <1        <2       <3    <4              | 4>     3>   2>      1>                  // Keys by number

*/
//
//      <pink2            , <pinky  , <ring   , <middl , <indx, <ind|, indx>, inde>, midd>, ring>, pink>, pink2>        ,
//      -*!-              ,         ,         ,        ,      ,    <|,>     ,      ,      ,      ,      ,               ,
        KC_ESC            , KC_QUOT , KC_COMM , KC_DOT , KC_P , KC_Y , KC_F , KC_G , KC_C , KC_R , KC_L , KC_BSPC       ,
        LCTL_T ( KC_TAB ) , KC_A    , KC_O    , KC_E   , KC_U , KC_I , KC_D , KC_H , KC_T , KC_N , KC_S , KC_MINS       ,
        CHOLTAP_LSHFT     , KC_SCLN , KC_Q    , KC_J   , KC_K , KC_X , KC_B , KC_M , KC_W , KC_V , KC_Z , CHOLTAP_RSHFT ,
//      -----------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , CHOLTAP_ACCE , DUO_HOLD , LT ( _MOV , KC_ENT ) , KC_SPC , DUO_HOLD , KC__YGUI , CHOLTAP_LAYR
//                         ,              ,          ,                    <|,>       ,          ,          ,
//      <1                 , <2           , <3       , <4                  |, 4>     , 3>       , 2>       , 1>
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

/*
     Layer _DDL (Dvorak descramble mode for letters)
                                             | Right hand
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>    // Keys by finger
     -o-                                    <|>                                    ... // -o- BASE access
     Esc       '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
     Tab+LCtl  aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
     LSht+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN   // _FUN _MOV tap
     -------------------------------------------------------------------------------
     Left+LAlt Del;_DDA _DDN(DRAW)  Enter+_MOV| Space  _DDN(DRAW) LGUI    Right;_RAR  // _XYZ is to layer
               hold     hold₍₂₎     hold      |        hold₍₂₎    hold    hold       // Layer switch type
                        ^---------------------+--------^                              // both hold = DRAW
     <1        <2       <3          <4        | 4>     3>         2>      1>            // Keys by number


     _DDL input results in the same as _LTR with computer side Dvorak remapping. Only shown what changes:

              '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL                 // row 4, result
                    oO    eE    uU    iI    | dD    hH    tT    nN    sS   -_            // row 3, result
              ;:    qQ    jJ    kK    xX    | bB          wW    vV    zZ                 // row 2, result

     (Keys for 'aA', '\|' and 'mM' are the same in Dvorak and Qwerty.)

 */
//                                                   
//
//      <pink2            , <pink, <ring, <midd, <indx, <ind|, indx>, inde>, middle> , ring>  , pink>   , pink2>        ,
//      -*-               ,      ,      ,      ,      ,    <|,>     ,      ,         ,        ,         , -!-           ,
        KC_ESC            , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I    , KC_O   , KC_P    , KC_BSPC       ,
        LCTL_T ( KC_TAB ) , KC_A , KC_S , KC_D , KC_F , KC_G , KC_H , KC_J , KC_K    , KC_L   , KC_SCLN , KC_QUOT       ,
        CHOLTAP_LSHFT     , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_N , KC_M , KC_COMM , KC_DOT , KC_SLSH , CHOLTAP_RSHFT ,
//      -----------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , CHOLTAP_ACCE , DUO_HOLD , LT ( _MOV , KC_ENT ) , KC_SPC , DUO_HOLD , KC__YGUI , CHOLTAP_LAYR
//                         ,              ,          ,                    <|,>       ,          ,          ,
//      <1                 , <2           , <3       , <4                  |, 4>     , 3>       , 2>       , 1>
                      ),

        /**/

    /* Layer _NSY: Numbers and symbols.
     *          Off hand Number input (-.Bksp ent (shft)tab).
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _NSY ] = LAYOUT (

/*
     Layer _NSY (Numbers and SYmbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSft   [{    ]}    /?    \|    =+    | +     |     ?     {     }   `+RSft // limitation prevents ~
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  
*/
//
//
//      <pink2             , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,         ,         ,         ,       <|,>        ,         ,         ,         ,         ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_TAB )  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_MINS ) , KC_LBRC , KC_RBRC , KC_SLSH , KC_BSLS , KC_EQL  , KC_PLUS , KC_PIPE , KC_QUES , KC_LCBR , KC_RCBR , RSFT_T ( KC_TILD ) ,  
//      -------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , DUO_HOLD , KC_ENT , KC_DOT , DUO_HOLD , KC__YGUI , RALT_T ( KC_RGHT )
//                         ,        , -*-      ,      <|,>       , -*-      ,          ,
//      <1                 , <2     , <3       , <4    |, 4>     , 3>       , 2>       , 1>
                      ),

        /**/


    /* Layer _DDN: Descrambled _NSY layer for a computer already set to Dvorak (see just above).
     *
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _DDN ] = LAYOUT (

/*
     Layer _DDN (Dvorak descramble mode for numbers/symbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   -_    =+    [{    \|    ]}    | }     |     {     _     +   `+RSht            // row 2, raw
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  

     _DDN input results in the same as _NSY with computer side Dvorak remapping. Only shown what changes:

              [{    ]}    /?           =+   |   +         ?     {     }                  // row 2, result
 */
//
//      <pink2             , <pinky  , <ring  , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,        ,         ,         ,       <|,>        ,         ,         ,         , -*-     ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT  , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_TAB )  , KC_1    , KC_2   , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_MINS ) , KC_MINS , KC_EQL , KC_LBRC , KC_BSLS , KC_RBRC , KC_RCBR , KC_PIPE , KC_LCBR , KC_UNDS , KC_PLUS , RSFT_T ( KC_TILD ) ,  
//  -----------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , DUO_HOLD , KC_ENT , KC_DOT , DUO_HOLD , KC__YGUI , RALT_T ( KC_RGHT )
//                         ,        , -*-      ,      <|,>       , -*-      ,          ,
//      <1                 , <2     , <3       , <4    |, 4>     , 3>       , 2>       , 1>
                      ),

        /**/

#endif // QWERTY_DVORAK .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ 


    /* Layer _MOV: Movement layer: mouse and hands on navigation
     *          Also delete/backspace, to navigate and delete together.
     */

    [ _MOV ] = LAYOUT (

/*
     triangle layout:
     Layer _MOV (MOVement, mouse movement on right hand)
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                        -*-              <|>                                           //(toggle) on _FUN
     BASE   PgDn  Up    PgUp  Home  Btn3  | xxx   WhDn  MsUp  WhU   WhLft Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht RCtl
     LSft*- xxx   Acc2  Acc1  Acc0  Btn2  | xxx   Btn2  Btn3  Btn4  Btn5  RSft         //(toggle) on BASE
     ---------------------------------------------------------
     LAlt Del   Ent   ___ | PgUp  PgDn  LGUI  RAlt
                      -*-<|>                                                             //(hold) on BASE
     <1   <2    <3    <4  | 4>    3>    2>    1>  

     flat layout (mouse movement on left hand):
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                        -*-              <|>                                           //(toggle) on _FUN
     BASE   WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn  Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSft*- Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSft         //(toggle) on BASE
     ---------------------------------------------------------
     LAlt Del   Ent   ___ | PgUp  PgDn  LGUI  RAlt
                      -*-<|>                                                             //(hold) on BASE
     <1   <2    <3    <4  | 4>    3>    2>    1>  
 */

         /* Inner default navigation/mouse layout. 11 means row 1, column 1, etc.
          * Configured for arrows on the right, mouse on the left (BTN* on the left side, that is).
          */
#ifndef ARROWS_TRIANGLE
    #define NAVI_11 KC_BTN3 // NAVI for 'navigation cluster', 11 for row 1, column 1, etc.
    #define                 NAVI_12 KC_PGUP
    #define                                 NAVI_13 KC_HOME
    #define                                                 NAVI_14 KC_END
    #define                                                                NAVI_15 KC_PGDN
    #define NAVI_21 KC_BTN1
    #define                 NAVI_22 KC_LEFT
    #define                                 NAVI_23 KC_UP
    #define                                                 NAVI_24 KC_DOWN
    #define                                                                NAVI_25 KC_RIGHT
    #define NAVI_31 KC_BTN2
    #define                 NAVI_32 KC_ACL0
    #define                                 NAVI_33 KC_ACL1
    #define                                                 NAVI_34 KC_ACL2
    #define                                                                NAVI_35 XXXXXXX
    //--------------------------------------------------------------------------
    // Configured for left handed mouse, with xxx,BTN* on the right most column.
    #define MOUS_11 KC_WH_L  // MOUS for mouse, etc.
    #define                 MOUS_12 KC_WH_D
    #define                                 MOUS_13 KC_WH_U
    #define                                                 MOUS_14 KC_WH_R
    #define                                                                MOUS_15 XXXXXXX
    #define MOUS_21 KC_MS_L
    #define                 MOUS_22 KC_MS_D
    #define                                 MOUS_23 KC_MS_U
    #define                                                 MOUS_24 KC_MS_R
    #define                                                                MOUS_25 KC_BTN1
    #define MOUS_31 KC_BTN5
    #define                 MOUS_32 KC_BTN4
    #define                                 MOUS_33 KC_BTN3
    #define                                                 MOUS_34 KC_BTN2
    #define                                                                MOUS_35 XXXXXXX
#endif
// Alternative navigation/mouse layout: arrows in triangle, and left hand on the left 'wasd' location.
// If you want these arrows on the right hand, you may want to edit this, to put right most column left, etc.
#ifdef ARROWS_TRIANGLE
    #define NAVI_11 KC_PGDN
    #define                 NAVI_12 KC_UP   
    #define                                 NAVI_13 KC_PGUP
    #define                                                 NAVI_14 KC_HOME
    #define                                                                 NAVI_15 KC_BTN3
    #define NAVI_21 KC_LEFT
    #define                 NAVI_22 KC_DOWN
    #define                                 NAVI_23 KC_RIGHT
    #define                                                  NAVI_24 KC_END
    #define                                                                 NAVI_25 KC_BTN1
    #define NAVI_31 XXXXXXX
    #define                 NAVI_32 KC_ACL2
    #define                                 NAVI_33 KC_ACL1
    #define                                                  NAVI_34 KC_ACL0
    #define                                                                 NAVI_35 KC_BTN2
    //--------------------------------------------------------------------------
    // If switching hands to put mouse left, same as for navigation side: switch outer columns by editing here.
    #define MOUS_11 XXXXXXX
    #define                 MOUS_12 KC_WH_D
    #define                                 MOUS_13 KC_MS_U
    #define                                                 MOUS_14 KC_WH_U
    #define                                                                MOUS_15 KC_WH_L
    #define MOUS_21 KC_BTN1
    #define                 MOUS_22 KC_MS_L
    #define                                 MOUS_23 KC_MS_D
    #define                                                 MOUS_24 KC_MS_R
    #define                                                                MOUS_25 KC_WH_R
    #define MOUS_31 XXXXXXX
    #define                 MOUS_32 KC_BTN2
    #define                                 MOUS_33 KC_BTN3
    #define                                                 MOUS_34 KC_BTN4
    #define                                                                MOUS_35 KC_BTN5
#endif

// Default left/right layout, meaning arrows right and mouse left.
#ifndef ARROWS_LEFT
    #define LEFT_AA MOUS_11
    #define LEFT_AB MOUS_12
    #define LEFT_AC MOUS_13
    #define LEFT_AD MOUS_14
    #define LEFT_AE MOUS_15
    #define LEFT_BA MOUS_21
    #define LEFT_BB MOUS_22
    #define LEFT_BC MOUS_23
    #define LEFT_BD MOUS_24
    #define LEFT_BE MOUS_25
    #define LEFT_CA MOUS_31
    #define LEFT_CB MOUS_32
    #define LEFT_CC MOUS_33
    #define LEFT_CD MOUS_34
    #define LEFT_CE MOUS_35
    #define RGHT_AA NAVI_11
    #define RGHT_AB NAVI_12
    #define RGHT_AC NAVI_13
    #define RGHT_AD NAVI_14
    #define RGHT_AE NAVI_15
    #define RGHT_BA NAVI_21
    #define RGHT_BB NAVI_22
    #define RGHT_BC NAVI_23
    #define RGHT_BD NAVI_24
    #define RGHT_BE NAVI_25
    #define RGHT_CA NAVI_31
    #define RGHT_CB NAVI_32
    #define RGHT_CC NAVI_33
    #define RGHT_CD NAVI_34
    #define RGHT_CE NAVI_35
#endif

#ifdef ARROWS_LEFT
    #define LEFT_AA NAVI_11
    #define LEFT_AB NAVI_12
    #define LEFT_AC NAVI_13
    #define LEFT_AD NAVI_14
    #define LEFT_AE NAVI_15
    #define LEFT_BA NAVI_21
    #define LEFT_BB NAVI_22
    #define LEFT_BC NAVI_23
    #define LEFT_BD NAVI_24
    #define LEFT_BE NAVI_25
    #define LEFT_CA NAVI_31
    #define LEFT_CB NAVI_32
    #define LEFT_CC NAVI_33
    #define LEFT_CD NAVI_34
    #define LEFT_CE NAVI_35
    #define RGHT_AA MOUS_11
    #define RGHT_AB MOUS_12
    #define RGHT_AC MOUS_13
    #define RGHT_AD MOUS_14
    #define RGHT_AE MOUS_15
    #define RGHT_BA MOUS_21
    #define RGHT_BB MOUS_22
    #define RGHT_BC MOUS_23
    #define RGHT_BD MOUS_24
    #define RGHT_BE MOUS_25
    #define RGHT_CA MOUS_31
    #define RGHT_CB MOUS_32
    #define RGHT_CC MOUS_33
    #define RGHT_CD MOUS_34
    #define RGHT_CE MOUS_35
#endif

//      <pink2   , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//               ,         ,         , -*-     ,         ,       <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE , LEFT_AA , LEFT_AB , LEFT_AC , LEFT_AD , LEFT_AE , RGHT_AA , RGHT_AB , RGHT_AC , RGHT_AD , RGHT_AE , KC_BSPC ,
        KC_LCTL  , LEFT_BA , LEFT_BB , LEFT_BC , LEFT_BD , LEFT_BE , RGHT_BA , RGHT_BB , RGHT_BC , RGHT_BD , RGHT_BE , KC_RCTL ,
        KC_LSFT  , LEFT_CA , LEFT_CB , LEFT_CC , LEFT_CD , LEFT_CE , RGHT_CA , RGHT_CB , RGHT_CC , RGHT_CD , RGHT_CE , KC_RSFT ,
//      ---------------------------------------------------------------------------------------------------
        KC_LALT , KC_DEL  , KC_ENT , _______ , KC_PGUP , KC_PGDN , KC__YGUI , KC_RALT
//              ,         ,        , -*-   <|,>        ,         ,          ,
//      <1      , <2      , <3     , <4     |, 4>      , 3>      , 2>       , 1>
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

/*
     _RAR (RARely used keys) (Only through _FUN layer)
    
     <pink2<pinky <ring <middl <indexx<indx2| indx2>index>middl>ring> pinky> pink2>
                               -*-         <|>                                         //(toggle) on _FUN
     BASE  xxx    xxx   xxx    xxx    xxx   | xxx   Play  Next  Prev  Stop   NumL
     P     Power• Wake• Sleep• Pause• ScrLk | PrtSc xxx   Vol+  Vol-  Mute   CapL     // • requires Shift
     Ü     uLNX   uBSD  uOSX   uWIN   uWNC  | xxx   xxx   xxx   xxx   Insert  APP     // Ü(nicode) tester
     ------------------------------------------------
     MLed  SLeds RGUI  xxx  | RSft(•) xxx   LGUI  ___                    // Middle-led, Side-leds: on/off
                           <|>                    -*-                                   // (Hold) on BASE
     <1    <2    <3    <4   | 4>      3>    2>    1>  
 */
//
//
//      <pink2        , <pinky           , <ring            , <middl           , <index           , <indx2           |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                    ,                  ,                  ,                  , -*-              ,                 <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE      , XXXXXXX          , XXXXXXX          , XXXXXXX          , XXXXXXX          , XXXXXXX           , XXXXXXX , KC_MPLY , KC_MNXT , KC_MPRV , KC_MSTP , KC_NLCK ,
        S ( KC_P )    , C_KC_PWR         , C_KC_WAKE        , C_KC_SLEP        , C_KC_PAUS        , KC_SLCK           , KC_PSCR , XXXXXXX , KC_VOLU , KC_VOLD , KC_MUTE , KC_CAPS ,
        X ( CUU_DIA ) , UNICODE_MODE_LNX , UNICODE_MODE_BSD , UNICODE_MODE_OSX , UNICODE_MODE_WIN , UNICODE_MODE_WINC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_INS  , KC_APP  ,
//      -------------------------------------------------------------------------------
        RGB_TOG , LEDS_ON , KC__XGUI , XXXXXXX , KC_RSFT , XXXXXXX , KC__YGUI , _______
//              ,         ,          ,       <|,>        ,         ,          ,
//      <1      , <2      , <3       , <4     |, 4>      , 3>      , 2>       , 1>
                      ),

        /**/


    /* Layer _PAD: Numbers pad, for numbers pad version of symbols (used in shortcuts in Blender).
     *             Number pad navigation will be more or less useless.
     */

    [ _PAD ] = LAYOUT (

/*
     Layer _PAD Numbers Pad (special symbol versions; regular '1' is not the same as this numpad '1', etc)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                      -*-  <|>                                         //(toggle) on _FUN
     BASE     xxx   xxx   .DEL  4LEFT 2DOWN | 8UP   6RGHT *     xxx   xxx   Bspc
     LCtl     1END  2DOWN 3PGDN 4LEFT 5     | 6RGHT 7HOME 8UP   9PGUP 0INS     -
     LSft     xxx   xxx   /     xxx   =     | +     3PGDN 1END  7HOME 9PGUP RSft
     -*-------------------------------------------------                               //(toggle) on BASE
     LAlt     Del   Tab   ENT  |  NUML  xxx   LGUI  RAlt
                              <|>

 */

//
//      <pink2   , <pinky  , <ring   , <middl      , <index  , <indx2     |, indx2>     , index>  , middl>         , ring>   , pinky>  , pink2>      ,
//               ,         ,         ,             ,         , -*-       <|,>           ,         ,                ,         ,         ,             ,
        CTO_BASE , XXXXXXX , XXXXXXX , KC_DOT      , KC_KP_4 , KC_KP_2     , KC_KP_8    , KC_KP_6 , KC_KP_ASTERISK , XXXXXXX , XXXXXXX , KC_BSPC     ,
        KC_LCTL  , KC_KP_1 , KC_KP_2 , KC_KP_3     , KC_KP_4 , KC_KP_5     , KC_KP_6    , KC_KP_7 , KC_KP_8        , KC_KP_9 , KC_KP_0 , KC_KP_MINUS ,
        KC_LSFT  , XXXXXXX , XXXXXXX , KC_KP_SLASH , XXXXXXX , KC_KP_EQUAL , KC_KP_PLUS , KC_KP_3 , KC_KP_1        , KC_KP_7 , KC_KP_9 , KC_RSFT     ,
//      ------------------------------------------------------------------------------------
        KC_LALT , KC_DEL , KC_TAB , KC_KP_ENTER , KC_NUMLOCK , XXXXXXX , KC__YGUI , KC_RALT
//              ,        ,        ,           <|,>           ,         ,          ,
//      <1      , <2     , <3     , <4         |, 4>         , 3>      , 2>       , 1>
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

/*
     Layer _ACC (ACCented characters, see _RAR layer for input modes)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>-*-                                         //(toggle) on _FUN
     BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bspc 
     Tab   äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     ---------------------------------------------
     LAlt ___   RGUI  Ent  | Spc   xxx   LGUI  xxx
          -*-             <|>                                                            //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  
 */
//
//      <pink2      , <pinky                   , <ring                    , <middl                   , <index                   , <indx2                  |, indx2>                   , index>                   , middl>                   , ring>                    , pinky>                   , pink2>  ,
//                  ,                          ,                          ,                          ,                          ,                        <|,>-*-                      ,                          ,                          ,                          ,                          ,         ,
        CTO_BASE    , XP ( CAL_ACU , CAU_ACU ) , XP ( COL_ACU , COU_ACU ) , XP ( CEL_ACU , CEU_ACU ) , XP ( CUL_ACU , CUU_ACU ) , XP ( CIL_ACU , CIU_ACU ) , XP ( CYL_ACU , CYU_ACU ) , XP ( CIJL_BI , CIJU_BI ) , XP ( CCL_CDL , CCU_CDL ) , XP ( COL_STK , COU_STK ) , XP ( CAL_RNG , CAU_RNG ) , KC_BSPC ,
        KC_TAB      , XP ( CAL_DIA , CAU_DIA ) , XP ( COL_DIA , COU_DIA ) , XP ( CEL_DIA , CEU_DIA ) , XP ( CUL_DIA , CUU_DIA ) , XP ( CIL_DIA , CIU_DIA ) , XP ( CYL_DIA , CYU_DIA ) , XP ( COEL_BI , COEU_BI ) , XP ( CAEL_BI , CAEU_BI ) , XP ( CNL_TLD , CNU_TLD ) , X ( CSL_SHP )            , KC_RCTL ,
        KC_LSFT     , XP ( CAL_GRA , CAU_GRA ) , XP ( COL_GRA , COU_GRA ) , XP ( CEL_GRA , CEU_GRA ) , XP ( CUL_GRA , CUU_GRA ) , XP ( CIL_GRA , CIU_GRA ) , XP ( CIL_CAR , CIU_CAR ) , XP ( CUL_CAR , CUU_CAR ) , XP ( CEL_CAR , CEU_CAR ) , XP ( COL_CAR , COU_CAR ) , XP ( CAL_CAR , CAU_CAR ) , KC_RSFT ,
//      ----------------------------------------------------------------------------
        KC_LALT , _______ , KC__XGUI , KC_ENT , KC_SPC , XXXXXXX , KC__YGUI , XXXXXXX 
//              , -*-     ,          ,      <|,>       ,         ,          , 
//      <1      , <2      , <3       , <4    |, 4>     , 3>      , 2>       , 1>
                      ),

        /**/


// These special Unicode layers for 'descramble' are not use in Qwerty compile version.
#ifndef QWERTY_DVORAK  // :   :   v   :   :   v   :   :   v   :   :   v   :   :   v   

    /* Layer _DDA: Descrambled _ACC layer for a computer already set to Dvorak (see just above).
     *
     */

    [ _DDA ] = LAYOUT (

/*
     Layer _ACC (ACCented characters, see _RAR layer for input modes)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>-*-                                         //(toggle) on _FUN
     BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bspc 
     LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     ---------------------------------------------
     LAlt ___   RGUI  Ent  | Spc   xxx   LGUI  xxx
          -*-             <|>                                                            //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  
 */
//
//      <pink2   , <pinky   , <ring    , <middl   , <index   , <indx2  |, indx2>   , index>   , middl>   , ring>    , pinky>   , pink2>  ,
//               ,          ,          ,          ,          ,        <|,>-*-      ,          ,          ,          ,          ,         ,
        CTO_BASE , UN_A_ACU , UN_O_ACU , UN_E_ACU , UN_U_ACU , UN_I_ACU , UN_Y_ACU , UN_IJ_BI , UN_C_CDL , UN_O_STK , UN_A_RNG , KC_BSPC ,
        KC_LCTL  , UN_A_DIA , UN_O_DIA , UN_E_DIA , UN_U_DIA , UN_I_DIA , UN_Y_DIA , UN_OE_BI , UN_AE_BI , UN_N_TLD , UN_S_SHP , KC_RCTL ,
        KC_LSFT  , UN_A_GRA , UN_O_GRA , UN_E_GRA , UN_U_GRA , UN_I_GRA , UN_I_CAR , UN_U_CAR , UN_E_CAR , UN_O_CAR , UN_A_CAR , KC_RSFT ,
//      ----------------------------------------------------------------------------
        KC_LALT , _______ , KC__XGUI , KC_ENT , KC_SPC , XXXXXXX , KC__YGUI , XXXXXXX 
//              , -*-     ,          ,      <|,>       ,         ,          ,
//      <1      , <2      , <3       , <4    |, 4>     , 3>      , 2>       , 1>
                      ),

#endif // QWERTY_DVORAK   :   :   ^   :   :   ^   :   :   ^   :   :   ^   :   :   ^   

        /**/

    /* Layer _DRA: Drawings, like various Unicode symbols, and whatever else.
     *          The emoticons follow the "logic" of the movement layer.
     *          The symbols ¡ and ¿ are placed on top of ! and ?.
     *   
     */

    [ _DRA ] = LAYOUT (

/*
     Layer _DRA (DRAwings, whatever else (rendering width varies in different applications))
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                   //(toggle) on _FUN
     BASE  „“    ”     ¤£    ∅ ¢   ±ƒ    | ❦♥    🙂🙁  👍👎   ⁽₍    ⁾₎    Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「─    」━   °〇   •§    …·    | ⮘     ⮚     ¿¡    《┄    》┅   RSft
     ----------------------------------------------
     LAlt Del   ___   Ent  | Spc   ___   LGUI  RGUI
                -*-       <|>      -*-                                                   //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  
 */
//
//      <pink2   , <pinky                     , <ring                      , <middl                       , <index                     , <indx2                      |, indx2>                       , index>                       , middl>                   , ring>                        , pinky>                       , pink2>  ,
//               ,                            ,                            ,                              ,                            ,                            <|,>                             , -*-                          ,                          ,                              ,                              ,         ,
        CTO_BASE , XP ( CS_DQUL , CS_DQUHR )  , X ( CS_DQUH )              , XP ( CS_CURREN , CS_POUND )  , XP ( CS_NONE , CS_CENT )   , XP ( CS_PLMI , CS_LGULDEN )  , XP ( CS_FLEUR , CS_HEART )   , XP ( CS_SMIL , CS_SAD_ )     , XP ( CS_THUP , CS_THDN ) , XP ( CS_OPSUP , CS_OPSUB )   , XP ( CS_CPSUP , CS_CPSUB )   , KC_BSPC ,
        KC_LCTL  , XP ( CN_1SUP , CN_1SUB )   , XP ( CN_2SUP , CN_2SUB )   , XP ( CN_3SUP , CN_3SUB )     , XP ( CN_4SUP , CN_4SUB )   , XP ( CN_5SUP , CN_5SUB )     , XP ( CN_6SUP , CN_6SUB )     , XP ( CN_7SUP , CN_7SUB )     , XP ( CN_8SUP , CN_8SUB ) , XP ( CN_9SUP , CN_9SUB )     , XP ( CN_0SUP , CN_0SUB )     , KC_RCTL ,
#ifdef space_cut_normal_arrow_ud 
        KC_LSFT  , XP ( CS_OCBRA , CS_LHORI ) , XP ( CS_CCBRA , CS_HHORI ) , XP ( CS_DEGREE , CS_CIRCLE ) , XP ( CS_BULLET , CS_PARA ) , XP ( CS_ELLIPS , CS_MIDDOT ) , X ( CS_LARROW )              , X ( CS_RARROW )              , XP ( CQU_INV , CEX_INV ) , XP ( CS_ODABRA , CS_LHORID ) , XP ( CS_CDABRA , CS_HHORID ) , KC_RSFT ,
#endif
#ifndef space_cut_normal_arrow_ud
        KC_LSFT  , XP ( CS_OCBRA , CS_LHORI ) , XP ( CS_CCBRA , CS_HHORI ) , XP ( CS_DEGREE , CS_CIRCLE ) , XP ( CS_BULLET , CS_PARA ) , XP ( CS_ELLIPS , CS_MIDDOT ) , XP ( CS_LARROW , CS_UARROW ) , XP ( CS_RARROW , CS_DARROW ) , XP ( CQU_INV , CEX_INV ) , XP ( CS_ODABRA , CS_LHORID ) , XP ( CS_CDABRA , CS_HHORID ) , KC_RSFT ,
#endif
//      ----------------------------------------------------------------------------
        KC_LALT , KC_DEL , DUO_HOLD , KC_ENT , KC_SPC , DUO_HOLD , KC__YGUI , KC__XGUI
//              ,        ,          ,      <|,>       ,          ,          ,
//      <1      , <2     , <3       , <4    |, 4>     , 3>       , 2>       , 1>
                      ),

        /**/


#ifndef QWERTY_DVORAK  // :   :   v   :   :   v   :   :   v   :   :   v   :   :   v   

    /* Layer _DDD: Drawings ('descramble'), like various Unicode symbols, and whatever else.
     *          The emoticons follow the "logic" of the movement layer.
     *          The symbols ¡ and ¿ are placed on top of ! and ?.
     *   
     */

    [ _DDD ] = LAYOUT (

/*
     Layer _DRA (DRAwings, whatever else (rendering width varies in different applications))
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                   //(toggle) on _FUN
     BASE  „“    ”     ¤£    ∅ ¢   ±ƒ    | ❦♥   🙂😃  👍👎   ⁽₍    ⁾₎     Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「─    」━   °〇   •§    …·    | ⮘     ⮚     ¿¡    《┄    》┅   RSft //⮙⮛, ┄┅ can be sacrificed
     ----------------------------------------------                            // to make room on device.
     LAlt Del   ___   Ent  | Spc   ___   LGUI  RGUI 
                -*-       <|>      -*-                                                   //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  
 */
//
//      <pink2      , <pinky     , <ring       , <middl      , <index      , <indx2      |, indx2>      , index>      , middl>     , ring>       , pinky>      , pink2>  ,
//                  ,            ,             ,             ,             ,            <|,>            , -*-         ,            ,             ,             ,         ,
        CTO_BASE    , UN_S_DQUL  , UN_S_DQUH   , UN_S_CURREN , UN_S_NONE   , UN_S_PLUSMIN , UN_S_FLEUR  , UN_S_SMIL   , UN_S_THUP  , UN_S_OPSUBP , UN_S_CPSUBP , KC_BSPC ,
        KC_LCTL     , UN_N_1SUBP , UN_N_2SUBP  , UN_N_3SUBP  , UN_N_4SUBP  , UN_N_5SUBP   , UN_N_6SUBP  , UN_N_7SUBP  , UN_N_8SUBP , UN_N_9SUBP  , UN_N_0SUBP  , KC_RCTL ,
        KC_LSFT     , UN_S_OCBRA , UN_S_CCBRA  , UN_S_DEGREE , UN_S_BULLET , UN_S_ELLIPS  , UN_S_LARROW , UN_S_RARROW , UN_QU_INV  , UN_S_ODABRA , UN_S_CDABRA , KC_RSFT ,
//      -------------------------------------------------------------------------------
        KC_LALT , KC_DEL , DUO_HOLD , KC_ENT  , KC_SPC  , DUO_HOLD , KC__YGUI , KC__XGUI
//              ,        ,          ,       <|,>        ,          ,          ,
//      <1      , <2     , <3       , <4     |, 4>      , 3>       , 2>       , 1>
                      ),  

#endif // QWERTY_DVORAK   :   :   ^   :   :   ^   :   :   ^   :   :   ^   :   :   ^   
                          
        /**/              
                          

    /* Layer _FUN: Function keys, most on the right side, some combo modifiers control/alt/shift
     *          Toward any layer by toggle. Set 'descramble' mode.
     */

    [ _FUN ] = LAYOUT (

/*
     Layer _FUN (F-keys, Layer access, Set BASE key direction)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl set   toggl toggl toggl | toggl toggl                   cycles   // Type of layer switch
                 -v-                    <|>                                       // -v- One-shot setting
     BASE: NUMS: FUN<  _MOV  _RAR  _PAD  | ACCE: DRAW: xxx   xxx   xxx   !Descr     //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10     RCtl     //...  ! 'descramble'
     LSft  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20   -*RSft     //... < toggle 'stay'
     -------------------------------------------------------                        //. -* toggle on BASE
     LAlt  LCtl&  LGUI  LCtl& | LSft& +LCtl&LSft LGUI   RAlt
           LSft         LAlt  | LAlt  &LAlt                                    
           +xxx         +xxx  | +xxx  +xxx
                             <|>
     <1    <2     <3    <4    | 4>    3>         2>     1>                
 */
//
//      <pink2   , <pinky   , <ring     , <middl      , <index      , <indx2     |, indx2>   , index>   , middl>  , ring>   , pinky>  , pink2>        ,
//               ,          , -*-       ,             ,             ,           <|,>         ,          ,         ,         ,         ,               ,
        CTO_BASE , CTO_NUMS , _FUN_STAY , TO ( _MOV ) , TO ( _RAR ) , TO ( _PAD ) , CTO_ACCE , CTO_DRAW , XXXXXXX , XXXXXXX , XXXXXXX , BASE_DESCRMBL ,
        KC_LCTL  , KC_F1    , KC_F2     , KC_F3       , KC_F4       , KC_F5       , KC_F6    , KC_F7    , KC_F8   , KC_F9   , KC_F10  , KC_RCTL       ,
        KC_LSFT  , KC_F11   , KC_F12    , KC_F13      , KC_F14      , KC_F15      , KC_F16   , KC_F17   , KC_F18  , KC_F19  , KC_F20  , KC_RSFT       ,
//      ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT , MT ( MOD_LCTL | MOD_LSFT, XXXXXXX ) , KC__XGUI , MT ( MOD_LCTL | MOD_LALT , XXXXXXX ) , MT ( MOD_LSFT | MOD_LALT , XXXXXXX ) , MT ( MOD_LCTL | MOD_LSFT | MOD_LALT , XXXXXXX ) , KC__YGUI , KC_RALT
//              ,                                     ,          ,                                    <|,>                                     ,                                                 ,          ,
//      <1      , <2                                  , <3       , <4                                  |, 4>                                   , 3>                                              , 2>       , 1>
                      ),

        /**/



/*
 * New layer template. Includes left/right movement arrows, deletion, modifiers.
 * If you want a new layer, in the logic of this layout you would add a toggle on the
 * _FUN layer top row on the first free key to it, and optionally alter the hold 
 * layer switch keys on the base layers. (Check if a new layer will fit on the chip.)
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

