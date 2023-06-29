// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY = 0,
    _GAME,
    _NAV,
    _NUMBER,
    _SYMBOL,
    _FUNC
};

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

// bottom mods
#define SYM_SPC LT(_SYMBOL, KC_SPC)
#define NUM_TAB LT(_NUMBER, KC_TAB)
#define FUNC_ESC LT(_FUNC, KC_ESC)
#define FUNC_ENT LT(_FUNC, KC_ENT)
#define NAV_BSPC LT(_NAV, KC_BSPC)
#define RALT_DEL RALT_T(KC_DEL)

// game layer mods
#define LALT_EQL LALT_T(KC_EQL)
#define LSFT_MINS LSFT_T(KC_MINS)
#define LCTL_ESC LCTL_T(KC_ESC)
#define LGUI_QUOT LGUI_T(KC_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
    *        .----------------------------------.                    ,----------------------------------.
    *        |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |
    * .------+------+------+------+------+------|                    |------+------+------+------+------+------.
    * |  =   |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  -   |   Z  |   X  |   C  |   V  |   B  |-------.    .-------|   N  |   M  |   ,  |   .  |   /  |  `   |
    * `-----------------------------------------/       /    \       \-----------------------------------------'
    *                         | Esc  | Tab  |  / Space /      \ Enter \  | Bsps | Del  |
    *                         |_FUNC | _NUM | /_SYMBOL/        \ _FUNC \ | _NAV | RAlt |
    *                         `-------------''-------'          '-------''-------------'
    */
    [_QWERTY] = LAYOUT(
                 KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_EQL,  HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,                KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, KC_QUOT,
        KC_MINS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_GRV,
                                      FUNC_ESC, NUM_TAB, SYM_SPC,     FUNC_ENT, NAV_BSPC, RALT_DEL
    ),

    [_GAME] = LAYOUT(
                   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        LALT_EQL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LGUI_QUOT,
        LSFT_MINS, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TG(_GAME),
                                       LCTL_ESC, NUM_TAB, SYM_SPC,    FUNC_ENT, NAV_BSPC, RALT_DEL
    ),

    [_NAV] = LAYOUT(
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX,       XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX,
        XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,             LALT(KC_UP),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             LALT(KC_DOWN), KC_HOME, KC_END,  KC_APP,  XXXXXXX, XXXXXXX,
                                       XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, _______, XXXXXXX
    ),

    [_NUMBER] = LAYOUT(
                 KC_BSLS, KC_7,    KC_8,    KC_9,    KC_0,                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, KC_COMM, KC_4,    KC_5,    KC_6,    KC_LBRC,             XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, XXXXXXX,
        KC_ENT,  KC_DOT,  KC_1,    KC_2,    KC_3,    KC_RBRC,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                     KC_BSPC, _______, TG(_GAME),       XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_SYMBOL] = LAYOUT(
                 LSFT(KC_BSLS), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0),               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, LSFT(KC_COMM), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_LBRC),            XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, XXXXXXX,
        KC_ENT,  LSFT(KC_DOT),  LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_RBRC),            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                           XXXXXXX, KC_BSPC, _______,     XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_FUNC] = LAYOUT(
                 KC_F12, KC_F7,   KC_F8,   KC_F9,   KC_PSCR,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, KC_F11, KC_F4,   KC_F5,   KC_F6,   KC_PAUS,            XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, XXXXXXX,
        KC_DEL,  KC_F10, KC_F1,   KC_F2,   KC_F3,   KC_CAPS,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                     _______, KC_MNXT, KC_MPLY,     _______, XXXXXXX, XXXXXXX
    )
};

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // allow multiple space, backspace, delete
        case SYM_SPC:
        case NAV_BSPC:
        case RALT_DEL:
            return false;
        default:
            return true;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    // different tapping term for different fingers
    switch (keycode) {
        // pinkies
        case HOME_A:
        case HOME_SCLN:
            return TAPPING_TERM + 70;
        // ring
        case HOME_S:
        case HOME_L:
            return TAPPING_TERM + 40;
        // middle
        case HOME_D:
        case HOME_K:
            return TAPPING_TERM + 20;
        // index and thumb
        default:
            return TAPPING_TERM;
    }
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_GAME] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_NAV] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [_NUMBER] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [_SYMBOL] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [_FUNC] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  }
};
#endif // ENCODER_MAP_ENABLE

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

const rgblight_segment_t PROGMEM game_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM capslockword_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_MAGENTA});
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(game_layer, capslock_layer, capslockword_layer);

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _GAME));
    return state;
}

void caps_word_set_user(bool active) {
    rgblight_set_layer_state(2, active);
}

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

#ifdef OLED_ENABLE

void render_layer(void) {
    switch (get_highest_layer(layer_state)) {
        case _NUMBER:
            oled_write_ln_P(PSTR("NMBR"), false);
            break;
        case _SYMBOL:
            oled_write_ln_P(PSTR("SMBL"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("NAV"), false);
            break;
        case _FUNC:
            oled_write_ln_P(PSTR("FUNC"), false);
            break;
        default:
            oled_write_ln_P(PSTR(" "), false);
            break;
    }
}

bool oled_task_user(void) {
    render_layer();
    return true;
}

#endif // OLED_ENABLE

