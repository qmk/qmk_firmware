/* Copyright 2021 Dave Vandyke <kzar@kzar.co.uk>,
 *   Based upon Xyverz's Kinesis keymap Copyright 2017-2020.
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

#include QMK_KEYBOARD_H
#include "version.h"
#include "my_keycodes.h"
#include "my_layers.h"
#include "features/caps_word.h"
#include "features/num_word.h"
#include "features/select_word.h"


// For more readable LED control code
#define LED_KEYPAD E26

//Aliases for longer keycodes
#define QWERTY TO(_QWERTY)


// Initialize variable holding the binary representation of active modifiers.
uint8_t mod_state;

// Super cmd↯TAB initializations
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;


// START TAP DANCE CODE
// Tap Dance Declarations
enum {
  LBCB = 0,
  RBCB,
  PLEQ,
  UNMN,
//   APQU,
//   SMCL,
  CMAG,
  SPOT,
  PDAG,
  NVUD,
  WIND,
  ISPT,
//   SLQU,
  GVES,
  SLSH,
  LPINKY,
  RPINKY,
};



// Define a type for as many tap dance states as needed
typedef enum {
    TD_NONE,
    UNKNOWN,
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
} td_state_t;

// Structure to define input into full tap dance
typedef struct {
    uint16_t kc1;
    uint16_t kc2;
    uint16_t kc3;
    uint16_t kc4;
    uint16_t kc5;
    uint16_t kc6;
} qk_tap_dance_full_t;

// Functions and structs associated with all full tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

/*
Functions associated with specific advanced tap dances
void full_td_finished(qk_tap_dance_state_t *state, void *user_data);
void full_td_reset(qk_tap_dance_state_t *state, void *user_data);
#define FULL_TAP_DANCE(kc1, kc2, kc3, kc4, kc5, kc6) \
         { .fn = {NULL, full_td_finished, full_td_reset}, .user_data = (void *)&((qk_tap_dance_full_t){kc1, kc2, kc3, kc4, kc5, kc6}), }
*/

// void window_td_finished(qk_tap_dance_state_t *state, void *user_data);
// void window_td_reset(qk_tap_dance_state_t *state, void *user_data);
// void lpinky_td_finished(qk_tap_dance_state_t *state, void *user_data);
// void lpinky_td_reset(qk_tap_dance_state_t *state, void *user_data);
// void rpinky_td_finished(qk_tap_dance_state_t *state, void *user_data);
// void rpinky_td_reset(qk_tap_dance_state_t *state, void *user_data);
// void slsh_td_finished(qk_tap_dance_state_t *state, void *user_data);
// void slsh_td_reset(qk_tap_dance_state_t *state, void *user_data);



// Triple Tap Dance function definition for period key
void triple_tap_dance_period (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_DOT);
    } else if (state->count == 2) {
        tap_code16(KC_RABK);
    } else if (state->count == 3) {
        tap_code(KC_DOT);
        tap_code(KC_DOT);
        tap_code(KC_DOT);
    } else {
        reset_tap_dance(state);
    }
}

// Triple Tap Dance function definition for / and ? key
void triple_tap_dance_slash (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_SLSH);
    } else if (state->count == 2) {
        tap_code16(KC_SLSH);
        tap_code16(KC_SLSH);
    } else if (state->count == 3) {
        tap_code16(KC_QUES);
    } else {
        reset_tap_dance(state);
    }
}

// Triple Tap Dance function definition for Esc key
void triple_tap_dance_esc (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_ESC);
    } else if (state->count == 2) {
        tap_code16(KC_GRV);
    } else if (state->count == 3) {
        tap_code16(KC_TILD);
    } else {
        reset_tap_dance(state);
    }
}

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


// Hands swapped matrix, except the F key row is left as is.


