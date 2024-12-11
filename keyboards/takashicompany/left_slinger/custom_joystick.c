// Copyright 2024 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "analog.h"
#include "gpio.h"
#include "wait.h"
#include "timer.h"
#include <stdlib.h>
#include "print.h"
#include "custom_joystick.h"

int16_t xOrigin, yOrigin;
uint16_t lastCursor = 0;
int16_t joystick_ratio = 100;
int16_t joystick_raw_x = 0;
int16_t joystick_raw_y = 0;

int16_t axisCoordinate_custom(pin_t pin, uint16_t origin) {
    int8_t  direction;              // 符号
    int16_t distanceFromOrigin;     // 原点からの距離。負数にはならない

    int16_t position = analogReadPin(pin);  // 多分だけどデフォルトだと512が中心に来るようになっている

    if (origin == position) {           // 原点と同じなら0とする
        return 0;
    } else if (origin > position) {     // 原点よりマイナス方向の場合の処理
         distanceFromOrigin = origin - position;
        direction          = -1;
    } else {                            // 原点よりプラス方向の処理
        distanceFromOrigin = position - origin;
        direction          = 1;
    }
    
    return distanceFromOrigin * direction;
}

void pointing_device_driver_init(void) {
    xOrigin = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    yOrigin = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {

    if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {    // 多分、指定のミリ秒経過したかを見て処理を走らせている
        lastCursor = timer_read();
		
        int16_t jsr = joystick_ratio;
        if (0 <= jsr && jsr < 10) {
            jsr = 10;
        }
        else if (-10 < jsr && jsr < 0) {
            jsr = -10;
        }

        joystick_raw_x = axisCoordinate_custom(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin);
        joystick_raw_y = axisCoordinate_custom(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin);

        mouse_report.x = joystick_raw_x / jsr;
        mouse_report.y = joystick_raw_y / jsr;
    }

    return mouse_report;
}

uint16_t       pointing_device_driver_get_cpi(void) { return 0; }
void           pointing_device_driver_set_cpi(uint16_t cpi) {}