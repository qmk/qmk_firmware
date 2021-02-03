#include QMK_KEYBOARD_H

#define LT_DEL  LT(_RGB, KC_DEL)
#define LT_CAPS LT(_FNC, KC_CAPS)
#define LM_LALT LM(_FNC, MOD_LALT)
#define LM_NALT LM(_NUM, MOD_LALT)
#define RSFT_SL RSFT_T(KC_SLSH)
#define RALT_F6 RALT_T(KC_F6)

enum piv3rt_layers {
    _DEF,
    _FNC,
    _RGB,
    _NUM,
};

enum piv3rt_keycodes {
    RGB_RST = SAFE_RANGE,
    RGB_PCY, // Cycle through RGB profiles
    RGB_000, // Turn everything off except profiles
    EACUTE,  // French É for Windows
    CCED,    // French Ç for Windows
    AGRAVE,  // French À for Windows
    FRQLT,   // French ≪ for Windows
    FRQGT,   // French ≫ for Windows
};

enum piv3rt_rgbprofiles {
    CSGO,
    TEXT,
    OFF, // Should be the last item
};

enum piv3rt_rgbprofiles current_profile = OFF;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(
        KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,
        LT_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   RSFT_SL, KC_UP,   LT_DEL,
        KC_LCTL,  KC_LGUI, LM_LALT,                            KC_SPC,                    RALT_F6, MO(_FNC), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FNC] = LAYOUT(
        TO(_NUM), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,
        _______,  AGRAVE,  KC_UP,   EACUTE,  _______, _______, _______, _______, KC_UP,   KC_UP,   KC_PGUP,  KC_HOME, KC_PSCR, KC_NUBS,
        _______,  KC_HOME, KC_DOWN, KC_END,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  KC_END,           KC_F8,
        _______,           _______, KC_CALC, CCED,    _______, _______, _______, _______, FRQLT,   FRQGT,    _______, KC_VOLU, KC_MUTE,
        _______,  _______, LM_NALT,                            _______,                   KC_MPLY, _______,  KC_MPRV, KC_VOLD, KC_MNXT
    ),
    [_RGB] = LAYOUT(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,
        _______,  RGB_TOG, _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______,  _______, _______, RESET,
        _______,  _______, _______, _______, _______, RGB_PCY, _______, _______, RGB_SPI, RGB_SPD, _______,  _______,          EEP_RST,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, RGB_000, _______,
        _______,  _______, _______,                            RGB_RST,                   _______, _______,  _______, _______, _______
    ),
    [_NUM] = LAYOUT(
        KC_NLCK,  KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, _______, _______, _______, _______, KC_PSLS, KC_PAST,  KC_PMNS, KC_PPLS, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,    _______, _______, TO(_DEF),
        _______,  _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,    _______,          KC_PENT,
        _______,           _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,    KC_P3,   _______, _______,
        _______,  _______, _______,                            KC_PENT,                   KC_P0,   KC_PDOT,  _______, _______, _______
    ),
};

void reset_leds(void) {
    current_profile = OFF;
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgb_matrix_sethsv(0x9f, 0xff, 0xff);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_RST:
        if (record->event.pressed) {
            reset_leds();
        }
        return false;
        break;
    case RGB_PCY:
        if (record->event.pressed) {
            // Cycle through RGB profiles
            current_profile = current_profile == OFF ? 0 : current_profile + 1;
        }
        return false;
        break;
    case RGB_000:
        if (record->event.pressed) {
            rgb_matrix_sethsv(0, 0, 0);
        }
        return false;
        break;
    case EACUTE:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P0) SS_TAP(X_P2) SS_TAP(X_P0) SS_TAP(X_P1) SS_UP(X_LALT));
        }
        return false;
        break;
    case CCED:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P9) SS_TAP(X_P9) SS_UP(X_LALT));
        }
        return false;
        break;
    case AGRAVE:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P9) SS_TAP(X_P2) SS_UP(X_LALT));
        }
        return false;
        break;
    case FRQLT:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P1) SS_TAP(X_P7) SS_TAP(X_P4) SS_UP(X_LALT));
        }
        return false;
        break;
    case FRQGT:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P1) SS_TAP(X_P7) SS_TAP(X_P5) SS_UP(X_LALT));
        }
        return false;
        break;
    }
    return true;
};

void rgb_matrix_indicators_user(void) {
    led_t led_state = host_keyboard_led_state();

    if (!g_suspend_state && rgb_matrix_config.enable) {
        if (led_state.caps_lock) {
            // Tab key = 27
            rgb_matrix_set_color(27, 0xff, 0x00, 0x00);
        }

        if (led_state.num_lock && (layer_state_is(_FNC) || layer_state_is(_NUM))) {
            // ESC key = 13
            rgb_matrix_set_color(13, 0xff, 0xff, 0xff);
        }

        if (layer_state_is(_NUM)) {
            // Exit with \ |
            rgb_matrix_set_color(14, 0xff, 0x00, 0x00);
            // Num pad
            for (int i=0; i<3; i++) {
                rgb_matrix_set_color(17 + i, 0xff, 0xff, 0xff);
                rgb_matrix_set_color(30 + i, 0xff, 0xff, 0xff);
                rgb_matrix_set_color(43 + i, 0xff, 0xff, 0xff);
            }
            rgb_matrix_set_color(58, 0xff, 0xff, 0xff);
            rgb_matrix_set_color(57, 0xff, 0xff, 0xff);
            return;
        }

        if (current_profile == CSGO) {
            // Moves
            rgb_matrix_set_color(25, 0xff, 0x00, 0x00);
            rgb_matrix_set_color(39, 0xff, 0x00, 0x00);
            rgb_matrix_set_color(38, 0xff, 0x00, 0x00);
            rgb_matrix_set_color(37, 0xff, 0x00, 0x00);

            // Grenades
            rgb_matrix_set_color(4, 0x00, 0xff, 0x00);
            rgb_matrix_set_color(3, 0xff, 0x66, 0x00);
            rgb_matrix_set_color(2, 0x66, 0x66, 0x22);
            rgb_matrix_set_color(1, 0xff, 0xff, 0xff);

            // Primary
            rgb_matrix_set_color(18, 0xff, 0x00, 0x00);
            rgb_matrix_set_color(17, 0x99, 0x33, 0x00);
            rgb_matrix_set_color(16, 0x00, 0xff, 0x00);

            // Secondary
            rgb_matrix_set_color(32, 0x66, 0x66, 0x22);
            rgb_matrix_set_color(31, 0x00, 0x00, 0xff);

            // Equipment
            rgb_matrix_set_color(30, 0xff, 0x00, 0xff);
            rgb_matrix_set_color(29, 0x00, 0x00, 0xff);
            rgb_matrix_set_color(28, 0x33, 0x66, 0x99);
            rgb_matrix_set_color(0, 0x33, 0x66, 0x99);
        } else if (current_profile == TEXT) {
            // Letters
            for (int i=0; i<7; i++) {
                rgb_matrix_set_color(17 + i, 0x33, 0x66, 0x99);
                rgb_matrix_set_color(31 + i, 0x33, 0x66, 0x99);
                rgb_matrix_set_color(46 + i, 0x33, 0x66, 0x99);
            }
            rgb_matrix_set_color(38, 0x33, 0x66, 0x99);
            rgb_matrix_set_color(39, 0x33, 0x66, 0x99);
            rgb_matrix_set_color(24, 0x33, 0x66, 0x99);
            rgb_matrix_set_color(25, 0x33, 0x66, 0x99);
            rgb_matrix_set_color(26, 0x33, 0x66, 0x99);
        }
    }
}
