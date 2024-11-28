
#include "keymap_us.h"
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"

enum layer_names {
    _DEF,
    _NUM,
    _SYM,
    _NAV
};

enum custom_keycodes {
    SS_Qu = SAFE_RANGE,
    SS_Prns
};

/*  KEY POSITION Names
    LN5 LN4 LN3 LN2 LN1 LN0     RN0 RN1 RN2 RN3 RN4 RN5
    LT5 LT4 LT3 LT2 LT1 LT0     RT0 RT1 RT2 RT3 RT4 RT5
    LM5 LM4 LM3 LM2 LM1 LM0     RM0 RM1 RM2 RM3 RM4 RM5
    LB5 LB4 LB3 LB2 LB1 LB0     RB0 RB1 RB2 RB3 RB4 RB5
                    LH1 LH0     RH0 RH1
*/

/*  Hands Down Promethium (canonical)
    ⎋   3   2@  1$   0#  4           7   6(  5() 9)  8  Cap
    ⇥   v   w   g    m   j           +=  .:  /   "!  '? `
    z   s   n⌥  t⌘   h⇧  k           ,;  a⇧  e⌘  i⌥  c  q
    tg  f⌃  p   d    l   x      	 -   u   o   y   b⌃ \
                         r   ⌫   ⏎   ␣
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
#define RN2 LT(0, KC_5)
#define RN3 KC_9
#define RN4 KC_8
#define RN5 KC_CAPS

// top row
#define LT5 KC_TAB
#define LT4 KC_V
#define LT3 KC_W
#define LT2 KC_G
#define LT1 KC_M
#define LT0 KC_J

#define RT0 KC_PLUS
#define RT1 KC_DOT
#define RT2 KC_SLSH
#define RT3 KC_DQUO
#define RT4 KC_QUOT
#define RT5 KC_GRV

// middle row
#define LM5 KC_Z
#define LM4 LT(_SYM, KC_S)
#define LM3 LALT_T(KC_N)
#define LM2 LGUI_T(KC_T)
#define LM1 LSFT_T(KC_H)
#define LM0 KC_K

#define RM0 KC_COMM
#define RM1 RSFT_T(KC_A)
#define RM2 RGUI_T(KC_E)
#define RM3 RALT_T(KC_I)
#define RM4 LT(_SYM, KC_C)
#define RM5 KC_Q

// bottom row
#define LB5 TG(_NUM)
#define LB4 LCTL_T(KC_F)
#define LB3 KC_P
#define LB2 KC_D
#define LB1 KC_L
#define LB0 KC_X

#define RB0 KC_MINS
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 RCTL_T(KC_B)
#define RB5 KC_BSLS

// thumb row
#define LH1 LT(_NAV, KC_R)
#define LH0 KC_BSPC

#define RH0 KC_ENT
#define RH1 LT(_NUM, KC_SPC)

#define ___x___ KC_NO  // visual aid to null keys

#include "g/keymap_combo.h"

uint8_t  saved_mods = 0;
static uint16_t keyhold_timer; // for handling Qu combo


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*  Hands Down Promethium (canonical)
    ⎋   3   2@  1$   0#  4           7   6(  5() 9)  8  Cap
    ⇥   v   w   g    m   j           +=  .:  /   "!  '? `
    z   s   n⌥  t⌘   h⇧  k           ,;  a⇧  e⌘  i⌥  c  q
    tg  f⌃  p   d    l   x      	 -   u   o   y   b⌃ \
                         r   ⌫   ⏎   ␣
  */
  [_DEF] = LAYOUT_voyager(
    LN5, LN4, LN3, LN2, LN1, LN0,           RN0, RN1, RN2, RN3, RN4, RN5,
    LT5, LT4, LT3, LT2, LT1, LT0,           RT0, RT1, RT2, RT3, RT4, RT5,
    LM5, LM4, LM3, LM2, LM1, LM0,           RM0, RM1, RM2, RM3, RM4, RM5,
    LB5, LB4, LB3, LB2, LB1, LB0,           RB0, RB1, RB2, RB3, RB4, RB5,
                             LH1, LH0, RH0, RH1
  ),

 /*	BEAKL-19 Numpad
			+	/	*	=
    ⇥   -   5   2   3   :
        7   .   1   0   4       	,   ⇧   ⌘   ⌥	⌃
        ,   6   9   8   ⏎       	-
    	                ␣   ⌫   ⏎   mo
  */
  [_NUM] = LAYOUT_voyager(
    _______, _______, KC_PLUS, KC_SLSH, KC_ASTR, KC_EQL,                    _______, _______, _______, _______, _______, _______,
    _______, KC_MINS, KC_5,    KC_2,    KC_3,    KC_COLN,                   _______, _______, _______, _______, _______, _______,
    _______, KC_7,    KC_DOT,  KC_1,    KC_0,    KC_4,                      _______, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, ___x___,
    _______, KC_COMM, KC_6,    KC_9,    KC_8,    KC_ENT,                    _______, ___x___, ___x___, ___x___, ___x___, _______,
                                                 KC_SPC,  _______, _______, _______
  ),

  /* BEAKL Symbols
    *		@	$	#					~	^	`
    *		<   =	>			       	[   _   ]
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
    	       ⌘Q      Scap    Sclp                            vol+    home    up	end             F12
    	⌃      ⌥       ⌘       ⇧             		           vol-    left    dn	rght	del
    	undo   cut     cpy     pst    redo                     mute     ⌫      ⇥     ⏎
                                                               dsk-    dsk+
  */
  [_NAV] = LAYOUT_voyager(
    _______, KC_F1,   KC_F2,   KC_F3,     KC_F4,         KC_F5,                          KC_F6,   KC_F7,      KC_F8,   KC_F9,      KC_F10,  KC_F11,
    _______, ___x___, G(KC_Q), LSG(KC_4), C(S(G(KC_4))), ___x___,                        KC_VOLU, G(KC_LEFT), KC_UP,   G(KC_RGHT), ___x___, KC_F12,
    ___x___, KC_LCTL, KC_LALT, KC_LGUI,   KC_LSFT,       ___x___,                        KC_VOLD, KC_LEFT,    KC_DOWN, KC_RGHT,    KC_DEL,  ___x___,
    ___x___, G(KC_Z), G(KC_X), G(KC_C),   G(KC_V),       LSG(KC_Z),                      KC_MUTE, KC_BSPC,    KC_TAB,  KC_ENT,     ___x___, ___x___,
                                                         _______,   _______, C(KC_LEFT), C(KC_RIGHT)
  )

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


// program custom keycode functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_custom_shift_keys(keycode, record)) { return false; }

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

        case RN2:
            // Unmatched return on tap
            if (record->tap.count) { return true; }
            // Send macro string on hold
            else if (record->event.pressed) { SEND_STRING("()" SS_TAP(X_LEFT)); }
            return false;
    }
    return true;
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_1,    KC_DLR},  /* shift 1 is $ */
    {KC_0,    KC_HASH}, /* shift 0 is # */
    {KC_6,    KC_LPRN}, /* shift 6 is ( */
    {KC_9,    KC_RPRN}, /* shift 9 is ) */
    {KC_DOT,  KC_COLN}, /* shift . is : */
    {KC_COMM, KC_SCLN}, /* shift , is ; */
    {KC_SLSH, KC_ASTR}, /* shift / is * */
    {KC_DQUO, KC_EXLM}, /* shift " is ! */
    {KC_QUOT, KC_QUES}, /* shift ' is ? */
	{KC_BSPC, KC_DEL},  /* shift ⌫ is ⌦ */
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);
