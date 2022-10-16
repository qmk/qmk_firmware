// Copyright 2022 Michal S. (@ihatethefrench)
// SPDX-License-Identifier: GPL-2.0-only

#include QMK_KEYBOARD_H 

// This specifies the layers that will be used
enum sofle_layers {
    _WORKMAN,
    _QWERTY,
    _MIDI,
    _LOWER,
    _RAISE,
    _ADJUST
};

// This specifies any custom keycodes I might have set
enum custom_keycodes {
    KC_WORKMAN = SAFE_RANGE,
    KC_QWERTY,
    KC_MIDI,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST
};

// Here the keymaps are defined in matrix form using KC_XYZ form keycodes
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * WORKMAN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Prnt |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  |  '   |
 * |------+------+------+------+------+------|       |    | MUTE  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   M  |   C  |   V  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_WORKMAN] = LAYOUT(
  KC_GRV,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                            KC_6,     KC_7,     KC_8,    KC_9,   KC_0,    KC_PSCR,
  KC_ESC,  KC_Q,   KC_D,    KC_R,    KC_W,     KC_B,                            KC_J,     KC_F,     KC_U,    KC_P,   KC_SCLN, KC_BSPC,
  KC_TAB,  KC_A,   KC_S,    KC_H,    KC_T,     KC_G,                            KC_Y,     KC_N,     KC_E,    KC_O,   KC_I,    KC_QUOT,
  KC_LSFT, KC_Z,   KC_X,    KC_M,    KC_C,     KC_V,     XXXXXXX,      KC_MUTE, KC_K,     KC_L,     KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                   KC_LGUI, KC_LALT, KC_LCTL,  KC_LOWER, KC_ENT,       KC_SPC,  KC_RAISE, KC_RCTL, KC_RALT, KC_RGUI
),

/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Prnt |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    | MUTE  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_GRV,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                           KC_6,       KC_7,     KC_8,    KC_9,   KC_0,    KC_PSCR,
  KC_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,                           KC_Y,       KC_U,     KC_I,    KC_O,   KC_P,    KC_BSPC,
  KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,     KC_G,                           KC_H,       KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,     XXXXXXX,     KC_MUTE, KC_N,       KC_M,     KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                   KC_LGUI, KC_LALT, KC_LCTL,  KC_LOWER, KC_SPC,      KC_ENT,  KC_RAISE, KC_RCTL, KC_RALT, KC_RGUI
),

/* MIDI
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Pnic | OCT0 | OCT1 | OCT2 | OCT3 | OCT4 |                    | OCT5 | OCT6 | OCT7 |      |      | MTOG |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |G#/Ab |Bb/A# |      |C#/Db |D#/Eb |                    |      |F#/Gb |G#/Ab |Bb/A# |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | A    | B    | C    | D    | E    |-------.    ,-------| F    | G    | A    | B    | C    | Wkmn |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      | TNSD | TNSU |-------|    |-------| BNDD | BNDU |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      | Susd | /OCTDN  /       \OCTUP \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_MIDI] = LAYOUT(
  MI_ALLOFF, MI_OCT_0, MI_OCT_1, MI_OCT_2, MI_OCT_3, MI_OCT_4,                      MI_OCT_5, MI_OCT_6, MI_OCT_7, _______, _______, MI_TOG,
  _______,   MI_Gs,    MI_As,    _______,  MI_Cs_1,  MI_Ds_1,                       _______,  MI_Fs_1,  MI_Gs_1,  MI_As_1, _______, _______,
  _______,   MI_A,     MI_B,     MI_C_1,   MI_D_1,   MI_E_1,                        MI_F_1,   MI_G_1,   MI_A_1,   MI_B_1,  MI_C_2,  KC_WORKMAN,
  _______,   _______,  _______,  _______,  MI_TRNSD, MI_TRNSU, _______,    _______, MI_BENDD, MI_BENDU, _______,  _______, _______, _______,
                       _______,  _______,  _______,  MI_SUS,   MI_OCTD,    MI_OCTU, _______,  _______,  _______,  _______
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |   |  |
 * |------+------+------+------+------+------|       |    | Run   |------+------+------+------+------+------|
 * |      |  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |      |      |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______,  _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, KC_F12,
  _______,  _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, KC_PIPE,
  _______,  KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       LALT(KC_F2), KC_LBRC, KC_RBRC, _______, _______, KC_BSLS, _______,
                     _______, _______, _______, _______, _______,       _______,     _______, _______, _______, _______
),

/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | ASTG |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |  Up  |      |      | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down | Rght |      | Wkmn |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      | Midi |      |      |-------|    |-------|      |      | Home | End  |      | Qwrt |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, KC_ASTG,
  _______, _______, _______, _______, _______, _______,                         _______, _______, KC_UP,   _______, _______, KC_DEL,
  _______, _______, _______, _______, _______, _______,                         _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_WORKMAN,
  _______, _______, _______, KC_MIDI, _______, _______, _______,       _______, _______, _______, KC_HOME, KC_END,  _______, KC_QWERTY,
                    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
)};

// This section only compiles if OLED_ENABLE is set to `yes` in rules.mk
#ifdef OLED_ENABLE

// Defining my custom text to draw to the screen :)
static void oled_screen(void) {
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR(">nix "), false);
    oled_write_ln_P(PSTR(">rust"), false);
    oled_write_ln_P(PSTR(">hs &"), false);
    oled_write_ln_P(PSTR(">rum"), false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR(" . ."), false);
    oled_write_ln_P(PSTR("  u "), false);
    oled_write_ln_P(PSTR("    d"), false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("mchal"), false);
}

// Set correct rotation so the text doesn't end up sideways
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

// I only draw to the right screen because I accidentally
// burned the left one with a soldering iron. Oops.
bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_screen();
    }
    return false;
}

#endif

// This section defines custom keycodes, which I use to manage layers
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
    }
    return true;
}

// This section only compiles if ENCODER_ENABLE is set to `yes` in rules.mk
#ifdef ENCODER_ENABLE

// This section is like the keymap matrix, but for rotary encoders
// My left encoder is currently not working, so I'm using Layers to cope :')
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_WORKMAN] = { ENCODER_CCW_CW(_______,     _______), ENCODER_CCW_CW(KC_VOLD,     KC_VOLU      )},
    [_QWERTY]  = { ENCODER_CCW_CW(_______,     _______), ENCODER_CCW_CW(KC_VOLD,     KC_VOLU      )},
    [_LOWER]   = { ENCODER_CCW_CW(_______,     _______), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [_RAISE]   = { ENCODER_CCW_CW(_______,     _______), ENCODER_CCW_CW(_______,     _______      )},
    [_ADJUST]  = { ENCODER_CCW_CW(_______,     _______), ENCODER_CCW_CW(_______,     _______      )},
};

#endif
