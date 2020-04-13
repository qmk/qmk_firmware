/*
Copyright 2018 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

#include "bmp_indicator_led.h"

// indicator priority -> lower is prior
const static uint8_t
    indicator_priority[INDICATOR_END] = {
        [INDICATOR_NONE] = 255,
        [INDICATOR_TURN_OFF] = 0,
        [INDICATOR_BATTERY] = 1,
        [INDICATOR_ADVERTISING] = 3,
        [INDICATOR_CONNECTED] = 2,
        [INDICATOR_CONNECTING] = 3,
        [INDICATOR_USER] = 0,
    };

typedef struct {
    BMP_INDICATOR_TYPE type;
    int32_t option;
} bmp_indicator_pattern_t;

#define INDICATOR_STACK_LEN 3
static bmp_indicator_pattern_t indicator_stack[INDICATOR_STACK_LEN];
static uint8_t indicator_stack_cnt = 0;

// return: stack index
int bmp_indicator_set(BMP_INDICATOR_TYPE type, int32_t option) {
    if (type >= INDICATOR_END) {
        return -1;
    }

    if (indicator_stack_cnt == 0) {
        indicator_stack[0].type = type;
        indicator_stack[0].option = option;
        indicator_stack_cnt = 1;
    }

    uint8_t priority = indicator_priority[type];

    for (uint8_t idx = 0;
            idx < sizeof(indicator_stack) / sizeof(indicator_stack[0]);
            idx++)
    {
        if (indicator_priority[indicator_stack[idx].type] >= priority) {
            indicator_stack[idx].type = type;
            indicator_stack[idx].option = option;
            indicator_stack_cnt = idx + 1;

            // clear rest of stack
            for (uint8_t idx = indicator_stack_cnt; idx < sizeof(indicator_stack) / sizeof(indicator_stack[0]); idx++) {
                indicator_stack[idx].type = INDICATOR_NONE;
                indicator_stack[idx].option = 0;
            }

            return idx;
        }
    }

    return -1;
}

static int bmp_indicator_none(uint32_t time_ms, int32_t option) {
    bmp_indicator_led_off();
    return 1;
}

static int bmp_indicator_turnoff(uint32_t time_ms, int32_t option) {
    bmp_indicator_led_off();
    return 1;
}

static int bmp_indicator_battery(uint32_t time_ms, int32_t option) {
    if (time_ms > 0 && time_ms <100) {
        bmp_indicator_led_on();
    }
    else if (time_ms > 300 && time_ms <400 && option > 1) {
        bmp_indicator_led_on();
    }
    else if (time_ms > 600 && time_ms <700 && option > 2) {
        bmp_indicator_led_on();
    }
    else if (time_ms > 3000) {
        bmp_indicator_led_off();
        return 1;
    }
    else {
        bmp_indicator_led_off();
    }

    return 0;
}

static int bmp_indicator_advertising(uint32_t time_ms, int32_t option) {
    const uint32_t period = 5000;
    uint32_t time_in_period = time_ms % period;

    if (time_in_period > 0 && time_in_period <50) {
        bmp_indicator_led_on();
    }
    else if (time_in_period > 150 && time_in_period <200) {
        bmp_indicator_led_on();
    }
    else {
        bmp_indicator_led_off();
    }

    return 0;
}

static int bmp_indicator_connected(uint32_t time_ms, int32_t option) {
    if (time_ms > 0 && time_ms <300) {
        bmp_indicator_led_on();
    }
    else if (time_ms > 3000) {
        bmp_indicator_led_off();
        return 1;
    }
    else {
        bmp_indicator_led_off();
    }

    return 0;
}

static int bmp_indicator_connecting(uint32_t time_ms, int32_t option) {
    return 1;
}

__attribute__((weak)) int bmp_indicator_user_pattern(uint32_t time_ms, int32_t option) { return 1; }

typedef int (*bmp_indicator_task_t)(uint32_t time_ms, int32_t option);
const static bmp_indicator_task_t indicator_tasks[INDICATOR_END] = {
    [INDICATOR_NONE] = bmp_indicator_none,
    [INDICATOR_TURN_OFF] = bmp_indicator_turnoff,
    [INDICATOR_BATTERY] = bmp_indicator_battery,
    [INDICATOR_ADVERTISING] = bmp_indicator_advertising,
    [INDICATOR_CONNECTED] = bmp_indicator_connected,
    [INDICATOR_CONNECTING] = bmp_indicator_connecting,
    [INDICATOR_USER] = bmp_indicator_user_pattern,
};

void bmp_indicator_task(uint32_t elapsed_time_ms) {
    static uint32_t time;
    static BMP_INDICATOR_TYPE current_type = INDICATOR_NONE;

    time += elapsed_time_ms;

    if (indicator_stack[0].type != current_type) {
        current_type = indicator_stack[0].type;
        time = 0;
    }

    int res = indicator_tasks[current_type](time, indicator_stack[0].option);

    if (res) {
        if (indicator_stack_cnt > 1) {
            for (int idx = 0;
                idx < indicator_stack_cnt - 1;
                idx++)
            {
                indicator_stack[idx] = indicator_stack[idx + 1];
            }

            indicator_stack_cnt--;
            indicator_stack[indicator_stack_cnt].type = INDICATOR_NONE;
            indicator_stack[indicator_stack_cnt].option = 0;
        } else {
            indicator_stack[0].type = INDICATOR_NONE;
            indicator_stack[0].option = 0;
            indicator_stack_cnt = 0;
        }
    }
}

static uint8_t indicator_led = 0xFF;
void bmp_indicator_init(uint8_t led_pin) {
    setPinOutput(led_pin);
    indicator_led = led_pin;
}

void bmp_indicator_led_on() {
    writePinHigh(indicator_led);
}

void bmp_indicator_led_off() {
    writePinLow(indicator_led);
}