/* QWERTY Layout (Default Layer)
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|ESC^ST|SWAPHD|  F2  |QWERTY|NUMSFT|FUNCTN|KEYPAD| NAV  |  F8  |                                     | CLEAR|MACROP|MACROR|MACROS| Mute | VolDn| VolUp|Keypad|  Fn  |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
| ESC^~#` |   1^!  |   2^@  |   3^#  |   4^$  |   5^%  |                                                     |   6^^  |  7^&   |  8^*   |  9^(   |   0^)  |  NAV    |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|   Tab   |    Q   |    W   |    E   |    R   |    T   |                                                     |    Y   |   U    |   I    |   O    |   P    |  Bksp   |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
| LPINKY  | A/LCTL | S/LOPT | D/LGUI | F/LSHF |    G   |                                                     |    H   | J/RSHF | K/RGUI | L/ROPT | :/RCTL |  RPINKY |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
| OS:SHFT |    Z   |    X   |    C   |    V   |    B   |                                                     |    N   |   M    |  ,|<   |  .|>   |  /^?   | OS:SHFT |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |   ***  |  ****  |  ***   |   _|-  |                                                                       |   Up   |  Down  |  Left  |  Right |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |SELWORD |CAPSWORD|                 | NUMWORD| LPINKY |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |  BkSp  |  Del   |  SPOT  |                 |WINDOWTD|  Enter |  Space |
	                                          | ^Del / |   /    |--------|                 |--------|    /   |    /   |
	                                          |  LGUI  |  LSHFT | APPNAV |                 |  OSMeh |  Keypad|  RGUI  |
	                                          `--------------------------'                 `--------------------------'
    Notes:
    / indicate: key-when-tapped/key-when-held
    | Triggered with Double Tap
    APPNAV opens application switcher for a renewable 1sec timeout, second press of key and all after presses right arrow. Add shift to press move left.
    ^ Triggered With Shift
    # Triggered With Command
    --- Command+` is mapped to "Move focus to next window" by MacOS
    * Tap and hold SwapHands for momentary swap, double tap for toggle on/off
    * Tap both shifts at same time for as long as their modtap length and CAPSWORD is activated
    * SELWORD selects current word, extends to next word on subsequent presses. Add shift and it selects line and adds next line with subsequent presses.
    *   Tap ESC or right arrow to deselect and move cursor to end of seelction. Or, tap left arrow to move cursor to beginning of selection.
    * LPINKY {1:One shot SYMBOLS layer, 1hold: NAV layer while holding, 2: NAV toggle, 2hold: Caps Word, 3: Numpad Toggle, 3hold: Control+C to end program running}
    * RPINKY: {1:One shot SYMBOLS layer, 1hold: ', 2: ", 2hold: Caps Word, 3: NUMSHIFT layer toggle, 3hold: ***}

    Wishes:
    * I might want ( moved to top layer
    * I want semicolon and colon switched using a magic key? or just switched.
    * Bottom for LH keys are now pointless - minus key could swap the shifted and unshifted values
    * SpaceCadet paranthesis are now silly becuase of home row mods. Turn into full tap dances or something?
    * Holding down tab could do something, same with holding down Backspace on RH
    * Space and Enter for LH?
    * Double hold on space should make Shift mod...
    * Top right NAV button is not well used
    * Should I add an OSMeh to LH?
    * Top Right Thumb can be customized more beyond a copy of LPINKY
    *     
    * LPINKY triple tap should bring up Left numpad
    * RPINKY Triple tap hold macro
    
    Usage work:
    * Work on using left thumb shift
    * Work on using home row mods
    * 
*/

[_QWERTY] = LAYOUT_pretty(
  ESC_STS, SH_TT,   KC_F2,   TO(_QWERTY),  TG(_NUMSHIFT),TG(_FUNCTION),TG(_KEYPAD),TG(_NAV),  KC_F8,  CLEAR, DM_PLY1, DM_REC1, DM_RSTP,KC_MUTE,KC_VOLD,KC_VOLU,TG(_KEYPAD), KC_APFN,
  TD(GVES), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TG(_NAV),
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                          KC_Y,    KC_U,    TD(ISPT),KC_O,    KC_P,    HYPR_T(KC_BSPC),
  TD(LPINKY),LCTL_T(KC_A),LOPT_T(KC_S),LGUI_T(KC_D),LSFT_T(KC_F),KC_G,                                          KC_H,RSFT_T(KC_J),RGUI_T(KC_K),ROPT_T(KC_L),RCTL_T(KC_COLN),TD(RPINKY),
  OSM(MOD_LSFT),LT(0,KC_Z),LT(0,KC_X),LT(0,KC_C),LT(0,KC_V),KC_B,                                            KC_N,    KC_M,    TD(CMAG),TD(PDAG),TD(SLSH), OSM(MOD_RSFT),
           _______, _______, _______,TD(UNMN),                                                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                                                  SELWORD, CAPWORD,                   NUMWORD, LT(_NAV, KC_BSLS),
                                                                TD(SPOT),                 TD(WIND),
                                LGUI_T(KC_BSPC), SFT_T(KC_DEL), APP_NAV,                   OSM(MOD_MEH), LT(_KEYPAD, KC_ENT), RGUI_T(KC_SPC)
),

/*
    Note: OSMeh is used for quick switching between apps. One shot Meh modifier is used
    to trigger "complex modifications" by Karabiner to switch to various applications
    using a successive alphanumeric key (first letter of application name,
    or second/third/... letter if first letter is taken) as follows:

,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         | QMK Web|        |Terminal| Chrome |Todoist |                                                     |SystPref|QuikNote|KrbnrEvt|Spotify |Photoshp|         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |PastePal| Safari | Drive  | Finder | Gmail  |                                                     |Spotlght|        |Desktop |LaunchPd|        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |  Zoom  |        |Calendar| VSCode |Bitwardn|                                                     | Notion |Messages|        |        |        |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
    Notes:
    * PastePal shortcut is configured in its own application
    * Desktop, Quick Note, Launchpad (also in Karabiner) shortcut is confifured in MacOS system preferences
    * KC_APFN is created through the Apple Fn patch: https://gist.github.com/fauxpark/010dcf5d6377c3a71ac98ce37414c6c4
*/

