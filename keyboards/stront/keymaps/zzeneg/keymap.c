// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "display.h"
#include "raw_hid.h"
#include "layers.h"

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_P RGUI_T(KC_P)

// bottom mods
#define SYM_SPC LT(_SYMBOL, KC_SPC)
#define NUM_TAB LT(_NUMBER, KC_TAB)
#define FUNC_ESC LT(_FUNC, KC_ESC)
#define FUNC_ENT LT(_FUNC, KC_ENT)
#define NAV_BSPC LT(_NAV, KC_BSPC)
#define EU_DEL LT(_EU, KC_DEL)

// game layer mods
#define LALT_Q LALT_T(KC_Q)
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
    // clang-format off
    [_QWERTY] = LAYOUT(
                            KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,    KC_U,    KC_I,     KC_O,
        KC_Q,     HOME_A,   HOME_S,  HOME_D,  HOME_F,  KC_G,                KC_H,    HOME_J,  HOME_K,   HOME_L,  HOME_P,   KC_SCLN,
        KC_MINS,  KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,                KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  KC_QUOT,
                                   FUNC_ESC,  NUM_TAB,  SYM_SPC,     FUNC_ENT,  NAV_BSPC,  EU_DEL
    ),

    [_GAME] = LAYOUT(
                            KC_W,    KC_E,    KC_R,    KC_T,               KC_Y,    KC_U,    KC_I,     KC_O,
        LALT_Q,     KC_A,   KC_S,    KC_D,    KC_F,    KC_G,               KC_H,    KC_J,    KC_K,     KC_L,    KC_P,     KC_SCLN,
        LSFT_MINS,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,               KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  LGUI_QUOT,
                                    LCTL_ESC,  NUM_TAB,  SYM_SPC,    FUNC_ENT,  NAV_BSPC,  EU_DEL
    ),

    [_EU] = LAYOUT(
                               XXXXXXX,     RALT(KC_E),  XXXXXXX,  XXXXXXX,               XXXXXXX,     RALT(KC_U),  XXXXXXX,  RALT(KC_O),
        XXXXXXX,  RALT(KC_A),  RALT(KC_S),  XXXXXXX,     KC_LSFT,  XXXXXXX,               XXXXXXX,     KC_RSFT,     XXXXXXX,  RALT(KC_L),  XXXXXXX,  XXXXXXX,
        XXXXXXX,  RALT(KC_Z),  RALT(KC_X),  RALT(KC_C),  XXXXXXX,  XXXXXXX,               RALT(KC_N),  XXXXXXX,     XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,
                                                     KC_ESC,   KC_TAB,   KC_SPC,      XXXXXXX,  KC_BSPC,   _______
    ),

    [_NAV] = LAYOUT(
                            DT_UP,    DT_DOWN,  DT_PRNT,  XXXXXXX,             KC_BSPC,        KC_CAPS,  KC_PGDN,  KC_PGUP,
        XXXXXXX,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,             LALT(KC_UP),    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_PAUS,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             LALT(KC_DOWN),  KC_HOME,  KC_END,   KC_INS,   KC_APP,   XXXXXXX,
                                            KC_ESC,   KC_TAB,   KC_SPC,     XXXXXXX,  _______,  KC_DEL
    ),

    [_NUMBER] = LAYOUT(
                           KC_7,    KC_8,    KC_9,    KC_PLUS,             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_EQL,  KC_0,     KC_4,    KC_5,    KC_6,    KC_DOT,              XXXXXXX,  KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  XXXXXXX,
        KC_ENT,  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_COMM,             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                     KC_BSPC,  _______,  TG(_GAME),       XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    [_SYMBOL] = LAYOUT(
                            KC_PERC,  KC_ASTR,  KC_LCBR,  KC_RCBR,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_PIPE,  KC_DLR,   KC_EXLM,  KC_AMPR,  KC_LPRN,  KC_RPRN,            XXXXXXX,  KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  XXXXXXX,
        KC_BSLS,  KC_CIRC,  KC_HASH,  KC_AT,    KC_LBRC,  KC_RBRC,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                          MO(_SYS),  KC_BSPC, _______,     XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_FUNC] = LAYOUT(
                            KC_F7,   KC_F8,   KC_F9,   XXXXXXX,            XXXXXXX,  KC_PSCR,  KC_SCRL,  KC_NUM,
        KC_LCTL,  KC_F11,   KC_F4,   KC_F5,   KC_F6,   KC_F12,             XXXXXXX,  KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  XXXXXXX,
        XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                         _______, KC_MNXT, KC_MPLY,     _______, XXXXXXX,  MO(_SYS)
    ),

    [_SYS] = LAYOUT(
                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______, QK_BOOT, _______,     _______, QK_BOOT, _______
    )
    // clang-format on
};

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // allow multiple backspace
        case NAV_BSPC:
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
        case HOME_P:
            return 250;
        // ring
        case HOME_S:
        case HOME_L:
            return 200;
        // middle
        case HOME_D:
        case HOME_K:
            return 160;
        // index
        case HOME_F:
        case HOME_J:
            return 140;
        // thumb and game
        default:
            return TAPPING_TERM;
    }
}

