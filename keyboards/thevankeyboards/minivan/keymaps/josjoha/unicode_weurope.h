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

/*        An amount of Unicode #defines
 *        - western european accented characters
 *        - various punctuation symbols, different number formats, math symbols, other symbols. 
 */

    // a lower case variants
#define CAL_ACU  0xe1 //   'C' for Costum 'A' for a, 'L' for lower, "ACU" for acute: á
#define CAL_CAR  0xe2 //        ''              ''        ''        "CAR" for caret: â
#define CAL_DIA  0xe4 //        ''              ''        ''        "DIA" for diaereses: ä
#define CAL_GRA  0xe0 //        ''              ''        ''        "GRA" for grave: à
      // A upper case variants
#define CAU_ACU  0xc1 //        ''              ''   'U' for upper, "ACU" for acute: Á
#define CAU_CAR  0xc2 //        ''              ''        ''        "CAR" for caret: Â
#define CAU_DIA  0xc4 //        ''              ''        ''        "DIA" for diaereses: Ä
#define CAU_GRA  0xc0 //        ''              ''        ''        "GRA" for grave: À

    // A with ring (Scandinavia)
#define CAL_RNG  0xe5 //        ''        'A' for a, 'L' for lower, "RNG" for Ring: å
#define CAU_RNG  0xc5 //        ''             ''    'U' for upper,        ''     : Å

    // AE (French)          
#define CAEL_BI  0xe6 //        ''        "AE" for ae, 'L' for lower        ''              : æ
#define CAEU_BI  0xc6 //        ''              ''     'U' for upper,       ''              : Æ

    // OE (French)
#define COEL_BI  0x153 //       ''        "AO" for ao, 'L' for lower, "BI" for two-character: œ
#define COEU_BI  0x152 //       ''              ''     'U' for upper,       ''              ; Œ

   // Mu (French)
#define C_MU_L   0x03BC //      ''        "MU" for Mu (Greek letter), 'L' for lower: 

    // C with cedilla
#define CCL_CDL  0xe7 //        ''        'C' for c, 'L' for lower, "CDL" for cedilla: ç 
#define CCU_CDL  0xc7 //        ''             ''    'U' for upper,        ''        : Ç

    // e lower case variants
#define CEL_ACU  0xe9 //   'C' for Costum 'E' for e, 'L' for lower, "ACU" for acute: é
#define CEL_CAR  0xea //        ''              ''        ''        "CAR" for caret: ê
#define CEL_DIA  0xeb //        ''              ''        ''        "DIA" for diaereses: ë
#define CEL_GRA  0xe8 //        ''              ''        ''        "GRA" for grave: è
      // E upper case variants
#define CEU_ACU  0xc9 //        ''              ''   'U' for uuper, "ACU" for acute: É
#define CEU_CAR  0xca //        ''              ''        ''        "CAR" for caret: Ê
#define CEU_DIA  0xcb //        ''              ''        ''        "DIA" for diaereses: Ë
#define CEU_GRA  0xc8 //        ''              ''        ''        "GRA" for grave: È
    
    // i lower case variants
#define CIL_ACU  0xed //        ''         'I' for i, 'L' for lower, "ACU" for acute: í
#define CIL_CAR  0xee //        ''              ''         ''        "CAR" for caret: î
#define CIL_DIA  0xef //        ''              ''         ''        "DIA" for diaereses: ï
#define CIL_GRA  0xec //        ''              ''         ''        "GRA" for grave: ì
      // I upper case variants
#define CIU_ACU  0xcd //        ''              ''    'U' for upper, "ACU" for acute: Í
#define CIU_CAR  0xce //        ''              ''         ''        "CAR" for caret: Î
#define CIU_DIA  0xcf //        ''              ''         ''        "DIA" for diaereses: Ï
#define CIU_GRA  0xcc //        ''              ''         ''        "GRA" for grave: Ì

    // N with tilde
#define CNL_TLD  0xf1 //        ''        'N' for n, 'L' for lower, "TLD" for tilde: ñ
#define CNU_TLD  0xd1 //        ''             ''    'U' for upper,        ''      : Ñ

    //Spanish additional symbols:
#define CEX_INV  0xa1 //        ''        "EX" for exclamation mark, "INV" for inverted: ¡
#define CQU_INV  0xbf //        ''        "QU" for question mark,           ''         : ¿
    
    // o lower case variants
