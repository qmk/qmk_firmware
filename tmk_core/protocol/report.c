/* Copyright 2017 Fred Sundvik
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

#include "report.h"
#include "action_util.h"
#include "host.h"
#include "keycode_config.h"
#include "debug.h"
#include "usb_device_state.h"
#include "util.h"
#include <string.h>

/** \brief has_anykey
 *
 * FIXME: Needs doc
 */
uint8_t has_anykey(void) {
    uint8_t  cnt = 0;
    uint8_t* p   = keyboard_report->keys;
    uint8_t  lp  = sizeof(keyboard_report->keys);
#ifdef NKRO_ENABLE
    if (usb_device_state_get_protocol() == USB_PROTOCOL_REPORT && keymap_config.nkro) {
        p  = nkro_report->bits;
        lp = sizeof(nkro_report->bits);
    }
#endif
    while (lp--) {
        if (*p++) cnt++;
    }
    return cnt;
}

/** \brief get_first_key
 *
 * FIXME: Needs doc
 */
uint8_t get_first_key(void) {
#ifdef NKRO_ENABLE
    if (usb_device_state_get_protocol() == USB_PROTOCOL_REPORT && keymap_config.nkro) {
        uint8_t i = 0;
        for (; i < NKRO_REPORT_BITS && !nkro_report->bits[i]; i++)
            ;
        return i << 3 | biton(nkro_report->bits[i]);
    }
#endif
    return keyboard_report->keys[0];
}

/** \brief Checks if a key is pressed in the report
 *
 * Returns true if the keyboard_report reports that the key is pressed, otherwise false
 * Note: The function doesn't support modifers currently, and it returns false for KC_NO
 */
bool is_key_pressed(uint8_t key) {
    if (key == KC_NO) {
        return false;
    }
#ifdef NKRO_ENABLE
    if (usb_device_state_get_protocol() == USB_PROTOCOL_REPORT && keymap_config.nkro) {
        if ((key >> 3) < NKRO_REPORT_BITS) {
            return nkro_report->bits[key >> 3] & 1 << (key & 7);
        } else {
            return false;
        }
    }
#endif
    for (int i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == key) {
            return true;
        }
    }
    return false;
}

/** \brief add key byte
 *
 * FIXME: Needs doc
 */
void add_key_byte(report_keyboard_t* keyboard_report, uint8_t code) {
    int8_t i     = 0;
    int8_t empty = -1;
    for (; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            break;
        }
        if (empty == -1 && keyboard_report->keys[i] == 0) {
            empty = i;
        }
    }
    if (i == KEYBOARD_REPORT_KEYS) {
        if (empty != -1) {
            keyboard_report->keys[empty] = code;
        }
    }
}

/** \brief del key byte
 *
 * FIXME: Needs doc
 */
void del_key_byte(report_keyboard_t* keyboard_report, uint8_t code) {
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            keyboard_report->keys[i] = 0;
        }
    }
}

#ifdef NKRO_ENABLE
/** \brief add key bit
 *
 * FIXME: Needs doc
 */
void add_key_bit(report_nkro_t* nkro_report, uint8_t code) {
    if ((code >> 3) < NKRO_REPORT_BITS) {
        nkro_report->bits[code >> 3] |= 1 << (code & 7);
    } else {
        dprintf("add_key_bit: can't add: %02X\n", code);
    }
}

/** \brief del key bit
 *
 * FIXME: Needs doc
 */
void del_key_bit(report_nkro_t* nkro_report, uint8_t code) {
    if ((code >> 3) < NKRO_REPORT_BITS) {
        nkro_report->bits[code >> 3] &= ~(1 << (code & 7));
    } else {
        dprintf("del_key_bit: can't del: %02X\n", code);
    }
}
#endif

/** \brief add key to report
 *
 * FIXME: Needs doc
 */
void add_key_to_report(uint8_t key) {
#ifdef NKRO_ENABLE
    if (usb_device_state_get_protocol() == USB_PROTOCOL_REPORT && keymap_config.nkro) {
        add_key_bit(nkro_report, key);
        return;
    }
#endif
    add_key_byte(keyboard_report, key);
}

/** \brief del key from report
 *
 * FIXME: Needs doc
 */
void del_key_from_report(uint8_t key) {
#ifdef NKRO_ENABLE
    if (usb_device_state_get_protocol() == USB_PROTOCOL_REPORT && keymap_config.nkro) {
        del_key_bit(nkro_report, key);
        return;
    }
#endif
    del_key_byte(keyboard_report, key);
}

/** \brief clear key from report
 *
 * FIXME: Needs doc
 */
void clear_keys_from_report(void) {
    // not clear mods
#ifdef NKRO_ENABLE
    if (usb_device_state_get_protocol() == USB_PROTOCOL_REPORT && keymap_config.nkro) {
        memset(nkro_report->bits, 0, sizeof(nkro_report->bits));
        return;
    }
#endif
    memset(keyboard_report->keys, 0, sizeof(keyboard_report->keys));
}

#ifdef MOUSE_ENABLE
/**
 * @brief Compares 2 mouse reports for difference and returns result. Empty
 * reports always evaluate as unchanged.
 *
 * @param[in] new_report report_mouse_t
 * @param[in] old_report report_mouse_t
 * @return bool result
 */
__attribute__((weak)) bool has_mouse_report_changed(report_mouse_t* new_report, report_mouse_t* old_report) {
    // memcmp doesn't work here because of the `report_id` field when using
    // shared mouse endpoint
    bool changed = ((new_report->buttons != old_report->buttons) ||
#    ifdef MOUSE_EXTENDED_REPORT
                    (new_report->boot_x != 0 && new_report->boot_x != old_report->boot_x) || (new_report->boot_y != 0 && new_report->boot_y != old_report->boot_y) ||
#    endif
                    (new_report->x != 0 && new_report->x != old_report->x) || (new_report->y != 0 && new_report->y != old_report->y) || (new_report->h != 0 && new_report->h != old_report->h) || (new_report->v != 0 && new_report->v != old_report->v));
    return changed;
}
#endif
