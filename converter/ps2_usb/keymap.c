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
#include "keycode.h"
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
    { KC_NO,    KC_##K01, KC_NO,    KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_NO    }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_NO    }, \
    { KC_##K18, KC_NO,    KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_NO    }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_NO    }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_NO    }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_NO    }, \
    { KC_##K38, KC_NO,    KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_NO    }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_NO    }, \
    { KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_NO    }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_NO,    KC_##K54, KC_##K55, KC_NO,    KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_NO,    KC_##K5D, KC_NO,    KC_##K5F }, \
    { KC_NO,    KC_##K61, KC_NO,    KC_NO,    KC_##K64, KC_NO,    KC_##K66, KC_##K67 }, \
    { KC_NO,    KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_##K78, KC_##K79, KC_##K7A, KC_##K7B, KC_##K7C, KC_##K7D, KC_##K7E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##K83, KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##K90, KC_##K91, KC_NO,    KC_NO,    KC_##K94, KC_##K95, KC_NO,    KC_NO    }, \
    { KC_##K98, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K9F }, \
    { KC_##KA0, KC_##KA1, KC_NO,    KC_##KA3, KC_NO,    KC_NO,    KC_NO,    KC_##KA7 }, \
    { KC_##KA8, KC_NO,    KC_NO,    KC_##KAB, KC_NO,    KC_NO,    KC_NO,    KC_##KAF }, \
    { KC_##KB0, KC_NO,    KC_##KB2, KC_NO,    KC_##KB4, KC_NO,    KC_NO,    KC_##KB7 }, \
    { KC_##KB8, KC_NO,    KC_##KBA, KC_##KBB, KC_NO,    KC_NO,    KC_NO,    KC_##KBF }, \
    { KC_##KC0, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##KC8, KC_NO,    KC_##KCA, KC_NO,    KC_NO,    KC_##KCD, KC_NO,    KC_NO    }, \
    { KC_##KD0, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##KDA, KC_NO,    KC_NO,    KC_NO,    KC_##KDE, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_##KE9, KC_NO,    KC_##KEB, KC_##KEC, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##KF0, KC_##KF1, KC_##KF2, KC_NO,    KC_##KF4, KC_##KF5, KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##KFA, KC_NO,    KC_##KFC, KC_##KFD, KC_##KFE, KC_NO    }, \
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
    KC_SCLN,        // Fn0
    KC_SLSH,        // Fn1
    KC_NO,          // Fn2
    KC_NO,          // Fn3
    KC_NO,          // Fn4
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
};


// The keymap is a 32*8 byte array which convert a PS/2 scan code into a USB keycode.
// See keycode.h for USB keycodes. You should omit a 'KC_' prefix of USB keycodes in keymap macro.
// Use KEYMAP_ISO() or KEYMAP_JIS() instead of KEYMAP() if your keyboard is ISO or JIS.
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
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
     * ; = Fn0(to Layer 5)
     * / = Fn1(to Layer 6)
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN0, QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN1,           RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 1: plain Qwerty without layer switching
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 2: Colemak http://colemak.com
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |BackSp|  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  K|  M|  ,|  ,|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   F,   P,   G,   J,   L,   U,   Y,   SCLN,LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    BSPC,A,   R,   S,   T,   D,   H,   N,   E,   I,   O,   QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   K,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 3: Dvorak http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|    \|
     * |-----------------------------------------------------------|
     * |BackSp|  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  ;|  Q|  J|  K|  X|  B|  M|  Wl  V|  Z|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   LBRC,RBRC,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, QUOT,COMM,DOT, P,   Y,   F,   G,   C,   R,   L,   SLSH,EQL, BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,A,   O,   E,   U,   I,   D,   H,   T,   N,   S,   MINS,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,SCLN,Q,   J,   K,   X,   B,   M,   W,   V,   Z,             RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 4: Workman http://viralintrospection.wordpress.com/2010/09/06/a-different-philosophy-in-designing-keyboard-layouts/
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  D|  R|  W|  B|  J|  F|  U|  P|  ;|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |CapsLo|  A|  S|  H|  T|  G|  Y|  N|  E|  O|  I|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  M|  C|  V|  K|  L|  ,|  ,|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   D,   R,   W,   B,   J,   F,   U,   P,   SCLN,LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    BSPC,A,   S,   H,   T,   G,   Y,   N,   E,   O,   I,   QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   M,   C,   V,   K,   L,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 5: Mouse keys
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |MwL|MwU|McU|WwU|WwR|MwL|MwD|MwU|MwR|   |   |   |    \|
     * |-----------------------------------------------------------|
     * |CapsLo|   |McL|McD|McR|   |McL|McD|McU|McR|Fn0|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |VoD|VoU|Mut|Mb2|Mb3|Mb2|Mb1|VoD|VoU|Mut|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Mb1           |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     * Mc = mouse cursor, Mw = mouse wheel, Mb = mouse button
     * Vo = Volume, Mut = Mute
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F8,  F10, F11, F12, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, WH_L,WH_D,MS_U,WH_U,WH_R,WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,  BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,NO,  MS_L,MS_D,MS_R,NO,  MS_L,MS_D,MS_U,MS_R,FN0, NO,       ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,VOLD,VOLU,MUTE,BTN2,BTN3,BTN2,BTN1,VOLD,VOLU,MUTE,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          BTN1,                    RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 6: Cursor keys
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgU| Up|PgU|End|Hom|PgD|PgU|End|   |   |   |    \|
     * |-----------------------------------------------------------|
     * |CapsLo|   |Lef|Dow|Rig|   |Lef|Dow| Up|Rig|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgU|End|Fn1|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     */
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

uint8_t keymap_fn_layer(uint8_t index)
{
    return pgm_read_byte(&fn_layer[index]);
}

uint8_t keymap_fn_keycode(uint8_t index)
{
    return pgm_read_byte(&fn_keycode[index]);
}
