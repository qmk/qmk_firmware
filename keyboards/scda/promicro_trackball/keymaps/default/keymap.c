#include QMK_KEYBOARD_H

bool set_scrolling = true;
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    }
    return mouse_report;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_0,
        KC_1,
                KC_3,
                KC_5,
        KC_6, KC_7,
        KC_8, KC_9,
        KC_A, KC_B,
        KC_C, KC_D,
        KC_E, KC_F,
        KC_G
    )
};
