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

 * Author: © 2021 by Jos Boersema
 *
 */

#pragma once

/*        An amount of Unicode #defines
 *        - hebrew
 */

    // 
#define HB_ALEF  0x05D0 // 'HB' for 'Hebrew', "ALEF" for Alef         : א
#define HB_BET   0x05D1 //      "           , "BET" for Bet           : ב
#define HB_GIMEL 0x05D2 //      "           , "GIMEL" for Gimel       : ג
#define HB_DALET 0x05D3 //      "           , "DALET" for Daled       : ד
#define HB_HE    0x05D4 //      "           , "HE" for He             : ה
#define HB_VAV   0x05D5 //      "           , "VAV" for Vav           : ו
#define HB_ZAYIN 0x05D6 //      "           , "ZAYIN" for Zayin       : ז
#define HB_GET   0x05D7 //      "           , "HET" for Het           : ח
#define HB_TET   0x05D8 //      "           , "TET" for Tet           : ט
#define HB_YOD   0x05D9 //      "           , "YOD" for Yod           : י
#define HB_KAFS  0x05DA //      "           , "KAFS" for Kaf sofiet   : ך
#define HB_KAF   0x05DB //      "           , "KAF" for Kaf           : כ
#define HB_LAMED 0x05DC //      "           , "LAMED" for Lamed       : ל
#define HB_MEMS  0x05DD //      "           , "MEMS" for Mem sofiet   : ם
#define HB_MEM   0x05DE //      "           , "MEM" for Mem           : מ
#define HB_NUNS  0x05DF //      "           , "NUNS" for Nun sofiet   : ן
#define HB_NUN   0x05E0 //      "           , "NUN" for Nun           : נ
#define HB_SAMEG 0x05E1 //      "           , "SAMEG" for Sameg       : ס
#define HB_AYIN  0x05E2 //      "           , "AYIN" for Ayin         : ע
#define HB_PES   0x05E3 //      "           , "PES"  for Pe sofiet    : ף
#define HB_PE    0x05E4 //      "           , "PE" for Pe             : פ
#define HB_TSDIS 0x05E5 //      "           , "TSDIS" for Tsadi sofiet: ץ
#define HB_TSADI 0x05E6 //      "           , "TSADI" for Tsadi       : צ
#define HB_QOF   0x05E7 //      "           , "QOF" for Qof           : ק
#define HB_RESH  0x05E8 //      "           , "RESH" for Resh         : ר
#define HB_SHIN  0x05E9 //      "           , "SHIN" for Shin         : ש
#define HB_TAV   0x05EA //      "           , "TAV" for Tav           : ת
#define HB_MAQAF 0x05be //      "           , "MAQAF" for Maqaf       : ־

// Yiddish digraphs:
//#define HB_D_VAV 0x05F0 //      "           , "D_VAV" for double Van  : װ
//#define HB_VAVYD 0x05F1 //      "           , "VAVYD" for Vav Yod     : ױ
//#define HB_D_YOD 0x05F2 //      "           , "D_YOD" for double Yod  : ײ

// special
#define HB_RLM   0x200F //      "           , "RLM" for Right-Left-Mark: <non-printing>
#define HB_LRM   0x200E //      "           , "LRM" for Left-Right-Mark: <non-printing>


// The below are displacing symbols on other layers, some of which are quite obscure
// and end up being unused. They are compiled based on a #define.
// These where reported as symbols present on hebrew keyboards: 
// U+05F3 : HEBREW PUNCTUATION GERESH
// U+20AC : EURO SIGN
// U+20AA : NEW SHEQEL SIGN {shekel}
// U+00B0 : DEGREE SIGN
// U+05AB : HEBREW ACCENT OLE
// U+05BD : HEBREW POINT METEG {siluq}
// U+00D7 : MULTIPLICATION SIGN {z notation Cartesian product}
// U+200E : LEFT-TO-RIGHT MARK [LRM]
// U+200F : RIGHT-TO-LEFT MARK [RLM]
// U+05BE : HEBREW PUNCTUATION MAQAF
// U+2013 : EN DASH
// U+05C2 : HEBREW POINT SIN DOT
// U+05C1 : HEBREW POINT SHIN DOT
// U+05B8 : HEBREW POINT QAMATS
// U+05F0 : HEBREW LIGATURE YIDDISH DOUBLE VAV {tsvey vovn}
// U+05B9 : HEBREW POINT HOLAM
// U+05B7 : HEBREW POINT PATAH
// U+05B2 : HEBREW POINT HATAF PATAH
// U+05F1 : HEBREW LIGATURE YIDDISH VAV YOD
// U+05F2 : HEBREW LIGATURE YIDDISH DOUBLE YOD {tsvey yudn}
// U+05B4 : HEBREW POINT HIRIQ
// U+201D : RIGHT DOUBLE QUOTATION MARK {double comma quotation mark}
// U+201E : DOUBLE LOW-9 QUOTATION MARK {low double comma quotation mark}
// U+05F4 : HEBREW PUNCTUATION GERSHAYIM
// U+05B6 : HEBREW POINT SEGOL
// U+05B1 : HEBREW POINT HATAF SEGOL
// U+05B5 : HEBREW POINT TSERE
// U+2019 : RIGHT SINGLE QUOTATION MARK {single comma quotation mark}
// U+201A : SINGLE LOW-9 QUOTATION MARK {low single comma quotation mark}
// U+00F7 : DIVISION SIGN {obelus}
// U+05BA : HEBREW POINT HOLAM HASER FOR VAV
// U+200D : ZERO WIDTH JOINER [ZWJ]
// U+201C : LEFT DOUBLE QUOTATION MARK {double turned comma quotation mark}
// U+201D : RIGHT DOUBLE QUOTATION MARK {double comma quotation mark}
// U+034F : COMBINING GRAPHEME JOINER [CGJ]
// U+05C6 : HEBREW PUNCTUATION NUN HAFUKHA
// U+200C : ZERO WIDTH NON-JOINER [ZWNJ]
// U+2018 : LEFT SINGLE QUOTATION MARK {single turned comma quotation mark}
// U+2019 : RIGHT SINGLE QUOTATION MARK {single comma quotation mark}
// Note: many modifiers probably only work with a hebrew language setting on the computer
//  operating system. As Unicode, it would print a disconnected diacretical symbol.

// Geresh
#define HB_GERSH 0x05F3 //      "           , "GERSH" for Geresh      : 
#define HB_GRSHM 0x05F4 //      "           , "GRSHM" for Gershayim   : 
// Currency
#define HB_SHEKL 0x20AA //      "           , "SHEKL" for shekel      :
