#include QMK_KEYBOARD_H
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif
#include "ps2_mouse.h"
extern keymap_config_t keymap_config;
//#include "LUFA/Drivers/Peripheral/TWI.h"

//#define TAPPING_FORCE_HOLD


enum santoku_layers 
{
	_DVORAK,
	_LOWER,
	_RAISE,
	_ADJUST,

	_QWERTY,
	_SYMBOL,
	_NAVIGATION,
	_FUNC
};

enum santoku_keycodes
{
	DVORAK = SAFE_RANGE,
	QWERTY,
	SYMBOL,
	NAVIGATION,
	FUNC,
	ONETAPALTTAB,
	OVERVIEW,
	TAPHOLDKEYTEST,
	TESTV
};

enum combos
{
	JK_ESC,
	MCOMMA_FORWARDHISTORY,
	NM_BACKHISTORY,
	HJ_CLOSETAB,
	YU_PREVTAB,
	UI_NEXTTAB
};

#define TO_DV TO(_DVORAK)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SFT_U SFT_T(KC_U) //TO SHORTEN THINGS UP IN LAYOUT MAP? MAKE A BUNCH OF THESE

const uint16_t PROGMEM jk_combo[]     = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM eu_combo[]     = {KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM mcomma_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM nm_combo[]     = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM hj_combo[]     = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM yu_combo[]     = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM ui_combo[]     = {KC_U, KC_I, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
	[JK_ESC]                = COMBO_ACTION(jk_combo),
	[EU_ENT]                = COMBO_ACTION(eu_combo),
	[UI_NEXTTAB]            = COMBO_ACTION(ui_combo),
	[YU_PREVTAB]            = COMBO_ACTION(yu_combo),
	[HJ_CLOSETAB]           = COMBO_ACTION(hj_combo),
	[NM_BACKHISTORY]        = COMBO_ACTION(nm_combo),
	[MCOMMA_FORWARDHISTORY] = COMBO_ACTION(mcomma_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case JK_ESC:
      if (pressed) {
        tap_code16(KC_ESC);
      }
      break;
    case EU_ENT:
      if (pressed) {
        tap_code16(KC_ENT);
      }
      break;
    case UI_NEXTTAB:
      if (pressed) {
        tap_code16(LCTL(KC_PGDN));
      }
      break;
    case YU_PREVTAB:
      if (pressed) {
        tap_code16(LCTL(KC_PGUP));
      }
      break;
    case HJ_CLOSETAB:
      if (pressed) {
        tap_code16(LCTL(KC_W));
      }
      break;
    case NM_BACKHISTORY:
      if (pressed) {
        tap_code16(LALT(KC_LEFT));
      }
      break;
    case MCOMMA_FORWARDHISTORY:
      if (pressed) {
        tap_code16(LALT(KC_RGHT));
      }
      break;
  }
}

static bool in_alttab = false; // does an ALT-TAB, for windows cycling, without an alt key


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DVORAK] = LAYOUT( \
			//TODO: Enter, Alt, Del, Gui
			//Consider miryoku style modifiers... homerow left->right super(aka gui), alt, ctrl, shift
			KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,	  KC_P,    KC_Y,         KC_F,    KC_G,   KC_C,      KC_R,   KC_L,    KC_SLSH, \
			KC_TAB,  KC_A,    KC_O,    KC_E,   	  KC_U,    KC_I,         KC_D,    KC_H,   KC_T,      KC_N,   KC_S,    KC_MINS, \
//MIRYOKU KC_TAB, GUI_T(KC_A), ALT_T(KC_O), CTL_T(KC_E), SFT_T(KC_U), KC_I,         KC_D, SFT_T(KC_H), CTL_T(KC_T), ALT_T(KC_N), GUI_T(KC_S),    KC_MINS, !ADD SLASH CHAR!
			KC_EQL,  KC_SCLN, KC_Q,    KC_J,  	  KC_K,    KC_X,         KC_B,    KC_M,   KC_W,      KC_V,   KC_Z,    KC_BSLS \
			XXXXXXX, XXXXXXX, XXXXXXX, TT(LOWER), KC_LSFT, KC_LCTL,      KC_BSPC, KC_SPC, TT(RAISE), XXXXXX, XXXXXXX, XXXXXXX 
//!MIRYOKU* XXXXXXX, XXXXXXX, XXXXXXX, TT(LOWER), KC_LSFT, KC_ENT,       KC_BSPC, KC_SPC, TT(RAISE), XXXXXX, XXXXXXX, XXXXXXX 
			//xxxxx, KC_ENT,  KC_LALT, TT(LOWER), KC_LSFT, KC_LCTL,      KC_BSPC, KC_SPC, TT(RAISE), KC_DEL, KC_LGUI, XXXXXXX
			),

	[_QWERTY] = LAYOUT( \
			KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    	  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC, \
			KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    	  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
			KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    	  KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_LGUI,\
			XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,     _______, _______, _______, XXXXXX, XXXXXXX, XXXXXXX
			),

	[_LOWER] = LAYOUT( \
			_______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR,     _______, KC_P7,   KC_P8,   KC_P9,  KC_PMNS, _______, \
			_______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR, 	  _______, KC_P4,   KC_P5,   KC_P6,  KC_PPLS, _______, \
			_______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_GRV,      _______, KC_P1,   KC_P2,   KC_P3,  KC_PENT, _______, \
			XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,     _______, _______, KC_KP_0, XXXXXX, XXXXXXX, XXXXXXX
//!MIRY*    XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,     KC_DEL,  _______, KC_KP_0, XXXXXX, XXXXXXX, XXXXXXX
			),

	[_RAISE] = LAYOUT( \
			_______, KC_PSCR, KC_HOME, KC_UP,   KC_END,  KC_PGUP,     KC_VOLU, KC_F7,   KC_F8,   KC_F9,  KC_F10,  XXXXXXX,\
			KC_CAPS, KC_INS,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,     KC_VOLD, KC_F4,   KC_F5,   KC_F6,  KC_F11,  XXXXXXX,\
			_______, KC_NLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_MUTE, KC_F1,   KC_F2,   KC_F3,  KC_F12,  XXXXXXX,\
			XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,     _______, _______, _______, XXXXXX, XXXXXXX, XXXXXXX
			),

	[_ADJUST] =  LAYOUT( \
			TO_DV, RESET,   _______, _______, _______, _______,       _______, _______, _______, _______, _______, KC_DEL,  \
			RGB_TOG, RGB_MOD, VLK_TOG, AU_ON,   AU_OFF,  AG_NORM,     AG_SWAP,  QWERTY,  DVORAK, _______, _______, _______, \
			RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,     _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,  \
			XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,     _______, _______, _______, XXXXXX,  XXXXXXX, XXXXXXX
			)