#define COL_ACU  0xf3 //   'C' for Costum 'O' for a, 'L' for lower, "ACU" for acute: ó
#define COL_CAR  0xf4 //        ''              ''        ''        "CAR" for caret: ô
#define COL_DIA  0xf6 //        ''              ''        ''        "DIA" for diaereses: ö
#define COL_GRA  0xf2 //        ''              ''        ''        "GRA" for grave: ò
      // O upper case variants
#define COU_ACU  0xd3 //        ''              ''   'U' for upper, "ACU" for acute: Ó
#define COU_CAR  0xd4 //        ''              ''        ''        "CAR" for caret: Ô
#define COU_DIA  0xd6 //        ''              ''        ''        "DIA" for diaereses: Ö
#define COU_GRA  0xd2 //        ''              ''        ''        "GRA" for grave: Ò
                            
    // O with stroke (Scandinavia)
#define COL_STK  0xf8 //        ''        'O' for o, 'L' for lower, "STK" for Stroke: ø
#define COU_STK  0xd8 //        ''             ''    'U' for upper,        ''       : Ø

    // u lower case variants
#define CUL_ACU  0xfa //    'C' for Costum 'U' for u, 'L' for lower, "ACU" for acute: ú
#define CUL_CAR  0xfb //        ''              ''        ''        "CAR" for caret: û
#define CUL_DIA  0xfc //        ''              ''        ''        "DIA" for diaereses: ü
#define CUL_GRA  0xf9 //        ''              ''        ''        "GRA" for grave: ù
      // U upper case variants
#define CUU_ACU  0xda //        ''        'U' for u, 'U' for upper, "ACU" for acute: Ú
#define CUU_CAR  0xdb //        ''              ''        ''        "CAR" for caret: Û
#define CUU_DIA  0xdc //        ''              ''        ''        "DIA" for diaereses: Ü
#define CUU_GRA  0xd9 //        ''              ''        ''        "GRA" for grave: Ù

    // Y with acute
#define CYL_ACU  0xfd //        ''        'Y' for y, 'L' for lower, "ACU" for Acute: ý
#define CYU_ACU  0xdd //        ''             ''    'U' for upper,        ''      : Ý
    // Y with diaereses
#define CYL_DIA  0xff //        ''        'Y' for y, 'L' for lower, "DIA" for Diareses: ÿ
#define CYU_DIA  0x178 //       ''             ''    'U' for upper,        ''         : Ÿ

    // Dutch IJ 
#define CIJL_BI  0x133 //       ''        'IJ' for ij, 'L' for lower, BI for two-character: ĳ
#define CIJU_BI  0x132 //       ''              ''   , 'U' for upper      ''              : Ĳ

    //German:
     // sharp s 
#define CSL_SHP  0xdf //        ''         'S' for s, 'L' for lower, "SHP" for sharp: ß
  
    // Some Unicode symbols that might be handy
      // Happy symbols:
#define CS_SMIL  0x1f642 // "C" for costum, "S" for symbol , "SMIL"  for <smile> 🙂 
#define CS_SMILP 0x1F60A //     ''        ,     ''         , "SMIL" for smile, "P" for plus: 😊
#define CS_THUP  0x1f44d //     ''        ,     ''         , "THUP"  for <thumb up> 👍 
  
      //Sad symbols
#define CS_SAD_  0x1f641 //     ''        ,     ''         , "SAD_"   for  <sad face>  🙁 
#define CS_SQUIG 0x2368 //      ''        ,     ''         , "SQUIG" for squigly face: ⍨
#define CS_THDN  0x1f44e //     ''        ,     ''         , "THDN"  for <thumb down>  👎 

// Punctuation
#define CS_ASTL    0x20F0 //    ''     ,    ''       , "AST" for asterisk, "L" for little:  ⃰
#define CS_DASH    0x2014 //    ''     ,    ''       , "DASH" for dash (a longer hyphen, if rendered correctly): —
#define CS_DQUH    0x201D //    ''     ,    ''       , "D" for double, "QU" for quote, "H" for high: ”
#define CS_DQUHR   0x201C //    ''     ,    ''       ,     ''       ,       ,,       ,     ''      , "R" for reverse: “
#define CS_DQUL    0x201E //    ''     ,    ''       ,                               , "L" for low: „
#define CS_GUILLE  0xAB //      ''     ,    ''       , "GUIL" for guillemet (French quotation), "LE" for left-pointing: «
#define CS_GUILRI  0xBB //      ''     ,    ''       ,        ''                              , "RI" for right-pointing: »
#define CS_GUILSLE 0x2039 //    ''     ,    ''       ,        ''                              , "S" for simple, "LE" for left-pointing: ‹
#define CS_GUILSRI 0x203A //    ''     ,    ''       ,        ''                              ,     ''        , "RI" for right-pointing: ›
#define CS_HQUOSB  0x201B //    ''     ,    ''       , "H" for high, "QUO" for quote, "S" for single, "B" for begin: ‛
#define CS_HQUOSE  0x2019 //    ''     ,    ''       ,     ''              ''             ''        , "E" for end: ’

     // Unusual parenthesis types