/*  Symbols layer:
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |    !   |    @   |    #   |    $   |    %   |                                                     |    ^   |    &   |    *   |    (   |    )   |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/


[_NUMSHIFT] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),


/* Symbols
    Mostly for coding, optimized currently for my use of Python
    Note: Best accessed through a oneshot layer key: LPINKY, RPINKY currently
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |   {    |        |                                                     |        |   }    |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |   #    |   (    |        |                                                     |        |   )    |        |        |    ;   |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |   [    |        |                                                     |        |   ]    |        |        |    \   |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |   |    |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |   +    |        |                 |        |   `    |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |   *    |                 |        |        |        |
	                                          |   =    |   -    |--------|                 |--------|   "    |   _    |
	                                          |        |        |TDSLSH  |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'

*/

[_SYMBOLS] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, KC_LCBR, _______,                                                       _______, KC_RCBR, _______, _______, _______, _______,
  _______, _______, _______, KC_HASH, KC_LPRN, _______,                                                       _______, KC_RPRN, _______, _______, KC_SCLN, _______,
  _______, _______, _______, _______, KC_LBRC, _______,                                                       _______, KC_RBRC, _______, _______, KC_BSLS, _______,
           _______, _______, _______, _______,                                                                         KC_PIPE, _______, _______, _______,
                                                        KC_PLUS, _______,                   _______, KC_GRV,
                                                                 KC_ASTR,                   _______,
                                               KC_EQL,  KC_MINS, TD(SLSH),                   _______, KC_DQUO, KC_UNDS
),

/*  VIM - Holding spot for future implementation

,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/

[_VIM] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),


/*
Navigation Layer
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
| Sleep|      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |   Up   |        |        |                                                     |        |        |   Up   |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |  Left  |  Down  |  Right |        |                                                     |        |  Left  |  Down  |  Right |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |WheelUp |        |MouseUp |        |        |                                                     |        |        | MouseUp|        | WheelUp|         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |WheelDn |MouseLft|MouseDn |MouseRgh|                                                                       |MouseLft| MouseDn|MouseRgh| WheelDn|
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          | Mouse  | Mouse  |        |                 |        | Mouse  | Mouse  |
	                                          | Button | Button |--------|                 |--------| Button | Button |
	                                          |   1    |   2    | QWERTY |                 | QWERTY |   2    |   1    |
	                                          `--------------------------'                 `--------------------------'
    Note:
    * QWERTY deactivates the layer and return to the main layout
*/

[_NAV] = LAYOUT_pretty(
  KC_SLEP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_UP,   _______, _______,                                                       _______, _______, KC_UP,   _______, _______, _______,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                                                       _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  _______, KC_WH_U, _______, KC_MS_U, _______, _______,                                                       _______, _______, KC_MS_U, _______, KC_WH_U, _______,
           KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R,                                                                         KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               KC_BTN1, KC_BTN2, QWERTY,                    QWERTY,  KC_BTN2, KC_BTN1
),
 
/*  Keypad Layer
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |        |        |        |        |        |                                                     |        | QWERTY |  KP =  |  KP /  |  KP *  |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
| KPSWAP  |        |        |        |        |        |                                                     |        |   7    |   8    |   9    |  KP -  |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |   4    |   5    |   6    |  KP +  |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |   0    |   1    |   2    |   3    |  KP .  |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/

[_KEYPAD] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KPSWAP,  _______, _______, _______, _______, _______,                                                       _______, QWERTY,  KC_PEQL, KC_PSLS, KC_PAST, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, KC_7,    KC_8,    KC_9,    KC_PMNS, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, KC_4,    KC_5,    KC_6,    KC_PPLS, _______,
  _______, _______, _______, _______, _______, _______,                                                       KC_0,    KC_1,    KC_2,    KC_3,    KC_PDOT, _______,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),
/*  LH Keypad
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |        | QWERTY |  KP =  |  KP /  |  KP *  |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
| KPSWAP  |        |   7    |   8    |   9    |  KP -  |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |   4    |   5    |   6    |  KP +  |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |    0   |   1    |   2    |   3    |  KP .  |                                                     |        |        |        |        |        |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/
[_LKEYPAD] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KPSWAP,  _______, QWERTY,  KC_PEQL, KC_PSLS, KC_PAST,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, KC_7,    KC_8,    KC_9,    KC_PMNS,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, KC_4,    KC_5,    KC_6,    KC_PPLS,                                                       _______, _______, _______, _______, _______, _______,
  _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_PDOT,                                                       _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),

/*  Function layer

,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |   F1   |   F2   |   F3   |   F4   |   F5   |                                                     |   F6   |   F7   |   F8   |   F9   |   F10  |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |  PgUp  |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |  PgDn  |  Mute  |  Vol-  |  Vol+  |  Home  |  End    |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |  Prev  |  Play  |  Next  |  Stop  |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 | QWERTY |        |        |
	                                          `--------------------------'                 `--------------------------'
*/
// [_FUNCTION] = LAYOUT_pretty(
//   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
//   _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
//   _______, _______, _______, _______, _______, _______,                                                       KC_PGUP, _______, _______, _______, _______, _______,
//   _______, _______, _______, _______, _______, _______,                                                       KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, KC_HOME, KC_END,
//            _______, _______, _______, _______,                                                                         KC_MPRV, KC_MPLY, KC_MNXT, MEH(KC_O),
//                                                         _______, _______,                   _______, _______,
//                                                                  _______,                   _______,
//                                                _______, _______, _______,                   QWERTY,  _______, _______
// ),

