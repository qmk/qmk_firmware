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

 * Author: © 2019, 2020 by Jos Boersema
 *
 */

/* This file contains mostly the Unicode and special macros.
   It contains the function: process_record_user(...)
 */

#include "./unicode_macros.h"
#include "./unicode_weurope.h"
#include "./unicode_hebrew.h"

// Definition of ƒ (Dutch currency symbol).
// Best changed in user_config.h, if you like a Euro symbol instead.
//
# ifndef UNICODE_CURRENCY // Prior optional definition in user_config.h
#     define UNICODE_CURRENCY 0x0192 // Hex number. The unicode hex number for position ƒ in the default keymap.
# endif

//
// 🛠
#define CS_USER_DEFINED 0x1F6E0 // Hammer & wrench (place holder). 

#define DIV10POINT TRUE // suggest to function write_number, to divide by 10 and print as a fraction: N.N

// Gives Unicode code points to the relevant QMK functions.
// Handles Dvorak 'descramble' Unicode mode, if compiled (only tested on Linux).
void unicode_hex2output (long unsigned int unshifted, long unsigned int shifted) {

    long unsigned int input; // which argument to work on

# ifdef DVORAK_DESCRAMBLE // Do the letter descramble if needed.

    char output[10]; // will hold the ascii for output
    int index; // count backwards 'to left' in the string
    long unsigned int bitmove; // move computation to next digit.
    long unsigned int work; // temporary value for computation

# endif

    // What to work on
    if(shift_ison) input = shifted; // Trying to get everything possible here in this function, to reduce firmware size.
    else input = unshifted;

# ifndef DVORAK_DESCRAMBLE // Only normal mode

    register_unicode ( (uint32_t) input ) ;

# else

    if(_FULL_ != alternate){ 

        register_unicode ( (uint32_t) input ) ; // normal Unicode mode

    }else{  // Special Dvorak-descramble mode: 0-9=0-9, a=a, b=n, c=i, d=h, e=d, f=y 
    
        // Take the hex value 4 bits at a time, starting with the least significant, convert to ascii, store
        index = 9;
        output[index] = '\0'; // terminator
        bitmove = 0x1; 
        while ((work = (input / bitmove)) && (index >= 0)) {
            index --;
            work &= 0xF; 
            if (work < 0xA){  // numbers
                output[index] = work + 0x30; // pad to ASCII
            }else{            // alphas
                if (0xA == work) output[index] = 'a';
                if (0xB == work) output[index] = 'n';
                if (0xC == work) output[index] = 'i';
                if (0xD == work) output[index] = 'h';
                if (0xE == work) output[index] = 'd';
                if (0xF == work) output[index] = 'y';
            }
            bitmove *= 0x10; // next digit
        }
    
        SEND_STRING ( SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) "f" SS_UP(X_LSHIFT) SS_UP(X_LCTRL) ); // lead-in for Unicode on Linux, 'descramble' mode
        send_string (output + index); // pointer to argument with formatted string
        SEND_STRING ( " " ); // Ends the Unicode numerical input mode
    }

# endif // DVORAK_DESCRAMBLE mode for that Base layer & mode setting is compiled in

} 


// Wrapper for unicode keys that do have the same on shift.
void unicode_hex2output_single (long unsigned int either) {
    unicode_hex2output (either, either);
}


// Required by QMK Unicode
const uint32_t PROGMEM unicode_map[] = {

};

// Macro name definitions. The Unicode layers _ACC, _DRA and _BON are defined here,
// because the Unicode map system does not have enough space (at time of this programming, year 2020).
enum custom_keycodes {

    // Macro, allowing the upper left button to switch to either _DEF_BASE base layer, or the _ALT_BASE base layer.
    // Alternate is set on/half/off in the _RAR layer. The word "base" is used to avoid "default," because the default
    // layer system call DF() is not being used.
    CTO_BASE = SAFE_RANGE, // 'C' for costum, "TO" for to, "BASE" for chosen base layer

    OTHER_BASE, // cycles modes: use _DEF_BASE, _ALT_BASE. For “dvorak²” layout (descramble) compile option, there is a third mode.

# if defined(BASE_NUMPAD__ALT_BASE)
    OTHER_BASE_GO, // Like OTHER_BASE, but also immediately switches to the other BASE layer.
# endif

    CTO_NUMS, // activates number-symbols layer, taking into account the dual layout mode
    CTO_ACCE, //             accented        '' 
    CTO_DRAW, //             drawings        ''

# ifndef CHOLTAP_ACCE_NOP
    CHOLTAP_ACCE, // Go to accented layer, or others in combination with other keys.
# endif 

// Keys can be pressed together for a separate layer (like 'adjust layer' on the Planck).
    DUO_HOLD,

    CHOLTAP_RSHFT, // Go to _FUN layer, or shift modifier.
    CHOLTAP_LSHFT, // Go to <configurable> layer, or shift modifier.
    CHOLTAP_LAYR,  // Go to _RAR layer, or right arrow 

// Shifts which on tap produce a key

   RSFT_TILDE,
   LSFT_DASH,

// Special macro to make F-keys one-shot or not.
    _FUN_STAY,

// Layer toggle to be guaranteed on up-key, therefore macro definition here.
    _MOV_UP,

// These macros protect the critical keys like 'Power' from accidental press, by needing Shift to be pressed.
    C_KC_PWR,  // Powers computer off.
    C_KC_WAKE,
    C_KC_SLEP, // sleep computer
    C_KC_PAUS, // pauze computer

// Toggles side leds on/off. 
    LEDS_ON,
    RGBTOG_, 

// Typing speed measuring 
    SPEED_TOG,
    SPEED_REPORT,

// Word/character counting
    COUNT_TOG,     // starts word counting
    COUNT_REPORT,  // writes to the computer as if typing, gives count report
    COUNT_WORDMIN, // reduces the word count
    COUNT_NULL,    // resets count to zero
    LT__MOV__KC_ENT, // move to layer _MOV, or <enter>

// The _ACC layer, additional Unicode.
# ifndef REMOVE_ACC // This cuts out the whole _ACC layer.
    XP_ACC_AA,
    XP_ACC_AB,
    XP_ACC_AC,
    XP_ACC_AD,
    XP_ACC_AE,
    XP_ACC_AF,
    XP_ACC_AG,
    XP_ACC_AH,
    XP_ACC_AI,
    XP_ACC_AJ,
    XP_ACC_BA,
    XP_ACC_BB,
    XP_ACC_BC,
    XP_ACC_BD,
    XP_ACC_BE,
    XP_ACC_BF,
    XP_ACC_BG,
    XP_ACC_BH,
    XP_ACC_BI,
    XP_ACC_BJ,
    XP_ACC_BK,
    XP_ACC_CA,
    XP_ACC_CB,
    XP_ACC_CC,
    XP_ACC_CD,
    XP_ACC_CE,
    XP_ACC_CF,
    XP_ACC_CG,
    XP_ACC_CH,
    XP_ACC_CI,
    XP_ACC_CJ,
# endif // REMOVE_ACC 

# ifndef REMOVE_DRA // This cuts out the whole _DRA layer
// The _DRA layer, additional Unicode.
    XP_DRA_AA,
    XP_DRA_AB,
    XP_DRA_AC,
    XP_DRA_AD,
    XP_DRA_AE,
    XP_DRA_AF,
    XP_DRA_AG,
    XP_DRA_AH,
    XP_DRA_AI,
    XP_DRA_AJ,
    XP_DRA_BA,
    XP_DRA_BB,
    XP_DRA_BC,
    XP_DRA_BD,
    XP_DRA_BE,
    XP_DRA_BF,
    XP_DRA_BG,
    XP_DRA_BH,
    XP_DRA_BI,
    XP_DRA_BJ,// XP_DRA_BK , // no 'BK' key definition on this layer
    XP_DRA_CA,
    XP_DRA_CB,
    XP_DRA_CC,
    XP_DRA_CD,
    XP_DRA_CE,
    XP_DRA_CF,
# endif // REMOVE_DRA
    XP_DRA_CG, // Needed for ☑ on Unicode tester key in _RAR
# ifndef REMOVE_DRA // This cuts out the whole _DRA layer
    XP_DRA_CH,
    XP_DRA_CI,
    XP_DRA_CJ,
# endif // REMOVE_DRA

// The _BON layer, additional Unicode.
# ifndef REMOVE_BON // Removes this layer entirely, if set.
    XP_BON_AA,
    XP_BON_AB,
    XP_BON_AC,
    XP_BON_AD,
    XP_BON_AE,
    XP_BON_AF,
    XP_BON_AG,
    XP_BON_AH,
    XP_BON_AI,
    XP_BON_AJ,
    XP_BON_BA,
    XP_BON_BB,
    XP_BON_BC,
    XP_BON_BD,
    XP_BON_BE,
    XP_BON_BF,
    XP_BON_BG,
    XP_BON_BH,
    XP_BON_BI,
    XP_BON_BJ,
    XP_BON_BK,
    XP_BON_CA,
    XP_BON_CB,
    XP_BON_CC,
    XP_BON_CD,
    XP_BON_CE,
    XP_BON_CF,
    XP_BON_CG,
    XP_BON_CH,
    XP_BON_CI,
    XP_BON_CJ,
# endif // REMOVE_BON 

// Hebrew
# if defined(BASE_HEBREW__DEF_BASE) || defined(BASE_HEBREW__ALT_BASE)
    XP_HEB_AA,
    XP_HEB_AB,
    XP_HEB_AC,
    XP_HEB_AD,
    XP_HEB_AE,
    XP_HEB_AF,
    XP_HEB_AG,
    XP_HEB_AH,
    XP_HEB_AI,
    XP_HEB_AJ,
    XP_HEB_BA,
    XP_HEB_BB,
    XP_HEB_BC,
    XP_HEB_BD,
    XP_HEB_BE,
    XP_HEB_BF,
    XP_HEB_BG,
    XP_HEB_BH,
    XP_HEB_BI,
    XP_HEB_BJ,
#     if defined(HEBREW_ISRAEL)
    XP_HEB_BK,  // 
#     endif
    XP_HEB_CA,
    XP_HEB_CB,
    XP_HEB_CC,
    XP_HEB_CD,
    XP_HEB_CE,
    XP_HEB_CF,
    XP_HEB_CG,
#     if defined(HEBREW_ISRAEL) || defined(HEBREW_DVORAK)
    XP_HEB_CH,
    XP_HEB_CI,
    XP_HEB_CJ,
#     endif
    XP_HEB_MQF, // ־
# endif //BASE_HEBREW__*

};

