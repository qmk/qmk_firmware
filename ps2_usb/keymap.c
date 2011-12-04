/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/* 
 * Keymap for PS/2 keyboard
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "usb_keycodes.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"




// Following macros help you to define a keymap with the form of actual keyboard layout.

/* US layout plus all other various keys */
#define KEYMAP_ALL( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5D, KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,               K6B,K73,K74,K79, \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,        K59,     KF5,      K69,K72,K7A,     \
    K14,K9F,K11,        K29,                K91,KA7,KAF,K94, KEB,KF2,KF4,  K70,    K71,KDA, \
                                                                                            \
    K61,                     /* for European ISO */                                         \
    K51, K13, K6A, K64, K67, /* for Japanese JIS */                                         \
    K08, K10, K18, K20, K28, K30, K38, K40, K48, K50, K57, K5F, /* F13-24 */                \
    KB7, KBF, KDE,           /* System Power, Sleep, Wake */                                \
    KA3, KB2, KA1,           /* Mute, Volume Up, Volume Down */                             \
    KCD, K95, KBB, KB4, KD0, /* Next, Previous, Stop, Pause, Media Select */                \
    KC8, KAB, KC0,           /* Mail, Calculator, My Computer */                            \
    K90, KBA, KB8, KB0,      /* WWW Search, Home, Back, Forward */                          \
    KA8, KA0, K98            /* WWW Stop, Refresh, Favorites */                             \
) { \
    { KB_NO,    KB_##K01, KB_NO,    KB_##K03, KB_##K04, KB_##K05, KB_##K06, KB_##K07 }, \
    { KB_##K08, KB_##K09, KB_##K0A, KB_##K0B, KB_##K0C, KB_##K0D, KB_##K0E, KB_NO    }, \
    { KB_##K10, KB_##K11, KB_##K12, KB_##K13, KB_##K14, KB_##K15, KB_##K16, KB_NO    }, \
    { KB_##K18, KB_NO,    KB_##K1A, KB_##K1B, KB_##K1C, KB_##K1D, KB_##K1E, KB_NO    }, \
    { KB_##K20, KB_##K21, KB_##K22, KB_##K23, KB_##K24, KB_##K25, KB_##K26, KB_NO    }, \
    { KB_##K28, KB_##K29, KB_##K2A, KB_##K2B, KB_##K2C, KB_##K2D, KB_##K2E, KB_NO    }, \
    { KB_##K30, KB_##K31, KB_##K32, KB_##K33, KB_##K34, KB_##K35, KB_##K36, KB_NO    }, \
    { KB_##K38, KB_NO,    KB_##K3A, KB_##K3B, KB_##K3C, KB_##K3D, KB_##K3E, KB_NO    }, \
    { KB_##K40, KB_##K41, KB_##K42, KB_##K43, KB_##K44, KB_##K45, KB_##K46, KB_NO    }, \
    { KB_##K48, KB_##K49, KB_##K4A, KB_##K4B, KB_##K4C, KB_##K4D, KB_##K4E, KB_NO    }, \
    { KB_##K50, KB_##K51, KB_##K52, KB_NO,    KB_##K54, KB_##K55, KB_NO,    KB_##K57 }, \
    { KB_##K58, KB_##K59, KB_##K5A, KB_##K5B, KB_NO,    KB_##K5D, KB_NO,    KB_##K5F }, \
    { KB_NO,    KB_##K61, KB_NO,    KB_NO,    KB_##K64, KB_NO,    KB_##K66, KB_##K67 }, \
    { KB_NO,    KB_##K69, KB_##K6A, KB_##K6B, KB_##K6C, KB_NO,    KB_NO,    KB_NO    }, \
    { KB_##K70, KB_##K71, KB_##K72, KB_##K73, KB_##K74, KB_##K75, KB_##K76, KB_##K77 }, \
    { KB_##K78, KB_##K79, KB_##K7A, KB_##K7B, KB_##K7C, KB_##K7D, KB_##K7E, KB_NO    }, \
    { KB_NO,    KB_NO,    KB_NO,    KB_##K83, KB_NO,    KB_NO,    KB_NO,    KB_NO    }, \
    { KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO    }, \
    { KB_##K90, KB_##K91, KB_NO,    KB_NO,    KB_##K94, KB_##K95, KB_NO,    KB_NO    }, \
    { KB_##K98, KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_##K9F }, \
    { KB_##KA0, KB_##KA1, KB_NO,    KB_##KA3, KB_NO,    KB_NO,    KB_NO,    KB_##KA7 }, \
    { KB_##KA8, KB_NO,    KB_NO,    KB_##KAB, KB_NO,    KB_NO,    KB_NO,    KB_##KAF }, \
    { KB_##KB0, KB_NO,    KB_##KB2, KB_NO,    KB_##KB4, KB_NO,    KB_NO,    KB_##KB7 }, \
    { KB_##KB8, KB_NO,    KB_##KBA, KB_##KBB, KB_NO,    KB_NO,    KB_NO,    KB_##KBF }, \
    { KB_##KC0, KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO    }, \
    { KB_##KC8, KB_NO,    KB_##KCA, KB_NO,    KB_NO,    KB_##KCD, KB_NO,    KB_NO    }, \
    { KB_##KD0, KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO    }, \
    { KB_NO,    KB_NO,    KB_##KDA, KB_NO,    KB_NO,    KB_NO,    KB_##KDE, KB_NO    }, \
    { KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO    }, \
    { KB_NO,    KB_##KE9, KB_NO,    KB_##KEB, KB_##KEC, KB_NO,    KB_NO,    KB_NO    }, \
    { KB_##KF0, KB_##KF1, KB_##KF2, KB_NO,    KB_##KF4, KB_##KF5, KB_NO,    KB_NO    }, \
    { KB_NO,    KB_NO,    KB_##KFA, KB_NO,    KB_##KFC, KB_##KFD, KB_##KFE, KB_NO    }, \
}

/* US layout */
#define KEYMAP( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5D, KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,               K6B,K73,K74,K79, \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,        K59,     KF5,      K69,K72,K7A,     \
    K14,K9F,K11,        K29,                K91,KA7,KAF,K94, KEB,KF2,KF4,  K70,    K71,KDA  \
) \
KEYMAP_ALL( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5D, KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,               K6B,K73,K74,K79, \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,        K59,     KF5,      K69,K72,K7A,     \
    K14,K9F,K11,        K29,                K91,KA7,KAF,K94, KEB,KF2,KF4,  K70,    K71,KDA, \
                                                                                            \
    NUBS,                                                                                   \
    RO, KANA, JYEN, HENK, MHEN,                                                             \
    F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,                             \
    SYSTEM_POWER, SYSTEM_SLEEP, SYSTEM_WAKE,                                                \
    AUDIO_MUTE, AUDIO_VOL_UP, AUDIO_VOL_DOWN,                                               \
    MEDIA_NEXT_TRACK, MEDIA_PREV_TRACK, MEDIA_STOP, MEDIA_PLAY_PAUSE, MEDIA_SELECT,         \
    MAIL, CALCULATOR, MY_COMPUTER,                                                          \
    WWW_SEARCH, WWW_HOME, WWW_BACK, WWW_FORWARD,                                            \
    WWW_STOP, WWW_REFRESH, WWW_FAVORITES                                                    \
)

/* ISO layout */
#define KEYMAP_ISO( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,     KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,K5D,K5A,               K6B,K73,K74,K79, \
    K12,K61,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K59,     KF5,      K69,K72,K7A,     \
    K14,K9F,K11,        K29,                K91,KA7,KAF,K94, KEB,KF2,KF4,  K70,    K71,KDA  \
) \
KEYMAP_ALL( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5D, KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,               K6B,K73,K74,K79, \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,        K59,     KF5,      K69,K72,K7A,     \
    K14,K9F,K11,        K29,                K91,KA7,KAF,K94, KEB,KF2,KF4,  K70,    K71,KDA, \
                                                                                            \
    K61,                                                                                    \
    RO, KANA, JYEN, HENK, MHEN,                                                             \
    F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,                             \
    SYSTEM_POWER, SYSTEM_SLEEP, SYSTEM_WAKE,                                                \
    AUDIO_MUTE, AUDIO_VOL_UP, AUDIO_VOL_DOWN,                                               \
    MEDIA_NEXT_TRACK, MEDIA_PREV_TRACK, MEDIA_STOP, MEDIA_PLAY_PAUSE, MEDIA_SELECT,         \
    MAIL, CALCULATOR, MY_COMPUTER,                                                          \
    WWW_SEARCH, WWW_HOME, WWW_BACK, WWW_FORWARD,                                            \
    WWW_STOP, WWW_REFRESH, WWW_FAVORITES                                                    \
)

/* JIS layout */
#define KEYMAP_JIS( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,         KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K6A,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,         KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,K5D,    K5A,               K6B,K73,K74,K79, \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,K51,        K59,     KF5,      K69,K72,K7A,     \
    K14,K9F,K11,    K67,K29,K64,K13,            K91,KA7,KAF,K94, KEB,KF2,KF4,  K70,    K71,KDA  \
) \
KEYMAP_ALL( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5D, KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,               K6B,K73,K74,K79, \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,        K59,     KF5,      K69,K72,K7A,     \
    K14,K9F,K11,        K29,                K91,KA7,KAF,K94, KEB,KF2,KF4,  K70,    K71,KDA, \
                                                                                            \
    NUBS,                                                                                   \
    K51, K13, K6A, K64, K67,                                                                \
    F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,                             \
    SYSTEM_POWER, SYSTEM_SLEEP, SYSTEM_WAKE,                                                \
    AUDIO_MUTE, AUDIO_VOL_UP, AUDIO_VOL_DOWN,                                               \
    MEDIA_NEXT_TRACK, MEDIA_PREV_TRACK, MEDIA_STOP, MEDIA_PLAY_PAUSE, MEDIA_SELECT,         \
    MAIL, CALCULATOR, MY_COMPUTER,                                                          \
    WWW_SEARCH, WWW_HOME, WWW_BACK, WWW_FORWARD,                                            \
    WWW_STOP, WWW_REFRESH, WWW_FAVORITES                                                    \
)


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    5,              // Fn0
    6,              // Fn1
    0,              // Fn2
    0,              // Fn3
    0,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KB_SCLN,        // Fn0
    KB_SLSH,        // Fn1
    KB_NO,          // Fn2
    KB_NO,          // Fn3
    KB_NO,          // Fn4
    KB_NO,          // Fn5
    KB_NO,          // Fn6
    KB_NO           // Fn7
};


// The keymap is a 32*8 byte array which convert a PS/2 scan code into a USB keycode.
// See usb_keycodes.h for USB keycodes. You should omit a 'KB_' prefix of USB keycodes in keymap macro.
// Use KEYMAP_ISO() or KEYMAP_JIS() instead of KEYMAP() if your keyboard is ISO or JIS.
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* keymap
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.     ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|     |Pwr|Slp|Wak|
     * `---'   `---------------' `---------------' `---------------' `-----------'     `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|  +|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl| |Lef|Dow|Rig| |      0|  .|   |
     * `-----------------------------------------------------------' `-----------' `---------------'
     */
    /* 0: default */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN0, QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN1,           RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 1: plain Qwerty without layer switching */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 2: Colemak http://colemak.com */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   F,   P,   G,   J,   L,   U,   Y,   SCLN,LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    BSPC,A,   R,   S,   T,   D,   H,   N,   E,   I,   O,   QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   K,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 3: Dvorak http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   LBRC,RBRC,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, QUOT,COMM,DOT, P,   Y,   F,   G,   C,   R,   L,   SLSH,EQL, BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,A,   O,   E,   U,   I,   D,   H,   T,   N,   S,   MINS,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,SCLN,Q,   J,   K,   X,   B,   M,   W,   V,   Z,             RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 4: Workman http://viralintrospection.wordpress.com/2010/09/06/a-different-philosophy-in-designing-keyboard-layouts/ */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   D,   R,   W,   B,   J,   F,   U,   P,   SCLN,LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    BSPC,A,   S,   H,   T,   G,   Y,   N,   E,   O,   I,   QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   M,   C,   V,   K,   L,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 5: Mouse keys */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F8,  F10, F11, F12, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, WH_L,WH_D,MS_U,WH_U,WH_R,WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,  BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,NO,  MS_L,MS_D,MS_R,NO,  MS_L,MS_D,MS_U,MS_R,FN0, NO,       ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,VOLD,VOLU,MUTE,BTN2,BTN3,BTN2,BTN1,VOLD,VOLU,MUTE,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          BTN1,                    RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 6: Cursor keys */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F8,  F10, F11, F12, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, NO,  NO,  NO,  BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,NO,  NO,  NO,  NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,       ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,VOLD,VOLU,MUTE,NO,  NO,  HOME,PGDN,PGUP,END, FN1,           RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return pgm_read_byte(&keymaps[(layer)][(row)][(col)]);
}

uint8_t keymap_fn_layer(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_layer[biton(fn_bits)]);
}

uint8_t keymap_fn_keycode(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_keycode[(biton(fn_bits))]);
}