// };

 
/*  Function layer

,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |   F1   |   F2   |   F3   |   F4   |   F5   |                                                     |   F6   |   F7   |   F8   |   F9   |   F10  | QWERTY  |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/

[_FUNCTION] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  TO(_QWERTY),
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),

};

// END of Keymaps

/*
This is the Stapelberg matrix as published at
https://github.com/stapelberg/kinesis-firmware/blob/master/kb_kinesis/config.kspec
Along with the pins for each row and column
             PB0 PB1 PB2 PB3 PB4 PB5 PB6
             kx0 kx1 kx2 kx3 kx4 kx5 kx6
PD0 k0x Row: EQL TAB CAP LSH X2  --  --
PD1 k1x Row: 1   Q   A   Z   BQ  --  --
PD2 k2x Row: 2   W   S   X   INS END --
PD3 k3x Row: 3   E   D   C   LFT HOM BAK
PD4 k4x Row: 4   R   F   V   --  --  DEL
PD5 k5x Row: 5   T   G   B   RT  LAL LCT
PD6 k6x Row: 6   Y   H   N   UP  SPC PGD
PD7 k7x Row: 7   U   J   M   --  RET --
PC0 k8x Row: 8   I   K   COM DWN RCT PGU
PC1 k9x Row: 9   O   L   PER LBR --  RAL
PC2 kAx Row: 0   P   SEM SLA RBR --  --
PC3 kBx Row: MIN BSL APO RSH X1  --  --
PC4 kCx Row: ESC F3  F6  F9  F12 PAU --
PC5 kDx Row: F1  F4  F7  F10 PRT PRG --
PC6 kEx Row: F2  F5  F8  F11 SLK KEY --
*/


const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = { \
    {{0, 11},  {1, 11},  {2, 11},  {3, 11}}, \
    {{0, 10},  {1, 10},  {2, 10},  {3, 10},  {4, 10}}, \
    {{0, 9},   {1, 9},   {2, 9},   {3, 9},   {4, 9},  {6, 6}}, \
    {{0, 8},   {1, 8},   {2, 8},   {3, 8},   {4, 8},  {6, 8},  {5, 6}}, \
    {{0, 7},   {1, 7},   {2, 7},   {3, 7}, {5, 7}}, \
    {{0, 6},   {1, 6},   {2, 6},   {3, 6},   {4, 5},  {6, 9},  {5, 8}}, \
    {{0, 5},   {1, 5},   {2, 5},   {3, 5},   {4, 5},  {6, 3},  {5, 2}}, \
    {{0, 4},   {1, 4},   {2, 4},   {3, 4},  {6, 4}}, \
    {{0, 3},   {1, 3},   {2, 3},   {3, 3},   {4, 3},  {6, 5},  {5, 3}}, \
    {{0, 2},   {1, 2},   {2, 2},   {3, 2},   {4, 2},  {5, 5}}, \
    {{0, 1},   {1, 1},   {2, 1},   {3, 1},   {4, 1}}, \
    {{0, 0},   {1, 0},   {2, 0},   {3, 0}}, \
    {{0, 12},  {1, 12},  {2, 12},  {3, 12},  {4, 12},  {5, 12}}, \
    {{0, 13},  {1, 13},  {2, 13},  {3, 13},  {4, 13},  {5, 13}}, \
    {{0, 14},  {1, 14},  {2, 14},  {3, 14},  {4, 14},  {5, 14}}  \
};