/////////////////////////TYE's maps/////////////////////////////
	[_QWERTY] = { /*QWERTY*/
		/*
		   SWITCH TO THIS FORMAT/SHORTCUT????:  KC_A,      L(MOUSE,KC_S), L(MIDDLE,KC_D), GUI(KC_F),       CTL(KC_G),
https://docs.qmk.fm/#/faq_keymap?id=arrow-on-right-modifier-keys-with-dual-role <-- User VIM nav arrow key without layer??? Tap and hold?
*/
		{KC_TAB,              KC_Q,              KC_W,     KC_E,    KC_R,     KC_T,   KC_Y,         KC_U,       KC_I,    KC_O,   KC_P,                  KC_BSLS },
		{MT(MOD_LGUI,KC_ESC), MT(MOD_LCTL,KC_A), KC_S,     KC_D,    KC_F,     KC_G,   KC_H,         KC_J,       KC_K,    KC_L,   MT(MOD_RCTL,KC_SCLN),  MT(MOD_RGUI,KC_QUOT)},
		{KC_LSFT,             MT(MOD_LALT,KC_Z), KC_X,     KC_C,    KC_V,     KC_B,   KC_N,         KC_M,       KC_COMM, KC_DOT, MT(MOD_RALT,KC_SLSH),  KC_RSFT },
		{XXXXXXX,             XXXXXXX,           XXXXXXX,  LT(_FUNC,KC_BSPC), KC_SPC, ONETAPALTTAB, TT(_NAVIGATION), TT(_SYMBOL),  KC_ENT, XXXXXXX,    XXXXXXX,   XXXXXXX }
	},

	[_SYMBOL] = {/*SYMBOL*/
		{KC_GRV,               KC_EXLM,              KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR, KC_ASTR,    KC_LPRN, KC_RPRN,              KC_MINS },
		{MT(MOD_LGUI,KC_ESC),  MT(MOD_LCTL,KC_1),    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,     KC_7,    KC_8,       KC_9,    MT(MOD_RCTL,KC_0),    MT(MOD_RGUI,KC_EQL) },
		{KC_LSFT,              MT(MOD_LALT,KC_BSLS), KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,  KC_LBRC,  KC_RBRC, KC_COMM,    KC_DOT,  MT(MOD_RALT,KC_SLSH), KC_RSFT },
		{XXXXXXX,              XXXXXXX,              XXXXXXX, KC_BSPC, KC_SPC,  XXXXXXX,  _______,  _______, KC_ENT,    XXXXXXX, XXXXXXX,              XXXXXXX }
	},

	[_NAVIGATION] = {/*NAVIGATION*/
		{KC_TAB,              XXXXXXX,                RCTL(KC_RGHT),  XXXXXXX,  XXXXXXX,     XXXXXXX,       KC_HOME,       KC_PGDN,      KC_PGUP,  KC_END,   RCTL(KC_TAB), XXXXXXX  },
		{MT(MOD_LGUI,KC_ESC), KC_LCTL,                XXXXXXX,        XXXXXXX,  KC_MS_WH_DOWN,     OVERVIEW,      KC_LEFT,       KC_DOWN,      KC_UP,    KC_RGHT,  KC_RCTL,      KC_RGUI  },
		{KC_LSFT,             MT(MOD_LALT,OVERVIEW),  XXXXXXX,        XXXXXXX,  KC_MS_WH_UP,       RCTL(KC_LEFT), LGUI(KC_LBRC), LGUI(KC_RBRC),LGUI(LSFT(KC_EQL)),  LGUI(LSFT(KC_MINS)),  KC_RALT,      KC_RSFT  },
		{XXXXXXX,             XXXXXXX,                XXXXXXX,        KC_DEL,   KC_SPC,      OVERVIEW,      _______,       _______,      KC_ENT,  XXXXXXX,  XXXXXXX,      XXXXXXX  }
	},

	[_FUNC] = {/*FUNCTION*/
		{XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, KC_F11,  KC_F12,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               XXXXXXX  },
		{MT(MOD_LGUI,KC_ESC), MT(MOD_LCTL,KC_F1), KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   MT(MOD_RCTL,KC_F10),   MT(MOD_RGUI,KC_ESC)  },
		{MT(KC_LSFT,KC_CAPS), MT(MOD_LALT,KC_F6), KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_LALT,               KC_RSFT  },
		{XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX,KC_SPC ,  XXXXXXX,  XXXXXXX, XXXXXXX, RESET,   XXXXXXX, XXXXXXX,               XXXXXXX  }
	}

};


