#include QMK_KEYBOARD_H
extern keymap_config_t keymap_config;

// Symbolic names for macro IDs.
#define _QWERTY  0  // QUERTY layer
#define _LOWER   1  // Lower layer
#define _RAISE   2  // Raise layer
#define _CUSTOM  3  // Custom layer (LOWER + RAISE)
#define _BL      4  // Backlight
#define _CUS0    5  // Mobile#
#define _CUS1    6  // signature
#define _CUS2    7  // macro 2
#define _CUS3    8  // macro 3
#define _CUS4    9  // macro 4
#define _CUS5    10 // email
#define _COPY    11 // copy
#define _PASTE   12 // paste
#define _CUT     13 // cut

// Macro shortcuts.
#define QWERTY  M(_LOWER)
#define LOWER   M(_LOWER)
#define RAISE   M(_RAISE)
#define CUSTOM  M(_CUSTOM)
#define BL      M(_BL)
#define CUS0    M(_CUS0)
#define CUS1    M(_CUS1)
#define CUS2    M(_CUS2)
#define CUS3    M(_CUS3)
#define CUS4    M(_CUS4)
#define CUS5    M(_CUS5)
#define COPY    M(_COPY)
#define PASTE   M(_PASTE)
#define CUT     M(_CUT)

// Func macro definitions.
#define LWR_PGDN LT(_LOWER, KC_PGDN) // Tap for PgDn, hold for LOWER
#define RSE_PGUP LT(_RAISE, KC_PGUP) // Tap for PgUp, hold for RAISE
#define CTL_CAPS MT(MOD_LCTL, KC_CAPS) // Tap for Caps, hold for Ctrl (DOESN'T SEEM TO WORK)
#define SFT_ENT  MT(MOD_RSFT, KC_ENT) // Tap for Enter, hold for Shift
#define ZM_NRM   FUNC(4) // Zoom normal
#define ZM_IN    FUNC(5) // Zoom out
#define ZM_OUT   FUNC(6) // Zoom in

// Enable these functions using FUNC(n) macro.
const uint16_t PROGMEM fn_actions[] = {
    [4] = ACTION_MODS_KEY(MOD_LCTL, KC_0),
    [5] = ACTION_MODS_KEY(MOD_LCTL, KC_MINS),
    [6] = ACTION_MODS_KEY(MOD_LCTL, KC_PLUS),
    [7] = ACTION_MODS_KEY(MOD_LCTL, KC_UNDS),
 };

// This config can be found at Keyboard layout editor site: https://goo.gl/cF7uIO
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_planck_grid( /* QWERTY */
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_DEL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT,
    KC_LCTL, KC_ESC,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),
[_LOWER] = LAYOUT_planck_grid( /* LOWER */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_MINS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_QUOT, KC_DQT,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, ZM_NRM,  ZM_IN,   ZM_OUT,  KC_TRNS, KC_PGDN, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
[_RAISE] = LAYOUT_planck_grid( /* RAISE */
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,    KC_RPRN,    KC_UNDS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_EQL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PLUS,    KC_TRNS,    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_PIPE, KC_GRV,  KC_TILD, S(KC_COMM), S(KC_DOT),  KC_BSLS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGUP, KC_TRNS, KC_MNXT,    KC_VOLD,    KC_VOLU, KC_MPLY
),
[_CUSTOM] = LAYOUT_planck_grid( /* CUSTOM */
    KC_F1,   KC_F2,   KC_F3,              KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, CUS0,    CUS3,    CUS4,    KC_TRNS, KC_F12,  KC_TRNS,
    KC_TRNS, KC_TRNS, CUT,                COPY,    PASTE,   CUS1,    CUS5,    CUS2,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    BL,      RESET,   LALT(LCTL(KC_DEL)), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)
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
    case _CUS0: // enter your mobile# here
	    return MACRODOWN(T(9), T(9), T(9), T(MINS),T(9), T(9), T(9), T(MINS),T(9), T(9), T(9), T(9),END);
    case _CUS1: // signature line for email
	    return MACRODOWN(T(ENT), T(ENT), T(MINS), T(J), T(W), END);
    case _CUS2: // Custom macro 2
	    return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_L), UP(KC_LSFT), END );
    case _CUS3: // custom macro 3
	    return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_F), UP(KC_LSFT), END );
    case _CUS4: // custom macro 4
	    return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_I), UP(KC_LSFT), END );
    case _CUS5: // Enter your email here
	    return MACRODOWN( TYPE(KC_F),
        DOWN(KC_LSFT), TYPE(KC_2), UP(KC_LSFT),
        TYPE(KC_G), TYPE(KC_M), TYPE(KC_A), TYPE(KC_I), TYPE(KC_L), TYPE(KC_DOT), TYPE(KC_C), TYPE(KC_O), TYPE(KC_M), END );
    case _CUT: //cut macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_X), UP(KC_LCTL), END );
    case _COPY: // copy macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_C), UP(KC_LCTL), END );
    case _PASTE: // paste macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_V), UP(KC_LCTL), END );
    };
    return MACRO_NONE;
}