// Matrix scan function constantly running => Similar to "do () while (keyboard is powered on)"
// void rgb_matrix_indicators_user(void) 
// {	
//     if (isRecording)
//     {
//         // timer_elapsed() is a built-in function in qmk => it calculates in ms the time elapsed with timer_read()
//         if (timer_elapsed(recording_timer) > 500) 
//         {
//             isRecordingLedOn = !isRecordingLedOn;
//             recording_timer = timer_read();
//         }
//         if (isRecordingLedOn)
//         {
//             writePin(LED_KEYPAD, 1);
//             writePin(LED_NUM_LOCK_PIN, 1);
//             writePin(LED_SCROLL_LOCK_PIN, 1);
//             writePin(LED_CAPS_LOCK_PIN, 1);
//         }
//     }
// }

bool isRecording = false;
bool isRecordingLedOn = false;
uint16_t recording_timer = 0;

// Listener function => Triggered when you start recording a macro.
void dynamic_macro_record_start_user(void) 
{
    isRecording = true;
    isRecordingLedOn = true;
    // timer_read() is a built-in function in qmk. => It read the current time
    recording_timer = timer_read();
}

// Listener function => Triggered when the macro recording is stopped.
void dynamic_macro_record_end_user(int8_t direction) 
{
    isRecording = false;
    isRecordingLedOn = false;
    layer_on(0); // Dummy call to get layer_state_set_user to update
}

// Turn on all LEDs to indicate CAPSWORD is active
void caps_word_set_user(bool active) {
    if (active) {
        // Do something when Caps Word activates.
        writePin(LED_KEYPAD, 0);
        writePin(LED_NUM_LOCK_PIN, 0);
        writePin(LED_SCROLL_LOCK_PIN, 0);
        writePin(LED_CAPS_LOCK_PIN, 0);
    }
    else {
        // Do something when Caps Word deactivates.
        writePin(LED_KEYPAD, 1);
        writePin(LED_NUM_LOCK_PIN, 1);
        writePin(LED_SCROLL_LOCK_PIN, 1);
        writePin(LED_CAPS_LOCK_PIN, 1);
    }
}

// Changes the LEDs on Keyboard to indicate active layers
layer_state_t layer_state_set_user(layer_state_t state) {
    if (!caps_word_get() && !isRecording) { // Let Macro and CapsWord LED settings override standard ones
        // LED Labelled: Keypad Symbol
        writePin(LED_KEYPAD, !layer_state_cmp(state, _KEYPAD));
        // LED Labelled: "1"
        writePin(LED_NUM_LOCK_PIN, !layer_state_cmp(state, _SYMBOLS));
        // LED Labelled: "↓"
        writePin(LED_SCROLL_LOCK_PIN, !layer_state_cmp(state, _NAV));
        // LED Labelled: "A"
        writePin(LED_CAPS_LOCK_PIN, !layer_state_cmp(state, _FUNCTION));
    }
    return state;
}

bool led_update_user(led_t led_state) {
    // Disable led_update_kb() so that layer indication code doesn't get overridden.
    return false;
}

void matrix_scan_user(void) {

    // CMD_TAB Timer Timed Out
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_cmd_tab_active = false;
        }
    }


    // Dynamic Macro Recording LED flash
    if (isRecording)
    {
        // timer_elapsed() is a built-in function in qmk => it calculates in ms the time elapsed with timer_read()
        if (timer_elapsed(recording_timer) > 500) 
        {
            isRecordingLedOn = !isRecordingLedOn;
            recording_timer = timer_read();
            writePin(LED_KEYPAD, 1);
            writePin(LED_NUM_LOCK_PIN, 1);
            writePin(LED_SCROLL_LOCK_PIN, 1);
            writePin(LED_CAPS_LOCK_PIN, 1);
        }
        if (isRecordingLedOn)
        {
            writePin(LED_KEYPAD, 0);
            writePin(LED_NUM_LOCK_PIN, 0);
            writePin(LED_SCROLL_LOCK_PIN, 0);
            writePin(LED_CAPS_LOCK_PIN, 0);
        }
    }
}

// Tap Dance processing function option 1
// This tap dance favors keys that are used frequently in typing like 'f'
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return UNKNOWN;
}

// Tap Dance processing function option 2
// This works well if you want this key to work as a "fast modifier". It favors being held over being tapped.
int hold_cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  // If count = 2, and it has been interrupted - assume that user is trying to type the letter associated with single tap.
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return UNKNOWN;
}

// Caps Lock Replacement Tap Dance 
// Create an instance of 'td_tap_t' for the 'full' tap dance.
// [NVUD] = FULL_TAP_DANCE(KC_UNDS, 3, 3, KC_CAPS, 4, C(KC_C)),

// static td_tap_t full_td_state = {
//   .is_press_action = true,
//   .state = TD_NONE
// };

// void full_td_finished (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
//   full_td_state.state = hold_cur_dance(state);
//   switch (full_td_state.state) {
//     case SINGLE_TAP: register_code16(keycodes->kc1); break;
//     case SINGLE_HOLD: layer_on(keycodes->kc2); break;
//     case DOUBLE_TAP: layer_invert(keycodes->kc3); break;
//     case DOUBLE_HOLD: register_code16(keycodes->kc4); break;
//     case TRIPLE_TAP: layer_invert(keycodes->kc5); break;
//     case TRIPLE_HOLD: register_code16(keycodes->kc6); break;
//     default: break;
//   }
// }

