#include QMK_KEYBOARD_H

#define CS_F10 LCTL(LSFT(KC_F10))
#define CS_F5  LCTL(LSFT(KC_F5))
#define C_PGUP  LCTL(KC_PGUP)
#define C_PGDN  LCTL(KC_PGDN)

enum custom_keycodes {
    SLKPONE = SAFE_RANGE,
    STR_TLD,                // ~
    STR_GRV,                // `
    STR_UKR_I,              // 
    STR_URK_II,             //
    GT_LSTR,                // Call Lester in GTA :)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default layouts
    LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          XXXXXXX,
        KC_LCTL, KC_LGUI, KC_LALT,        LCTL_T(KC_SPC),  LCTL_T(KC_SPC),  LCTL_T(KC_SPC),       MO(2),   MO(3),   KC_LEFT, KC_DOWN, KC_RGHT 
    ),

    // LAYOUT 1
    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______, _______, KC_HOME, KC_END,  _______, _______, _______, _______, _______, _______, KC_MPLY, RGB_TOG, _______,          RESET,
        _______, _______, _______, KC_DEL,  _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_PGUP,                   _______,
        _______, _______, _______, STR_TLD, STR_GRV, _______, _______, KC_MNXT, _______, KC_VOLD, KC_VOLU, KC_PGDN, KC_UP,            _______,
        _______, _______, _______,                   _______, _______, _______,                   _______, _______, KC_HOME, _______, KC_END
    ),

    // LAYOUT 2
    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   CS_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   CS_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, _______,          RESET,
        _______, _______, _______, _______, DF(6),   DF(4),   _______, _______, _______, _______, _______, C_PGUP,                    _______,
        _______, _______, _______, STR_TLD, STR_GRV, _______, _______, _______, _______, KC_VOLD, KC_VOLU, C_PGDN,  KC_UP,            _______,
        _______, _______, _______,                   KC_RCTL, KC_RCTL, KC_RCTL,                   _______, _______, KC_HOME, _______, KC_END
    ),

    // LAYOUT 3 - shortcuts
    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   CS_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   CS_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SLKPONE, _______, _______,          RESET,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_PGUP,                    _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_PGDN,  KC_UP,            _______,
        _______, _______, _______,                   KC_RCTL, KC_RCTL, KC_RCTL,                   _______, _______, KC_HOME, _______, KC_END
    ),

    // LAYOUT 4 - Windows and Gaming layout
    LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,
        MO(5),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          XXXXXXX,
        KC_LCTL, KC_LGUI, KC_LALT,              KC_SPC,  KC_SPC,  KC_SPC,                         MO(5),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT 
    ),

    // LAYOUT 5 - Windows Func layout
    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, RGB_TOG, KC_PSCR,          RESET,
        _______, _______, _______, KC_DEL,  _______, DF(0),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_PGUP,                   _______,
        _______, _______, _______, _______, _______, _______, _______, KC_MNXT, _______, KC_VOLD, KC_VOLU, KC_PGDN, KC_RSFT,          _______,
        _______, _______, _______,                   _______, _______, _______,                   _______, _______, KC_HOME, KC_UP,   KC_END
    ),

    // LAYOUT 6 - GTA layout
    LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,
        KC_RSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,            XXXXXXX,
        KC_LCTL, KC_LCTL, KC_LSFT,              KC_SPC,  KC_SPC,  KC_SPC,                         MO(7),   KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT 
    ),
    // LAYOU 7 - GTA func layout
    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, DF(0),   _______, _______, _______, GT_LSTR, _______, KC_PGUP,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_PGDN, KC_CAPS,          _______,
        _______, _______, _______,                   KC_LOCK, KC_LOCK, KC_LOCK,                   _______, KC_LGUI, KC_HOME, KC_UP,   KC_END
    ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_SPC):
            return TAPPING_TERM + 2000;
        case RSFT_T(KC_UP):
            return 100;
        default:
            return TAPPING_TERM;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

layer_state_t layer_state_set_user(layer_state_t  state) {
    switch (biton32(state)) {
        case 4:
            rgblight_setrgb (0x00,  0xFF, 0x00);
            break;
        case 5:
            rgblight_setrgb (0x00,  0xFF, 0x00);
            break;
        case 7:
            rgblight_setrgb (0x55,  0x55, 0x00);
            break;
        default: //  for any other layers, or the default layer
            rgblight_setrgb (0x00,  0x00, 0xFF);
            break;
    }
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case 0:
            rgblight_setrgb (0x00,  0x00, 0xFF);
            break;
        case 4:
            rgblight_setrgb (0x00,  0xFF, 0x00);
            break;
    }
    return state;
}

void keyboard_post_init_user(void) {
    layer_state_set_user(layer_state);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SLKPONE:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LSFT)"\\"SS_UP(X_LSFT)SS_UP(X_LCTL)":+1:"SS_DELAY(250)SS_TAP(X_ENT));
        }         
        break;
    case STR_GRV:
        if (record->event.pressed) {
            SEND_STRING("`");
        }
        break;
    case STR_TLD:
        if (record->event.pressed) {
            SEND_STRING("~");
        }
        break;
    case GT_LSTR:
        if (record->event.pressed) {
            SEND_STRING(
                SS_DOWN(X_UP)SS_DELAY(1000)
                SS_DOWN(X_RGHT)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_ENT)SS_DELAY(500)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
                SS_DOWN(X_UP)SS_DELAY(100)
            );
        }
        break;
    }

    return true;
};
