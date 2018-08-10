#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Define layer names
enum userspace_layers {
  gGK = 0,
  _GK,
  _QW,
  SUB,
  SUP,
  NUM,
  DIR,
  ETC,
  gNUM,
  gDIR,
  gETC
};

enum userspace_custom_keycodes {
  gGHERKIN = SAFE_RANGE,
  GHERKIN,
  QWERTY,
  SUBTER,
  SUPRA,
  NUMBER,
  DIRECTION,
  ETCETERA,
  gNUMBER,
  gDIRECTION,
  gETCETERA,
};

//Tap Dance Declarations (list of my tap dance configurations)
#ifdef TAP_DANCE_ENABLE
enum {
  TD_SFT_CAPS = 0
  ,TD_Q_ESC
  ,ENT_TAP_DANCE
  ,DEL_TAP_DANCE
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
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)

// Blocks for each of the major keyboard layouts
// Organized so we can quickly adapt and modify all of them
// at once, rather than for each keyboard, one at a time.
// And this allows for much cleaner blocks in the keymaps.

// NOTE: These are all the same length.  If you do a search/replace
//       then you need to add/remove underscores to keep the
//       lengths consistent.


  /* PURE GHERKIN
   * .-----------------------------------------------------------------------------------------.
   * | Q//ESC | W      | E      | R      | T      | Y      | U      | I      | O      | P      |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | A      | S      | D      | F      | G      | H      | J      | K      | L      | SPACE  |
   * |        |        |        |        |        |        |        |        |        |SFThold |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | Z      | X      | C      | V/NUM  | B/ETC  | N      | M/DIR  | ,/GUI  | ./ALT  | BKSC   |
   * | SFThold|        |        |        |        |        |        |        |        |CTRLhold|
   * '-----------------------------------------------------------------------------------------'
   */
#define _______________Gherkin_Row_0_______________			TD(TD_Q_ESC), 	KC_W,    	KC_E,    KC_R,         KC_T,			KC_Y, 					KC_U,          KC_I,           	KC_O,          	KC_P
#define _______________Gherkin_Row_1_______________			KC_A,         	KC_S,    	KC_D,    KC_F,         KC_G,          	KC_H, 					KC_J,          KC_K,           	KC_L,          	SFT_T(KC_SPC)
#define _______________Gherkin_Row_2_______________			SFT_T(KC_Z),  	KC_X,    	KC_C,    LT(NUM, KC_V),LT(ETC, KC_B), 	KC_N, 					LT(DIR, KC_M), GUI_T(KC_COMM), 	ALT_T(KC_DOT), 	CTL_T(KC_BSPC)

  /* Directional Keys
   * .-----------------------------------------------------------------------------------------.
   * | TAB    |   up   |        | INS    |  CTRL  | SHIFT  | PgUp   | HOME   |  -     |  =     |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | left   |  down  | right  | PrScr  | SHIFT  |  CTRL  | PgDn   | END    |  [     |  ]     |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | P-Brk  |        |        |        |        |        |        | RGUI   | ALT    |  /     |
   * '-----------------------------------------------------------------------------------------'
   */
#define _______________Gherkin_DIR_0_______________			KC_TAB,  	  	KC_UP,		_______, KC_INS,  	   	KC_LCTL, 	  	KC_RSFT,				KC_PGUP, 		KC_HOME,		KC_MINS,		KC_EQL
#define _______________Gherkin_DIR_1_______________			KC_LEFT,		KC_DOWN,	KC_RGHT, KC_PSCR, 		KC_LSFT, 		KC_RCTL,				KC_PGDN, 		KC_END,  		KC_LBRC, 		KC_RBRC
#define _______________Gherkin_DIR_2_______________			KC_PAUS, 		_______,	_______, _______, 		_______, 		_______,				_______, 		KC_RGUI, 		KC_LALT, 		KC_SLSH

  /* Numbers
   * .-----------------------------------------------------------------------------------------.
   * | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | F11    | F12    |        |        |        | ENTER  | SHIFT  | GUI    | ./ALT  | BKSC   |
   * |        |        |        |        |        |        |        |        |        |CTRLhold|
   * '-----------------------------------------------------------------------------------------'
   */
#define _______________Gherkin_NUM_0_______________			KC_F1,   		KC_F2,		KC_F3,	KC_F4,   		KC_F5,			KC_F6,					KC_F7,   		KC_F8,   		KC_F9,   		KC_F10
#define _______________Gherkin_NUM_1_______________			KC_1,    		KC_2,    	KC_3,	KC_4,    		KC_5,    		KC_6,					KC_7,   		KC_8,		    KC_9,    		KC_0
#define _______________Gherkin_NUM_2_______________			KC_F11,  		KC_F12,  	_______,_______, 		_______, 		KC_ENT,					KC_RSFT, 		KC_RGUI, 		ALT_T(KC_DOT), 	CTL_T(KC_BSPC)

  /* ETC
   * .-----------------------------------------------------------------------------------------.
   * |  `     | mUP    |        |        | RESET  | SHIFT  | mUp    | mDown  |        |  \     |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | mLeft  | mDown  | mRight |        | SHIFT  | mBtn3  | mBtn1  | mBtn2  |  ;     |  '     |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | Sft//Cp|        |        |        |        | C-A-D  | mLeft  | mRight | ALT    |  DEL   |
   * '-----------------------------------------------------------------------------------------'
   */
#define _______________Gherkin_ETC_0_______________			KC_GRV,  		KC_MS_U, 	_______,_______, 		RESET,   		KC_RSFT,				KC_WH_U, 		KC_WH_D, 		_______, 		KC_BSLS
#define _______________Gherkin_ETC_1_______________			KC_MS_L, 		KC_MS_D, 	KC_MS_R,_______, 		KC_LSFT, 		KC_BTN3,				KC_BTN1, 		KC_BTN2, 		KC_SCLN, 		KC_QUOT
#define _______________Gherkin_ETC_2_______________			TD(TD_SFT_CAPS),_______, 	_______,_______, 		_______, 		LALT(LCTL(KC_DEL)), 	KC_WH_L, 		KC_WH_R, 		KC_LALT, 		KC_DEL

#define _______________GherkinLike_0_______________
#define _______________GherkinLike_1_______________
#define _______________GherkinLike_2_______________
#define _______________Qwerty_Row__0_______________
#define _______________Qwerty_Row__1_______________
#define _______________Qwerty_Row__2_______________
#define ________________SUPRA_Row_0________________
#define ________________SUPRA_Row_1________________
#define ________________SUPRA_Row_2________________
#define _______________SUBTER_Row__0_______________
#define _______________SUBTER_Row__1_______________
#define _______________SUBTER_Row__2_______________
#define _______________NUMBERS_Row_0_______________
#define _______________NUMBERS_Row_1_______________
#define _______________NUMBERS_Row_2_______________
#define _____________DIRECTIONS_Row__0_____________
#define _____________DIRECTIONS_Row__1_____________
#define _____________DIRECTIONS_Row__2_____________
#define ______________ETCETERA_Row__0______________
#define ______________ETCETERA_Row__1______________
#define ______________ETCETERA_Row__2______________


#endif // !USERSPACE
