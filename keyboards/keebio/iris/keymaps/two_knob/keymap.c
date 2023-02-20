// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

/* Defines macros for use with the configurators "Any" key. (These are non-standard macros). */
/* Move active application right half. */
#define KC_CSGRA LCTL(LSFT(LGUI(KC_RGHT)))
/* Move active application to left half. */
#define KC_CSGLA LCTL(LSFT(LGUI(KC_LEFT)))
/* Maximize active application. */
#define KC_MAXIM LCTL(LSFT(LGUI(KC_UP)))
/* Minimize active application. */
#define KC_MINIM LCTL(LSFT(LGUI(KC_DOWN)))

/* Rotary encoder variables used to hold down Command (GUI) key while cycling through open programs. */
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    CMD_TAB_CW,
    CMD_TAB_CCW,
};

/**
 * Tap Dance declarations
 */
enum tapdances {
    _TD_FIVE_ENTER,
};

/* Tapdance */
#define TD_FIVE_ENTER TD(_TD_FIVE_ENTER)

/**
 * Tap Dance definitions
 *
 * NOTE - if your not using tapdance, comment out:
 * TAP_DANCE_ENABLE = yes in rules.mk
 * define TAPPING_TERM 175 in config.h
 * else you'll get a compile error.
 *
 * To use this in the configurator, enter the name 'TD_FIVE_ENTER' in the "Any" key.
 */
qk_tap_dance_action_t tap_dance_actions[] = {
    /* Tap once for 5, twice for Enter. */
    [_TD_FIVE_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_ENT),
};

/**
 * Keymap. Generated via configurator.
 *
 * You can download/upload the two_know.json to the configurator:
 * https://config.qmk.fm/#/keebio/iris/rev6a/LAYOUT
 *
 * If you make changes and download the json, you can run qmk json2c two_knob.json to get converted text.
 * You can copy and paste it here.
 * You will have to reneame the array keys from ints to the custom keycode names.
 *
 * The rotary encoders are programmed manually below because the configurator does not support them yet.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(KC_EQL, KC_1, KC_2, KC_3, KC_4, TD_FIVE_ENTER, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, LT(1, KC_DEL), LT(2, KC_A), LCTL_T(KC_S), KC_D, LGUI_T(KC_F), KC_G, KC_H, RGUI_T(KC_J), KC_K, RCTL_T(KC_L), LT(2, KC_SCLN), LT(1, KC_QUOT), SC_LSPO, LALT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_MINIM, KC_MAXIM, KC_N, KC_M, KC_COMM, KC_DOT, RALT_T(KC_SLSH), SC_RSPC, QK_GESC, KC_SPC, KC_BSPC, KC_TAB, KC_ENT, KC_DEL),
    [_LOWER]  = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, DT_PRNT, KC_7, KC_8, KC_9, KC_ASTR, KC_F12, KC_TRNS, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_GRV, DT_UP, KC_4, KC_5, KC_6, KC_PPLS, KC_TRNS, KC_TRNS, KC_HASH, KC_DLR, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS, KC_TRNS, DT_DOWN, KC_1, KC_2, KC_3, KC_PSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0),
    [_RAISE]  = LAYOUT(RGB_TOG, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_UP, KC_BTN2, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPI, RGB_SPD, KC_TRNS, KC_TRNS, KC_CSGLA, KC_CSGRA, KC_TRNS, KC_TRNS),
    [_ADJUST] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
        _______, _______, _______, _______, _______, _______
        // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
 * Define lighting layers.
 *
 * Iris rev6a uses WS2812 RGB Matrix lighting.
 * The RGB Matrix lighting option has already been enabled in ../../rev6a/config.h
 * You'll need to add #define SPLIT_LAYER_STATE_ENABLE to config.h if you
 * will be customizing the LED's per key.
 *
 * Here's how to customize the colors per layer and per key:
 * https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgb_matrix.md#direct-operation-iddirect-operation
 *
 * If you start getting real weird with it, your likely to exceed the firmware limit of 28672.
 * You may need to selectively disable some effects:
 * https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgb_matrix.md#rgb-matrix-effects-idrgb-matrix-effects
 *
 * There are 68 Leds. Printed on the board itself, the led numbers are 1-68.
 * For color addressing, use 0-67 as the index number.
 * rgb_matrix_set_color(index, r, g, b)
 *
 * Here's an LED number guide:
 * FRONT
 * Left Hand                    Right Hand
 * |00|01|02|03|04|05|          |39|38|37|36|35|34|
 * |11|10|09|08|07|06|          |40|41|42|43|44|45|
 * |12|13|14|15|16|17|          |51|50|49|48|47|46|
 * |23|22|21|20|19|18|27|    |61|52|53|54|55|56|57|
 *             |24|25|26|    |60|59|58|
 * REVERSE
 * Right Hand                   Left Hand
 * |65|--|--|66|--|67|          |33|--|32|--|--|31|
 * |--|--|--|--|--|--|          |--|--|--|--|--|--|
 * |--|--|--|--|--|--|          |--|--|--|--|--|--|
 * |64|--|--|63|--|--|--|    |--|--|--|29|--|--|30|
 *             |--|62|--|    |--|28|--|
 */
