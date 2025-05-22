// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "keycodes.h"
#include "keymap_us.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

enum layer_names {
    _DEF,
    _NUM,
    _SYM,
    _NAV,
};

enum custom_keycodes {
    SS_Qu = SAFE_RANGE,
};

/*  KEY POSITION Names

    LT4 LT3 LT2 LT1 LT0           RT0 RT1 RT2 RT3 RT4
    LM4 LM3 LM2 LM1 LM0           RM0 RM1 RM2 RM3 RM4
    LB4 LB3 LB2 LB1 LB0 LB00 RB00 RB0 RB1 RB2 RB3 RB4
    LH4 LH3 LH2 LH1 LH0 LH00 RH00 RH0 RH1 RH2 RH3 RH4
*/

/*  Hands Down Promethium
    v   w   g2   m   j           =_  .:  '2   -+  /
    s⌃  n⌥  t3   h⌘  k           ,;  a⌘  e1   i⌥  c⌃
    f   p   d    l   x	Vol Vol	 `   u   o    y   b
    ←   →  app   ⇥   r⇧  ⌫   ⏎   ␣⇧  ⎋  num   ↑   ↓
*/

// top row
#define LT4 KC_V
#define LT3 KC_W
#define LT2 LT(_SYM, KC_G)
#define LT1 KC_M
#define LT0 KC_J

#define RT0 KC_EQL
#define RT1 KC_DOT
#define RT2 LT(_SYM, KC_QUOT)
#define RT3 KC_MINS
#define RT4 KC_SLSH

// middle row
#define LM4 LCTL_T(KC_S)
#define LM3 LALT_T(KC_N)
#define LM2 LT(_NAV, KC_T)
#define LM1 LGUI_T(KC_H)
#define LM0 KC_K

#define RM0 KC_COMM
#define RM1 RGUI_T(KC_A)
#define RM2 LT(_NUM, KC_E)
#define RM3 RALT_T(KC_I)
#define RM4 RCTL_T(KC_C)

// bottom row
#define LB4 KC_F
#define LB3 KC_P
#define LB2 KC_D
#define LB1 KC_L
#define LB0 KC_X
#define LB00 KC_VOLD

#define RB00 KC_VOLU
#define RB0 KC_GRV
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 KC_B

// thumb row
#define LH4 KC_LEFT
#define LH3 KC_RGHT
#define LH2 G(KC_TAB)
#define LH1 KC_TAB
#define LH0 LSFT_T(KC_R)
#define LH00 KC_BSPC

#define RH00 KC_ENT
#define RH0 RSFT_T(KC_SPC)
#define RH1 KC_ESC
#define RH2 TG(_NUM)
#define RH3 KC_UP
#define RH4 KC_DOWN

#define ___x___ KC_NO  // visual aid to null keys

#include "g/keymap_combo.h"

