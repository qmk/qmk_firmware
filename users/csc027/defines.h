/*
Copyright 2020 Constantine Chen @csc027

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

#pragma once
#include "csc027.h"

#define MC_RSFE RSFT_T(KC_ENT)  // Right Shift on hold, Enter on tap
#define MC_LSEC LSFT_T(KC_ESC)  // Left Shift on hold, Escape on tap

#define ________________ KC_TRNS

/* QWERTY Layer
 *
 *  The basic layer of this keymap is a QWERTY layer.
 *
 *  - Modifier keys more closely resemble a standard keyboard's layout.
 *  - There is a "Nxt L" function that cycles through the QWERTY and
 *    game layers.  This has been implemented by hard coding the jump to the
 *    next layer in each of the layers using the TO() macro.  Currently, the
 *    "Nxt L" function skips over the momentary layers (i.e., Mouse, Lower,
 *    Raise, Windows Terminal, and Convenience layers).
 *  - There is a "Rst L" function that resets the current layer to the
 *    QWERTY layer.
 *  - The "Wt" momentary function goes to the macro layer which has Windows
 *    Terminal shortcuts.
 *  - The Right Shift key also doubles as an Enter key if it is tapped rather
 *    than held.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * | Tab |  Q  |  W  |  E  |  R  |  T  |  |  Y  |  U  |  I  |  O  |  P  |BkSpc|
 * |-----------------------------------|  |-----------------------------------|
 * | Esc |  A  |  S  |  D  |  F  |  G  |  |  H  |  J  |  K  |  L  |  ;  |  '  |
 * |-----------------------------------|  |-----------------------------------|
 * |Shift|  Z  |  X  |  C  |  V  |  B  |  |  N  |  M  |  ,  |  .  |  /  |Sf/En|
 * |-----------------------------------|  |-----------------------------------|
 * |Cntrl|Super| Alt |Convc|Lower|Space|  |Space|Raise|  \  |  Wt |Nxt L|Rst L|
 * `-----------------------------------'  `-----------------------------------'
 */

#define _____________________QWERTY_L1_____________________  KC_TAB,   KC_Q,     KC_W,     KC_E,      KC_R,     KC_T
#define _____________________QWERTY_L2_____________________  KC_ESC,   KC_A,     KC_S,     KC_D,      KC_F,     KC_G
#define _____________________QWERTY_L3_____________________  KC_LSFT,  KC_Z,     KC_X,     KC_C,      KC_V,     KC_B
#define _____________________QWERTY_L4_____________________  KC_LCTL,  KC_LGUI,  KC_LALT,  MO(_CN),   LOWER,    KC_SPC

#define _____________________QWERTY_R1_____________________  KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_BSPC
#define _____________________QWERTY_R2_____________________  KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT
#define _____________________QWERTY_R3_____________________  KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,  MC_RSFE
#define _____________________QWERTY_R4_____________________  KC_SPC,   RAISE,    KC_BSLS,  MO(_WT),   TO(_GG),  XXXXXXX

