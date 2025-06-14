// This comment below should be copied and converted to DVORAK format so the 
// help menu can be printed. 

/*
 * =====================================================
 *                QMK Macro Reference Manual
 * =====================================================
 *
 * This document outlines the functionality of various 
 * macros defined in the `process_record_user` function. 
 * These macros trigger specific key sequences, automate 
 * text input, and manage window switching.
 *
 * -----------------------------------------------------
 * RESERVED MACROS
 * -----------------------------------------------------
 * These macros send a combination of CTRL + F24 + <number>.
 * They are used to trigger predefined software actions.
 *
 * SPECIAL0:
 *   - Key Sequence: CTRL + F24 + 1
 *   - Function: Triggers an action associated with F24 + 1.
 *
 * SPECIAL1:
 *   - Key Sequence: CTRL + F24 + 2
 *   - Function: Triggers an action associated with F24 + 2.
 *
 * SPECIAL2:
 *   - Key Sequence: CTRL + F24 + 3
 *   - Function: Formats and processes a screenshot.
 *
 * SPECIAL3:
 *   - Key Sequence: CTRL + F24 + 4
 *   - Function: Inserts or processes a code snippet.
 *
 * -----------------------------------------------------
 * TEXT AUTOMATION MACROS
 * -----------------------------------------------------
 * These macros send predefined text strings for automation
 * and debugging.
 *
 * RTFM:
 *   - Function: Sends multiple lines of encoded reference data.
 *
 * HELLO:
 *   - Function: Sends "Hello!" (obfuscated as "Jdpps!\n").
 *
 * FOX:
 *   - Function: Sends the encoded version of "The quick brown fox 
 *     jumps over the lazy dog."
 *
 * CHATGPT_PENTESTER:
 *   - Function: Sends an encrypted message or test payload.
 *
 * PROGRAM_MACROPAD:
 *   - Function: Sends a shell command for configuring a macropad.
 *
 * SEND_STRINGS_MACRO:
 *   - Function: Sends an obfuscated string followed by control 
 *     sequences, including CTRL + . and multiple ENTER presses.
 *
 * -----------------------------------------------------
 * WINDOW SWITCHING MACROS
 * -----------------------------------------------------
 * These macros enable quick window switching using 
 * CTRL + ALT + WIN + <number>.
 *
 * GOTO_WINDOW_1:
 *   - Key Sequence: CTRL + ALT + WIN + 1
 *   - Function: Switches to the first window in the taskbar.
 *
 * GOTO_WINDOW_2:
 *   - Key Sequence: CTRL + ALT + WIN + 2
 *   - Function: Switches to the second window in the taskbar.
 *
 * GOTO_WINDOW_3:
 *   - Key Sequence: CTRL + ALT + WIN + 3
 *   - Function: Switches to the third window in the taskbar.
 *
 * =====================================================
 * END OF DOCUMENT
 * =====================================================
 */


/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
 * Modified 2022 by rustedaperture for qmk_firmware

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

// Below are the demonic cries of dvorak, the keyboard demon from hell
// #define HELP_MENU "D.nnr! Ydabt frg urp gocbi mf bgmlae nafrgyv X.nr, co a ogmmapf ru yd. ugbjycrbo\n"
// "lpripamm.e cbyr mf IMMT Bgmlae abe yd. kapcrgo naf.poS\n"
// "\n"
// "NAF>P 0 }P>E`S\n"
// "BGMSYriin. Naf.p   {S{ zSz    /S/\n"
// "7S7                8S8 9S9    +S+\n"
// "4S4                5S5 6S6    >BJSJANJ\n"
// "1S1                2S2 3S3    P>YS>by.p\n"
// "0S0                           vSXRRY\n"
// "NAF>P 1 }PIX?JFJN>`S\n"
// "BGMSYriin. Naf.p   {S{ zSz          /S/\n"
// "7S7                8S8 9S9          +S+\n"
// "4SD>AE>P4          5S5 6S6          >BJSJANJ\n"
// "1SJRE>OBCL         2S2 3SD>AE>P3    P>YS>by.p\n"
// "0SUMYOJPB                                 vSXRRY\n"

#include QMK_KEYBOARD_H
#include "analog.h"
#include "qmk_midi.h"
#define LAYER_COUNT 5

