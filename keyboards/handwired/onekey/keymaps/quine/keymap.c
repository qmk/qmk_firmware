#include <handwired/onekey/onekey.h>
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { LAYOUT_ortho_1x1(KC_A) };
const char *buf[30] = {
"#include <handwired/onekey/onekey.h>",
"const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { LAYOUT_ortho_1x1(KC_A) };",
"const char *buf[30] = {",
"",
"};",
"bool process_record_user(uint16_t keycode, keyrecord_t *record) {",
"  switch(keycode) {",
"    case KC_A:",
"      if (record->event.pressed) {",
"        for (int i = 0; i < 3; i++) {",
"          send_string(buf[i]);",
"          tap_code(KC_ENT);",
"        }",
"        for (int i = 0; i < 30; i++) {",
"          send_string(buf[3]);",
"          tap_code16(S(KC_QUOT));",
"          send_string(buf[i]);",
"          tap_code16(S(KC_QUOT));",
"          tap_code(KC_COMM);",
"          tap_code(KC_ENT);",
"        }",
"        for (int i = 4; i < 30; i++) {",
"          send_string(buf[i]);",
"          tap_code(KC_ENT);",
"        }",
"      }",
"      return false;",
"  }",
"  return true;",
"};",
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_A:
      if (record->event.pressed) {
        for (int i = 0; i < 3; i++) {
          send_string(buf[i]);
          tap_code(KC_ENT);
        }
        for (int i = 0; i < 30; i++) {
          send_string(buf[3]);
          tap_code16(S(KC_QUOT));
          send_string(buf[i]);
          tap_code16(S(KC_QUOT));
          tap_code(KC_COMM);
          tap_code(KC_ENT);
        }
        for (int i = 4; i < 30; i++) {
          send_string(buf[i]);
          tap_code(KC_ENT);
        }
      }
      return false;
  }
  return true;
};