// Pre-existing function, called for every key up and down.
// This function is sortof the hub of the whole thing.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // User input for the word count menu
    if (sizecount_menu) {
         if (record->event.pressed) { // key down

             switch (keycode) {
                 case KC_0: // read in how many is maximum
                     sizecount_max = (sizecount_max * 10);
                     break;

                 case KC_1:
                     sizecount_max = (sizecount_max * 10) + 1;
                     break;

                 case KC_2:
                     sizecount_max = (sizecount_max * 10) + 2;
                     break;

                 case KC_3:
                     sizecount_max = (sizecount_max * 10) + 3;
                     break;

                 case KC_4:
                     sizecount_max = (sizecount_max * 10) + 4;
                     break;

                 case KC_5:
                     sizecount_max = (sizecount_max * 10) + 5;
                     break;

                 case KC_6:
                     sizecount_max = (sizecount_max * 10) + 6;
                     break;

                 case KC_7:
                     sizecount_max = (sizecount_max * 10) + 7;
                     break;

                 case KC_8:
                     sizecount_max = (sizecount_max * 10) + 8;
                     break;

                 case KC_9:
                     sizecount_max = (sizecount_max * 10) + 9;
                     break;

                 case KC_C: // count characters
                     sizecount_max_type = SIZECOUNT_CHAR;
                     sizecount_menu = FALSE;
                     break;

                 case KC_W: // count words
                     sizecount_max_type = SIZECOUNT_WORD;
                     sizecount_menu = FALSE;
                     break;

                 // Anything else ends menu input.
                 case KC_DOT:
                 case KC_ESC:
                     sizecount_menu = FALSE; // break out
                     break;

             }
             if (!sizecount_menu) { // end
                     send_string ("->");
                     write_number (sizecount_max, FALSE);  // just indicate something
             }
         }
    }

    // Go back to base-layer after pressing an F-key, on key-up to avoid BASE key activation
    if ((_fun_stay == FALSE) && // 
        (((keycode >= KC_F1) && (keycode <= KC_F12))
         ||
        ((keycode >= KC_F13) && (keycode <= KC_F24)))) {  // assumes keycodes 1-12 and 13-24 are consequtive, which seems likely, although using 1-24 failed (probably not consequtive)
         // Go back to base layer
         if (!(record->event.pressed)) { // key up
             if (alternate) { // 
                 layer_move (_ALT_BASE); 
             }else{
                 layer_move (_DEF_BASE);
             }
        }
    }

    // Detect if Shift was pressed in isolation, by seeing if another key was pressed during the time
    // the right shift key was held down.
    // This system is also used by CHOLTAP_ACCE
    // This helps make sure a tapped use of these keys is correctly differentiated from their use as a  
    // modifier/layer-hold key. The Shift and CHOLTAP_ACCE should not normally interfere with each other.
    if (isolate_trigger) { // speed: hoping this statement to execute a little quicker overall, than the next 
        if ((keycode != CHOLTAP_RSHFT)   // not right shift up
             &&
            (keycode != CHOLTAP_LSHFT)   // not left shift up
             &&
            (keycode != CHOLTAP_ACCE)    // _ACC layer (and others)
             &&
            (keycode != RSFT_TILDE)      // Shift on _NSY
             &&
            (keycode != LSFT_DASH)       // Shift on _NSY
             &&
            (keycode != CHOLTAP_LAYR)) 
                                       { // _RAR layer, or RAlt/Alt-Gr
            isolate_trigger = FALSE; // another key was pressed
        }
    }

    // This block contains the complex macros, which should not count in speed counting or word/character counting,
    // because they aren't typed characters.
    switch (keycode) {

        // Typing speed measuring
        case SPEED_TOG: // Toggle speed measuring on/off
            if (record->event.pressed) { // key down
                if (speed_measure) {
                    speed_measure = FALSE;

# ifdef RGBLIGHT_ENABLE
                    rgblight_sethsv_noeeprom (HSV_PURPLE); // indicates stop (_RAR color)
# endif

                }else{
                    // initialization of measurements
                    speed_measure = TRUE; // activates
                    speed = 0; // start at 0 k/s 
                    speed_countdown = SPEED_COUNTDOWN; // reset, speed is measured in batches of keypresses
                    speed_counttime = timer_read32 ();// get current time
                    speed_add = 0;// speed average accumulator, it keeps adding the *speed* of each batch to this total
                    speed_batches = 0; // divider for speed_add to get the average

# ifdef RGBLIGHT_ENABLE
                    // set middle led
                    rgblight_sethsv_noeeprom (HSV_WHITE); // indicates start
# endif

                }

# ifdef RGBLIGHT_ENABLE
                isolate_rgblight_set ();
# endif

            }
            break; 

        case SPEED_REPORT: // Report the current typing speed by writing it, as if typing
            if (record->event.pressed) { // down
                short added = 5; // This counts how many characters the report itself is adding into the current text,
                                 // to later delete it from the character count for text-size counting.
              
                if (speed_measure) {

# ifdef WORDS_PER_MINUTE

                    // The speed is recorded as an accumulation of keystrokes-per-second, times 10 for added precision.
                    // This will be converted into words-per-minute by dividing by 5 characters for a word including
                    // blank space and punctuation, and multiplied by 60 for seconds per minute. ⁶⁰/₅ = 12. Multiplied
                    // by 12 is the simple conversion.
                    send_string ("<"); // +1 character written // analogue to '<POWER>'
                    added += write_number ((long int)((speed*12)/10), FALSE); // writes the speed 
                    send_string ("wpm"); // +3 character written
                    if (0 != speed_batches) {
                        long int average_times_ten;
                        average_times_ten =(long int) ((speed_add * 12) / speed_batches); // *12 converts k/s to wpm

                        send_string (";"); // +①   ''       
                        added += write_number (average_times_ten / 10, FALSE); // writes the average speed, cannot use decimal because precision is not there
                        send_string ("wpm"); // +③
                        added += write_number ((long int) speed_batches, FALSE); // amount of batches
                        send_string ("x"); // +①
                        added += 9 + write_number ((long int) SPEED_COUNTDOWN, FALSE); // amount of batches
                        send_string ("keys"); // +④ = ⑨
           
                        speed_led ( (int) (average_times_ten / 12));// on report, show the average
                                                                         // we need to convert back to k/s now
                    }

# else // keystrokes per second, k/s

                    send_string ("<"); // +1 character written // analogue to '<POWER>'
                    added += write_number ((long int)(speed/10), FALSE); // writes the speed 
                    send_string ("k/s"); // +3 character written
                    if (0 != speed_batches) {
                        long int average_times_ten;
                        average_times_ten =(long int) (speed_add / speed_batches);

                        send_string (";"); // +①   ''       
                        added += write_number (average_times_ten, DIV10POINT); // writes the average speed 
                        send_string ("k/s"); // +③
                        added += write_number ((long int) speed_batches, FALSE); // amount of batches
                        send_string ("x"); // +①
                        added += 9 + write_number ((long int) SPEED_COUNTDOWN, FALSE); // amount of batches
                        send_string ("keys"); // +④ = ⑨
           
                        speed_led ( (int) average_times_ten );// on report, show the average. speed_led divides by 10
                    }

# endif

                    send_string (">"); // +1 = 5
                    if (sizecount_measure) sizecount_chars += added;   // the user is expected to hit <backspace>
                }else{
                    send_string ("<Soff>"); // indicates off
                    if (sizecount_measure) sizecount_chars += 5;  // user: <backspace>, to take it down again
                }

                key_timer = timer_read ();

            }else{ // key up
                // This use of the key is for callibrating your colors; it is difficult otherwise to see.
                // This is not part of normal usage, therefore it is kept bare bones to reduce firmware size
                if (timer_elapsed (key_timer) > 999) { // held for one second
                    speed += 10;
                    write_number ((long int)(speed/10), FALSE); // writes the speed 
                    speed_led (speed); // update led
                }
            }
            break;

        case COUNT_TOG: // Toggle start/stop text size measuring
            if (record->event.pressed) { // key down

                key_timer = timer_read ();

            }else{ // up
                if (timer_elapsed (key_timer) < 500) { // held for less than half a second (tapped)
                    if (sizecount_measure) {

                        sizecount_measure = FALSE;

# ifdef RGBLIGHT_ENABLE
                        rgblight_sethsv_noeeprom (HSV_PURPLE); // indicates stop (color of _RAR)
                        isolate_rgblight_set ();
# endif

                    }else{

                        sizecount_measure = TRUE; // start counting
                        sizecount_word = FALSE; // detect double blanks. leading blanks are not a word

# ifdef RGBLIGHT_ENABLE
                        if (0 == sizecount_max) {
                            rgblight_sethsv_noeeprom (HSV_BLUE); // indicates start/activated, but only without maximum set
                            isolate_rgblight_set (); // .. if maximum set, led goes green to red.
                        }else{
                            rgblight_sethsv_noeeprom (HSV_GREEN); // indicates start/activated, but only without maximum set
                            isolate_rgblight_set (); // .. if maximum set, led goes green to red.
                        }
# endif

                    }
                }else{ // held longer
                    sizecount_menu = TRUE;
                    send_string ("<Nc|w>"); // Menu: N amount, c|w character|word counting. Input is a number then ‛c’ or ‛w’
                    sizecount_max = 0;
                }
            }
            break;

        case COUNT_NULL: // Sets the count to zero, which allows on/off to have a suspend/resume 
            if (record->event.pressed) { // key up
                sizecount_blanks = 0; // 
                sizecount_chars = 0;

# ifdef RGBLIGHT_ENABLE
                rgblight_sethsv_noeeprom (HSV_CYAN); // indicates reset
                isolate_rgblight_set ();
# endif

            }
            break;

        case COUNT_REPORT: // Report the current typing speed 
            if (record->event.pressed) {
                // We assume the user is writing a report in its active document, and then likely deleting it.
                short added = 0; // This counts how much characters the report adds into the user document.

                if (sizecount_measure) {
                    send_string ("<"); // + 1 and ① characters (1 is one logical stream, ① another)
                    if (0 == sizecount_max) { // no size counting maximum, print both characters and words

                        added += write_number (sizecount_chars, FALSE); // returns how many characters where printed
                        send_string ("c;"); // + 2
                        added += write_number (sizecount_blanks, FALSE) + 5; // adds here
                        send_string ("w>"); // + 2 = 5

                    }else{ // Only show the one for which the maximum is set, don't throw off that mental focus
                        if (SIZECOUNT_WORD == sizecount_max_type ) {

                            added += write_number (sizecount_blanks, FALSE) + 3;
                            send_string ("w>"); // + ② = ③

                        }else{ // characters

                            added += write_number (sizecount_chars, FALSE) + 3; // returns how many characters where printed
                            send_string ("c>"); // + ② = ③

                        }
                        // add current maximum setting
                        send_string ("["); // + 1
                        added += write_number (sizecount_max, FALSE) + 3; 
                        if (SIZECOUNT_WORD == sizecount_max_type) send_string ("w]"); // + 2
                        else                                      send_string ("c]"); // + 2
                    }
                    sizecount_chars += added; // Account for the written characters in the report itself.

                }else{ // no size counting, also here: keep the report terse
                     send_string ("<Coff>"); // indicates off (no need to add to count, since counting is off)
                }
            }
            break;

        // This allows the user to manually remove word counts, when he has deleted a word.
        // This is not needed for character count, because <backspace> counts as minus.
        case COUNT_WORDMIN: // Take down one word in the word-count.
            if (record->event.pressed) { // down
                key_timer = timer_read ();
            }else{ // up
                if (timer_elapsed (key_timer) < 500) { // held for less than half a second (tapped)
                    sizecount_blanks--;
                }else{
                    sizecount_blanks -= 10;
                }
            }
            break;

    // Shift detection system.
                                                  // Disused because it turned out 'one shot' like Unicode input. Shift detection copied from.
                                                  // https://github.com/kyleterry/qmk_firmware/blob/master/quantum/quantum.c
                                                  //uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));

        // Crude but self contained in this source file shift detection.
        // ... right shift
        case KC_RSFT:
        // + ... left shift
        case KC_LSFT:
            if (record->event.pressed) { // key down
                shift_ison = 1; // shift depressed
            }else{ // key up
                shift_ison = 0; // shift released
            }
            // There are macros on Shift who also alter this variable.
            break;

        case OTHER_BASE: // Switching through the default/alternate BASE modes, and Descramble for that Dvorak compile
            if (record->event.pressed) {
                ;
            }else{ // key up

                // Cycles through the modes
# ifdef DVORAK_DESCRAMBLE // version Dvorak+Dvorak-descramble has 3 modes
                if (_NORMAL_ == alternate) {
                    alternate = _FULL_;// alternate layers
                    default_layer_set (_ALT_BASE_MASK); // This is needed only for a rare case,
                                 //  where _DEF_BASE and _ALT_BASE their layer switching keys don't line up,
                                 //  such as with Qwerty Base Arrow
                } else if (_HALF_ == alternate) {
                    alternate = _NORMAL_;// normal layers
                    default_layer_set (_DEF_BASE_MASK);
                }else{ // _FULL_ == alternate
                    alternate = _HALF_;// alternate layers, without 'descramble' recomputing Unicode
                    //default_layer_set (_ALT_BASE_MASK);
                    // it cycles, and this comes always after it was set _FULL_
                }
# else          // Only switching the BASE layers between alternate and default

                if (_NORMAL_ == alternate) {
                    alternate = _FULL_;// alternate base layers
                    default_layer_set (_ALT_BASE_MASK);
                }else{
                    alternate = _NORMAL_;// default base layers
                    default_layer_set (_DEF_BASE_MASK);
                } 
# endif

                indicate_base ();  // activate led change 
            }
            break; 

# if defined(BASE_NUMPAD__ALT_BASE)

        case OTHER_BASE_GO: // Switching through the default/alternate BASE modes, and Descramble for that Dvorak compile
            if (record->event.pressed) {
                ;
            }else{ // key up

                // Cycles through the modes
# ifdef DVORAK_DESCRAMBLE // version Dvorak+Dvorak-descramble has 3 modes
                if (_NORMAL_ == alternate) {
                    alternate = _FULL_;// alternate layers
                    default_layer_set (_ALT_BASE_MASK);
                } else if (_HALF_ == alternate) {
                    alternate = _NORMAL_;// normal layers
                    default_layer_set (_DEF_BASE_MASK);
                }else{ // _FULL_ == alternate
                    alternate = _HALF_;// alternate layers, without 'descramble' recomputing Unicode
                    //default_layer_set (_ALT_BASE_MASK);
                    // it cycles, and this comes always after it was set _FULL_
                }
# else          // Only switching the BASE layers between alternate and default

                if (_NORMAL_ == alternate) {
                    alternate = _FULL_;// alternate base layers
                    default_layer_set (_ALT_BASE_MASK);
                }else{
                    alternate = _NORMAL_;// default base layers
                    default_layer_set (_DEF_BASE_MASK);
                } 
# endif
                // make the switch to the other Base layer
                if (alternate) { // 
                    layer_move (_ALT_BASE); 
                }else{
                    layer_move (_DEF_BASE);
                }
            }
            break; 
# endif

        //     Switching to layers:

        case CTO_BASE:
        // User pressed upper/left button, while not on BASE layer: ‛escape’ from a layer to BASE layer.
        // On BASE itself, that key is <Escape>.
            if (record->event.pressed) { // key down
                ;
            }else{ // key up
                if (alternate) { // go to the alternate version (bit of a hack maybe, but all alternate
                       // ... modes are non-zero)
                    layer_move (_ALT_BASE); 
                }else{
                    layer_move (_DEF_BASE); 
                }
            } 
            break;

        case CTO_NUMS: // activates number-symbols layer
            if (record->event.pressed) { // key down
                ; 
            }else{ // key up, so that upon key down the target layer isn't already activated, triggering that key on up
                if (alternate) { // go to the alternate version
                    layer_move (_ALT_NSY); 
                }else{
                    layer_move (_DEF_NSY); 
                }
            } 
            break; 

        case CTO_ACCE: // Unicode layer
            if (record->event.pressed) { // key down
                ;
            }else{ // key up

# ifndef REMOVE_ACC // This cuts out the whole _ACC layer.
                layer_move (_ACC); // activates normal accented layer
# else
#     ifdef _ACC_KEY_ALT_LAYER
                layer_move (_ACC_KEY_ALT_LAYER); // Alternative layer user configuration
#     endif
# endif

            }
            break; 

        case CTO_DRAW: // Unicode layer
            if (record->event.pressed) { // key down
                ;
            }else{ // key up

# ifndef REMOVE_DRA // This cuts out the whole _DRA layer.
                layer_move (_DRA); // activates normal accented layer
# else
#     ifdef _DRA_KEY_ALT_LAYER
                layer_move (_DRA_KEY_ALT_LAYER); // Alternative layer user configuration
#     endif
# endif
            } 
          break; 

        // The below are a simulated LT(layer,kc), layer-tap. 
        // Double-tap-hold repeater functionality: not done. 
        // They switch what layer to use depending on 'alternate' variable
        // Basically it starts the right layer on key down, goes back to base layer on key up,
        // and throws in a keypress as well if tapped.
        // It also integrates with DUO_HOLD, to reach the _BON layer.

# ifndef CHOLTAP_ACCE_NOP // When this key has been eviscerated, this macro becomes useless
        case CHOLTAP_ACCE: // Works with DUO_HOLD macro to activate one of several layers.
            if (record->event.pressed) { // key down
                key_timer = timer_read ();
                isolate_trigger = TRUE; // keep track of whether another key gets pressed.

                duo_press_acc_bon ++; // This signals to the two DUO_HOLD keys, whether a move to _BON is desired.

                if (duo_press_nsy_dra) { // One or more of the DUO_HOLD layer keys was already pressed; move to _BON

#     ifndef REMOVE_BON // Removes this layer entirely, if set.
                    layer_move (_BON); // Bonus Unicode layer
#     else
#         ifdef _BON_KEY_ALT_LAYER
                    layer_move (_BON_KEY_ALT_LAYER); // Alternative layer user configuration
#         endif
#     endif 

                }else{ // pressed in isolation

#     ifndef REMOVE_ACC // This cuts out the whole _ACC layer.
                    layer_move (_ACC); // Accented layer
#     else
#         ifdef _ACC_KEY_ALT_LAYER
                    layer_move (_ACC_KEY_ALT_LAYER); // Alternative layer user configuration
#         endif
#     endif 

                }
            }else{ // key up

                duo_press_acc_bon --;

                if (1 == duo_press_nsy_dra) { // One DUO_HOLD layer keys is still pressed; move to numbers/symbols

                    if (_FULL_ == alternate) {
                        layer_move (_ALT_NSY); 
                    }else{
                        layer_move (_DEF_NSY); 
                    }
                }else if (2 == duo_press_nsy_dra) { // Two of the DUO_HOLD layer keys are still pressed: move to _DRA

#     ifndef REMOVE_DRA // This cuts out the whole _DRA layer.
                    layer_move (_DRA); // activates normal accented layer
#     else
#         ifdef _DRA_KEY_ALT_LAYER
                    layer_move (_DRA_KEY_ALT_LAYER); // Alternative layer user configuration
#         endif
#     endif

                }else{
                    if (alternate) { // No _DEF_NSY layer keys remain pressed; Go back to base layer
                        layer_move (_ALT_BASE); 
                    }else{
                        layer_move (_DEF_BASE);
                    }
                }

                // Pressed in isolation
                if (isolate_trigger) 
                {
                    if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                        SEND_STRING (SS_TAP (X_DEL));
                    }
                }
            }
            break;
