// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers { _QWERTY, _LOWER, _RAISE };

/* Defines macros for use with the configurators "Any" key. (These are non-standard macros using the "Magnet" app on Mac). */
/* Move active application right half. */
#define KC_CSGRA LCTL(LSFT(LGUI(KC_RGHT)))
/* Move active application to left half. */
#define KC_CSGLA LCTL(LSFT(LGUI(KC_LEFT)))
/* Maximize active application. */
#define KC_MAXIM LCTL(LSFT(LGUI(KC_UP)))
/* Minimize active application. */
#define KC_MINIM LCTL(LSFT(LGUI(KC_DOWN)))

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    CMD_TAB_CW,
    CMD_TAB_CCW,
};

/* Rotary encoder variables used to hold down Command (GUI) key while cycling through open programs. */
bool     is_cmd_tab_active = false;
uint16_t cmd_tab_timer     = 0;

/**
 * Tap Dance declarations
 */
enum tapdances {
    _TD_FIVE_ENTER,
};

/* Tapdance */
#define TD5ENT TD(_TD_FIVE_ENTER)

/**
 * Tap Dance definitions
 *
 * To use this in the configurator, enter the name 'TD5ENT' in the "Any" key.
 */
tap_dance_action_t tap_dance_actions[] = {
    /* Tap once for 5, twice for Enter. */
    [_TD_FIVE_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_ENT),
};

/**
 * Keymap.
 * The rotary encoders are programmed manually below because the configurator does not support them yet.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
     /*
         QWERTY
        ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
        │ = │ 1 │ 2 │ 3 │ 4 │ 5 │               │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Tab│ Q │ W │ E │ R │ T │               │ Y │ U │ I │ O │ P │ \ │
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Esc│ A │ S │ D │ F │ G │               │ H │ J │ K │ L │ ; │ ' │
        ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
        │Sft│ Z │ X │ C │ V │ B │Min│       │Max│ N │ M │ , │ . │ / │Sft│
        └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │ ← │ → │Esc│Spc│Bsp│       │Tab│Ent│Del│ ↓ │ ↑ │
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */
    [_QWERTY] = LAYOUT_split4x6_r1(
        KC_EQL,       KC_1,         KC_2,         KC_3,    KC_4,          TD5ENT,                                      KC_6,   KC_7,         KC_8,     KC_9,         KC_0,            KC_MINS, 
        KC_TAB,       KC_Q,         KC_W,         KC_E,    KC_R,          KC_T,                                        KC_Y,   KC_U,         KC_I,     KC_O,         KC_P,            KC_BSLS, 
        LT(1,KC_DEL), LT(2,KC_A),   LCTL_T(KC_S), KC_D,    LGUI_T(KC_F),  KC_G,                                        KC_H,   RGUI_T(KC_J), KC_K,     RCTL_T(KC_L), LT(2,KC_SCLN),   LT(1,KC_QUOT), 
        KC_LSFT,      LALT_T(KC_Z), KC_X,         KC_C,    KC_V,          KC_B,            KC_MINIM,  KC_MAXIM,         KC_N,   KC_M,         KC_COMM,  KC_DOT,       RALT_T(KC_SLSH), KC_RSFT, 
                                                  KC_LEFT, KC_RGHT,       QK_GESC, KC_SPC, KC_BSPC,   KC_TAB,   KC_ENT, KC_DEL, KC_UP,        KC_DOWN
    ),

    /*
        Symbols/Numpad Layer
        ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
        │F1 │F1 │F2 │F3 │F4 │F5 │               │F6 │F7 │F8 │F9 │F10│F11│
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │___│ ! │ @ │ { │ } │ | │               │QMK│ 7 │ 8 │ 9 │ * │F12│
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │___│ # │ $ │ ( │ ) │ ` │               │QMK│ 4 │ 5 │ 6 │ + │___│
        ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
        │___│ # │ $ │ [ │ ] │ ~ │___│       │___│QMK│ 1 │ 2 │ 3 │ / │___│
        └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │___│___│___│___│___│       │ 0 │ 0 │ 0 │ 0 │ 0 │
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */

    [_LOWER] = LAYOUT_split4x6_r1(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                      KC_F6,   KC_F7, KC_F8, KC_F9, KC_F10,  KC_F11, 
        KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                    DT_PRNT, KC_7,  KC_8,  KC_9,  KC_ASTR, KC_F12, 
        KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                     DT_UP,   KC_4,  KC_5,  KC_6,  KC_PPLS, KC_TRNS, 
        KC_TRNS, KC_HASH, KC_DLR,  KC_LBRC, KC_RBRC, KC_TILD,          KC_TRNS,  KC_TRNS,        DT_DOWN, KC_1,  KC_2,  KC_3,  KC_PSLS, KC_TRNS, 
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_P0,   KC_P0, KC_P0,   KC_P0, KC_P0
    ),

    /*
        Navigation/Function Layer
        ┌────┬────┬────┬────┬────┬────┐               ┌────┬────┬────┬────┬────┬────┐
        │RGB │ACL0│ACL1│ACL2│____│____│               │____│____│MOD │RMOD│HUI │HUD │
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │____│____│____│MS_U│____│____│               │____│BTN1│ ↑  │BTN2│SAI │SAD │
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │____│____│MS_L│MS_D│MS_R│____│               │____│ ←  │ ↓  │ →  │VAI │VAD │
        ├────┼────┼────┼────┼────┼────┼────┐     ┌────┼────┼────┼────┼────┼────┼────┤
        │____│____│____│____│____│____│____│     │____│____│____│____│____│SPI │SPD │
        └────┴────┴────┴────┴────┴────┴────┘     └────┴────┴────┴────┴────┴────┴────┘
                      ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                      │___│___│___│___│QMK│       │QMK│___│___│___│___│
                      └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */    
    [_RAISE] = LAYOUT_split4x6_r1(
        RGB_TOG, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS,                                        KC_TRNS, KC_TRNS, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS,                                        KC_TRNS, KC_BTN1, KC_UP,   KC_BTN2,  RGB_SAI, RGB_SAD, 
        KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,                                        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT,  RGB_VAI, RGB_VAD, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,   KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  RGB_SPI, RGB_SPD, 
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CSGLA,  KC_CSGRA, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
        case CMD_TAB_CW:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case CMD_TAB_CCW:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

/**
 * Helper function for rotary encoder.
 *
 * If the timer has elapsed, the Command/Gui tab will be released.
 * You can adjust the milliseconds to speed up the CMD key release.
 */
void matrix_scan_user(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 900) {
            unregister_code(KC_LGUI);
            is_cmd_tab_active = false;
        }
    }
}

