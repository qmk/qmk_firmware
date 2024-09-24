// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"

enum layer_names {
    _DEF,
    _NUM,
    _SYM,
    _NAV,
};

enum custom_keycodes {
    SS_Qu,
    SS_Th,
    SS_Ch,
    SS_Sh,
    SS_Gh,
    SS_Wh,
    SS_Ph,
};

/*  KEY POSITION Names

    LT4 LT3 LT2 LT1 LT0           RT0 RT1 RT2 RT3 RT4
    LM4 LM3 LM2 LM1 LM0           RM0 RM1 RM2 RM3 RM4
    LB4 LB3 LB2 LB1 LB0 LB00 RB00 RB0 RB1 RB2 RB3 RB4
    LH4 LH3 LH2 LH1 LH0 LH00 RH00 RH0 RH1 RH2 RH3 RH4
*/

/*  Base (alpha) Layer Hands Down Vibranuim-F
            Building for Atreus44

    x   w   m⌃   g   j           +=  .:  /⌃   "!  '?
    s   c⌥  n⌘   t⇧  k           ,;  a⇧  e⌘   i⌥  h
    f   p   l    d   v	 `   \	 -   u   o    y   b
    ←   →  app   ⇥   r   ⌫   ⏎   ␣   ⎋  num   ↑   ↓
*/

// top row
#define LT4 KC_X
#define LT3 KC_W
#define LT2 LCTL_T(KC_M)
#define LT1 KC_G
#define LT0 KC_J

#define RT0 KC_PLUS
#define RT1 KC_DOT
#define RT2 RCTL_T(KC_SLSH)
#define RT3 KC_DQUO
#define RT4 KC_QUOT

// middle row
#define LM4 LT(_SYM, KC_S)
#define LM3 LALT_T(KC_C)
#define LM2 LGUI_T(KC_N)
#define LM1 LSFT_T(KC_T)
#define LM0 KC_K

#define RM0 KC_COMM
#define RM1 RSFT_T(KC_A)
#define RM2 RGUI_T(KC_E)
#define RM3 RALT_T(KC_I)
#define RM4 LT(_SYM, KC_H)

// bottom row
#define LB4 KC_F
#define LB3 KC_P
#define LB2 KC_L
#define LB1 KC_D
#define LB0 KC_V
#define LB00 KC_GRV

#define RB00 KC_BSLS
#define RB0 KC_MINS
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 KC_B

// thumb row
#define LH4 KC_LEFT
#define LH3 KC_RGHT
#define LH2 G(KC_TAB)
#define LH1 KC_TAB
#define LH0 LT(_NAV, KC_R)
#define LH00 KC_BSPC

#define RH00 KC_ENT
#define RH0 LT(_NUM, KC_SPC)
#define RH1 KC_ESC
#define RH2 TG(_NUM)
#define RH3 KC_UP
#define RH4 KC_DOWN

#define ___x___ KC_NO  // visual aid to null keys

// layer momentaries
// #define OS_SYM OSL(_SYM)

// layer tap
// #define SPC_NUM LT(_NUM, KC_SPC)
// #define R_NAV LT(_NAV, KC_R)
// #define ENT_SYM LT(_SYM, KC_ENT)
// #define MY_PRNS LT(0, KC_1)

// One Shots
// #define OSMSFT OSM(MOD_LSFT)
// #define OSMCMD OSM(MOD_LGUI)
// #define OSMOPT OSM(MOD_LALT)
// #define OSMCTL OSM(MOD_LCTL)

#include "g/keymap_combo.h"

