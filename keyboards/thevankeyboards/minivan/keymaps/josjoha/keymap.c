
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
 * keymap, led code original copied from ../jetpacktuxedo, some
 * copy/paste from QMK documentation code examples (etc).
 * Remainder: (C) 2019 by J.B. <joshb@xs4all.nl>
 *
 */

/* Todo:
 *
 *  - Add a third mode, middle led white, for combining _ACC and _DRA with _DDL, 
 *    because the Unicode input modes on the other platforms might be the same
 *    whether Dvorak is set or not. Another option is to ignore _DDA and _DDD
 *    when the Unicode input mode is not Linux (harder to do).
 *  ... need to make costum LT switch for _DDL layer. 
 */

#include QMK_KEYBOARD_H

// Layer switch TT(layer) tapping amount to make it toggle
//#define TAPPING_TOGGLE 2

#define PRESCRAMBLED_U "f"  // This is the letter 'u' for Unicode input, as effective on a computer set to Dvorak

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
#define _REV 6  // Reversing: numbers right, navigation left (mirrored.)
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
    CS_LGULDEN,
    CS_UGULDEN,
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

     // Dutch currency
    [CS_LGULDEN] = 0x0192, //     ''              ''          "L" for lower, "GULDEN" for guilder: ƒ
    [CS_UGULDEN] = 0x0191, //     ''              ''          "U" for upper,           ''        : Ƒ
    
     // circle and dots
    [CS_CIRCLE] = 0x3007, //      ''              ''          "CIRCLE" for circle: 〇
    [CS_DEGREE] = 0x00B0, //      ''              ''          "DEGREE" for degree: °
    [CS_MIDDOT] = 0x00B7, //      ''              ''          "MIDDOT" for mid dot: ·
    [CS_BULLET] = 0x2022, //      ''              ''          "BULLET" for bullet: •

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
    CTMP_ACCE,
    CTMP_DRAW,
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
    //UN_S_SAD_, // access by shifted UN_S_SQIG
    UN_S_SMIL,
    UN_S_SQIG,
    UN_S_THDN,
    UN_S_THUP,
    //UN_S_YAYS, // access by shifted UN_S_SMIL
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
    UN_S_GULDEN,
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
    UN_S_PlUSMIN,
    UN_S_PLMI,
    UN_S_DQUL,
    UN_S_DQUH,
    UN_S_CIRCLE,
    UN_S_MIDDOT,
    UN_S_BULLET,
    UN_S_DEGREE,
    UN_S_OPSUBP,
    UN_S_CPSUBP,   
    UN_S_LARROW,
    UN_S_RARROW,
    UN_S_FLEUR,
};

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
   if (_REV != layer) { layer_off ( _REV ) ; } 
   if (_ACC != layer) { layer_off ( _ACC ) ; } 
   if (_DRA != layer) { layer_off ( _DRA ) ; } 
   if (_DDD != layer) { layer_off ( _DDD ) ; } 
   if (_DDA != layer) { layer_off ( _DDA ) ; } 
   if (_DDN != layer) { layer_off ( _DDN ) ; } 
   if (_DDL != layer) { layer_off ( _DDL ) ; } 
}

// help user with leds
void indicate_scramble (void)
{
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
}

