#pragma once

#include QMK_KEYBOARD_H
#include "version.h"

enum layer_names {
    _DEF,
    _NUM,
    _SYM,
    _NAV,
    _SNTH,
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
    LN5 LN4 LN3 LN2 LN1 LN0     RN0 RN1 RN2 RN3 RN4 RN5
    LT5 LT4 LT3 LT2 LT1 LT0     RT0 RT1 RT2 RT3 RT4 RT5
    LM5 LM4 LM3 LM2 LM1 LM0     RM0 RM1 RM2 RM3 RM4 RM5
    LB5 LB4 LB3 LB2 LB1 LB0     RB0 RB1 RB2 RB3 RB4 RB5
                    LH1 LH0     RH0 RH1
*/

/*  Base (alpha) Layer Hands Down Vibranuim-F
            Building for ZSA Voyager
    ⎋           ⇥        tg          tg  (   ⌦    )   vol↓↑
    `   x   w   m⌃   g   j           +=  .:  /⌃   "!  '? \
    z   s   c⌥  n⌘   t⇧  k           ,;  a⇧  e⌘   i⌥  h  q
        f   p   l    d   v      	 -   u   o    y   b
                         r   ⌫   ⏎   ␣
*/

// Num row
#define LN5 KC_ESC
#define LN4 KC_NO
#define LN3 KC_NO
#define LN2 KC_TAB
#define LN1 KC_NO
#define LN0 TO(_SNTH)

#define RN0 TG(_NUM)
#define RN1 KC_LPRN
#define RN2 KC_DEL
#define RN3 KC_RPRN
#define RN4 KC_VOLD
#define RN5 KC_VOLU

// top row
#define LT5 KC_GRV
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
#define RT5 KC_BSLS

// middle row
#define LM5 KC_Z
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
#define RM5 KC_Q

// bottom row
#define LB5 KC_NO
#define LB4 KC_F
#define LB3 KC_P
#define LB2 KC_L
#define LB1 KC_D
#define LB0 KC_V

#define RB0 KC_MINS
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 KC_B
#define RB5 KC_NO

// thumb row
#define LH1 LT(_NAV, KC_R)
#define LH0 KC_BSPC

#define RH0 KC_ENT
#define RH1 LT(_NUM, KC_SPC)

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
  /*  Base (alpha) Layer Hands Down Vibranuim-F
            Building for ZSA Voyager
    ⎋           ⇥        tg          tg  (   ⌦   )   vol↓↑
    `   x   w   m⌃   g   j           +=  .:  /⌃  "!  '? \
    z   s   c⌥  n⌘   t⇧  k           ,;  a⇧  e⌘  i⌥  h  q
        f   p   l    d   v      	 -   u   o   y   b
                         r   ⌫   ⏎   ␣
  */
  [_DEF] = LAYOUT_voyager(
    LN5, LN4, LN3, LN2, LN1, LN0,   RN0, RN1, RN2, RN3, RN4, RN5,
    LT5, LT4, LT3, LT2, LT1, LT0,   RT0, RT1, RT2, RT3, RT4, RT5,
    LM5, LM4, LM3, LM2, LM1, LM0,   RM0, RM1, RM2, RM3, RM4, RM5,
    LB5, LB4, LB3, LB2, LB1, LB0,   RB0, RB1, RB2, RB3, RB4, RB5,
    LH1, LH0, RH0, RH1
  ),

  /*        ⇥  					tg
    *   7   8   9   -       	+   .   ⌃
    /   1   2   3   +       	,   ⇧   ⌘   ⌥
    ,   4   5   6   =       	-   ⌫
    	                0   .   ⏎   ␣
  */
  [_NUM] = LAYOUT_voyager(
    _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
    _______, KC_ASTR, KC_7,    KC_8,    KC_9,    KC_MINS,                  _______, _______, KC_RCTL, _______, _______, ___x___,
    _______, KC_SLSH, KC_1,    KC_2,    KC_3,    KC_PLUS,                  _______, KC_RSFT, KC_RGUI, KC_RALT, _______, ___x___,
    _______, KC_COMM, KC_4,    KC_5,    KC_6,    KC_EQL,                   ___x___, KC_BSPC, KC_TAB,  KC_ENT,  ___x___, _______,
                                                 KC_0,    KC_DOT, _______, _______
  ),