# endif // CHOLTAP_ACCE_NOP

        case CHOLTAP_LAYR: //to _RAR on hold, otherwise a keycode
            if (record->event.pressed) { // key down
                key_timer = timer_read ();
                isolate_trigger = TRUE; // keep track of whether another key gets pressed.

# ifdef BASE_RIGHT_ALT
                SEND_STRING (SS_DOWN (X_RALT)); 
# else
                layer_move (_RAR); // activates descrambled drawings layer
# endif

            }else{ // key up
                // Go back to base layer
                if (speed_measure) speed_led (speed); // The _RAR layer overwrites the middle led, 
                  //.. for use with alternate _HALF_ led colors (middle); thus needs to be set back to speed
                  // led color upon leaving.

# ifdef BASE_RIGHT_ALT
                SEND_STRING (SS_UP (X_RALT)); 
# else
                if (alternate) { 
                    layer_move (_ALT_BASE); 
                }else{
                    layer_move (_DEF_BASE);
                }
# endif

                // Pressed in isolation
                if (isolate_trigger) 
                {
                    if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                        SEND_STRING (SS_TAP (X_RIGHT));
                    }
                }
            }
            break;

# ifndef DUO_HOLD_BASIC
        // This is the normal 'big' version, dealing with switching between _DEF_NSY/_ALT_NSY, _ACC, _DRA and _BON, in 
        // .. conjunction with the CHOLTAP_ACCE macro.
        case DUO_HOLD: // The macro around the split space-bar. Both keys come to this macro.
            if (record->event.pressed) { // key down

                duo_press_nsy_dra ++; // simple way to keep track of how many are pressed

                if (duo_press_acc_bon){ // Preceded by holding the _ACC/_BON layer switch key: move to _BON

#     ifndef REMOVE_BON // Removes this layer entirely, if set.
                    layer_move (_BON); // Bonus Unicode layer
#     else
#         ifdef _BON_KEY_ALT_LAYER
                    layer_move (_BON_KEY_ALT_LAYER); // Alternative layer user configuration
#         endif
#     endif 

                }else if (1 == duo_press_nsy_dra) { // This is the first press of either of the DUO_HOLD keys on BASE

                    if (_NORMAL_ == alternate) {
                        layer_move (_DEF_NSY); 
                    }else{
                        layer_move (_ALT_NSY); 
                    }
                }
                else if (2 == duo_press_nsy_dra) { // both are pressed

#     ifndef REMOVE_DRA // This cuts out the whole _DRA layer.
                    layer_move (_DRA); // activates normal accented layer
#     else
#         ifdef _DRA_KEY_ALT_LAYER
                    layer_move (_DRA_KEY_ALT_LAYER); // Alternative layer user configuration
#         endif
#     endif
                }

            }else{ // key up

                duo_press_nsy_dra --; 

                if (1 == duo_press_nsy_dra) {
                    if (duo_press_acc_bon){ // Still holding the _ACC/_BON layer switch key, and one DUO_HOLD keys

#     ifndef REMOVE_BON // Removes this layer entirely, if set.
                    layer_move (_BON); // Bonus Unicode layer
#     else
#         ifdef _BON_KEY_ALT_LAYER
                    layer_move (_BON_KEY_ALT_LAYER); // Alternative layer user configuration
#         endif
#     endif 

                    }else{
                        if (_NORMAL_ == alternate) { 
                            layer_move (_DEF_NSY); 
                        }else{
                            layer_move (_ALT_NSY); 
                        }
                    }
                }
                else { // Has to be zero.
                    if (duo_press_acc_bon){ // Still holding the _ACC/_BON layer switch key, but zero DUO_HOLD layer keys

#     ifndef REMOVE_ACC // This cuts out the whole _ACC layer.
                        layer_move (_ACC); // Accented layer
#     else
#         ifdef _ACC_KEY_ALT_LAYER
                        layer_move (_ACC_KEY_ALT_LAYER); // Alternative layer user configuration
#         endif
#     endif 

                    }else{
                         if (alternate) { // Back to letters
                            layer_move (_ALT_BASE); 
                         }else{
                            layer_move (_DEF_BASE);
                         }
                    }
                }
            }
            break;
