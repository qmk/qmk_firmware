
#include "keycodes.h"
#include "keymap_us.h"
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
#include "features/select_word.h"

enum layer_names {
    _DEF,
    _NUM,
    _SYM,
    _NAV
};

enum custom_keycodes {
    SS_Qu = SAFE_RANGE,
    SELWBAK,
    SELWFWD,
    SELLINE,
};

/*  KEY POSITION Names
    LN5 LN4 LN3 LN2 LN1 LN0     RN0 RN1 RN2 RN3 RN4 RN5
    LT5 LT4 LT3 LT2 LT1 LT0     RT0 RT1 RT2 RT3 RT4 RT5
    LM5 LM4 LM3 LM2 LM1 LM0     RM0 RM1 RM2 RM3 RM4 RM5
    LB5 LB4 LB3 LB2 LB1 LB0     RB0 RB1 RB2 RB3 RB4 RB5
                    LH1 LH0     RH0 RH1
*/

/*  Hands Down Promethium (canonical)
    ⎋   3   2@  1$   0#  4           7   6   5   9   8  CW
    ⇥   v   w   g2   m   j           /   .:  =2  -   '  `
    z   s⌃  n⌥  t3   h⌘  k           ,;  a⌘  e1  i⌥  c⌃ q
    tg  f   p   d    l   x      	 ;   u   o   y   b  \
                         r⇧  ⌫   ⏎   ␣⇧
  */

// Num row
#define LN5 KC_ESC
#define LN4 KC_3
#define LN3 KC_2
#define LN2 KC_1
#define LN1 KC_0
#define LN0 KC_4

#define RN0 KC_7
#define RN1 KC_6
#define RN2 KC_5
#define RN3 KC_9
#define RN4 KC_8
#define RN5 CW_TOGG

// top row
#define LT5 KC_TAB
#define LT4 KC_V
#define LT3 KC_W
#define LT2 LT(_SYM, KC_G)
#define LT1 KC_M
#define LT0 KC_J

#define RT0 KC_SLSH
#define RT1 KC_DOT
#define RT2 LT(_SYM, KC_EQL)
#define RT3 KC_MINS
#define RT4 KC_QUOT
#define RT5 KC_GRV

// middle row
#define LM5 KC_Z
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
#define RM5 KC_Q

// bottom row
#define LB5 TG(_NUM)
#define LB4 KC_F
#define LB3 KC_P
#define LB2 KC_D
#define LB1 KC_L
#define LB0 KC_X

#define RB0 KC_SCLN
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 KC_B
#define RB5 KC_BSLS

// thumb row
#define LH1 LSFT_T(KC_R)
#define LH0 KC_BSPC

#define RH0 KC_ENT
#define RH1 RSFT_T(KC_SPC)

#define ___x___ KC_NO  // visual aid to null keys

#include "g/keymap_combo.h"

