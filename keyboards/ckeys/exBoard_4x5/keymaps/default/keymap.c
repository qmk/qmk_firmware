#include QMK_KEYBOARD_H

enum layers {
  _BASE,                // base layer
  _LAYERS,              // layer of all layers
  _MUSIC,               // music mode
  _MIDI,                // midi mode
  _MOUSE,               // mousekeys
  _TERMINAL,            // terminal
  _ADMIN                // admin duties
};

enum custom_keycodes {
  TERM_ABOUT = SAFE_RANGE,
  TERM_PRINT,
  TERM_FLUSH,
  TERM_HELP,
  CKEYS_ABOUT,
};

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//           ┌─────────┬─────────┬─────────┬─────────┬─────────┐
//           │         │         │         │         │         │
//           │    7    │    8    │    9    │    /    │  ADMIN  │
//  ROTORY   │         │         │         │         │         │
//  RIGHT:   ├─────────┼─────────┼─────────┼─────────┼─────────┤
//  VOL UP   │         │         │         │         │         │
//           │    4    │    5    │    6    │    *    │  MOUSE  │
//  ROTORY   │         │         │         │         │         │
//  LEFT:    ├─────────┼─────────┼─────────┼─────────┼─────────┤
//  VOL DOWN │         │         │         │         │         │
//           │    1    │    2    │    3    │    -    │  MIDI   │
//           │         │         │         │         │         │
// ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
// │         │         │         │         │         │         │
// │ LAYERS  │    0    │    .    │    =    │    +    │  MUSIC  │
// │         │         │         │         │         │         │
// └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

  [_BASE] = LAYOUT(
    KC_KP_7, KC_KP_8,   KC_KP_9,     KC_PSLS, TG(_ADMIN), TG(_LAYERS) \
    KC_KP_4, KC_KP_5,   KC_KP_6,     KC_PAST, TG(_MOUSE),             \
    KC_KP_1, KC_KP_2,   KC_KP_3,     KC_PMNS, TG(_MIDI),              \
    KC_KP_0, KC_KP_DOT, KC_KP_EQUAL, KC_PPLS, TG(_MUSIC)              \
  ),
    /* LAYERS
   * ,---------------------------.
   * |  MUSIC  |     |     |  X  |
   * |---------+-----+-----+-----|
   * |  MOUSE  |     |     |     |
   * |---------+-----+-----+-----|
   * |TERMINAL |     |     |     |
   * |---------+-----+-----+-----|
   * |  ADMIN  |     |     |     |
   * `---------------------------'
   */
  [_LAYERS] = LAYOUT(
    _______, _______, _______, _______, TG(_ADMIN), TG(_BASE) \
    _______, _______, _______, _______, TG(_MOUSE),           \
    _______, _______, _______, _______, TG(_MIDI),            \
    _______, _______, _______, _______, TG(_MUSIC)            \
  ),

// MUSIC LAYER
//           ┌─────────┬─────────┬─────────┬─────────┬─────────┐
//           │         │         │         │         │         │
//           │    ♫    │    ♫    │    ♫    │    ♫    │    ♫    │
//  ROTORY   │         │         │         │         │         │
//  RIGHT:   ├─────────┼─────────┼─────────┼─────────┼─────────┤
//  OCT UP   │         │         │         │         │         │
//           │    ♫    │    ♫    │    ♫    │    ♫    │    ♫    │
//  ROTORY   │         │         │         │         │         │
//  LEFT:    ├─────────┼─────────┼─────────┼─────────┼─────────┤
//  OCT DOWN │         │         │         │         │         │
//           │    ♫    │    ♫    │    ♫    │    ♫    │    ♫    │
//           │         │         │         │         │         │
// ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
// │         │         │         │         │         │         │
// │  BASE   │    ♫    │    ♫    │    ♫    │    ♫    │    ♫    │
// │         │         │         │         │         │         │
// └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

  [_MUSIC] = LAYOUT(
    MU_ON, MU_ON, MU_ON, MU_ON, TG(_BASE), MU_OFF,            \
    MU_ON, MU_ON, MU_ON, MU_ON, MU_ON, \
    MU_ON, MU_ON, MU_ON, MU_ON, MU_ON,            \
    MU_ON, MU_ON, MU_ON, MU_ON, MU_ON \
  ),

