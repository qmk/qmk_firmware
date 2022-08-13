/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define TRANS_LAYER_NO 11

#define TRANS_KEYCODES_ENUM TM_AVC,TM_AAC,TM_DC,TM_EC,TM_MUT,TM_VID,ED_ZOP,ED_ZON,ED_NEWT,ED_NTAB,ED_PTAB,ED_CTAB,ED_RTAB,VS_SB,VS_COM,VS_UCOM,VS_NCUR,VS_BCUR,VS_ZOP,VS_ZON,DC_NUCM,DC_PUCM,DC_AC

#define TRANS_CUSTOM_KEYCODES case TM_AVC: SEND_STRING(SS_LCTL(SS_LSFT("a"))); break; case TM_AAC: SEND_STRING(SS_LCTL(SS_LSFT("s"))); break; case TM_DC: SEND_STRING(SS_LCTL(SS_LSFT("d"))); break; case TM_EC: SEND_STRING(SS_LCTL(SS_LSFT("h"))); break; case TM_MUT: SEND_STRING(SS_LCTL(SS_LSFT("m"))); break; case TM_VID: SEND_STRING(SS_LCTL(SS_LSFT("o"))); break; case ED_ZOP: SEND_STRING(SS_LCTL("+")); break; case ED_ZON: SEND_STRING(SS_LCTL("-")); break; case ED_NEWT: SEND_STRING(SS_LCTL("n")); break; case ED_NTAB: SEND_STRING(SS_LCTL(SS_TAP(X_TAB))); break; case ED_PTAB: SEND_STRING(SS_LCTL(SS_TAP(X_PGDN))); break; case ED_CTAB: SEND_STRING(SS_LCTL("w")); break; case ED_RTAB: SEND_STRING(SS_LCTL(SS_LSFT("t"))); break; case VS_SB: SEND_STRING(SS_LCTL("b")); break; case VS_COM: SEND_STRING(SS_DOWN(X_LCTRL) "k" SS_DELAY(20) "c" SS_UP(X_LCTRL)); break; case VS_UCOM: SEND_STRING(SS_DOWN(X_LCTRL) "k" SS_DELAY(20) "u" SS_UP(X_LCTRL)); break; case VS_NCUR: SEND_STRING(SS_LCTL(SS_TAP(X_RGHT))); break; case VS_BCUR: SEND_STRING(SS_LCTL(SS_TAP(X_LEFT))); break; case VS_ZOP: SEND_STRING(SS_LCTL(SS_LSFT("."))); break; case VS_ZON: SEND_STRING(SS_LCTL(SS_LSFT(","))); break; case DC_NUCM: SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT(SS_TAP(X_DOWN))))); break; case DC_PUCM: SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT(SS_TAP(X_UP))))); break; case DC_AC: SEND_STRING(SS_LCTL("\n")); break;

#define TRANS_LAYER_STRINGS "Media Controls","Teams Macros","Edge Macros","VSCode Macros","Visual Studio","Discord","Configuration","Configuration","Lockscreen","TOPT","Empty"

#define TRANS_KEYMAP_STRINGS {{"","","RGB TOG"},{"","Vol. +",""},{"","Vol. -",""},{"","Mute",""},{"Prev T ","Play","Next T."}},{{"","","RGB TOG"},{"Vol. +","Accpt C"," Mute M"},{"Vol. -","Accpt V"," Tog V"},{"Mute","Decln C",""},{"","End Cll",""}},{{"","","RGB TOG"},{"Zoom +","New Tab"," Vol. +"},{"Zoom -","Nxt Tab"," Vol. -"},{"Cls Tb ","Prv Tab"," Mute"},{"Prev T.","Play","Next T."}},{{"","","RGB TOG"},{"Zoom +","","Sidebar"},{"Zoom -","Nxt Tab"," Cmment"},{"","Prv Tab","Ucmmnt"},{"Bck cur","","Nxt cur"}},{{"","","RGB TOG"},{"Zoom +","RunDbg",""},{"Zoom -",""," Cmment"},{"","StepIn"," Ucmmnt"},{"Bckcur ","NextBp "," Nxtcur"}},{{"","","RGB TOG"},{"Acpt C ","PrvMsg ","NxtMsg"},{"","PageUp ","Vol. +"},{"","PageDn ","Vol. -"},{"","",""}},{{"","","RGB TOG"},{"IndOLED","TgIndi ","MskAnim"},{"BongoC ","RGBHUE ","ShwAnim"},{"Logo","RGBSAT ","RGBMOD"},{"LShift ","RGBVAL ","RGBSPD "}},{{"","","RGB TOG"},{"EEreset","Make","Boot"},{"Debug","",""},{"","",""},{"","",""}},{{"","",""},{"","",""},{"","",""},{"","",""},{"","",""}},{{"","",""},{"FB","Google","Twitter"},{"IG","HMail",""},{"","",""},{"","",""}},{{"","",""},{"","",""},{"","",""},{"","",""},{"","",""}}

