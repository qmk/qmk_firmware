#include "lets-split.h"
#include "action_layer.h"

#define BASE 0

enum preonic_keycodes {
  KC_IDK = SAFE_RANGE,
  PM_RESET
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T     },
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G     },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B     },
  {KC_IDK,  KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  PM_RESET }
}

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_IDK:
      if (record->event.pressed) {
        SEND_STRING("IDK. ");
      }
      return false;
      break;
    case PM_RESET:
      if (record->event.pressed) {
        promicro_bootloader_jmp(true);
      }
      return false;
      break;
  }
  return true;
};