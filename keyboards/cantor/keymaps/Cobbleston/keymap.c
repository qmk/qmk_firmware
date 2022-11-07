#include QMK_KEYBOARD_H

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
	[0] = LAYOUT_split_3x6_3(
		CAPS_WORD,	KC_Q,			KC_W,			KC_F,			KC_P,			KC_B,	/**/	KC_J,	KC_L,			KC_U, 			KC_Y, 			KC_QUOT, 		KC_NO, 
		KC_NO,		LGUI_T(KC_A),	LALT_T(KC_R),	LCTL_T(KC_S),	LSFT_T(KC_T),	KC_G,	/**/	KC_M,	RSFT_T(KC_N),	RCTL_T(KC_E),	RALT_T(KC_I),	RGUI_T(KC_O),	KC_SCLN,
		KC_NO, 		KC_Z,		 	KC_X,			KC_C,			KC_D,			KC_V,	/**/	KC_K,	KC_H,			KC_COMM,		KC_DOT,			KC_SLSH,		KC_PSCR,
											LT(3, KC_DEL),	LT(2, KC_TAB),	LT(1, KC_ESC),	/**/	LT(4, KC_ENT),	KC_SPC,		KC_BSPC
	),
	[1] = LAYOUT_split_3x6_3(
		KC_NO, 		UC(0x00F9),	UC(0x00E0),	UC(0x00E8),	UC(0x00EC),	UC(0x00F2),	/**/		KC_NO,		KC_LBRC, 	KC_RBRC,	KC_LCBR,	KC_RCBR,	KC_NO,
	  	KC_NO, 		KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,		/**/		KC_CAPS,	KC_LEFT, 	KC_DOWN,	KC_UP,		KC_RGHT,	KC_NO,
	    KC_NO, 		UC(0x00D9),	UC(0x00C0),	UC(0x00C8),	UC(0x00CC),	UC(0x00D2),	/**/		KC_INS,		KC_HOME, 	KC_PGDN,	KC_PGUP,	KC_END,		KC_NO,
											KC_NO, 		KC_NO,		KC_NO,		/**/		KC_LPRN,	KC_SPC,		KC_RPRN
	),
	[2] = LAYOUT_split_3x6_3(
		KC_NO,		KC_QUOT,	KC_LT,		KC_GT,		KC_DQUO,	KC_DOT,		/**/		KC_AMPR,	DP2X,		KC_LBRC,	KC_RBRC,	KC_PERC,	KC_NO,
		KC_NO,		KC_EXLM,	KC_MINS,	KC_PLUS,	KC_EQL,		KC_HASH,	/**/		KC_PIPE,	KC_COLN,	KC_LPRN,	KC_RPRN,	KC_QUES,	KC_NO,
		KC_NO,		KC_CIRC,	KC_SLSH,	KC_ASTR,	KC_BSLS,	UPDIR,		/**/		KC_TILD,	KC_DLR,		KC_LCBR,	KC_RCBR,	KC_AT,		KC_NO,
											KC_NO,		KC_NO,		KC_NO,		/**/		KC_NO,		KC_NO,		KC_NO
		),
	[3] = LAYOUT_split_3x6_3(
		KC_NO,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		/**/		KC_PAST,	KC_7,		KC_8,		KC_9,		KC_PMNS,	KC_NO,
		KC_F11,		KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,		/**/		KC_PSLS,	KC_4,		KC_5,		KC_6,		KC_PPLS,	KC_NO,
		KC_F12,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		/**/		KC_PEQL,	KC_1,		KC_2,		KC_3,		KC_NO,		KC_NO,
											KC_NO,		KC_NO,		KC_NO,		/**/		KC_ENT,		KC_0,		KC_DOT
		),
	[4] = LAYOUT_split_3x6_3(
		QK_BOOT,	KC_NO,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		/**/		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		UC(0x30C4),	KC_NO,		/**/		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		/**/		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
											KC_NO,		KC_NO,		KC_NO,		/**/		KC_NO,		KC_NO,		KC_NO
		)
};