/* Raise Layer
 *
 *  The Raise layer accommodates the Home, End, Page Up, and Page Down keys
 *  in what would be the Vim arrow keys positions.  This is done as opposed
 *  to using C-D, C-U, 0, $, and ^, because it would require a separate layer.
 *
 *  - The top row has the shifted versions of the number row, rather than the
 *    numbers themselves.  This is a change to have a mnemonic where shifted
 *    elements are on the Raise layer.  This also makes it easy to use some of
 *    Vim style movement controls (e.g. $, %), but makes it harder for others
 *    (e.g. ^, (, )). Consider swapping the number row with the shifted number
 *    row if you do not care about the mnemonic.
 *  - The Left Brace, Right Brace, Underscore, and Plus keys have been moved
 *    from the right side to the left side.  This will take some getting used
 *    to, as these keys are normally on the right side of the keyboard.  An
 *    alternative would be to keep the keys on the right hand side just under
 *    the Parentheses.  This would prevent the use of Vim arrow keys however.
 *  - The F keys have been laid across the bottom in the Raise layer, rather
 *    than the Lower layer to allow easy access to the Alt-F4 chord for
 *    Windows.  When the F keys were put in the Lower layer, it made it hard
 *    to use this chord, as the Lower key, the Alt key, and the F4 key were
 *    all right next to each other.
 *  - A Delete key has been added in this layer to allow easy access to the
 *    Control-Alt-Delete login chord for Windows.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |  ~  |  !  |  @  |  #  |  $  |  %  |  |  ^  |  &  |  *  |  (  |  )  | Del |
 * |-----------------------------------|  |-----------------------------------|
 * |     |  _  |  +  |  {  |  }  | Caps|  | Home| PgDn| PgUp| End |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |  F1 |  F2 |  F3 |  F4 |  F5 |  |  F6 |  F7 |  F8 |  F9 | F10 |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ______________________RAISE_L1_____________________  KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC
#define ______________________RAISE_L2_____________________  _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_CAPS
#define ______________________RAISE_L3_____________________  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5
#define ______________________RAISE_L4_____________________  _______,  _______,  _______,  _______,  _______,  _______

#define ______________________RAISE_R1_____________________  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_DELT
#define ______________________RAISE_R2_____________________  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   XXXXXXX,  XXXXXXX
#define ______________________RAISE_R3_____________________  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______
#define ______________________RAISE_R4_____________________  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX

/* Lower Layer
 *
 *  The lower layout scheme accommodates the Vim style arrow keys.
 *
 *  - The arrow keys are in the normal Vim positions.
 *  - The Left Square Bracket, Right Square Bracket, Minus, and Equal keys
 *    have been moved from the right side to the left side.  This will take
 *    some getting used to, as it is on the left rather than the right.
 *  - A Delete key has been added in this layer to allow easy access to the
 *    Control-Alt-Delete login chord for Windows.
 *  - The remaining F keys are in this layer.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  |  6  |  7  |  8  |  9  |  0  | Del |
 * |-----------------------------------|  |-----------------------------------|
 * |     |  -  |  =  |  [  |  ]  |     |  | Left| Down|  Up |Right|     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     | F11 | F12 |     |     |     |  |     |     |     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ______________________LOWER_L1_____________________  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5
#define ______________________LOWER_L2_____________________  _______,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  XXXXXXX
#define ______________________LOWER_L3_____________________  _______,  KC_F11,   KC_F12,   XXXXXXX,  XXXXXXX,  XXXXXXX
#define ______________________LOWER_L4_____________________  _______,  _______,  _______,  _______,  _______,  _______

#define ______________________LOWER_R1_____________________  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DELT
#define ______________________LOWER_R2_____________________  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  XXXXXXX
#define ______________________LOWER_R3_____________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______
#define ______________________LOWER_R4_____________________  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX

/* Mouse Layer
 *
 *  The mouse layer adds keys to use the keyboard like a mouse.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |Ms-Lc|Ms-Rc|     |  | Ms-L| Ms-D| Ms-U| Ms-R|     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ______________________MOUSE_L1_____________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
#define ______________________MOUSE_L2_____________________  _______,  XXXXXXX,  XXXXXXX,  KC_BTN1,  KC_BTN2,  XXXXXXX
#define ______________________MOUSE_L3_____________________  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
#define ______________________MOUSE_L4_____________________  _______,  _______,  _______,  _______,  _______,  _______

#define ______________________MOUSE_R1_____________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
#define ______________________MOUSE_R2_____________________  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  XXXXXXX,  XXXXXXX
#define ______________________MOUSE_R3_____________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______
#define ______________________MOUSE_R4_____________________  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX

/* Convenience Layer
 *
 *  The Convenience layer adds miscellaneous chords to the keyboard.
 *
 *  - The Number Lock key is physically in the same spot as the Caps Lock key
 *    in the raise layer.
 *  - There is also a Backspace Key for convenience.
 *  - There is a convenience macro to type the Control-Alt-Delete login chord for Windows.
 *  - There is a convenience macro to switch context from the Remote Desktop to the local
 *    machine in Windows.
 *  - There are convenience macros to switch between virtual desktops in Windows.
 *  - There are convenience macros to create and delete virtual desktops in Windows.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |     |     |Insrt|ScrLk|PrtSc|     |  |     |     |     |     |     |BkSpc|
 * |-----------------------------------|  |-----------------------------------|
 * |     |     | App | LCAD|MRDCC|NmLck|  |MVTDL|MVTDC|MVTDN|MVTDR|     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ___________________CONVENIENCE_L1__________________  XXXXXXX,  XXXXXXX,  KC_INS,   KC_SLCK,  KC_PSCR,  XXXXXXX
#define ___________________CONVENIENCE_L2__________________  _______,  XXXXXXX,  KC_APP,   MC_lcad,  MC_rdcc,  KC_NLCK
#define ___________________CONVENIENCE_L3__________________  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
#define ___________________CONVENIENCE_L4__________________  _______,  _______,  _______,  _______,  _______,  _______

#define ___________________CONVENIENCE_R1__________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_BSPC
#define ___________________CONVENIENCE_R2__________________  MC_vtdl,  MC_vtdc,  MC_vtdn,  MC_vtdr,  XXXXXXX,  XXXXXXX
#define ___________________CONVENIENCE_R3__________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______
#define ___________________CONVENIENCE_R4__________________  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX

/* Windows Terminal Layer
 *
 *  Contains shortcuts for pane and tab usage for Windows Terminal
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |     |Tab 1|Tab 2|Tab 3|Tab 4|Tab 5|  |Tab 6|Tab 7|Tab 8|Tab 9|TrCnP|BkSpc|
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |Split|Close|     |     |  |FcsLf|FcsDn|FcsUp|FcsRt|     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |VSplt|     |  |     |     |     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ________________WINDOWS_TERMINAL_L1________________  XXXXXXX,  MC_trt1,  MC_trt2,  MC_trt3,  MC_trt4,  MC_trt5
#define ________________WINDOWS_TERMINAL_L2________________  _______,  XXXXXXX,  MC_trps,  MC_trpc,  XXXXXXX,  MC_trtn
#define ________________WINDOWS_TERMINAL_L3________________  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MC_trpv,  XXXXXXX
#define ________________WINDOWS_TERMINAL_L4________________  _______,  _______,  _______,  _______,  _______,  _______

#define ________________WINDOWS_TERMINAL_R1________________  MC_trt6,  MC_trt7,  MC_trt8,  MC_trt9,  MC_trcp,  KC_BSPC
#define ________________WINDOWS_TERMINAL_R2________________  MC_trpl,  MC_trpd,  MC_trpu,  MC_trpr,  XXXXXXX,  XXXXXXX
#define ________________WINDOWS_TERMINAL_R3________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______
#define ________________WINDOWS_TERMINAL_R4________________  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX

/* General Game Layer
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  |  6  |  7  |  8  |  9  |  0  |BkSpc|
 * |-----------------------------------|  |-----------------------------------|
 * | Tab |  Q  |  W  |  E  |  R  |  T  |  |  Y  |  U  |  I  |  O  |  P  |  \  |
 * |-----------------------------------|  |-----------------------------------|
 * |Sf/Ec|  A  |  S  |  D  |  F  |  G  |  |  H  |  J  |  K  |  L  |  ;  |Enter|
 * |-----------------------------------|  |-----------------------------------|
 * | Ctl |  Z  | Alt |  X  |  C  |Space|  |Space|  M  |  B  |  .  |Nxt L|Rst L|
 * `-----------------------------------'  `-----------------------------------'
 */

