#include QMK_KEYBOARD_H
#define C_ESC CTL_T(KC_ESC)

#define RGBLIGHT_SLEEP

// Layers
#define _BASE   0
#define _FN     1
#define _LIGHTS 2

/* Layout designed primarily around replicating the ergonomics of an HHKB, with
 * a standard 60% spacebar row to be more compatible with conveniently
 * available parts. The feature most shamelessly ripped off from the HHKB is
 * the split right shift and backspace.
 *
 * This keymap is macOS-oriented by default, but the AG_SWAP key on the
 * function key can be double-tapped to swap alt and gui, making this layout
 * also functional for Linux and PC.
 *
 * Lastly, we also use the Space Cadet paren management, so left shift and
 * right shift can be used on their own to type open paren and close paren
 * respectively.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base layer
 * Looks like this                                                Arranged like this
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐  ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │  │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤  ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ { │ } │Bksp │  │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤  ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │esc/^ │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │  │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │lshift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │rshift│fn1│  │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤  ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤
 * │ctrl│alt │win │                        │win │alt │menu│ctrl│  │40  │41  │43  │46                      │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘  └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
*/
	[_BASE] = LAYOUT_60_ansi_split_bs_rshift(
 //    _0        _1        _2      _3       _4      _5      _6      _7       _8     _9       _A       _B        _C       _D           _E
/*0_*/ KC_GESC,  KC_1,     KC_2,   KC_3,    KC_4,   KC_5,   KC_6,   KC_7,    KC_8,  KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSLS,     KC_GRV,
/*1_*/ KC_TAB,             KC_Q,   KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC,     KC_BSPC,
/*2_*/ C_ESC,              KC_A,   KC_S,    KC_D,   KC_F,   KC_G,   KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,
/*3_*/ KC_LSFT,            KC_Z,   KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT,     MO(_FN),
/*4_*/ KC_LCTL,  KC_LALT,          KC_LGUI,                 KC_SPC,                          KC_RGUI, KC_RALT,           MO(_LIGHTS), KC_RCTL
  ),

/* Fn layer, where blank keys indicates transparency to the base layer
 * Looks like this                                                Arranged like this (as above)
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐  ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │slp│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│ins│del│  │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤  ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │caps │bup│bdn│   │XXX│   │   │   │prt│scl│pus│ ↑ │   │     │  │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤  ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │vup│vdn│vmt│   │   │   │   │hme│pup│ ← │ → │ Return │  │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │lshift  │   │   │   │   │   │   │   │end│pdn│ ↓ │rshift│   │  │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤  ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤
 * │ctrl│lalt│lgui│       S P A C E        │rgui│ralt│menu│ctrl│  │40  │41  │43  │46                      │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘  └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 * XXX = RESET (dfu mode)
*/
	[_FN] = LAYOUT_60_ansi_split_bs_rshift(
 //    _0       _1       _2       _3       _4        _5       _6       _7       _8       _9       _A       _B       _C       _D         _E
/*0_*/ KC_SLEP, KC_F1,   KC_F2  , KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,    KC_DEL,
/*1_*/ KC_CAPS,          KC_BDN,  KC_BUP,  KC_NO,    RESET,   KC_NO,   KC_NO,   KC_NO,   KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   KC_NO,     KC_NO,
/*2_*/ KC_NO,            KC_VOLD,  KC_VOLU,  KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_RGHT, KC_RETURN,
/*3_*/ KC_LSPO,          KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_END,  KC_PGDN, KC_DOWN,          KC_RSPC,   KC_TRNS,
/*4_*/ KC_LCTL, KC_LALT,          KC_LGUI,                    KC_SPC,                             KC_RGUI, KC_RALT,          KC_APP,    AG_SWAP
  ),

/* LIGHTS LAYER (stolen shamelessly from 256k_HHKB
 *
 *  ,---------------------------------------------------------------------------------------------------------------------+
 * | RGB_TOGGLE  | STATIC | BREATHE | RAINBOW | SWIRL | SNAKE | KNIGHTRIDER | XMAS | STATIC_GRAD | _ |  _ | _ | _ | _ | _ |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | RBG_MOD      |  HUE_INC |  SATURATION_INC  |  BRIGHT_INC   |  _  |  _  |  _  |  _ |  _ |  _ |  _ |  _  |  _  |  _    |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | CTRL           |  HUE_DEC |  SATURATION_DEC  |  BRIGHT_DEC  |  _  |  _  |  _ |  _  |  _  |  _  |  _  |  _  |    _    |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | Shift                |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |  _   |    _   |
 * |----------------------------------------------------------------------------------------------------------------------+
 * |                             _    |      _     |               _               |     _      |     _                   |
 * `----------------------------------------------------------------------------------------------------------------------'
 */
	[_LIGHTS] = LAYOUT_60_ansi_split_bs_rshift(
//     _0       _1       _2       _3       _4        _5        _6       _7       _8       _9      _A      _B      _C      _D      _E
/*0_*/ RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
/*1_*/ RGB_MOD,          RGB_HUI, RGB_SAI, RGB_VAI,  KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
/*2_*/ KC_NO,            RGB_HUD, RGB_SAD, RGB_VAD,  KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
/*3_*/ KC_NO,            KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,          KC_NO,  KC_NO,
/*4_*/ KC_NO,   KC_NO,            KC_NO,                       KC_NO,                             KC_NO,  KC_NO,          KC_NO,  KC_NO
  )
};