#define CS_OCBRA  0x300c //     ''     ,    ''       , "O" for opening, "C" for corner, "BRA" for bracket:「
#define CS_CCBRA  0x300d //     ''     ,    ''       , "C" for closing,     ''                ''         : 」
#define CS_ODABRA 0x300a //     ''          ''       , "O" for opening, "D" for double, "A" for angled, "BRA" for bracket:《
#define CS_CDABRA 0x300b //     ''     ,    ''       , "C" for closing,     ''              ''                ''         : 》

     // currency
#define CS_LGULDEN  UNICODE_CURRENCY //    ''        , "L" for lower, "GULDEN" for gulden (guilder): ƒ
                // ^ special case for easy user configuration
#define CS_CURREN 0xA4 //       ''     ,        ''   , "CURREN" for currency, 'any currency' symbol: ¤
#define CS_POUND  0xA3 //       ''     ,        ''   , "POUND" for pound: £
#define CS_CENT   0xA2 //       ''     ,        ''   , "CENT" for cent: ¢

    // legal
#define CS_COPY   0xA9 //       ''     ,        ''   , "COPY" for copyright: 
#define CS_COPYL  0x1F12F  //   ''     ,        ''   , "COPY" for Copyright, "L" for left: 
    
     // circle, dots, bullet points
#define CS_BULLET 0x2022 //     ''     ,        ''   , "BULLET" for bullet: •
#define CS_CIRCLE 0x3007 //     ''     ,        ''   , "CIRCLE" for circle: 〇
#define CS_DEGREE 0xB0   //     ''     ,        ''   , "DEGREE" for degree: °
#define CS_ELLIPS 0x2026 //     ''     ,        ''   , "ELLIPS" for bullet: …
#define CS_FINGER 0x261E //     ''     ,        ''   , "FINGER" for finger: ☞
#define CS_MIDDOT 0x00B7 //     ''     ,        ''   , "MIDDOT" for mid dot: ·
#define CS_PARA   0x00A7 //     ''     ,        ''   , "PARA" for paragraaf: §

     // super and sub script numbers
#define CN_0SUB  0x2080 //      ''     , N for number, "SUB" for sub-script or "SUP" for super-script:₀
#define CN_0SUP  0x2070 //      ''     ,    ''       ,                           ''                  :⁰
#define CN_1SUB  0x2081 //      ''     ,    ''       ,        ''                                     :₁
#define CN_1SUP  0xB9   //      ''     ,    ''       ,                           ''                  :¹
#define CN_2SUB  0x2082 //      ''     ,    ''       ,        ''                                     :₂
#define CN_2SUP  0xB2   //      ''     ,    ''       ,                           ''                  :²
#define CN_3SUB  0x2083 //      ''     ,    ''       ,        ''                                     :₃
#define CN_3SUP  0xB3   //      ''     ,    ''       ,                           ''                  :³
#define CN_4SUB  0x2084 //      ''     ,    ''       ,        ''                                     :₄
#define CN_4SUP  0x2074 //      ''     ,    ''       ,                           ''                  :⁴
#define CN_5SUB  0x2085 //      ''     ,    ''       ,        ''                                     :₅
#define CN_5SUP  0x2075 //      ''     ,    ''       ,                           ''                  :⁵
#define CN_6SUB  0x2086 //      ''     ,    ''       ,        ''                                     :₆
#define CN_6SUP  0x2076 //      ''     ,    ''       ,                           ''                  :⁶
#define CN_7SUB  0x2087 //      ''     ,    ''       ,        ''                                     :₇
#define CN_7SUP  0x2077 //      ''     ,    ''       ,                           ''                  :⁷
#define CN_8SUB  0x2088 //      ''     ,    ''       ,        ''                                     :₈
#define CN_8SUP  0x2078 //      ''     ,    ''       ,                           ''                  :⁸
#define CN_9SUB  0x2089 //      ''     ,    ''       ,        ''                                     :₉
#define CN_9SUP  0x2079 //      ''     ,    ''       ,                           ''                  :⁹