uint8_t  saved_mods = 0;
static uint16_t keyhold_timer; // for handling Qu combo


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/*  Hands Down Promethium
    v   w   g2   m   j           =_  .:  '2   -+  /
    s⌃  n⌥  t3   h⌘  k           ,;  a⌘  e1   i⌥  c⌃
    f   p   d    l   x	Vol Vol	 `   u   o    y   b
    ←   →  app   ⇥   r⇧  ⌫   ⏎   ␣⇧  ⎋  num   ↑   ↓
    */

  	[_DEF] = LAYOUT(
    LT4, LT3, LT2, LT1, LT0,             RT0, RT1, RT2, RT3, RT4,
    LM4, LM3, LM2, LM1, LM0,             RM0, RM1, RM2, RM3, RM4,
    LB4, LB3, LB2, LB1, LB0, LB00, RB00, RB0, RB1, RB2, RB3, RB4,
    LH4, LH3, LH2, LH1, LH0, LH00, RH00, RH0, RH1, RH2, RH3, RH4
    ),

    /*  BEAKL-19 numpad
    	-   5   2   3   :
    	7   .   1   0   4           ⌘   mo   ⌥	⌃
    	/   6   9   8   ,
    	    +   =   *   ␣   ⌫
    */
    [_NUM] = LAYOUT(
    KC_MINS, KC_5,    KC_2,    KC_3,    KC_COLN,                   _______, _______, _______, _______, _______,
    KC_7,    KC_DOT,  KC_1,    KC_0,    KC_4,                      _______, KC_RGUI, _______, KC_RALT, KC_RCTL,
    KC_SLSH, KC_6,    KC_9,    KC_8,    KC_COMM, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_PLUS, KC_EQL,  KC_ASTR, KC_SPC,  _______, _______, _______, _______, _______, _______, _______
    ),

    /* Getreur Symbols
    *
    *	`	<   >	-	|		    ^  	{   }   $   \
    *   !   *   /   =   &          	#   (   )   ;   "
    *   ~   +   [	]   %		    @ 	:   ,   .	'
    */
    [_SYM] = LAYOUT(
    KC_GRV,  KC_LABK, KC_RABK, KC_MINS, KC_PIPE,                   KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  KC_BSLS,
    KC_EXLM, KC_ASTR, KC_SLSH, KC_RPRN, KC_AMPR,                   KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQT,
	KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, _______, _______, KC_AT,   KC_COLN, KC_COMM, KC_DOT,  KC_QUOT,
    _______, _______, _______, _______, KC_SPC,  _______, _______, _______, _______, _______, _______, _______
    ),

    /*  BEAKL-19 symbols
    *       <   =   >   @   	^	[	_   ]
    *   \   (   -   )   +       %   {   ;   }	!
    *       *   :   /   #		$	&	~	|
    *                   ␣
    *
    [_SYM] = LAYOUT(
    ___x___, KC_LABK, KC_EQL,  KC_RABK, KC_AT,                     KC_CIRC, KC_LBRC, KC_UNDS, KC_RBRC, ___x___,
    KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,                   KC_PERC, KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM,
	___x___, KC_ASTR, KC_COLN, KC_SLSH, KC_HASH, _______, _______, KC_DLR,  KC_AMPR, KC_TILD, KC_PIPE, ___x___,
    _______, _______, _______, _______, KC_SPC,  _______, _______, _______, _______, _______, _______, _______
    ),
    */

    /*
                               Sclp  Scap                     vol+    home    up	end
    	⌃       ⌥       (mo)   ⌘     Sall        		      vol-    left    dn	rght    ⌦
    	undo   copy     cut    pst   redo                     mute    ←Sel    Sel→  ←line→
                                                              dsk-    dsk+
    */
    [_NAV] = LAYOUT(
    ___x___, ___x___, _______, C(S(G(KC_4))), LSG(KC_4),                   KC_VOLU,    G(KC_LEFT), KC_UP,   G(KC_RGHT), ___x___,
    KC_LCTL, KC_LALT, _______, KC_LGUI,       G(KC_A),                     KC_VOLD,    KC_LEFT,    KC_DOWN, KC_RGHT,    KC_DEL,
    G(KC_Z), G(KC_C), G(KC_X), G(KC_V),       LSG(KC_Z), _______, _______, KC_MUTE,    SELWBAK,    SELWORD, SELLINE,    ___x___,
    _______, _______, _______, _______,       _______,   _______, _______, C(KC_LEFT), C(KC_RGHT), _______, _______,    _______
    ),

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	    case LH0:
        case RH0:
            return TAPPING_TERM - 50;

    	//case LM4:
        //case LM3:
        //case LM2:
        //case LM1:
        //case RM1:
        //case RM2:
        //case RM3:
        //case RM4:
            //return TAPPING_TERM + 75;

        default:
            return TAPPING_TERM;
    }
};

/*
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LH0:
        case RH0:
            return true;    // Immediately select the hold action when another key is tapped.

        default:
            return false;   // Do not select the hold action when another key is tapped.
    }
};
*/

uint16_t get_tap_flow(
    uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {

    if (prev_keycode == KC_BSPC) {
        return 0;  // Disable filter when immediately following backspace.
    }

    switch (keycode) {
        case LSFT_T(KC_R):
        case RSFT_T(KC_SPC):
            return 0;  // Disable filter for these keys.

        default:
            return g_tap_flow_term;  // Longer timeout otherwise.
    }
};

// Handedness for Chordal Hold
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', '*', '*',  '*', '*', 'R', 'R', 'R', 'R'
    );

// program custom keycode functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case SS_Qu:  // send "qu" on tap
		    saved_mods = get_mods();
            if (record->event.pressed) {
                keyhold_timer = 0;
                register_code(KC_Q);

                if (!(saved_mods & (MOD_MASK_GUI + MOD_MASK_ALT + MOD_MASK_CTRL))) {// Only allow shift or caps
                    keyhold_timer = timer_read(); // time held, or since last pressed alone
                    clear_mods();
                    tap_code(KC_U);
                    set_mods(saved_mods);
                }
                return false; // handled it

            } else {
                unregister_code(KC_Q);
                if (timer_elapsed(keyhold_timer) > TAPPING_TERM) {
                    tap_code(KC_BSPC);
                }
                keyhold_timer = 0;
                return false; // handled it
            }
            return true;  // Didn't handle this
            break;

            case SELWBAK:  // Backward word selection.
            if (record->event.pressed) {
                select_word_register('B');
            } else {
                select_word_unregister();
            }
            break;

        case SELWORD:  // Forward word selection.
            if (record->event.pressed) {
                select_word_register('W');
            } else {
                select_word_unregister();
            }
            break;

        case SELLINE:  // Line selection.
            if(record->event.pressed) {
                select_word_register('L');
            } else {
                select_word_unregister();
            }
            break;
    }
    return true;
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_EQL, KC_UNDS},  // Shift = is _
    {KC_DOT , KC_COLN}, // Shift . is :
    {KC_MINS, KC_PLUS}, // Shift - is +
    {KC_COMM, KC_SCLN}, // Shift , is ;
    {KC_BSPC, KC_DEL},  // Shift ⌫ is ⌦
};