  /* Pascal Getreuer Mod
    *
    *		<   >	@			       &   [   ]
    *   !   -   +   =   `          \   :   (   )   ?
    *   ^   /   *   #   ~		   |   $   {   }   %
  */
  [_SYM] = LAYOUT_voyager(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, QK_BOOT,
    _______, ___x___, KC_LABK, KC_RABK, KC_AT,   ___x___,                   ___x___, KC_AMPR, KC_LBRC, KC_RBRC, ___x___, _______,
    _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_GRV,                    KC_BSLS, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES, _______,
    _______, KC_CIRC, KC_SLSH, KC_ASTR, KC_HASH, KC_TILD,                   KC_PIPE, KC_DLR,  KC_LCBR, KC_RCBR, KC_PERC, _______,
                                                 _______, _______, _______, _______
  ),

  /*    F1     F2      F3	   F4	  F5			           F6	   F7	   F8	F9	    F10	    F11
    	       ⌘Q      ⌃       Sclp   Scap                     vol+    home    up	end             F12
    	       ⌥       ⌘       ⇧             		           vol-    left    dn	rght	del
    	undo   cut     cpy     pst    redo                     mute     ⌫      ⇥     ⏎
                                                               dsk-    dsk+
  */
  [_NAV] = LAYOUT_voyager(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,         KC_F5,                          KC_F6,   KC_F7,      KC_F8,   KC_F9,      KC_F10,  KC_F11,
    ___x___, ___x___, G(KC_Q), KC_LCTL, C(S(G(KC_4))), LSG(KC_4),                      KC_VOLU, G(KC_LEFT), KC_UP,   G(KC_RGHT), ___x___, KC_F12,
    _______, _______, KC_LALT, KC_LGUI, KC_LSFT,       ___x___,                        KC_VOLD, KC_LEFT,    KC_DOWN, KC_RGHT,    KC_DEL,  ___x___,
    _______, G(KC_Z), G(KC_X), G(KC_C), G(KC_V),       LSG(KC_Z),                      KC_MUTE, KC_BSPC,    KC_TAB,  KC_ENT,     ___x___, ___x___,
                                                         _______, _______, C(KC_LEFT), C(KC_RIGHT)
  ),

  /*  Base (alpha) Layer SNTH
    ⎋           ⇥        tg              (   ⌦   )   vol↓↑
    `   x   p   d⌃   m   q           =   y   o⌃  u!  .  \
    z   s   n⌥  t⌘   h⇧  v           g   c⇧  a⌘  e⌥  i  q
        f   b   k    l   j      	 z   w   '   /   ,
                         r   ⌫   ⏎   ␣
  */
  [_SNTH] = LAYOUT_voyager(
    _______, _______,        _______,      _______,      _______,      TO(_DEF), 					_______, _______,      _______,      _______,      _______,        _______,
    _______, KC_X,           KC_P,         LCTL_T(KC_D), KC_M,         KC_Q,     					KC_EQL,  KC_Y,         RCTL_T(KC_O), KC_U,         KC_DOT,         _______,
    _______, LT(_SYM, KC_S), LALT_T(KC_N), LGUI_T(KC_T), LSFT_T(KC_H), KC_V,     					KC_G,    RSFT_T(KC_C), RGUI_T(KC_A), RALT_T(KC_E), LT(_SYM, KC_I), _______,
    ___x___, KC_F,           KC_B,         KC_K,         KC_L,         KC_J,     					KC_Z,    KC_W,         KC_QUOT,      KC_SLSH,      KC_COMM,        ___x___,
                                                                       _______,  _______,  _______, _______
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
                tap_code(KC_S); // send "C" honouring caps
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
    }
    return true;
};

// Key overrides
const key_override_t plus_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_PLUS, KC_EQL);	/* shift + is = */
const key_override_t dot_key_override = ko_make_basic(MOD_MASK_SHIFT,  KC_DOT, KC_COLN);	/* shift . is : */
const key_override_t comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);	/* shift , is ; */
const key_override_t slsh_key_override = ko_make_basic(MOD_MASK_SHIFT, RT2, KC_ASTR);	    /* shift / is * */
const key_override_t bsls_key_override = ko_make_basic(MOD_MASK_ALT,   RT2, KC_BSLS);		/* alt   / is \ */
const key_override_t dquo_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DQUO, KC_QUES);	/* shift " is ? */
const key_override_t quot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_EXLM);	/* shift ' is ! */
const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);	/* shift ⌫ is ⌦ */

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &plus_key_override,
    &dot_key_override,
    &comm_key_override,
    &slsh_key_override,
    &bsls_key_override,
    &dquo_key_override,
    &quot_key_override,
    &bspc_key_override,
};
