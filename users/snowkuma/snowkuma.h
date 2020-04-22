/* Copyright 2019 @ninjonas
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
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "process_records.h"

#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif
#if defined(KEYBOARD_lily58_rev1) & defined(PROTOCOL_LUFA)
  #include "lufa.h"
  #include "split_util.h"
#endif

enum layers {
  _COLEMAK = 0,
  _NAV,
  _SYMBOL,
  _NUMBER,
  _ARRANGE,
  _MOUSE,
  _THUMB,
  _FUNCTION
};

// Shortcut Keys
#define K_LOCK LGUI(LCTL(KC_Q)) // Locks screen on MacOS
#define K_CSCN LGUI(LCTL(LSFT(KC_4))) // Copy a portion of the screen to the clipboard
#define K_CPRF LGUI(LSFT(KC_M)) //   + Shift + M. Used for switching Google Chrome profiles
#define K_MDSH LSFT(LALT(KC_MINS))
#define K_LAPP SGUI(KC_TAB) //  + Shift + Tab
#define K_RAPP LGUI(KC_TAB) //  + Tab

// Layer Keys
#define SPC_NAV LT(_NAV, KC_SPC)
#define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define DEL_SYM LT(_SYMBOL, KC_DEL)
#define ESC_NUM LT(_NUMBER, KC_ESC)
#define TAB_SFT SFT_T(KC_TAB)
#define MIN_ARR LT(_ARRANGE, KC_MINS)
#define ENT_THU LT(_THUMB, KC_ENT)

// magnet keycodes
#define M_LEFT LCA(KC_LEFT)
#define M_TOP LCA(KC_UP)
#define M_BOTT LCA(KC_DOWN)
#define M_RGHT LCA(KC_RGHT)

#define M_TOPL LCA(KC_U)
#define M_TOPR LCA(KC_I)
#define M_BOTL LCA(KC_J)
#define M_BOTR LCA(KC_K)

#define M_L13 LCA(KC_D)
#define M_L23 LCA(KC_E)
#define M_C13 LCA(KC_F)
#define M_R23 LCA(KC_T)
#define M_R13 LCA(KC_G)

#define M_1_6 LCA(KC_1)
#define M_2_6 LCA(KC_2)
#define M_3_6 LCA(KC_3)
#define M_4_6 LCA(KC_4)
#define M_5_6 LCA(KC_5)
#define M_6_6 LCA(KC_6)
#define M_L_56 LCA(KC_COMM)
#define M_R_56 LCA(KC_DOT)

#define M_NEXT LCAG(KC_RGHT)
#define M_PREV LCAG(KC_LEFT)

#define M_MAX LCA(KC_ENT)
#define M_CEN LCA(KC_C)
#define M_REST LCA(KC_BSPC)

// Modifier tapholds
#define T_SFT SFT_T(KC_T)
#define N_SFT SFT_T(KC_N)
#define Q_CTL CTL_T(KC_Q)
#define W_ALT ALT_T(KC_W)
#define F_GUI GUI_T(KC_F)
#define U_GUI GUI_T(KC_U)
#define Y_ALT ALT_T(KC_Y)
#define SCL_CTL CTL_T(KC_SCLN)

// Special characters
#define GBP A(KC_3)
#define EURO A(S(KC_2))

// Shortcuts
#define INPUT_L LCAG(KC_SPC)
#define TXT_PLS G(KC_PLUS)
#define TXT_MIN G(KC_MINS)
#define SC_CAPF G(S(KC_3))  // Capture the full screen to file
#define SC_CAPP G(S(KC_4))  // Capture portion of screen to file
#define CUT G(KC_X)
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define NXT_WIN G(KC_GRV)
#define EMOJI G(C(KC_SPC))  // brings up the emoji picker in OSX
#define VOLUP KC__VOLUP     // shorter naming for layout tidiness
#define VOLDOWN KC__VOLDOWN
#define MUTE KC_MUTE

// Layout blocks

/* COLEMAK
                     LEFT                                                    RIGHT
   ,---------------------------------------.               ,---------------------------------------.
L1 |   Q   |   Q   |   F   |   P   |   G   |           R1  |   J   |   L   |   U   |   Y   |   ;   |
   |  Ctrl |  Alt  |  GUI  |       |       |               |       |       |  Ctrl |  Alt  |  GUI  |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 |   A   |   R   |   S   |   T   |   D   |           R2  |   H   |   N   |   E   |   I   |   O   |
   |       |       |       | Shift |       |               |       | Shift |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L3 |   Z   |   X   |   C   |   V   |   B   |           R3  |   K   |   M   |   ,   |   .   |   '   |
   |       |       |       |       |       |               |       |       |       |       |       |
   '-------+-------+-------+-------+-------'               '-------+-------+-------+-------+-------'
*/

