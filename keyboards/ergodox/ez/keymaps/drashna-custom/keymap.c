#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"

// Define layer names 
#define BASE 0
#define SYMB 1
#define OVERWATCH 2
#define DIABLO 3
#define MOUS 4

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))


#define M_VERSION M(0)
#define M_SYMM M(1)
#define M_SALT M(2)
#define M_HARD M(3)
#define M_MAKE M(4)
#define M_COVECUBE M(5)
#define M_MORESALT M(6)
#define M_DOOMFIST M(7)



bool skip_leds = false;
bool has_layer_changed = false;
static uint8_t current_layer;

static uint16_t key_timer;
static uint16_t diablo_timer[4];
static uint8_t diablo_times[] = {0, 1, 3, 5, 10};
static uint8_t diablo_key_time[4];

bool check_dtimer(uint8_t dtimer) {
    // has the correct number of seconds elapsed (as defined by diablo_times)
    return (timer_elapsed(diablo_timer[dtimer]) < ( diablo_key_time[dtimer] * 1000 ) ) ? false : true;
};

bool checktime(void){
    return (timer_elapsed(key_timer) < 150) ? true : false;
};


enum custom_keycodes {
	PLACEHOLDER = SAFE_RANGE, // can always be here
	EPRM,
	VRSN,
	RGB_SLD,
	RGB_0000FF,
	RGB_008000,
	RGB_FF0000,
	RGB_800080,
	RGB_00FF90,
    KC_DIABLO_CLEAR
};

#ifdef TAP_DANCE_ENABLE
enum {
	TD_ESC_CAPS = 0,
	TD_SPACE,
	TD_DIABLO_J,
	TD_CLN,
	TD_EGG,
	TD_FLSH,
	TD_DIABLO_1,
	TD_DIABLO_2,
	TD_DIABLO_3,
	TD_DIABLO_4
};



void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code (KC_RSFT);
		register_code (KC_SCLN);
	} else {
		register_code (KC_SCLN);
	}
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		unregister_code (KC_RSFT);
		unregister_code (KC_SCLN);
	} else {
		unregister_code (KC_SCLN);
	}
}

void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
	if (state->count >= 10) {
		SEND_STRING ("Safety dance!");
		reset_tap_dance (state);
	}
}

// on each tap, light up one led, from right to left
// on the forth tap, turn them off from right to left
void dance_flsh_each(qk_tap_dance_state_t *state, void *user_data) {
	if (!skip_leds) {
		ergodox_board_led_off();
		ergodox_right_led_1_off();
		ergodox_right_led_2_off();
		ergodox_right_led_3_off();
		skip_leds = true;
	}
	switch (state->count) {
		case 1:
			ergodox_right_led_3_on();
            break;
        case 2:
			ergodox_right_led_2_on();
			break;
		case 3:
			ergodox_right_led_1_on();
			break;
		case 4:
			ergodox_right_led_3_off();
			_delay_ms(50);
			ergodox_right_led_2_off();
			_delay_ms(50);
			ergodox_right_led_1_off();

	}
}

// on the fourth tap, set the keyboard on flash state
void dance_flsh_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count >= 4) {
#ifdef LAYER_UNDERGLOW_LIGHTING
        rgblight_enable();
        rgblight_mode(1);
        rgblight_setrgb(0xff,0x00,0x00);
#endif
		reset_keyboard();
		reset_tap_dance(state);
	}
}

void diablo_tapdance_master (qk_tap_dance_state_t *state, void *user_data, uint8_t diablo_key) {
    if (state->count >= 6) {
        diablo_key_time[diablo_key] = diablo_times[0];
        reset_tap_dance(state);
    } else {
        diablo_key_time[diablo_key] = diablo_times[state->count - 1];
    }
}

void diablo_tapdance1 (qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master (state, user_data, 0);
}

void diablo_tapdance2 (qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master (state, user_data, 1);
}

void diablo_tapdance3 (qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master (state, user_data, 2);
}

void diablo_tapdance4 (qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master (state, user_data, 3);
}