# else
        // This is the eviscerated version, compiled when all Unicode layers _ACC, _DRA, _BON are cut, and layer key
        // .. combinations have not been assigned other uses.
        case DUO_HOLD: // The macro for the keys around the split space-bar. Both keys come to this macro.
            if (record->event.pressed) { // key down

                duo_press_nsy_dra ++; // simple way to keep track of how many are pressed

                if (0 != duo_press_nsy_dra) { // One or more of the DUO_HOLD keys is pressed
                    if (_NORMAL_ == alternate) {
                        layer_move (_DEF_NSY); 
                    }else{
                        layer_move (_ALT_NSY); 
                    }
                }
            }else{ // key up

                duo_press_nsy_dra --; 

                if (0 == duo_press_nsy_dra) { // None of the DUO_HOLD keys remains pressed
                    if (alternate) { // Back to letters
                       layer_move (_ALT_BASE); 
                    }else{
                       layer_move (_DEF_BASE);
                    }
                }
            }
            break;
# endif // DUO_HOLD_BASIC

        //   When held the key is shift. When tapped it is computed if the tap is short enough,
        // and if no other key was pressed, in which case: right-shift-up is a toggle to the _FUN layer.
        // The timing is meant to be able to undo an erroneous shift press just by holding longer,
        // and the test if another key was pressed is to prevent an erroneous detection when typing
        // very fast.
        //   The reason for this on shift is to isolate GUI, where _FUN was previously more easily
        // located. No alternative tapping function with GUI because some systems do not treat GUI
        // purely as a modifier it seems. Since it is a toggle anyway, _FUN can fit away from the thumb-hold row.
        case CHOLTAP_RSHFT: // When tapped it toggles the _FUN layer, when held it is Shift

            if (record->event.pressed) { // key down

                SEND_STRING (SS_DOWN (X_RSFT)); 
                shift_ison = 1; // shift depressed

                key_timer = timer_read ();
                isolate_trigger = TRUE; // keep track of whether another key gets pressed until key-up

            }else{ // key up

                SEND_STRING (SS_UP (X_RSFT)); 
                shift_ison = 0; // shift released

                if (isolate_trigger) { // no other key was hit since key down 


                    // Held medium long: _PAD, long: _MOV.
                    // The reason to have a switch to _MOV on the left hand, is to be able to reach arrows on a toggle,
                    // all by the left hand, when the right hand is on the mouse.
                    if ((timer_elapsed (key_timer) <= 200)) { // tapped short (milliseconds)

# ifndef SWITCH_RSHIFT_FUN_RAR // user config to reverse what this key its timing toggles to

                        layer_move (_FUN); // activates function layer as a toggle

                    } else { // held for longer

                        layer_move (_RAR); 
 
# else

                        layer_move (_RAR); // activates function layer as a toggle

                    } else { // held for longer

                        layer_move (_FUN); 

# endif
 

                    }
                }
            }
            break;

        // The left-shift version of the above keycode. User can configure something (_PAD is default)
        case CHOLTAP_LSHFT: // When tapped it toggles the _MOV layer, when held it is Shift
                            // _RAR was the first idea, but some of its keys are too dangerous regarding accidents.
            if (record->event.pressed) { // key down

                SEND_STRING (SS_DOWN (X_LSFT)); 
                shift_ison = 1; // shift depressed

# ifndef REMOVE_PAD // The _PAD layer exists, we will use a timer …

                key_timer = timer_read ();

# endif


                // This variable is re-used, for speed and because using both shifts is useless,
                // .. thus very rare, and also not a usage problem if it occured.
                isolate_trigger = TRUE; // keep track of whether another key gets pressed.

            }else{ // key up

                SEND_STRING (SS_UP (X_LSFT)); 
                shift_ison = 0; // shift released

                if (isolate_trigger) { // no other key was hit since key down 

# ifndef REMOVE_PAD // The _PAD layer exists, differentiate meaning by timer.

                    // Held medium long: _PAD, long: _MOV.
                    // The reason to have a switch to _MOV on the left hand, is to be able to reach arrows on a toggle,
                    // all by the left hand, when the right hand is on the mouse.
                    if ((timer_elapsed (key_timer) <= 200)) { // tapped medium-long (milliseconds)

#     ifndef SWITCH_LSHIFT_PAD_MOV // user config to reverse what this key its timing toggles to

                        layer_move (_PAD); 

                    } else { // held for longer

                        layer_move (_MOV); 

#     else

                        layer_move (_MOV); 

                    } else { // held for longer

                        layer_move (_PAD); 

#     endif

                    }

# else // _PAD layer was eviscerated

                        layer_move (_MOV); 

# endif

                }
            }
            break;

/*
        case RSFT_TILDE:

            if (record->event.pressed) { // key down

                SEND_STRING (SS_DOWN (X_RSFT)); 
                shift_ison = 1; // shift depressed

                key_timer = timer_read ();
                isolate_trigger = TRUE; // keep track of whether another key gets pressed until key-up

            }else{ // key up

                SEND_STRING (SS_UP (X_RSFT)); 
                shift_ison = 0; // shift released

                if (isolate_trigger) { // no other key was hit since key down 


                    // Held medium long: _PAD, long: _MOV.
                    // The reason to have a switch to _MOV on the left hand, is to be able to reach arrows on a toggle,
                    // all by the left hand, when the right hand is on the mouse.
                    if ((timer_elapsed (key_timer) <= 200)) { // tapped short (milliseconds)

                        SEND_STRING ("~");

                    }
                }
            }
            break;
*/

        case RSFT_TILDE: // firmware size optimization, saves 36 bytes
        case LSFT_DASH:

            if (record->event.pressed) { // key down

                if (RSFT_TILDE == keycode) { // this is probably not needed, both can be left or right shift
                    SEND_STRING (SS_DOWN (X_RSFT)); 
                }else{
                    SEND_STRING (SS_DOWN (X_LSFT)); 
                }
                shift_ison = 1; // shift depressed

                key_timer = timer_read ();
                isolate_trigger = TRUE; // keep track of whether another key gets pressed until key-up

            }else{ // key up

                if (RSFT_TILDE == keycode) { 
                    SEND_STRING (SS_UP (X_RSFT)); 
                }else{
                    SEND_STRING (SS_UP (X_LSFT)); 
                }
  
                shift_ison = 0; // shift released

                if (isolate_trigger) { // no other key was hit since key down 


                    // Held medium long: _PAD, long: _MOV.
                    // The reason to have a switch to _MOV on the left hand, is to be able to reach arrows on a toggle,
                    // all by the left hand, when the right hand is on the mouse.
                    if ((timer_elapsed (key_timer) <= 200)) { // tapped short (milliseconds)

                        if (RSFT_TILDE == keycode) { 
                            SEND_STRING ("~");
                        }else{
                            SEND_STRING ("-");
                        }
                    }
                }
            }
            break;

        case _FUN_STAY: // toggles if the f-keys return _FUN layer to BASE after one press
            if (record->event.pressed) { // key down

                if (_fun_stay == FALSE) { 
                    _fun_stay = TRUE;
                }else{
                    _fun_stay = FALSE;
                }
                indicate_fun_stay (); // leds
            }
            break;