#define ________________General_Game_4x12_L1_______________  KC_GRV,   KC_1,  KC_2,     KC_3,    KC_4,     KC_5
#define ________________General_Game_4x12_L2_______________  KC_TAB,   KC_Q,  KC_W,     KC_E,    KC_R,     KC_T
#define ________________General_Game_4x12_L3_______________  MC_LSEC,  KC_A,  KC_S,     KC_D,    KC_F,     KC_G
#define ________________General_Game_4x12_L4_______________  KC_LCTL,  KC_Z,  KC_LALT,  KC_X,    KC_C,     KC_SPC

#define ________________General_Game_4x12_R1_______________  KC_6,     KC_7,  KC_8,     KC_9,    KC_0,     KC_BSPC
#define ________________General_Game_4x12_R2_______________  KC_Y,     KC_U,  KC_I,     KC_O,    KC_P,     KC_BSLS
#define ________________General_Game_4x12_R3_______________  KC_H,     KC_J,  KC_K,     KC_L,    KC_SCLN,  KC_ENT
#define ________________General_Game_4x12_R4_______________  KC_SPC,   KC_M,  KC_B,     KC_DOT,  TO(_CS),  TO(_QW)

/* CS:GO Layer
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |     |  1  |  2  |  3  |  4  |  5  |  |  6  |  7  |  8  |  9  |  0  |BkSpc|
 * |-----------------------------------|  |-----------------------------------|
 * | Tab |  Q  |  W  |  E  |  R  |  T  |  |  Y  |  4  |  5  |  6  |     |NmLck|
 * |-----------------------------------|  |-----------------------------------|
 * |Shift|  A  |  S  |  D  |  F  |  G  |  |  H  |  1  |  2  |  3  |Enter| Esc |
 * |-----------------------------------|  |-----------------------------------|
 * | Ctl |  Z  | Alt |  X  |  B  |Space|  |Space|  0  |  0  |  .  |Nxt L|Rst L|
 * `-----------------------------------'  `-----------------------------------'
 */