// if the flash state didnt happen, then turn off leds, left to right
void dance_flsh_reset(qk_tap_dance_state_t *state, void *user_data) {
	_delay_ms(200);
	ergodox_right_led_1_off();
	_delay_ms(200);
	ergodox_right_led_2_off();
	_delay_ms(200);
	ergodox_right_led_3_off();
	_delay_ms(500);
	skip_leds = false;
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	//Tap once for Esc, twice for Caps Lock
	[TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
	//Tap one for Space, and twice for Enter
	[TD_SPACE]     = ACTION_TAP_DANCE_DOUBLE(KC_SPACE, KC_ENTER),
	// Special Z
	[TD_DIABLO_J]  = ACTION_TAP_DANCE_DOUBLE(KC_J, S(KC_J)),
	// Once for colin, twice for semi-colin
	[TD_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset),
	// Tap until you get a surprise
	[TD_EGG] = ACTION_TAP_DANCE_FN (dance_egg),
	//Once for Blue, Twice for Green, Thrice for Red, and four to flash
	[TD_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED (dance_flsh_each, dance_flsh_finished, dance_flsh_reset),
    
    [TD_DIABLO_1] = ACTION_TAP_DANCE_FN(diablo_tapdance1),
    [TD_DIABLO_2] = ACTION_TAP_DANCE_FN(diablo_tapdance2),
    [TD_DIABLO_3] = ACTION_TAP_DANCE_FN(diablo_tapdance3),
    [TD_DIABLO_4] = ACTION_TAP_DANCE_FN(diablo_tapdance4),

};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = KEYMAP(
				KC_EQUAL,KC_1,KC_2,KC_3,KC_4,KC_5,TG(MOUS),
				KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,TG(DIABLO),
				KC_BSPACE,KC_A,KC_S,KC_D,KC_F,KC_G,
				KC_LSHIFT,CTL_T(KC_Z),KC_X,KC_C,KC_V,KC_B,TG(OVERWATCH),
				LT(SYMB,KC_GRAVE),KC_QUOTE,KC_LGUI,KC_LEFT,KC_RIGHT,
									ALT_T(KC_APPLICATION),KC_LGUI,
									KC_HOME,
									KC_SPACE,KC_BSPACE,KC_LBRACKET,
									
				TG(MOUS),KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,
				TG(DIABLO),KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLASH,
				KC_H,KC_J,KC_K,KC_L,KC_SCOLON,GUI_T(KC_QUOTE),
				TG(OVERWATCH),KC_N,KC_M,KC_COMMA,KC_DOT,CTL_T(KC_SLASH),KC_RSHIFT,
				KC_PGDOWN,KC_PGUP,KC_DOWN,KC_UP,MO(SYMB),
				KC_LALT,CTL_T(KC_ESCAPE),
				KC_END,
				KC_RBRACKET,KC_DELETE,KC_ENTER
			),

  [SYMB] = KEYMAP(
				TD(TD_ESC_CAPS),KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRANSPARENT,
				M_VERSION,KC_EXLM,KC_AT,KC_LCBR,KC_RCBR,KC_PIPE,KC_TRANSPARENT,
				M_MAKE,KC_HASH,KC_DLR,KC_LPRN,KC_RPRN,KC_GRAVE,
				TD(TD_FLSH),KC_PERC,KC_CIRC,KC_LBRACKET,KC_RBRACKET,KC_TILD,M_COVECUBE,
				KC_NO,KC_AMPR,KC_ASTR,KC_COLN,KC_SCOLON,
									RGB_MOD,RGB_0000FF,
									RGB_008000,
									RGB_VAD,RGB_VAI,RGB_FF0000,
				
				KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,
				KC_TRANSPARENT,KC_KP_PLUS,KC_KP_7,KC_KP_8,KC_KP_9,KC_KP_ASTERISK,KC_F12,
				KC_KP_MINUS,KC_KP_4,KC_KP_5,KC_KP_6,KC_KP_SLASH,KC_PSCREEN,
				KC_TRANSPARENT,KC_NUMLOCK,KC_KP_1,KC_KP_2,KC_KP_3,KC_EQUAL,KC_PAUSE,
				KC_KP_0,KC_KP_0,KC_KP_DOT,KC_KP_ENTER,KC_KP_ENTER,
				RGB_TOG,RGB_SLD,
				RGB_HUI,
				RGB_HUD,KC_KP_DOT,KC_KP_0
			),

  [OVERWATCH] = KEYMAP(
				KC_ESCAPE,KC_1,KC_2,KC_3,KC_4,M_MORESALT,M_SYMM,
				KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_BSPACE,
				KC_LCTL,KC_A,KC_S,KC_D,KC_F,KC_G,
				KC_LSHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_TRANSPARENT,
				KC_LCTL,M_SALT,KC_LGUI,KC_Y,KC_LALT,
									KC_ESCAPE,KC_LGUI,
									M_DOOMFIST,
									KC_SPACE,KC_V,KC_H,
									
				M_HARD,KC_F9,KC_F10,KC_F11,KC_F12,KC_NO,KC_NO,
				KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,
				KC_NO,
				KC_NO,KC_NO,KC_NO
			),

  [DIABLO] = KEYMAP(
				KC_ESCAPE,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,
				KC_TAB,KC_S,KC_I,KC_F,KC_M,KC_T,KC_TRANSPARENT,
				KC_Q,KC_1,KC_2,KC_3,KC_4,KC_G,
				KC_NUMLOCK,KC_KP_1,KC_KP_2,KC_KP_3,KC_KP_4,KC_Z,TO(BASE),
				KC_LCTL,TD(TD_DIABLO_1),TD(TD_DIABLO_2),TD(TD_DIABLO_3),TD(TD_DIABLO_4),
									KC_L,LSFT(KC_J),
									KC_F,
									SFT_T(KC_SPACE),ALT_T(KC_Q),KC_DIABLO_CLEAR,
									
									
				KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,
				KC_NO,
				KC_NO,KC_NO,KC_NO
			),

  [MOUS] = KEYMAP(
				KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,
				KC_NO,KC_NO,KC_MS_UP,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,
				KC_NO,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_NO,KC_NO,
				KC_NO,KC_MS_ACCEL0,KC_MS_ACCEL1,KC_MS_ACCEL2,KC_NO,KC_NO,KC_TRANSPARENT,
				KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
									KC_NO,KC_NO,
									KC_MS_WH_UP,
									KC_MS_BTN1,KC_MS_BTN2,KC_MS_WH_DOWN,
				
				KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,KC_MS_ACCEL0,KC_MS_ACCEL1,KC_MS_ACCEL2,KC_NO,KC_NO,
				KC_TRANSPARENT,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_STOP,KC_AUDIO_MUTE,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_NO,
				KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,
				KC_NO,
				KC_MS_BTN3,KC_MS_BTN4,KC_MS_BTN5
			),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(SYMB) // FN1 - Momentary Layer 1 (Symbols)
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
   
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case 0:
            if (record->event.pressed) {
                // Output Keyboard Firmware info
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
            }
        case 1:
            if (record->event.pressed) {
                // Symmentra "Left Click to win" salt
                return MACRO( I(50),  T(ENTER), I(5), D(LSFT), T(L), U(LSFT), T(E), T(F), T(T), T(SPACE), T(C), T(L), T(I), T(C), T(K), T(SPACE), T(T), T(O), T(SPACE), T(W), T(I), T(N), D(LSFT), T(1), U(LSFT), T(ENTER), END );
            }
        case 2:
            if (record->event.pressed) {
                //salt salt salt
                return MACRO( I(50), T(ENTER), I(5), D(LSFT), T(S), U(LSFT), T(A), T(L), T(T), T(COMMA), T(SPACE), T(S), T(A), T(L), T(T), T(COMMA), T(SPACE), T(S), T(A), T(L), T(T), T(DOT), T(DOT), T(DOT), T(ENTER), END );
            }
        case 3:
            if (record->event.pressed) {
                // your saltiness makes me hard
                return MACRO( I(50),  T(ENTER), I(5), D(LSFT), T(Y), U(LSFT), T(O), T(U), T(R), T(SPACE), T(S), T(A), T(L), T(T), T(SPACE), T(O), T(N), T(L), T(Y), T(SPACE), T(M), T(A), T(K), T(E), T(S), T(SPACE), T(M), T(Y), T(SPACE), T(P), T(E), T(N), T(I), T(S), T(SPACE), T(T), T(H), T(A), T(T), T(SPACE), T(M), T(U), T(C), T(H), T(SPACE), T(H), T(A), T(R), T(D), T(E), T(R), T(COMMA), T(SPACE), T(A), T(N), T(D), T(SPACE), T(E), T(V), T(E), T(N), T(SPACE), T(M), T(O), T(R), T(E), T(SPACE), T(A), T(G), T(G), T(R), T(E), T(S), T(S), T(I), T(V), T(E), D(LSFT), T(1), U(LSFT), T(ENTER), END );
            }
        case 4:
            if (record->event.pressed) {
                // make ergodox-ez-drashna-custom-teensy
                return MACRO( I(5), T(M), T(A), T(K), T(E), T(SPACE), T(E), T(R), T(G), T(O), T(D), T(O), T(X), T(MINUS), T(E), T(Z), T(MINUS), T(D), T(R), T(A), T(S), T(H), T(N), T(A), T(MINUS), T(C), T(U), T(S), T(T), T(O), T(M), T(MINUS), T(T), T(E), T(E), T(N), T(S), T(Y), T(ENTER), END );
            }
        case 5:
            if (record->event.pressed) {
                //super secret hash
                SEND_STRING("supersecrethash");
                return MACRO_NONE;
            }
        case 6:
            if (record->event.pressed) {
                // Please sir, can I have some more salt
                return MACRO( I(50), T(ENTER), I(5), D(LSFT), T(P), U(LSFT), T(L), T(E), T(A), T(S), T(E), T(SPACE), T(S), T(I), T(R), T(COMMA), T(SPACE), T(C), T(A), T(N), T(SPACE), D(LSFT), T(I), U(LSFT), T(SPACE), T(H), T(A), T(V), T(E), T(SPACE), T(S), T(O), T(M), T(E), T(SPACE), T(M), T(O), T(R), T(E), T(SPACE), T(S), T(A), T(L), T(T), D(LSFT), T(SLASH), U(LSFT), D(LSFT), T(1), U(LSFT), T(ENTER), END );
            }
            break;
        case 7:
        if (record->event.pressed) {
                // DoomFisted
                // Hey, look at me.  I'm Doomfist, and I'm overpowered!  
                // All I do is spam punches all day!   I'm DPS, tank and 
                // defense, rolled into one! All I need is team healing to be complete!
                return MACRO( I(50), T(ENTER), I(5), D(LSFT), T(H), U(LSFT), T(E), T(Y), T(COMMA), T(SPACE), T(L), T(O), T(O), T(K), T(SPACE), T(A), T(T), T(SPACE), T(M), T(E), T(DOT), T(SPACE), T(SPACE), D(LSFT), T(I), U(LSFT), T(QUOTE), T(M), T(SPACE), D(LSFT), T(D), U(LSFT), T(O), T(O), T(M), T(F), T(I), T(S), T(T), T(COMMA), T(SPACE), T(A), T(N), T(D), T(SPACE), D(LSFT), T(I), U(LSFT), T(QUOTE), T(M), T(SPACE), T(O), T(V), T(E), T(R), T(P), T(O), T(W), T(E), T(R), T(E), T(D), D(LSFT), T(1), U(LSFT), T(SPACE), T(SPACE), D(LSFT), T(A), U(LSFT), T(L), T(L), T(SPACE), D(LSFT), T(I), U(LSFT), T(SPACE), T(D), T(O), T(SPACE), T(I), T(S), T(SPACE), T(S), T(P), T(A), T(M), T(SPACE), T(P), T(U), T(N), T(C), T(H), T(E), T(S), T(SPACE), T(A), T(L), T(L), T(SPACE), T(D), T(A), T(Y), D(LSFT), T(1), U(LSFT), T(SPACE), T(SPACE), T(SPACE), D(LSFT), T(I), U(LSFT), T(QUOTE), T(M), T(SPACE), D(LSFT), T(D), U(LSFT), D(LSFT), T(P), U(LSFT), D(LSFT), T(S), U(LSFT), T(COMMA), T(SPACE), T(T), T(A), T(N), T(K), T(SPACE), T(A), T(N), T(D), T(SPACE), T(D), T(E), T(F), T(E), T(N), T(S), T(E), T(COMMA), T(SPACE), T(R), T(O), T(L), T(L), T(E), T(D), T(SPACE), T(I), T(N), T(T), T(O), T(SPACE), T(O), T(N), T(E), D(LSFT), T(1), U(LSFT), T(SPACE), D(LSFT), T(A), U(LSFT), T(L), T(L), T(SPACE), D(LSFT), T(I), U(LSFT), T(SPACE), T(N), T(E), T(E), T(D), T(SPACE), T(I), T(S), T(SPACE), T(T), T(E), T(A), T(M), T(SPACE), T(H), T(E), T(A), T(L), T(I), T(N), T(G), T(SPACE), T(T), T(O), T(SPACE), T(B), T(E), T(SPACE), T(C), T(O), T(M), T(P), T(L), T(E), T(T), T(E), D(LSFT), T(1), U(LSFT), T(ENTER), END );
            }
        case 8: //MAC1 - Hold for rshift and } on tap
            if (record->event.pressed) {
                key_timer = timer_read();
                return MACRO(D(LSFT), END );
            } else {
                return checktime() ? MACRO(U(LSFT),D(RALT),T(7),U(RALT),END): MACRO(U(LSFT),END);
            }; break;
        case 9:	//MAC1 - Hold for rshift and } on tap
            if (record->event.pressed) {
                key_timer = timer_read();
                return MACRO(D(RSFT), END );
            } else {
                return checktime()  ? MACRO(U(RSFT),D(RALT),T(0),U(RALT),END): MACRO(U(RSFT),END);
            }; break;
        case 10: //MAC2 - Hold for lctrl and [ on tap
            if (record->event.pressed) {
                key_timer = timer_read();
                return MACRO(D(LCTL), END );
            } else {return checktime() ? MACRO(U(LCTL),D(RALT),T(8),U(RALT),END):MACRO(U(LCTL),END);
            }; break;
        case 11: //MAC3 - Hold for rctrl and ] on tap
            if (record->event.pressed) {
                key_timer = timer_read();
                return MACRO(D(RCTL), END );
            } else {
                return checktime() ? MACRO(U(RCTL),D(RALT),T(9),U(RALT),END):MACRO(U(RCTL),END);
            }; break;
    }
    return MACRO_NONE;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		// dynamically generate these.
		case EPRM:
			if (record->event.pressed) {
                eeconfig_init();
			}
			return false;
			break;
		case VRSN:
			if (record->event.pressed) {
				SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
			}
			return false;
			break;
		case RGB_SLD:
			if (record->event.pressed) {
				rgblight_mode(1);
			}
			return false;
			break;

		case RGB_0000FF:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0x00,0x00,0xff);
				#endif
			}
			return false;
			break;

		case RGB_008000:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0x00,0x80,0x00);
				#endif
			}
			return false;
			break;

		case RGB_FF0000:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0xff,0x00,0x00);
				#endif
			}
			return false;
			break;

		case RGB_800080:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0x80,0x00,0x80);
				#endif
			}
			return false;
			break;

		case RGB_00FF90:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0x00,0xff,0x90);
				#endif
			}
			return false;
			break;
        case KC_DIABLO_CLEAR:
            if (record->event.pressed) {
                uint8_t dtime;
                
                for (dtime = 0; dtime < 4; dtime++) {
                    diablo_key_time[dtime] = diablo_times[0];
                }
            }
            return false;
            break;
            
	}
	return true;
}

