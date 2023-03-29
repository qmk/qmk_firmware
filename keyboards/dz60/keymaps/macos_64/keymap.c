#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* ,-----------------------------------------------------------------------------------------.
   * | Esc | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   | -   | =   | Backspace |
   * |-----------------------------------------------------------------------------------------+
   * | Tab    | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | [   | ]   |   \    |
   * |-----------------------------------------------------------------------------------------+
   * | Caps     | A   | S   | D   | F   | G   | H   | J   | K   | L   | ;   | '   | Enter      |
   * |-----------------------------------------------------------------------------------------+
   * | Shift     | Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   |Shift| Up |Delete|
   * |-----------------------------------------------------------------------------------------+
   * | Ctrl | Alt  | Cmd  |               Space                |   Fn  | Alt | Left| Down|Right|
   * `-----------------------------------------------------------------------------------------'
   */
  LAYOUT_all(
    QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_DELETE,
    KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_SPC, KC_NO, MO(1), KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT),

  /* ,-----------------------------------------------------------------------------------------.
   * | ` ~ | BR- | BR+ |     |     |     |     |PREV |PLAY |NEXT |MUTE | V- | V+ |    Delete   |
   * |-----------------------------------------------------------------------------------------+
   * |        |     |     |  Up |     |     |     |     |  0  |  1  |  2  |  3  |     |  QK_BOOT |
   * |-----------------------------------------------------------------------------------------+
   * |         |     | Left| Down|Right|     |     |     |     |  4  |  5  |  6  |             |
   * |-----------------------------------------------------------------------------------------+
   * |           |     |     |     |     |     |     |     |     |  7  |  8  |  9  |     |     |
   * |-----------------------------------------------------------------------------------------+
   * |      |      |      |                                      |     |     |     |     |     |
   * `-----------------------------------------------------------------------------------------'
   */
  LAYOUT_all(
    KC_GRV , KC_SCRL, KC_PAUSE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_NO, KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_1, KC_2, KC_3, KC_TRNS, QK_BOOT,
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
