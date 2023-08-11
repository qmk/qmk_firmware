#include QMK_KEYBOARD_H

#define PGMOD LT(_NUM, KC_PGDN)
#define TABMOD LT(_FN1, KC_TAB)
#define SPCMOD LT(_FN1, KC_SPACE)
#define ENTMOD LT(_FN2, KC_ENTER)
#define ESCMOD LT(_NUM, KC_ESC)
#define RSMOD LT(_FN1, KC_RSFT)
#define CMDBSP MT(MOD_LGUI, KC_BSPC)
#define ALTDEL MT(MOD_LALT, KC_DEL)
#define CTRLSP MT(MOD_LCTL, KC_SPACE)
#define BWORD LCTL(KC_BSPC)
#define JUMPBACK LSFT(KC_TAB)
#define LWORD LCTL(KC_LEFT)
#define RWORD LCTL(KC_RIGHT)
#define UNDO LCTL(KC_Z)
#define NTAB LCTL(KC_T)
#define CTAB LCTL(KC_W)
#define XPANDR LCTL(LSFT(KC_X))
#define TAB1 LCTL(KC_1)
#define TAB2 LCTL(KC_2)
#define TAB3 LCTL(KC_3)
#define TAB4 LCTL(KC_4)
#define RVOLU LCTL(KC_RBRC)
#define RVOLD LCTL(KC_LBRC)

enum layer_names {
  _BASE,
  _DEL,
  _FN1,
  _FN2,
  _NUM,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  CSPEAK,
  PARADOWN,
  PMERGE,
  WREFRESH,
  REMCAPS,
  SPEAK1,
  SPEAK2,
  SPEAK3,
  SPEAK4
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
	case CSPEAK:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PAGEDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PAGEDOWN));
	}
	break;
	case SPEAK1:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PAGEDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PAGEDOWN) SS_LCTL(SS_TAP(X_1)));
	}
	break;
	case SPEAK2:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PAGEDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PAGEDOWN) SS_LCTL(SS_TAP(X_2)));
	 }
	break;
	case SPEAK3:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PAGEDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PAGEDOWN) SS_LCTL(SS_TAP(X_3)));
	}
	break;
	case SPEAK4:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PAGEDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PAGEDOWN) SS_LCTL(SS_TAP(X_4)));
	}
	break;
	case PARADOWN:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PAGEDOWN) SS_TAP(X_ENTER) SS_TAP(X_PAGEDOWN));
	}
	break;
	case PMERGE:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_BACKSPACE) SS_TAP(X_SPACE) SS_LCTL(SS_TAP(X_BACKSPACE)) SS_TAP(X_SPACE));
	}
	break;
	case WREFRESH:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_BACKSPACE));
	}
	break;
	case REMCAPS:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_LCTL(SS_TAP(X_LEFT)) SS_TAP(X_DELETE));
	}
	break;
};
return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_ortho_4x12(
    KC_ESC  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , NTAB  ,
    JUMPBACK, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_MINS,
    CMDBSP  , ALTDEL , KC_NO  , CTRLSP , TABMOD , PGMOD  ,   ENTMOD , SPCMOD , MO(_DEL),KC_NO  , KC_BSPC, KC_DEL
  ),

[_FN1] = LAYOUT_ortho_4x12(
    _______, TAB1   , TAB2   , TAB3   , TAB4   , _______,     _______, UNDO   , _______, _______, _______, CTAB   ,
    KC_CAPS, _______, _______, _______, _______, _______,     KC_HOME, KC_LEFT, KC_UP  , KC_RIGHT,KC_END , KC_NO  ,
    _______, _______, XPANDR , _______, _______, _______,     _______, PMERGE , KC_DOWN, _______, _______, _______,
    WREFRESH,_______, _______, _______, LWORD  , RWORD  ,     RVOLD  , RVOLU  , _______, _______, _______, _______
  ),

[_FN2] = LAYOUT_ortho_4x12(
    _______, SPEAK1 , SPEAK2 , SPEAK3 , SPEAK4 , _______,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, PARADOWN, CSPEAK,    _______, _______, _______, _______, _______, _______
  ),

[_DEL] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______,     _______, UNDO   , _______, _______, _______, CTAB   ,
    REMCAPS, _______, _______, _______, _______, _______,     _______, KC_LEFT, KC_UP  ,KC_RIGHT, _______, _______,
    _______, _______, _______, _______, _______, _______,     _______, _______, KC_DOWN, _______, _______, _______,
    _______, _______, _______, KC_DEL , KC_BSPC, BWORD  ,     _______, _______, _______, _______, _______, _______
  ),

[_NUM] = LAYOUT_ortho_4x12(
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_MINS, KC_EQL, 
    KC_CAPS, _______, _______, _______, _______, _______,     KC_MINS, KC_4   , KC_5   , KC_6   , KC_COLN, _______,
    _______, _______, _______, _______, _______, KC_LBRC,     KC_RBRC, KC_1   , KC_2   , KC_3   , KC_BSLS, _______, 
    _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,     _______, _______, KC_0   , _______, _______, _______
  )
};