uint8_t  saved_mods = 0;
static uint16_t keyhold_timer; // for handling Qu combo


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/*
        x   w   m⌃   g   j           +=  .:  /⌃   "!  '?
        s   c⌥  n⌘   t⇧  k           ,;  a⇧  e⌘   i⌥  h
        f   p   l    d   v	 `   \	 -   u   o    y   b
        ←   →  app   ⇥   r   ⌫   ⏎   ␣   ⎋  num   ↑   ↓
    */

  	[_DEF] = LAYOUT(
    LT4, LT3, LT2, LT1, LT0,             RT0, RT1, RT2, RT3, RT4,
    LM4, LM3, LM2, LM1, LM0,             RM0, RM1, RM2, RM3, RM4,
    LB4, LB3, LB2, LB1, LB0, LB00, RB00, RB0, RB1, RB2, RB3, RB4,
    LH4, LH3, LH2, LH1, LH0, LH00, RH00, RH0, RH1, RH2, RH3, RH4
    ),

    /*
    	*   7   8   9   -       +   .   ^
    	/   1   2   3   +       ,   ⇧   ⌘   ⌥
    	,   4   5   6   =       -   ⌫   ⇥   ⏎
    	←   →       .   0   ␣
    */
    [_NUM] = LAYOUT(
    KC_ASTR, KC_7,    KC_8,    KC_9,    KC_MINS,                   _______, _______, KC_RCTL, _______, _______,
    KC_SLSH, KC_1,    KC_2,    KC_3,    KC_PLUS,                   _______, KC_RSFT, KC_RGUI, KC_RALT, _______,
    KC_COMM, KC_4,    KC_5,    KC_6,    KC_EQL,  _______, _______, _______, KC_BSPC, KC_TAB,  KC_ENT,  _______,
    _______, _______, _______, KC_DOT,  KC_0,    KC_SPC,  _______, _______, _______, _______, _______, _______
    ),

    /*
    *       <   >   @      			&	[   ]
    *   !   -   +   =   `       \   :   (   )	?
    *   ⌃   /   *   #   ~		|	$	{	}	%
    */
    [_SYM] = LAYOUT( // Pascal Getreuer Mod
    ___x___, KC_LABK, KC_RABK, KC_AT,   ___x___,                   ___x___, KC_AMPR, KC_LBRC, KC_RBRC, ___x___,
    KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_GRV,                    KC_BSLS, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES,
    KC_CIRC, KC_SLSH, KC_ASTR, KC_HASH, KC_TILD, _______, _______, KC_PIPE, KC_DLR,  KC_LCBR, KC_RCBR, KC_PERC,
    _______, _______, _______, _______, KC_SPC,  _______, _______, _______, _______, _______, _______, _______
    ),

    /*
               ⌘Q      ⌃       Sclp   Scap                     vol+    home    up	end
    	       ⌥       ⌘       ⇧             		           vol-    left    dn	rght	del
    	undo   cut     cpy     pst    redo                     mute     ⌫      ⇥     ⏎
                                                               dsk-    dsk+
    */
    [_NAV] = LAYOUT(
    ___x___, G(KC_Q), KC_LCTL, C(S(G(KC_4))), LSG(KC_4),                   KC_VOLU,    G(KC_LEFT), KC_UP,   G(KC_RGHT), ___x___,
    _______, KC_LALT, KC_LGUI, KC_LSFT,       G(KC_A),                     KC_VOLD,    KC_LEFT,    KC_DOWN, KC_RGHT,    KC_DEL,
    G(KC_Z), G(KC_X), G(KC_C), G(KC_V),       LSG(KC_Z), _______, _______, KC_MUTE,    KC_BSPC,	   KC_TAB,  KC_ENT,     ___x___,
    _______, _______, _______, _______,       _______,   _______, _______, C(KC_LEFT), C(KC_RGHT), _______, _______,    _______
    ),

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	    case LM1:
        case RM1:
            return TAPPING_TERM - 25;

    	case LB4:
        case LM3:
        case LM2:
        case RM2:
        case RM3:
        case RB4:
            return TAPPING_TERM + 75;

        default:
            return TAPPING_TERM;
    }
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LM1:
        case RM1:
            return true;    // Immediately select the hold action when another key is tapped.

        default:
            return false;   // Do not select the hold action when another key is tapped.
    }
};

void add_h_digragh(void) {
    unregister_mods(MOD_MASK_SHIFT);
    tap_code(KC_H); // send "h" honouring CAPSLK state
};

// program custom keycode functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_custom_shift_keys(keycode, record)) { return false; }

    switch (keycode) {
        case SS_Qu:  // send "qu" if held
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

     // the H digraphs
        case SS_Th:
            if (record->event.pressed) {
                tap_code(KC_T); // send "T" honouring caps
			    add_h_digragh();
            }
            break;
        case SS_Ch:
            if (record->event.pressed) {
                tap_code(KC_C); // send "C" honouring caps
                add_h_digragh();
            }
            break;
        case SS_Sh:
            if (record->event.pressed) {
                tap_code(KC_S); // send "S" honouring caps
                add_h_digragh();
            }
            break;
        case SS_Gh:
            if (record->event.pressed) {
                tap_code(KC_G); // send "G" honouring caps
                add_h_digragh();
            }
            break;
        case SS_Wh:
            if (record->event.pressed) {
                tap_code(KC_W); // send "W" honouring caps
                add_h_digragh();
            }
            break;
        case SS_Ph:
            if (record->event.pressed) {
                tap_code(KC_P); // send "P" honouring caps
                add_h_digragh();
            }
            break;
        /* case SS_Prns:
            if (record->event.pressed) {
            	SEND_STRING("()"SS_TAP(X_LEFT));
            }
            break;
        case MY_PRNS:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LPRN); // send "(" on tap
            } else if (record->event.press) {c∑∑∑∑∑∑∑
                tap_code16(KC_RPRN); // send ")" on hold
            }
            return false; */
    }
    return true;
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_PLUS, KC_EQL},	/* shift + is = */
    {KC_DOT, KC_COLN},  /* shift . is : */
    {KC_COMM, KC_SCLN}, /* shift , is ; */
    {RCTL_T(KC_SLSH), KC_ASTR}, /* shift / is * */
    {KC_DQUO, KC_EXLM}, /* shift " is ! */
    {KC_QUOT, KC_QUES}, /* shift ' is ? */
	{KC_BSPC, KC_DEL},  /* shift ⌫ is ⌦ */
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(*custom_shift_keys);
