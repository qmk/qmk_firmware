
#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

extern keymap_config_t keymap_config;

// Symbolic names for macro IDs.
#define _QWERTY  0 // QUERTY layer
#define _LOWER   1 // Lower layer
#define _RAISE   2 // Raise layer
#define _CUSTOM  3 // Custom layer (LOWER + RAISE)
#define _BL      4 // Backlight
#define _MOB     5 // Mobile#
#define _CUS1    6 // Custom macro 1
#define _CUS2    7 // Custom macro 2

// Macro shortcuts.
#define QWERTY  M(_LOWER)
#define LOWER   M(_LOWER)
#define RAISE   M(_RAISE)
#define CUSTOM  M(_CUSTOM)
#define BL      M(_BL)
#define MOB     M(_MOB)
#define CUS1    M(_CUS1)
#define CUS2    M(_CUS2)

// Func macro definitions.
#define LWR_PGDN LT(_LOWER, KC_PGDN) // Tap for PgDn, hold for LOWER
#define RSE_PGUP LT(_RAISE, KC_PGUP) // Tap for PgUp, hold for RAISE
#define CTL_CAPS FUNC(2) // Tap for Caps, hold for Ctrl (DOESN'T SEEM TO WORK)
#define SFT_ENT  FUNC(3) // Tap for Enter, hold for Shift
#define ZM_NRM   FUNC(4) // Zoom normal
#define ZM_IN    FUNC(5) // Zoom out
#define ZM_OUT   FUNC(6) // Zoom in
#define EM_UNDO  FUNC(7) // Emacs Undo

// Enable these functions using FUNC(n) macro.
const uint16_t PROGMEM fn_actions[] = {
    [2] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_CAPS),
    [3] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
    [4] = ACTION_MODS_KEY(MOD_LCTL, KC_0),
    [5] = ACTION_MODS_KEY(MOD_LCTL, KC_MINS),
    [6] = ACTION_MODS_KEY(MOD_LCTL, KC_PLUS),
    [7] = ACTION_MODS_KEY(MOD_LCTL, KC_UNDS),
 };

// This config can be found at Keyboard layout editor site: http://goo.gl/zjXL2l
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /* QWERTY */
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT},
    {KC_LCTL, KC_ESC,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_LOWER] = { /* LOWER */
    {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {BL,      ZM_NRM,  ZM_IN,   ZM_OUT,  KC_TRNS, KC_PGDN, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},
[_RAISE] = { /* RAISE */
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_PIPE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV,  KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGUP, KC_TRNS, EM_UNDO, KC_VOLD, KC_VOLU, KC_MUTE}
},
[_CUSTOM] = { /* CUSTOM */
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MOB,     KC_TRNS, CUS1,    CUS2,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
}
};

// Set a layer persistently.
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Macro actions for each corresponding ID.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
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
    case _BL: // Backlight
	if (record->event.pressed) {
	    register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
	    backlight_step();
#endif
	} else {
	    unregister_code(KC_RSFT);
	}
	break;
    case _MOB: // Your mobile# here.
	return MACRODOWN(T(1), T(2), T(3), T(MINS),
			 T(1), T(2), T(3), T(MINS),
			 T(1), T(2), T(3), T(4),
			 END);
    case _CUS1: // Your custom macro 1
	return MACRODOWN(T(E), T(M), T(A), T(C), T(S), T(SPC), END);
    case _CUS2: // Your custom macro 2
	return MACRODOWN(T(L), T(S), T(SPC), T(MINS), T(L), T(ENT), END);
    };
    return MACRO_NONE;
}
