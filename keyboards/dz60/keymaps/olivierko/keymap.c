#include QMK_KEYBOARD_H

enum keyboard_layers {
  _BL,
  _SL,
  _FL,
  _CL,
};

enum custom_keycodes {
  SWE_AA = SAFE_RANGE,
  SWE_AE,
  SWE_OE,
};

char *alt_codes[][2] = {
    {
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_2)SS_TAP(X_KP_9)), // Alt+0229 → å
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_9)SS_TAP(X_KP_7)), // Alt+0197 → Å
    },
    {
		SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_2)SS_TAP(X_KP_8)), // Alt+0228 → ä
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_9)SS_TAP(X_KP_6)), // Alt+0196 → Ä
    },
    {
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_4)SS_TAP(X_KP_6)), // Alt+0246 → ö
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_1)SS_TAP(X_KP_4)), // Alt+0214 → Ö
    },
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BL] = LAYOUT_olivierko(
		KC_ESC,	 	KC_1,	  	KC_2,	 	KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,	KC_EQL,		KC_BSLS,		KC_GRV,
		KC_TAB,	 	KC_Q,	  	KC_W,	 	KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_LBRC,	KC_RBRC,	KC_BSPC,
		MO(_FL),	KC_A,	  	KC_S,	 	KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,	KC_ENT,		
		KC_LSFT, 	KC_Z,	  	KC_X,	 	KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	KC_UP, 		KC_RSFT,	
		KC_LCTL, 	KC_LGUI,  	KC_LALT, 										KC_SPC,											KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_RCTL),
									
	[_SL] = LAYOUT_olivierko(
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	SWE_AA,		KC_NO,		KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	SWE_OE,		SWE_AE,		KC_TRNS,		
		KC_TRNS, 	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS, 	KC_TRNS,	
		KC_TRNS, 	KC_TRNS,  	KC_TRNS, 										KC_TRNS,										KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS),									
									
	[_FL] = LAYOUT_olivierko(								
		KC_ESC,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_PSCR,		KC_PAUSE,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_DELETE,
		KC_NO,		DF(_BL),	DF(_SL),	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_INS,	
		KC_LSFT,	KC_NO,		KC_NO,		KC_CAPS,	KC_NO,		KC_NO,		KC_NO,		KC_MUTE,	KC_NO,		KC_NO,		KC_NO,		KC_PGUP,	KC_RSFT,	
		KC_LCTL,	MO(_CL),	KC_LALT,										KC_MPLY,										KC_HOME,	KC_PGDOWN,	KC_END,		KC_RCTL),
											
	[_CL] = LAYOUT_olivierko(								
		RGB_TOG,	RGB_MOD,	RGB_HUI,	RGB_HUD,	RGB_SAI,	RGB_SAD,	RGB_VAI,	RGB_VAD,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,			KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		QK_BOOT,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_NO,		KC_NO,		DEBUG,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,	
		KC_LSFT,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_RSFT,	
		KC_NO,		KC_NO,		KC_NO,											KC_NO,											KC_NO,		KC_NO,		KC_NO,		KC_NO),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!record->event.pressed) 
		return true;

    switch (keycode) {
		case SWE_AA: 
		case SWE_AE: 
		case SWE_OE: {
			uint16_t index = keycode - SWE_AA;
			uint8_t shift = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

			unregister_code(KC_LSFT);
			unregister_code(KC_RSFT);

			send_string(alt_codes[index][(bool)shift]);

			if (shift & MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
			if (shift & MOD_BIT(KC_RSFT)) register_code(KC_RSFT);

			return false;
		}
		default:
			return true;
    }
}