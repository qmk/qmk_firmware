/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define LT_DEL  LT(_RGB, KC_DEL)
#define LT_CAPS LT(_FNC, KC_CAPS)
#define LM_LALT LM(_FNC, MOD_LALT)
#define LM_NALT LM(_NUM, MOD_LALT)
#define RSFT_SL RSFT_T(KC_SLSH)
#define RALT_F6 RALT_T(KC_F6)
#define CTLINS  LCTL(KC_INS)     // Ctrl + Insert (terminal copy)
#define SFTINS  LSFT(KC_INS)     // Shift + Insert (terminal paste)
#define AMDREP  LCTL(LSFT(KC_S)) // AMD Replay
#define AMDREC  LCTL(LSFT(KC_E)) // AMD Record

enum piv3rt_layers {
    _DEF,
    _MAC,
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
        KC_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,
        LT_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,           KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   RSFT_SL,  KC_UP,   LT_DEL,
        KC_LCTL, KC_LGUI,  LM_LALT,                            KC_SPC,                    RALT_F6, MO(_FNC), KC_LEFT,  KC_DOWN, KC_RGHT
    ),
    [_MAC] = LAYOUT(
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        KC_LGUI, KC_LCTL,  KC_LGUI,                            _______,                   _______, _______,  _______,  _______, _______
    ),
    [_FNC] = LAYOUT(
        _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_DEL,
        _______, AGRAVE,   KC_UP,   EACUTE,  _______, KC_INS,  _______, _______, KC_UP,   KC_UP,   KC_PGUP,  KC_HOME,  KC_PSCR, KC_NUBS,
        _______, KC_HOME,  KC_DOWN, KC_END,  CTLINS,  SFTINS,  _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  KC_END,            KC_F8,
        _______,           _______, KC_CALC, CCED,    _______, _______, _______, _______, FRQLT,   FRQGT,    TG(_NUM), KC_VOLU, KC_MUTE,
        _______, TG(_MAC), LM_NALT,                            _______,                   KC_MPLY, _______,  KC_MPRV,  KC_VOLD, KC_MNXT
    ),
    [_RGB] = LAYOUT(
        _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_DEL,
        _______, RGB_TOG,  _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______,  _______,  _______, RESET,
        _______, _______,  _______, _______, _______, RGB_PCY, _______, _______, RGB_SPI, RGB_SPD, _______,  _______,           EEP_RST,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  RGB_000, _______,
        _______, _______,  _______,                            RGB_RST,                   _______, _______,  KC_PWR,   AMDREC,  AMDREP
    ),
    [_NUM] = LAYOUT(
        KC_NLCK, _______,  _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,    _______,  _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,    _______,  _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,    KC_PENT,           KC_PENT,
        _______,           _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT,  TG(_NUM), _______, _______,
        _______, _______,  _______,                            KC_PENT,                   _______, _______,  _______,  _______, _______
    ),
};

void reset_leds(void) {
    current_profile = OFF;
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgb_matrix_sethsv(0x6a, 0x33, 0xff);
}

void suspend_wakeup_init_user(void) {
    current_profile = OFF;
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

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    led_t led_state = host_keyboard_led_state();

    if (led_state.caps_lock) {
        // Tab key = 27
        RGB_MATRIX_INDICATOR_SET_COLOR(27, 0xff, 0x00, 0x00);
    }

    if (led_state.num_lock && (layer_state_is(_FNC) || layer_state_is(_NUM))) {
        // ESC key = 13
        RGB_MATRIX_INDICATOR_SET_COLOR(13, 0xff, 0x55, 0x55);
    }

    if (layer_state_is(_NUM)) {
        // Num pad
        for (int i=0; i<3; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(3 + i, 0xff, 0x55, 0x55);
            RGB_MATRIX_INDICATOR_SET_COLOR(17 + i, 0xff, 0x55, 0x55);
            RGB_MATRIX_INDICATOR_SET_COLOR(30 + i, 0xff, 0x55, 0x55);
        }
        RGB_MATRIX_INDICATOR_SET_COLOR(43, 0xff, 0x00, 0x00);
        return;
    }

    if (layer_state_is(_RGB)) {
        // AMD record and replay
        RGB_MATRIX_INDICATOR_SET_COLOR(54, 0x00, 0xff, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(55, 0xff, 0x00, 0x00);
    }

    if (current_profile == CSGO) {
        // Moves
        RGB_MATRIX_INDICATOR_SET_COLOR(25, 0xff, 0x00, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(39, 0xff, 0x00, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(38, 0xff, 0x00, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(37, 0xff, 0x00, 0x00);

        // Grenades
        RGB_MATRIX_INDICATOR_SET_COLOR(4, 0x00, 0xff, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(3, 0xff, 0x66, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(2, 0x66, 0x66, 0x22);
        RGB_MATRIX_INDICATOR_SET_COLOR(1, 0xff, 0xff, 0xff);

        // Primary
        RGB_MATRIX_INDICATOR_SET_COLOR(18, 0xff, 0x00, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(17, 0x99, 0x33, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(16, 0x00, 0xff, 0x00);

        // Secondary
        RGB_MATRIX_INDICATOR_SET_COLOR(32, 0x66, 0x66, 0x22);
        RGB_MATRIX_INDICATOR_SET_COLOR(31, 0x00, 0x00, 0xff);

        // Equipment
        RGB_MATRIX_INDICATOR_SET_COLOR(30, 0xff, 0x00, 0xff);
        RGB_MATRIX_INDICATOR_SET_COLOR(29, 0x00, 0x00, 0xff);
        RGB_MATRIX_INDICATOR_SET_COLOR(28, 0x33, 0x66, 0x99);
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0x33, 0x66, 0x99);
    } else if (current_profile == TEXT) {
        // Letters
        for (int i=0; i<7; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(17 + i, 0x33, 0x66, 0x99);
            RGB_MATRIX_INDICATOR_SET_COLOR(31 + i, 0x33, 0x66, 0x99);
            RGB_MATRIX_INDICATOR_SET_COLOR(46 + i, 0x33, 0x66, 0x99);
        }
        RGB_MATRIX_INDICATOR_SET_COLOR(38, 0x33, 0x66, 0x99);
        RGB_MATRIX_INDICATOR_SET_COLOR(39, 0x33, 0x66, 0x99);
        RGB_MATRIX_INDICATOR_SET_COLOR(24, 0x33, 0x66, 0x99);
        RGB_MATRIX_INDICATOR_SET_COLOR(25, 0x33, 0x66, 0x99);
        RGB_MATRIX_INDICATOR_SET_COLOR(26, 0x33, 0x66, 0x99);
    }
}