// MIDI LAYER
//           ┌─────────┬─────────┬─────────┬─────────┬─────────┐
//           │         │         │         │         │         │
//           │   D♯    │    E    │    F    │   F♯    │    G    │
//  ROTORY   │         │         │         │         │         │
//  RIGHT:   ├─────────┼─────────┼─────────┼─────────┼─────────┤
//  OCT UP   │         │         │         │         │         │
//           │   A♯    │    B    │    C    │   C♯    │    D    │
//  ROTORY   │         │         │         │         │         │
//  LEFT:    ├─────────┼─────────┼─────────┼─────────┼─────────┤
//  OCT DOWN │         │         │         │         │         │
//           │    F    │   F♯    │    G    │   G♯    │    A    │
//           │         │         │         │         │         │
// ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
// │         │         │         │         │         │         │
// │  BASE   │    C    │   C♯    │    D    │   D♯    │    E    │
// │         │         │         │         │         │         │
// └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

  [_MIDI] = LAYOUT(
    MI_Ds_3, MI_E_3,  MI_F_3, MI_Fs_3, MI_G_3, TG(_BASE),            \
    MI_As_2, MI_B_2,  MI_C_3, MI_Cs_3, MI_D_3, \
    MI_F_2,  MI_Fs_2, MI_G_2, MI_Gs_2, MI_A_2,            \
    MI_C_2,  MI_Cs_2, MI_D_2, MI_Ds_2, MI_E_2 \
  ),

    /* MOUSE
   * ,-------------------------------------------------.
   * |  BUTTON 5 |           | SCROLL UP  |     X      |
   * |-----------+-----------+------------+------------|
   * |     X     |LEFT CLICK |     UP     |RIGHT CLICK |
   * |-----------+-----------+------------+------------|
   * |  BUTTON 4 |   LEFT    |    DOWN    |   RIGHT    |
   * |-----------+-----------+------------+------=-----|
   * |  BUTTON 3 |SCROLL LEFT|SCROLL DOWN |SCROLL RIGHT|
   * `-------------------------------------------------'
   */
  [_MOUSE] = LAYOUT(
    KC_MS_BTN5, _______,       KC_MS_WH_UP,   _______, _______, _______,        \
    _______,    KC_MS_BTN1,    KC_MS_UP,      KC_MS_BTN2, _______,   \
    KC_MS_BTN4, KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_RIGHT,_______,   \
    KC_MS_BTN3, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_RIGHT, _______, \
  ),
    /* TERMINAL
   * ,---------------------------------------.
   * |            |ABOUT|          |    X    |
   * |------------+-----+----------+---------|
   * |TERMINAL OFF|PRINT|          |         |
   * |------------+-----+----------+---------|
   * |     X      |FLUSH|          |         |
   * |------------+-----+----------+---------|
   * |TERMINAL ON |HELP |          |         |
   * `--------=======------------------------'
   */
  [_TERMINAL] = LAYOUT(
    _______,    TERM_ABOUT, _______, _______, _______, _______,\
    TERM_OFF,   TERM_PRINT, _______, _______, _______, \
    _______,    TERM_FLUSH, _______, _______, _______, \
    TERM_ON,    TERM_HELP , _______, _______, _______ \
  ),
    /* ADMIN
   * ,-----------------------------------------.
   * |   RESET    |     |           |    X     |
   * |------------+-----+-----------+----------|
   * |ABOUT CKEYS |     |           |          |
   * |------------+-----+-----------+----------|
   * |            |     |CLICKY UP  |CLICKY OFF|
   * |------------+-----+-----------+----------|
   * |     X      |     |CLICKY DOWN|CLICKY ON |
   * `-----------------------------------------'
   */
  [_ADMIN] = LAYOUT(
    RESET,       _______, _______, _______, _______, _______, \
    CKEYS_ABOUT, _______, _______, _______, _______, \
    _______,     _______, _______, CK_OFF,  _______, \
    _______,     _______, _______, CK_ON,   _______, \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TERM_ABOUT:
      if (record->event.pressed) {
        // when keycode TERM_ABOUT is pressed
        SEND_STRING("about"SS_TAP(X_ENTER));
      } else {
        // when keycode TERM_ABOUT is released
      }
      break;
    case TERM_PRINT:
      if (record->event.pressed) {
        SEND_STRING("print"SS_TAP(X_ENTER));
      } else { }
      break;
    case TERM_FLUSH:
      if (record->event.pressed) {
        SEND_STRING("flush"SS_TAP(X_ENTER));
      } else { }
      break;
    case TERM_HELP:
      if (record->event.pressed) {
        SEND_STRING("help"SS_TAP(X_ENTER));
      } else { }
      break;
    case CKEYS_ABOUT:
      if (record->event.pressed) {
        SEND_STRING("https://cKeys.org"SS_TAP(X_ENTER)"Making people smile one keyboard at a time."SS_TAP(X_ENTER)"cKeys is a volunteer-run 501(c)(3) nonprofit organization."SS_TAP(X_ENTER));
      } else { }
      break;
  }
  return true;
};