void send_diablo_keystroke (uint8_t diablo_key) {
    if (current_layer == DIABLO) {
        switch (diablo_key) {
            case 0:
                SEND_STRING("1");
                break;
            case 1:
                SEND_STRING("2");
                break;
            case 2:
                SEND_STRING("3");
                break;
            case 3:
                SEND_STRING("4");
                break;
        }
    }
}

void run_diablo_macro_check(void) {
    uint8_t dtime;
    
    for (dtime = 0; dtime < 4; dtime++) {
        if (check_dtimer(dtime) && diablo_key_time[dtime]) {
            diablo_timer[dtime] = timer_read();
            send_diablo_keystroke(dtime);
        } 
    }
    
}

void matrix_init_user(void) { // Runs boot tasks for keyboard
    wait_ms(500);
    ergodox_board_led_on();
    wait_ms(200);
    ergodox_right_led_1_on();
    wait_ms(200);
    ergodox_right_led_2_on();
    wait_ms(200);
    ergodox_right_led_3_on();
    wait_ms(200);
    ergodox_board_led_off();
    wait_ms(200);
    ergodox_right_led_1_off();
    wait_ms(200);
    ergodox_right_led_2_off();
    wait_ms(200);
    ergodox_right_led_3_off();

    
#ifdef LAYER_UNDERGLOW_LIGHTING
	rgblight_enable();
	rgblight_sethsv(195,255,255);
	rgblight_mode(5);
#endif 
    has_layer_changed = false;
    
    
    
};