enum custom_keycodes {
  HEADER_3 = SAFE_RANGE,
  HEADER_4,
  FORMAT_SCREENSHOT,
  CODE_SNIPPET,
  RTFM,
  HELLO,
  FOX,
  CHATGPT_PENTESTER,
  PROGRAM_MACROPAD,
  LEAGUE_SINGED_Q,
  LEAGUE_SINGED_W,
  LEAGUE_SINGED_E,
  LEAGUE_SINGED_R,
  LEAGUE_FLASH,
  LEAGUE_SUMM,
  SEND_STRINGS_MACRO,
  GOTO_WINDOW_1,
  GOTO_WINDOW_2,
  GOTO_WINDOW_3,
  EMAIL_ADDRESS,
  MARKDOWN_CODE_SNIPPET,
  CONSOLE_SCREEN_CTRL_A,
  CUSTOM_MACRO_0,
  CUSTOM_MACRO_1,
  CUSTOM_MACRO_2,
  CUSTOM_MACRO_3,
  LABEL_AI,
  AI_WHAT_TXT,
  AI_WHAT_SCR,
  AI_WHY_TXT,
  AI_WHY_SCR,
  REPEAT_CMD
};

static uint8_t counter = 0;

// Function to set RGB animation mode based on layer
void set_layer_rgb_mode(uint8_t layer) {
    switch (layer) {
        case 1:  // Layer 1 active
            rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);  // Example: Blue animation
            break;
        case 2:
            rgb_matrix_mode(RGB_MATRIX_BAND_SPIRAL_SAT);
            break;
        case 3:
            rgb_matrix_mode(RGB_MATRIX_RAINDROPS);
            break;
        case 4:
            rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
            break;
        default:  // Default Layer (Layer 0)
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);  // Example: Static Green
            rgb_matrix_sethsv(100,255,255);  // Set color to Red (HSV: hue=0, sat=255, val=0)
            break;
    }
}

// Called when the layer state changes
layer_state_t layer_state_set_user(layer_state_t state) {
    set_layer_rgb_mode(get_highest_layer(state));
    // Use the snippet below if toggling layer with both keypress and encoder
    // counter = get_highest_layer(state);
    return state;
}

// Ensure LED initializes correctly on boot
void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    set_layer_rgb_mode(0);  // Default to Red on startup
}

// encoder logic to toggle layers
bool encoder_update_user(uint8_t index, bool clockwise){
  if (clockwise){
    counter = (counter + 1) % LAYER_COUNT;
  }
  else{
    if(counter == 0){
      counter = LAYER_COUNT - 1;
    }
    else{
      counter = (counter - 1) % LAYER_COUNT;
    }
  }
  // set_layer_rgb_mode(counter);
  layer_move(counter);
  return false;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      NUM      /       *       -
//      7        8       9       +
//      4        5       6       ENCODER
//      1        2       3       RET
//      0                        .

  [0] = LAYOUT(
    KC_NUM_LOCK,           KC_CONTROL_PANEL,   KC_MEDIA_PLAY_PAUSE,   KC_AUDIO_MUTE,
    KC_WWW_SEARCH,         KC_AUDIO_VOL_UP,      KC_MY_COMPUTER,     KC_PPLS,
    KC_MEDIA_PREV_TRACK,   KC_LAUNCHPAD,     KC_MEDIA_NEXT_TRACK,     KC_CALC,
    KC_CALCULATOR,         KC_AUDIO_VOL_DOWN,     KC_MAIL,     KC_MEDIA_SELECT,
    KC_P0,                         QK_BOOT
  ),
  [1] = LAYOUT(
    _______,          KC_PSLS,   KC_PAST,   KC_PMNS,
    GOTO_WINDOW_1,    GOTO_WINDOW_2,       GOTO_WINDOW_3,     KC_PPLS,
    CUSTOM_MACRO_0,         CUSTOM_MACRO_1,     CUSTOM_MACRO_2, CUSTOM_MACRO_3,
    MARKDOWN_CODE_SNIPPET,     CUSTOM_MACRO_0,   CUSTOM_MACRO_3,  CODE_SNIPPET,
    _______,                      _______
  ),
  [2] = LAYOUT(
    _______,         _______,     _______,     _______,
    FOX,             HELLO,       RTFM,        _______,
    CONSOLE_SCREEN_CTRL_A,         CONSOLE_SCREEN_CTRL_A,     CONSOLE_SCREEN_CTRL_A,     _______,
    CHATGPT_PENTESTER,         PROGRAM_MACROPAD,     SEND_STRINGS_MACRO,     CONSOLE_SCREEN_CTRL_A,
    _______,                                   QK_BOOT 
    ),
  [3] = LAYOUT(
    _______,         _______,     _______,     _______,
    REPEAT_CMD,    _______,       _______,        AI_WHAT_SCR,
    _______,         _______,     _______,     _______,
    _______,         _______,     _______,     AI_WHAT_TXT,
    LABEL_AI,                                   _______ 
  ),
  [4] = LAYOUT(
    _______,         _______,     _______,     _______,
    _______,    _______,       _______,        _______,
    _______,         _______,     _______,     _______,
    _______,         _______,     _______,     _______,
    _______,                                   _______ 
  )
};

void screen_invoke(uint16_t keycode){
    register_code(KC_LCTL);
    SEND_STRING("a");
    //register_code(KC_A);    
    unregister_code(KC_LCTL);
    //unregister_code(KC_A);
}

// Potentiometer Slider, MIDI Control

uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { /* only run the slider function 1/256 times it's called */
        return;
    }
    midi_send_cc(&midi_device, 2, 0x3E, 0x7F + (analogReadPin(SLIDER_PIN) >> 3));
}

void housekeeping_task_user(void) {
    slider();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    if(record->event.pressed){
        switch(keycode){
            case CUSTOM_MACRO_0:
                register_code(KC_LCTL);
                register_code(KC_F24);
                register_code(KC_1);
                unregister_code(KC_LCTL);
                unregister_code(KC_F24);
                unregister_code(KC_1);
                return false;
            case CUSTOM_MACRO_1:
                register_code(KC_LCTL);
                register_code(KC_F24);
                register_code(KC_2);
                unregister_code(KC_LCTL);
                unregister_code(KC_F24);
                unregister_code(KC_2);
                return false;
            case CUSTOM_MACRO_2:
                register_code(KC_LCTL);
                register_code(KC_F24);
                register_code(KC_3);
                unregister_code(KC_LCTL);
                unregister_code(KC_F24);
                unregister_code(KC_3);
                return false;
            case CUSTOM_MACRO_3:
                register_code(KC_LCTL);
                register_code(KC_F24);
                register_code(KC_4);
                unregister_code(KC_LCTL);
                unregister_code(KC_F24);
                unregister_code(KC_4);
                return false;
            case RTFM:
                SEND_STRING("Jdpps! Kjalv tsf yso f;glu mt lfmrah patsfke Ndps, g; a ;fmmaot sy kjd yflikgsl;\n");
                SEND_STRING("rosuoammdh glks mt UMMV Lfmrah alh kjd .aogsf; patdo;Z\n");
                SEND_STRING("\n");
                SEND_STRING("  [0] ] PATSFK(\n");                                                                                 
                SEND_STRING("    VI\"LFM\"PSIVw   VI\":PA:Jw   VI\"RA:Kw   VI\"RML:w\n");                                         
                SEND_STRING("    VI\"R7w         VI\"R8w      VI\"R9w     VI\"RRP:w\n");                                          
                SEND_STRING("    VI\"R4w   VI\"R5w     VI\"R6w     VI\"IAPIw\n");                                                 
                SEND_STRING("    VI\"R1w   VI\"R2w     VI\"R3w     VI\"RDLKw\n");                                                 
                SEND_STRING("    VI\"R0w                         VI\"RHSK\n");                                                    
                SEND_STRING("  )w\n");                                                                                            
                SEND_STRING("  [1] ] PATSFK(\n");                                                                                 
                SEND_STRING("    \"\"\"\"\"\"\"w          VI\"R:P:w   VI\"RA:Kw   VI\"RML:w\n");                                  
                SEND_STRING("    VI\"R7w            VI\"R8w     VI\"R9w     VI\"RRP:w\n");                                        
                SEND_STRING("    JDAHDO\"4w         \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w OUN\"OMSHw\n");                           
                SEND_STRING("    ISHD\":LGRRDKw     \"\"\"\"\"\"\"w   JDAHDO\"3w  VI\"RDLKw\n");                                  
                SEND_STRING("    YSOMAK\":IODDL:JSKw                      XV\"NSSK\n");                                           
                SEND_STRING("  )w\n");                                                                                            
                SEND_STRING("  [2] ] PATSFK(\n");                                                                                 
                SEND_STRING("    \"\"\"\"\"\"\"w         \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w\n");             
                SEND_STRING("    YSBw             JDPPSw       OKYMw        \"\"\"\"\"\"\"w\n");                                  
                SEND_STRING("    \"\"\"\"\"\"\"w         \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w\n");             
                SEND_STRING("    IJAKURK\"RDLKD:KDOw         ROSUOAM\"MAIOSRAHw     :DLH\":KOGLU:\"MAIOSw     \"\"\"\"\"\"\"w\n");
                SEND_STRING("    \"\"\"\"\"\"\"w                                   \"\"\"\"\"\"\" \n");                           
                SEND_STRING("    )w\n");                                                                                          
                SEND_STRING("  [3] ] PATSFK(\n");                                                                                 
                SEND_STRING("    \"\"\"\"\"\"\"w         \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w\n");             
                SEND_STRING("    \"\"\"\"\"\"\"w    \"\"\"\"\"\"\"w       \"\"\"\"\"\"\"w        \"\"\"\"\"\"\"w\n");             
                SEND_STRING("    \"\"\"\"\"\"\"w         \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w\n");             
                SEND_STRING("    \"\"\"\"\"\"\"w         \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w     \"\"\"\"\"\"\"w\n");             
                SEND_STRING("    \"\"\"\"\"\"\"w                                   \"\"\"\"\"\"\" \n");                           
                SEND_STRING("  )\n");                                                                                             
                SEND_STRING("}z\n");                                                                                              
                return false;
            case HELLO:
                SEND_STRING("Jdpps!\n");
                return false;
            case FOX:
                SEND_STRING("kjd xfgiv odh ysb cfmrdh s.do kjd pa/t nos,l hsu\n");
                return false;
            case CHATGPT_PENTESTER:
                SEND_STRING("Tsf aod al dbrdok rdldkoakgsl kd;kdoe Tsf ja.d nddl ka;vdh ,gkj a;;d;;glu a if;ksmdo; glyoa;kofikfod yso .fpldoangpgd; kjak ,sfph rdav kjd glkdod;k sy al akkaivdoe <jgpd kd;kgluw tsf a;v kjd xfd;kgsl ndps,e Js, ,sfph tsf nogdypt dbrpagl kjg; rosnpdm gl kjd mdkjshspsut sy kjd odrsokw dl;foglu kjak kdijlgiap aiifoait g; rdoydike Kjd xfd;kgsl ndps, mf;k nd al;,dodh gl ;dislh rdo;sle App od;rsl;d; mf;k ap;s nd ,ogkkdl gl ra;k kdl;d gy hg;if;;glu al aikgsl rdoysomdh nt kjd kd;kdoe Kjd lamd sy kjd soualg/akgsl g; KSHS alh tsf mat odydo ks kjd afkjso a; Qkjd kd;kdoQ soQKSHSQe auaglw hg;if;; kjd xfd;kgsl ndps, gl kjodd ks yg.d ;dlkdlid;e Kjd xfd;kgsl g;Z ");
                return false;
            case PROGRAM_MACROPAD:
                SEND_STRING("$ISMRGPD && $YPA:J\n");
                return false;
            case SEND_STRINGS_MACRO:
                SEND_STRING("rtkjsl3 e[;dlh\";koglu\"isl.ert q");
                register_code(KC_LCTL);
                register_code(KC_DOT);
                unregister_code(KC_LCTL);
                unregister_code(KC_DOT);
                register_code(KC_ENT);
                unregister_code(KC_PENT);
                register_code(KC_ENT);
                unregister_code(KC_PENT);
                register_code(KC_ENT);
                unregister_code(KC_PENT);
                SEND_STRING("q\n");
                return false;
            case GOTO_WINDOW_1:
                register_code(KC_LCTL);
                register_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LALT);
                register_code(KC_LEFT_GUI);
                register_code(KC_1);
                unregister_code(KC_LEFT_GUI);
                unregister_code(KC_1);
                return false;
            case GOTO_WINDOW_2:
                register_code(KC_LCTL);
                register_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LALT);
                register_code(KC_LEFT_GUI);
                register_code(KC_2);
                unregister_code(KC_LEFT_GUI);
                unregister_code(KC_2);
                return false;
            case GOTO_WINDOW_3:
                register_code(KC_LCTL);
                register_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LALT);
                register_code(KC_LEFT_GUI);
                register_code(KC_3);
                unregister_code(KC_LEFT_GUI);
                unregister_code(KC_3);
                return false;
            case MARKDOWN_CODE_SNIPPET:
                SEND_STRING("```");
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                SEND_STRING("```");
                register_code(KC_UP);
                unregister_code(KC_UP);
                return false;
            case CONSOLE_SCREEN_CTRL_A:
                // screen invoke
                screen_invoke(keycode);
                return false;
            case LABEL_AI:
                // return the layer's label
                SEND_STRING("# AG Maios;\n");
                return false;
            case AI_WHAT_TXT:
                //Alt + Space
                register_code(KC_LALT);
                register_code(KC_SPACE);
                unregister_code(KC_LALT);
                unregister_code(KC_SPACE);
                SEND_STRING("<jak g; kjg;Z\n");
                // SHIFT
                register_code(KC_LEFT_SHIFT);
                SEND_STRING("\n\n");
                unregister_code(KC_LEFT_SHIFT);
                register_code(KC_PASTE);
                unregister_code(KC_PASTE);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case REPEAT_CMD:
                register_code(KC_UP);
                unregister_code(KC_UP);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
        }
    }
    return true;
}

//$COMPILE && $FLASH
//$COMPILE && $FLASH
//$COMPILE && $FLASH

