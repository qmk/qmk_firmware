#pragma once

#include "quantum.h"

// Define layer names and order
#ifdef KEYBOARD_gherkin
enum userspace_layers {
  gGK = 0,
  gNUM,
  gDIR,
  gETC,
  _GK,
  _QW,
  ONE,
  SUB,
  SUP,
  NUM,
  DIR,
  ETC,
  _FN,
  PAD,
  GK50,
};
#elif KEYBOARD_40percentclub_5x5
enum userspace_layers {
  GK50 = 0,
  _GK,
  _QW,
  PAD,
  gNUM,
  gDIR,
  gETC,
  gGK,
  ONE,
  SUB,
  SUP,
  NUM,
  DIR,
  ETC,
  _FN,
};
#else
  enum userspace_layers {
  _GK = 0,
  _QW,
  PAD,
  ONE,
  SUB,
  SUP,
  NUM,
  DIR,
  ETC,
  gGK,
  gNUM,
  gDIR,
  gETC,
  _FN,
  GK50,
};
#endif

enum userspace_custom_keycodes {
  gGHERKIN = SAFE_RANGE,
  GHERKIN,
  QWERTY,
  ONEHAND,
  SUBTER,
  SUPRA,
  NUMBER,
  DIRECTION,
  ETCETERA,
  gNUMBER,
  gDIRECTION,
  gETCETERA,
  FUNCTION,
  NUMPAD,
  GHERKIN50,

};

//Tap Dance Declarations (list of my tap dance configurations)
#ifdef TAP_DANCE_ENABLE
enum {
  TD_SFT_CAPS = 0
  ,TD_Q_ESC
  ,CAD_TD
  ,RST_TAP_DANCE
  ,LYR_TAP_DANCE
  ,LYR50_TAP_DANCE
  ,LYR75_TAP_DANCE
  ,BSW_TAP_DANCE
};
#endif

// Since our quirky block definitions are basically a list of comma separated
// arguments, we need a wrapper in order for these definitions to be
// expanded before being used as arguments to the LAYOUT_xxx macro.
#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_3x10_wrapper(...)       LAYOUT_ortho_3x10(__VA_ARGS__)
#define LAYOUT_ortho_4x4_wrapper(...)        LAYOUT_ortho_4x4(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x5_wrapper(...)        LAYOUT_ortho_5x5(__VA_ARGS__)
#define LAYOUT_ortho_5x10_wrapper(...)       LAYOUT_ortho_5x10(__VA_ARGS__)
#define LAYOUT_ortho_5x15_wrapper(...)       LAYOUT_ortho_5x15(__VA_ARGS__)

// Blocks for each of the major keyboard layouts
// Organized so we can quickly adapt and modify all of them
// at once, rather than for each keyboard, one at a time.
// And this allows for much cleaner blocks in the keymaps.

// NOTE: These are all the same length.  If you do a search/replace
//       then you need to add/remove underscores to keep the
//       lengths consistent.


/* Pure Gherkin
 * .-----------------------------------------------------------------------------------------.
 * | Q//ESC | W      | E      | R      | T      | Y      | U      | I      | O      | P      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | A      | S      | D      | F      | G      | H      | J      | K      | L      | SPACE  |
 * |        |        |        |        |        |        |        |        |        |SFThold |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Z      | X      | C      | V/gNUM | B/gETC | N      | M/gDIR | ,/GUI  | ./ALT  | BSPC   |
 * | SFThold|        |        |        |        |        |        |        |        |CTRLhold|
 * '-----------------------------------------------------------------------------------------'
 */
#define _______________Gherkin_Row_0_______________			TD(TD_Q_ESC),	KC_W,	KC_E, 	KC_R, 			KC_T, 			KC_Y, 	KC_U, 			KC_I, 			KC_O, 			KC_P
#define _______________Gherkin_Row_1_______________			KC_A, 			KC_S, 	KC_D, 	KC_F, 			KC_G, 			KC_H, 	KC_J, 			KC_K, 			KC_L, 			SFT_T(KC_SPC)
#define _______________Gherkin_Row_2_______________			SFT_T(KC_Z), 	KC_X, 	KC_C, 	LT(gNUM,KC_V),	LT(gETC,KC_B),  KC_N, 	LT(gDIR,KC_M), 	GUI_T(KC_COMM),	ALT_T(KC_DOT),	CTL_T(KC_BSPC)

