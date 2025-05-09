/* Copyright 2020 yushakobo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rev3_4rows.h"

bool is_mac_mode(void) {
    return keymap_config.swap_lalt_lgui == false;
}

void set_mac_mode(bool macmode) {
    /* The result is the same as pressing the AG_NORM(=MAGIC_UNSWAP_ALT_GUI)/AG_SWAP(=MAGIC_SWAP_ALT_GUI) keys.
     * see
     *   https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L123-L124
     *   https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L80-L81
     */
    keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = !macmode;
    eeconfig_update_keymap(keymap_config.raw);
}

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    switch (index) {
    case 0:
        if(active) { // Left no.1  Helix rev3 common
            set_mac_mode(false);
        } else {
            set_mac_mode(true);
        }
        break;
    default: // Left no.2 or Right no.1 or Right no.2 for user/keymap
        dip_switch_update_user(index, active);
        break;
    }
    return true;
}
#endif

#ifdef OLED_ENABLE
static char *sprint_decimal(char *buf, int data) {
    if (data > 9) {
        buf = sprint_decimal(buf, data/10);
    }
    *buf++ = "0123456789"[data%10];
    *buf = '\0';
    return buf;
}

char *sprints(char *buf, char *src) {
    while (*src) {
        *buf++ = *src++;
    }
    *buf = '\0';
    return buf;
}

char *sprintd(char *buf, char *leadstr, int data) {
    buf = sprints(buf, leadstr);
    buf = sprint_decimal(buf, data);
    return buf;
}

char *sprint2d(char *buf, char *leadstr, int data) {
    buf = sprints(buf, leadstr);
    if (data > 99) {
        return sprint_decimal(buf, data);
    }
    if (data < 10) {
        *buf++ = ' ';
    }
    return sprint_decimal(buf, data);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    static const char PROGMEM helix_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4,
        0x0
    };
    static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};

    if (is_keyboard_master()) {
        if (is_mac_mode()) {
            oled_write_P(os_logo[0][0], false);
            oled_write_P(PSTR("\n"), false);
            oled_write_P(os_logo[0][1], false);
        }else{
            oled_write_P(os_logo[1][0], false);
            oled_write_P(PSTR("\n"), false);
            oled_write_P(os_logo[1][1], false);
        }
        char buf[20];
        sprint2d(buf, " Layer: ", get_highest_layer(layer_state));
        oled_write(buf, false);
    } else {
        oled_write_P(helix_logo, false);
    }
    return false;
}
#endif