# ifdef MOREKEY2_ARROW_CLUSTER

        case _MOV_UP: // To be sure it activates on up key, and not already has triggered the _MOV layer during up-key.
            if (record->event.pressed) { // key down
               ;
            }else{ // key up
               layer_move (_MOV);
            }
            break;
# endif

        // These keys are so disruptive on an erroneous key press, that they are behind a shift lock.
        // When used unshifted, they print a memory aid string: their name.
        case C_KC_PWR: 
            if (record->event.pressed) { // key down
                if (shift_ison) { 
                    SEND_STRING (SS_TAP (X_PWR)); 
                }else{
                    SEND_STRING ("<POWER>"); // Memory aid
                }
            }
            break;

        case C_KC_WAKE:
            if (record->event.pressed) { // key down
                if (shift_ison) { 
                    SEND_STRING (SS_TAP (X_WAKE)); 
                }else{
                    SEND_STRING ("<WAKE>"); // Memory aid
                }
            }
            break;

        case C_KC_SLEP:
            if (record->event.pressed) { // key down
                if (shift_ison) { 
                    SEND_STRING (SS_TAP (X_SLEP)); 
                }else{
                    SEND_STRING ("<SLEEP>"); // Memory aid
                }
            }
            break;

        case C_KC_PAUS:
            if (record->event.pressed) { // key down
                if (shift_ison) { 
                    SEND_STRING (SS_TAP (X_PAUS)); 
                }else{
                    SEND_STRING ("<PAUSE>"); // Memory aid
                }
            }
            break;

        case LEDS_ON: // Toggles left/right leds on or off
            if (record->event.pressed) { // key down

# ifdef RGBLIGHT_ENABLE
                if (leds_on == FALSE) { 
                    leds_on = TRUE;
                }else{
                    leds_on = FALSE;
                }
                set_led_colors_ (state_recall); // Update leds
            }
# endif

            break;

# ifdef LEDS_OFF_BASE_DEF  // This messes with led effect on/off, so we need to track the state of this setting now.
        case RGBTOG_: // Toggles middle led on or off
            if (record->event.pressed) { // key down
                if (led_middle_on == FALSE) { 
                    led_middle_on = TRUE;
                    rgblight_enable_noeeprom (); 
                }else{
                    led_middle_on = FALSE;
                    rgblight_disable_noeeprom (); 
                }
            }
            break;
# endif   

        // Some keycodes treated specially for the two counting systems (speed, text size)
        // Deletions:
        case KC_BSPC: // non-counting speed
        case KC_DEL: // non-counting speed
            if (record->event.pressed) { // key down
                if (sizecount_measure) sizecount_chars--; // minus count for text size (removed a character)
            }
            break;

        // White space for counting words
        case LT__MOV__KC_ENT: // We want to count the <enter> for word-counts, sadly this looses the key repetition of LT(…)
            if (record->event.pressed) { // key down

                key_timer = timer_read ();
                layer_move (_MOV);

            }else{ // key up
                 if (alternate) { // Back to letters
                     layer_move (_ALT_BASE); 
                 }else{
                     layer_move (_DEF_BASE);
                 }
                 if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                     send_string ("\n");
                     if (sizecount_measure) {
                         sizecount_chars++;

                         if (sizecount_word) sizecount_blanks++; // count a word
                         sizecount_word = FALSE; // don't count immediately next blank as a word
                     }
                 }
            }
            break;

        // Word counting
        case KC_SPC:
            if (record->event.pressed) { // key down
                if (sizecount_measure) {
                    sizecount_chars++;

                    if (sizecount_word) sizecount_blanks++; // count a word
                    sizecount_word = FALSE; // don't count immediately next blank as a word
                }
            }
            break;

        // These are excluded from counting for text size/speed, they prevent the “default“ in the case statement to execute.

        case KC_LEFT:
        case KC_UP:
        case KC_DOWN:
        case KC_RIGHT:
        case KC_PGUP:
        case KC_PGDN:
        case KC_HOME:
        case KC_END:
        case LALT_T ( KC_LEFT ):
            if (speed_measure) speed_countdown++; // Navigation could be integral to someone typing and correcting mistakes,
                                                  // but those keys don't add any text.
        // Mouse movement is discounted in both speed and text size
        case KC_WH_L:
        case KC_WH_D:
        case KC_WH_U:
        case KC_WH_R:
        case KC_MS_L:
        case KC_MS_D:
        case KC_MS_U:
        case KC_MS_R:
        case KC_BTN1:
        case KC_BTN5:
        case KC_BTN4:
        case KC_BTN3:
        case KC_BTN2:
            break;


        default: // If something else, it is a speed- and text measurement counting key
            if (record->event.pressed) { // key down
                if (speed_measure) speed_countdown--;
                if (sizecount_measure) sizecount_chars++; 
            }
    }

    // If speed measuring is on, count keypresses
    // The idea is to more/less follow common standard with typing speed counting: shift is not counted,
    // layer-switching or its equivalent is neither. Arrows are not counted. 
    if (speed_measure) {
        if (record->event.pressed) { // key down

            if (0 >= speed_countdown) {

                // key presses per second, but times ten for added precision of one digit
                // This calculation quickly looses precision if not calculated with high enough numbers, but low enough to fit.
                speed = (int) ( (SPEED_COUNTDOWN * 1000 ) / ((timer_read32 () - speed_counttime)/10) ); // counts time in ms
                speed_led (speed); // updates led

                // record for average
                if (0 < (speed/10)) { // ignore 0 k/s batches, we assume the typer took a break
                    speed_batches++; 
                    speed_add += speed; 
                }

                // reset for next batch
                speed_countdown = SPEED_COUNTDOWN; // reset
                speed_counttime = timer_read32 ();
            }
        }
    }

    // For word-counting, ignore double blanks
    if (sizecount_measure) {
        if (record->event.pressed) { 
            bool within = TRUE; // When text size is maximized, this indicates we are not yet at that maximum.

# ifdef RGBLIGHT_ENABLE
            unsigned short size_fraction = 0; // Used to compute led color as a fraction of a set maximum which is already typed.
# endif

            // ignoring blanks wordcount
            if ((keycode != KC_SPC)
                 &&
                (keycode != KC_TAB) // This is ok, but a tab on BASE layer combo with Control, is not caught by this XXX (problem ignored, I never write Tab in a text worth counting)
                 &&
                (keycode != LT__MOV__KC_ENT)
                 &&
                (keycode != LT__MOV__KC_ENT)) {

                sizecount_word = TRUE; // current key is not a blank, so we set this trigger for next key press
            }

            // computing maximum count effects: leds
            if (0 != sizecount_max) { 

                if (SIZECOUNT_WORD == sizecount_max_type) {
                    if (sizecount_blanks > sizecount_max) within = FALSE;
                }else{ // count chars
                    if (sizecount_chars > sizecount_max) within = FALSE;
                }

                // led colors
                if (within) { // green to red middle led

# ifdef RGBLIGHT_ENABLE
                    if (SIZECOUNT_WORD == sizecount_max_type) {
                        size_fraction = (90 * sizecount_blanks) / sizecount_max; 
                    }else{
                        size_fraction = (90 * sizecount_chars) / sizecount_max;
                    } 

                    rgblight_sethsv_noeeprom (90 - size_fraction , 255, 255); // green to red, full saturation, full lit
# endif
                
                }else{ // when at or over the limit: blink led red/white
                    if ((KC_BSPC != keycode) 
                         && (KC_DEL != keycode) // User already deleting, doubling is confusing
                         && (CHOLTAP_LAYR != keycode)) { // This brings up the _RAR layer, to access the Count settings.

                        SEND_STRING (SS_TAP(X_BSPC)); // refuses to type further, the user is stopped from typing to make it obvious

                    }

# ifdef RGBLIGHT_ENABLE
                    if (sizecount_chars & 0x1) { // flip by every keypress
                        rgblight_sethsv_noeeprom (HSV_RED);
                    }else{
                        rgblight_sethsv_noeeprom (HSV_WHITE); 
                    }
# endif

                }

# ifdef RGBLIGHT_ENABLE
                rgblight_set (); // only center led is altered, no need to go through isolate_rgblight_set()
# endif

            }
        }
    }

    // Simple macros, printing a character.
    switch (keycode) {

        /* _ACC layer definitions. */

   // ------------------------- row 4

# ifndef REMOVE_ACC // This cuts out the whole _ACC layer.
        case XP_ACC_AA: // because a 
            if (record->event.pressed) { // key down
                unicode_hex2output (CAL_ACU, CAU_ACU);//  á Á
            }
            break;

        case XP_ACC_AB: // because o (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (COL_ACU, COU_ACU);// ó Ó
            }
            break;

        case XP_ACC_AC: // because e (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CEL_ACU, CEU_ACU);// é É
            }
            break;

        case XP_ACC_AD: // because u (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CUL_ACU, CUU_ACU);// ú Ú
            }
            break;

        case XP_ACC_AE: // because i (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CIL_ACU, CIU_ACU);// í Í 
            }
            break;

        case XP_ACC_AF: // Because near Y 
            if (record->event.pressed) { // key down
                unicode_hex2output (CYL_ACU, CYU_ACU);// ý Ý
            }
            break;

        case XP_ACC_AG: // because near Y 
            if (record->event.pressed) { // key down
                unicode_hex2output (CIJL_BI, CIJU_BI);// ĳ Ĳ
            }
            break;

        case XP_ACC_AH: // because c (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CCL_CDL, CCU_CDL);// ç Ç
            }
            break;

        case XP_ACC_AI: // because ring-finger left is o (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (COL_STK, COU_STK);// ø Ø
            }
            break;

        case XP_ACC_AJ: // because pinky finger left is a 
            if (record->event.pressed) { // key down
                unicode_hex2output (CAL_RNG, CAU_RNG);// å Å
            }
            break;

   // ------------------------- row 3
        case XP_ACC_BA: // because a 
            if (record->event.pressed) { // key down
                unicode_hex2output (CAL_DIA, CAU_DIA);// ä Ä
            }
            break;

        case XP_ACC_BB: // because o (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (COL_DIA, COU_DIA);// ö Ö
            }
            break;

        case XP_ACC_BC: // because e (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CEL_DIA, CEU_DIA);// ë Ë
            }
            break;

        case XP_ACC_BD: // because u (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CUL_DIA, CUU_DIA);// ü Ü
            }
            break;

        case XP_ACC_BE: // because i
            if (record->event.pressed) { // key down
                unicode_hex2output (CIL_DIA, CIU_DIA);// ï Ï
            }
            break;

        case XP_ACC_BF: // because near y
            if (record->event.pressed) { // key down
                unicode_hex2output (CYL_DIA, CYU_DIA);// ÿ Ÿ
            }
            break;

        case XP_ACC_BG: // because vague logic about other hand having ae near on similar fingers
            if (record->event.pressed) { // key down
                unicode_hex2output (COEL_BI, COEU_BI);// œ Œ
            }
            break;

        case XP_ACC_BH: // because near œ, toward the side of a (pinky)
            if (record->event.pressed) { // key down
                unicode_hex2output (CAEL_BI, CAEU_BI);// æ Æ
            }
            break;

        case XP_ACC_BI: // because n
            if (record->event.pressed) { // key down
                unicode_hex2output (CNL_TLD, CNU_TLD);// ñ Ñ
            }
            break;

        case XP_ACC_BJ: // because s
            if (record->event.pressed) { // key down
                unicode_hex2output_single (CSL_SHP);// ß ß
            }
            break;

        case XP_ACC_BK: // because roughly the location on French keyboard
            if (record->event.pressed) { // key down
                unicode_hex2output_single (C_MU_L);// μ
            }
            break;

   // ------------------------- row 2
        case XP_ACC_CA: // because a
            if (record->event.pressed) { // key down
                unicode_hex2output (CAL_GRA, CAU_GRA);//à À
            }
            break;

        case XP_ACC_CB: // because o (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (COL_GRA, COU_GRA);// ò Ò
            }
            break;

        case XP_ACC_CC: // because e (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CEL_GRA, CEU_GRA);// è È
            }
            break;

        case XP_ACC_CD: // because u (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CUL_GRA, CUU_GRA);// ù Ù
            }
            break;

        case XP_ACC_CE: // because i (Dvorak)
            if (record->event.pressed) { // key down
                unicode_hex2output (CIL_GRA, CIU_GRA);// ì Ì
            }
            break;

        case XP_ACC_CF: // because other hand same finger i
            if (record->event.pressed) { // key down
                unicode_hex2output (CIL_CAR, CIU_CAR);// î Î
            }
            break;

        case XP_ACC_CG: // because  other hand same finger u 
            if (record->event.pressed) { // key down
                unicode_hex2output (CUL_CAR, CUU_CAR);// û Û
            }
            break;

        case XP_ACC_CH: // because  other hand same finger e 
            if (record->event.pressed) { // key down
                unicode_hex2output (CEL_CAR, CEU_CAR);// ê Ê
            }
            break;

        case XP_ACC_CI: // because  other hand same finger o 
            if (record->event.pressed) { // key down
                unicode_hex2output (COL_CAR, COU_CAR);// ô Ô
            }
            break;

        case XP_ACC_CJ: // because  other hand same finger a 
            if (record->event.pressed) { // key down
                unicode_hex2output (CAL_CAR, CAU_CAR);// â Â
            }
            break;