#define TRANS_INDICATORS {{{0x000000}, {0xfc035a}, {0x000000}},{{0x000000}, {0xfc035a}, {0x000000}},{{0x000000}, {0x00ccff}, {0x000000}},{{0x0aff43}, {0x0aff43}, {0x0aff43}}},{{{0xfc035a}, {0x2ee634}, {0xff0a58}},{{0xfc035a}, {0x2ee634}, {0x993f5b}},{{0x00ccff}, {0xe6502e}, {0x000000}},{{0x000000}, {0xe62e2e}, {0x000000}}},{{{0x9f36f5}, {0x9f36f5}, {0xfc035a}},{{0x9f36f5}, {0x9f36f5}, {0xfc035a}},{{0x9f36f5}, {0x9f36f5}, {0x00ccff}},{{0xfc035a}, {0xfc035a}, {0xfc035a}}},{{{0x9f36f5}, {0x000000}, {0xfc035a}},{{0x9f36f5}, {0x9f36f5}, {0xfc035a}},{{0x000000}, {0x9f36f5}, {0xfc035a}},{{0xfc035a}, {0x000000}, {0xfc035a}}},{{{0xfc035a}, {0x8ae6b5}, {0x000000}},{{0xfc035a}, {0x000000}, {0x65f235}},{{0x000000}, {0x8ae6b5}, {0x0c2e00}},{{0xfc035a}, {0x8ae6b5}, {0xfc035a}}},{{{0xdb043e}, {0x0f3efa}, {0x0f3efa}},{{0x000000}, {0x8ae6b5}, {0xfc035a}},{{0x000000}, {0x8ae6b5}, {0xfc035a}},{{0x000000}, {0x000000}, {0x000000}}},{{{0x0ffaf6}, {0x0ffaf6}, {0x0ffaf6}},{{0x0ffaf6}, {0x3d0099}, {0x0ffaf6}},{{0x0ffaf6}, {0x3d0099}, {0x3d0099}},{{0xd2db25}, {0x3d0099}, {0x3d0099}}},{{{0xff0000}, {0x00ff00}, {0x0000ff}},{{0x3d0099}, {0x000000}, {0x000000}},{{0x000000}, {0x000000}, {0x000000}},{{0x000000}, {0x000000}, {0x000000}}},{{{0x505050}, {0x505050}, {0x505050}},{{0x505050}, {0x505050}, {0x505050}},{{0x505050}, {0x505050}, {0x505050}},{{0x505050}, {0x505050}, {0x500000}}},{{{0x505050}, {0x505050}, {0x505050}},{{0x505050}, {0x505050}, {0x000000}},{{0x000000}, {0x000000}, {0x000000}},{{0x000000}, {0x000000}, {0x000000}}},{{{0x000000}, {0x000000}, {0x000000}},{{0x000000}, {0x000000}, {0x000000}},{{0x000000}, {0x000000}, {0x000000}},{{0x000000}, {0x000000}, {0x000000}}}

#define TRANS_KEYMAP [0] = LAYOUT(RGB_TOG,KC_NO,KC_VOLU,KC_NO,KC_NO,KC_VOLD,KC_NO,KC_NO,KC_MUTE,KC_NO,KC_MPRV,KC_MPLY,KC_MNXT),[1] = LAYOUT(RGB_TOG,KC_VOLU,TM_AVC,TM_MUT,KC_VOLD,TM_AAC,TM_VID,KC_MUTE,TM_DC,KC_NO,KC_NO,TM_EC,KC_NO),[2] = LAYOUT(RGB_TOG,ED_ZOP,ED_NEWT,KC_VOLU,ED_ZON,ED_NTAB,KC_VOLD,ED_CTAB,ED_PTAB,KC_MUTE,KC_MPRV,KC_MPLY,KC_MNXT),[3] = LAYOUT(RGB_TOG,ED_ZOP,KC_NO,VS_SB,ED_ZON,ED_NTAB,VS_COM,KC_NO,ED_PTAB,VS_UCOM,VS_BCUR,KC_NO,VS_NCUR),[4] = LAYOUT(RGB_TOG,VS_ZOP,KC_F5,KC_NO,VS_ZON,KC_NO,VS_COM,KC_NO,KC_F11,VS_UCOM,VS_BCUR,KC_F10,VS_NCUR),[5] = LAYOUT(RGB_TOG,DC_AC,DC_PUCM,DC_NUCM,KC_NO,KC_PGUP,KC_VOLU,KC_NO,KC_PGDN,KC_VOLD,KC_NO,KC_NO,KC_NO),[6] = LAYOUT(RGB_TOG,MC_ODEF,MC_INDI,MC_MSKI,MC_OBNC,RGB_HUI,MC_SHWA,MC_OLOG,RGB_SAI,RGB_MOD,KC_LSFT,RGB_VAI,RGB_SPI),[7] = LAYOUT(RGB_TOG,EE_CLR,QK_MAKE,QK_BOOT,DB_TOGG,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),[8] = LAYOUT(RGB_TOG,LS_BTN7,LS_BTN8,LS_BTN9,LS_BTN4,LS_BTN5,LS_BTN6,LS_BTN1,LS_BTN2,LS_BTN3,LS_BTN0,LS_BTN0,LS_BACK),[9] = LAYOUT(KC_NO,OTPBTN0,OTPBTN1,OTPBTN2,OTPBTN3,OTPBTN4,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),[10] = LAYOUT(RGB_TOG,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO)

#define TOTP_LAYER 9

#if (__has_include("keys.h"))
    #include "keys.h"
#else
    #define DISABLE_SECRETS
#endif
