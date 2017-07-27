#include "deltasplit75.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// Fillers to make layering more clear

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {	
	/* Layer 0: Default Layer
     *,-----------------------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6|    F7| F8| F9| F10| F11| F12|Prnt|Ins|Del| 
	 * |----------------------------------------------------------------------|
     * |  `|  1|  2|  3|  4|  5|  6|    7|  8|  9|  0|  -|  =| Backspace| Home|
     * |----------------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|      Y|  U|  I|  O|  P|  [|  ]|  \|    PgUp|
     * |----------------------------------------------------------------------|
     * |Ctrl|  A|  S|  D|  F|  G|       H|  J|  K|  L|  ;|  '|Enter  |  PgDown|
     * |----------------------------------------------------------------------|
     * |Shif|   |  Z|  X|  C|  V|  B|   N|  M|  ,|  .|  /|Shift |      Up| End|
     * |----------------------------------------------------------------------|
     * |CapsLo|Gui |Alt |Sp |Mod |      Sp| Alt| Gui| Ctrl|    | Lef| Dow| Rig|
     * `----------------------------------------------------------------------'
     */
	KEYMAP_V2(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,  KC_F4, KC_F5,  KC_F6,            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,  KC_INS,  KC_DEL, 
		KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,  KC_5,   KC_6,             KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_TRNS, KC_HOME, // KC_TRNS is the unneeded key in the split backspace.
		KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,  KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS, KC_PGUP, 
		KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,  KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_TRNS,  KC_ENT,  KC_PGDN, // KC_TRNS is unneeded ISO enter key. 
		KC_LSFT, KC_TRNS, KC_Z,    KC_X,   KC_C,  KC_V,   KC_B,             KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_UP,   KC_END,  // KC_TRNS is uneeded ISO layout key.
		KC_CAPS, KC_LGUI, KC_LALT,         KC_SPC, MO(1),                   KC_SPC,  KC_RALT, KC_RGUI, KC_RCTL,                   KC_LEFT,  KC_DOWN, KC_RGHT),

	KEYMAP_V2(
		RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, 
		RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_VOLD, 
		KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_MPRV, KC_STOP, KC_MNXT),

};