/* Directional Keys
 * .-----------------------------------------------------------------------------------------.
 * | TAB    |   up   |        | INS    |  CTRL  | SHIFT  | PgUp   | HOME   |  -     |  =     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | left   |  down  | right  | PrScr  | SHIFT  |  CTRL  | PgDn   | END    |  [     |  ]     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | P-Brk  |        |        |        |        |        |        | RGUI   | ALT    |  /     |
 * '-----------------------------------------------------------------------------------------'
 */
#define _______________Gherkin_DIR_0_______________			KC_TAB,	 KC_UP,   _______, KC_INS,  KC_LCTL, KC_RSFT, KC_PGUP, KC_HOME, KC_MINS, KC_EQL
#define _______________Gherkin_DIR_1_______________			KC_LEFT, KC_DOWN, KC_RGHT, KC_PSCR, KC_LSFT, KC_RCTL, KC_PGDN, KC_END,  KC_LBRC, KC_RBRC
#define _______________Gherkin_DIR_2_______________			KC_PAUS, _______, _______, _______, _______, _______, _______, KC_RGUI, KC_LALT, KC_SLSH

/* Numbers
 * .-----------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | F11    | F12    |        |        |        | ENTER  | SHIFT  | GUI    | ./ALT  | BSPC   |
 * |        |        |        |        |        |        |        |        |        |CTRLhold|
 * '-----------------------------------------------------------------------------------------'
 */
#define _______________Gherkin_NUM_0_______________			KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,   KC_F6,  KC_F7,   KC_F8,   KC_F9,         KC_F10
#define _______________Gherkin_NUM_1_______________			KC_1,   KC_2,   KC_3,	KC_4,    KC_5,    KC_6,   KC_7,    KC_8,    KC_9,          KC_0
#define _______________Gherkin_NUM_2_______________			KC_F11, KC_F12, _______,_______, _______, KC_ENT, KC_RSFT, KC_RGUI, ALT_T(KC_DOT), CTL_T(KC_BSPC)

/* Et Cetera
 * .-----------------------------------------------------------------------------------------.
 * |  `     | mUP    |        |        | RESET  | SHIFT  | mScrDn | mScrUp |        |  \     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | mLeft  | mDown  | mRight |        | SHIFT  | mBtn3  | mBtn1  | mBtn2  |  ;     |  '     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Sft//Cp| CAPS   |        |        |        | C-A-D  | mScrL  | mScrR  | ALT    |  DEL   |
 * '-----------------------------------------------------------------------------------------'
 */
#define _______________Gherkin_ETC_0_______________			KC_GRV, 		KC_MS_U, _______,_______, RESET,   KC_RSFT, 			KC_WH_D, KC_WH_U, _______, KC_BSLS
#define _______________Gherkin_ETC_1_______________			KC_MS_L, 		KC_MS_D, KC_MS_R,_______, KC_LSFT, KC_BTN3, 			KC_BTN1, KC_BTN2, KC_SCLN, KC_QUOT
#define _______________Gherkin_ETC_2_______________			TD(TD_SFT_CAPS),KC_CAPS, _______,_______, _______, LALT(LCTL(KC_DEL)),	KC_WH_L, KC_WH_R, KC_LALT, KC_DEL

/* Gherkin-Like
 * .-----------------------------------------------------------------------------------------------------------.
 * | ESC    | Q//ESC | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BSPC   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | A      | S      | D      | F      | G      | H      | J      | K      | L      | SPACE  |  '     |
 * |        |        |        |        |        |        |        |        |        |        |SFThold |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |SFT/CAPS| Z      | X      | C      | V/NUM  | B/ETC  | N      | M/DIR  | ,/GUI  | ./ALT  | BSPC   | ENT/SFT|
 * |        |SFThold |        |        |        |        |        |        |        |        |CTRLhold|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCTRL  | LGUI   | ALT    | ONEHAND|  NUM   | ETC    | SPACE  |  DIR   | RGUI   | ALT    | DEL    | CTRL   |
 * '-----------------------------------------------------------------------------------------------------------'
 */
