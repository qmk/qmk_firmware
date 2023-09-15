// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later
// Code forked from https://github.com/brentaro/QMK_HID_Gamepad_with_SOCD
#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "joystick.h"

// Joystick Config
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL,
};

bool DPU_STATE = false;
bool DPD_STATE = false;
bool DPL_STATE = false;
bool DPR_STATE = false;

bool gamepad_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GP_DPU:
            if (record->event.pressed) {
                DPU_STATE = true;
                if (DPD_STATE) {
                    unregister_joystick_button(16);
                } else {
                    register_joystick_button(18);
                }
            } else {
                DPU_STATE = false;
                unregister_joystick_button(18);
                if (DPD_STATE) {
                    register_joystick_button(16);
                }
            }
            return false;
        case GP_DPD:
            if (record->event.pressed) {
                DPD_STATE = true;
                if (DPU_STATE) {
                    unregister_joystick_button(18);
                } else {
                    register_joystick_button(16);
                }
            } else {
                DPD_STATE = false;
                unregister_joystick_button(16);
                if (DPU_STATE) {
                    register_joystick_button(18);
                }
            }
            return false;
        case GP_DPL:
            if (record->event.pressed) {
                DPL_STATE = true;
                if (DPR_STATE) {
                    unregister_joystick_button(17);
                } else {
                    register_joystick_button(15);
                }
            } else {
                DPL_STATE = false;
                unregister_joystick_button(15);
                if (DPR_STATE) {
                    register_joystick_button(17);
                }
            }
            return false;
        case GP_DPR:
            if (record->event.pressed) {
                DPR_STATE = true;
                if (DPL_STATE) {
                    unregister_joystick_button(15);
                } else {
                    register_joystick_button(17);
                }
            } else {
                DPR_STATE = false;
                unregister_joystick_button(17);
                if (DPL_STATE) {
                    register_joystick_button(15);
                }
            }
            return false;
        case GP_X:
            if (record->event.pressed) {
                register_joystick_button(0);
            } else {
                unregister_joystick_button(0);
            }
            return false;
        case GP_A:
            if (record->event.pressed) {
                register_joystick_button(1);
            } else {
                unregister_joystick_button(1);
            }
            return false;
        case GP_B:
            if (record->event.pressed) {
                register_joystick_button(2);
            } else {
                unregister_joystick_button(2);
            }
            return false;
        case GP_Y:
            if (record->event.pressed) {
                register_joystick_button(3);
            } else {
                unregister_joystick_button(3);
            }
            return false;
        case GP_LB:
            if (record->event.pressed) {
                register_joystick_button(4);
            } else {
                unregister_joystick_button(4);
            }
            return false;
        case GP_RB:
            if (record->event.pressed) {
                register_joystick_button(5);
            } else {
                unregister_joystick_button(5);
            }
            return false;
        case GP_LT:
            if (record->event.pressed) {
                register_joystick_button(6);
            } else {
                unregister_joystick_button(6);
            }
            return false;
        case GP_RT:
            if (record->event.pressed) {
                register_joystick_button(7);
            } else {
                unregister_joystick_button(7);
            }
            return false;
        case GP_BCK:
            if (record->event.pressed) {
                register_joystick_button(8);
            } else {
                unregister_joystick_button(8);
            }
            return false;
        case GP_STA:
            if (record->event.pressed) {
                register_joystick_button(9);
            } else {
                unregister_joystick_button(9);
            }
            return false;
        case GP_LSB:
            if (record->event.pressed) {
                register_joystick_button(10);
            } else {
                unregister_joystick_button(10);
            }
            return false;
        case GP_RSB:
            if (record->event.pressed) {
                register_joystick_button(11);
            } else {
                unregister_joystick_button(11);
            }
            return false;
        case GP_HOM:
            if (record->event.pressed) {
                register_joystick_button(12);
            } else {
                unregister_joystick_button(12);
            }
            return false;
        default:
            return true;
    }
}
