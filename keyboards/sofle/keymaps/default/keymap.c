#include QMK_KEYBOARD_H

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _M_QWERTY,
    _W_QWERTY,
    _M_COLEMAK,
    _W_COLEMAK,
    _LOWER,
    _M_RAISE,
    _W_RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_M_QWERTY = SAFE_RANGE,
    KC_W_QWERTY,
    KC_M_COLEMAK,
    KC_W_COLEMAK,
    KC_M_LOWER,
    KC_W_LOWER,
    KC_M_RAISE,
    KC_W_RAISE,
    KC_ADJUST,
};

/* Linux/win variants */
#define KC_W_UNDO    LCTL(KC_Z)
#define KC_W_CUT     LCTL(KC_X)
#define KC_W_COPY    LCTL(KC_C)
#define KC_W_PASTE   LCTL(KC_V)
#define KC_W_PRVWD   LCTL(KC_LEFT)
#define KC_W_NXTWD   LCTL(KC_RIGHT)
#define KC_W_LSTRT   KC_HOME
#define KC_W_LEND    KC_END
#define KC_W_DLINE   LCTL(KC_BSPC)

/* Mac variants */
#define KC_M_UNDO  LGUI(KC_Z)
#define KC_M_CUT   LGUI(KC_X)
#define KC_M_COPY  LGUI(KC_C)
#define KC_M_PASTE LGUI(KC_V)
#define KC_M_PRVWD LALT(KC_LEFT)
#define KC_M_NXTWD LALT(KC_RIGHT)
#define KC_M_LSTRT LGUI(KC_LEFT)
#define KC_M_LEND  LGUI(KC_RIGHT)
#define KC_M_DLINE LGUI(KC_BSPC)

#define ______ KC_TRNS
#define XXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_M_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV, \
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC, \
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXX,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_LCTRL,KC_LALT,KC_LGUI,KC_M_LOWER, KC_ENT,      KC_SPC,  KC_M_RAISE, KC_RGUI, KC_RALT, KC_RCTRL \
),
[_W_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV, \
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC, \
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXX,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_LGUI,KC_LALT,KC_LCTRL,KC_M_LOWER, KC_ENT,      KC_SPC,  KC_M_RAISE, KC_RCTRL, KC_RALT, KC_RGUI \
),
/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_M_COLEMAK] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV, \
  KC_ESC,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_BSPC, \
  KC_TAB,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXX,KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_LCTRL,KC_LALT,KC_LGUI,KC_M_LOWER, KC_ENT,      KC_SPC,  KC_M_RAISE, KC_RGUI, KC_RALT, KC_RCTRL \
),
[_W_COLEMAK] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV, \
  KC_ESC,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_BSPC, \
  KC_TAB,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXX,KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_LGUI,KC_LALT,KC_LCTRL,KC_M_LOWER, KC_ENT,      KC_SPC,  KC_M_RAISE, KC_RCTRL, KC_RALT, KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT( \
  ______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,\
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12, \
  ______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
  ______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, ______,       ______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, ______, \
                       ______, ______, ______, ______, ______,       ______, ______, ______, ______, ______\
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_M_RAISE] = LAYOUT( \
  ______, ______ , ______ , ______ , ______ , ______,                             ______,  ______  , ______,  ______ ,  ______ ,______, \
  ______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXX, XXXXXX,                          KC_PGUP, KC_M_PRVWD,   KC_UP,KC_M_NXTWD,KC_M_DLINE,KC_BSPC, \
  ______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXX, KC_CAPS,                         KC_PGDN,    KC_LEFT, KC_DOWN,   KC_RGHT,   KC_DEL, KC_BSPC, \
  ______,KC_M_UNDO, KC_M_CUT,KC_M_COPY,KC_M_PASTE, XXXXXX,______,       ______,  XXXXXX, KC_M_LSTRT, XXXXXX, KC_M_LEND,  XXXXXX, ______, \
                         ______, ______, ______, ______,  ______,       ______, ______, ______, ______, ______ \
),
[_W_RAISE] = LAYOUT( \
  ______, ______ , ______ , ______ , ______ , ______,                             ______,  ______  , ______,  ______ ,  ______ ,______, \
  ______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXX, XXXXXX,                          KC_PGUP, KC_W_PRVWD,   KC_UP,KC_W_NXTWD,KC_W_DLINE, KC_BSPC, \
  ______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXX, KC_CAPS,                         KC_PGDN,    KC_LEFT, KC_DOWN,   KC_RGHT,    KC_DEL, KC_BSPC, \
  ______,KC_W_UNDO,KC_W_CUT,KC_W_COPY,KC_W_PASTE,XXXXXX,  ______,       ______,  XXXXXX, KC_W_LSTRT, XXXXXX, KC_W_LEND,   XXXXXX, ______, \
                         ______, ______, ______, ______,  ______,       ______, ______, ______, ______, ______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |MACQWR|MACCOL|      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |WINQWR|WINCOL|      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXX , XXXXXX,  XXXXXX  ,  XXXXXX , XXXXXX,    XXXXXX,              XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
  RESET  , XXXXXX,KC_M_QWERTY,KC_M_COLEMAK,XXXXXX, XXXXXX,              XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
  XXXXXX , XXXXXX,KC_W_QWERTY,KC_W_COLEMAK,XXXXXX, XXXXXX,              XXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXX, XXXXXX, \
  XXXXXX , XXXXXX,  XXXXXX  , XXXXXX  , XXXXXX, XXXXXX, XXXXXX,     XXXXXX, XXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXX, XXXXXX, \
                        ______, ______, ______, ______, ______,     ______, ______, ______, ______, ______ \
  )
};

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    switch (biton32(default_layer_state)) {
        case _W_QWERTY:
            oled_write_P(PSTR("Qwrt\nLinux"), false);
            break;
        case _M_QWERTY:
            oled_write_P(PSTR("Qwrt\nMac\n"), false);
            break;
        case _W_COLEMAK:
            oled_write_P(PSTR("Clmk\nLinux"), false);
            break;
        case _M_COLEMAK:
            oled_write_P(PSTR("Clmk\nMac\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (biton32(layer_state)) {
        case _M_COLEMAK:
        case _W_COLEMAK:
        case _M_QWERTY:
        case _W_QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _M_RAISE:
        case _W_RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_ln_P(led_usb_state & (1 << USB_LED_CAPS_LOCK) ? PSTR("CPSLK") : PSTR("     "), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_W_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_W_QWERTY);
            }
            return false;
            break;
        case KC_M_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_M_QWERTY);
            }
            return false;
            break;
        case KC_W_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_W_COLEMAK);
            }
            return false;
            break;
        case KC_M_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_M_COLEMAK);
            }
            return false;
            break;
        case KC_M_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _M_RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _M_RAISE, _ADJUST);
            }
            return false;
            break;
        case KC_M_RAISE:
            if (record->event.pressed) {
                layer_on(_M_RAISE);
                update_tri_layer(_LOWER, _M_RAISE, _ADJUST);
            } else {
                layer_off(_M_RAISE);
                update_tri_layer(_LOWER, _M_RAISE, _ADJUST);
            }
            return false;
            break;
        case KC_W_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _W_RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _W_RAISE, _ADJUST);
            }
            return false;
            break;
        case KC_W_RAISE:
            if (record->event.pressed) {
                layer_on(_W_RAISE);
                update_tri_layer(_LOWER, _W_RAISE, _ADJUST);
            } else {
                layer_off(_W_RAISE);
                update_tri_layer(_LOWER, _W_RAISE, _ADJUST);
            }
            return false;
            break;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
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
}

#endif