// Exponent symbols
#define CS_CPSUB  0x208E //   ''     ,    ''       , "C" for closing, "P" for paranthesis, "SUB" for subscript: ₎
#define CS_OPSUB  0x208D //   ''     ,    ''       , "O" for opening,     ''             ,       ''           : ₍
#define CS_CPSUP  0x207E //   ''     ,    ''       , "C" for closing,     ''             , "SUP" for superscript: ⁾
#define CS_OPSUP  0x207D //   ''     ,    ''       , "O" for opening:     ''             ,       ''             : ⁽
#define CS_EXPMIN 0x207B //   ''     ,    ''       , "EXP" for exponent, "MIN" for minus : ⁻
#define CS_EXPPLS 0x207A //   ''     ,    ''       ,       ''          , "PLS" for plus : ⁺
// Math
#define CS_ABOUT  0x2248 //   ''     ,    ''       , "ABOUT" for about equal: ≈
#define CS_CUMMU  0x2211 //   ''     ,    ''       , "CUMMU" for cummulative: ∑
#define CS_DIVI   0xF7 //     ''     ,    ''       , "DIVI" for division: ÷
#define CS_EGTHAN 0x2265 //   ''     ,    ''       , "E" for equal, "G" for or-greater, "THAN" for than: ≥
#define CS_ELTHAN 0x2264 //   ''     ,    ''       , "E" for equal, "L" for or-less, "THAN" for than: ≤
#define CS_INFIN  0x221E //   ''     ,    ''       , "INFIN" for infinity: ∞
#define CS_MULT   0xD7 //     ''     ,    ''       , "MULTI" for multiplication: ×
#define CS_NONE   0x2205 //   ''     ,    ''       , "NONE" for empty-set / no-solution: ∅ 
#define CS_PLMI   0xB1   //   ''     ,    ''       , "PLMI" for plus-minus; ±
#define CS_PROM   0x2030 //   ''     ,    ''       , "PROM" for promille: ‰
#define CS_PROTT  0x2031 //   ''     ,    ''       , "PRO" for pro-, "TT" for ten-thousandth: ‱
#define CS_SQRT   0x221A //   ''     ,    ''       , "SQRT" for square root: √
#define CS_UNEQL  0x2260 //   ''     ,    ''       , "UNEQL" for unequal: ≠
 
# ifdef POINT_ON_CHECKBOXES
    // pointers
#     define CS_CHECK_H 0x2B9B // ''     ,    ''       , "H" for Down,          ''      : ⮛
#     define CS_CHECK_B 0x2B98 // ''     ,    ''       , "L" for Left, "ARROW" for arrow: ⮘
#     define CS_CHECK_Y 0x2B9A // ''     ,    ''       , "R" for Right,         ''      : ⮚
#     define CS_CHECK_N 0x2B99 // ''     ,    ''       , "U" for UP,            ''      : ⮙
# else
    // checkboxes
#     define CS_CHECK_H 0x1F5F9 // ''  ,    ''       , "CHECK" for check mark, "H" for heavy: 🗹
#     define CS_CHECK_B 0x2610 //  ''  ,    ''       ,         ''            , "B" for blank: ☐ 
#     define CS_CHECK_Y 0x2611 //  ''  ,    ''       ,         ''            , "Y" for yes: ☑ 
#     define CS_CHECK_N 0x2612 //  ''  ,    ''       ,         ''            , "N" for no: ☒ 
# endif

// More arrows
#define CS_ARR_DN 0x2B07 //     ''     ,    ''       , "ARR" for arrow, "DN" for down: ⬇
#define CS_ARR_LE 0x2B05 //     ''     ,    ''       , "ARR" for arrow, "LE" for left: ⬅
#define CS_ARR_RI 0x27A1 //     ''     ,    ''       , "ARR" for arrow, "RI" for right: ➡
#define CS_ARR_UP 0x2B06 //     ''     ,    ''       , "ARR" for arrow, "UP" for up: ⬆

// More checkmarks
#define CS_BOTCH 0x2717 //      ''     ,    ''       , "BOTCH" for botched: ✗
#define CS_CHECK 0x2713 //      ''     ,    ''       , "CHECK" for check mark: ✓

