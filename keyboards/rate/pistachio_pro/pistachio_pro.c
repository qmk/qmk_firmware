// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdio.h>
#include "quantum.h"
#include "lib/bme280.h"

void keyboard_post_init_kb(void) {
    bme280_init();
    keyboard_post_init_kb();
}
void housekeeping_task_kb(void) {
    bme280_exec();
    housekeeping_task_user();
}

#ifdef OLED_ENABLE
const char code_to_name[60] = {
    //clang-format off
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',  'p', 'q', 'r',  's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1',
    '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
    // clang-format on
};

static void print_airstate(void) {
    char   airstate_str[32];
    double temp;
    double press;
    double hum;

    temp  = bme280_getTemp();
    press = bme280_getPress();
    hum   = bme280_getHum();

    oled_write_ln_P(PSTR("\nTemp   Press    Hum"), false);
    snprintf(airstate_str, sizeof(airstate_str), "%ddeg  %dhPa  %d%% \n", (int)temp, (int)press, (int)hum);
    oled_write(airstate_str, false);

    return;
}

static keyrecord_t keylog_record;
static void        print_keylog(void) {
    char keylog_str[32];

    oled_write_ln_P(PSTR("\nKeylog"), false);
    snprintf(keylog_str, sizeof(keylog_str), "row:%d col:%d", keylog_record.event.key.row, keylog_record.event.key.col);
    oled_write(keylog_str, false);

    return;
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_write_ln_P(PSTR("  - PistachioPro -"), false);
    print_airstate();
    print_keylog();

    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    if (record->event.pressed) {
        keylog_record = *record;
    }
    return true;
}
#endif
