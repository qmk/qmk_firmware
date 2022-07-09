#include QMK_KEYBOARD_H 

enum sofle_layers {
    _WORKMAN,
    _QWERTY,
    _MIDI,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    KC_WORKMAN = SAFE_RANGE,
    KC_QWERTY,
    KC_MIDI,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * WORKMAN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Prnt |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  |  '   |
 * |------+------+------+------+------+------|  MUTE |    | Run   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   M  |   C  |   V  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_WORKMAN] = LAYOUT(
  KC_GRV,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                                KC_6,     KC_7,     KC_8,    KC_9,   KC_0,    KC_PSCR,
  KC_ESC,  KC_Q,   KC_D,    KC_R,    KC_W,     KC_B,                                KC_J,     KC_F,     KC_U,    KC_P,   KC_SCLN, KC_BSPC,
  KC_TAB,  KC_A,   KC_S,    KC_H,    KC_T,     KC_G,                                KC_Y,     KC_N,     KC_E,    KC_O,   KC_I,    KC_QUOT,
  KC_LSFT, KC_Z,   KC_X,    KC_M,    KC_C,     KC_V,     KC_MUTE,      LALT(KC_F2), KC_K,     KC_L,     KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                   KC_LGUI, KC_LALT, KC_LCTRL, KC_LOWER, KC_ENT,       KC_SPC,      KC_RAISE, KC_RCTRL, KC_RALT, KC_RGUI
),

/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Prnt |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    | Run   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_GRV,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                               KC_6,     KC_7,     KC_8,    KC_9,   KC_0,    KC_PSCR,
  KC_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,                               KC_Y,     KC_U,     KC_I,    KC_O,   KC_P,    KC_BSPC,
  KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,     KC_G,                               KC_H,     KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,     KC_MUTE,     LALT(KC_F2), KC_N,     KC_M,     KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                   KC_LGUI, KC_LALT, KC_LCTRL, KC_LOWER, KC_SPC,      KC_ENT,      KC_RAISE, KC_RCTRL, KC_RALT, KC_RGUI
),

/* MIDI
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Pnic | OCT0 | OCT1 | OCT2 | OCT3 | OCT4 |                    | OCT5 | OCT6 | OCT7 |      |      | MTOG |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | SQTG |      |      |      |C#/Db |D#/Eb |                    |      |F#/Gb |G#/Ab |Bb/A# |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | C    | D    | E    |-------.    ,-------| F    | G    | A    | B    |      | Wkmn |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      | TNSD | TNSU |-------|    |-------| BNDD | BNDU | CHUP | CHDN |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      | Susd | /OCTDN  /       \OCTUP \  | Chrd |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_MIDI] = LAYOUT(
  MI_ALLOFF, MI_OCT_0, MI_OCT_1,  MI_OCT_2,  MI_OCT_3,  MI_OCT_4,                       MI_OCT_5, MI_OCT_6, MI_OCT_7, _______, _______, MI_TOG,
  SQ_TOG,    SQ_TMPD,  SQ_TMPU,   _______,   MI_Cs,     MI_Ds,                          _______,  MI_Fs,    MI_Gs,    MI_As,   _______, _______,
  _______,   SQ_RES_2, SQ_RES_4,  MI_C,      MI_D,      MI_E,                           MI_F,     MI_G,     MI_A,     MI_B,    MI_C_1,  KC_WORKMAN,
  _______,   SQ_RES_8, SQ_RES_16, SQ_RES_32, MI_TRNSD,  MI_TRNSU, _______,    _______,  MI_BENDD, MI_BENDU, _______,  _______, _______, _______,
                       _______,   _______,   _______,   MI_SUS,   MI_OCTD,    MI_OCTU,  _______,  _______,  _______,  _______
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |   |  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |      |      |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______,  _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, KC_F12,
  _______,  _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, KC_PIPE,
  _______,  KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, _______, _______, KC_BSLS, _______,
                     _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | ASTG |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |  Up  |      | RStp | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down | Rght | Rec1 | Ply1 |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | Home | End  | Rec2 | Ply2 |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, KC_ASTG,
  _______, _______, _______, _______, _______, _______,                         _______, _______, KC_UP,   _______, DM_RSTP, KC_DEL,
  _______, _______, _______, _______, _______, _______,                         _______, KC_LEFT, KC_DOWN, KC_RGHT, DM_REC1, DM_PLY1,
  _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, KC_HOME, KC_END,  DM_REC2, DM_PLY2,
                    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Rset |      |      |      |      |      |                    |      |      |      |      |      | Qwrt |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      | Wkmn |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QWERTY,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WORKMAN,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_MIDI, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
)};

#ifdef OLED_ENABLE

static void oled_screen(void) {
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR(">nix "), false);
    oled_write_ln_P(PSTR(">rust"), false);
    oled_write_ln_P(PSTR(">py &"), false);
    oled_write_ln_P(PSTR(">rum"), false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR(" . ."), false);
    oled_write_ln_P(PSTR("  u "), false);
    oled_write_ln_P(PSTR("    d"), false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("mchal"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_screen();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
            }
            return false;
        case KC_MIDI:
            if (record->event.pressed) {
              set_single_persistent_default_layer(_MIDI);
            }
						return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
		}
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDOWN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif
