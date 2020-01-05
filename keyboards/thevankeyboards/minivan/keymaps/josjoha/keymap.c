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
 * Remainder: (C) 2019 by J.B. <joshb@xs4all.nl>
 *
 */

/* Todo:
 *       (unknown)
 */
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
         * Comment out if you prefer a flat "vim" type layout.
         */
 
//#define ARROWS_TRIANGLE // implies mouse is also similarly in a triangle.

         /* Uncomment below line to put the arrows on the left, comment out to have arrows right. */

//#define ARROWS_LEFT // implies mouse is right


        /* Uncomment below line to have LGUI (OS key) where RGUI is, and RGUI where LGUI is. */

#define SWITCH_GUIS // Set this if you want LGUI on the BASE layer rather than RGUI, while remaining consistent on all lyaers.


        /* Uncomment one of the below lines, determining where L-shift tap-toggles to on the BASE layer. */

//#define LSHIFT_LAYER_RAR // Be warned and don't hold it against me if you accidentally hit 'Power' at the wrong moment.
//#define LSHIFT_LAYER_MOV // Handy to have navigation on a toggle. 
                         // _MOV is the least dangerous layer to accidentally activate.
//#define LSHIFT_LAYER_DRA // _DRA is also the least easy to access layer normally, on pinky which is sortof wrong.
                         // This would help alleviate it.
//#define LSHIFT_LAYER_ACC // If typing a lot of these in a row
#define LSHIFT_LAYER_PAD // Easier Access to numpad (for default shortcuts in blender for example).


// Below here no more comfortable configuration options.....
// ---------------------------------------------------------


#ifndef SWITCH_GUIS
    #define KC__XGUI KC_LGUI
    #define KC__YGUI KC_RGUI
#endif
#ifdef SWITCH_GUIS
    #define KC__XGUI KC_RGUI
    #define KC__YGUI KC_LGUI
#endif


#include QMK_KEYBOARD_H
#define RGBLIGHT_SLEEP // QMK docs: "If defined, the RGB lighting will be switched off when the host goes to sleep"

// Layer switch TT(layer) tapping amount to make it toggle
//#define TAPPING_TOGGLE 2
#define TAPPING_TERM_HOLTAP 225 // 175 ms proved unreliable, 225 ms seems ok

#define PRESCRAMBLED_U "f"  // This is the letter 'u' for Unicode input, as effective on GNU/Debian/Linux 10 set to Dvorak
static uint16_t key_timer; // Used in _DDL to differentiate layer switching in half or full descramble mode.
                           // In 'full' mode it goes to _DDD and _DDA Unicode layers, in 'half' mode to _DRA and _ACC.

extern keymap_config_t keymap_config;


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

// Notice this order in layer_state_set_user as well, regarding the led indicators.
// Below #defines the internal order of the layers.
// The layers beginning with DD are the 'Dvorak Descramble' layers.

#define _LTR 0  // letters (Dvorak)
#define _NSY 2  // numbers and symbols
#define _FUN 11 // function keys, layer switcher, given highest order precedence just in case
#define _MOV 4  // movement arrows and mouse
#define _RAR 5  // strange keys never used, Unicode config
#define _PAD 6  // Numbers pad (these are different versions of the same symbols)
#define _ACC 7  // Accented letters 
#define _DRA 9  // Unusual symbols and whatever else
#define _DDD 10 // Descramble version of _DRA
#define _DDA 8  // Descramble version of _ACC
#define _DDN 3  // Descramble version of _NSY
#define _DDL 1  // Descramble version of _LTR
//
// The normal and Dvorak descramble BASE _DDL needs to have a low order
// number, so that the other layers can be accessed on top of it.  The rest
// of the order does not matter, but to keep the code easier the descramble
// layers are near the layer they descramble. F-keys is on top because it
// is the layers hub, although that should not matter either.
// It seems that setting the 'default' layer is not needed, no need for DF(layer).

#define _NORMAL_ 0 // Some defines to make the code a bit easier to read with regards to descramble
#define _HALF_ 1
#define _FULL_ 2
short descramble = _NORMAL_; // to remember if we are in descramble mode for 'escape'ing out of layers to the right base
                      // There are three modes: 0 for everything normal, 1 for descramble for letters and number/symbols,
                      // .. but with the normal unicode layers, and 2 for all in descramble mode, where the Unicode
                      // .. coding is for a Linux system (shift-control-U + HEX input).
                      // The 1 mode is added, for systems where the Unicode input might work the same whether or not
                      // .. the computer is already set to Dvorak. (This is untested as far as the result on  those
                      // .. systems XXX.)

//* Shift detection
// * Replaced by get_mod () (Code kept in comments in case this system breaks by updates to other sources files.)
bool shift_ison = 0; // keep track of the state of shift (Capslock is ignored). There may be more elegant code for this in
                     //   QMK (a function seems to do it?), but this is simple and keeps the issue isolated to this file.
#define TRUE 1
#define FALSE 0
bool _fun_stay = FALSE; // for making _FUN layer not return to BASE after pressing f-key
bool leds_on = TRUE; // toggle leds on/off
bool isolate_trigger = FALSE; // detects if _FUN layer shift was pressed and no other key 
 

    /* These are the accented characters of most/all western European Nations.
     * Using the Unicode input system
     */
enum unicode_names { // See below under 'unicode map' for meaning
    // For normal Dvorak BASE layer set:
    CAEL_BI,
    CAEU_BI,
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
    COEL_BI,
    COEU_BI,
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
    CIJL_BI,
    CIJU_BI,
    CS_OCBRA,
    CS_CCBRA,
    CS_ODABRA,
    CS_CDABRA,
    CS_ELLIPS,
    CS_CIRCLE,
    CN_0SUB,
    CN_0SUP,
    CN_1SUB,
    CN_1SUP,
    CN_2SUB,
    CN_2SUP,
    CN_3SUB,
    CN_3SUP,
    CN_4SUB,
    CN_4SUP,
    CN_5SUB,
    CN_5SUP,
    CN_6SUB,
    CN_6SUP,
    CN_7SUB,
    CN_7SUP,
    CN_8SUB,
    CN_8SUP,
    CN_9SUB,
    CN_9SUP,
    CS_OPSUP,
    CS_OPSUB,
    CS_CPSUP,
    CS_CPSUB,
    CS_PARA,
    CS_PLMI,
    CS_DQUL,
    CS_DQUH,
    CS_DQUHR,
    CS_MIDDOT,
    CS_BULLET,
    CS_DEGREE,
    CS_LARROW,
    CS_UARROW,
    CS_RARROW,
    CS_DARROW,
    CS_FLEUR,
    CS_HEART,
    CS_LGULDEN,
    CS_CURREN,
    CS_POUND,
    CS_CENT,
    CS_NONE,
    CS_LHORI,
    CS_HHORI,
    CS_LHORID,
    CS_HHORID,
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

    // A with ring (Scandinavia)
    [CAL_RNG] = 0x00e5, //      ''        'A' for a, 'L' for lower, "RNG" for Ring: å
    [CAU_RNG] = 0x00c5, //      ''             ''    'U' for upper,        ''     : Å

    // AE (French)          
    [CAEL_BI] = 0x00e6, //        ''        "AE" for ae, 'L' for lower        ''              : æ
    [CAEU_BI] = 0x00c6, //        ''              ''     'U' for upper,       ''              : Æ

    // OE (French)
    [COEL_BI] = 0x0153, //        ''        "AO" for ao, 'L' for lower, "BI" for two-character: œ
    [COEU_BI] = 0x0152, //        ''              ''     'U' for upper,       ''              ; Œ

    // C with cedilla
    [CCL_CDL] = 0x00e7, //      ''        'C' for c, 'L' for lower, "CDL" for cedilla: ç 
    [CCU_CDL] = 0x00c7, //      ''             ''    'U' for upper,        ''        : Ç

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

    // N with tilde
    [CNL_TLD] = 0x00f1, //      ''        'N' for n, 'L' for lower, "TLD" for tilde: ñ
    [CNU_TLD] = 0x00d1, //      ''             ''    'U' for upper,        ''      : Ñ

    //Spanish additional symbols:
    [CEX_INV] = 0x00a1, //      ''        "EX" for exclamation mark, "INV" for inverted: ¡
    [CQU_INV] = 0x00bf, //      ''        "QU" for question mark,           ''         : ¿
    
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
                            
    // O with stroke (Scandinavia)
    [COL_STK] = 0x00f8, //      ''        'O' for o, 'L' for lower, "STK" for Stroke: ø
    [COU_STK] = 0x00d8, //      ''             ''    'U' for upper,        ''       : Ø

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

    // Y with acute
    [CYL_ACU] = 0x00fd, //      ''        'Y' for y, 'L' for lower, "ACU" for Acute: ý
    [CYU_ACU] = 0x00dd, //      ''             ''    'U' for upper,        ''      : Ý
    // Y with diaereses
    [CYL_DIA] = 0x00ff, //      ''        'Y' for y, 'L' for lower, "DIA" for Diareses: ÿ
    [CYU_DIA] = 0x0178, //      ''             ''    'U' for upper,        ''         : Ÿ

    // Dutch IJ 
    [CIJL_BI] = 0x0133, //      ''        'IJ' for ij, 'L' for lower, BI for two-character: ĳ
    [CIJU_BI] = 0x0132, //      ''              ''   , 'U' for upper      ''              : Ĳ

    //German:
     // sharp s 
    [CSL_SHP] = 0x00df, //      ''         'S' for s, 'L' for lower, "SHP" for sharp: ß
  
    // Some Unicode symbols that might be handy
      // Happy symbols:
    [CS_THUP] = 0x1f44d, //      ''         'S' for symbol,  "THUP"  for <thumb up> 👍 
    [CS_SMIL] = 0x1f642, //      ''              ''          "SMIL"  for <smile> 🙂 
    [CS_YAYS] = 0x1f603, //      ''              ''          "YAYS"  for <big smile>  😃 
  
      //Sad symbols
    [CS_SAD_] = 0x1f641, //      ''              ''          "SAD_"   for  <sad face>  🙁 
    [CS_SQIG] = 0x2368,  //      ''              ''          "SQIG"  for "Squiggly" face <sad>  ⍨
    [CS_THDN] = 0x1f44e, //      ''              ''          "THDN"  for <thumb down>  👎 

     // Unusual parenthesis types
    [CS_OCBRA] = 0x300c, //      ''              ''          "O" for opening, "C" for corner, "BRA" for bracket:「
    [CS_CCBRA] = 0x300d, //      ''              ''          "C" for closing,                                  : 」
    [CS_ODABRA] = 0x300a, //     ''              ''          "O" for opening, "D" for double, "A" for angled, "BRA" for bracket:《
    [CS_CDABRA] = 0x300b, //     ''              ''          "C" for closing,      ''              ''                ''        : 》

     // currency
    [CS_LGULDEN] = 0x0192, //    ''              ''          "L" for lower, "GULDEN" for guilder: ƒ
    [CS_CURREN] = 0x00A4, //     ''              ''          "CURREN" for currency, 'any currency' symbol: ¤
    [CS_POUND] = 0x00A3, //      ''              ''          "POUND" for pound: £
    [CS_CENT] = 0x00A2, //       ''              ''          "CENT" for cent: ¢
    [CS_NONE] = 0x2205, //       ''              ''          "NONE" for empty-set / no-solution: ∅ 
    
     // circle and dots
    [CS_CIRCLE] = 0x3007, //      ''              ''          "CIRCLE" for circle: 〇
    [CS_DEGREE] = 0x00B0, //      ''              ''          "DEGREE" for degree: °
    [CS_MIDDOT] = 0x00B7, //      ''              ''          "MIDDOT" for mid dot: ·
    [CS_BULLET] = 0x2022, //      ''              ''          "BULLET" for bullet: •
    [CS_ELLIPS] = 0x2026, //      ''              ''          "ELLIPS" for bullet: …

     // super and sub script numbers
    [CN_0SUB] =  0x2080, //       ''     , N for number, "SUB" for sub-script or "SUP" for super-script:₀
    [CN_0SUP] =  0x2070, //       ''     ,    ''       ,                           ''                  :⁰
    [CN_1SUB] =  0x2081, //       ''     ,    ''       ,        ''                                     :₁
    [CN_1SUP] =  0x00B9, //       ''     ,    ''       ,                           ''                  :¹
    [CN_2SUB] =  0x2082, //       ''     ,    ''       ,        ''                                     :₂
    [CN_2SUP] =  0x00B2, //       ''     ,    ''       ,                           ''                  :²
    [CN_3SUB] =  0x2083, //       ''     ,    ''       ,        ''                                     :₃
    [CN_3SUP] =  0x00B3, //       ''     ,    ''       ,                           ''                  :³
    [CN_4SUB] =  0x2084, //       ''     ,    ''       ,        ''                                     :₄
    [CN_4SUP] =  0x2074, //       ''     ,    ''       ,                           ''                  :⁴
    [CN_5SUB] =  0x2085, //       ''     ,    ''       ,        ''                                     :₅
    [CN_5SUP] =  0x2075, //       ''     ,    ''       ,                           ''                  :⁵
    [CN_6SUB] =  0x2086, //       ''     ,    ''       ,        ''                                     :₆
    [CN_6SUP] =  0x2076, //       ''     ,    ''       ,                           ''                  :⁶
    [CN_7SUB] =  0x2087, //       ''     ,    ''       ,        ''                                     :₇
    [CN_7SUP] =  0x2077, //       ''     ,    ''       ,                           ''                  :⁷
    [CN_8SUB] =  0x2088, //       ''     ,    ''       ,        ''                                     :₈
    [CN_8SUP] =  0x2078, //       ''     ,    ''       ,                           ''                  :⁸
    [CN_9SUB] =  0x2089, //       ''     ,    ''       ,        ''                                     :₉
    [CN_9SUP] =  0x2079, //       ''     ,    ''       ,                           ''                  :⁹
    [CS_OPSUB] = 0x208D, //       ''     , S for symbol,        ''                                     :₍
    [CS_OPSUP] = 0x207D, //       ''     ,    ''       ,                           ''                  :⁽
    [CS_CPSUB] = 0x208E, //       ''     ,    ''       ,        ''                                     :₎
    [CS_CPSUP] = 0x207E, //       ''     ,    ''       ,                           ''                  :⁾

    // Symbols from Dutch typewriter, other Dutch 
    [CS_PARA] = 0x00A7,  //       ''     , S for symbol, "PARA" for paragraaf: §
    [CS_PLMI] = 0x00B1,  //       ''     ,    ''       , "PLMI" for plus-minus; ±
    [CS_DQUL] = 0x201E,  //       ''     ,    ''       , "D" for double, "QU" for quote, "L" for low: „
    [CS_DQUH] = 0x201D,  //       ''     ,    ''       ,      ''       ,       ,,      , "H" for high: ”
    [CS_DQUHR] = 0x201C, //       ''     ,    ''       ,      ''       ,       ,,      , "H" for high, "R" for reverse: “
    // arrows
    [CS_LARROW] = 0x2B98, //      ''     ,    ''       , "L" for Left, "ARROW" for arrow: ⮘
    [CS_UARROW] = 0x2B99, //      ''     ,    ''       , "U" for UP,            ''      : ⮙
    [CS_RARROW] = 0x2B9A, //      ''     ,    ''       , "R" for Right,         ''      : ⮚
    [CS_DARROW] = 0x2B9B, //      ''     ,    ''       , "D" for Down,          ''      : ⮛
    // ornamental, heart
    [CS_FLEUR] = 0x2766, //       ''     ,    ''       , "FLEUR" for fleur (flower): ❦
    [CS_HEART] = 0x2665, //       ''     ,    ''       ' "HEART" for heart: ♥

    [CS_LHORI] = 0x2500, //       ''     ,    ''       ' "L" for light, "HORI" for horizontal: ─
    [CS_HHORI] = 0x2501, //       ''     ,    ''       ' "H" for heavy,         ''           : ━
    [CS_LHORID] = 0x2504,//       ''     ,    ''       ' "L" for light,         ''           , "D" for dash: ┄
    [CS_HHORID] = 0x2505,//       ''     ,    ''       ' "H" for heavy,         ''           , "D" for dash: ┅
};


// Macros, allowing the upper left button to switch to either _LTR base layer, or the _DDL descramble base layer.
// Same on _FUN layer key toggles. That way the whole board works the same, with the use of descramble or not.
// Descramble is set on/half/off in the _FUN layer. The word "base" is used to avoid "default," because the default
// layer system call DF()is not being used.
enum custom_keycodes {
    CTO_BASE = SAFE_RANGE, // 'C' for costum, "TO" for to, "BASE" for chosen base layer
    // BASE_NORMAL and BASE_DD_HALF are discontinued, but if you like one key to go to a mode 
    // .. you can re-instate the code.
    //BASE_NORMAL,                   // "BASE" for base layer, "_LTR" for that layer
    BASE_DESCRMBL, // New: cycles    //         ''             "_DDL" for that layer 
    //BASE_DD_HAlF,                  //         ''             "_DDL" for that layer
    CTO_NUMS, // activates number-symbols layer
    CTO_FUNC,
    CTO_MOVE,
    CTO_RARE,
    CTO_REVE,
    CTO_ACCE,
    CTO_DRAW,
    CHOLTAP_ACCE,
    CHOLTAP_RSHFT,
    CHOLTAP_LSHFT,
    CHOLTAP_DRAW,
    _FUN_STAY,
    C_KC_PWR, 
    C_KC_WAKE,
    C_KC_SLEP,
    C_KC_PAUS,
    LEDS_ON,
    //
    // For descramble BASE layer set. These need to be 'costum' keycodes, which seems to prevent
    // the assigned key to end up doing other stuff besides what we have defined in this file.
    // The below are the same as above for the normal maps, but there is not upper/lower case
    // because that is handled by noting the state of Shift. These are merely keycodes that refer
    // to their macro, which then refers to the above Unicode map version and then recode that.
    // UN_OE_BI refers to the values in COEL_BI and COEU_BI, recodes them and gives as output, etc.
    // (These lists are sorted.)
    UN_A_ACU,
    UN_A_CAR,
    UN_A_DIA,
    UN_AE_BI,
    UN_A_GRA,
    UN_A_RNG,
    UN_C_CDL,
    UN_E_ACU,
    UN_E_CAR,
    UN_E_DIA,
    UN_E_GRA,
    //UN_EX_INV,
    UN_I_ACU,
    UN_I_CAR,
    UN_I_DIA,
    UN_I_GRA,
    UN_N_TLD,
    UN_O_ACU,
    UN_O_CAR,
    UN_O_DIA,
    UN_OE_BI,
    UN_IJ_BI,
    UN_O_GRA,
    UN_O_STK,
    UN_QU_INV,
    UN_S_SHP,
    UN_S_SMIL,
    UN_S_THUP,
    UN_U_ACU,
    UN_U_CAR,
    UN_U_DIA,
    UN_U_GRA,
    UN_Y_ACU,
    UN_Y_DIA,
    UN_S_OCBRA,
    UN_S_CCBRA,
    UN_S_ODABRA,
    UN_S_CDABRA,
    UN_N_0SUBP,
    UN_N_1SUBP,
    UN_N_2SUBP,
    UN_N_3SUBP,
    UN_N_4SUBP,
    UN_N_5SUBP,
    UN_N_6SUBP,
    UN_N_7SUBP,
    UN_N_8SUBP,
    UN_N_9SUBP,
    UN_S_PLUSMIN,
    UN_S_PLMI,
    UN_S_DQUL,
    UN_S_DQUH,
    UN_S_CIRCLE,
    UN_S_MIDDOT,
    UN_S_BULLET,
    UN_S_ELLIPS,
    UN_S_DEGREE,
    UN_S_OPSUBP,
    UN_S_CPSUBP,   
    UN_S_LARROW,
    UN_S_RARROW,
    UN_S_FLEUR,
    UN_S_CURREN,
    UN_S_NONE,
};

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

// pre-existing function
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

// Descramble Unicode functions, for layouts _DDA, _DDD
// This function sends the leader codes that are common to most/all accented characters,
// in an effort to reduce memory use, and/or to simplify the code. The "f" becomes "u"
// when the computer side remaps the input to Dvorak (which problem is what 'descramble' deals with).
void unicode_lead_00 ( void ) { 
    SEND_STRING ( SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) "f" SS_UP(X_LSHIFT) SS_UP(X_LCTRL) "00" ) ; // lead-in for Unicode on Linux
}
// Same as above, but without first two zeroes 
void unicode_lead ( void ) { 
    SEND_STRING ( SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) "f" SS_UP(X_LSHIFT) SS_UP(X_LCTRL) ) ; // lead-in for Unicode on Linux
}
// Tail end of unicode input.
void unicode_tail ( void ) { 
    SEND_STRING ( " " ) ; // Ends the Unicode numerical input mode, replacing input with desired character (Linux)
}

// Activate the given layer
void activate_this_layer (int layer) {
    layer_on (layer) ;
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

// Process the user input, as far as special costumization within this source file is concerned.
// The special layer switching keys.
// The Unicode system to work with descramble.
// pre-existing function
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Go back to base-layer after pressing an F-key, on key-up to avoid BASE key activation
    if ((_fun_stay == FALSE) && // 
        (((keycode >= KC_F1) && (keycode <= KC_F12))
         ||
        ((keycode >= KC_F13) && (keycode <= KC_F24)))) {  // assumes keycodes 1-12 and 13-24 are consequtive, which seems likely, although using 1-24 failed (probably not consequtive)
         // Go back to base layer
         if (!(record->event.pressed)) { // key up
             if (descramble) { // 
                 activate_this_layer (_DDL); 
                 deactivate_all_but (_DDL); 
             } else {
                 activate_this_layer (_LTR);
                 deactivate_all_but (_LTR); 
             }
        }
    }

    // Detect if right shift was pressed in isolation
    if (isolate_trigger) { // speed: hoping this statement to execute a little quicker overall, than the next 
        if ((keycode != CHOLTAP_RSHFT)   // not right shift up
             &&
            (keycode != CHOLTAP_LSHFT)) { // not left shift up
            isolate_trigger = FALSE;
        }
    }


    // Layer switching:
    switch (keycode) {

    // Shift detection system.
    // Following ... Disused again, because it turned out 'one shot' like
    // Unicode input. Shift detection copied from.
    // https://github.com/kyleterry/qmk_firmware/blob/master/quantum/quantum.c
    //uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));

            // Re-instated ...
           // /* Crude but self contained shift detection.
        // Record state of shift
        // ... right shift
        case KC_RSFT:
        // + ... left shift
        case KC_LSFT:
            if (record->event.pressed) { // key down
                shift_ison = 1; // shift depressed
            } else { // key up
                shift_ison = 0; // shift released
            }
          break;

        //   Setting the descramble mode
        /*  // Discrete keys for switching descramble, but discontinued for sake of physical keyspace
        case BASE_NORMAL: // User wants to switch to normal input BASE key pointing 
            if (record->event.pressed) {
                ;
            } else { // key up
                descramble = _NORMAL_; // off  
                indicate_scramble (); // Help user with indicator
            }
            break;           
        case BASE_DD_HAlF: // User wants to switch to descramble BASE key pointing, but retain normal Unicode coding
            if (record->event.pressed) {
                ;
            } else { // key up
                descramble = _HALF_;// on
                indicate_scramble (); 
            }
            break; */
        case BASE_DESCRMBL: // Switching through the descramble modes
            if (record->event.pressed) {
                ;
            } else { // key up
                // Cycles through the modes
                if (_NORMAL_ == descramble) {
                    descramble = _FULL_;// all descramble layers
                } else if (_HALF_ == descramble) {
                    descramble = _NORMAL_;// normal layers
                } else { // _FULL_ == descramble
                    descramble = _HALF_;// with normal Unicode layers
                }
                indicate_scramble ();  // activate led change 
            }
            break; 

        //     Switching to layers:
        case CTO_BASE:
        // User pressed upper/left button (escape from a layer to BASE layer)
            if (record->event.pressed) { // key down
                if (descramble) { // go to the descramble version (bit of a hack maybe, but all descramble
                       // ... modes are non-zero, and all use _DDL layer)
                    activate_this_layer (_DDL); // activates descrambled num-sys layer
                } else {
                    activate_this_layer (_LTR); // activates normal num-sys layer
                }
            } else { // key up
                if (descramble) {
                    deactivate_all_but (_DDL); // stop all other layers 
                } else {
                    deactivate_all_but (_LTR); //  "     "
                }
            }
            break;
        case CTO_NUMS: // activates number-symbols layer
                // It seems best to first enable the chosen layer on key-down, then stop others on key-up.
                // Alternatives gave some issues. Other keymaps seem to do it this way (IIRC).
            if (record->event.pressed) { // key down
                if (descramble) { // go to the descramble version
                    activate_this_layer (_DDN); // activates descrambled num-sys layer
                } else {
                    activate_this_layer (_NSY); // activates normal num-sys layer
                }
            } else { // key up
                if (descramble) {
                    deactivate_all_but (_DDN); // stop all other layers 
                } else {
                    deactivate_all_but (_NSY); //  "     "
                }
            }
            break; 
        case CTO_ACCE: // Unicode layer
            if (record->event.pressed) { // key down
                if (_FULL_ == descramble) { // go to the descramble version
                    activate_this_layer (_DDA); // activates descrambled accented layer
                } else {
                    activate_this_layer (_ACC); // activates normal accented layer
                }
            } else { // key up
                if (_FULL_ == descramble) {
                    deactivate_all_but (_DDA); // stop all other layers 
                } else {
                    deactivate_all_but (_ACC); //  "     "
                }
            }
            break; 
        case CTO_DRAW: // Unicode layer
            if (record->event.pressed) { // key down
                if (_FULL_ == descramble) { // go to the descramble version
                    activate_this_layer (_DDD); // activates descrambled drawings layer
                } else {
                    activate_this_layer (_DRA); // activates normal drawings layer
                }
            } else { // key up
                if (_FULL_ == descramble) {
                    deactivate_all_but (_DDD); // stop all other layers 
                } else {
                    deactivate_all_but (_DRA); //  "     "
                }
            }
            break; 

        //   When held the key is shift. When tapped it is computed if the tap is short enough,
        // and if no other key was pressed, in which case: shift-up and a toggle to the _FUN layer.
        // The timing is meant to be able to undo an erroneous shift press just by holding longer,
        // and the test if another key was pressed is to prevent an erroneous detection when typing
        // very fast, also because _FUN can cause havock in a program with its F-keys.
        //   The reason for this on shift is to isolate GUI, where _FUN was previously
        // located. No alternative tapping function with GUI because some systems do not treat GUI
        // purely as a modifier. Since its a tap anyway, _FUN can fit away from the thumb-hold row.
        case CHOLTAP_RSHFT: // When tapped it toggles the _FUN layer, when held it is Shift
            if (record->event.pressed) { // key down
                key_timer = timer_read ();
                SEND_STRING (SS_DOWN (X_RSFT)); 
                isolate_trigger = TRUE; // keep track of whether another key gets pressed.
            } else { // key up
                SEND_STRING (SS_UP (X_RSFT)); 
                 if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                    if (isolate_trigger) { // no other key was hit since key down 
                        activate_this_layer (_FUN); // activates function layer as a toggle
                        deactivate_all_but (_FUN);  
                    }
                 }
            }
            break;
        // The left-shift version of the above keycode.
        case CHOLTAP_LSHFT: // When tapped it toggles the _MOV layer, when held it is Shift
                            // _RAR was the first idea, but some of its keys are too dangerous regarding accidents.
            if (record->event.pressed) { // key down
                key_timer = timer_read ();
                SEND_STRING (SS_DOWN (X_LSFT)); 
                // This key is re-used, for speed and because using both shifts is useless,
                // .. thus very rare, and also not a usage problem if it occured.
                isolate_trigger = TRUE; // keep track of whether another key gets pressed.
            } else { // key up
                SEND_STRING (SS_UP (X_LSFT)); 
                 if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                    if (isolate_trigger) { // no other key was hit since key down 
#ifdef LSHIFT_LAYER_RAR
                        activate_this_layer (_RAR); // activates function layer as a toggle
                        deactivate_all_but (_RAR);  
#endif
#ifdef LSHIFT_LAYER_MOV
                        activate_this_layer (_MOV); // activates function layer as a toggle
                        deactivate_all_but (_MOV);  
#endif
#ifdef LSHIFT_LAYER_DRA
                        activate_this_layer (_DRA); // activates function layer as a toggle
                        deactivate_all_but (_DRA);  
#endif
#ifdef LSHIFT_LAYER_ACC
                        activate_this_layer (_ACC); // activates function layer as a toggle
                        deactivate_all_but (_ACC);  
#endif
#ifdef LSHIFT_LAYER_PAD
                        activate_this_layer (_PAD); // activates function layer as a toggle
                        deactivate_all_but (_PAD);  
#endif

                    }
                 }
            }
            break;

        // These two are a simulated LT(layer,kc), layer-tap. 
        // Double-tap-hold functionality: not done, but holding _NSY layer gives a normal Del there
        // They switch what layer to use depending on 'descramble'
        // Basically it starts the right layer on key down, goes back to base layer on key up,
        // and throws in a keypress if tapped.
        case CHOLTAP_ACCE: //LT ( _DDA , KC_DEL ) or to _ACC, depending ...
            if (record->event.pressed) { // key down
                 key_timer = timer_read ();
                 if (_FULL_ == descramble) {
                     activate_this_layer (_DDA); // activates descrambled drawings layer
                     deactivate_all_but (_DDA); 
                 } else {
                     activate_this_layer (_ACC); // activates normal drawings layer
                     deactivate_all_but (_ACC);
                 }
            } else { // key up
                 // Go back to base layer
                 if (descramble) { // 
                     activate_this_layer (_DDL); 
                     deactivate_all_but (_DDL); 
                 } else {
                     activate_this_layer (_LTR);
                     deactivate_all_but (_LTR); 
                 }
                 if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                     SEND_STRING (SS_TAP (X_DEL));
                 }
            }
            break;
        case CHOLTAP_DRAW: //LT ( _DDD , KC_RIGHT ), or to _DRA, depending ...
            if (record->event.pressed) { // key down
                 key_timer = timer_read ();
                 if (_FULL_ == descramble) {
                     activate_this_layer (_DDD); // activates descrambled drawings layer
                     deactivate_all_but (_DDD); 
                 } else {
                     activate_this_layer (_DRA); // activates normal drawings layer
                     deactivate_all_but (_DRA);
                 }
            } else { // key up
                 // Go back to base layer
                 if (descramble) { // 
                     activate_this_layer (_DDL); 
                     deactivate_all_but (_DDL); 
                 } else {
                     activate_this_layer (_LTR);
                     deactivate_all_but (_LTR); 
                 }
                 if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                     SEND_STRING (SS_TAP (X_RIGHT));
                 }
            }
            break;
        case _FUN_STAY: // causes the f-keys to *not* return _FUN layer to BASE
            if (record->event.pressed) { // key down
                if (_fun_stay == FALSE) { // cycles, so it becomes permament until altered
                    _fun_stay = TRUE;
                } else {
                    _fun_stay = FALSE;
                }
            }
            break;
        // These keys are so dangerous that they are behind a shift lock.
        // Although the layer is already a bit hard to reach, the media keys might be used.
        case C_KC_PWR: 
            if (record->event.pressed) { // key down
                if (shift_ison) { 
                    SEND_STRING (SS_TAP (X_PWR)); 
                }
            }
            break;
        case C_KC_WAKE:
            if (record->event.pressed) { // key down
                if (shift_ison) { 
                    SEND_STRING (SS_TAP (X_WAKE)); 
                }
            }
            break;
        case C_KC_SLEP:
            if (record->event.pressed) { // key down
                if (shift_ison) { 
                    SEND_STRING (SS_TAP (X_SLEP)); 
                }
            }
            break;
        case C_KC_PAUS:
            if (record->event.pressed) { // key down
                if (shift_ison) { 
                    SEND_STRING (SS_TAP (X_PAUS)); 
                }
            }
            break;

        case LEDS_ON: // Toggles leds on or off
            if (record->event.pressed) { // key down
                if (leds_on == FALSE) { 
                    leds_on = TRUE;
                    leds_show_off ();
                } else {
                    leds_on = FALSE;
                    leds_show_off ();
                }
            }
            break;
     
        // Unicode macros for descramble mode.
        // The plan was to use the already defined hex values, convert them to ascii and then use them (itoa(...), stdlib.h).
        // However it seems SEND_STRING cannot take a variable.
        // It seems that it has to be a hardcoded constant. 
        // The table of 'descramble' conversion of the ASCII representation of hex values is:
        // 0-9=0-9, a=a, b=n, c=i, d=h, e=d, f=y (computer side maps to Dvorak, before interpreting the value)
        
        // 'a' variants (basic)
        case UN_A_ACU:
            if (record->event.pressed) { // key down
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i1"); } else { SEND_STRING ("d1"); }  // áÁ
                unicode_tail ();
            }
          break;
        case UN_A_CAR:
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i2"); } else { SEND_STRING ("d2"); } // âÂ
                unicode_tail ();
            }
          break;
        case UN_A_DIA:
            if (record->event.pressed) {
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i4"); } else { SEND_STRING ("d4"); } // äÄ
                unicode_tail ();
            }
          break;
        case UN_A_GRA:
            if (record->event.pressed) {
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i0"); } else { SEND_STRING ("d0"); } // àÀ
                unicode_tail ();
            }
          break;
        case UN_A_RNG:
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i5"); } else { SEND_STRING ("d5"); } // åÅ
                unicode_tail ();
            }
          break;
        case UN_AE_BI: 
            if (record->event.pressed) {
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i6"); } else { SEND_STRING ("d6"); } // æÆ
                unicode_tail ();
            }
          break;
        case UN_OE_BI: 
            if (record->event.pressed) { // key down
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("0152"); } else { SEND_STRING ("0153"); } // œŒ
                unicode_tail ();
            }
          break;
        case UN_C_CDL: 
            if (record->event.pressed) {
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i7"); } else { SEND_STRING ("d7"); } // çÇ
                unicode_tail ();
            }
          break;
        case UN_E_ACU: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i9"); } else { SEND_STRING ("d9"); } // éÉ
                unicode_tail ();
            }
          break;
        case UN_E_CAR: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("ia"); } else { SEND_STRING ("da"); } // êÊ
                unicode_tail ();
            }
          break;
        case UN_E_DIA: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("in"); } else { SEND_STRING ("dn"); } // ëË
                unicode_tail ();
            }
          break;
        case UN_E_GRA: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("i8"); } else { SEND_STRING ("d8"); } // èÈ
                unicode_tail ();
            }
          break;
        case UN_I_ACU: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("ih"); } else { SEND_STRING ("dh"); } // íÍ
                unicode_tail ();
            }
          break;
        case UN_I_CAR: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("id"); } else { SEND_STRING ("dd"); } // îÎ
                unicode_tail ();
            }
          break;
        case UN_I_DIA: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("iy"); } else { SEND_STRING ("iy"); } // ÏÏ
                unicode_tail ();
            }
          break;
        case UN_I_GRA: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("ii"); } else { SEND_STRING ("di"); } // ìÌ
                unicode_tail ();
            }
          break;
        case UN_N_TLD: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("h1"); } else { SEND_STRING ("y1"); } // ñÑ
                unicode_tail ();
            }
          break;
          /*
        case UN_EX_INV: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                SEND_STRING ("a1"); // ¡
                unicode_tail ();
            }
          break;
          */
        case UN_QU_INV: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("a1"); } else { SEND_STRING ("ny"); } // 
                unicode_tail ();
            }
          break;
        case UN_O_ACU: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("h3"); } else { SEND_STRING ("y3"); } // óÓ
                unicode_tail ();
            }
          break;
        case UN_O_CAR: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("h4"); } else { SEND_STRING ("y4"); } // ôÔ
                unicode_tail ();
            }
          break;
        case UN_O_DIA: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("h6"); } else { SEND_STRING ("y6"); } // öÖ
                unicode_tail ();
            }
          break;
        case UN_O_GRA: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("h2"); } else { SEND_STRING ("y2"); } // òÒ
                unicode_tail ();
            }
          break;
        case UN_O_STK: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("h8"); } else { SEND_STRING ("y8"); } // øØ
                unicode_tail ();
            }
          break;
        case UN_S_SHP: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                SEND_STRING ("hy"); // ß
                unicode_tail ();
            }
          break;
        case UN_U_ACU: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("ha"); } else { SEND_STRING ("ya"); } // úÚ
                unicode_tail ();
            }
          break;
        case UN_U_CAR: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("hn"); } else { SEND_STRING ("yn"); } // ûÛ
                unicode_tail ();
            }
          break;
        case UN_U_DIA: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("hi"); } else { SEND_STRING ("yi"); } // üÜ
                unicode_tail ();
            }
          break;
        case UN_U_GRA: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("h9"); } else { SEND_STRING ("y9"); } // ùÙ
                unicode_tail ();
            }
          break;
        case UN_Y_ACU: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("hh"); } else { SEND_STRING ("yh"); } // ýÝ
                unicode_tail ();
            }
          break;
        case UN_Y_DIA: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("0178"); } else { SEND_STRING ("00yy"); } // ÿŸ
                unicode_tail ();
            }
          break;
        case UN_IJ_BI: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("0132"); } else { SEND_STRING ("0133"); } // ĳĲ
                unicode_tail ();
            }
          break;
        case UN_S_THUP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("1y44d"); } else { SEND_STRING ("1y44h"); } // 👎👍
                unicode_tail ();
            }
          break;
        case UN_S_SMIL: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("1y641"); } else { SEND_STRING ("1y642"); } // 🙂🙁
                unicode_tail ();
            }
          break;
        case UN_S_OCBRA: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2500"); } else { SEND_STRING ("300i"); } // 「
                unicode_tail ();
            }
          break;
        case UN_S_CCBRA: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2501"); } else { SEND_STRING ("300h"); } //  」
                unicode_tail ();
            }
          break;
        case UN_S_ODABRA: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2504"); } else { SEND_STRING ("300a"); } //  《
                unicode_tail ();
            }
          break;
        case UN_S_CDABRA: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2505"); } else { SEND_STRING ("300n"); } //  》
                unicode_tail ();
            }
          break;
        case UN_S_PLUSMIN: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("0192"); } else { SEND_STRING ("00n1"); } // ƒ±
                unicode_tail ();
            }
          break;
        case UN_S_CURREN: 
            if (record->event.pressed) { 
                unicode_lead_00 ();
                if (shift_ison) { SEND_STRING ("a3"); } else { SEND_STRING ("a4"); } // £ ¤
                unicode_tail ();
            }
          break;
        case UN_S_NONE: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("00a2"); } else { SEND_STRING ("2205"); } // ∅ ¢
                unicode_tail ();
            }
          break;

        case UN_S_DEGREE: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("3007"); } else { SEND_STRING ("00n0"); } // 〇°
                unicode_tail ();
            }
          break;
        case UN_S_BULLET: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("00a7"); } else { SEND_STRING ("2022"); } // §•
                unicode_tail ();
            }
          break;
        case UN_S_ELLIPS: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("00n7"); } else { SEND_STRING ("2026"); } // ·…
                unicode_tail ();
            }
          break;
        // 0-9=0-9, a=a, b=n, c=i, d=h, e=d, f=y 
     // super and sub script numbers
        case UN_N_0SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2080"); } else { SEND_STRING ("2070"); } // ₀⁰
                unicode_tail ();
            }
          break;

        case UN_N_1SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2081"); } else { SEND_STRING ("00n9"); } // ₁¹
                unicode_tail ();
            }
          break;
        case UN_N_2SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2082"); } else { SEND_STRING ("00n2"); } // ₂²
                unicode_tail ();
            }
          break;
        case UN_N_3SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2083"); } else { SEND_STRING ("00n3"); } // ₃³
                unicode_tail ();
            }
          break;
        case UN_N_4SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2084"); } else { SEND_STRING ("2074"); } // ₄⁴
                unicode_tail ();
            }
          break;
        case UN_N_5SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2085"); } else { SEND_STRING ("2075"); } // ₅⁵
                unicode_tail ();
            }
          break;
        case UN_N_6SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2086"); } else { SEND_STRING ("2076"); } // ₆⁶
                unicode_tail ();
            }
          break;
        case UN_N_7SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2087"); } else { SEND_STRING ("2077"); } // ₇⁷
                unicode_tail ();
            }
          break;
        case UN_N_8SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2088"); } else { SEND_STRING ("2078"); } // ₈⁸
                unicode_tail ();
            }
          break;
        case UN_N_9SUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2089"); } else { SEND_STRING ("2079"); } // ₉⁹
                unicode_tail ();
            }
          break;
        case UN_S_OPSUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("208h"); } else { SEND_STRING ("207h"); } // ₍⁽
                unicode_tail ();
            }
          break;
        case UN_S_CPSUBP: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("208d"); } else { SEND_STRING ("207d"); } // ₎⁾
                unicode_tail ();
            }
          break;
        case UN_S_DQUL: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("201i"); } else { SEND_STRING ("201d"); } // „“
                unicode_tail ();
            }
          break;
        case UN_S_DQUH: 
            if (record->event.pressed) { 
                unicode_lead ();
                SEND_STRING ("201h"); // ”
                unicode_tail ();
            }
          break;
        case UN_S_LARROW: 
            if (record->event.pressed) { 
                unicode_lead ();
                SEND_STRING (""); // 
                if (shift_ison) { SEND_STRING ("2n99"); } else { SEND_STRING ("2n98"); } // ⮙⮘ 
                unicode_tail ();
            }
          break;
        case UN_S_RARROW: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2n9n"); } else { SEND_STRING ("2n9a"); } // ⮛⮚
                unicode_tail ();
            }
          break;
        case UN_S_FLEUR: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2665"); } else { SEND_STRING ("2766"); } // ♥❦
                unicode_tail ();
            }
          break;
     }
     return true;
        // 0-9=0-9, a=a, b=n, c=i, d=h, e=d, f=y 
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 
    /* Layer _LTR: Dvorak, normal BASE layer and 'default' layer
     *
     * - Dual use keys create a delay in the key (tap/hold keys), therefore
     *   space is not dual use (most ued key), neither is hyphen.
     *
     * - If _ACC right hand or _RAR is much used, an obvious choice is to 
     *   change the layer switched to by the Delete key, or copy the more
     *   used keys to the _DRA layer, etc. Perhaps ;: could be a layer
     *   switch key as well, if not much used; or space as many do.
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
     -------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY  Enter+_MOV| Space  _NSY LGUI    Right;_DRA              // _XYZ is to layer
               hold     hold  hold      |        hold         hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number

*/
//
//      <pink2            , <pinky  , <ring   , <middl , <indx, <ind|, indx>, inde>, midd>, ring>, pink>, pink2>        ,
//      -*!-              ,         ,         ,        ,      ,    <|,>     ,      ,      ,      ,      ,               ,
        KC_ESC            , KC_QUOT , KC_COMM , KC_DOT , KC_P , KC_Y , KC_F , KC_G , KC_C , KC_R , KC_L , KC_BSPC       ,
        LCTL_T ( KC_TAB ) , KC_A    , KC_O    , KC_E   , KC_U , KC_I , KC_D , KC_H , KC_T , KC_N , KC_S , KC_MINS       ,
        CHOLTAP_LSHFT     , KC_SCLN , KC_Q    , KC_J   , KC_K , KC_X , KC_B , KC_M , KC_W , KC_V , KC_Z , CHOLTAP_RSHFT ,
//      -----------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , CHOLTAP_ACCE , MO ( _NSY ) , LT ( _MOV , KC_ENT ) , KC_SPC , MO ( _NSY ) , KC__YGUI , CHOLTAP_DRAW
//                         ,              ,             ,                    <|,>       ,             ,          ,
//      <1                 , <2           , <3          , <4                  |, 4>     , 3>          , 2>       , 1>
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
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2> 
     -o-                                    <|>                                   ...  //(to) BASE access
     Esc       qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP         Bksp
     Tab+LCtl  aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:           '"
     LSft+_MOV zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSft+_FUN   // _FUN _MOV tap
     -------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY  Enter+_MOV| Space  _NSY LGUI    Right;_DRA              // _XYZ is to layer
               hold     hold  hold      |        hold         hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number


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
        LALT_T ( KC_LEFT ) , CHOLTAP_ACCE , MO ( _DDN ) , LT ( _MOV , KC_ENT ) , KC_SPC , MO ( _DDN ) , KC__YGUI , CHOLTAP_DRAW
//                         ,              ,             ,                    <|,>       ,             ,          ,
//      <1                 , <2           , <3          , <4                  |, 4>     , 3>          , 2>       , 1>
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
        LALT_T ( KC_LEFT ) , KC_DEL , _______ , KC_ENT , KC_DOT , _______ , KC__YGUI , RALT_T ( KC_RGHT )
//                         ,        , -*-     ,      <|,>       , -*-     ,          ,
//      <1                 , <2     , <3      , <4    |, 4>     , 3>      , 2>       , 1>
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
        LALT_T ( KC_LEFT ) , KC_DEL , _______ , KC_ENT , KC_DOT , _______ , KC__YGUI , RALT_T ( KC_RGHT )
//                         ,        , -*-     ,      <|,>       , -*-     ,          ,
//      <1                 , <2     , <3      , <4    |, 4>     , 3>      , 2>       , 1>
                      ),

        /**/


    /* Layer _MOV: Movement layer: mouse and hands on navigation
     *          Also delete/backspace, to navigate and delete together.
     */

    [ _MOV ] = LAYOUT (

/*
     Layer _MOV (MOVement, mouse movement on left hand)
    
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
    #define                 MOUS_32 KC_BTN5
    #define                                 MOUS_33 KC_BTN4
    #define                                                 MOUS_34 KC_BTN3
    #define                                                                MOUS_35 KC_BTN2
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
     Ü     uLNX   uBSD  uOSX   uWIN   uWNC  | xxx   xxx   xxx   xxx   Insert xxx      // Ü(nicode) tester
     ------------------------------------------------------
     MLed  SLeds RGUI  xxx  | RSft(•) xxx   xxx   LGUI  App                      // Middle-led, Side-leds: on/off
                           <|>
     <1    <2    <3    <4   | 4>      3>    2>    1>  
 */
//
//
//      <pink2        , <pinky           , <ring            , <middl           , <index           , <indx2           |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                    ,                  ,                  ,                  , -*-              ,                 <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE      , XXXXXXX          , XXXXXXX          , XXXXXXX          , XXXXXXX          , XXXXXXX           , XXXXXXX , KC_MPLY , KC_MNXT , KC_MPRV , KC_MSTP , KC_NLCK ,
        S ( KC_P )    , C_KC_PWR         , C_KC_WAKE        , C_KC_SLEP        , C_KC_PAUS        , KC_SLCK           , KC_PSCR , XXXXXXX , KC_VOLU , KC_VOLD , KC_MUTE , KC_CAPS ,
        X ( CUU_DIA ) , UNICODE_MODE_LNX , UNICODE_MODE_BSD , UNICODE_MODE_OSX , UNICODE_MODE_WIN , UNICODE_MODE_WINC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_INS  , XXXXXXX ,
//      ------------------------------------------------------------------------------
        RGB_TOG , LEDS_ON , KC__XGUI , XXXXXXX , KC_RSFT , XXXXXXX , KC__YGUI , KC_APP
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
     LSft 「─    」━   °〇   •§    …·    | ⮘⮙    ⮚⮛    ¿¡    《┄    》┅   RSft
     ---------------------------------------------
     LAlt xxx   RGUI  Ent  | Spc   xxx   LGUI  ___
                          <|>                  -*-                                       //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  
 */
//
//      <pink2   , <pinky                     , <ring                      , <middl                       , <index                     , <indx2                      |, indx2>                       , index>                       , middl>                   , ring>                        , pinky>                       , pink2>  ,
//               ,                            ,                            ,                              ,                            ,                            <|,>                             , -*-                          ,                          ,                              ,                              ,         ,
        CTO_BASE , XP ( CS_DQUL , CS_DQUHR )  , X ( CS_DQUH )              , XP ( CS_CURREN , CS_POUND )  , XP ( CS_NONE , CS_CENT )   , XP ( CS_PLMI , CS_LGULDEN )  , XP ( CS_FLEUR , CS_HEART )   , XP ( CS_SMIL , CS_SAD_ )     , XP ( CS_THUP , CS_THDN ) , XP ( CS_OPSUP , CS_OPSUB )   , XP ( CS_CPSUP , CS_CPSUB )   , KC_BSPC ,
        KC_LCTL  , XP ( CN_1SUP , CN_1SUB )   , XP ( CN_2SUP , CN_2SUB )   , XP ( CN_3SUP , CN_3SUB )     , XP ( CN_4SUP , CN_4SUB )   , XP ( CN_5SUP , CN_5SUB )     , XP ( CN_6SUP , CN_6SUB )     , XP ( CN_7SUP , CN_7SUB )     , XP ( CN_8SUP , CN_8SUB ) , XP ( CN_9SUP , CN_9SUB )     , XP ( CN_0SUP , CN_0SUB )     , KC_RCTL ,
        KC_LSFT  , XP ( CS_OCBRA , CS_LHORI ) , XP ( CS_CCBRA , CS_HHORI ) , XP ( CS_DEGREE , CS_CIRCLE ) , XP ( CS_BULLET , CS_PARA ) , XP ( CS_ELLIPS , CS_MIDDOT ) , XP ( CS_LARROW , CS_UARROW ) , XP ( CS_RARROW , CS_DARROW ) , XP ( CQU_INV , CEX_INV ) , XP ( CS_ODABRA , CS_LHORID ) , XP ( CS_CDABRA , CS_HHORID ) , KC_RSFT ,
//      -----------------------------------------------------------------------------
        KC_LALT , XXXXXXX , KC__XGUI , KC_ENT , KC_SPC , XXXXXXX , KC__YGUI , _______
//              ,         ,          ,      <|,>       ,         ,          ,
//      <1      , <2      , <3       , <4    |, 4>     , 3>      , 2>       , 1>
                      ),


        /**/


    /* Layer _DDD: Drawings, like various Unicode symbols, and whatever else.
     *          The emoticons follow the "logic" of the movement layer.
     *          The symbols ¡ and ¿ are placed on top of ! and ?.
     *   
     */

    [ _DDD ] = LAYOUT (

/*
     Layer _DRA (DRAwings, whatever else (rendering width varies in different applications))
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                   //(toggle) on _FUN
     BASE  „“    ”     ¤£    ∅ ¢   ±ƒ    | ❦♥   🙂😃  👍👎   ⁽₍    ⁾₎    Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「─    」━   °〇   •§    …·    | ⮘⮙    ⮚⮛    ¿¡    《┄    》┅   RSft
     ---------------------------------------------
     LAlt xxx   RGUI  Ent  | Spc   xxx   LGUI  ___  
                          <|>                  -*-                                       //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  
 */
//
//      <pink2      , <pinky     , <ring       , <middl      , <index      , <indx2      |, indx2>      , index>      , middl>     , ring>       , pinky>      , pink2>  ,
//                  ,            ,             ,             ,             ,            <|,>            , -*-         ,            ,             ,             ,         ,
        CTO_BASE    , UN_S_DQUL  , UN_S_DQUH   , UN_S_CURREN , UN_S_NONE   , UN_S_PLUSMIN , UN_S_FLEUR  , UN_S_SMIL   , UN_S_THUP  , UN_S_OPSUBP , UN_S_CPSUBP , KC_BSPC ,
        KC_LCTL     , UN_N_1SUBP , UN_N_2SUBP  , UN_N_3SUBP  , UN_N_4SUBP  , UN_N_5SUBP   , UN_N_6SUBP  , UN_N_7SUBP  , UN_N_8SUBP , UN_N_9SUBP  , UN_N_0SUBP  , KC_RCTL ,
        KC_LSFT     , UN_S_OCBRA , UN_S_CCBRA  , UN_S_DEGREE , UN_S_BULLET , UN_S_ELLIPS  , UN_S_LARROW , UN_S_RARROW , UN_QU_INV  , UN_S_ODABRA , UN_S_CDABRA , KC_RSFT ,
//      -------------------------------------------------------------------------------
        KC_LALT , XXXXXXX , KC__XGUI , KC_ENT  , KC_SPC  , XXXXXXX , KC__YGUI , _______
//              ,         ,          ,       <|,>        ,         ,          ,
//      <1      , <2      , <3       , <4     |, 4>      , 3>      , 2>       , 1>
                      ),  
                          
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
 * layer switch keys on the base layers. (The firmware is already large.)
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