uint8_t  saved_mods = 0;
static uint16_t keyhold_timer; // for handling Qu combo


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*  Hands Down Promethium
    ⎋   3   2@  1$   0#  4           7   6   5   9   8  CW
    ⇥   v   w   g2   m   j           /   .:  =2  -   '  `
    z   s⌃  n⌥  t3   h⌘  k           ,;  a⌘  e1  i⌥  c⌃ q
    tg  f   p   d    l   x      	 ;   u   o   y   b  \
                         r⇧   ⌫   ⏎   ␣⇧
  */
  [_DEF] = LAYOUT_voyager(
    LN5, LN4, LN3, LN2, LN1, LN0,           RN0, RN1, RN2, RN3, RN4, RN5,
    LT5, LT4, LT3, LT2, LT1, LT0,           RT0, RT1, RT2, RT3, RT4, RT5,
    LM5, LM4, LM3, LM2, LM1, LM0,           RM0, RM1, RM2, RM3, RM4, RM5,
    LB5, LB4, LB3, LB2, LB1, LB0,           RB0, RB1, RB2, RB3, RB4, RB5,
                             LH1, LH0, RH0, RH1
  ),

 /*	BEAKL-19 Numpad
			+	=	*
    ⇥   -   5   2   3   :
        7   .   1   0   4       	,   ⌘  (mo)  ⌥	 ⌃
        /   6   9   8   ,       	-
    	                ␣   ⌫   ⏎   ␣⇧
  */
  [_NUM] = LAYOUT_voyager(
    _______, _______, KC_PLUS, KC_EQL,  KC_ASTR, _______,                   _______, _______, _______, _______, _______, _______,
    _______, KC_MINS, KC_5,    KC_2,    KC_3,    KC_COLN,                   _______, _______, _______, _______, _______, _______,
    _______, KC_7,    KC_DOT,  KC_1,    KC_0,    KC_4,                      _______, KC_RGUI, _______, KC_RALT, KC_RCTL, ___x___,
    _______, KC_SLSH, KC_6,    KC_9,    KC_8,    KC_COMM,                   _______, ___x___, ___x___, ___x___, ___x___, _______,
                                                 KC_SPC,  _______, _______, _______
  ),

  /* BEAKL-19 Symbols
    *		@	$	#					~	^	`
    *       <   =   >                   [   _   ]
    *   \   (   -   )   +          	%   {   ;   }   !
    *       *   :	/   		      	&   ~   |
  */
  [_SYM] = LAYOUT_voyager(
    _______, _______, KC_AT,   KC_DLR,  KC_HASH, _______,                   _______, KC_TILD, KC_CIRC, KC_GRV,  _______, QK_BOOT,
    _______, ___x___, KC_LABK, KC_EQL,  KC_RABK, ___x___,                   ___x___, KC_LBRC, KC_UNDS, KC_RBRC, ___x___, _______,
    _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,                   KC_PERC, KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM, _______,
    _______, ___x___, KC_ASTR, KC_COLN, KC_SLSH, ___x___,                   ___x___, KC_AMPR, KC_TILD, KC_PIPE, ___x___, _______,
                                                 KC_SPC,  _______, _______, _______
  ),

  /*    F1     F2      F3	   F4	  F5			           F6	   F7	   F8	F9	    F10	    F11
    	       quit            Sclp   Scap                     vol+    home    up	end             F12
    	⌃      ⌥       (mo)     ⌘     SelAll       		       vol-    left    dn	rght	del
    	undo   cpy             pst    redo                     mute    Wrd←   Wrd→  Line
                                        ⇧                      dsk-    dsk+
  */
  [_NAV] = LAYOUT_voyager(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,         KC_F5,                          KC_F6,   KC_F7,      KC_F8,   KC_F9,      KC_F10,  KC_F11,
    _______, ___x___, G(KC_Q), _______, C(S(G(KC_4))), LSG(KC_4),                      KC_VOLU, G(KC_LEFT), KC_UP,   G(KC_RGHT), ___x___, KC_F12,
    ___x___, KC_LCTL, KC_LALT, _______, KC_LGUI,       G(KC_A),                        KC_VOLD, KC_LEFT,    KC_DOWN, KC_RGHT,    KC_DEL,  ___x___,
    ___x___, G(KC_Z), G(KC_C), G(KC_X), G(KC_V),       LSG(KC_Z),                      KC_MUTE, SELWBAK,    SELWFWD, SELLINE,    ___x___, ___x___,
                                                       KC_LSFT,   _______, C(KC_LEFT), C(KC_RGHT)
  ),

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	    case LH1:
        case RH1:
            return TAPPING_TERM - 25;

    	case LM4:
        case LM3:
        case LM2:
        case LM1:
        case RM1:
        case RM2:
        case RM3:
        case RM4:
            return TAPPING_TERM + 75;

        default:
            return TAPPING_TERM;
    }
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LH1:
        case RH1:
            return true;    // Immediately select the hold action when another key is tapped.

        default:
            return false;   // Do not select the hold action when another key is tapped.
    }
};

char chordal_hold_handedness(keypos_t key) {
    if (key.col == 0 || key.col == MATRIX_COLS - 1) {
        return '*';  // Exempt the outer columns.
    }
    // On split keyboards, typically, the first half of the rows are on the
    // left, and the other half are on the right.
    return key.row < MATRIX_ROWS / 2 ? 'L' : 'R';
};


// program custom keycode functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_custom_shift_keys(keycode, record)) { return false; }
    if (!process_select_word(keycode, record)) { return false; }

    switch (keycode) {
        case SS_Qu:  // send "qu" on tap, bspc "u" if held
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

        case SELWFWD:  // Forward word selection.
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
    {KC_1,    KC_DLR},  /* shift 1 is $ */
    {KC_0,    KC_HASH}, /* shift 0 is # */
    {KC_DOT,  KC_COLN}, /* shift . is : */
    {KC_COMM, KC_SCLN}, /* shift , is ; */
    /* {LT(_SYM, KC_SLSH), KC_ASTR},  shift / is * */
    /* {KC_DQUO, KC_EXLM},  shift " is ! */
    /* {KC_QUOT, KC_QUES},  shift ' is ? */
	{KC_BSPC, KC_DEL},  /* shift ⌫ is ⌦ */
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);
