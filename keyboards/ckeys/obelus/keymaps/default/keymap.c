#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* LAYERS
   * ,-----------------------.
   * |     |     |     |RESET|
   * |-----+-----+-----+-----|
   * |MUSIC|     |     |     |
   * |-----+-----+-----+-----|
   * |NUMPD| NAV |GAMES|     |
   * |-----+-----+-----+-----|
   * |     |     |     |     |
   * `---------------------- '
   */
  [0] = LAYOUT_ortho_4x4( /* LAYER SELECT */
    _______, _______, _______, RESET,   \
    TO(4),   _______, _______, _______, \
    TO(1),   TO(2),   TO(3),   _______, \
    _______, _______, _______, _______  \
  ),
  /* NUMPAD
   * ,-----------------------.
   * |  7  |  8  |  9  |  *  |
   * |-----+-----+-----+-----|
   * |  4  |  5  |  6  |  -  |
   * |-----+-----+-----+-----|
   * |  1  |  2  |  3  |  +  |
   * |-----+-----+-----+-----|
   * |  0  |  .  |  /  |  =  |
   * `---------------------- '
   */
  [1] = LAYOUT_ortho_4x4( /* NUMPAD */
    KC_P7, KC_P8,   KC_P9,   KC_PAST,        \
    KC_P4, KC_P5,   KC_P6,   KC_PMNS,        \
    KC_P1, KC_P2,   KC_P3,   KC_PPLS,        \
    KC_P0, KC_PDOT, KC_PSLS, LT(5, KC_PENT)  \
  ),
  /* NUMPAD SUPPLEMENT
   * ,-----------------------.
   * |NUMLK|     |     |     |
   * |-----+-----+-----+-----|
   * |     |     |     |     |
   * |-----+-----+-----+-----|
   * |     |     |     |     |
   * |-----+-----+-----+-----|
   * |     |     |     |     |
   * `---------------------- '
   */
  [5] = LAYOUT_ortho_4x4( /* NUMPAD SUPPLEMENT */
    KC_NLCK, _______, _______, TO(0),   \
    _______, _______, _______, _______, \
    _______, _______, _______, _______, \
    _______, _______, _______, _______  \
  ),
  /* NAV
   * ,-----------------------.
   * | INS |PGUP | TAB |PRSCR|
   * |-----+-----+-----+-----|
   * | DEL |PGDN |VOLD |VOLU |
   * |-----+-----+-----+-----|
   * |HOME | UP  | END |     |
   * |-----+-----+-----+-----|
   * |LEFT |DOWN |RIGHT|ENTER|
   * `---------------------- '
   */
  [2] = LAYOUT_ortho_4x4( /* NAV CLUSTER */
    KC_INS,  KC_PGUP, KC_TAB,  KC_PSCR, \
    KC_DEL,  KC_PGDN, KC_VOLD, KC_VOLU, \
    KC_HOME, KC_UP,   KC_END,  TO(0),   \
    KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT   \
  ),
  /* GAMING
   * ,-----------------------.
   * | ESC |  1  |  2  |  3  |
   * |-----+-----+-----+-----|
   * | TAB |  Q  |  W  |  E  |
   * |-----+-----+-----+-----|
   * |SHIFT|  A  |  S  |  D  |
   * |-----+-----+-----+-----|
   * |CTRL |  C  |  R  |SPACE|
   * `---------------------- '
   */
  [3] = LAYOUT_ortho_4x4( /* GAMING */
    LT(4, KC_ESC), KC_1, KC_2, KC_3,  \
    KC_TAB,        KC_Q, KC_W, KC_E,  \
    KC_LSFT,       KC_A, KC_S, KC_D,  \
    KC_LCTL,       KC_C, KC_R, KC_SPC \
  ),
  /* MUSIC
   * ,-----------------------.
   * |     |     |     |     |
   * |-----+-----+-----+-----|
   * |     |     |     |     |
   * |-----+-----+-----+-----|
   * |     |     |     |     |
   * |-----+-----+-----+-----|
   * |TOGGL|MODE |     |     |
   * `---------------------- '
   */
  [4] = LAYOUT_ortho_4x4( /* NUMPAD SUPPLEMENT */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    MU_TOG,   MU_MOD, XXXXXXX, TO(0)    \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}
