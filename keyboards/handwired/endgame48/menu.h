// Copyright 2022 Andrew Dunai (@and3rson)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "stdint.h"
#include "endgame48.h"
#include "symbols.h"
#include "oled/oled_driver.h"
#include "stdio.h"

typedef struct menu_item_t {
    char title[6];
    void (*func)(void);
    struct menu_t *submenu;
} menu_item_t;

typedef struct menu_t {
    char   *title;
    uint8_t count;
    uint8_t current;
    uint8_t scroll;
    void (*opened)(struct menu_t *);
    menu_item_t *items;
} menu_t;

extern menu_t main_menu;

bool menu_process_record(uint16_t keycode, keyrecord_t *record);
bool menu_encoder_update(uint8_t index, bool clockwise);
bool menu_oled_task(void);
