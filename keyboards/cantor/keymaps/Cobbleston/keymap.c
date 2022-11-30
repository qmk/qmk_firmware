#include QMK_KEYBOARD_H

enum layers {
	BASE,
	SYM,
	ARROW,
	NUMBER,
	MOUSE,
	MISC
};

enum custom_keycodes {
    UPDIR = SAFE_RANGE,
    DP2X,
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case UPDIR:  // Types ../ to go up a directory on the shell.
      if (record->event.pressed) {
        SEND_STRING("../");
      }
      return false;

    case DP2X:  // Types two time : -> ::
      if (record->event.pressed) {
        SEND_STRING("::");
      }
      return false;
  }
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_split_3x6_3(
		CAPS_WORD,	KC_Q,			KC_W,			KC_E,			KC_R,			KC_T,	/**/	KC_Y,	KC_U,			KC_I, 			KC_O, 			KC_P, 				KC_PSCR, 
		KC_NO,		LGUI_T(KC_A),	LALT_T(KC_S),	LCTL_T(KC_D),	LSFT_T(KC_F),	KC_G,	/**/	KC_H,	RSFT_T(KC_J),	RCTL_T(KC_K),	RALT_T(KC_L),	RGUI_T(KC_SCNL),	KC_NO,
		KC_NO, 		KC_Z,		 	KC_X,			KC_C,			KC_V,			KC_B,	/**/	KC_N,	KC_M,			KC_COMM,		KC_DOT,			KC_SLSH,			KC_NO,
								LT(NUMBER, KC_DEL),	LT(ARROW, KC_TAB),	LT(MOUSE, KC_ESC),	/**/	LT(MISC, KC_ENT),	LT(SYM, KC_SPC),	KC_BSPC
	),
	[ARROW] = LAYOUT_split_3x6_3(
		KC_NO, 		UC(0x00F9),	UC(0x00E0),	UC(0x00E8),	UC(0x00EC),	UC(0x00F2),	/**/	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
	  	KC_NO, 		KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,		/**/	KC_CAPS,	KC_LEFT, 	KC_DOWN,	KC_UP,		KC_RGHT,	KC_NO,
	    KC_NO, 		UC(0x00D9),	UC(0x00C0),	UC(0x00C8),	UC(0x00CC),	UC(0x00D2),	/**/	KC_INS,		KC_HOME, 	KC_PGDN,	KC_PGUP,	KC_END,		KC_NO,
											KC_NO, 		KC_NO,		KC_NO,		/**/	KC_ENT,		KC_SPC,		KC_BSPC
	),
	[NUMBER] = LAYOUT_split_3x6_3(
		KC_NO,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		/**/	KC_PAST,	KC_7,		KC_8,		KC_9,		KC_PMNS,	KC_NO,
		KC_F11,		KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,		/**/	KC_PSLS,	KC_4,		KC_5,		KC_6,		KC_PPLS,	KC_NO,
		KC_F12,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		/**/	KC_PEQL,	KC_1,		KC_2,		KC_3,		KC_NO,		KC_NO,
											KC_NO,		KC_NO,		KC_NO,		/**/	KC_ENT,		KC_0,		KC_DOT
	),
	[SYM] = LAYOUT_split_3x6_3(
		KC_NO,		KC_QUOT,	KC_LT,		KC_GT,		KC_DQUO,	KC_GRAVE,	/**/	KC_AMPR,	DP2X,		KC_LBRC,	KC_RBRC,	KC_PERC,	KC_NO,
		KC_NO,		KC_EXLM,	KC_MINS,	KC_PLUS,	KC_EQL,		KC_HASH,	/**/	KC_PIPE,	KC_COLN,	KC_LPRN,	KC_RPRN,	KC_QUES,	KC_NO,
		KC_NO,		KC_CIRC,	KC_SLSH,	KC_ASTR,	KC_BSLS,	UPDIR,		/**/	KC_TILD,	KC_DLR,		KC_LCBR,	KC_RCBR,	KC_AT,		KC_NO,
											KC_DEL,		KC_TAB,		KC_ESC,		/**/	KC_NO,		KC_NO,		KC_NO
	),
	[MISC] = LAYOUT_split_3x6_3(
		QK_BOOT,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		/**/	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		UC(0x30C4),	KC_NO,		/**/	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		/**/	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
											KC_NO,		KC_NO,		KC_NO,		/**/	KC_NO,		KC_NO,		KC_NO
	),
	[MOUSE] = LAYOUT_split_3x6_3(
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		/**/	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,		/**/	KC_NO,		KC_MS_L,	KC_MS_D,	KC_MS_U,	KC_MS_R,	KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		/**/	KC_NO,		KC_WH_L,	KC_WH_D,	KC_WH_U,	KC_WH_R,	KC_NO,
											KC_NO,		KC_NO,		KC_NO,		/**/	KC_BTN1,	KC_BTN2,	KC_BTN3
	)
};