// void full_td_reset (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
//   switch (full_td_state.state) {
//     case SINGLE_TAP: unregister_code16(keycodes->kc1); break;
//     case SINGLE_HOLD: layer_off(keycodes->kc2); break;
//     // case DOUBLE_TAP: unregister_code16(keycodes->kc3); break;
//     case DOUBLE_HOLD: unregister_code16(keycodes->kc4); break;
//     // case TRIPLE_TAP: unregister_code16(keycodes->kc5); break;
//     case TRIPLE_HOLD: unregister_code16(keycodes->kc6); break;
//     default: break;
//   }
//   full_td_state.state = 0;
// }

// SLSH Tap Dance
// Create an instance of 'td_tap_t' for the 'slsh' tap dance.
static td_tap_t slsh_td_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void slsh_td_finished (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
  slsh_td_state.state = hold_cur_dance(state);
  switch (slsh_td_state.state) {
    case SINGLE_TAP: tap_code(KC_SLSH); break;  // One slash
    case SINGLE_HOLD: tap_code16(G(KC_SLSH)); break;    // Command + / shortcut for commenting a line
    case DOUBLE_TAP: tap_code16(KC_SLSH); tap_code16(KC_SLSH); break;   // Double slash
    case DOUBLE_HOLD: SEND_STRING("/**/"); tap_code(KC_LEFT); tap_code(KC_LEFT); tap_code(KC_ENT); tap_code(KC_ENT); tap_code(KC_UP); break;    // HTML multiline comment
    case TRIPLE_TAP: tap_code16(KC_QUES); break;    // Question mark
    // case TRIPLE_HOLD: register_code16(C(KC_C)); break;   // Nothing
    default: break;
  }
}

void slsh_td_reset (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
//   switch (slsh_td_state.state) {
    // case SINGLE_TAP: unregister_code16(keycodes->kc1); break;
    // case SINGLE_HOLD: layer_off(_NAV); break;
    // case DOUBLE_TAP: unregister_code16(G(KC_GRV)); break;
    // case DOUBLE_HOLD: layer_off(_NAV); clear_mods(); break;
    // case TRIPLE_TAP: layer_invert(_NUMPAD); break;
    // case TRIPLE_HOLD: unregister_code16(C(KC_C)); break;
    // default: break;
//   }
  slsh_td_state.state = 0;
}

// RPINKY Tap Dance
// Create an instance of 'td_tap_t' for the 'rpinky' tap dance.
static td_tap_t rpinky_td_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void rpinky_td_finished (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
  rpinky_td_state.state = hold_cur_dance(state);
  switch (rpinky_td_state.state) {
    case SINGLE_TAP: tap_code(KC_QUOT); break;                                             // Single Quote
    case SINGLE_HOLD: layer_on(_SYMBOLS); set_oneshot_layer(_SYMBOLS, ONESHOT_START); break; // One shot coding symbols layer
    case DOUBLE_TAP: tap_code16(KC_DQUO); break;                                            // Double Quote
    case DOUBLE_HOLD: caps_word_set(true); break;                                           // Caps Word
    case TRIPLE_TAP: layer_invert(_NUMSHIFT); break;                                        // Toggle NUMSHIFT layer
    case TRIPLE_HOLD: layer_invert(_KEYPAD); break;                                         // Toggle KEYPAD layer
    default: break;
  }
}

void rpinky_td_reset (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
  switch (rpinky_td_state.state) {
    case SINGLE_TAP: layer_off(_NAV); break;
    case SINGLE_HOLD: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    // case DOUBLE_TAP: unregister_code16(G(KC_GRV)); break;
    // case DOUBLE_HOLD: layer_off(_NAV); clear_mods(); break;
    // case TRIPLE_TAP: layer_invert(_NUMPAD); break;
    // case TRIPLE_HOLD: unregister_code16(C(KC_C)); break;
    default: break;
  }
  rpinky_td_state.state = 0;
}

// LPINKY Tap Dance
// Create an instance of 'td_tap_t' for the 'lpinky' tap dance.
static td_tap_t lpinky_td_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void lpinky_td_finished (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
  lpinky_td_state.state = cur_dance(state);
  switch (lpinky_td_state.state) {
    case SINGLE_TAP: layer_on(_SYMBOLS); set_oneshot_layer(_SYMBOLS, ONESHOT_START); break; // One shot coding symbols layer
    case SINGLE_HOLD: layer_on(_NAV); break;                                                // Navigation layer while holding
    case DOUBLE_TAP: layer_invert(_NAV); break;                                             // Navigation layer toggle
    case DOUBLE_HOLD: caps_word_set(true); break;                                           // Caps Word
    case TRIPLE_TAP: layer_invert(_LKEYPAD); break;                                         // Toggle Numpad
    case TRIPLE_HOLD: register_code16(C(KC_C)); break;                                      // Control+C to end running program in terminal
    default: break;
  }
}

