// Copyright 2022 Andrew Dunai (@and3rson)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "menu.h"

static int8_t  menu_depth = -1;
static menu_t *menus[8];

#define MENU_OPENED menu_depth != -1
#define MENU_CURRENT menus[menu_depth]
#define MENU_MAX_ITEMS 10

bool menu_process_record(uint16_t keycode, keyrecord_t *record) {
    if (MENU_OPENED) {
        /* Menu is open */
        if (record->event.pressed) {
            if (keycode == KC_EGMENU) {
                menu_t     *menu = MENU_CURRENT;
                menu_item_t item = menu->items[menu->current];
                if (item.submenu != NULL) {
                    item.submenu->current = 0;
                    item.submenu->scroll  = 0;
                    menus[++menu_depth]   = item.submenu;
                    item.submenu->opened(item.submenu);
                } else if (item.func != NULL) {
                    item.func();
                    menu_depth = -1;
                }
            } else {
                menu_depth--;
            }
        }
        return false;
    } else if (keycode == KC_EGMENU) {
        /* Menu is not open, KC_EGMENU pressed */
        if (record->event.pressed) {
            main_menu.current   = 0;
            main_menu.scroll    = 0;
            menus[++menu_depth] = &main_menu;
        }
        return false;
    }
    return true;
}

bool menu_encoder_update(uint8_t index, bool clockwise) {
    if (MENU_OPENED) {
        menu_t *menu = MENU_CURRENT;
        if (clockwise) {
            if (menu->current < menu->count - 1) {
                menu->current++;
            }
            if (menu->current - menu->scroll >= MENU_MAX_ITEMS) {
                menu->scroll++;
            }
        } else {
            if (menu->current) {
                menu->current--;
            }
            if (menu->current < menu->scroll) {
                menu->scroll--;
            }
        }
        return false;
    }
    return true;
}

bool menu_oled_task(void) {
    if (MENU_OPENED) {
        oled_clear();
        oled_write_P(logo, false);
        menu_t *menu     = MENU_CURRENT;
        char    title[7] = "     \0\0";
        sprintf(title, "%-5s", menu->title);
        title[5] = '\n';
        oled_write(title, false);
        for (uint8_t i = menu->scroll; i < (menu->count >= MENU_MAX_ITEMS ? menu->scroll + MENU_MAX_ITEMS : menu->count); i++) {
            char buf[6] = "     \0";
            sprintf(buf, "%-5s", menu->items[i].title);
            oled_write(buf, menu->current == i);
        }
        return false;
    }
    return true;
}
