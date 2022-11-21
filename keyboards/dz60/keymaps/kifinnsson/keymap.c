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
    KI_BKSP,
    KI_BSLS,
    KI_WLFT,
    KI_WRGT,
    };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT_all(
		QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,   KC_U,     KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,
		MO(1),   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,   KC_E,     KC_I,    KC_O,    KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(2),   KC_K,   KC_M,     KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, KC_RSFT, XXXXXXX,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, MO(1),  XXXXXXX,  MO(3),   KC_RCTL),

	LAYOUT_all(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
		_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		_______, XXXXXXX, KC_TAB,  KC_LSFT, KC_LCTL, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_CAPS, XXXXXXX,
		_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,,
		_______, _______, XXXXXXX, KC_ENT,  KC_ENT,  KC_ENT,  _______, _______, _______, _______, QK_BOOT),

	LAYOUT_all(
		KI_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KI_BKSP,
		_______, KI_1,    KI_2,    KI_3,    KI_4,    KI_5,    KI_6,    KI_7,    KI_8,    KI_9,    KI_10,   KI_11,   KI_12,   KI_BSLS,
		_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, KI_WLFT, KI_WRGT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		_______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX),

	LAYOUT_all(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Keycodes Starting with KI_ are place holders for my personal macros. They are set below. Most are simple SEND_STRINGS().
    case KI_ESC:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_1:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_2:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_3:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_4:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_5:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_6:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_7:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_8:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_9:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_10:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_11:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_12:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_BKSP:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_BSLS:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key

    //Windows Win+Left tap to move window without resetting KC_LGUI
    //Additional code is in matrix_scan_user()
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
      return false; // Skip all further processing of this key
    //Windows Win+Right tap to move window without resetting KC_LGUI
    //Additional code is in matrix_scan_user()
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
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

//Check if KC_LGUI is active in KI_WLFT and KI_WRGT
void matrix_scan_user(void) { 
  if (is_lgui_active) {
    if (timer_elapsed(lgui_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_lgui_active = false;
    }
  }
}