// bool rgb_matrix_indicators_user(void) {
//   if (IS_LAYER_ON(1)) {
//     /* Upperleft most key red: */
//     rgb_matrix_set_color(0,255,0,0);
//     /* Upperright most front key blue: */
//     rgb_matrix_set_color(0,0,255,0);
//     /* Bottom right on lefthand Green: */
//     rgb_matrix_set_color(0, RGB_GREEN);
//   }
//   else if (IS_LAYER_ON(2)) {
//     /* RGB +/- controls. */
//     rgb_matrix_set_color(35, RGB_RED);
//     rgb_matrix_set_color(34, RGB_BLUE);
//     rgb_matrix_set_color(37, RGB_RED);
//     rgb_matrix_set_color(36, RGB_BLUE);
//     rgb_matrix_set_color(44, RGB_RED);
//     rgb_matrix_set_color(45, RGB_BLUE);
//     rgb_matrix_set_color(47, RGB_RED);
//     rgb_matrix_set_color(46, RGB_BLUE);
//     rgb_matrix_set_color(56, RGB_RED);
//     rgb_matrix_set_color(57, RGB_BLUE);
//     /* RGB Toggle. */
//     rgb_matrix_set_color(00, RGB_PURPLE);
//     /* Move screen left/right. */
//     rgb_matrix_set_color(26, RGB_YELLOW);
//     rgb_matrix_set_color(60, RGB_YELLOW);
//     /* Arrow keys. */
//     rgb_matrix_set_color(50, RGB_PURPLE);
//     rgb_matrix_set_color(49, RGB_PURPLE);
//     rgb_matrix_set_color(48, RGB_PURPLE);
//     rgb_matrix_set_color(42, RGB_PURPLE);
//     /* Mouse movement arrows. */
//     rgb_matrix_set_color(14, RGB_ORANGE);
//     rgb_matrix_set_color(15, RGB_ORANGE);
//     rgb_matrix_set_color(16, RGB_ORANGE);
//     rgb_matrix_set_color(8, RGB_ORANGE);
//     /* Mouse buttons. */
//     rgb_matrix_set_color(41, RGB_ORANGE);
//     rgb_matrix_set_color(43, RGB_ORANGE);
//     /* Mouse acceleration. */
//     rgb_matrix_set_color(01, 200, 165, 0);
//     rgb_matrix_set_color(02, 255, 200, 0);
//     rgb_matrix_set_color(03, 255, 235, 0);
//   }
//    return false;
// }

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
#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        /* Left Hand */                                                     /* Right Hand */
        /* Switch between tabs. (Control + Tab). */                         /* Switch between open apps on Mac. (Command + Tab + timer logic) */
        [_QWERTY] =  { ENCODER_CCW_CW(S(C(KC_TAB)), C(KC_TAB)),             ENCODER_CCW_CW(CMD_TAB_CCW, CMD_TAB_CW)  },
        /* Scrolls left & right. (Shift + Mouse Wheel Up). */               /* Scrolls up and down. (Page Down & Page Up - mouse wheel scroll incraments are too small) */
        [_LOWER] =  { ENCODER_CCW_CW(S(KC_MS_WH_UP), S(KC_MS_WH_DOWN)),     ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  },
        /* Selects adjacent words. (Command + Shift + Right Arrow). */      /* Jumps to end/start of line. Hold shift to select. (Gui + arrow). */
        [_RAISE] =  { ENCODER_CCW_CW(C(S(KC_LEFT)), C(S(KC_RGHT))),         ENCODER_CCW_CW(G(KC_LEFT), G(KC_RGHT))  },
        /* Scroll through RGB Modes */                                      /* Right & left arrow */
        [_ADJUST] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),                    ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    };
#endif


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
