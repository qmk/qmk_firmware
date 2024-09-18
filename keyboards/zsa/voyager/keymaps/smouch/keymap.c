#pragma once

#include QMK_KEYBOARD_H
#include "version.h"
#include "keycodes.h"
#include "features/custom_shift_keys.h"
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