# endif // REMOVE_ACC // This cuts out the whole _ACC layer.


        /* _DRA layer definitions. */


# ifndef REMOVE_DRA // This cuts out the whole _DRA layer
   // ------------------------- row 4
        case XP_DRA_AA: // because '", the opening „“ at the ‛open’ of the keyboard (left/up)
            if (record->event.pressed) { // key down

                unicode_hex2output (CS_DQUHR, CS_DQUL);// “ „

            }
            break;

        case XP_DRA_AB: // because to the right of opening “, ≤ on <
            if (record->event.pressed) { // key down

                unicode_hex2output (CS_DQUH, CS_ELTHAN);// ” ≤

            }
            break;

        case XP_DRA_AC: // because this is where the £ is on an English keyboard, on 'any' money symbols ¤; ≥ on >
            if (record->event.pressed) { // key down

                unicode_hex2output (CS_POUND, CS_EGTHAN);// £ ≥

            }
            break;

        case XP_DRA_AD: // because ∅ looks like ¢, and ¢ (cent) is on $ (money) ?
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_4THROW
                unicode_hex2output (CS_NONE, CS_CENT);// ∅ ¢
#     else
                unicode_hex2output_single (CS_NONE);// ∅ ¢
#     endif

            }
            break;

        case XP_DRA_AE: // because percentages %‰‱ and money ƒ are numerical ?
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_4THROW
                unicode_hex2output (CS_PLMI, CS_LGULDEN);// ± ƒ
#     else
                unicode_hex2output_single (CS_PLMI);// ±
#     endif

            }
            break;

        case XP_DRA_AF: // Because left of 🙂, on top of ★
            if (record->event.pressed) { // key down

                unicode_hex2output (CS_FLEUR, CS_HEART);// ❦ ♥

            }
            break;

        case XP_DRA_AG: // because 😊 ⍨ 
            if (record->event.pressed) { // key down

                unicode_hex2output (CS_SMIL, CS_SAD_);// 🙂 🙁

            }
            break;

        case XP_DRA_AH: // because «no reason», next to 😊 (emoticons)
            if (record->event.pressed) { // key down

                unicode_hex2output (CS_THUP, CS_THDN);// 👍 👎

            }
            break;

        case XP_DRA_AI: // because (
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_4THROW
                unicode_hex2output (CS_OPSUP, CS_OPSUB);// ⁽ ₍
#     endif

            }
            break;

        case XP_DRA_AJ: // because )
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_4THROW
                unicode_hex2output (CS_CPSUP, CS_CPSUB);// ⁾ ₎
#     endif

            }
            break;

   // ------------------------- row 3
        case XP_DRA_BA: // because 1
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_1SUP, CN_1SUB);// ¹ ₁
#     else
                unicode_hex2output_single (CN_1SUP);// ¹ 
#     endif

            }
            break;

        case XP_DRA_BB: // because 2
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_2SUP, CN_2SUB);// ² ₂
#     else
                unicode_hex2output_single (CN_2SUP);// ²
#     endif

            }
            break;

        case XP_DRA_BC: // because 3
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_3SUP, CN_3SUB);// ³ ₃
#     else
                unicode_hex2output_single (CN_3SUP);// ³
#     endif

            }
            break;

        case XP_DRA_BD: // because 4
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_4SUP, CN_4SUB);// ⁴ ₄
#     else
                unicode_hex2output_single (CN_4SUP);// ⁴
#     endif

            }
            break;

        case XP_DRA_BE: // because 5
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_5SUP, CN_5SUB);// ⁵ ₅
#     else
                unicode_hex2output_single (CN_5SUP);// ⁵
#     endif

            }
            break;

        case XP_DRA_BF: // because 6
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_6SUP, CN_6SUB);// ⁶ ₆
#     else
                unicode_hex2output_single (CN_6SUP);// ⁶
#     endif

            }
            break;

        case XP_DRA_BG: // because 7
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_7SUP, CN_7SUB);// ⁷ ₇
#     else
                unicode_hex2output_single (CN_7SUP);// ⁷
#     endif

            }
            break;

        case XP_DRA_BH: // because 8
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_8SUP, CN_8SUB);// ⁸ ₈
#     else
                unicode_hex2output_single (CN_8SUP);// ⁸
#     endif

            }
            break;

        case XP_DRA_BI: // because 9
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_9SUP, CN_9SUB);// ⁹ ₉
#     else
                unicode_hex2output_single (CN_9SUP);// ⁹
#     endif

            }
            break;

        case XP_DRA_BJ: // because 0
            if (record->event.pressed) { // key down

#     ifdef SUB_SCRIPT_NUMS 
                unicode_hex2output (CN_0SUP, CN_0SUB);// ⁰ ₀
#     else
                unicode_hex2output_single (CN_0SUP);// ⁰
#     endif

            }
            break;

   // ------------------------- row 2
        case XP_DRA_CA: // because [
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_2NDROW
                unicode_hex2output (CS_OCBRA, CB_HHORI);// 「 ━
#     else
                unicode_hex2output_single (CB_HHORI);// ━
#     endif

            }
            break;

        case XP_DRA_CB: // because ]
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_2NDROW
                unicode_hex2output (CS_CCBRA, CB_LHORI);// 」 ─
#     else
                unicode_hex2output_single (CB_LHORI);// ─
#     endif

            }
            break;

        case XP_DRA_CC: // because «no reason»
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_2NDROW
                unicode_hex2output (CS_DEGREE, CS_CIRCLE);// ° 〇
#     else
                unicode_hex2output_single (CS_DEGREE);// °
#     endif

            }
            break;

        case XP_DRA_CD: // because «no reason»
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_2NDROW
                unicode_hex2output (CS_BULLET, CS_PARA);// • §
#     else
                unicode_hex2output_single (CS_BULLET);// •
#     endif

            }
            break;

        case XP_DRA_CE: // because «no reason»
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_2NDROW
                unicode_hex2output (CS_ELLIPS, CS_MIDDOT);// … ·
#     else
                unicode_hex2output_single (CS_ELLIPS);// … 
#     endif

            }
            break;

        case XP_DRA_CF: // because «no reason» (+ resembles ‛☒’ ?), ✗
            if (record->event.pressed) { // key down
                unicode_hex2output (CS_CHECK_B, CS_CHECK_N);// ☐ ☒
            }
            break;
