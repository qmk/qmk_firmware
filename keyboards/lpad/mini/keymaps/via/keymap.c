// #include "drashna.h"
#include "mini.h"
#include "oled.c"
#include "encoder.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		TO(1), KC_MUTE,
		KC_P7, KC_P8, KC_P9, KC_BSPC,
		KC_P4, KC_P5, KC_P6, LT(1, KC_PENT),
		KC_P1, KC_P2, KC_P3,
		KC_P0, KC_KP_DOT),

	[1] = LAYOUT(
		TO(2), KC_MUTE,
		RGB_RMOD, RGB_MOD, KC_TRNS, RGB_TOG,
		RGB_VAD, RGB_VAI, KC_TRNS, LT(1, KC_PENT),
		RGB_SAD, RGB_SAI, KC_TRNS,
		KC_PWR, RESET),

	[2] = LAYOUT(
		TO(3), KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS),

    [3] = LAYOUT(
		TO(4), KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS),

    [4] = LAYOUT(
		TO(0), KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS)

};


// void pointing_device_task(void) {
//     report_mouse_t report = pointing_device_get_report();

//     // todo read as one vector
//     if (timer_elapsed(lastCursor) > cursorTimeout) {
//         lastCursor = timer_read();
//         report.x   = axisToMouseComponent(B4, xOrigin, maxCursorSpeed, xPolarity);
//         report.y   = axisToMouseComponent(B5, yOrigin, maxCursorSpeed, yPolarity);
//     }
//     //
//     if (!readPin(E6)) {
//         report.buttons |= MOUSE_BTN1;
//     } else {
//         report.buttons &= ~MOUSE_BTN1;
//     }

//     pointing_device_set_report(report);
//     pointing_device_send();
// }

// void matrix_init_keymap(void) {
//     // init pin? Is needed?
//     setPinInputHigh(E6);
//     // Account for drift
//     xOrigin = analogReadPin(B4);
//     yOrigin = analogReadPin(B5);
// }