void matrix_scan_user(void) {  // runs frequently to update info
    uint8_t modifiders = get_mods();
    uint8_t layer = biton32(layer_state);
	
	if (!skip_leds) {
		ergodox_board_led_off();
		ergodox_right_led_1_off();
		ergodox_right_led_2_off();
		ergodox_right_led_3_off();
        
        if ( modifiders & MODS_SHIFT_MASK) {
                ergodox_right_led_1_on();
        }
        if ( modifiders & MODS_CTRL_MASK) {
                ergodox_right_led_2_on();
        }
        if ( modifiders & MODS_ALT_MASK) {
                ergodox_right_led_3_on();
        }
        
    }
        
    switch (layer) {
        case SYMB:
            #ifdef LAYER_UNDERGLOW_LIGHTING
            if (has_layer_changed) {
                rgblight_sethsv (240,255,255);
            }
            #else
            ergodox_right_led_3_on();
            #endif
            break;
        case OVERWATCH:
            #ifdef LAYER_UNDERGLOW_LIGHTING
            if (has_layer_changed) {
                rgblight_sethsv (30,255,255);
            }
            #else
            ergodox_right_led_2_on();
            #endif
            break;
        case DIABLO:
            #ifdef LAYER_UNDERGLOW_LIGHTING
            if (has_layer_changed) {
                rgblight_sethsv (0,255,255);
            }
            #else
            ergodox_right_led_1_on();
            #endif
            break;
        case MOUS:
            #ifdef LAYER_UNDERGLOW_LIGHTING
            if (has_layer_changed) {
                rgblight_sethsv (60,255,255);
            }
            #else
            ergodox_right_led_3_on();
            ergodox_right_led_2_on();
            #endif
            break;
        case 5:
            #ifdef LAYER_UNDERGLOW_LIGHTING
            if (has_layer_changed) {
                rgblight_sethsv (255,255,255);
            }
            #else
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            #endif
            break;
        case 6:
            #ifdef LAYER_UNDERGLOW_LIGHTING
            if (has_layer_changed) {
                rgblight_sethsv (255,255,255);
            }
            #else
            ergodox_right_led_2_on();
            ergodox_right_led_1_on();
            #endif
            break;
        case 7:
            #ifdef LAYER_UNDERGLOW_LIGHTING
            if (has_layer_changed) {
                rgblight_sethsv (255,255,255);
            }
            #else
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            #endif
            break;
        default:
            // Do not add anything here, as this will be ran EVERY check, and can cause a significant slowdown
            #ifdef LAYER_UNDERGLOW_LIGHTING
            if (has_layer_changed) {
                rgblight_sethsv (195,255,255);
            }
            #endif
            break;
    }
        
    if (current_layer == layer) {
        has_layer_changed = false;
    } else {
        has_layer_changed = true;
        current_layer = layer;
    }
    run_diablo_macro_check();
};