#define _______________GherkinLike_0_______________     KC_ESC, _______________Gherkin_Row_0_______________, KC_BSPC
#define _______________GherkinLike_1_______________     KC_TAB, _______________Gherkin_Row_1_______________, KC_QUOT
#define _______________GherkinLike_2_______________     TD(TD_SFT_CAPS), SFT_T(KC_Z), KC_X, KC_C, LT(NUM, KC_V),LT(ETC, KC_B),KC_N, LT(DIR, KC_M), GUI_T(KC_COMM), ALT_T(KC_DOT), CTL_T(KC_BSPC), SFT_T(KC_ENT)
#define _______________GherkinLike_3_______________     KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, NUMBER, ETCETERA, KC_SPC,DIRECTION, KC_RGUI, KC_RALT, KC_DEL, KC_RCTL
#define _______________GherkinLike_3_OneHand_______     KC_LCTL, KC_LGUI, KC_LALT, ONEHAND, NUMBER, ETCETERA, KC_SPC,DIRECTION, KC_RGUI, KC_RALT, ONEHAND, KC_RCTL

/* Qwerty
 * .-------------------------------------------------------------------------------------.
 * | Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BSPC  |
 * |-------+------+------+------+------+-------------+------+------+------+------+-------|
 * | Tab   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '    |
 * |-------+------+------+------+------+------|------+------+------+------+------+-------|
 * |Sft/Cps|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |ENT/SFT|
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * | LCTRL | LGUI | ALT  | ALT  | SUB  | SHIFT| SPACE| SUP  | RGUI | RALT | DEL  | CTRL  |
 * '-------------------------------------------------------------------------------------'
 */
#define _______________Qwerty_Row__0_______________   KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC
#define _______________Qwerty_Row__1_______________   KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define _______________Qwerty_Row__2_______________   TD(TD_SFT_CAPS),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_ENT)
#define _______________Qwerty_Row__3_______________   KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, SUBTER,  KC_LSFT, KC_SPC,  SUPRA,   KC_RGUI, KC_RALT, KC_DEL,  KC_RCTL

