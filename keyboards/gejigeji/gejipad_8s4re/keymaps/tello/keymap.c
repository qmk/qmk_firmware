// Copyright 2026 gejigeji-com (@gejigeji-com)
// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * gejipad_8s4re - "tello" keymap
 *
 * Sends DJI Tello SDK text commands (over a serial terminal connected to the
 * USB CDC / keyboard output) for basic flight control.
 */
#include QMK_KEYBOARD_H

enum custom_keycodes {
    TELLO_LAND = SAFE_RANGE,
    TELLO_TAKEOFF,
    TELLO_RIGHT_100,
    TELLO_RIGHT_50,
    TELLO_FLIP_R,
    TELLO_FLIP_L,
    TELLO_LEFT_50,
    TELLO_LEFT_100,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        /* SW6          SW7              SW8             SW9           SW10          SW11           SW12            SW13 */
        TELLO_LAND,    TELLO_RIGHT_100, TELLO_RIGHT_50, TELLO_FLIP_R, TELLO_FLIP_L, TELLO_LEFT_50, TELLO_LEFT_100, TELLO_TAKEOFF
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }
    switch (keycode) {
        case TELLO_LAND:
            SEND_STRING("land" SS_TAP(X_ENTER));
            return false;
        case TELLO_TAKEOFF:
            SEND_STRING("takeoff" SS_TAP(X_ENTER));
            return false;
        case TELLO_RIGHT_100:
            SEND_STRING("right 100" SS_TAP(X_ENTER));
            return false;
        case TELLO_RIGHT_50:
            SEND_STRING("right 50" SS_TAP(X_ENTER));
            return false;
        case TELLO_FLIP_R:
            SEND_STRING("flip r" SS_TAP(X_ENTER));
            return false;
        case TELLO_FLIP_L:
            SEND_STRING("flip l" SS_TAP(X_ENTER));
            return false;
        case TELLO_LEFT_50:
            SEND_STRING("left 50" SS_TAP(X_ENTER));
            return false;
        case TELLO_LEFT_100:
            SEND_STRING("left 100" SS_TAP(X_ENTER));
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0: // up / down
            if (clockwise) {
                SEND_STRING("up 20" SS_TAP(X_ENTER));
            } else {
                SEND_STRING("down 20" SS_TAP(X_ENTER));
            }
            break;
        case 1: // forward / back
            if (clockwise) {
                SEND_STRING("forward 20" SS_TAP(X_ENTER));
            } else {
                SEND_STRING("back 20" SS_TAP(X_ENTER));
            }
            break;
        case 2: // cw / ccw (yaw)
            if (clockwise) {
                SEND_STRING("cw 5" SS_TAP(X_ENTER));
            } else {
                SEND_STRING("ccw 5" SS_TAP(X_ENTER));
            }
            break;
        case 3: // right / left
            if (clockwise) {
                SEND_STRING("right 20" SS_TAP(X_ENTER));
            } else {
                SEND_STRING("left 20" SS_TAP(X_ENTER));
            }
            break;
    }
    return true;
}
#endif
