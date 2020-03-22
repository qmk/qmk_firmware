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

 * Author: (C) 2019 by Jos Boersema
 *
 */

/* This file contains mostly the Unicode and special macros.
   It contains the function: process_record_user(...)
 */

#include "./unicode_macros.h"

// Two easy to change spots on the Unicode keymap
// ƒ (best configured in keymap.c)
#ifndef UNICODE_CURRENCY // Prior optional definition in keymap.c
    #define UNICODE_CURRENCY 0x0192 // Hex number. The unicode hex number for position ƒ in the default keymap.
#endif
#ifndef UNICODE_CURRENCY_DESCRAMBLE // Prior optional definition in keymap.c
    #define UNICODE_CURRENCY_DESCRAMBLE "0192"
        // need to recode the hex number *letters* like so: 0-9=0-9, a=a, b=n, c=i, d=h, e=d, f=y
        // You can ignore UNICODE_CURRENCY_DESCRAMBLE if you compile with QWERTY_DVORAK set (see keymap.c)
#endif
// 🛠
#define CS_USER_DEFINED 0x1F6E0 // Hammer & wrench (place holder).
#define CS_USER_DEFINED_DESCRAMBLE "1y6d0" // String. Same, but for 'descramble'. If you change this, you
        // need to recode the hex number *letters* like so: 0-9=0-9, a=a, b=n, c=i, d=h, e=d, f=y
        // You can ignore UNICODE_CURRENCY_DESCRAMBLE if you compile with QWERTY_DVORAK set (see keymap.c)

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
    CIJL_BI,
    CIJU_BI,
    CIL_ACU,
    CIL_CAR, 
    CIL_DIA,
    CIL_GRA,
    CIU_ACU,
    CIU_CAR,
    CIU_DIA,
    CIU_GRA,
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
    CS_BULLET,
    CS_CCBRA,
    CS_CDABRA,
    CS_CENT,
    CS_CIRCLE,
    CS_CPSUB,
    CS_CPSUP,
    CS_CURREN,
    CS_DARROW,
    CS_DEGREE,
    CS_DQUH,
    CS_DQUHR,
    CS_DQUL,
    CS_ELLIPS,
    CS_FLEUR,
    CS_HEART,
    CS_HHORI,
    CS_HHORID,
    CS_LARROW,
    CS_LGULDEN,
    CS_LHORI,
    CS_LHORID,
    CSL_SHP,
    CS_MIDDOT,
    CS_NONE,
    CS_OCBRA,
    CS_ODABRA,
    CS_OPSUB,
    CS_OPSUP,
    CS_PARA,
    CS_PLMI,
    CS_POUND,
    CS_RARROW,
    CS_SAD_,
    CS_SMIL,
    CS_SQIG,
    CS_THDN,
    CS_THUP,
    CS_UARROW,
    CS_USER,
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

    [CS_USER] = CS_USER_DEFINED, // Remaining free spot; making it easy to configure on top of this fdile.

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
    [CS_LGULDEN] = UNICODE_CURRENCY, //    ''              ''          "L" for lower, "GULDEN" for guilder: ƒ
                // ^ special case for easy user configuration
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
    // English and Dutch quotations
    [CS_DQUL] = 0x201E,  //       ''     ,    ''       , "D" for double, "QU" for quote, "L" for low: „
    [CS_DQUH] = 0x201D,  //       ''     ,    ''       ,      ''       ,       ,,      , "H" for high: ”
    [CS_DQUHR] = 0x201C, //       ''     ,    ''       ,      ''       ,       ,,      , "H" for high, "R" for reverse: “
#ifndef CHECKBOXES_ON_POINT
    // pointers
    [CS_LARROW] = 0x2B98, //      ''     ,    ''       , "L" for Left, "ARROW" for arrow: ⮘
    [CS_UARROW] = 0x2B99, //      ''     ,    ''       , "U" for UP,            ''      : ⮙
    [CS_RARROW] = 0x2B9A, //      ''     ,    ''       , "R" for Right,         ''      : ⮚
    [CS_DARROW] = 0x2B9B, //      ''     ,    ''       , "D" for Down,          ''      : ⮛