// circled numbers
#define CN_0CIRC  0x24EA //   ''     , "N" for number, "0" for , "CIRC" for circled: ⓪
#define CN_1CIRC  0x2460 //   ''     ,     ''        , "1" for 1, "CIRC" for circled: ①
#define CN_2CIRC  0x2461 //   ''     ,     ''        , "2" for 2, "CIRC" for circled: ②
#define CN_3CIRC  0x2462 //   ''     ,     ''        , "3" for 3, "CIRC" for circled: ③
#define CN_4CIRC  0x2463 //   ''     ,     ''        , "4" for 4, "CIRC" for circled: ④
#define CN_5CIRC  0x2464 //   ''     ,     ''        , "5" for 5, "CIRC" for circled: ⑤
#define CN_6CIRC  0x2465 //   ''     ,     ''        , "6" for 6, "CIRC" for circled: ⑥
#define CN_7CIRC  0x2466 //   ''     ,     ''        , "7" for 7, "CIRC" for circled: ⑦
#define CN_8CIRC  0x2467 //   ''     ,     ''        , "8" for 8, "CIRC" for circled: ⑧
#define CN_9CIRC  0x2468 //   ''     ,     ''        , "9" for 9, "CIRC" for circled: ⑨
#define CN_10CIRC 0x2469 //   ''     ,     ''        , "10" for 10, "CIRC" for circled: ⑩
#define CN_11CIRC 0x246A //   ''     ,     ''        , "11" for 11, "CIRC" for circled: ⑪
#define CN_12CIRC 0x246B //   ''     ,     ''        , "12" for 12, "CIRC" for circled: ⑫
#define CN_13CIRC 0x246C //   ''     ,     ''        , "13" for 13, "CIRC" for circled: ⑬
#define CN_14CIRC 0x246D //   ''     ,     ''        , "14" for 14, "CIRC" for circled: ⑭
#define CN_15CIRC 0x246E //   ''     ,     ''        , "15" for 15, "CIRC" for circled: ⑮
#define CN_16CIRC 0x246F //   ''     ,     ''        , "16" for 16, "CIRC" for circled: ⑯
#define CN_17CIRC 0x2470 //   ''     ,     ''        , "17" for 17, "CIRC" for circled: ⑰
#define CN_18CIRC 0x2471 //   ''     ,     ''        , "18" for 18, "CIRC" for circled: ⑱
#define CN_19CIRC 0x2472 //   ''     ,     ''        , "19" for 19, "CIRC" for circled: ⑲

// Box drawings
#define CB_C_LEDN 0x2513 //   ''     , "B" for box drawing, "C" for corner, "LE" for left, "DN" for down: ┓
#define CB_C_LEUP 0x251B //   ''     ,     ''             , "C" for corner, "LE" for left, "UP" for up: ┛
#define CB_C_RIDN 0x250F //   ''     ,     ''             , "C" for corner, "RI" for right, "DN" for down: ┏
#define CB_C_RIUP 0x2517 //   ''     ,     ''             , "C" for corner, "RI" for right, "UP" for up: ┗
#define CB_VE     0x2503 //   ''     ,     ''             , "VE" for verticle: ┃
#define CB_VE_BI  0x254B //   ''     ,     ''             , "VE" for verticle, "BI" for bi (two): ╋
#define CB_VE_DOT 0x2507 //   ''     ,     ''             , "VE" for verticle, "DOT" for dotted: ┇
#define CB_VE_LE  0x252B //   ''     ,     ''             , "VE" for verticle, "LE" for left: ┫
#define CB_VE_RI  0x2523 //   ''     ,     ''             , "VE" for verticle, "RI" for right: ┣
// Horizontal lines, can be used with box drawings
#define CB_HHORI  0x2501 //   ''     ,     ''             , "H" for heavy,         ''           : ━
#define CB_HHORID 0x2505 //   ''     ,     ''             , "H" for heavy,         ''           , "D" for dashes: ┅
#define CB_LHORI  0x2500 //   ''     ,     ''             , "L" for light, "HORI" for horizontal: ─
#define CB_LHORID 0x2504 //   ''     ,     ''             , "L" for light,         ''           , "D" for dashes: ┄

// Signs, unusual
#define CS_ALERT 0x26A0 //    ''     , "S" for symbol, "ALERT" for alert/warning: ⚠
#define CS_STARB 0x2605 //    ''     ,    ''         , "STAR" for star, "B" for big: ★
#define CS_STARL 0x66D  //    ''     ,    ''         , "STAR" for star, "L" for little: ٭
#define CS_FLEUR 0x2766 //    ''     ,    ''         , "FLEUR" for fleur (flower): ❦
#define CS_HEART 0x2665 //    ''     ,    ''         , "HEART" for heart: ♥