bool encoder_update_user(uint8_t index, bool clockwise) {
        if (clockwise) {
            //tap_code(KC_PGDN);
            tap_code(KC_WH_U);
            tap_code(KC_WH_U);
            tap_code(KC_WH_U);
        } else {
            //tap_code(KC_PGUP);
            tap_code(KC_WH_D);
            tap_code(KC_WH_D);
            tap_code(KC_WH_D);
        }
	return true;
}


void keyboard_post_init_user(void) {
	// Customise these values to desired behaviour
	debug_enable=false;
	debug_matrix=false;
	debug_keyboard=false;
	debug_mouse=false;
	//ps2_mouse_set_remote_mode();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	static uint16_t key_timer;
	//static bool in_cursor_mode = false;

	switch (keycode) {
		case TAPHOLDKEYTEST:
			if (record->event.pressed) {
				key_timer = timer_read();  // start the timer
				return false;              // return false to keep anything from being sent
			} else {
                // If key was held
				if (timer_elapsed(key_timer) > 250) {
						SEND_STRING(SS_TAP(X_G));
    					return false;
    				} else { 
                        // if key was tapped
						SEND_STRING(SS_TAP(X_B));
    					return false;
    				}
    			}
			break;

		case TESTV:
			SEND_STRING(SS_TAP(X_V));
			return false;

		case RESET:
			//oled_write_ln_P(PSTR("RESETORFLASH"), true);
			_delay_ms(1000);
			break;

		case ONETAPALTTAB:
			// Macro to handle lower-tab as alt-tab
			if (record->event.pressed) {
				if (!in_alttab) {
					SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_TAB));
					in_alttab = true;
				} else {
					SEND_STRING(SS_TAP(X_TAB));
					// Do not release Alt here, or it will be impossible to switch more than one window:
					// alt-tab-tab will be interpreted as alt-tab, then tab
				}
			}
			return false;
			break;

		case OVERVIEW:
			// Macro to handle overview mode. Enter overview, wait, then skip to window after current window
			if (record->event.pressed) {
				SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_F5));
				SEND_STRING(SS_UP(X_LGUI));
				_delay_ms(500);
				SEND_STRING(SS_TAP(X_DOWN));
			}
			return false;
			break;

		default:
			if ((keycode != ONETAPALTTAB) && in_alttab) {
				// Exit alt tab before treating normally the keycode
				SEND_STRING(SS_UP(X_LALT));
				in_alttab = false;
				return false;   
			}

	}
	return true;
}


