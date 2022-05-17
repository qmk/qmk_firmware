// Copyright 2022 Andrew Dunai (@and3rson)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "endgame48.h"
#include "quantum.h"
#include "raw_hid.h"
#include "bitwise.h"
#include "oled/oled_driver.h"
#include "symbols.h"
#include "string.h"
#include "stdio.h"
#include "eeprom.h"
#include "encoder.h"
#include "menu.h"
#include "rgblight.h"

volatile static uint32_t reset_requested = 0;

void oled_paint(void);

void request_reset(void) {
    reset_requested = timer_read32();
    oled_clear();
    oled_write_P(logo, false);
    oled_write_P(resetIcon, false);
    oled_write("\nREADY\n FOR \nFLASH", false);

    for (int i = 0; i < 16; i++) {
        oled_render();
    }
    rgblight_setrgb((DEBUG_COLOR >> 16) & 0xFF, (DEBUG_COLOR >> 8) & 0xFF, DEBUG_COLOR & 0xFF);
    reset_keyboard();
}

void mute(void) {
    tap_code(KC_MUTE);
}

void init_eeprom_menu(menu_t *this) {
    for (uint16_t i = 0; i < this->count; i++) {
        uint8_t b = eeprom_read_byte((uint8_t *)i);
        sprintf(this->items[i].title, "%02X:%02X", i, b);
    }
}

static menu_t list_eeprom_menu = {
    .title  = "EEPRM",
    .count  = 64,
    .items  = (menu_item_t[64]){},
    .opened = init_eeprom_menu,
};

menu_t main_menu = {
    .title = "CFG",
    .count = 5,
    .items =
        (menu_item_t[]){
            {
                .title = "Mute",
                .func  = mute,
            },
            {
                .title = "RGB",
                .func  = rgblight_toggle_noeeprom,
            },
            {
                .title = "Reset",
                .func  = request_reset,
            },
            {
                .title   = "LsEE",
                .submenu = &list_eeprom_menu,
            },
            {
                .title = "DelEE",
                .func  = eeconfig_init,
            },
        },
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!menu_process_record(keycode, record)) {
        return false;
    }
    return process_record_user(keycode, record);
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!menu_encoder_update(index, clockwise)) {
        return false;
    }
    return encoder_update_user(index, clockwise);
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static uint32_t last_render = 0;

bool oled_task_kb(void) {
    if (timer_elapsed32(last_render) > 100) {
        last_render = timer_read32();
        if (!menu_oled_task()) {
            return false;
        }
        oled_task_user();
    }
    return false;
}
