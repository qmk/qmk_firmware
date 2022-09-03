#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │F13│F14│F15│F16│
     * ├───┼───┼───┼───┤
     * │Num│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │ 0     │ . │   │
     * └───────┴───┴───┘
     */
    [0] = LAYOUT_6x4(
        KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_P0,   KC_PDOT, KC_PENT,
        KC_VOLD, KC_BRID, KC_DOWN, KC_PGDN,
        KC_VOLU, KC_BRIU, KC_UP,   KC_PGUP
    ),
    [1] = LAYOUT_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),
    [2] = LAYOUT_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),
    [3] = LAYOUT_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),
};

keyevent_t encoder0_cw = {
    .key = (keypos_t){.row = 6, .col = 0},
    .pressed = false
};
keyevent_t encoder0_ccw = {
    .key = (keypos_t){.row = 6, .col = 1},
    .pressed = false
};
keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 6, .col = 2},
    .pressed = false
};
keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 6, .col = 3},
    .pressed = false
};
keyevent_t encoder2_cw = {
    .key = (keypos_t){.row = 7, .col = 0},
    .pressed = false
};
keyevent_t encoder2_ccw = {
    .key = (keypos_t){.row = 7, .col = 1},
    .pressed = false
};
keyevent_t encoder3_cw = {
    .key = (keypos_t){.row = 7, .col = 2},
    .pressed = false
};
keyevent_t encoder3_ccw = {
    .key = (keypos_t){.row = 7, .col = 3},
    .pressed = false
};

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder0_cw)) {
        encoder0_cw.pressed = false;
        encoder0_cw.time = (timer_read() | 1);
        action_exec(encoder0_cw);
    }
    if (IS_PRESSED(encoder0_ccw)) {
        encoder0_ccw.pressed = false;
        encoder0_ccw.time = (timer_read() | 1);
        action_exec(encoder0_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }
    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder2_cw)) {
        encoder2_cw.pressed = false;
        encoder2_cw.time = (timer_read() | 1);
        action_exec(encoder2_cw);
    }
    if (IS_PRESSED(encoder2_ccw)) {
        encoder2_ccw.pressed = false;
        encoder2_ccw.time = (timer_read() | 1);
        action_exec(encoder2_ccw);
    }

    if (IS_PRESSED(encoder3_cw)) {
        encoder3_cw.pressed = false;
        encoder3_cw.time = (timer_read() | 1);
        action_exec(encoder3_cw);
    }
    if (IS_PRESSED(encoder3_ccw)) {
        encoder3_ccw.pressed = false;
        encoder3_ccw.time = (timer_read() | 1);
        action_exec(encoder3_ccw);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            encoder0_cw.pressed = true;
            encoder0_cw.time = (timer_read() | 1);
            action_exec(encoder0_cw);
            wait_ms(20);
        } else {
            encoder0_ccw.pressed = true;
            encoder0_ccw.time = (timer_read() | 1);
            action_exec(encoder0_ccw);
            wait_ms(20);
        }
    } else if (index == 1) {
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
            wait_ms(20);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
            wait_ms(20);
        }
    } else if (index == 2) {
        if (clockwise) {
            encoder2_cw.pressed = true;
            encoder2_cw.time = (timer_read() | 1);
            action_exec(encoder2_cw);
            wait_ms(20);
        } else {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = (timer_read() | 1);
            action_exec(encoder2_ccw);
            wait_ms(20);
        }
    } else if (index == 3) {
        if (clockwise) {
            encoder3_cw.pressed = true;
            encoder3_cw.time = (timer_read() | 1);
            action_exec(encoder3_cw);
            wait_ms(20);
        } else {
            encoder3_ccw.pressed = true;
            encoder3_ccw.time = (timer_read() | 1);
            action_exec(encoder3_ccw);
            wait_ms(20);
        }
    }

    return false;
}