// Process the user input, as far as special costumization within this source file is concerned.
// The special layer switching keys.
// The Unicode system to work with descramble.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Layer switching:
    switch (keycode) {
	//   Setting the descramble mode
	/*  // Discontinued for keyspace
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
    }
    // Shift detection system.
    // Following ... Disused again, because it turned out 'one shot' like
    // Unicode input. Shift detection copied from.
    // https://github.com/kyleterry/qmk_firmware/blob/master/quantum/quantum.c
    //uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));

    switch (keycode) {
	    // Re-instated ...
	   // /* Crude but self contained shift detection.
        // Record state of shift
        // ... left shift
        case KC_LSFT:
        // ... right shift
        case KC_RSFT:
            if (record->event.pressed) { // key down
                shift_ison = 1; // shift depressed
            } else { // key up
                shift_ison = 0; // shift released
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
    	        SEND_STRING ("1y44h"); // 👍
		unicode_tail ();
            }
	  break;
        case UN_S_SMIL: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        if (shift_ison) { SEND_STRING ("1y603"); } else { SEND_STRING ("1y642"); } // 🙂😃
		unicode_tail ();
            }
	  break;
        case UN_S_SQIG: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        if (shift_ison) { SEND_STRING ("1y641"); } else { SEND_STRING ("2368"); } // ⍨🙁
		unicode_tail ();
            }
	  break;
        case UN_S_THDN: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        SEND_STRING ("1y44d"); // 👎
		unicode_tail ();
            }
	  break;
        case UN_S_OCBRA: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        SEND_STRING ("300i"); // 「
		unicode_tail ();
            }
	  break;
        case UN_S_CCBRA: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        SEND_STRING ("300h"); // 」
		unicode_tail ();
            }
	  break;
        case UN_S_ODABRA: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        SEND_STRING ("300a"); // 《
		unicode_tail ();
            }
	  break;
        case UN_S_CDABRA: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        SEND_STRING ("300n"); // 》
		unicode_tail ();
            }
	  break;
        case UN_S_GULDEN: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        if (shift_ison) { SEND_STRING ("0191"); } else { SEND_STRING ("0192"); } // ƒƑ
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
        case UN_S_PlUSMIN: 
            if (record->event.pressed) { 
		unicode_lead ();
    	        if (shift_ison) { SEND_STRING ("00n7"); } else { SEND_STRING ("00n1"); } // ·±
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
// Left+LAlt Del+_ACC _NSY  Enter+_MOV| Space _NSY _FUN    Right+_DRA             // _XYZ are layer switches
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
        LALT_T ( KC_LEFT ) , LT ( _ACC , KC_DEL ) , MO ( _NSY ) , LT ( _MOV , KC_ENT ) , KC_SPC , MO ( _NSY ) , TO ( _FUN ) , LT ( _DRA , KC_RIGHT )
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
// ------------------------------------------------------------------
// Left+LAlt Del+_DDA _DDN  Enter+_MOV| Space _DDN _FUN    Right+_DDD            // _XYZ are layer switches
//                                   <|>                                  
//           hold     hold  hold      |       hold toggl   hold                  // Type of layer switch
// <1        <2       <3    <4        | 4>    3>   2>      1>                    // Keys by number
//                                                   
//
//      <pink2            , <pink, <ring, <midd, <indx, <ind|, indx>, inde>, middle> , ring>  , pink>   , pink2>  ,
//      -*-               ,      ,      ,      ,      ,    <|,>     ,      ,         ,        ,         , -!-     ,
        KC_ESC            , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I    , KC_O   , KC_P    , KC_BSPC ,
        LCTL_T ( KC_TAB ) , KC_A , KC_S , KC_D , KC_F , KC_G , KC_H , KC_J , KC_K    , KC_L   , KC_SCLN , KC_QUOT ,
        KC_LSFT           , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_N , KC_M , KC_COMM , KC_DOT , KC_SLSH , KC_RSFT ,
//      ---------------------------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , LT ( _DDA , KC_DEL ) , MO ( _DDN ) , LT ( _MOV , KC_ENT ) , KC_SPC , MO ( _DDN ) , TO ( _FUN ) , LT ( _DDD , KC_RIGHT )
//                         ,                      ,             ,                    <|,>       ,             ,              ,
//      <1                 , <2                   , <3          , <4                  |, 4>     , 3>          , 2>           , 1>
                      ),
    //CTMP_ACCE,
    //CTMP_DRAW,
    //-here

        /**/

    /* Layer _NSY: Numbers and symbols.
     *          Off hand Number input (-.Bksp ent (shft)tab).
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _NSY ] = LAYOUT (

// <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
//          -*-                          <|>                                    // Layer access from _FUN -*-
// BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
// Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(    0) `~+RCtl
// -+LSft   [{    ]}    /?    \|     =+   | +     |     ?     {     }   `+RSft   // QMK limitation prevents ~
// -------------------------------------------------------
// Left+LAlt Del   ___   Ent  | .   ___   ,     Right+RAlt
//                 -*-       <|>    -*-                                         // Layer access from _LTR -*-
// <1        <2    <3    <4   | 4>  3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,         ,         ,         ,       <|,>        ,         ,         ,         ,         ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_TAB )  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_MINS ) , KC_LBRC , KC_RBRC , KC_SLSH , KC_BSLS , KC_EQL  , KC_PLUS , KC_PIPE , KC_QUES , KC_LCBR , KC_RCBR , RSFT_T ( KC_TILD ) ,  
//      -------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , _______ , KC_ENT , KC_DOT , _______ , KC_COMM  , RALT_T ( KC_RGHT )
//                         ,        , -*-     ,      <|,>       , -*-     ,          ,
//      <1                 , <2     , <3      , <4    |, 4>     , 3>      , 2>       , 1>
                      ),

        /**/


    /* Layer _DDN: Descrambled _NSY layer for a computer already set to Dvorak (see just above).
     *
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _DDN ] = LAYOUT (

// <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                       <|>                        -*-                      // on _FUN
// BASE     !     @     #     $     %     | ^     &     *     (     )     Bspc
// Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(    0) `~+RCtl
// -+LSht   -_    =+    [{    ]}    \|    | |     }     {     _     +   `+RSht                   // raw
//          [{    ]}    /?    \|    =+    | +     |     ?     {     }                         // result
// -------------------------------------------------------
// Left+LAlt Del   ___   Ent  | .   ___   ,     Right+RAlt
//                 -*-       <|>    -*-                                                      // on _DDL
// <1        <2    <3    <4   | 4>  3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring  , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,        ,         ,         ,       <|,>        ,         ,         ,         , -*-     ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT  , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC            ,
        LCTL_T ( KC_TAB )  , KC_1    , KC_2   , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_MINS ) , KC_MINS , KC_EQL , KC_LBRC , KC_BSLS , KC_RBRC , KC_RCBR , KC_PIPE , KC_LCBR , KC_UNDS , KC_PLUS , RSFT_T ( KC_TILD ) ,  
//  ----------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , _______ , KC_ENT , KC_DOT , _______ , KC_COMM , RALT_T ( KC_RGHT )
//                         ,        , -*-     ,      <|,>       , -*-     ,         ,
//      <1                 , <2     , <3      , <4    |, 4>     , 3>      , 2>      , 1>
                      ),

        /**/


    /* Layer _MOV: Movement layer: mouse and hands on navigation
     *          Also delete/backspace, to navigate and delete together.
     */

    [ _MOV ] = LAYOUT (

// <pinky2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                       -*-              <|>
// BASE      WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn  Bksp
// Tab+LCtl  MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
// LSft      Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSft
// --------------------------------------------------------
// Left+LAlt Del   Ent   ___ | PgUp  PgDn  xxx   Right+RAlt
//                       -*-<|>
// <1        <2    <3    <4  | 4>    3>    2>    1>  
//
//
//      <pink2            , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                        ,         ,         , -*-     ,         ,       <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE          , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , XXXXXXX , KC_BTN3 , KC_PGUP , KC_HOME , KC_END  , KC_PGDN , KC_BSPC ,
        LCTL_T ( KC_TAB ) , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , KC_BTN1 , KC_BTN1 , KC_LEFT , KC_UP   , KC_DOWN , KC_RGHT , KC_RCTL ,
        KC_LSFT           , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN2 , XXXXXXX , KC_BTN2 , KC_ACL0 , KC_ACL1 , KC_ACL2 , XXXXXXX , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL  , KC_ENT , _______ , KC_PGUP , KC_PGDN , XXXXXXX , RALT_T ( KC_RGHT )
//                         ,         ,        , -*-   <|,>        ,         ,         ,
//      <1                 , <2      , <3     , <4     |, 4>      , 3>      , 2>      , 1>
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

// <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
//                                  -*-  <|>
// BASE     PgDn  End   Home  PgUp  xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
// Tab+LCtl Left  Down  Up    Right xxx   | 6^    7&    8*    9(    0)    RCtl
// -+LSft   xxx   xxx   xxx   xxx   xxx   | 5%    4$    3#    2@    1!    RSft
// -----------------------------------------------------------
// Left+LAlt Del   PgDn     PgUp | .    xxx   ,     Right+RAlt
//                              <|>
// <1        <2    <3       <4   | 4>   3>    2>    1>  
//
//
//      <pink2             , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>  ,
//                         ,         ,         ,         ,         , -*-   <|,>        ,         ,         ,         ,         ,         ,
        CTO_BASE           , KC_PGDN , KC_END  , KC_HOME , KC_PGUP , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC ,
        LCTL_T ( KC_TAB )  , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , XXXXXXX , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_RCTL ,
        LSFT_T ( KC_MINS ) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_5    , KC_4    , KC_3    , KC_2    , KC_1    , KC_RSFT ,
//      -------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , KC_DEL , KC_PGDN , KC_PGUP , KC_DOT  , XXXXXXX , KC_COMM , RALT_T ( KC_RGHT )
//                         ,        ,         ,       <|,>        ,         ,         ,
//      <1                 , <2     , <3      , <4     |, 4>      , 3>      , 2>      , 1>
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
// BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bspc 
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
        CTO_BASE    , XP ( CAL_ACU , CAU_ACU ) , XP ( COL_ACU , COU_ACU ) , XP ( CEL_ACU , CEU_ACU ) , XP ( CUL_ACU , CUU_ACU ) , XP ( CIL_ACU , CIU_ACU ) , XP ( CYL_ACU , CYU_ACU ) , XP ( CIJL_BI , CIJU_BI ) , XP ( CCL_CDL , CCU_CDL ) , XP ( COL_STK , COU_STK ) , XP ( CAL_RNG , CAU_RNG ) , KC_BSPC ,
        KC_LCTL     , XP ( CAL_DIA , CAU_DIA ) , XP ( COL_DIA , COU_DIA ) , XP ( CEL_DIA , CEU_DIA ) , XP ( CUL_DIA , CUU_DIA ) , XP ( CIL_DIA , CIU_DIA ) , XP ( CYL_DIA , CYU_DIA ) , XP ( COEL_BI , COEU_BI ) , XP ( CAEL_BI , CAEU_BI ) , XP ( CNL_TLD , CNU_TLD ) , X ( CSL_SHP )            , KC_RCTL ,
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
// BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bspc
// LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
// LSft  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSft
// --------------------------------------------------
// LAlt+Left ___   LGUI  Ent  | Spc   RGUI  xxx   ___
//           -*-             <|>                  -*-
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2   , <pinky   , <ring    , <middl   , <index   , <indx2  |, indx2>   , index>   , middl>   , ring>    , pinky>   , pink2>  ,
//               ,          ,          ,          ,          ,        <|,>-*-      ,          ,          ,          ,          ,         ,
        CTO_BASE , UN_A_ACU , UN_O_ACU , UN_E_ACU , UN_U_ACU , UN_I_ACU , UN_Y_ACU , UN_IJ_BI , UN_C_CDL , UN_O_STK , UN_A_RNG , KC_BSPC ,
        KC_LCTL  , UN_A_DIA , UN_O_DIA , UN_E_DIA , UN_U_DIA , UN_I_DIA , UN_Y_DIA , UN_OE_BI , UN_AE_BI , UN_N_TLD , UN_S_SHP , KC_RCTL ,
        KC_LSFT  , UN_A_GRA , UN_O_GRA , UN_E_GRA , UN_U_GRA , UN_I_GRA , UN_I_CAR , UN_U_CAR , UN_E_CAR , UN_O_CAR , UN_A_CAR , KC_RSFT ,
//      ---------------------------------------------------------------------------
        KC_LALT , _______ , KC_LGUI , KC_ENT , KC_SPC , KC_RGUI , XXXXXXX , _______ 
//              , -*-     ,         ,      <|,>       ,         ,         , -*-
//      <1      , <2      , <3      , <4    |, 4>     , 3>      , 2>      , 1>
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
// BASE  „“    ⁽₍    ⁾₎    ”     ❦♥    | ƒƑ    🙂😃  👍     👎    ⍨🙁   Bspc
// LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
// LSft 「     」    °〇   •§    ±·    | ⮘⮙    ⮚⮛    ¿¡    《     》    RSft
// ---------------------------------------------------------
// LAlt+Left xxx   xxx   Ent  | Spc   xxx   xxx   Right+RAlt
//                           <|>
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2   , <pinky                      , <ring                      , <middl                       , <index                     , <indx2                    |, indx2>                         , index>                       , middl>                   , ring>                    , pinky>                   , pink2>  ,
//               ,                             ,                            ,                              ,                            ,                          <|,>                               , -*-                          ,                          ,                          ,                          ,         ,
        CTO_BASE , XP ( CS_DQUL   , CS_DQUHR ) , XP ( CS_OPSUP , CS_OPSUB ) , XP ( CS_CPSUP , CS_CPSUB )   , X ( CS_DQUH )              , XP ( CS_FLEUR , CS_HEART ) , XP ( CS_LGULDEN , CS_UGULDEN ) , XP ( CS_SMIL , CS_YAYS )     , X ( CS_THUP )            , X ( CS_THDN )            , XP ( CS_SQIG , CS_SAD_ ) , KC_BSPC ,
        KC_LCTL  , XP ( CN_1SUP   , CN_1SUB )  , XP ( CN_2SUP , CN_2SUB )   , XP ( CN_3SUP , CN_3SUB )     , XP ( CN_4SUP , CN_4SUB )   , XP ( CN_5SUP , CN_5SUB )   , XP ( CN_6SUP , CN_6SUB )       , XP ( CN_7SUP , CN_7SUB )     , XP ( CN_8SUP , CN_8SUB ) , XP ( CN_9SUP , CN_9SUB ) , XP ( CN_0SUP , CN_0SUB ) , KC_RCTL ,
        KC_LSFT  , X ( CS_OCBRA )              , X ( CS_CCBRA )             , XP ( CS_DEGREE , CS_CIRCLE ) , XP ( CS_BULLET , CS_PARA ) , XP ( CS_PLMI , CS_MIDDOT ) , XP ( CS_LARROW , CS_UARROW )   , XP ( CS_RARROW , CS_DARROW ) , XP ( CQU_INV , CEX_INV ) , X ( CS_ODABRA )          , X ( CS_CDABRA )          , KC_RSFT ,
//      --------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) , XXXXXXX , XXXXXXX , KC_ENT , KC_SPC , XXXXXXX , XXXXXXX , RALT_T ( KC_RGHT )
//                         ,         ,         ,      <|,>       ,         ,         ,
//      <1                 , <2      , <3      , <4    |, 4>     , 3>      , 2>      , 1>
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
// BASE  „“    ⁽₍    ⁾₎    ”     ❦♥    | ƒƑ    🙂😃  👍     👎    ⍨🙁   Bspc
// LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
// LSft 「     」    °〇   •§    ±·    | ⮘⮙    ⮚⮛    ¿¡    《     》    RSft
// ---------------------------------------------------------
// LAlt+Left xxx   xxx   Ent  | Spc   xxx   xxx   Right+RAlt
//                           <|>
// <1        <2    <3    <4   | 4>    3>    2>    1>  
//
//
//      <pink2      , <pinky     , <ring       , <middl      , <index      , <indx2      |, indx2>      , index>      , middl>     , ring>       , pinky>      , pink2>  ,
//                  ,            ,             ,             ,             ,            <|,>            , -*-         ,            ,             ,             ,         ,
        CTO_BASE    , UN_S_DQUL  , UN_S_OPSUBP , UN_S_CPSUBP , UN_S_DQUH   , UN_S_FLEUR   , UN_S_GULDEN , UN_S_SMIL   , UN_S_THUP  , UN_S_THDN   , UN_S_SQIG   , KC_BSPC ,
        KC_LCTL     , UN_N_1SUBP , UN_N_2SUBP  , UN_N_3SUBP  , UN_N_4SUBP  , UN_N_5SUBP   , UN_N_6SUBP  , UN_N_7SUBP  , UN_N_8SUBP , UN_N_9SUBP  , UN_N_0SUBP  , KC_RCTL ,
        KC_LSFT     , UN_S_OCBRA , UN_S_CCBRA  , UN_S_DEGREE , UN_S_BULLET , UN_S_PlUSMIN , UN_S_LARROW , UN_S_RARROW , UN_QU_INV  , UN_S_ODABRA , UN_S_CDABRA , KC_RSFT ,

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

// Layer _FUN (F-keys, Layer access, Set BASE key direction)
//
// <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
// toggl toggl toggl toggl toggl toggl | toggl toggl                   cycles   // Type of layer switch
//             -*-                    <|>                                         // Access -*- _FUN
// BASE: NUMS: _FUN  _MOV  _RAR  _REV  | ACCE: DRAW: xxx   xxx   xxx   !Descr     //':' are dynamic ...
// LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10     RCtl     // ... ! 'descramble'
// LSft  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20     RSft
// ----------------------------------------------------------
// LAlt  LCtl&   LCtl&   LSft& | +LCtl&LSft xxx   BASE   RAlt               // ! sets 'descramble' mode
//       LSft    LAlt    LAlt  | &LAlt                                     
//       +xxx    +xxx    +xxx  | +xxx                                                    // When tapped
//                            <|>                 -*-                                 // Acces -*- base
// <1    <2      <3      <4    | 4>         3>    2>     1>                
//
//
//      <pink2   , <pinky   , <ring       , <middl      , <index      , <indx2     |, indx2>   , index>   , middl>  , ring>   , pinky>  , pink2>        ,
//               ,          , -*-         ,             ,             ,           <|,>         ,          ,         ,         ,         ,               ,
        CTO_BASE , CTO_NUMS , TO ( _FUN ) , TO ( _MOV ) , TO ( _RAR ) , TO ( _REV ) , CTO_ACCE , CTO_DRAW , XXXXXXX , XXXXXXX , XXXXXXX , BASE_DESCRMBL ,
        KC_LCTL  , KC_F1    , KC_F2       , KC_F3       , KC_F4       , KC_F5       , KC_F6    , KC_F7    , KC_F8   , KC_F9   , KC_F10  , KC_RCTL       ,
        KC_LSFT  , KC_F11   , KC_F12      , KC_F13      , KC_F14      , KC_F15      , KC_F16   , KC_F17   , KC_F18  , KC_F19  , KC_F20  , KC_RSFT       ,
//      ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT , MT ( MOD_LCTL | MOD_LSFT, XXXXXXX ) , MT ( MOD_LCTL | MOD_LALT , XXXXXXX ) , MT ( MOD_LSFT | MOD_LALT , XXXXXXX ) , MT ( MOD_LCTL | MOD_LSFT | MOD_LALT , XXXXXXX ) , XXXXXXX , CTO_BASE , KC_RALT
//              ,                                     ,                                      ,                                    <|,>                                                ,               , -*-      ,
//      <1      , <2                                  , <3                                   , <4                                  |, 4>                                              , 3>            , 2>       , 1>
                      ),

        /**/



/*
 * New layer template. Includes left/right movement arrows, deletion, modifiers.
 * If you want a new layer, in the logic of this layout you would add a toggle on the
 * _FUN layer top row on the first free key to it, and optionally alter the hold 
 * layer switch keys on the base layers.
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

uint32_t layer_state_set_user(uint32_t state){
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;
    short color_ddl = 28 ;


    // The order should be the reverse of the #defines of layer number of the layers on top
    // because higher layer number is higher priority if activated
    /* _LTR 0 _DDL 1 _NSY 2 _DDN 3 _MOV 4 _RAR 5 _REV 6 _ACC 7 _DDA 8 _DRA 9 _DDD 10 _FUN 11 */
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
    if (layer_state_cmp (state, _DRA)) { // Unicode drawings and unusual things
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
    else if (layer_state_cmp (state, _REV)) { // reverse hands layer
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