#define ___________________CSGO_4x12_L1____________________  XXXXXXX, KC_1,   KC_2,     KC_3,     KC_4,     KC_5
#define ___________________CSGO_4x12_L2____________________  KC_TAB,  KC_Q,   KC_W,     KC_E,     KC_R,     KC_T
#define ___________________CSGO_4x12_L3____________________  KC_LSFT, KC_A,   KC_S,     KC_D,     KC_F,     KC_G
#define ___________________CSGO_4x12_L4____________________  KC_LCTL, KC_Z,   KC_LALT,  KC_X,     KC_B,     KC_SPC

#define ___________________CSGO_4x12_R1____________________  KC_6,    KC_P7,  KC_P8,    KC_P9,    KC_0,     KC_BSPC
#define ___________________CSGO_4x12_R2____________________  KC_Y,    KC_P4,  KC_P5,    KC_P6,    XXXXXXX,  KC_NLCK
#define ___________________CSGO_4x12_R3____________________  KC_H,    KC_P1,  KC_P2,    KC_P3,    KC_PENT,  KC_ESC
#define ___________________CSGO_4x12_R4____________________  KC_SPC,  KC_P0,  KC_P0,    KC_PDOT,  TO(_QW),  TO(_QW)

/* Convenience macros
 *
 * These are accelerator macros for simplifying declaration of PROGMEM strings
 */

// Declare variable name
#define CUSTOM_VAR(VAR)                      mc_##VAR

// Declare PROGMEM string using the variable name
#define CUSTOM_DEF(VAR)                      const char CUSTOM_VAR(VAR)[] PROGMEM =

// Declare enum name
#define CUSTOM_ENUM(VAR)                     MC_##VAR

#define CUSTOM_MACRO_STRING(X)               X

#define COMMA_DELIM(...)                     ,
#define SEMI_DELIM(...)                      ;

#define DROP(...)

/* Keycode synchronization macros
 *
 * These macros help synchronize the keycodes between the string declaration, string pointer declaration, and enum order.
 */

#define CUSTOM_MACROS(CUSTOM_NAME, CUSTOM_STRING, CUSTOM_DELIM) \
    CUSTOM_NAME(rdcc)       CUSTOM_STRING(SS_LCTL(SS_LALT(SS_TAP(X_HOME))))   CUSTOM_DELIM() \
    CUSTOM_NAME(lcad)       CUSTOM_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DELETE)))) CUSTOM_DELIM() \
    CUSTOM_NAME(trcp)       CUSTOM_STRING(SS_LCTL(SS_LSFT("p")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trps)       CUSTOM_STRING(SS_LALT(SS_LSFT("-")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trpv)       CUSTOM_STRING(SS_LALT(SS_LSFT("+")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trpc)       CUSTOM_STRING(SS_LCTL(SS_LSFT("w")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trpl)       CUSTOM_STRING(SS_LALT(SS_TAP(X_LEFT)))            CUSTOM_DELIM() \
    CUSTOM_NAME(trpd)       CUSTOM_STRING(SS_LALT(SS_TAP(X_DOWN)))            CUSTOM_DELIM() \
    CUSTOM_NAME(trpu)       CUSTOM_STRING(SS_LALT(SS_TAP(X_UP)))              CUSTOM_DELIM() \
    CUSTOM_NAME(trpr)       CUSTOM_STRING(SS_LALT(SS_TAP(X_RIGHT)))           CUSTOM_DELIM() \
    CUSTOM_NAME(trtn)       CUSTOM_STRING(SS_LCTL(SS_LSFT("t")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt1)       CUSTOM_STRING(SS_LCTL(SS_LALT("1")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt2)       CUSTOM_STRING(SS_LCTL(SS_LALT("2")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt3)       CUSTOM_STRING(SS_LCTL(SS_LALT("3")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt4)       CUSTOM_STRING(SS_LCTL(SS_LALT("4")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt5)       CUSTOM_STRING(SS_LCTL(SS_LALT("5")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt6)       CUSTOM_STRING(SS_LCTL(SS_LALT("6")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt7)       CUSTOM_STRING(SS_LCTL(SS_LALT("7")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt8)       CUSTOM_STRING(SS_LCTL(SS_LALT("8")))              CUSTOM_DELIM() \
    CUSTOM_NAME(trt9)       CUSTOM_STRING(SS_LCTL(SS_LALT("9")))              CUSTOM_DELIM() \
    CUSTOM_NAME(vtdl)       CUSTOM_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_LEFT))))   CUSTOM_DELIM() \
    CUSTOM_NAME(vtdc)       CUSTOM_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_F4))))     CUSTOM_DELIM() \
    CUSTOM_NAME(vtdn)       CUSTOM_STRING(SS_LCTL(SS_LGUI("d")))              CUSTOM_DELIM() \
    CUSTOM_NAME(vtdr)       CUSTOM_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_RIGHT))))