/* SUPRA
 * .-----------------------------------------------------------------------------------------------------------.
 * | RESET  | TAB    |   up   |        | INS    | CTRL   | SHIFT  | PgUp   | Home   |   -    |   =    |  DEL   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |  left  |  down  | right  | PrScr  | SHIFT  | CTRL   | PgDn   | End    |   [    |   ]    |   \    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | P-Brk  |        |        |        |        |        |        | RGUI   | ALT    |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
#define ________________SUPRA_Row_0________________   RESET,   KC_TAB,  KC_UP,   _______, KC_INS,  KC_LCTL, KC_RSFT, KC_PGUP, KC_HOME, KC_MINS, KC_EQL,  KC_DEL
#define ________________SUPRA_Row_1________________   _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PSCR, KC_LSFT, KC_RCTL, KC_PGDN, KC_END,  KC_LBRC, KC_RBRC, KC_BSLS
#define ________________SUPRA_Row_2________________   _______, KC_PAUS, _______, _______, _______, _______, _______, _______, KC_RGUI, KC_RALT, _______, _______
#define ________________SUPRA_Row_3________________   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______

/* SUBTER
 * .-----------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    |  DEL   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |    `   | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F11    | F12    |        |        |        |        |        | RGUI   | ./ALT  | BSPC   |        |
 * |        |        |        |        |        |        |        |        |        |        |CTRLhold|	       |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | gherkin|        |        |        | ENTER  | SHIFT  |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
#define _______________SUBTER_Row__0_______________   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,  KC_F9,			KC_F10,			KC_DEL
#define _______________SUBTER_Row__1_______________   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,   KC_9, 			KC_0,    		_______
#define _______________SUBTER_Row__2_______________   _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______,  KC_RGUI,ALT_T(KC_DOT),  	CTL_T(KC_BSPC), _______
#define _______________SUBTER_Row__3_______________   _______, _______, GHERKIN, _______, _______, _______, KC_ENT,  KC_LSFT,  _______,_______,			_______,		_______

/* Gherkin Numbers
 * .-----------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | BSPC |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F11    | F12    |        |        |        | ENTER  | SHIFT  | RGUI   | ./ALT  | BSPC   |        |
 * |        |        |        |        |        |        |        |        |        |        |CTRLhold|	  	   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | ENTER  | SHIFT  | RGUI   |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
#define _______________NUMBERS_Row_0_______________   _______, _______________Gherkin_NUM_0_______________,  KC_BSPC
#define _______________NUMBERS_Row_1_______________   _______, _______________Gherkin_NUM_1_______________,  _______
#define _______________NUMBERS_Row_2_______________   _______, _______________Gherkin_NUM_2_______________,  _______
#define _______________NUMBERS_Row_3_______________   _______, _______, _______, _______, _______, _______, KC_ENT, KC_RSFT, KC_RGUI, _______, _______, _______


/* Gherkin Directional Keys
 * .-----------------------------------------------------------------------------------------------------------.
 * |        | TAB    |   up   |        | INS    | CTRL   | SHIFT  | PgUp   | HOME   |  -     |  =     | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | left   |  down  | right  | PrScr  | SHIFT  | CTRL   | PgDn   | END    |  [     |  ]     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | P-Brk  |        |        |        |        |        |        | RGUI   | ALT    |  /     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | qwerty |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
#define _____________DIRECTIONS_Row__0_____________   _______, _______________Gherkin_DIR_0_______________, KC_DEL
#define _____________DIRECTIONS_Row__1_____________   _______, _______________Gherkin_DIR_1_______________, _______
#define _____________DIRECTIONS_Row__2_____________   _______, _______________Gherkin_DIR_2_______________, _______
#define _____________DIRECTIONS_Row__3_____________   _______, _______, QWERTY, _______, _______, _______, _______, _______, _______, _______, _______, _______

/* Gherkin Et Cetera
 * .-----------------------------------------------------------------------------------------------------------.
 * |        |  `     | mUP    |        |        | RESET  | SHIFT  | mScrUp |mScrDown|        |  \     | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | mLeft  | mDown  | mRight |        | SHIFT  | mBtn3  | mBtn1  | mBtn2  |  ;     |  '     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | Sft//Cp|        |        |        |        | C-A-D  |mScrLeft| mScrRt | ALT    |  DEL   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | C-A-D  |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
#define ______________ETCETERA_Row__0______________   _______, _______________Gherkin_ETC_0_______________, KC_DEL
#define ______________ETCETERA_Row__1______________   _______, _______________Gherkin_ETC_1_______________, _______
#define ______________ETCETERA_Row__2______________   _______, _______________Gherkin_ETC_2_______________, _______
#define ______________ETCETERA_Row__3______________   _______, _______, _______, _______, _______, _______, LALT(LCTL(KC_DEL)), _______, _______, _______, _______, _______
 
/* Single 4x4 board only
 * .-----------------------------------.
 * |   7    |   8    |   9    |  BSPC  |
 * |--------+--------+--------+--------|
 * |   4    |   5    |   6    | SPACE  |
 * |--------+--------+--------+--------|
 * |   1    |   2    |   3    | ENTER  |
 * |--------+--------+--------+--------|
 * |   0    |/ //_GK |   .    |   -    |
 * '-----------------------------------'
 */

#define _______________NUMPAD_Row__0_______________  KC_KP_7, KC_KP_8, KC_KP_9,   KC_BSPC
#define _______________NUMPAD_Row__1_______________  KC_KP_4, KC_KP_5, KC_KP_6,   KC_SPC
#define _______________NUMPAD_Row__2_______________  KC_KP_1, KC_KP_2, KC_KP_3,   KC_PENT
#define _______________NUMPAD_Row__3_______________  KC_KP_0, TD(LYR_TAP_DANCE), KC_KP_DOT, KC_PMNS
