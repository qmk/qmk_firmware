#include "xd75.h"

#define A_BSPC  LALT(KC_BSPC) // delete whole word in Mac
// #define C_BSPS  LCTL(KC_BSPC) // delete whole word in PC; currently not in use
#define A_LEFT  LALT(KC_LEFT)
#define A_RGHT  LALT(KC_RGHT)
#define C_RGHT  LCTL(KC_RGHT)
#define C_LEFT  LCTL(KC_LEFT)
#define SftEnt  SFT_T(KC_ENT)
#define GBSPC   LGUI_T(KC_BSPC)
#define CBSPC   LCTL_T(KC_BSPC)

//internet browser tab shortcuts and window swapping for Mac and Win
#define GSL     LGUI(S(KC_LEFT)) // back one tab in Safari
#define GSR     LGUI(S(KC_RGHT)) // forward one tab in Safari
#define CTLPGDN LCTL(KC_PGDN)   // back one tab on Windows
#define CTLPGUP LCTL(KC_PGUP)   // forward one tab on Windows
#define G_TAB   LGUI(KC_TAB)    // MAC: switch applications
#define G_GRV   LGUI(KC_GRV)    // MAC: switch between windows within an application
#define A_TAB   LALT(KC_TAB)
#define C_TAB   LCTL(KC_TAB)

//
#define NAV     LT(3, KC_TAB)
#define NAVPC   LT(4, KC_TAB)

// Layer shorthand
#define _COLEMAK 0
#define _PC 1
#define _SYMBOL 2   //Function keys, numbers, symbols, Backlighting
#define _NAV 3   //Navigation Layer on Mac
#define _NAVPC 4 //Navigation Layer on Win

//tapdance declarations
enum {
  SFT_LCK
};

//alias for tapdance
#define SftLck TD(SFT_LCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `~     | 1      | 2      | 3      | 4      | 5      | -      | SWITCH | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | ESC/`~ | Q      | W      | F      | P      | G      | [      | \      | ]      | J      | L      | U      | Y      | ;      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | NAVTAB | A      | S      | D      | F      | G      | PgUp   |PlayPaus| ENTER  | H      | N      | E      | I      | O      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |SFT/CAPS| Z      | X      | C      | V      | B      | PgDn   |  UP    | ENTER  | K      | M      | ,      | .      | /      | SftEnt |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | DEL    | LGUI   | LCTRL  | LALT   | LGUI   | BKSPC  | LEFT   | DOWN   | RIGHT  | SPACE  | SYMBOL | RGUI   | RALT   | RCTRL  | BL     |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_COLEMAK] = { /* COLEMAK */
  { KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MINS, TG(1)  , KC_EQL,  KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_GESC, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,   KC_LBRC, KC_BSLS, KC_RBRC, KC_J,   KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_BSPC },
  { NAV    , KC_A,    KC_R,    KC_S,    KC_T,    KC_D,   KC_PGUP, KC_ESC , KC_ENT , KC_H,   KC_N,   KC_E,    KC_I,    KC_O,    KC_QUOT },
  { SftLck , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_PGDN, KC_UP  , KC_ENT , KC_K,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, SftEnt  },
  { KC_DEL , KC_LGUI, KC_LCTL, KC_LALT, KC_LGUI, GBSPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC, MO(2) , KC_RGUI, KC_RALT, KC_RCTL, BL_STEP },
 },
    
// Windows Layer: essentially swaps Control and GUI

 [_PC] = { /* WINDOWS */
  { _______, _______, _______, _______, _______, _______, _______, TG(0)  , _______, _______, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { NAVPC  , _______, _______, _______, _______, _______, _______, KC_MPLY, _______, _______, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { _______, KC_LCTL, KC_LGUI, _______, KC_LCTL, _______, _______, _______, _______, _______, _______, KC_RCTL, KC_RALT, KC_RGUI, _______ },
 },

/* SYMBOL
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F12    | F1     | F2     | F3     | F4     | F5     |        |        |        | F6     | F7     | F8     | F9     | F10    | F11    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | [{     | 1      | 2      | 3      | 4      | 5      |        |        |        | 6      | 7      | 8      | 9      | 0      | }]     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | !      | @      | #      | $      | %      |        |        |        | ^      | &      | *      | (      | )      | =      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | HOME   | END    | BL_OFF | BL_ON  |        |        |        |        |        | -_     |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_SYMBOL] = { /* SYMBOL */
  { _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______, _______, _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______},
  { KC_LBRC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, _______, _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_RBRC},
  { _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL },
  { _______, KC_HOME, KC_END , BL_OFF , BL_ON  , KC_F11 , _______, _______, _______, KC_F12 , KC_MINS, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, A_BSPC , _______, _______, _______, _______, _______, _______, _______, _______, _______},
 },

 
 [_NAV] = { /* NAVIGATION for Mac */
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, C_TAB  , A_LEFT,  KC_UP,   A_RGHT , KC_DEL , _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, GSL    , KC_LEFT, KC_DOWN, KC_RGHT, GSR    , _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, G_TAB  , ABSPC  , KC_HOME, KC_END , G_GRV  , _______},
  { RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
 },

 [_NAVPC] = { /* NAVIGATION FOR WINDOWS: replaces Alt with Control, GUI with Alt, and browser tab shortcuts*/
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, C_TAB  , C_LEFT,  KC_UP,   C_RGHT , KC_DEL , _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, CTLPGUP, KC_LEFT, KC_DOWN, KC_RGHT, CTLPGDN, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, A_TAB  , CBSPC  , KC_HOME, KC_END , _______, _______},
  { RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
 }
};

// Shift vs capslock function. From bbaserdem's Planck keymap.
void caps_tap (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LSFT);
    } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        register_code (KC_CAPS);
    }
}
void caps_tap_end (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_LSFT);
    } else {
        unregister_code (KC_CAPS);
    }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Shift, twice for Caps Lock
  [SFT_LCK] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end )
};

/* Template for future layers
 [_LAYER_NAME] = { 
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
 }
};
*/