void matrix_init_user(void) {
#ifdef USE_I2C
	i2c_master_init();
#ifdef SSD1306OLED
	// calls code for the SSD1306 OLED
	_delay_ms(400);
	TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
	iota_gfx_init();   // turns on the display
#endif
#endif
}

//#ifdef OLED_DRIVER_ENABLE
#ifdef OLED_ENABLE
void oled_task_user(void) {
	// Vanity Text
	static bool show_vanity_text = true;
	if (show_vanity_text) {
		oled_write_ln_P(PSTR("  Santoku Keyboard"), false);
		oled_write_ln_P(PSTR("       by Tye"), false);
		oled_write_ln_P(PSTR(""), false);
		oled_write_ln_P(PSTR("    Hello, world."), false);
		if (timer_read() > 7500) {
			show_vanity_text = false;
		}
	}
	else if (in_alttab ) {
		oled_write_ln_P(PSTR("   ALT-TAB ACTIVE   "), true);

	}
	else {
		uint8_t wpm = get_current_wpm();
		if (wpm < 20) {
			oled_write("CrOS  ", false);
		}
		else {
			char wpm_display[9];
			sprintf(wpm_display, "WPM:%d ", get_current_wpm());
			oled_write(wpm_display, false);
		}

		// Host Keyboard Layer Status
		switch (get_highest_layer(layer_state)) {
			case _QWERTY:
				oled_write_P(PSTR("QWERTY\n"), false);
				oled_write_ln_P(PSTR(""), false);
				oled_write_ln_P(PSTR("TB  qwert | yuiop\\"), false);
				oled_write_ln_P(PSTR("ES  asdfg | hjkl;'"), false);
				oled_write_ln_P(PSTR("SH  zxcvb | nm,./"), false);
				break;
			case _SYMBOL:
				oled_write_P(PSTR("   Symbol   \n"), true);
				oled_write_ln_P(PSTR(""), false);
				oled_write_ln_P(PSTR(" `  !@#$% | ^&*()-"), false);
				oled_write_ln_P(PSTR("ES  12345 | 67890="), false);
				oled_write_ln_P(PSTR("SH  \\_+{} | [],./"), false);
				break;
			case _NAVIGATION:
				oled_write_P(PSTR(" Navigation \n"), true);
				oled_write_ln_P(PSTR(""), false);
				oled_write_ln_P(PSTR("   | HM PD PU EN NT"), false);
				oled_write_ln_P(PSTR("   | << vv ^^ >>"), false);
				oled_write_ln_P(PSTR("ov | D[ D] D+ D-"), false);
				break;
			case _FUNC:
				oled_write_P(PSTR("  Function  \n"), true);
				oled_write_ln_P(PSTR(""), false);
				oled_write_ln_P(PSTR("          |"), false);
				oled_write_ln_P(PSTR("ES F12345 | 67890"), false);
				oled_write_ln_P(PSTR("CP F      | ab"), false);
				break;
			default:
				oled_write_ln_P(PSTR("Undefined"), false);
		}
	}

	/*
	// Host Keyboard LED Status
	led_t led_state = host_keyboard_led_state();
	oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
	oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
	oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	*/
}
#endif