uint16_t HOME_CTRL_pressed_time = 0;

bool custom_home_row_ctrl(keyrecord_t *record, uint16_t time) {
    if (record->tap.count && record->event.pressed && get_mods() & MOD_MASK_CTRL) {
        if (TIMER_DIFF_16(record->event.time, HOME_CTRL_pressed_time) < time) {
            del_mods(MOD_MASK_CTRL);
            tap_code(KC_D);
        }
    }

    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_MINS:
        case KC_RSFT:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    // clang-format off
    [_QWERTY] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_GAME] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_EU] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_NAV] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [_NUMBER] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [_SYMBOL] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [_FUNC] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [_SYS] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  }
    // clang-format on
};
#endif // ENCODER_MAP_ENABLE

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

const rgblight_segment_t PROGMEM        game_layer[]         = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM        capslock_layer[]     = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM        capslockword_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_MAGENTA});
const rgblight_segment_t *const PROGMEM rgb_layers[]         = RGBLIGHT_LAYERS_LIST(game_layer, capslock_layer, capslockword_layer);

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}

void caps_word_set_user(bool active) {
    rgblight_set_layer_state(2, active);
}

#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

static bool display_enabled;

void keyboard_post_init_user(void) {
    debug_enable = true;

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    rgblight_layers = rgb_layers;
#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

    if (is_keyboard_master()) {
        display_enabled = display_init();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprintf("keycode %u %s %s %d\n", keycode, record->event.pressed ? "pressed" : "depressed", record->tap.interrupted ? "interrupted" : "not interrupted", record->tap.count);

    if (display_enabled) {
        display_process_record(keycode, record);
    }

    switch (keycode) {
        case HOME_D:
            // save time when CTRL from D key is pressed
            if (!record->tap.count && record->event.pressed) {
                HOME_CTRL_pressed_time = record->event.time;
            }
            return true;
        case HOME_S:
            // if S is pressed and CTRL is active, and < 170 passed since CTRL was pressed, cancel CTRL and send D instead
            return custom_home_row_ctrl(record, 170);
        case HOME_A:
            // if A is pressed and CTRL is active, and < 200 passed since CTRL was pressed, cancel CTRL and send D instead
            return custom_home_row_ctrl(record, 200);
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    rgblight_set_layer_state(0, layer_state_cmp(state, _GAME));
#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

    if (display_enabled) {
        display_process_layer_state(get_highest_layer(state));
    }

    return state;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    dprintf("received %u bytes from HID \n", length);

    if (display_enabled) {
        display_process_raw_hid_data(data, length);
    }
}

void housekeeping_task_user(void) {
    if (display_enabled) {
        display_refresh_data();
    }
}
