#include "chocopad.h"

#define _BASE 0
#define _FN1 1
#define _FN2 2

#define KC_L1 LT(1, KC_P0)
#define KC_L2 LT(2, KC_SPC)
#define KC_MAC1 ADMIN
#define KC_MAC2 SMSPC
#define KC_M192 M192
#define KC_M255 M255

enum custom_keycodes {
  NUMPAD = SAFE_RANGE,
  ADMIN,
  SMSPC,
  M192,
  M255
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_4x4(
    KC_P7,   KC_P8,   KC_P9,   KC_BSPC,
    KC_P4,   KC_P5,   KC_P6,   KC_TAB ,
    KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_L1,   KC_L2,   KC_PDOT, KC_PSLS
  ),

  [_FN1] = LAYOUT_ortho_4x4(
    KC_ESC,  KC_MAC1, KC_MAC2, KC_DEL ,
    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_M192, KC_M255, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, _______, XXXXXXX
  ),

  [_FN2] = LAYOUT_ortho_4x4(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
    BL_STEP, _______, XXXXXXX, XXXXXXX
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADMIN:
      if (record->event.pressed) {
	SEND_STRING("Administrator");
      }
      return false;
      break;
    case SMSPC:
      if (record->event.pressed) {
	SEND_STRING("Simspace1!");
      }
      return false;
      break;
    case M192:
      if (record->event.pressed) {
	SEND_STRING("192.168.");
      }
      return false;
      break;
    case M255:
      if (record->event.pressed) {
	SEND_STRING("255");
      }
      return false;
      break;
  }
  return true;
};
