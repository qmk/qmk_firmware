#include QMK_KEYBOARD_H

enum layers {
	BASE,
	LOWER,
	RAISE,
	BOTH
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

// Custom Keycode
#define GUI_ESC  GUI_T(KC_ESC)
#define TAB_NUM  LT(NUMBER, KC_TAB)
#define BSPC_NAV  LT(NAVIG, KC_BSPC)
#define SPC_SYM  LT(SYMBOL, KC_SPC)
#define CTRL_ENT  LCTL_T(KC_ENT)

// Accent Letters
#define ALIT UC(0x00E0)
#define ABIG UC(0x00C0)
#define ELIT UC(0x00E8)
#define EBIG UC(0x00C8)
#define ILIT UC(0x00EC)
#define IBIG UC(0x00CC)
#define OLIT UC(0x00F2)
#define OBIG UC(0x00D2)
#define ULIT UC(0x00F9)
#define UBIG UC(0x00D9)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_split_3x6_3(
		KC_TAB,		KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	/**/	KC_Y,	KC_U,	KC_I, 		KC_O, 	KC_P, 		KC_DEL, 
		KC_ALT,		KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	/**/	KC_H,	KC_J,	KC_K,		KC_L,	KC_SCLN,	KC_PSCR,
		KC_LSFT, 	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	/**/	KC_N,	KC_M,	KC_COMM,	KC_DOT,	KC_SLSH,	OSL(EXTRA),
						CTRL_ENT,	GUI_ESC,	TAB_NUM,	/**/	BSPC_NAV,	SPC_SYM,	KC_LSFT
	),
	[NUMBER] = LAYOUT_split_3x6_3( // NUMBER + GUI/ALT/CTRL/SHIFT + FUNCTION
		KC_NO,	KC_F1,		 KC_F2,		KC_F3,		KC_F4,		KC_F5,	/**/	KC_PAST,	KC_7,	KC_8,	KC_9,	KC_PMNS,	KC_NO,
		KC_F11,	KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,	/**/	KC_PSLS,	KC_4,	KC_5,	KC_6,	KC_PPLS,	KC_NO,
		KC_F12,	KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,	/**/	KC_PEQL,	KC_1,	KC_2,	KC_3,	KC_NO,		KC_NO,
										KC_NO,		KC_NO,		LT(EXTRA),	/**/	KC_ENT,		KC_0,	KC_DOT
	),
	[NAVIG] = LAYOUT_split_3x6_3( // ARROW + ÀÈÌÒÙ
		KC_NO, 	ULIT,	ALIT,	ELIT,	ILIT,	OLIT,	/**/	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
	  	KC_NO, 	KC_LGUI,KC_LALT,KC_LCTL,KC_LSFT,KC_NO,	/**/	KC_LEFT, 	KC_DOWN,	KC_UP,		KC_RGHT,	KC_CAPS,	KC_NO,
	    KC_NO, 	UBIG,	ABIG,	EBIG,	IBIG,	OBIG,	/**/	KC_HOME, 	KC_PGDN,	KC_PGUP,	KC_END,		KC_INS,		KC_NO,
						KC_NO,	 	KC_NO,		KC_NO,	/**/	LT(EXTRA),	KC_SPC,		KC_LSFT
	),
	[SYM] = LAYOUT_split_3x6_3(
		KC_NO,		KC_QUOT,	KC_LT,		KC_GT,		KC_DQUO,	KC_GRAVE,	/**/	KC_AMPR,	DP2X,		KC_LBRC,	KC_RBRC,	KC_PERC,	KC_NO,
		KC_NO,		KC_EXLM,	KC_MINS,	KC_PLUS,	KC_EQL,		KC_HASH,	/**/	KC_PIPE,	KC_COLN,	KC_LPRN,	KC_RPRN,	KC_QUES,	KC_NO,
		KC_NO,		KC_CIRC,	KC_SLSH,	KC_ASTR,	KC_BSLS,	UPDIR,		/**/	KC_TILD,	KC_DLR,		KC_LCBR,	KC_RCBR,	KC_AT,		KC_NO,
											KC_DEL,		KC_TAB,		KC_ESC,		/**/	KC_NO,		KC_NO,		KC_NO
	),
	[EXTRA] = LAYOUT_split_3x6_3(
		QK_BOOT,KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	/**/	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	/**/	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	/**/	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
						KC_NO,		KC_NO,		KC_NO,	/**/	KC_NO,		KC_NO,		KC_NO
	)
};