/**
 * Rotary Encoder.
 *
 * This can't be programmed through configurator. You must do it here.
 *
 * This uses the amazing "Encoder map" feature which replicates the normal keyswitch layer handling functionality, but with encoders.
 * https://docs.qmk.fm/#/feature_encoders?id=encoder-map
 *
 * Uses a variant of the Super-alt-tab macro to switch between open applications on a mac. (Command-tab)
 * https://docs.qmk.fm/#/feature_macros?id=super-alt%e2%86%aftab
 */
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    /* Left Hand */                             /* Right Hand */
    /* Switch between tabs. (Control + Tab). */ /* Switch between open apps on Mac. (Command + Tab + timer logic) */
    [_QWERTY] = {ENCODER_CCW_CW(C(KC_TAB), S(C(KC_TAB))), ENCODER_CCW_CW(CMD_TAB_CCW, CMD_TAB_CW)},
    /* Scrolls left & right. (Shift + Mouse Wheel Up). */ /* Scrolls up and down. (Page Down & Page Up - mouse wheel scroll incraments are too small) */
    [_LOWER] = {ENCODER_CCW_CW(S(KC_MS_WH_UP), S(KC_MS_WH_DOWN)), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    /* Selects adjacent words. (Command + Shift + Right Arrow). */ /* Jumps to end/start of line. Hold shift to select. (Gui + arrow). */
    [_RAISE] = {ENCODER_CCW_CW(C(S(KC_LEFT)), C(S(KC_RGHT))), ENCODER_CCW_CW(G(KC_LEFT), G(KC_RGHT))}
};
#endif