#endif
#ifdef CHECKBOXES_ON_POINT
    // checkboxes
    [CS_LARROW] = 0x02610, //      ''     ,    ''       ,                                : ☐ 
    [CS_UARROW] = 0x02612, //      ''     ,    ''       ,                                : ☒ 
    [CS_RARROW] = 0x02611, //      ''     ,    ''       ,                                : ☑ 
    [CS_DARROW] = 0x1F5F9, //      ''     ,    ''       ,                                : 🗹
#endif
    // ornamental, heart
    [CS_FLEUR] = 0x2766, //       ''     ,    ''       , "FLEUR" for fleur (flower): ❦
    [CS_HEART] = 0x2665, //       ''     ,    ''       ' "HEART" for heart: ♥

    [CS_LHORI] = 0x2500, //       ''     ,    ''       ' "L" for light, "HORI" for horizontal: ─
    [CS_HHORI] = 0x2501, //       ''     ,    ''       ' "H" for heavy,         ''           : ━
    [CS_LHORID] = 0x2504,//       ''     ,    ''       ' "L" for light,         ''           , "D" for dashes: ┄
    [CS_HHORID] = 0x2505,//       ''     ,    ''       ' "H" for heavy,         ''           , "D" for dashes: ┅
};

enum custom_keycodes {
// Macros, allowing the upper left button to switch to either _LTR base layer, or the _DDL descramble base layer.
// Allowing the upper left button to switch to either _LTR base layer, or the _DDL descramble base layer.
// Same on _FUN layer key toggles. That way the whole board works the same, with the use of descramble or not.
// Descramble is set on/half/off in the _FUN layer. The word "base" is used to avoid "default," because the default
// layer system call DF()is not being used.
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
    CHOLTAP_LAYR,
// Special macro to make F-keys one-shot or not.
    _FUN_STAY,
// Layer toggle to be guaranteed on up-key.
    _MOV_UP,
// These macros protect the critical keys like 'Power' from accidental press.
    C_KC_PWR, 
    C_KC_WAKE,
    C_KC_SLEP,
    C_KC_PAUS,
// Toggles leds on/off. Note that RGB_TOG is a build-in keycode, to toggle the other led.
    LEDS_ON,
// These keys can be pressed together for a separate layer (like 'adjust layer' on the Planck).
    DUO_HOLD,

#ifndef QWERTY_DVORAK 
       // .... v .... v .... v .... v .... v .... v .... v .... v .... v .... v 
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
    UN_IJ_BI,
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
    UN_N_TLD,
    UN_O_ACU,
    UN_O_CAR,
    UN_O_DIA,
    UN_OE_BI,
    UN_O_GRA,
    UN_O_STK,
    UN_QU_INV,
    UN_S_BULLET,
    UN_S_CCBRA,
    UN_S_CDABRA,
    UN_S_CIRCLE,
    UN_S_CPSUBP,   
    UN_S_CURREN,
    UN_S_DEGREE,
    UN_S_DQUH,
    UN_S_DQUL,
    UN_S_ELLIPS,
    UN_S_FLEUR,
    UN_S_LARROW,
    UN_S_MIDDOT,
    UN_S_NONE,
    UN_S_OCBRA,
    UN_S_ODABRA,
    UN_S_OPSUBP,
    UN_S_PLMI,
    UN_S_PLUSMIN,
    UN_S_RARROW,
    UN_S_SHP,
    UN_S_SMIL,
    UN_S_THUP,
    UN_U_ACU,
    UN_U_CAR,
    UN_U_DIA,
    UN_U_GRA,
    UN_Y_ACU,
    UN_Y_DIA,
#endif // QWERTY_DVORAK .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ 
};


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
                 layer_move (_DDL); 
             } else {
                 layer_move (_LTR);
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
#ifndef QWERTY_DVORAK // normal version Dvorak+Dvorak-descramble
                if (_NORMAL_ == descramble) {
                    descramble = _FULL_;// all descramble layers
                } else if (_HALF_ == descramble) {
                    descramble = _NORMAL_;// normal layers
                } else { // _FULL_ == descramble
                    descramble = _HALF_;// with normal Unicode layers
                }
#endif
#ifdef QWERTY_DVORAK // The 'full descramble' is used for plain Dvorak here, which has better led colors.
                     // The #defines cause the _FULL_ descramble to point to the normal Unicode layers.
                if (_NORMAL_ == descramble) {
                    descramble = _FULL_;// all descramble layers
                } else {
                    descramble = _NORMAL_;// normal layers
                } 
#endif
                indicate_scramble ();  // activate led change 
            }
            break; 

        //     Switching to layers:
        case CTO_BASE:
        // User pressed upper/left button (escape from a layer to BASE layer)
            if (record->event.pressed) { // key down
                ;
            }
            else { // key up
                if (descramble) { // go to the descramble version (bit of a hack maybe, but all descramble
                       // ... modes are non-zero, and all use _DDL layer)
                    layer_move (_DDL); // activates descrambled num-sys layer
                } else {
                    layer_move (_LTR); // activates normal num-sys layer
                }
            } 
            break;
        case CTO_NUMS: // activates number-symbols layer
                // It seems best to first enable the chosen layer on key-down, then stop others on key-up.
                // Alternatives gave some issues. Other keymaps seem to do it this way (IIRC).
            if (record->event.pressed) { // key down
                ;
            }
            else { // key up
                if (descramble) { // go to the descramble version
                    layer_move (_DDN); // activates descrambled num-sys layer
                } else {
                    layer_move (_NSY); // activates normal num-sys layer
                }
            } 
                      // These '_NSY and _DDN' layers do not have the below
                      // #ifdef QWERTY_DVORAK system, because they are not Unicode,
                      // and those layers are switched by their re-definition in ./qwerty_dvorak.c
                      // The alternate layer is in use with QWERTY_DVORAK set.
            break; 
        case CTO_ACCE: // Unicode layer
            if (record->event.pressed) { // key down
                ;
            }
            else { // key up
#ifndef QWERTY_DVORAK // normal mode keyboard: Dvorak with Dvorak-descramble
                if (_FULL_ == descramble) { // go to the descramble version
                    layer_move (_DDA); // activates descrambled accented layer
                } else {
                    layer_move (_ACC); // activates normal accented layer
                }
#endif
#ifdef QWERTY_DVORAK // alternative layout: Qwerty with Dvorak on 'descramble'
                     // The 'full descramble' becomes Dvorak standard, hence normal _ACC layer.
                layer_move (_ACC); // activates normal accented layer
#endif
            }
            break; 
        case CTO_DRAW: // Unicode layer
            if (record->event.pressed) { // key down
                ;
            }
            else { // key up
#ifndef QWERTY_DVORAK 
                if (_FULL_ == descramble) { // go to the descramble version
                    layer_move (_DDD); // activates descrambled drawings layer
                } else {
                    layer_move (_DRA); // activates normal drawings layer
                }
#endif
#ifdef QWERTY_DVORAK 
                layer_move (_DRA); // activates normal drawings layer
#endif
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
#ifndef QWERTY_DVORAK // normal mode keyboard: Dvorak with Dvorak-descramble
                 if (_FULL_ == descramble) {
                     layer_move (_DDA); // activates descrambled drawings layer
                 } else {
                     layer_move (_ACC); // activates normal drawings layer
                 }
#endif
#ifdef QWERTY_DVORAK // alternative layout: Qwerty with Dvorak on 'descramble'
                     // The 'full descramble' becomes Dvorak standard, hence normal _ACC layer.
                 layer_move (_ACC); // activates descrambled drawings layer
#endif
            } else { // key up
                 // Go back to base layer
                 if (descramble) { // 
                     layer_move (_DDL); 
                 } else {
                     layer_move (_LTR);
                 }
                 if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                     SEND_STRING (SS_TAP (X_DEL));
                 }
            }
            break;
        case CHOLTAP_LAYR: //LT ( _DDD , KC_RIGHT ), or to _DRA, depending ...
            if (record->event.pressed) { // key down
                 key_timer = timer_read ();
                 layer_move (_RAR); // activates descrambled drawings layer
            } else { // key up
                 // Go back to base layer
                 if (descramble) { // 
                     layer_move (_DDL); 
                 } else {
                     layer_move (_LTR);
                 }
                 if (timer_elapsed (key_timer) <= TAPPING_TERM_HOLTAP) { // tapped
                     SEND_STRING (SS_TAP (X_RIGHT));
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
                        layer_move (_FUN); // activates function layer as a toggle
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
                        layer_move (_RAR); // activates function layer as a toggle
#endif
#ifdef LSHIFT_LAYER_MOV
                        layer_move (_MOV); // activates function layer as a toggle
#endif
#ifdef LSHIFT_LAYER_DRA
                        layer_move (_DRA); // activates function layer as a toggle
#endif
#ifdef LSHIFT_LAYER_ACC
                        layer_move (_ACC); // activates function layer as a toggle
#endif
#ifdef LSHIFT_LAYER_PAD
                        layer_move (_PAD); // activates function layer as a toggle
#endif

                    }
                 }
            }
            break;
        case DUO_HOLD:
            if (record->event.pressed) { // key down
                 duo_press ++; // simple way to keep track of how many are pressed
                 if (1 == duo_press) {
                     if (_NORMAL_ == descramble) { // In all 'descramble' modes to the 'descramble' layer of numbers/symbols
                         layer_move (_NSY); // activates normal numbers/symbols
                     } else {
                         layer_move (_DDN); // activates 'descramble' version
                     }
                 }
                 else if (2 == duo_press) { // both are pressed
#ifndef QWERTY_DVORAK  // The _DDD layer is not even compiled in this compile version
                     if (_FULL_ == descramble) { 
                         layer_move (_DDD); // activates Linux 'descramble' layer
                     } else {
                         layer_move (_DRA); // activates normal Unicode layer
                     }
#endif
#ifdef QWERTY_DVORAK 
                     layer_move (_DRA); // activates normal Unicode layer
#endif
                 }
            } else { // key up
                 duo_press --; 
                 if (1 == duo_press) {
                     if (_NORMAL_ == descramble) { // In all 'descramble' modes to the 'descramble' layer of numbers/symbols
                         layer_move (_NSY); // activates normal numbers/symbols
                     } else {
                         layer_move (_DDN); // activates 'descramble' version
                     }
                 }
                 else { // Has to be zero. Back to letters
                     if (descramble) { // 
                         layer_move (_DDL); 
                     } else {
                         layer_move (_LTR);
                     }
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
#ifdef MOREKEY2_ARROW_CLUSTER
        case _MOV_UP: // To be sure it activates on up key, and not trigger the _MOV layer on up-key.
            if (record->event.pressed) { // key down
            } else { // key up
               layer_move (_MOV);
            }
            break;
#endif

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
     
#ifndef QWERTY_DVORAK 
       // .... v .... v .... v .... v .... v .... v .... v .... v .... v .... v 

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
                if (shift_ison) { SEND_STRING ("iy"); } else { SEND_STRING ("dy"); } // ïÏ
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
                if (shift_ison) { SEND_STRING ("2504"); } else { SEND_STRING ("300a"); } //  《┄
                unicode_tail ();
            }
          break;
        case UN_S_CDABRA: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2505"); } else { SEND_STRING ("300n"); } //  》┅
                unicode_tail ();
            }
          break;
        case UN_S_PLUSMIN: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING (UNICODE_CURRENCY_DESCRAMBLE); } else { SEND_STRING ("00n1"); } // ƒ±
                                            // ^ special case for easy user configuration
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
                if (shift_ison) { SEND_STRING (CS_USER_DEFINED_DESCRAMBLE); } else { SEND_STRING ("201h"); } // 🛠”
                unicode_tail ();
            }
          break;
#ifndef CHECKBOXES_ON_POINT
        case UN_S_LARROW: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2n99"); } else { SEND_STRING ("2n98"); } // ⮙⮘ 
                unicode_tail ();
            }
          break;
        case UN_S_RARROW: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2n9n"); } else { SEND_STRING ("2n9a");  } // ⮛⮚
                unicode_tail ();
            }
          break;
#endif
#ifdef CHECKBOXES_ON_POINT
        case UN_S_LARROW: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("02612"); } else { SEND_STRING ("02610"); } // ☒  ☐
                unicode_tail ();
            }
          break;
        case UN_S_RARROW: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("1y5y9"); } else { SEND_STRING ("02611");  } // ☑  🗹  
                unicode_tail ();
            }
          break;
#endif
        case UN_S_FLEUR: 
            if (record->event.pressed) { 
                unicode_lead ();
                if (shift_ison) { SEND_STRING ("2665"); } else { SEND_STRING ("2766"); } // ♥❦
                unicode_tail ();
            }
          break;
#endif // QWERTY_DVORAK .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ .... ^ 
     }
     return true;
        // 0-9=0-9, a=a, b=n, c=i, d=h, e=d, f=y 
};