# endif

        // This one must be included for _RAR layer
        case XP_DRA_CG: // because next to ✗ ☐ ☒
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_2NDROW
                unicode_hex2output (CS_CHECK_Y, CS_CHECK_H);// ☑ 🗹
#     else
                unicode_hex2output_single (CS_CHECK_Y);// ☑ 
#     endif

            }
            break;

# ifndef REMOVE_DRA // This cuts out the whole _DRA layer
        case XP_DRA_CH: // because ?
            if (record->event.pressed) { // key down
                unicode_hex2output (CQU_INV, CEX_INV);// ¿ ¡
            }
            break;

        case XP_DRA_CI: // because {, ┄ «no reason» (opposite side from ━)
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_2NDROW
                unicode_hex2output (CS_ODABRA, CB_LHORID);// 《 ┄ 
#     else
                unicode_hex2output_single (CB_LHORID);// ┄ 
#     endif

            }
            break;

        case XP_DRA_CJ: // because }, ┅ «no reason» (opposite side from ─)
            if (record->event.pressed) { // key down

#     ifdef FULL_DRA_2NDROW
                unicode_hex2output (CS_CDABRA, CB_HHORID);// 》 ┅
#     else
                unicode_hex2output_single (CB_HHORID);// ┅
#     endif
            }
            break;
# endif // REMOVE_DRA


        /* _BON layer definitions. Due to running out of X(…), XP(…) space.*/

   // ------------------------- row 4
# ifndef REMOVE_BON // Removes this layer entirely, if set.
        case XP_BON_AA: // because of ' "
            if (record->event.pressed) { // key down

#     ifdef FULL_BON_4THROW
                unicode_hex2output (CS_HQUOSB, CS_USER_DEFINED);// ‛ 🛠
#     else
                unicode_hex2output_single (CS_HQUOSB);// ‛ 
#     endif

            }
            break;

        case XP_BON_AB: // because of <, because "WASD" on _MOV
   //  0x2019, single quotation mark: ’
   // 0x2B06 arrow up: ⬆
            if (record->event.pressed) { // key down
                unicode_hex2output (CS_HQUOSE, CS_ARR_UP);// ’ ⬆
            }
            break;

        case XP_BON_AC: // because of >
   // 0x00A4 any currency symbol: ¤
   // 0x1F12F  Copyleft: 🄯 (means free to copy, see also © for not free to copy.)
            if (record->event.pressed) { // key down

#     ifdef FULL_BON_4THROW
            unicode_hex2output (CS_CURREN, CS_COPYL);// ¤ 🄯 
#     else
            unicode_hex2output_single (CS_CURREN);// ¤
#     endif

            }
            break;

        case XP_BON_AD: // because $ and ¢ can be about money, and money is often added together
                        // because … no reason, left over space.
   //  0x2211,  summation: ∑
   //  0xA9, copyright: ©
            if (record->event.pressed) { // key down

#     ifdef FULL_BON_4THROW
            unicode_hex2output (CS_CUMMU, CS_COPY);// ∑ ©
#     else
            unicode_hex2output_single (CS_CUMMU);// ∑
#     endif

            }
            break;

        case XP_BON_AE: // because % for percent
   //  0x2030,//  promille: ‰
   //  0x2031,//  pro ten thousandth: ‱
            if (record->event.pressed) { // key down

#     ifdef FULL_BON_4THROW
                unicode_hex2output (CS_PROM, CS_PROTT);// ‰ ‱
#     else
                unicode_hex2output_single (CS_PROM);// ‰
#     endif

            }
            break;

        case XP_BON_AF: // Because ♥ is a star, ❦ and stars can be used as bullet points
   //  0x2605, star: ★
   //  0x066D, star small: ٭
            if (record->event.pressed) { // key down

#     ifdef FULL_BON_4THROW
                unicode_hex2output (CS_STARB, CS_STARL);// ★ ٭
#     else
                unicode_hex2output_single (CS_STARB);// ★
#     endif

            }
            break;

        case XP_BON_AG: // because of 🙂 🙁
   //  0x1f60A,// <smile> ^^  😊
   //  0x2368,//  "Squiggly" face <sad>  ⍨

#     ifdef FULL_BON_4THROW
            if (record->event.pressed) { // key down
                unicode_hex2output (CS_SMILP, CS_SQUIG);// 😊 ⍨
            }
#     endif

            break;

        case XP_BON_AH: // because * also for multiply, because asterisk *
   //  0x00D7,//  multiply: ×
   //  0x20F0     high asterisk:  ⃰(this thing seems to behave a bit weird in vim(1) or terminal)
            if (record->event.pressed) { // key down

#     ifdef FULL_BON_4THROW
                unicode_hex2output (CS_MULT, CS_ASTL);// ×  ⃰
#     else
                unicode_hex2output_single (CS_MULT);// × 
#     endif

            }
            break;

        case XP_BON_AI: // because ø sort of seems to divide something, and √ also does that, and close to ⁻⁺ (exponential)
   //  0x221A,//  square root: √
            if (record->event.pressed) { // key down

#     ifdef FULL_BON_4THROW
            unicode_hex2output_single (CS_SQRT);// √ 
#     endif

            }
            break;

        case XP_BON_AJ: // because å points in the circle where this exponential minus goes, and it is right/"up" on the board
                        // because ⁻⁺ belong together
   //  0x207B,//  exponential minus sign: ⁻
   //  0x207A,//  exponential plus: ⁺

#     ifdef FULL_BON_4THROW
            if (record->event.pressed) { // key down
                unicode_hex2output (CS_EXPMIN, CS_EXPPLS);// ⁻ ⁺
            }
#     endif

            break;

   // ------------------------- row 3
        case XP_BON_BA: // because 1, because "WASD" on _MOV (depending on setup)
   //  0x2460,   "1" : ①
   //  0x2B05, arrow left: ⬅
            if (record->event.pressed) { // key down
                unicode_hex2output (CN_1CIRC, CS_ARR_LE);// ① ⬅
            }
            break;

        case XP_BON_BB: // because 2, because "WASD" on _MOV (depending)
   //  0x2461,   "2" : ② 
   //  0x2B07, arrow down: ⬇
            if (record->event.pressed) { // key down
                unicode_hex2output (CN_2CIRC, CS_ARR_DN);// ② ⬇
            }
            break;

        case XP_BON_BC: // because 3, because "WASD" on _MOV (depending)
   //  0x2462,   "3" : ③
   //  0x27A1, arrow right: ➡
            if (record->event.pressed) { // key down
                unicode_hex2output (CN_3CIRC, CS_ARR_RI);// ③ ➡
            }
            break;

        case XP_BON_BD: // because 4, because ┏ forms a box with the other box drawings to the right/down
   //  0x2463,   "4" : ④
   //  0x250F, box drawing heavy: ┏
            if (record->event.pressed) { // key down

#     ifdef BOX_DRAWINGS
                unicode_hex2output (CN_4CIRC, CB_C_RIDN);// ④ ┏
#     else
                unicode_hex2output_single (CN_4CIRC);// ④
#     endif

            }
            break;

        case XP_BON_BE: // because 5, because ┓ forms a box
   //  0x2513,box drawing heavy: ┓
            if (record->event.pressed) { // key down

#     ifdef BOX_DRAWINGS
                unicode_hex2output (CN_5CIRC, CB_C_LEDN);// ⑤ ┓
#     else
                unicode_hex2output_single (CN_5CIRC);// ⑤ 
#     endif

            }
            break;

        case XP_BON_BF: // because 6, because ┃ continues box block
   //  0x2465,   "6" : ⑥
   //  0x2503, box drawing heavy: ┃
            if (record->event.pressed) { // key down

#     ifdef BOX_DRAWINGS
                unicode_hex2output (CN_6CIRC, CB_VE);// ⑥ ┃
#     else
                unicode_hex2output_single (CN_6CIRC);// ⑥ 
#     endif

            }
            break;

        case XP_BON_BG: // because 7, because ┇ continues box block
   //  0x2466,   "7" : ⑦
   //  0x2507,    dotted line verticle (heavy): ┇
            if (record->event.pressed) { // key down

#     ifdef BOX_DRAWINGS
                unicode_hex2output (CN_7CIRC, CB_VE_DOT);// ⑦ ┇
#     else
                unicode_hex2output_single (CN_7CIRC);// ⑦ 
#     endif

            }
            break;

        case XP_BON_BH: // because 8, ╋ because 8 also has a crossing line in it
   //  0x254B, crossing lines: ╋
   //  0x2467,   "8" : ⑨
            if (record->event.pressed) { // key down

#     ifdef BOX_DRAWINGS
                unicode_hex2output (CN_8CIRC, CB_VE_BI);// ⑧ ╋
#     else
                unicode_hex2output_single (CN_8CIRC);// ⑧ 
#     endif

            }
            break;

        case XP_BON_BI: // because 9
   //  0x2468,   "9" : ⑨
   //  0x2513,box drawing heavy: ┓
            if (record->event.pressed) { // key down

                unicode_hex2output_single (CN_9CIRC);// ⑨ 

            }
            break;

        case XP_BON_BJ: // because 0, because a "0" can also be a symbol for infinity, round & round
   //  0x24EA,   "0" : ⓪
   //  0x221E,//  infinity:∞
            if (record->event.pressed) { // key down
                unicode_hex2output (CN_0CIRC, CS_INFIN);// ⓪ ∞
            }
            break;

        case XP_BON_BK: // because -, because ~
   //  0x2014,// dash: — (might not render differently than a hyphen - in some applications. Dash is longer).
   //  0x2248,// about equal to: ≈
            if (record->event.pressed) { // key down
                unicode_hex2output (CS_DASH, CS_ABOUT);// — ≈
            }
            break;

   // ------------------------- row 2
        case XP_BON_CA: // because 1 above, because 「[
   //  0x2039, opening single corner quotation: ‹
            if (record->event.pressed) { // key down
                unicode_hex2output_single (CS_GUILSLE);//  ‹
            }
            break;

        case XP_BON_CB: // because 2 above, because 」]
   //  0x203A, closing sinle corner quotation: ›
            if (record->event.pressed) { // key down
                unicode_hex2output_single (CS_GUILSRI);//  ›
            }
            break;

        case XP_BON_CC: // because 3 above, because / (division)
   //  0x00F7,//  division: ÷
            if (record->event.pressed) { // key down
                unicode_hex2output_single (CS_DIVI);//  ÷
            }
            break;

        case XP_BON_CD: // because 4 above, ┗ because forms box
   //  0x261E, hand bullet point: ☞
   //  0x2517, box drawing heavy: ┗
            if (record->event.pressed) { // key down
#    ifdef BOX_DRAWINGS
                unicode_hex2output (CS_FINGER, CB_C_RIUP);//  ☞ ┗
#    else
                unicode_hex2output_single (CS_FINGER);//  ☞
#    endif

            }
            break;

        case XP_BON_CE: // because 5 above, because =, ┛ because forms box
   //  0x2260,//  inequal: ≠
   //  0x251B, box drawing heavy: ┛
            if (record->event.pressed) { // key down

#    ifdef BOX_DRAWINGS
                unicode_hex2output (CS_UNEQL, CB_C_LEUP);//  ≠ ┛
#    else
                unicode_hex2output_single (CS_UNEQL);//  ≠
#    endif

            }
            break;

        case XP_BON_CF: // because ☒ , ┣ box drawings block, some place
   //  0x2717, cross mark: ✗ (complements ✓)
   //  0x2523, box drawing: ┣
            if (record->event.pressed) { // key down

#    ifdef BOX_DRAWINGS
                unicode_hex2output (CS_BOTCH, CB_VE_RI);//  ✗ ┣
#    else
                unicode_hex2output_single (CS_BOTCH);//  ✗ 
#    endif

            }
            break;

        case XP_BON_CG: // because 7 above, because ☑ 🗹 , ┫ complements with key to its left
   //  0x2713, checkmark: ✓ 
   //  0x252B, box drawing: ┫

            if (record->event.pressed) { // key down
#    ifdef BOX_DRAWINGS
                unicode_hex2output (CS_CHECK, CB_VE_LE);//  ✓ ┫
#    else
                unicode_hex2output_single (CS_CHECK);//  ✓
#    endif

            }
            break;

        case XP_BON_CH: // because 8 above, because ¡ (inverted exclamation mark)
   //  0x26A0,//  alert: ⚠
            if (record->event.pressed) { // key down
                unicode_hex2output_single (CS_ALERT);//  ⚠
            }
            break;

        case XP_BON_CI: // because 9 above, because 《
   //  0xAB, French quotation opening: «
            if (record->event.pressed) { // key down
                unicode_hex2output_single (CS_GUILLE);//  «
            }
            break;

        case XP_BON_CJ: // because 0 above, because 》
   //  0xBB, French quotation closing: »
            if (record->event.pressed) { // key down
                unicode_hex2output_single (CS_GUILRI);//  »
            }
            break;

