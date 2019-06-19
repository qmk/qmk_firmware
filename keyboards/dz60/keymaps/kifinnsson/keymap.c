#include QMK_KEYBOARD_H

bool is_lgui_active = false;
uint16_t lgui_timer = 0;


//Macro Declarations
enum my_keycodes {
  KI_NO = SAFE_RANGE,
    KI_1,
    KI_2,
    KI_3,
    KI_4,
    KI_5,
    KI_6,
    KI_7,
    KI_8,
    KI_9,
    KI_10,
    KI_11,
    KI_12,
    KI_ESC,
		KI_KI,
		KI_KI2,
		WG_PHON,
		KI_SIG,
    KI_BKSP,
    KI_BSLS,
    KI_WLFT,
    KI_WRGT,
    KI_ININ
    };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT_all(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,   KC_U,     KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,
		MO(1),   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,   KC_E,     KC_I,    KC_O,    KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(2),   KC_K,   KC_M,     KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, KC_RSFT, XXXXXXX,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, MO(1),  XXXXXXX,  MO(3),   KC_RCTL),

	LAYOUT_all(
		KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		_______, KI_ININ, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,
		_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,,
		_______, _______, XXXXXXX, KC_ENT,  KC_ENT,  KC_ENT,  _______, _______, _______, _______, RESET),

	LAYOUT_all(
		KI_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  WG_PHON, KI_BKSP,
		XXXXXXX, KI_1,    KI_2,    KI_3,    KI_4,    KI_5,    KI_6,    KI_7,    KI_8,    KI_9,    KI_10,   KI_11,   KI_12,   KI_BSLS,
		KC_CAPS, XXXXXXX, XXXXXXX, KI_SIG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KI_KI2,  _______, KI_KI,   _______, KI_WLFT, KI_WRGT, _______, _______, _______, _______,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,),

	LAYOUT_all(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KI_BKSP:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LCTRL)"v"SS_UP(X_LCTRL)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_BSPACE)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_BSPACE)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_BSPACE)SS_TAP(X_BSPACE)SS_TAP(X_BSPACE)SS_TAP(X_BSPACE));
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_BSLS:
      if (record->event.pressed) {
        SEND_STRING("https://apps.mypurecloud.com/directory/#/engage/admin/interactions/"SS_DOWN(X_LCTRL)"v"SS_UP(X_LCTRL));
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_ESC:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key

    case KI_KI:
      if (record->event.pressed) {
        SEND_STRING("ki.finnsson");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_KI2:
      if (record->event.pressed) {
        SEND_STRING("Ki Finnsson");
      } else {
        
      }
    case KI_9:
      if (record->event.pressed) {
        SEND_STRING("98741236");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_ININ:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)"98741236"SS_TAP(X_TAB)SS_TAP(X_TAB)"98741236"SS_TAP(X_TAB)SS_TAP(X_DELETE));
      } else {
        
      }
      return false; // Skip all further processing of this key      
    case WG_PHON:
      if (record->event.pressed) {
        SEND_STRING("1-877-435-7948");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_SIG:
      if (record->event.pressed) {
        SEND_STRING("Ki Finnsson"SS_TAP(X_ENTER));
				SEND_STRING("IT Service Improvement Specialist"SS_TAP(X_ENTER));
				SEND_STRING("Western Governors University"SS_TAP(X_ENTER)SS_TAP(X_ENTER));
				SEND_STRING("4001 South 700 East, Suite 700"SS_TAP(X_ENTER));
				SEND_STRING("Salt Lake City, UT 84107"SS_TAP(X_ENTER));
				SEND_STRING("P: 877.435.7948"SS_TAP(X_ENTER));
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_WLFT:
      if (record->event.pressed) {
        if (!is_lgui_active) {
          is_lgui_active = true;
          register_code(KC_LGUI);
        } 
        lgui_timer = timer_read();
        tap_code(KC_LEFT);
      } else {
        
      }
      return false;
    case KI_WRGT:
      if (record->event.pressed) {
        if (!is_lgui_active) {
          is_lgui_active = true;
          register_code(KC_LGUI);
        } 
        lgui_timer = timer_read();
        tap_code(KC_RIGHT);
      } else {
        
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

void matrix_scan_user(void) { 
  if (is_lgui_active) {
    if (timer_elapsed(lgui_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_lgui_active = false;
    }
  }
}