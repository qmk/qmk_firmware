// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

extern keymap_config_t keymap_config;

// Symbolic names for macro IDs.
#define _QWERTY  0 // QUERTY layer
#define _RAISE   1 // Raise layer
#define _LOWER   2 // Lower layer
#define _CUSTOM  3 // Custom layer
#define _BL      4 // Backlight
#define _MOBILE  5 // Mobile#
#define _CUSTOM1 6 // Custom macro 1
#define _CUSTOM2 7 // Custom macro 2

// Macro shortcuts.
#define RAISE   M(_RAISE)
#define LOWER   M(_LOWER)
#define CUSTOM  M(_CUSTOM) // RAISE + LOWER
#define BL      M(_BL)
#define MOBILE  M(_MOBILE)
#define CUSTOM1 M(_CUSTOM1)
#define CUSTOM2 M(_CUSTOM2)

// This config can be found at Keyboard layout editor site: http://goo.gl/zjXL2l
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /* QWERTY */
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, FUNC(3)},
    {KC_LCTL, KC_ESC,  KC_LGUI, KC_LALT, RAISE,   KC_SPC,  KC_SPC,  LOWER,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT}
},
[_RAISE] = { /* RAISE */
    {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_QUOT, KC_DQT,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {BL,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},
[_LOWER] = { /* LOWER */
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_LCBR, KC_BSLS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV,  KC_TILD, KC_BSLS, KC_PIPE, KC_LBRC, KC_LBRC, KC_TRNS, KC_TRNS},
    {RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_PGDN, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE}
},
[_CUSTOM] = { /* CUSTOM */
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MOBILE,  KC_TRNS, CUSTOM1, CUSTOM2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
}
};

// Enable these functions using FUNC(n) macro. They seem to be buggy mostly.
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(_RAISE, KC_PGUP),   // Tap for PgUp, hold for RAISE
    [1] = ACTION_LAYER_TAP_KEY(_LOWER, KC_PGDN),   // Tap for PgDn, hold for LOWER
    [2] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_CAPS),  // Tap for Caps, hold for Ctrl
    [3] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),   // Tap for Enter, hold for Shift
};

// Set a layer persistantly.
void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Macro actions for each corresponding ID.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
    case _QWERTY: // Default QWERTY layer. // This case not used for now.
	if (record->event.pressed) {
	    persistant_default_layer_set(1UL<<_QWERTY);
	}
	break;
    case _RAISE: // Raised layer.
	if (record->event.pressed) {
	    layer_on(_RAISE);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	} else {
	    layer_off(_RAISE);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	}
	break;
    case _LOWER: // Lowered layer.
	if (record->event.pressed) {
	    layer_on(_LOWER);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	} else {
	    layer_off(_LOWER);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	}
	break;
    case _BL:// Backlight
	if (record->event.pressed) {
	    register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
	    backlight_step();
#endif
	} else {
	    unregister_code(KC_RSFT);
	}
	break;
    case _MOBILE:// Your mobile# here.
	return MACRODOWN(T(1), T(2), T(3), T(MINS),
			 T(1), T(2), T(3), T(MINS),
			 T(1), T(2), T(3), T(4),
			 END);
    case _CUSTOM1:// Your custom macro 1
	return MACRODOWN(T(E), T(M), T(A), T(C), T(S), T(SPC), END);
    case _CUSTOM2:// Your custom macro 2
	return MACRODOWN(T(L), T(S), T(SPC), T(MINS), T(L), T(ENT), END);
    };
    return MACRO_NONE;
}