void lpinky_td_reset (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
  switch (lpinky_td_state.state) {
    case SINGLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: layer_off(_NAV); break;
    // case DOUBLE_TAP: unregister_code16(G(KC_GRV)); break;
    // case DOUBLE_HOLD: layer_off(_NAV); clear_mods(); break;
    // case TRIPLE_TAP: layer_invert(_NUMPAD); break;
    case TRIPLE_HOLD: unregister_code16(C(KC_C)); break;
    default: break;
  }
  lpinky_td_state.state = 0;
}


// Window Management Tap Dance
// Create an instance of 'td_tap_t' for the 'window' tap dance.
static td_tap_t window_td_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void window_td_finished (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
  window_td_state.state = hold_cur_dance(state);
  switch (window_td_state.state) {
    case SINGLE_TAP: add_oneshot_mods(MOD_MASK_CSAG); break;            // One shot Hyper key
    case SINGLE_HOLD: layer_on(_NAV); set_mods(MOD_MASK_CA); break;     // Navigation layer while holding, with CTL+OPT active
    case DOUBLE_TAP: register_code16(G(KC_GRV)); break;                 // Switch between open windows of the same application
    case DOUBLE_HOLD: layer_on(_NAV); set_mods(MOD_MASK_CAG); break;    // Navigation layer while holding, with CMD+CTL+OPT active 
    case TRIPLE_TAP: add_oneshot_mods(MOD_MASK_SA); break;              // One shot SHIFT+OPT
    case TRIPLE_HOLD: register_code16(G(KC_H)); break;                  // Hide window
    default: break;
  }
}

void window_td_reset (qk_tap_dance_state_t *state, void *user_data) {
//   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
  switch (window_td_state.state) {
    // case SINGLE_TAP: unregister_code16(keycodes->kc1); break;
    case SINGLE_HOLD: layer_off(_NAV); clear_mods(); break;
    case DOUBLE_TAP: unregister_code16(G(KC_GRV)); break;
    case DOUBLE_HOLD: layer_off(_NAV); clear_mods(); break;
    // case TRIPLE_TAP: break;
    case TRIPLE_HOLD: unregister_code16(G(KC_H)); break;
    default: break;
  }
  window_td_state.state = 0;
}


// Declare the functions to be used with tap dance key(s)
qk_tap_dance_action_t tap_dance_actions[] = {
    [LBCB] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),  // Left bracket on a single-tap, left brace on a double-tap
    [RBCB] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),  // Right bracket on a single-tap, right brace on a double-tap
    [PLEQ] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_PLUS),   // Equal sign on a single-tap, plus sign on a double-tap
    [UNMN] = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),  // Underscore sign on a single-tap, minus on a double-tap
    // [SMCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),   // Semicolon on a single-tap, colon on a double-tap
    // [APQU] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),  // Single quote on a single-tap, double quote on a double-tap
    [CMAG] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LABK),  // Comma on a single-tap, left angle bracket on a double-tap
    [SPOT] = ACTION_TAP_DANCE_DOUBLE(G(KC_SPC), KC_RBRC),  // Command+Space (Spotlight) on a single-tap, Right brace on a double-tap
    [ISPT] = ACTION_TAP_DANCE_DOUBLE(KC_I, G(KC_SPC)),  // I key on a single-tap, Command+Space (Spotlight) on a double-tap


    // Advanced Tap Dance functions
    [PDAG] = ACTION_TAP_DANCE_FN(triple_tap_dance_period), // Dot on a single-tap, right angle bracket on a double-tap, three dots on a triple tap
    // [SLQU] = ACTION_TAP_DANCE_FN(triple_tap_dance_slash), // Slash on a single-tap, two slashes on a double-tap, question mark on a triple tap
    [GVES] = ACTION_TAP_DANCE_FN(triple_tap_dance_esc), // Esc on a single-tap, grave on a double-tap, tilde on a triple tap
    // [NVUD] = FULL_TAP_DANCE(KC_UNDS, 3, 3, KC_CAPS, 4, C(KC_C)),
    [SLSH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, slsh_td_finished, slsh_td_reset),
    [RPINKY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rpinky_td_finished, rpinky_td_reset),
    [LPINKY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lpinky_td_finished, lpinky_td_reset),
    [WIND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, window_td_finished, window_td_reset),
};

// This function holds the main switch statement for keycode definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Caps word
    if (!process_caps_word(keycode, record)) { return false; }

    // Num word
    if (!process_record_num_word(keycode, record)) { return false; }

    // Select word macro from https://getreuer.info/posts/keyboards/select-word/index.html
    if (!process_select_word(keycode, record, SELWORD)) { return false; }

    // Store the current modifier state in a variable for later reference
    mod_state = get_mods();

    switch (keycode) {
        case LT(0,KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_X)); // Intercept hold function to send CMD+X
                return false;
            }
            return true;             // Return true for normal processing of tap key code
        case LT(0,KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_C)); // Intercept hold function to send CMD+C
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_V):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_V)); // Intercept hold function to send CMD+V
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_Z):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_Z)); // Intercept hold function to send CMD+Z
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case CLEAR:                  // Clears all keycodes currently pressed, including modifiers
            if (!record->tap.count && record->event.pressed) {
                clear_keyboard();
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case RCTL_T(KC_COLN):
            if (record->tap.count && record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT || get_oneshot_mods() & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_SCLN keycode
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_LNUM); // Dummy keypress to get rid of lingering one shot modifier shift that seems to be a bug
                    tap_code(KC_SCLN);
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the colon key.
                    set_mods(mod_state);
                }
                else{
                    tap_code16(KC_COLN); // Send KC_COLN on single tap
                }
                return false;        // Return false to ignore further processing of key
            }
            break;
        case LGUI_T(KC_BSPC):
        case HYPR_T(KC_BSPC):
            {
                // Initialize a boolean variable that keeps track
                // of the delete key status: registered or not?
                static bool delkey_registered;
                if (record->event.pressed) {
                    // Detect the activation of either shift keys
                   
                    if (mod_state & MOD_MASK_SHIFT || get_oneshot_mods() & MOD_MASK_SHIFT) {
                        // First temporarily canceling both shifts so that
                        // shift isn't applied to the KC_DEL keycode
                        del_mods(MOD_MASK_SHIFT);
                        tap_code(KC_LNUM); // Dummy keypress to get rid of lingering one shot modifier shift that seems to be a bug
                        register_code(KC_DEL);
                        set_mods(mod_state);
                        // Update the boolean variable to reflect the status of KC_DEL
                        delkey_registered = true;
                        // Reapplying modifier state so that the held shift key(s)
                        // still work even after having tapped the Backspace/Delete key.
                        return false;
                    }
                }
                else { // on release of KC_BSPC
                    // In case KC_DEL is still being sent even after the release of KC_BSPC
                    if (delkey_registered) {
                        del_mods(MOD_MASK_SHIFT);
                        unregister_code(KC_DEL);
                        set_mods(mod_state);
                        delkey_registered = false;
                        return false;
                    }
                }
                return true;
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;
        case CAPWORD: // Caps Word
            if (record->event.pressed) {
                    caps_word_set(true);
                    break;
            }
        case APP_NAV:
            // Super cmd↯TAB modified for MacOS to CMD_TAB
            // This macro will register KC_LGUI and tap KC_TAB, then wait for 1000ms. 
            // If the key is tapped again, it will send another KC_TAB and restart timer.
            // If there is no tap within 1000m, KC_LGUI will be unregistered, thus allowing you to cycle through windows.
            // Press shift key with APP_NAV key to send Shift+Cmd+Tab which iterates through the application switcher window backwards.
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return true;
        case KPSWAP:
            if (record->event.pressed) {
                layer_invert(_KEYPAD);
                layer_invert(_LKEYPAD);
                return false;
            }
            return true;
        case(ESC_STS):
            if (mod_state & MOD_MASK_GUI) {
                        tap_code(KC_ESC);
                        // if (mod_state & MOD_MASK_ALT);
                        // tap_code(KC_ESC);
                        return false;
                    }
                // return true;
            else if (mod_state & MOD_MASK_SHIFT || get_oneshot_mods() & MOD_MASK_SHIFT) {
                // Detect the activation of either shift keys
                if (record->event.pressed) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the following code
                    del_mods(MOD_MASK_SHIFT);
                    
                    SEND_STRING("Firmware> QMK " QMK_VERSION ", " QMK_BUILDDATE "\n");
                    SEND_STRING("Keyboard> " QMK_KEYBOARD "\n");
                    SEND_STRING("Keymap> " QMK_KEYMAP "\n");

                    if (keymap_config.nkro)
                        SEND_STRING("NKRO> Enabled\n");
                    else
                        SEND_STRING("NKRO> Disabled\n");

                    if (debug_enable)
                        SEND_STRING("Debug> Enabled\n");
                    else
                        SEND_STRING("Debug> Disabled\n");

                    // Reapplying modifier state so that the held shift key(s) still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            }
            else if (record->event.pressed) {
                // Esc key activated without either shift key
                register_code(KC_ESC);
                return false;
            }
            else {
                // On release of Esc key if Status was not executed
                unregister_code(KC_ESC);
                return false;
            }
            break;
        default: break;
    }
    return true;  // Return true for normal processing of tap keycode
}