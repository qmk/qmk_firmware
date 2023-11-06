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
 * Remainder: © 2019, 2020, 2021 by Jos Boersema
 */

// --------------------------------------v---------------------------------------
//                                 Configuration:
// --------------------------------------v---------------------------------------
#include "./user_config.h" // Edit this file to set user preference compile options.
// --------------------------------------^---------------------------------------



    /* Configurable keymap for Minivan layouts 44, 45, 46 keys.  
     * May work for 12×12×12×[11-12] keys as well.
     * Configuration in ./user_config.h
     */

  /* Overview of the code
   *
   * The base layers are in separate files;
   * process_record_user(), unicode macros are defined in unicode_macros.c;
   * accented characters are defined in unicode_weurope.h
   *
   * Unicode macros facilitate recomputing for re-computing the Dvorak with changed letters 
   * ('descramble'), and exist because space ran out for * UP(…).
   *
   * The led color code might be a bit hairy, due to speed/count middle led overlapping layer color. 
   *
   *  Preprocessor indentation: # always in column one, #includes and #defines
   *  are most to the left unless nested, except in the user configuration
   *  block where room is left for a ‛//’. Logical stuff (#if etc) is
   *  indented from column two, and then in each nesting goes 4 more spaces
   *  to the right, so in between the normal code indentations. There should
   *  be a newline above and below logical statements. This makes preprocessor
   *  statements stand out, while giving more information in each statement.
   *  C indentation: trying to follow QMK standard.
   *
   */


#include QMK_KEYBOARD_H

// Bit masks for the Base layers, to set them as Default, in order to make transparency look back to the right one.
#define _DEF_BASE_MASK 0x1 // Some functions take a bit-mask, where layer 0 (zero) is called 0x1 instead.
#define _ALT_BASE_MASK 0x2 // Some functions take a bit-mask, where layer 0 (zero) is called 0x1 instead.

// Below #defines the internal order of the layers.
// Notice this order in layer_state_set_user as well, regarding the led indicators.
enum {
    _DEF_BASE,  //  Default BASE layer (layer at startup). Typically the letters.

# ifndef MINIFAN_SINGLE_LAYOUT

    _ALT_BASE,  //  Alternative BASE layer.

# endif

    _DEF_NSY,   //  numbers and symbols

# ifndef MINIFAN_SINGLE_LAYOUT

    _ALT_NSY,   //  Alternate version of _DEF_NSY

# endif

    _MOV,  //  movement arrows and mouse
    _RAR,  //  keys RARely used, Unicode config, Power keys, Media keys, alternate mode switch, speed/size count, …

# ifndef REMOVE_PAD

    _PAD,  //  Numbers pad. These are different versions of the same numbers, that is ‛1’ (_NSY) ≠ ‛1’ (_PAD).

# endif

# ifndef REMOVE_ACC // Removes this layer entirely, if set.

    _ACC,  //  Accented letters 

# endif

# ifndef REMOVE_DRA // Removes this layer entirely, if set.

    _DRA,  //  Unusual symbols and whatever else

# endif

# ifndef REMOVE_BON // Removes this layer entirely, if set.

    _BON,  //  Bonus layer with more Unicode symbols

# endif

    _FUN,  //  function keys, layer switcher, given highest order precedence just in case
} ;
// The default and alternate base layers needs to have a low order
// number, so that the other layers can be accessed on top of it.
// Default Layer is set, according to active Base pair.

// What BASE layer is active.
enum {
    _NORMAL_, // BASE layer is _DEF_BASE
    _FULL_,   // BASE layer is _ALT_BASE
# ifdef DVORAK_DESCRAMBLE // not used with other keymaps
    _HALF_,   // BASE layer is _ALT_BASE For DVORAK_DESCRAMBLE keymap: does *not* re-compute letters in Unicode
              // This is for different Unicode encodings than “Control+U+HEX” (Linux). It will go through what is set on _RAR
# endif
};
// The mechanism is about what layer to return to, once needing to go back to the letters layer (BASE).

# ifndef STARTUP_ALTERNATE // Startup with in default BASE, normal mode.
short alternate = _NORMAL_;
# else                    // Startup with alternate BASE active
short alternate = _FULL_; // 
# endif

//* Shift detection
bool shift_ison = 0; // keep track of the state of shift (Capslock is ignored). There may be more elegant code for this in
                     //   QMK (a function seems to do it?), but this is simple and keeps the issue isolated to this file.
# define TRUE 1
# define FALSE 0
bool _fun_stay = FALSE; // for making _FUN layer not return to BASE after pressing an F-key
bool leds_on; // toggle leds on/off

# ifdef LEDS_OFF_BASE_DEF  
bool led_middle_on = TRUE; // Set to off later, if startup setting is off.
# endif

bool isolate_trigger = FALSE; // detects if _FUN layer move was pressed, and no other key (no normal use of Shift).
bool capslock; // keeps track of capslock state
bool numlock; // keeps track of numlock state
//layer_state_t state_recall; // We are calling the function set_led_colors_ from this file as well.
// speed measuring
bool     speed_measure = SPEED_INIT_VALUE; // feature activated or not on startup
uint32_t speed_counttime; // counts the time
short    speed_countdown = SPEED_COUNTDOWN; // countdown to next computation/effects
int      speed; // we store typing result (keys/second) to make reporting less stressful on user, as it doesn't run away after typing
                // the value is recorded 10 times higher, to allow another digit of precision, needed to calculate Words-Per-Minute
long int speed_batches = 0; // This counts how many batches of SPEED_COUNTDOWN have been added to wordcount_speed_add
long int speed_add = 0; // This just adds the speed computed for every batch of SPEED_COUNTDOWN, also times 10 for precision
// character and word counting, attempting to count the final text being written
bool     sizecount_measure = COUNT_INIT_VALUE; // feature activated or not on startup
long int sizecount_blanks = 0; // This counts spaces/enters as a means of counting words, with manual substraction key
long int sizecount_chars = 0; // This counts characters, substraction for delete/backspace
bool     sizecount_word; // remember if the last character was whitespace, so a second does not count a word
bool     sizecount_menu = FALSE; // menu mode for configuring sizecount led color & alert system for maximum size.
long int sizecount_max = 0; // the maximum system for count, alert user about relative size/limit
bool     sizecount_max_type; // is size counting by word or by character
#define SIZECOUNT_WORD 0 // The type of text size counting: words
#define SIZECOUNT_CHAR 1 //           "                   : characters

/* This file contains mostly the Unicode and special macros.
   It contains the function: process_record_user(...)
   It has been isolated because the source file got long.
 */
#include "./unicode_macros.c"


// Pre-existing function, run when the keyboard starts up.
void keyboard_post_init_user (void) {

# ifdef RGBLIGHT_ENABLE

// Set side leds on/off startup
#     ifdef STARTUP_SIDE_LEDS_OFF
    leds_on = FALSE;
#     else
    leds_on = TRUE;
#     endif

    // Set up RGB effects on _only_ the first LED 
    rgblight_set_effect_range (1, 1); // Takes a range: 1st arg is start, 2nd how many
    rgblight_sethsv_noeeprom (HSV_WHITE); // Startup color of keyboard.
    // Set LED effects to breathing mode
    rgblight_mode_noeeprom (RGBLIGHT_EFFECT_BREATHING + 2);

    // Init the first and last LEDs to a static color.
    setrgb (0, 0, 0, (LED_TYPE *)&led[0]); // Led[0] is led 0
    setrgb (0, 0, 0, (LED_TYPE *)&led[2]); // 2nd led

// The logic seems to be to establish the effect first, and then toggle it on/off.
#     ifdef STARTUP_MID_LED_OFF
    rgblight_disable (); // 
#         ifdef LEDS_OFF_BASE_DEF  // This messes with led effect on/off, so we need to track the state of this setting now.
    led_middle_on = FALSE;
#         endif
#     endif

    isolate_rgblight_set ();

# endif //RGBLIGHT_ENABLE

// Set startup layer
# ifdef STARTUP_ALTERNATE 
    layer_move (_ALT_BASE);
# else
    layer_move (_DEF_BASE);
# endif

    _fun_stay = TRUE; // startup with F-keys not returning to Base after stroke (_FUN)

}


// Writes a number as if typed on keyboard. Typically to show a speed/text size measurement.
// If last argument is TRUE it prints a dot ‛.’ before the last digit
int write_number (long int input, short divide10) { 
    long int step10;
    short digit;
    short start = FALSE;
    short printed = 0;
    char output[2];

    output[1] = '\0';
    if (0 > input) { // number is negative
        send_string ("-"); // minus
        printed++;
        input *= -1; // turn positive
    }
    for (step10 = 1000000000; 0 != step10; step10 /= 10) { // assuming 32 bit, ± 10⁹
        digit = input / step10; 
        input = input % step10;
        if (!start) { // remove leading zeros
            if ((0 != digit) || (1 == step10)) start = TRUE; // If all zeros, always print last zero.
        }
        if (divide10 && (1 == step10)) { // print with a dot before the last digit
            send_string (".");
            printed++;
        }
        if (start) { // print
            output[0] = '0' + digit;
            send_string (output);
            printed++;
        }
    }
    return printed;
}


