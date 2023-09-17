#include QMK_KEYBOARD_H

#define _BL0 0
#define _FL1 1
#define _FL2 2
#define _FL3 3

#define MACOSLK LCTL(LGUI(KC_Q)) // CTRL+CMD+Q == screen lock in macOS 10.13+

enum rys_keycodes {
  STOKEN1 = SAFE_RANGE,
  STOKEN2,
  STOKEN3,
  STOKEN4,
  STOKEN5,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case STOKEN1:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN1);
      }
      break;
    case STOKEN2:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN2);
      }
      break;
    case STOKEN3:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN3);
      }
      break;
    case STOKEN4:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN4);
      }
      break;
    case STOKEN5:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN5);
      }
      break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap base layer (_BL0) - default layer
   * ,---------------------------.
   * | ST1  | ST2  | ST3  | ST4  |
   * |---------------------------|
   * |MO(1) | LOCK | VOL- | VOL+ |
   * `---------------------------'
   */
   [_BL0] = LAYOUT(
     STOKEN1, STOKEN2, STOKEN3, STOKEN4,
    MO(_FL1), MACOSLK, KC_VOLD, KC_VOLU),
  /* Keymap base layer (_FL1) - function layer 1
   * ,---------------------------.
   * |      |      |      |      |
   * |---------------------------|
   * |      | ST5  |   \  | RST  |
   * `---------------------------'
   */
   [_FL1] = LAYOUT(
     _______, _______, _______, _______,
     _______, STOKEN5, KC_NUBS, QK_BOOT),
  /* Keymap base layer (_FL2) - function layer 2
   * ,---------------------------.
   * |      |      |      |      |
   * |---------------------------|
   * |      |      |      |      |
   * `---------------------------'
   */
   [_FL2] = LAYOUT(
     _______, _______, _______, _______,
     _______, _______, _______, _______),
  /* Keymap base layer (_FL3) - function layer 3
   * ,---------------------------.
   * |      |      |      |      |
   * |---------------------------|
   * |      |      |      |      |
   * `---------------------------'
   */
   [_FL3] = LAYOUT(
     _______, _______, _______, _______,
     _______, _______, _______, _______),
};