#define _________________COLEMAK_L1________________        Q_CTL,   W_ALT,   F_GUI,   KC_P,    KC_G
#define _________________COLEMAK_L2________________        KC_A,    KC_R,    KC_S,    T_SFT,   KC_D
#define _________________COLEMAK_L3________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________        KC_J,    KC_L,    U_GUI,   Y_ALT,   SCL_CTL
#define _________________COLEMAK_R2________________        KC_H,    N_SFT,   KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________        KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT

/* NAV
                     LEFT                                                    RIGHT
   ,---------------------------------------.               ,---------------------------------------.
L1 |  Ctrl |  Alt  |  GUI  |       |       |            R1 |       | Home  |   Up  |  End  | Page  |
   |       |       |       |       |       |               |       |       |       |       |  Up   |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 | Next  |       |       | Shift |       |            R2 |       | Left  |  Down | Right | Page  |
   | Window|       |       |       |       |               |       |       |       |       | Down  |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L3 |       |       |       |       |       |            R3 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   '-------+-------+-------+-------+-------'               '-------+-------+-------+-------+-------'
*/
#define _________________NAV_L1____________________        KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX
#define _________________NAV_L2____________________        NXT_WIN, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX
#define _________________NAV_L3____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _________________NAV_R1____________________        XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP
#define _________________NAV_R2____________________        XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#define _________________NAV_R3____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

/* SYMBOL
                     LEFT                                                    RIGHT
   ,---------------------------------------.               ,---------------------------------------.
L1 |   !   |   @   |   *   |   &   |   |   |            R1 |       |   [   |   ^   |   ]   |   :   |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 |   ~   |   <   |   %   |   %   |   £   |            R2 |   ?   |   (   |   $   |   )   |   /   |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L3 |   `   |   +   |   -   |   =   |   €   |            R3 |   |   |   {   |   #   |   }   |   \   |
   |       |       |       |       |       |               |       |       |       |       |       |
   '-------+-------+-------+-------+-------'               '-------+-------+-------+-------+-------'
*/

#define _________________SYM_L1____________________        KC_EXLM, KC_AT,   KC_ASTR, KC_AMPR, KC_PIPE
#define _________________SYM_L2____________________        KC_TILD, KC_LT,   KC_PERC, KC_GT,   GBP
#define _________________SYM_L3____________________        KC_GRV,  KC_PLUS, KC_MINS, KC_EQL,  EURO

#define _________________SYM_R1____________________        XXXXXXX, KC_LBRC, KC_CIRC, KC_RBRC, KC_COLN
#define _________________SYM_R2____________________        KC_QUES, KC_LPRN, KC_DLR,  KC_RPRN, KC_SLSH
#define _________________SYM_R3____________________        KC_PIPE, KC_LCBR, KC_HASH, KC_RCBR, KC_BSLS


/* NUMBER
                     LEFT                                                    RIGHT
   ,---------------------------------------.               ,---------------------------------------.
L1 |       |       |  CUT  |       |       |            R1 |   /   |   7   |   8   |   9   |   *   |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 |   :   |   #   |  COPY | PASTE |   £   |            R2 |   .   |   4   |   5   |   6   |   -   |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L3 |   `   |   +   |   -   |   =   |   €   |            R3 |   ,   |   1   |   2   |   3   |   +   |
   |       |       |       |       |       |               |       |       |       |       |       |
   '-------+-------+-------+-------+-------'               |-------+-------+-------+-------+-------'
                                                        R4 |   \   |   0   |   =   |                
                                                           |       |       |       |                
                                                           '-------+-------+-------'
*/

#define _________________NUM_L1____________________        XXXXXXX, XXXXXXX, CUT,     XXXXXXX, XXXXXXX
#define _________________NUM_L2____________________        KC_COLN, KC_HASH, COPY,    PASTE,   GBP
#define _________________NUM_L3____________________        KC_COMM, KC_PLUS, KC_MINS, KC_EQL,  EURO

#define _________________NUM_R1____________________        KC_SLSH, KC_7,    KC_8,    KC_9,    KC_ASTR
#define _________________NUM_R2____________________        KC_DOT,  KC_4,    KC_5,    KC_6,    KC_MINS
#define _________________NUM_R3____________________        KC_COMM, KC_1,    KC_2,    KC_3,    KC_PLUS
#define ________NUM_R4___________                          KC_BSLS, KC_0,    KC_EQL