// This function prevents the middle led from being altered by layer
// switching (showing the layer color, that is), when another 
// functionality takes precedent over the middle led.
void middle_led_control (short hsv_h, short hsv_s, short hsv_v ) {
# ifdef RGBLIGHT_ENABLE

    if (FALSE == speed_measure) { // only touch middle led if no speed measuring going on
       if ( ! ((TRUE == sizecount_measure) && (0 != sizecount_max)) ) { // only touch middle led if no text size
              // counting set to a maximum is going on.

            rgblight_sethsv_noeeprom (hsv_h, hsv_s, hsv_v); // set it
        }
    }

# endif
}


// Set middle led color for speed system. Needed in various places.
void speed_led (int speed) {
# ifdef RGBLIGHT_ENABLE

    speed /= 10; // argument is in 10 times its value
    if ( ! ((TRUE == sizecount_measure) && (0 != sizecount_max)) ) { // only touch middle led if no text size
           // counting set to a maximum is going on.
        rgblight_sethsv_noeeprom (SPEED_HUE_STEP * speed + SPEED_HUE_START, 255, 128); // full saturation, but half lit
        rgblight_set (); // only center led is altered, no need to go through isolate_rgblight_set()
    }

# endif
}


// do this in one place to handle left/right leds being off here
void isolate_rgblight_set (void) {

# ifdef RGBLIGHT_ENABLE
    if (!leds_on) { // left/right leds are off
        // overwrite previously colors
        uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
        uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
        led0r = 0; 
        led0g = 0; 
        led0b = 0; 
        led2r = 0; 
        led2g = 0; 
        led2b = 0; 
        setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
        setrgb(led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2
    }
    rgblight_set ();
# endif

}


// _FUN layer leds.
void indicate_fun_stay (void) {
# ifdef RGBLIGHT_ENABLE

    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
    // See also below under _FUN layer led
    if (_fun_stay == TRUE) { // normal mode, 0 (100% normal)
        led0r = 255; // red
        led2r = 255; // Yellow
        led2g = 50;
    }else{
        led0r = 255; // Yellow
        led0g = 50;  //   
        led2r = 255; // red
    }
    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb(led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2
    isolate_rgblight_set ();

# endif //RGBLIGHT_ENABLE
}


// _RAR layer leds
// It is a function because this is also called when the Base layer OTHER_BASE key is pressed
void indicate_base (void) {
# ifdef RGBLIGHT_ENABLE

    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
    // See also below under _FUN layer led
    if (_NORMAL_ == alternate) { // normal mode, 0 (100% normal)
        led0r = 255; //  shine white left led
        led0g = 255;
        led0b = 255;
        rgblight_sethsv_noeeprom (HSV_PURPLE);  // This overrides the speed setting.
        led2r = 100; // purple
        led2b = 100;
    }

#     ifdef DVORAK_DESCRAMBLE // not used with other keymaps
      else if (_HALF_ == alternate) { // alternate mode, 1 (normal unicode)
        led0r = 100; // purple
        led0b = 100;
        rgblight_sethsv_noeeprom (HSV_WHITE); //  shine white middle led (still breathes)
        led2r = 100; // purple
        led2b = 100;
    }
#     endif

      else if (_FULL_ == alternate) { // alternate mode, 1 (recomputed unicode for DVORAK_DESCRAMBLE)
        led0r = 100; // purple
        led0b = 100;
        rgblight_sethsv_noeeprom (HSV_PURPLE); 
        led2r = 255;//  shine white right led
        led2g = 255; 
        led2b = 255; 
    }
    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb(led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2
    isolate_rgblight_set ();

# endif //RGBLIGHT_ENABLE
}


// Sets led colors for all layers. Including Capslock/Numlock changes. See a computer side activated function for that too:
//                                                                                    led_update_user (…)
void set_led_colors_ (layer_state_t state) {
# ifdef RGBLIGHT_ENABLE

    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
    short color_ddl = 28 ;

#     ifdef LEDS_OFF_BASE_DEF 
    // Special case of switching centre led effect on/off
    if (!layer_state_cmp (state, _DEF_BASE)) { // letters
        //if (rgblight_is_enabled())
        if (led_middle_on) { // Follows user setting based on _RAR key.
            rgblight_enable_noeeprom (); // Would be easier if middle_led_control (…) could set brightness to dark, but seems to not work.
        }
    }
#     endif

    // The order should be the reverse of the #defines of layer number of the layers on top
    // because higher layer number is higher priority if activated
    /* _DEF_BASE 0 _ALT_BASE 1 _DEF_NSY 2 _ALT_NSY 3 _MOV 4 _RAR 5 _PAD 6 _ACC 7 _DRA 8 _BON 9 _FUN 10 */
    if (layer_state_cmp (state, _FUN)) { // F-keys, and layer toggles
        middle_led_control (HSV_RED); // purple
        indicate_fun_stay (); // Indicates state of _fun_stay, but only when it is being toggled.
        return ; // indicate_fun_stay function already does it all.
    } 

#     ifndef REMOVE_BON // Removes this layer entirely, if set.
    else if (layer_state_cmp (state, _BON)) {  // Bonus layer with encircled numbers and more symbols
        // side leds dark
        middle_led_control (HSV_YELLOW); 
    }
#     endif // REMOVE_BON 

#     ifndef REMOVE_DRA // This cuts out the whole _DRA layer
    else if (layer_state_cmp (state, _DRA)) { // Unicode drawings and unusual things
        led0r = 255; // gold red
        led0g = 128; // 
        led2r = 255; //
        led2g = 128; //
        middle_led_control( HSV_GOLDENROD ); 
    }
#     endif // REMOVE_DRA

#     ifndef REMOVE_ACC // This cuts out the whole _ACC layer.
    else if (layer_state_cmp (state, _ACC)) { // Accented letters (Unicode input layer)
        led0g = 150; // With some blue, because it is also a symbol 
        led0b = 100;
        led2g = 150;
        led2b = 100;
        middle_led_control (HSV_TURQUOISE); // cyan
    }
#    endif // REMOVE_ACC

#    ifndef REMOVE_PAD
    else if (layer_state_cmp (state, _PAD)) { // numbers pad layer
        if (numlock) {
            led0b = 255; // Blue for the numbers part 
            led2g = 255; // Green for the navigation part
        }else{
            led0g = 255; // reversed 
            led2b = 255; //
        }
        middle_led_control (60, 20, 100); // yellow (low saturation)
    }
#     endif // REMOVE_PAD

    //---
    else if (layer_state_cmp (state, _RAR)) { // layer with special keys
        indicate_base (); // this function already does it all
        return; // 
    }
    //---
    else if (layer_state_cmp (state, _MOV)) { // movement layer
        led0g = 255;// movement is green, "go forward"
        led2g = 255; 
        middle_led_control(HSV_GREEN);
    }
    //--- (pair)
    else if (layer_state_cmp (state, _ALT_NSY)) { // alternate, numbers/symbols 
        led0b = 255; //  first led follows the corresponding default layer: _DEF_NSY 
        led2r = color_ddl; // Same as DDL, to which it belongs.
        led2g = color_ddl; // 
        led2b = color_ddl; // 
        middle_led_control (HSV_BLUE); 
    }
    else if (layer_state_cmp (state, _DEF_NSY)) { // symbols and numbers
        led0b = 255; // blue for symbols, like ink (writing)
        led2b = 255;
        middle_led_control (HSV_BLUE);
    }
    //--- (pair)
    // Alternate BASE layer (alternate)
    else if (layer_state_cmp (state, _ALT_BASE)) {

#     ifdef LEDS_OFF_BASE_ALT // Alternative Base leds off (always)

        rgblight_disable_noeeprom ();

#     else // do use leds on Alternative Base layer

#         if !defined(BASE_NUMPAD__ALT_BASE) // Normal led colors for ‛regular’ base layers like Dvorak, Qwerty. 

        if (capslock) {
           led2r = 255; // Brighter version to indicate capslock
           led2g = 255; // 
           led2b = 255; // 
        } else {
           led2r = color_ddl; // A bit of a white not too bright color on right
           led2g = color_ddl; // 
           led2b = color_ddl; // 
        }
        middle_led_control (HSV_TEAL); // seems to be the same as CYAN/AZURE, conflicts with _ACC

#         else // Numpad configured on Alternate Base, which should show the state of NumLock

        // This is a copy of the _PAD led colors, but less bright
        if (numlock) {
            led0b = 80; // Blue for the numbers part 
            led2g = 80; // Green for the navigation part
        }else{
            led2b = 80; // reversed 
            led0g = 80; //
        }
        middle_led_control (60, 20, 100);  // light-blue

#         endif // BASE_NUMPAD__ALT_BASE

#     endif // LEDS_OFF_BASE_ALT 

    }
    // Default layer (generally), normal BASE layer
    else if (layer_state_cmp (state, _DEF_BASE)) { // letters

#     ifdef LEDS_OFF_BASE_DEF // Default Base leds off (always)

        rgblight_disable_noeeprom ();

#     else // Do use leds on Default Base

        if (capslock) {
            led0r = 255; // Brighter version to indicate capslock
            led0g = 255; // 
            led0b = 255; // 
        } else {
            led0r = 28; // A bit of a weak white color on left 
            led0g = 28; // 
            led0b = 28; // 
        }
        middle_led_control (HSV_TEAL);

#     endif // LEDS_OFF_BASE_DEF 

    }
    //---

    // pushes the configuration
    setrgb (led0r, led0g, led0b, (LED_TYPE *)&led[0]); // Led 0
    setrgb (led2r, led2g, led2b, (LED_TYPE *)&led[2]); // Led 2

    isolate_rgblight_set (); // Activates the led color change, after on/off check.

# endif //RGBLIGHT_ENABLE
}

// Pre-existing QMK function, called when NumLock/CapsLock key is pressed, including on another keyboard.
// This function sets two booleans that keep track of the current capslock/numlock state, for use in layer led colors.
bool led_update_user (led_t led_state) {

    if (led_state.num_lock) { // This doesn't look at the keyboard leds or any other actual leds. It seems to look at whether
                              // or not the computer has numlock in the on/off state.
        numlock = TRUE;
    }else{
        numlock = FALSE;
    }
    if (led_state.caps_lock) {
        capslock = TRUE;
    }else{
        capslock = FALSE;
    }
    //layer_state_set_user 
    set_led_colors_ (state_recall); // Update leds
    return true ;
}


// pre-existing function, called when layer changes
layer_state_t layer_state_set_user (layer_state_t state) {

  set_led_colors_ (state); // Update leds 
  state_recall = state; // Recall this, for calling set_led_colors_(…) on Num/Capslock changes in led_update_user(…)
  return state;
}

// -------------------------------- layers --------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/********************        What base layers to use:        **************/

//                         * Dvorak *
# if defined(BASE_DVORAK__DEF_BASE) || defined(BASE_DVORAK__ALT_BASE)
#     include "./base_dvorak.c" // Regular Dvorak.
# endif

//                         * Dvorak descramble *
# if defined(BASE_DVORAK_DESCRAMBLE__ALT_BASE) // only for ‛Alternate’ base
#     include "./base_dvorak_descramble.c" // Dvorak for when computer is already remapping to Dvorak.
# endif

//                         * Qwerty *
# if defined(BASE_QWERTY__DEF_BASE) || defined(BASE_QWERTY__ALT_BASE)
#     include "./base_qwerty.c" // Regular Qwerty.
# endif
    
//                         * Qwerty arrows on Base *
# if defined(BASE_QWERTY_BASEARROW__DEF_BASE) || defined(BASE_QWERTY_BASEARROW__ALT_BASE)
#     include "./base_qwerty_basearrow.c" // Qwerty + arrows
# endif

//                         * Colemak *
# if defined(BASE_COLEMAK__DEF_BASE) || defined(BASE_COLEMAK__ALT_BASE)
#     include "./base_colemak.c" // Regular Colemak.
# endif

//                         * Workman *
# if defined(BASE_WORKMAN__DEF_BASE) || defined(BASE_WORKMAN__ALT_BASE)
#     include "./base_workman.c" // Regular Workman.
# endif

//                         * Numpad *
# if defined(BASE_NUMPAD__ALT_BASE)
#     include "./base_numpad.c" // Numbers pad
# endif

//                         * Hebrew *
# if defined(BASE_HEBREW__DEF_BASE) || defined(BASE_HEBREW__ALT_BASE)
#     include "./base_hebrew.c" // Hebrew
# endif

// // ⬇ insert your ./base_YOUR_KEYMAP.c #include here:


//                         * YOUR KEYMAP *
// # if defined(BASE_YOUR_KEYMAP__DEF_BASE) || defined(BASE_YOUR_KEYMAP__ALT_BASE)
// #     include "./base_YOUR_KEYMAP.c" // Your Keymap.
// # endif

// If your keymap also has a ./base_YOUR_KEYMAP.h configuration/header file, #include it in ./user_config.h
// Look for similar inclusions of base header files, similar to the #includes here.
// You should be able to just copy what you did here, and only change “.c” into “.h”.

// // ⬆


        // See the ./bases_*.c file for definition of _DEF_BASE, _DEF_NSY, _ALT_BASE, _ALT_NSY layers, selected in ./user_config.h

        /* ⬆⬇ (next layer) */


# ifndef BASESFILE_LAYER_MOV // Use a definition of this layer in the ./bases_* file, where this #define can be defined.

    /* Layer _MOV: Movement layer: mouse and hands on navigation
     *          Also delete/backspace, to navigate and delete together.
     */

    [ _MOV ] = LAYOUT_redefined (

/*
     Layer _MOV (MOVement, mouse movement on right hand)

     triangle layout (mouse right hand):
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                        //(toggle) on _FUN
     BASE   PgDn  Up    PgUp  Home  Btn3  | xxx   WhDn  MsUp  WhU   WhLft    Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht    RCtl
     LSht*- xxx   Acc2  Acc1  Acc0  Btn2  | Btn2  Btn3  Btn4  Btn5  xxx      RSht      //(toggle) on BASE
     ----------------------------------------------------------------------------
     LAlt Del   Ent   ___ | PgUp  PgDn  LGUI  RAlt
                      -*-<|>                                                             //(hold) on BASE
     <1 ± <2    <3    <4  | 4>    3>    2>  ± 1>  
        …                                   …

     triangle layout, 'arrow' additional hardware key, with arrow cluster (difference marked _):
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                        //(toggle) on _FUN
     BASE   PgDn  Up    PgUp  Home  Btn3  | xxx   WhDn  MsUp  WhU   WhLft    Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht    RCtl
     LSht*- xxx   Acc2  Acc1  Acc0  Btn2  | Btn2  Btn3  Btn4  Btn5  _Up_     RSht      //(toggle) on BASE
     ----------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp       PgDn   _Left__Down__Right_
                                      -*-<|>                                             //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>         3>      2>   _±_    1>  
                        …     

     triangle layout, 'arrow' additional hardware key, with arrow cluster and navigation keys:
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                        //(toggle) on _FUN
     BASE   PgDn  Up    PgUp  Home _Btn4_ | xxx   WhDn  MsUp  WhU   WhLft    Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht    RCtl
     LSht*- xxx   Acc2  Acc1  Acc0 _Btn5_ | Btn2  Btn3 _Home__PgUp_ _Up_   _PgDn_      //(toggle) on BASE
     ----------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _End_   _Left__Down__Right_
                                      -*-<|>                                             //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>         3>      2>   _±_    1>  
                        …


     flat layout (mouse movement on left hand):
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                        //(toggle) on _FUN
     BASE   WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn     Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right    RCtl
     LSht*- Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx      RSht      //(toggle) on BASE
     ----------------------------------------------------------------------------
     LAlt Del   Ent   ___ | PgUp  PgDn  LGUI  RAlt
                      -*-<|>                                                             //(hold) on BASE
     <1 ± <2    <3    <4  | 4>    3>    2>  ± 1>  
        …

     flat layout, 'arrow' additional hardware key, with arrow cluster (difference marked _)
   
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                        //(toggle) on _FUN
     BASE   WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn     Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right    RCtl
     LSht*- Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx      RSht      //(toggle) on BASE
     ----------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp       _Left_ _Up_  _Down__Right_
                                      -*-<|>                                           //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>          3>     2>   _±_    1>  
                        …

     flat layout, 'arrow' additional hardware key, with arrow cluster and additional navigation keys:
   
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                        //(toggle) on _FUN
     BASE   WLft  WDn   WUp   WRht  xxx   |_Acc2_ PgUp  Home  End   PgDn     Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right    RCtl
     LSht*- Btn5  Btn4  Btn3  Butn2 xxx   |_Acc1_ Acc0 _PgUp__Home__End_   _PgDn_      //(toggle) on BASE
     ----------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp       _Left_ _Up_  _Down__Right_
                                      -*-<|>                                             //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>          3>     2>   _±_    1>  
                        …

     flat layout, 'arrow' additional hardware key, with arrow cluster, additional navigation keys, vi(1) layout:
   
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                        //(toggle) on _FUN
     BASE   WLft  WDn   WUp   WRht  xxx   |_Acc2_ PgUp  Home  End   PgDn     Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Left  Down  Up    Right Btn1     RCtl
     LSht*- Btn5  Btn4  Btn3  Butn2 xxx   |_Acc1_ Acc0 _PgUp__Home__End_   _PgDn_      //(toggle) on BASE
     ----------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp       _Left_ _Down__Up_  _Right_
                                      -*-<|>                                             //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>          3>     2>   _±_    1>  
                        …
 */

         /* Inner default navigation/mouse layout. 11 means row 1, column 1, etc.
          * Configured for arrows on the right, mouse on the left (BTN* on the left side, that is).
          */

#     ifndef ARROWS_TRIANGLE
#         define NAVI_11 KC_BTN3 // NAVI for 'navigation cluster', 11 for row 1, column 1, etc.
#         define                 NAVI_12 KC_PGUP
#         define                                 NAVI_13 KC_HOME
#         define                                                 NAVI_14 KC_END
#         define                                                                NAVI_15 KC_PGDN
#         define NAVI_21 KC_BTN1
#         define                 NAVI_22 KC_LEFT
#         define                                 NAVI_23 KC_UP
#         define                                                 NAVI_24 KC_DOWN
#         define                                                                NAVI_25 KC_RIGHT
#         define NAVI_31 KC_BTN2
#         define                 NAVI_32 KC_ACL0
#         define                                 NAVI_33 KC_ACL1
#         define                                                 NAVI_34 KC_ACL2
#         define                                                                NAVI_35 XXXXXXX
          //-----------------------------------------------------------------------------------
          // Configured for left handed mouse, with xxx,BTN* on the right most column.
#         define MOUS_11 KC_WH_L  // MOUS for mouse, etc.
#         define                 MOUS_12 KC_WH_D
#         define                                 MOUS_13 KC_WH_U
#         define                                                 MOUS_14 KC_WH_R
#         define                                                                MOUS_15 XXXXXXX
#         define MOUS_21 KC_MS_L
#         define                 MOUS_22 KC_MS_D
#         define                                 MOUS_23 KC_MS_U
#         define                                                 MOUS_24 KC_MS_R
#         define                                                                MOUS_25 KC_BTN1
#         define MOUS_31 KC_BTN5
#         define                 MOUS_32 KC_BTN4
#         define                                 MOUS_33 KC_BTN3
#         define                                                 MOUS_34 KC_BTN2
#         define                                                                MOUS_35 XXXXXXX
#     endif

// Alternative navigation/mouse layout: arrows in triangle, and left hand on the left 'wasd' location.
// If you want these arrows on the right hand, you may want to edit this, to put right most column left, etc.

#     ifdef ARROWS_TRIANGLE
#         define NAVI_11 KC_PGDN
#         define                 NAVI_12 KC_UP   
#         define                                 NAVI_13 KC_PGUP
#         define                                                 NAVI_14 KC_HOME
#         define                                                                 NAVI_15 KC_BTN3
#         define NAVI_21 KC_LEFT
#         define                 NAVI_22 KC_DOWN
#         define                                 NAVI_23 KC_RIGHT
#         define                                                  NAVI_24 KC_END
#         define                                                                 NAVI_25 KC_BTN1
#         define NAVI_31 XXXXXXX
#         define                 NAVI_32 KC_ACL2
#         define                                 NAVI_33 KC_ACL1
#         define                                                  NAVI_34 KC_ACL0
#         define                                                                 NAVI_35 KC_BTN2
          //------------------------------------------------------------------------------------
          // If switching hands to put mouse left, same as for navigation side: switch outer columns by editing here.
#         define MOUS_11 XXXXXXX
#         define                 MOUS_12 KC_WH_D
#         define                                 MOUS_13 KC_MS_U
#         define                                                 MOUS_14 KC_WH_U
#         define                                                                MOUS_15 KC_WH_L
#         define MOUS_21 KC_BTN1
#         define                 MOUS_22 KC_MS_L
#         define                                 MOUS_23 KC_MS_D
#         define                                                 MOUS_24 KC_MS_R
#         define                                                                MOUS_25 KC_WH_R
#         define MOUS_31 KC_BTN2
#         define                 MOUS_32 KC_BTN3
#         define                                 MOUS_33 KC_BTN4
#         define                                                 MOUS_34 KC_BTN5
#         define                                                                MOUS_35 XXXXXXX
#     endif

// Default left/right layout, meaning arrows right and mouse left.
#     ifndef ARROWS_LEFT
#         define LEFT_AA MOUS_11
#         define LEFT_AB MOUS_12
#         define LEFT_AC MOUS_13
#         define LEFT_AD MOUS_14
#         define LEFT_AE MOUS_15
#         define LEFT_BA MOUS_21
#         define LEFT_BB MOUS_22
#         define LEFT_BC MOUS_23
#         define LEFT_BD MOUS_24
#         define LEFT_BE MOUS_25
#         define LEFT_CA MOUS_31
#         define LEFT_CB MOUS_32
#         define LEFT_CC MOUS_33
#         define LEFT_CD MOUS_34
#         define LEFT_CE MOUS_35
#         define RGHT_AA NAVI_11
#         define RGHT_AB NAVI_12
#         define RGHT_AC NAVI_13
#         define RGHT_AD NAVI_14
#         define RGHT_AE NAVI_15
#         define RGHT_BA NAVI_21
#         define RGHT_BB NAVI_22
#         define RGHT_BC NAVI_23
#         define RGHT_BD NAVI_24
#         define RGHT_BE NAVI_25
#         define RGHT_CA NAVI_31
#         define RGHT_CB NAVI_32
#         define RGHT_CC NAVI_33
#         define RGHT_CD NAVI_34
#         define RGHT_CE NAVI_35
#     endif
      
#     ifdef ARROWS_LEFT
#         define LEFT_AA NAVI_11
#         define LEFT_AB NAVI_12
#         define LEFT_AC NAVI_13
#         define LEFT_AD NAVI_14
#         define LEFT_AE NAVI_15
#         define LEFT_BA NAVI_21
#         define LEFT_BB NAVI_22
#         define LEFT_BC NAVI_23
#         define LEFT_BD NAVI_24
#         define LEFT_BE NAVI_25
#         define LEFT_CA NAVI_31
#         define LEFT_CB NAVI_32
#         define LEFT_CC NAVI_33
#         define LEFT_CD NAVI_34
#         define LEFT_CE NAVI_35
#         define RGHT_AA MOUS_11
#         define RGHT_AB MOUS_12
#         define RGHT_AC MOUS_13
#         define RGHT_AD MOUS_14
#         define RGHT_AE MOUS_15
#         define RGHT_BA MOUS_21
#         define RGHT_BB MOUS_22
#         define RGHT_BC MOUS_23
#         define RGHT_BD MOUS_24
#         define RGHT_BE MOUS_25
#         define RGHT_CA MOUS_31
#         define RGHT_CB MOUS_32
#         define RGHT_CC MOUS_33
#         define RGHT_CD MOUS_34
#         define RGHT_CE MOUS_35
#     endif

/* Definition of the additional arrow cluster with optional navigation keys, for the 'arrow' hardware layout.
 *
 * By default what becomes the up-arrow (row 2, 2nd key from right) is a no-action key on this layer,
 * which can be displaced without worry.
 * Keys that are displaced for the larger arrow cluster with navigation keys, get moved to the second definition
 * of KC_BTN2 and KC_BTN3, which is on the non-mouse hand.
 *
 * Only the version where the triangle arrows are defined for the left hand, or the version where the flat line
 * arrows are defined for the right hand, are supported.
 *
 * There are several configurations, worked down in order to keep this mess under control.
 *                
 *                                           v----------------------not-defined-------------v----------------v
 *                                 !MOREKEY2_ARROW_CLUSTER   !MOREKEY2_ADD_NAVIGATION  !ARROWS_TRIANGLE  !ARROWS_LEFT             
 * defined MOREKEY2_ARROW_CLUSTER   ......................            yes                    yes            yes
 * defined MOREKEY2_ADD_NAVIGATION        yes                 .......................        yes          only for flat arrows
 * defined ARROWS_TRIANGLE                yes                         yes               ...............      no  
 * defined ARROWS_LEFT                    yes                    only for triangle          yes           ...........
 *                                  MOREKEY2_ARROW_CLUSTER    MOREKEY2_ADD_NAVIGATION   ARROWS_TRIANGLE   ARROWS_LEFT             
 *                                           ^--------------------------defined-------------^----------------^
 *
 * Definition order:
 *  0 no arrow cluster (and therefore no additional navigation keys either)
 *  1 triangle arrows with arrow cluster
 *  2    ''                  ''          + additional navigation and repositioning displaced keys
 *  3 flat arrows with arrow cluster
 *  4    ''                  ''          + additional navigation and repositioning displaced keys
 */

                                               /* 0 (Nothing special, just the default keys)*/

// Default layout without arrow cluster. (With a little imagination you can visualize the keyboard.)
#     if !defined(MOREKEY2_ARROW_CLUSTER) 
//                                                                             Default 
#         define _MOV_KEY_ROW2_KEY1                               KC_RSFT    
#         define _MOV_KEY_ROW2_KEY2                     RGHT_CE              // Key counting from the right to the left. 
#         define _MOV_KEY_ROW2_KEY3           RGHT_CD                        
#         define _MOV_KEY_ROW2_KEY4 RGHT_CC                                  
//                                  ------------------------------------------
#         define _MOV_KEY_ROW1_KEY1                               KC_RALT    //                         ''
#         define _MOV_KEY_ROW1_KEY2                     MORE_key2            //                         ''
#         define _MOV_KEY_ROW1_KEY3           KC__YGUI                       //                         ''                 (etc)
#         define _MOV_KEY_ROW1_KEY4 KC_PGDN                                  
//                <|,>        ,         ,         ,         ,
//                 |, 4>      , 3>      , 2>      , ±       , 1>         // ± is the additional hardware key
#     endif                                                       

                                              /* 1 (triangle arrows with arrow cluster) */

// Patch in the arrows for arrow triangle layout
#     if defined(MOREKEY2_ARROW_CLUSTER) && defined(ARROWS_TRIANGLE)
//                                                                             Arrow cluster
#         define _MOV_KEY_ROW2_KEY2                     KC_UP                
//                                 ------------------------------------------
#         define _MOV_KEY_ROW1_KEY1                               KC_RIGHT   
#         define _MOV_KEY_ROW1_KEY2                     KC_DOWN              
#         define _MOV_KEY_ROW1_KEY3           KC_LEFT                        
//                <|,>        ,         ,         ,         ,
//                 |, 4>      , 3>      , 2>      , ±       , 1> 
#     endif

// The default layout around the arrows
#     if defined(MOREKEY2_ARROW_CLUSTER) && !defined(MOREKEY2_ADD_NAVIGATION) && defined(ARROWS_TRIANGLE)      
//                                                                             Default keys
#         define _MOV_KEY_ROW2_KEY1                               KC_RSFT    
#         define _MOV_KEY_ROW2_KEY3           RGHT_CD                        
#         define _MOV_KEY_ROW2_KEY4 RGHT_CC                                  
//                                 ------------------------------------------
#         define _MOV_KEY_ROW1_KEY4 KC_PGDN                                  
//                <|,>        ,         ,         ,         ,
//                 |, 4>      , 3>      , 2>      , ±       , 1> 
#    endif                                     
                                           
                                              /*  2 (  ''                  ''          + additional navigation and repositioning displaced keys) */

// Patch in the navigation keys for the arrow in triangle layout.
#     if defined(MOREKEY2_ADD_NAVIGATION) && defined(ARROWS_TRIANGLE)        // Navigation additional keys (arrows implied).
#         define _MOV_KEY_ROW2_KEY1                               KC_PGDN    
#         define _MOV_KEY_ROW2_KEY3           KC_PGUP                        
#         define _MOV_KEY_ROW2_KEY4 KC_HOME                                  
//                                 ------------------------------------------
#         define _MOV_KEY_ROW1_KEY4 KC_END                                   
//                    <|,>        ,         ,         ,         ,
//                     |, 4>      , 3>      , 2>      , ±       , 1>         
#     endif

// We have now overwritten the positions of RGHT_CC and RGHT_CD, which could be useful keys.
// You don't want to mess with BTN1 on the other hand, because it needs to select together with mouse moving in many applications.
#     if defined(MOREKEY2_ADD_NAVIGATION) && defined(ARROWS_TRIANGLE) && defined(ARROWS_LEFT)  // ARROWS_LEFT because the wider map is edited
//
//        ... spelling this out to keep brain for exploding:
//        Overwritten (copied from above):
//         #define RGHT_CC MOUS_33
//         #define                                 MOUS_33 KC_BTN4
//         #define RGHT_CD MOUS_34
//         #define                                                 MOUS_34 KC_BTN5
//        'BTN4' and 'BTN5' are overwritten.
//        Where are KC_BTN2 and KC_BTN3 on the non-mouse hand:
//         #define                                                                 NAVI_15 KC_BTN3
//         #define LEFT_AE NAVI_15
//         #define                                                                 NAVI_35 KC_BTN2
//         #define LEFT_CE NAVI_35
//        'LEFT_AE' and 'LEFT_CE' provide room.
//
#         undef  LEFT_AE
#         define LEFT_AE KC_BTN4
#         undef  LEFT_CE
#         define LEFT_CE KC_BTN5
#     endif

                                              /* 3 (flat arrows with arrow cluster) */

#     if defined(MOREKEY2_ARROW_CLUSTER) && !defined(ARROWS_TRIANGLE)
//                                                                         arrow cluster
#         define _MOV_KEY_ROW1_KEY1                               KC_RIGHT                                 
#         define _MOV_KEY_ROW1_KEY2                     KC_DOWN                        
#         define _MOV_KEY_ROW1_KEY3           KC_UP                
#         define _MOV_KEY_ROW1_KEY4 KC_LEFT    
//                    <|,>        ,         ,         ,         ,
//                     |, 4>      , 3>      , 2>      , ±       , 1> 
#     endif

// The default layout around the arrows
#     if defined(MOREKEY2_ARROW_CLUSTER) && !defined(MOREKEY2_ADD_NAVIGATION) && !defined(ARROWS_TRIANGLE)      
//                                                                         Default 
#         define _MOV_KEY_ROW2_KEY1                               KC_RSFT    
#         define _MOV_KEY_ROW2_KEY2                     RGHT_CE              // Key counting from the right to the left. 
#         define _MOV_KEY_ROW2_KEY3           RGHT_CD                        
#         define _MOV_KEY_ROW2_KEY4 RGHT_CC                                  
//                    <|,>        ,         ,         ,         ,
//                     |, 4>      , 3>      , 2>      , ±       , 1> 
#     endif


                                              /* 4 (   ''                  ''          + additional navigation and repositioning displaced keys) */

// The definitions for the additional navigation keys (HOME, etc)
#     if defined(MOREKEY2_ADD_NAVIGATION) && !defined(ARROWS_TRIANGLE)
//                                                                         Additional navigation keys: flat
#         define _MOV_KEY_ROW2_KEY1                               KC_PGDN                                  
#         define _MOV_KEY_ROW2_KEY2                     KC_END                         
#         define _MOV_KEY_ROW2_KEY3           KC_HOME              
#         define _MOV_KEY_ROW2_KEY4 KC_PGUP    
//                    <|,>        ,         ,         ,         ,
//                     |, 4>      , 3>      , 2>      , ±       , 1>         
#     endif

// Replace the overwritten key positions:
# if defined(MOREKEY2_ADD_NAVIGATION) && !defined(ARROWS_TRIANGLE) && !defined(ARROWS_LEFT)   // !ARROWS_LEFT because the wider map is edited
//
//        Overwritten (copied from above):
//         #define RGHT_CC NAVI_33
//         #define                                 NAVI_33 KC_ACL1
//         #define RGHT_CD NAVI_34
//         #define                                                 NAVI_34 KC_ACL2
//        'KC_ACL1' and 'KC_ACL2' are overwritten.
//        Where are BTN2 and BTN3 on the non-mouse hand:
//         #define NAVI_11 KC_BTN3
//         #define RGHT_AA NAVI_11
//         #define NAVI_31 KC_BTN2
//         #define RGHT_CA NAVI_31
//        'RGHT_AA' and 'RGHT_CA' provide room.
//         It seems best to count the acceleration keys from right to left/up on the keyboard.
//
#         undef  RGHT_AA
#         define RGHT_AA KC_ACL2
#         undef  RGHT_CA
#         define RGHT_CA KC_ACL1
#     endif

// Changes the home row on the right hand to become HJKL (as in Qwerty) vi(1) arrow keys,
// and causes the arrow block to move one key to the left. The key lost on the left is
// put back on the other end (pinky).
// Row 3
#     if defined(VI_SWITCHERYDOO) && !defined(ARROWS_TRIANGLE) // For all hardware variants
//                |, indx2>  , index>  , middl>   , ring>     , pinky>    , pink2>    ,
//               <|,>        ,         ,          ,           ,           ,           ,
#         undef  RGHT_BA
#         define RGHT_BA KC_LEFT
#         undef  RGHT_BB
#         define RGHT_BB           KC_DOWN
#         undef  RGHT_BC
#         define RGHT_BC                     KC_UP
#         undef  RGHT_BD
#         define RGHT_BD                                KC_RIGHT
#         undef  RGHT_BE
#         define RGHT_BE                                            KC_BTN1
#     endif
// Row 1
#     if defined(VI_SWITCHERYDOO) && !defined(ARROWS_TRIANGLE) && defined(MOREKEY2_ARROW_CLUSTER) // Only for 'arrow' hardware
//                                                                         arrow cluster
#         undef  _MOV_KEY_ROW1_KEY1 
#         define _MOV_KEY_ROW1_KEY1                               KC_RIGHT                                 
#         undef  _MOV_KEY_ROW1_KEY2
#         define _MOV_KEY_ROW1_KEY2                     KC_UP                          
#         undef  _MOV_KEY_ROW1_KEY3
#         define _MOV_KEY_ROW1_KEY3           KC_DOWN              
#         undef  _MOV_KEY_ROW1_KEY4
#         define _MOV_KEY_ROW1_KEY4 KC_LEFT    
//                    <|,>        ,         ,         ,         ,
//                     |, 4>      , 3>      , 2>      , ±       , 1>         
#     endif

// (If you want to alter something in detail just for your keyboard, it is probably smart to just write in the keycodes (like KC_PGUP) in the final definitions here below.)
//
//      <pink2   , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>             , ring>              , pinky>             , pink2>             ,
//               ,         ,         , -*-     ,         ,       <|,>        ,         ,                    ,                    ,                    ,                    ,
        CTO_BASE , LEFT_AA , LEFT_AB , LEFT_AC , LEFT_AD , LEFT_AE , RGHT_AA , RGHT_AB , RGHT_AC            , RGHT_AD            , RGHT_AE            , KC_BSPC            ,
        KC_LCTL  , LEFT_BA , LEFT_BB , LEFT_BC , LEFT_BD , LEFT_BE , RGHT_BA , RGHT_BB , RGHT_BC            , RGHT_BD            , RGHT_BE            , KC_RCTL            ,
        KC_LSFT  , LEFT_CA , LEFT_CB , LEFT_CC , LEFT_CD , LEFT_CE , RGHT_CA , RGHT_CB , _MOV_KEY_ROW2_KEY4 , _MOV_KEY_ROW2_KEY3 , _MOV_KEY_ROW2_KEY2 , _MOV_KEY_ROW2_KEY1 ,
//      --------------------------------------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT 
#     ifdef TRANSMINIVAN_LEFTSIDE
                , TRANS_LEFT
#     endif

#     ifdef MORE_KEY__COMMAND
                , MORE_key1 
#     endif

                , KC_DEL , KC_ENT 

#     ifndef SPACE_LEFT__ENTER_RIGHT      // standard, layer switch on Base
                                  , _______ 
#     else                                // reversed
                                  , KC_PGUP 
#     endif


#     ifdef TRANSMINIVAN_MIDLEFT
                                            , TRANS_MIDLEFT
#     endif


#     ifndef SPACE_LEFT__ENTER_RIGHT                // standard
                                            , KC_PGUP 
#     else                                          // reversed, layer switch on Base
                                            , _______ 
#     endif


#     ifdef TRANSMINIVAN_RIGHTSIDE
                                                      , TRANS_RIGHT
#     endif

                                                      , _MOV_KEY_ROW1_KEY4 , _MOV_KEY_ROW1_KEY3

#     ifdef MORE_KEY__ARROW
                                                                           , _MOV_KEY_ROW1_KEY2
#     endif
                                                                                                , _MOV_KEY_ROW1_KEY1
//            ,          ,        , -*-   <|,>        ,                    ,                    ,
//      <1 ±± , <2       , <3     , <4     |, 4>      , 3>                 , 2>                 , ±  ±  1>

                      ),

# endif // BASESFILE_LAYER_MOV

        /* ⬆⬇ */

# ifndef BASESFILE_LAYER_RAR // Use a definition of this layer in the ./bases_* file, where this #define can be defined.

    /* Layer _RAR: Various special keys.
     *          - The key which switches between Default and Alternate base layer.
     *          - Power keys
     *            The power keys have to be pressed with Shift, as a safety guard.
     *            Without shift they write their name, as if someone typed it.
     *          - Media keys
     *          - Brightness for screen keys (depends on computer system if it works)
     *          - Leds of keyboard on/off
     *          - Unicode input mode
     *            ☑  precedes the Unicode input modes, as memory aid and tester
     *               Note that ☑ has no letters in its Unicode, but press with Shift for 🗹 
     *               which does. This matters when testing ‛descramble’ Dvorak mode.
     *          - Capslock is on its normal position
     *          - Insert
     *          - APP (whatever it is) fakes being next to right GUI (though other layer).
     *          - The traditional obsolete button like ScrLk/PrtSc are also included, in
     *            case some program needs them.
     *          - Speed measuring
     *          - Text size measuring
     *          - Some unused spots remaining.
     */

    [ _RAR ] = LAYOUT_redefined (

/*
     _RAR (RARe keys. Power keys, Unicode mode, Alternate BASE, Media, Brightness, Speed, leds, …)
    
     <pink2<pinky <ring <middl <indexx<indx2| indx2>index>middl>ring> pinky> pink2>
                                           <|>      -*-                                //(toggle) on _FUN
     BASE  Cnt/Mx Cnull CWmin  CRprt  Speed | SRprt Play  Next  Prev  Stop RSht(•)   
     CapsL Power• Wake• Sleep• Pause• ScrLk | PrtSc xxx   Vol+  Vol-  Mute Insert     // • requires Shift
     ☑     uLNX   uBSD  uOSX   uWIN   uWNC  | xxx   xxx   Bri+  Bri-  xxx     APP     // Ü(nicode) tester
     ----------------------------------------------------------------------------
     SLed  MLeds RGUI  xxx  | !Alter  xxx   LGUI  ___            // Middle-led, Side-leds, ! 'alternate'
                           <|>                    -*-                                   // (Hold) on BASE
     <1 ±  <2  ± <3    <4   | 4>      3>    2>  ± 1>  
        …                                       …
 */
//
//      <pink2    , <pinky           , <ring            , <middl           , <index           , <indx2           |, indx2>        , index>  , middl>           , ring>              , pinky>  , pink2>        ,
//                ,                  ,                  ,                  , -*-              ,                 <|,>              ,         ,                  ,                    ,         ,               ,
        CTO_BASE  , COUNT_TOG        , COUNT_NULL       , COUNT_WORDMIN    , COUNT_REPORT     , SPEED_TOG         , SPEED_REPORT  , KC_MPLY , KC_MNXT          , KC_MPRV            , KC_MSTP , KC_RSFT       ,
        KC_CAPS   , C_KC_PWR         , C_KC_WAKE        , C_KC_SLEP        , C_KC_PAUS        , KC_SCRL           , KC_PSCR       , XXXXXXX , KC_VOLU          , KC_VOLD            , KC_MUTE , KC_INS        ,
        XP_DRA_CG , UC_LINX          , UC_BSD           , UC_MAC           , UC_WIN           , UC_WINC           , XXXXXXX       , XXXXXXX , KC_BRIGHTNESS_UP , KC_BRIGHTNESS_DOWN , XXXXXXX , KC_APP        ,
//      -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        LEDS_ON  
#     ifdef TRANSMINIVAN_LEFTSIDE
                , TRANS_LEFT
#     endif

#     ifdef MORE_KEY__COMMAND
                , MORE_key1
#     endif

#     ifdef LEDS_OFF_BASE_DEF  // This messes with led effect on/off, so we need to track the state of this setting now.
                , RGBTOG_ 
#     else                     // Here we don't mess with led effect on/off, so we can use QMK key blindly.
                , RGB_TOG
#     endif
                          , KC__XGUI , XXXXXXX 

#     ifdef TRANSMINIVAN_MIDLEFT
                                               , TRANS_MIDLEFT
#     endif

                                               , OTHER_BASE , XXXXXXX 

#     ifdef TRANSMINIVAN_RIGHTSIDE
                                                                      , TRANS_RIGHT
#     endif                                                           
                                                                      
                                                                      , KC__YGUI
                                                                      
#     ifdef MORE_KEY__ARROW                                           
                                                                      , MORE_key2  
#     endif                                                           
                                                                                 , _______
//              ,         ,          ,       <|,>        ,            ,          ,
//      <1 ± ±  , <2      , <3       , <4     |, 4>      , 3>         , 2>       , ±  ±  1>

                      ),

# endif // BASESFILE_LAYER_RAR

        /* ⬆⬇ */

# ifndef REMOVE_PAD // This removes all references to _PAD in the code, therefore is not functionally the same as BASESFILE_LAYER_PAD

#     ifndef BASESFILE_LAYER_PAD // Use a definition of this layer in the ./bases_* file, where this #define can be defined.

#         ifndef NUMPAD_COMMON_SQUARE // Use default _PAD layer, where numbers are aligned as they are on _NSY.
                                  // Conversely, if this is defined, this layer will resembel a numeric keypad.
                                  // See also base_numpad.c 

    /* Layer _PAD: Numbers pad, for numbers pad version of numbers (computer programs can see the difference).
     *             Number pad navigation will be more or less useless, but there is a repetition of the Numpad
     *             keys 4,2,8,6 row 4 for arrows, and 3,1,7,9 row 2 for navigation, to make it a little easier to find.
     */

    [ _PAD ] = LAYOUT_redefined (

/*
     Layer _PAD Numbers Pad (special symbol versions; regular '1' is not the same as this numpad '1', etc)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                    -*-                    <|>                                         //(toggle) on _FUN
     BASE     xxx   xxx   .DEL  4LEFT 2DOWN | 8UP   6RGHT *     xxx   xxx      Bksp
     LCtl     1END  2DOWN 3PGDN 4LEFT 5     | 6RGHT 7HOME 8UP   9PGUP 0INS        -
     LSht     xxx   xxx   /     xxx   =     | +     3PGDN 1END  7HOME 9PGUP    RSht
     -*---------------------------------------------------------------------------- //-*-  toggle on BASE
     LAlt     Del   Tab   ENT  |  NUML  xxx   LGUI  RAlt
                              <|>
     <1   ±   <2    <3    <4   |  4>    3>    2>  ± 1>  
          …                                       …

 */

//
//      <pink2   , <pinky  , <ring   , <middl      , <index  , <indx2     |, indx2>     , index>  , middl>         , ring>   , pinky>  , pink2>      ,
//               ,         ,         ,             ,         , -*-       <|,>           ,         ,                ,         ,         ,             ,
        CTO_BASE , XXXXXXX , XXXXXXX , KC_KP_DOT   , KC_KP_4 , KC_KP_2     , KC_KP_8    , KC_KP_6 , KC_KP_ASTERISK , XXXXXXX , XXXXXXX , KC_BSPC     ,
        KC_LCTL  , KC_KP_1 , KC_KP_2 , KC_KP_3     , KC_KP_4 , KC_KP_5     , KC_KP_6    , KC_KP_7 , KC_KP_8        , KC_KP_9 , KC_KP_0 , KC_KP_MINUS ,
        KC_LSFT  , XXXXXXX , XXXXXXX , KC_KP_SLASH , XXXXXXX , KC_KP_EQUAL , KC_KP_PLUS , KC_KP_3 , KC_KP_1        , KC_KP_7 , KC_KP_9 , KC_RSFT     ,
//      ----------------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT 

#             ifdef TRANSMINIVAN_LEFTSIDE
                , _______ // On Base layers this key typically defaults to MO ( _PAD )
#             endif

#             ifdef MORE_KEY__COMMAND
                , MORE_key1
#             endif

                , KC_DEL , KC_TAB , KC_KP_ENTER

#             ifdef TRANSMINIVAN_MIDLEFT
                                                , TRANS_MIDLEFT
#             endif

                                                , KC_NUM , XXXXXXX , KC__YGUI

#             ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                  , TRANS_RIGHT
#             endif

#             ifdef MORE_KEY__ARROW
                                                                                  , MORE_key2  
#             endif

                                                                                  , KC_RALT
//              ,        ,        ,           <|,>           ,         ,          ,
//      <1  ± ± , <2     , <3     , <4         |, 4>         , 3>      , 2>       , ±  ±  1>

                      ),

#         else // NUMPAD_COMMON_SQUARE 

    [ _PAD ] = LAYOUT_redefined (

/*
     
     * Layer _PAD: Option for a different _PAD layer in the common layers system.
     *             This variety resembles the square layout of a numerical keyboard.
     *             It is different from one of the Numpad Base layer compile options, in that
     *             it only has a number pad for the right hand. It is also different in featuring
     *             modifiers, and the overall layout is sligthly different (Enter, = symbol).
     *
     *             ‛Tab’ on key 3 left hand is the same as the other _PAD layer option (with the
     *             numbers in a line, equal to the _NSY layer), to retain the same ability to
     *             type Control-Tab. It seems better to have RAlt in its usual place, Enter in
     *             its usual place, than to strictly follow a standard numeric keyboard layout
     *             (which puts Enter somewhere on the right, row 1). It seems easy enough to
     *             type Enter on this key as well, even with the right hand. Numlock is also
     *             in its usual place. Note that ‛Del’ on the left, row 1, is not a numbers pad
     *             Delete/Dot key, but standard Delete, also in the usual place.
     *
     *             This is probably the better one of the square layout numpads, unless you have a use
     *             for the two hands version. This is also available on ‛Base’ Numpad.
     * 
     
     Layer _PAD (Number pad, with NumLock on)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     BASE     xxx   xxx   xxx   xxx   xxx   | =     7     8     9    -   Bspc
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     4     5     6    +   RCtl
     LSht     xxx   xxx   xxx   xxx   xxx   | /     1     2     3    ,   RSht  
     ------------------------------------------------------------------------
                   LAlt   Del    Tab   Ent  | NumL  0     .     RAlt      
                                           <|>           
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                        …                   |                 …           

     Layer _PAD (Number pad, with NumLock off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring >pin>pink2>
                                           <|>
     BASE     xxx   xxx   xxx   xxx   xxx   | =     Home  Up    PgUp  -   Bspc
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     Left  5     Right +   RCtl
     LSht     xxx   xxx   xxx   xxx   xxx   | /     End   Down  PgDn  ,   RSht  
     -------------------------------------------------------------------------
                   LAlt   Del    Tab   Ent  | NumL  Ins   Del   RAlt      
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                        …                   |                 …           
 
*/

//
//      <pink2   , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>         , index>  , middl>  , ring>   , pinky>      , pink2>  ,
//               ,         ,         ,         ,         , -*-   <|,>               ,         ,         ,         ,             ,         ,
        CTO_BASE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_EQUAL    , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_KP_MINUS , KC_BSPC ,
        KC_LCTL  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_ASTERISK , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_KP_PLUS  , KC_RCTL ,
        KC_LSFT  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_SLASH    , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_KP_COMMA , KC_RSFT ,
//      -----------------------------------------------------------------------------------------------------------------------------------
        KC_LALT 

#             ifdef TRANSMINIVAN_LEFTSIDE
                , TRANS_LEFT  
#             endif

#             ifdef MORE_KEY__COMMAND
                , MORE_key1
#             endif

                , KC_DEL     , KC_TAB , KC_KP_ENTER  

#             ifdef TRANSMINIVAN_MIDLEFT
                                                    , TRANS_MIDLEFT
#             endif

                                                    , KC_NUM , KC_KP_0 

// See comment in ./base_numpad.c on the first layout (double handed Base layer), about the next few keys:
// This layer follows that layout Base Numpad.
// ---⬇

#     ifdef TRANSMINIVAN_RIGHTSIDE
                                                                           , TRANS_RIGHT   
#     endif                                                                                     
                                                                                            
#     ifdef MORE_KEY__ARROW                                                                     
                                                                         //, MORE_key2   
                                                                           , KC__YGUI
#     endif                                                                                           
// ---⬆
                                                                           , KC_KP_DOT  

                                                                                       , KC_RALT
//              ,            ,        ,           <|,>           ,         ,           ,
//      <1  ± ± , <2         , <3     , <4         |, 4>         , 3> ± ±  , 2>        ,       1>

                      ),


#         endif // NUMPAD_COMMON_SQUARE 

#     endif // BASESFILE_LAYER_PAD

# endif // REMOVE_PAD

        /* ⬆⬇ */

# ifndef REMOVE_ACC // This cuts out the whole _ACC layer.

#     ifndef BASESFILE_LAYER_ACC // Use a definition of this layer in the ./bases_* file, where this #define can be defined.

    /* Layer _ACC: Accented and other unusual characters. It seems this would
     *             cover Dutch, German, French, Scandinavia, Italy and Spain.
     *          It should helps with remembering what keys are where, if one
     *             knows the logic behind it (however flawed it might be).
     *          This layer has the uncluttered Tab key (whoohoo!).
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
     */ 

    [ _ACC ] = LAYOUT_redefined (

/*
     Layer _ACC (ACCented characters, see _RAR layer for input modes)
    
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                       -*-              <|>                                            //(toggle) on _FUN
     BASE      áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bksp
     RCTL(Tab) äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß       μ
     LSht      àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     ----------------------------------------------------------------------------
     LAlt ___   ___   Ent  | Spc   ___   ___   RAlt 
          -*-             <|>                                                            //(hold) on BASE
     <1 ± <2    <3    <4   | 4>    3>    2>  ± 1>  
        …                                    …
 */
//
//      <pink2          , <pinky    , <ring     , <middl    , <index    , <indx2   |, indx2>    , index>    , middl>    , ring>     , pinky>    , pink2>    ,
//                      ,           ,           ,           ,           ,         <|,>-*-       ,           ,           ,           ,           ,           ,
        CTO_BASE        , XP_ACC_AA , XP_ACC_AB , XP_ACC_AC , XP_ACC_AD , XP_ACC_AE , XP_ACC_AF , XP_ACC_AG , XP_ACC_AH , XP_ACC_AI , XP_ACC_AJ , KC_BSPC   ,
        LCTL ( KC_TAB ) , XP_ACC_BA , XP_ACC_BB , XP_ACC_BC , XP_ACC_BD , XP_ACC_BE , XP_ACC_BF , XP_ACC_BG , XP_ACC_BH , XP_ACC_BI , XP_ACC_BJ , XP_ACC_BK , 
        KC_LSFT         , XP_ACC_CA , XP_ACC_CB , XP_ACC_CC , XP_ACC_CD , XP_ACC_CE , XP_ACC_CF , XP_ACC_CG , XP_ACC_CH , XP_ACC_CI , XP_ACC_CJ , KC_RSFT   ,
//      ----------------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT 
#         ifdef TRANSMINIVAN_LEFTSIDE
                        , TRANS_LEFT
#         endif

#         ifdef MORE_KEY__COMMAND
                        , MORE_key1
#         endif

                        , _______ , _______ , KC_ENT  

#     ifdef TRANSMINIVAN_MIDLEFT
                                                     , TRANS_MIDLEFT
#     endif

                                                     , KC_SPC , _______ , _______ 

#         ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                  , TRANS_RIGHT
#         endif                                              
                                                             
#         ifdef MORE_KEY__ARROW                              
                                                                                  , MORE_key2  
#         endif                                              
                                                             
                                                                                  , KC_RALT
//              , -*-     ,         ,      <|,>               ,         ,         , 
//      <1 ± ±  , <2      , <3      , <4    |, 4>             , 3>      , 2>      , ±  ±  1>

                      ),

#     endif // BASESFILE_LAYER_ACC

# endif // REMOVE_ACC

        /* ⬆⬇ */

# ifndef REMOVE_DRA // This cuts out the whole _DRA layer

#     ifndef BASESFILE_LAYER_DRA // Use a definition of this layer in the ./bases_* file, where this #define can be defined.

    /* Layer _DRA: Drawings, like various Unicode symbols.
     *   
     */

    [ _DRA ] = LAYOUT_redefined (

/*
     Layer _DRA (DRAwings, whatever else (rendering width varies in different applications))
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                             -*-        <|>                                            //(toggle) on _FUN
     BASE  “„    ”≤    £≥    ∅ ¢   ±ƒ    | ❦♥    🙂🙁  👍👎   ⁽₍    ⁾₎    Bksp
     Tab   ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCTL
     LSht 「━    」─   °〇   •§    …·    | ⮘⮙   ⮚⮛     ¿¡    《┄    》┅   RSht
     -------------------------------------------------------------------------
     LAlt ___   ___   Ent  | Spc   ___   ___   RAlt 
                -*-       <|>      -*-                                                   //(hold) on BASE
     <1 ± <2    <3    <4   | 4>    3>    2>  ± 1>  
        …                                    …
 */
//
//      <pink2   , <pinky    , <ring     , <middl    , <index    , <indx2   |, indx2>    , index>    , middl>    , ring>     , pinky>    , pink2>  ,
//               ,           ,           ,           ,           ,         <|,>          , -*-       ,           ,           ,           ,         ,
        CTO_BASE , XP_DRA_AA , XP_DRA_AB , XP_DRA_AC , XP_DRA_AD , XP_DRA_AE , XP_DRA_AF , XP_DRA_AG , XP_DRA_AH , XP_DRA_AI , XP_DRA_AJ , KC_BSPC ,
        KC_TAB   , XP_DRA_BA , XP_DRA_BB , XP_DRA_BC , XP_DRA_BD , XP_DRA_BE , XP_DRA_BF , XP_DRA_BG , XP_DRA_BH , XP_DRA_BI , XP_DRA_BJ , KC_RCTL ,
        KC_LSFT  , XP_DRA_CA , XP_DRA_CB , XP_DRA_CC , XP_DRA_CD , XP_DRA_CE , XP_DRA_CF , XP_DRA_CG , XP_DRA_CH , XP_DRA_CI , XP_DRA_CJ , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT 

#         ifdef TRANSMINIVAN_LEFTSIDE
                , TRANS_LEFT
#         endif

#         ifdef MORE_KEY__COMMAND
                , MORE_key1
#         endif

                , _______ , _______ , KC_ENT

#     ifdef TRANSMINIVAN_MIDLEFT
                                             , TRANS_MIDLEFT
#     endif

                                             , KC_SPC , _______ , _______ 

#         ifdef TRANSMINIVAN_RIGHTSIDE
                                                                          , TRANS_RIGHT
#         endif

#         ifdef MORE_KEY__ARROW
                                                                          , MORE_key2  
#         endif                          

                                                                          , KC_RALT
//              ,         ,         ,      <|,>       ,         ,         ,
//      <1 ± ±  , <2      , <3      , <4    |, 4>     , 3>      , 2>      , ±  ±  1>

                      ),

#     endif // BASESFILE_LAYER_RAR

# endif // REMOVE_DRA

        /* ⬆⬇ */

# ifndef REMOVE_BON // Removes this layer entirely, if set.

#     ifndef BASESFILE_LAYER_BON // Use a definition of this layer in the ./bases_* file, where this #define can be defined.

/* 
 * Bonus layer: Enumeration numbers, some general purpose / mathematical symbols
 * ⁻ is an exponential minus sign (the center-dot · can be used in exponents too)
 * × is multiplication
 * ‰ is promille, ‱ is pro-tenthousandth
 * 
 */

    [ _BON ] = LAYOUT_redefined (

/* 
     Layer _BON (Bonus layer, a variety of more stuffs.)

     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                   -*-  <|>
     BASE  ‛ 🛠  ’ ⬆   ¤ 🄯   ∑ ©   ‰ ‱   | ★ ٭   😊 ⍨  ×  ⃰   √     ⁻ ⁺    Bksp
     `~    ① ⬅   ② ⬇   ③ ➡   ④ ┏   ⑤  ┓  | ⑥ ┃   ⑦ ┇   ⑧ ╋   ⑨     ⓪ ∞    — ≈    // — is a dash (larger), not hyphen
     LSht  ‹     ›     ÷     ☞ ┗   ≠  ┛  | ✗ ┣   ✓ ┫   ⚠     «     »      RSht
     -------------------------------------------------------------------------
     Left  ___   ___   Ent  | Spc   ___   ___   Right
           -*-   -*-       <|>      -*-                                                   // Activation on BASE
     <1  ± <2    <3    <4   | 4>    3>    2>  ± 1>  
         …                                    …
 */
//
//      <pink2      , <pinky    , <ring     , <middl    , <index    , <indx2   |, indx2>    , index>    , middl>    , ring>     , pinky>    , pink2>    ,
//                  ,           ,           ,           ,           ,         <|,>          ,           ,           ,           ,           ,           ,
        CTO_BASE    , XP_BON_AA , XP_BON_AB , XP_BON_AC , XP_BON_AD , XP_BON_AE , XP_BON_AF , XP_BON_AG , XP_BON_AH , XP_BON_AI , XP_BON_AJ , KC_BSPC   ,
        KC_GRV      , XP_BON_BA , XP_BON_BB , XP_BON_BC , XP_BON_BD , XP_BON_BE , XP_BON_BF , XP_BON_BG , XP_BON_BH , XP_BON_BI , XP_BON_BJ , XP_BON_BK ,
        KC_LSFT     , XP_BON_CA , XP_BON_CB , XP_BON_CC , XP_BON_CD , XP_BON_CE , XP_BON_CF , XP_BON_CG , XP_BON_CH , XP_BON_CI , XP_BON_CJ , KC_RSFT   ,
//      -------------------------------------------------------------------------------------------------------------------------------------------------
        KC_LEFT 

#         ifdef TRANSMINIVAN_LEFTSIDE
                , TRANS_LEFT
#         endif

#         ifdef MORE_KEY__COMMAND
                , MORE_key1
#         endif                 

                , _______ , _______ , KC_ENT

#     ifdef TRANSMINIVAN_MIDLEFT
                                             , TRANS_MIDLEFT
#     endif

                                             , KC_SPC , _______ , _______

#         ifdef TRANSMINIVAN_RIGHTSIDE
                                                                          , TRANS_RIGHT
#         endif

#         ifdef MORE_KEY__ARROW                    
                                                                          , MORE_key2  
#         endif                                                                                           
                                                                          , KC_RIGHT
//              ,         ,         ,      <|,>       ,         ,         ,
//      <1  ± ± , <2      , <3      , <4    |, 4>     , 3>      , 2>      , ± ± 1>

                      ),

#     endif // BASESFILE_LAYER_BON

# endif // REMOVE_BON 

        /* ⬆⬇ */
                          
# ifndef BASESFILE_LAYER_FUN // Use a definition of this layer in the ./bases_* file, where this #define can be defined.

    /* Layer _FUN: Function keys until F20. Some combo modifiers control/alt/shift
     * Toward any layer by toggle. Layer can be set to return to BASE after one F-key press (FUN<, row 1)
     */

    [ _FUN ] = LAYOUT_redefined ( 

/*
     Layer _FUN (F-keys, Layer access, Set BASE key direction)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl set   toggl toggl toggl | toggl toggl                            // Type of layer switch
                                        <|>                                       
     BASE: NUMS: _PAD  _ACC  _DRA  _BON  | _MOV  _RAR  xxx   xxx   xxx    Bksp       //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10    RCtl
     LSht  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20    RSht     
     ----------------------------------------------------------------------*--       //-*-  toggle on BASE
     LAlt  LCtl&  LCtl&  LSht&  | FUN< +LCtl&LSht LGUI   RAlt                        //... < toggle 'stay'
           LSht   LAlt   LAlt   |      &LAlt                                    
           +xxx   +xxx   +xxx   |      +xxx
                               <|>
     <1  ± <2     <3     <4     | 4>   3>         2>  ±  1>                
         …                                            …
 */
//
//      <pink2   , <pinky   , <ring       , <middl   , <index   , <indx2    |, indx2>      , index>      , middl>  , ring>   , pinky>  , pink2>  ,
//               ,          , -*-         ,          ,          ,          <|,>            ,             ,         ,         ,         ,         ,
        CTO_BASE , CTO_NUMS , TO ( _PAD ) , CTO_ACCE , CTO_DRAW , TO ( _BON ), TO ( _MOV ) , TO ( _RAR ) , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC ,
        KC_LCTL  , KC_F1    , KC_F2       , KC_F3    , KC_F4    , KC_F5      , KC_F6       , KC_F7       , KC_F8   , KC_F9   , KC_F10  , KC_RCTL ,
        KC_LSFT  , KC_F11   , KC_F12      , KC_F13   , KC_F14   , KC_F15     , KC_F16      , KC_F17      , KC_F18  , KC_F19  , KC_F20  , KC_RSFT ,
//      ------------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT 
#     ifdef TRANSMINIVAN_LEFTSIDE
                , TRANS_LEFT
#     endif

#     ifdef MORE_KEY__COMMAND
                , MORE_key1
#     endif

                , MT ( MOD_LCTL | MOD_LSFT, XXXXXXX ) , MT ( MOD_LCTL | MOD_LALT , XXXXXXX ) , MT ( MOD_LSFT | MOD_LALT , XXXXXXX )

#     ifdef TRANSMINIVAN_MIDLEFT
                                                                                                                                    , TRANS_MIDLEFT
#     endif

                                                                                                                                    , _FUN_STAY , MT ( MOD_LCTL | MOD_LSFT | MOD_LALT , XXXXXXX ) , KC__YGUI

#     ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                                                                                                                             , _______ // On Base layers this key typically defaults to MO ( _FUN )
#     endif

#     ifdef MORE_KEY__ARROW
                                                                                                                                                                                                             , MORE_key2  
#     endif
                                                                                                                                                                                                             , KC_RALT
//              ,                                     ,                                      ,                                    <|,>          ,                                                 ,          ,
//      <1 ± ±  , <2                                  , <3                                   , <4                                  |, 4>        , 3>                                              , 2>       , ±  ±  1>

                      ),

# endif // BASESFILE_LAYER_FUN

        /* ⬆  */


/*
 * New layer template. Includes left/right movement arrows, deletion, modifiers.
 * If you want a new layer, in the logic of this layout you would add a toggle on the
 * _FUN layer top row on the first free key to it, and optionally alter the hold 
 * layer switch keys on the base layers. (Check if a new layer will fit on the chip.)
 *
    [ _??? ] = LAYOUT_redefined (

// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                    <|>
// BASE  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx    Bksp
// LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx    RCtl
// LSht  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx    RSht
// -------------------------------------------------------------------------
// LAlt+Left Del   ___   Ent  | Spc   ___   ___   RAlt+Right
//                           <|>
// <1   ±    <2    <3    <4   | 4>    3>    2>  ± 1>  
//      …                                       …
//
//
//      <pink2   , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//               ,         ,         ,         ,         ,       <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC ,
        KC_LCTL  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RCTL ,
        KC_LSFT  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RSFT ,
//      ------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) 

# ifdef TRANSMINIVAN_LEFTSIDE
                           , TRANS_LEFT
# endif

# ifdef MORE_KEY__COMMAND
                           , MORE_key1
# endif                 

                           , KC_DEL , XXXXXXX , KC_ENT

#     ifdef TRANSMINIVAN_MIDLEFT
                                                       , TRANS_MIDLEFT
#     endif

                                                       , KC_SPC , XXXXXXX , XXXXXXX

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                    , TRANS_RIGHT
# endif

# ifdef MORE_KEY__ARROW
                                                                                    , MORE_key2  
# endif                                                                                          

                                                                                    , RALT_T ( KC_RIGHT )
//                         ,        ,         ,      <|,>       ,         ,         ,
//      <1      ± ±        , <2     , <3      , <4    |, 4>     , 3>      , 2>      , ± ± 1>

                      ),
*/

};

