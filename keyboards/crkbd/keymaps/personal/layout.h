const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
    KC_ESC,  KC_Q,  KC_W,  KC_F,    KC_P,     KC_B,                      KC_J,     KC_L,   KC_U,    KC_Y,   KC_SCLN, KC_LBRC,
    KC_TAB,  KC_A,  KC_S,  KC_R,    KC_T,     KC_G,                      KC_M,     KC_N,   KC_E,    KC_I,   KC_O,    KC_BSPC,
    KC_LSFT, KC_Z,  KC_C,  KC_D,    KC_V,     KC_X,                      KC_K,     KC_H,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                                 KC_LCTL, KC_LOWER,  KC_SPC,     KC_ENT, KC_RAISE, KC_RALT
    ),

  [1] = LAYOUT_split_3x6_3(
    LSFT(KC_1), LSFT(KC_2), LSFT(KC_3),    LSFT(KC_4), LSFT(KC_5),    LSFT(KC_6),                   KC_7,    KC_8,   KC_9,  KC_PAST,    LSFT(KC_8),    LSFT(KC_9),
    RALT(KC_Q), KC_GRV,     RALT(KC_MINS), KC_MINS,    LSFT(KC_MINS), LSFT(KC_0),                   KC_4,    KC_5,   KC_6,  LSFT(KC_7), LSFT(KC_QUOT), LSFT(KC_BSLS),
    KC_LSFT,    KC_UNDO,    KC_COPY,       KC_DEL,     KC_PASTE,      KC_CUT,                       KC_1,    KC_2,   KC_3,  KC_PPLS,    KC_QUOT,       KC_BSLS,
                                                       KC_LCTL,       _______,    KC_SPC,     KC_0, _______, KC_NUBS
    ),

  [2] = LAYOUT_split_3x6_3(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_INS,  KC_HOME, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                       KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX, KC_EXEC, KC_APP,  KC_LGUI,                      KC_FIND, KC_END,  XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX,
                                        KC_LCTL, _______,  KC_SCRL,   KC_CAPS, _______, KC_RALT
    ),

  [3] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SCRL, KC_PAUS,                      XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,RGB_RMOD, RGB_MOD,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  )
};