/* ARRANGE
                     LEFT                                                    RIGHT
   ,---------------------------------------.               ,---------------------------------------.
L1 |       |       |       |       |       |            R1 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 |       |       |       |       |       |            R2 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L3 |       |       |       |       |       |            R3 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   '-------+-------+-------+-------+-------'               '-------+-------+-------+-------+-------'
*/

#define _________________ARR_L1____________________        M_1_6,   M_2_6,   M_MAX,   M_5_6,   M_6_6
#define _________________ARR_L2____________________        M_L13,   M_L23,   M_C13,   M_R23,   M_R13
#define _________________ARR_L3____________________        M_L_56,  M_3_6,   M_REST,  M_4_6,   M_R_56

#define _________________ARR_R1____________________        XXXXXXX, M_TOPL,  M_TOP,   M_TOPR,  XXXXXXX
#define _________________ARR_R2____________________        M_PREV,  M_LEFT,  M_BOTT,  M_RGHT,  M_NEXT
#define _________________ARR_R3____________________        XXXXXXX, M_BOTL,  M_CEN,   M_BOTR,  XXXXXXX

/* MOUSE
                     LEFT                                                    RIGHT
   ,---------------------------------------.               ,---------------------------------------.
L1 |       |       |       |       |       |            R1 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 |       |       |       |       |       |            R2 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L3 |       |       |       |       |       |            R3 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   '-------+-------+-------+-------+-------'               '-------+-------+-------+-------+-------'
*/


#define _________________MOU_L1____________________        KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX
#define _________________MOU_L2____________________        KC_BTN3, KC_BTN2, KC_BTN1, KC_LSFT, XXXXXXX
#define _________________MOU_L3____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _________________MOU_R1____________________        XXXXXXX, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U
#define _________________MOU_R2____________________        XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D
#define _________________MOU_R3____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX


/* THUMB
                     LEFT                                                    RIGHT
   ,---------------------------------------.               ,---------------------------------------.
L1 |       |       |       |       |       |            R1 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 |       |       |       |       |       |            R2 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L3 |       |       |       |       |       |            R3 |       |       |       |       |       |
   |       |       |       |       |       |               |       |       |       |       |       |
   '-------+-------+-------+-------+-------'               '-------+-------+-------+-------+-------'
*/

#define _________________THU_L1____________________        XXXXXXX, M_XXX4,  M_XXX3,  XXXXXXX, M_XXX2
#define _________________THU_L2____________________        XXXXXXX, XXXXXXX, M_SPOTIFY, M_TYPE,  M_XXX1
#define _________________THU_L3____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_BRAVE

#define _________________THU_R1____________________        XXXXXXX, XXXXXXX, INPUT_L, XXXXXXX, TXT_PLS
#define _________________THU_R2____________________        XXXXXXX, KC_CAPS, EMOJI,   M_ITERM, TXT_MIN
#define _________________THU_R3____________________        XXXXXXX, M_MONEY, XXXXXXX, XXXXXXX, XXXXXXX

/* FUNCTION
                     LEFT                                                    RIGHT
   ,---------------------------------------.               ,---------------------------------------.
L1 | Ctrl  | Alt   | GUI   |       |       |            R1 |       |  F7   |  F8   |  F9   | F12   |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 |       |       |       | Shift |       |            R2 |       |  F4   |  F5   |  F6   | F11   |
   |       |       |       |       |       |               |       |       |       |       |       |
   |-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------|
L2 |       |       |       |       |       |            R2 |       |  F1   |  F2   |  F3   | F10   |
   |       |       |       |       |       |               |       |       |       |       |       |
   '-------+-------+-------+-------+-------'               '-------+-------+-------+-------+-------'
*/

#define _________________FUN_L1____________________        KC_LCTL, KC_LALT, KC_LGUI,  XXXXXXX, XXXXXXX
#define _________________FUN_L2____________________        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX
#define _________________FUN_L3____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _________________FUN_R1____________________        XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12
#define _________________FUN_R2____________________        XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11
#define _________________FUN_R3____________________        XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10

/* MOD THUMB CLUSTER
                 LEFT                              RIGHT
       ,-----------------------.         ,-----------------------.
Tap    |  ESC  | BSpc  | Tab   |         |   -   | Space | Enter |
Hold   |  NUM  | Symbol| Shift |         |Arrange|  NAV  | Thumb |
       '-------+-------+-------'         '-------+-------+-------'
*/

#define ________MOD_LEFT_________        ESC_NUM, BSP_SYM, TAB_SFT
#define ________MOD_RIGHT________        MIN_ARR, SPC_NAV, ENT_THU  


// Layout wrappers
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_planck_wrapper(...) LAYOUT(__VA_ARGS__)