# endif // REMOVE_BON 

// Hebrew
# if defined(BASE_HEBREW__DEF_BASE) || defined(BASE_HEBREW__ALT_BASE)
// The layout follows a standard hebrew keyboard, with the exception
// of ק, which is displaced by “.>” copied from the Dvorak layout.

        // HEBREW_DVORAK
        // These letters on the upper left follow Dvorak layout.
        // The reason is space on the device: these are not macros.
        // Also: typing compatibility between Dvorak and Hebrew
        // for these similar/same symbols: ,<.>. Idealy these symbols
        // should be the hebrew variation, if space allows it.

# if defined(HEBREW_ISRAEL)

        case XP_HEB_AA: //
            if (record->event.pressed) { // key down
                // These shifts-up seem to work on GNU/Debian/Linux, otherwise it prints ':'
                if (shift_ison) send_string ( SS_UP(X_RSFT) SS_UP(X_LSFT) ";" ); // moved here from <esc> on standard hebrew
                else send_string  ("/");//
            } break;

        case XP_HEB_AB: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_GERSH);// ׳
            }
            break;
        
        case XP_HEB_AC: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_QOF);// ק
            }
            break;

# elif defined(HEBREW_QWERTY)

        case XP_HEB_AA: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_TAV);// ת
            }
            break;

        case XP_HEB_AB: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_TSDIS);// ץ 
            }
            break;

        case XP_HEB_AC: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_QOF);// ק
            }
            break;

# endif // #HEBREW_*

        case XP_HEB_AD: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_RESH);// ר
            }
            break;

        case XP_HEB_AE: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_ALEF);// א
    
            }
            break;

        case XP_HEB_AF: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_TET);// ט
            }
            break;

        case XP_HEB_AG: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_VAV);// ו
            }
            break;

        case XP_HEB_AH: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_NUNS);// ן
            }
            break;

        case XP_HEB_AI: 
            if (record->event.pressed) { // key down

# if   defined(HEBREW_ISRAEL)
                        // The logic is that it mirrors '", “„, ”≤, ‛’ in Dvorak Base and other layers.
                        // Therefore the little and ring fingers are used. Mirroring ━─ and ┄┅ on DRA_
                        // layer, the outside on the keyboard is “big/fat”, the inside is “small/thin”,
                        // like something protected in a shell. Hence: ……׳״
                unicode_hex2output_single (HB_MEMS);// ם // ׳ is located elsewhere
# elif defined(HEBREW_QWERTY) || defined(HEBREW_DVORAK)
                unicode_hex2output (HB_MEMS, HB_GERSH);// ם׳
# endif

            }
            break;

        case XP_HEB_AJ: //
            if (record->event.pressed) { // key down

# if   defined(HEBREW_ISRAEL)
                unicode_hex2output_single (HB_PE);// פ // ״ is located elsewhere
# elif defined(HEBREW_QWERTY) || defined(HEBREW_DVORAK)
                unicode_hex2output (HB_PE, HB_GRSHM);// פ״
# endif

            }
            break;

   // ------------------------- row 3
        case XP_HEB_BA: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_SHIN);// ש
            }
            break;

        case XP_HEB_BB: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_DALET);// ד
            }
            break;

        case XP_HEB_BC: //Right-left-mark to the first free strong homerow finger on the left (middle)
            if (record->event.pressed) { // key down
                unicode_hex2output (HB_GIMEL, HB_RLM);// ג {RLM}
            }
            break;

        case XP_HEB_BD: // The logic is that כ is the same key as 4 on another layer, which connects
                        // with $, and other currencies in the same region (ƒ£). 
            if (record->event.pressed) { // key down
                unicode_hex2output (HB_KAF, HB_SHEKL);// כ₪
            }
            break;

        case XP_HEB_BE: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_AYIN);// ע
            }
            break;

        case XP_HEB_BF: // 
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_YOD);// י
            }
            break;

        case XP_HEB_BG: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_GET);// ח
            }
            break;

        case XP_HEB_BH: //
            if (record->event.pressed) { // key down
                unicode_hex2output (HB_LAMED, HB_LRM);// ל {LRM}
            }
            break;

        case XP_HEB_BI: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_KAFS);// ך
            }
            break;

        case XP_HEB_BJ: //
            if (record->event.pressed) { // key down

# if   defined(HEBREW_ISRAEL) || defined(HEBREW_QWERTY)
                if (shift_ison) send_string (":"); // : (the hebrew eqquivalent is apparently almost never used, and this saves space)
                else unicode_hex2output_single (HB_PES);// ף
# elif defined(HEBREW_DVORAK)
                unicode_hex2output_single (HB_PES);// ף
# endif 

            }
            break;

# if defined(HEBREW_ISRAEL)
        case XP_HEB_BK: // 
            if (record->event.pressed) { // key down
                if (shift_ison) unicode_hex2output_single (HB_GRSHM);// ״
                else send_string (","); // comma
            }
            break;
# endif

        case XP_HEB_MQF: // ־ Maqaf
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_MAQAF);// ־ 
            }
            break;

   // ------------------------- row 2
        case XP_HEB_CA: //
            if (record->event.pressed) { // key down
// Hebrew harmonization + ':'
# if   defined(HEBREW_ISRAEL) || defined(HEBREW_QWERTY)
                unicode_hex2output_single (HB_ZAYIN);// ז
# elif defined(HEBREW_DVORAK)
                if (shift_ison) send_string (":"); //
                else unicode_hex2output_single (HB_ZAYIN);// ז
# endif
            }
            break;

        case XP_HEB_CB: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_SAMEG);// ס
            }
            break;

        case XP_HEB_CC: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_BET);// ב
            }
            break;

        case XP_HEB_CD: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_HE);// ה
            }
            break;

        case XP_HEB_CE: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_NUN);// נ
            }
            break;

        case XP_HEB_CF: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_MEM);// מ
            }
            break;

        case XP_HEB_CG: //
            if (record->event.pressed) { // key down
                unicode_hex2output_single (HB_TSADI);// צ 
            }
            break;

#     if defined(HEBREW_ISRAEL) || defined(HEBREW_DVORAK)
        case XP_HEB_CH: //
            if (record->event.pressed) { // key down

#         if defined(HEBREW_ISRAEL)
                if (shift_ison) send_string ("<"); // 
                else unicode_hex2output_single (HB_TAV);// ת
#         else // HEBREW_DVORAK
                unicode_hex2output_single (HB_TAV);// ת
#         endif 

            }
            break;

        case XP_HEB_CI: //
            if (record->event.pressed) { // key down

#         if defined(HEBREW_ISRAEL)
                if (shift_ison) send_string (">"); // 
                else unicode_hex2output_single (HB_TSDIS);// ץ
#         else // HEBREW_DVORAK
                unicode_hex2output_single (HB_TSDIS);// ץ
#         endif 

            }
            break;

        case XP_HEB_CJ: // anomaly
            if (record->event.pressed) { // key down

#         if defined(HEBREW_ISRAEL)
                if (shift_ison) send_string ("?"); // 
                else send_string ("."); // 
#         else // HEBREW_DVORAK
                unicode_hex2output_single (HB_QOF);// ק
#         endif 

            }
            break;
#     endif // HEBREW_*

    // HB_D_VAV,
    // HB_VAVYD,
    // HB_D_YOD,
# endif // Hebrew Base layer
    }

    return true;
};
