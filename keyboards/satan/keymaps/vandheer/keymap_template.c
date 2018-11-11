const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BLANK
   * ,-----------------------------------------------------------.
   * |    |   |   |   |   |   |   |   |   |   |   |   |   |      |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |Nav~Esc|   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |Shift   |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |Ctrl|Alt |Gui |                        |Gui |Alt |Fn |Macro|
   * `-----------------------------------------------------------'
   */
[_BLANK] = KEYMAP_ANSI(
  KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO, \
  KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO, \
  KC_TRNS,  KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,          KC_NO,  \
  KC_TRNS,  KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,                    KC_NO, \
  KC_TRNS,  KC_TRNS,  KC_TRNS,                         KC_TRNS,               KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS),
};
