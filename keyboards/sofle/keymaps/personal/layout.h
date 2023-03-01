const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   !  |   "  |   #  |   $  |   %  |                    |   &  |   /  |   |  |   \  |   @  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   Ñ  |  ´   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   R  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  | Bspc |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   C  |   D  |   V  |   X  |-------|    |-------|   K  |   H  |   ,  |   .  |   -  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTR | LGUI | LALT |LOWER | /Space  /       \Enter \  |RAISE | ALTGR| RGUI | RCTRL|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_COLEMAK] = LAYOUT(
  KC_ESC,  LSFT(KC_1),  LSFT(KC_2),  LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),                       LSFT(KC_6), LSFT(KC_7), KC_GRV,  RALT(KC_MINS), RALT(KC_Q), KC_MINS,
  KC_CAPS, KC_Q,        KC_W,        KC_F,       KC_P,       KC_B,                             KC_J,       KC_L,       KC_U,    KC_Y,          KC_SCLN,    KC_LBRC,
  KC_TAB,  KC_A,        KC_S,        KC_R,       KC_T,       KC_G,                             KC_M,       KC_N,       KC_E,    KC_I,          KC_O,       KC_BSPC,
  KC_LSFT, KC_Z,        KC_C,        KC_D,       KC_V,       KC_X,       KC_MUTE,     RGB_TOG, KC_K,       KC_H,       KC_COMM, KC_DOT,        KC_SLSH,    KC_RSFT,
                        TD(TD_NUM),  KC_LGUI,    KC_LALT,    KC_LOWER,   KC_SPC,      KC_ENT,  KC_RAISE,   KC_RALT,    KC_RGUI, TD(TD_ARS)
),

/* LOWER
 * ,------------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2   |  F3  |  F4  |  F5  |  F6  |                    |   7  |   8  |   9  |   /  |   (  |   )  |
 * |------+-------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F7  |  F8   |  F9  |  F10 |  F11 |  F12 |                    |   4  |   5  |   6  |   *  |   [  |   ]  |
 * |------+-------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |Colemak|Lower |Raise |      |      |-------.    ,-------|   1  |   2  |   3  |   -  |   {  |   }  |
 * |------+-------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |  UNDO | COPY |  DEL | PASTE| CUT  |-------|    |-------|   =  |   0  |   .  |   +  |   <  |   >  |
 * `------------------------------------------/       /     \      \-----------------------------------------.
 *            | LCTR | LGUI | LALT |LOWER | /Space  /       \Enter \  |RAISE | ALTGR| RGUI | RCTRL|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------.            `------.`---------------------------.
 */
[_LOWER] = LAYOUT(
  KC_F1,   KC_F2,      KC_F3,     KC_F4,     KC_F5,    KC_F6,                                 KC_7,    KC_8,  KC_9,    KC_PSLS,    LSFT(KC_8),    LSFT(KC_9),
  KC_F7,   KC_F8,      KC_F9,     KC_F10,    KC_F11,   KC_F12,                                KC_4,    KC_5,  KC_6,    KC_PAST, LSFT(KC_QUOT), LSFT(KC_BSLS),
  XXXXXXX, KC_COLEMAK, KC_PLOWER, KC_PRAISE, XXXXXXX,  XXXXXXX,                               KC_1,    KC_2,  KC_3,    KC_PMNS,       KC_QUOT,       KC_BSLS,
  KC_LSFT, KC_UNDO,    KC_COPY,   KC_DEL,    KC_PASTE, KC_CUT,      _______,       _______, LSFT(KC_0),    KC_0,  KC_PDOT, KC_PPLS,       KC_NUBS, LSFT(KC_NUBS),
                       TD(TD_LCMK),   _______,   _______,  _______, _______,       _______,    _______, _______,  _______, TD(TD_ARS)
),

/* RAISE
 * ,------------------------------------------.                    ,-----------------------------------------.
 * |      |       |      |PRNSCR|SCRLCK| PAUSE|                    |      |      |      |      |      |      |
 * |------+-------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |       |      |      |      |      |                    |  INS | HOME |  Up  | PGUP |      |      |
 * |------+-------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |Colemak|Lower |Raise |      |      |-------.    ,-------|  DEL | Left | Down | Right|      |      |
 * |------+-------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|       |      |      |      |      |-------|    |-------|      | END  |      | PGDN |      |      |
 * `------------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTR | LGUI | LALT |LOWER | /Space  /       \Enter \  |RAISE | ALTGR| RGUI | RCTRL|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  XXXXXXX, XXXXXXX,    XXXXXXX,    KC_PSCR,   KC_SCRL,  KC_PAUS,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX,  XXXXXXX,                         KC_INS,  KC_HOME, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_COLEMAK, KC_PLOWER,  KC_PRAISE, XXXXXXX,  XXXXXXX,                         KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
  KC_LSFT, XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX,  XXXXXXX, _______,       _______, XXXXXXX,  KC_END, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX,
                       TD(TD_NUM), _______,   _______,  _______, _______,       _______, _______, _______, _______, TD(TD_RCMK)
),

/* ADJUST
 * ,------------------------------------------.                    ,-----------------------------------------.
 * |       |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |-------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |       |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |-------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |       |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |-------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |       |      |      |      |      |      |-------|    |-------|PreRGB|PosRGB|      |      |      |      |
 * `------------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | / Space /        \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `----------------------------------'             '------''---------------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, RGB_RMOD, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    _______, _______, _______, _______, _______,     _______, _______,  _______, _______, _______
  )
};
