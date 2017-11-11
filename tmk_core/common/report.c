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
#include "host.h"
#include "keycode_config.h"
#include "debug.h"
#include "util.h"

uint8_t has_anykey(report_keyboard_t* keyboard_report)
{
    uint8_t cnt = 0;
    for (uint8_t i = 1; i < KEYBOARD_REPORT_SIZE; i++) {
        if (keyboard_report->raw[i])
            cnt++;
    }
    return cnt;
}

uint8_t get_first_key(report_keyboard_t* keyboard_report)
{
#ifdef NKRO_ENABLE
    if (keyboard_protocol && keymap_config.nkro) {
        uint8_t i = 0;
        for (; i < KEYBOARD_REPORT_BITS && !keyboard_report->nkro.bits[i]; i++)
            ;
        return i<<3 | biton(keyboard_report->nkro.bits[i]);
    }
#endif
#ifdef USB_6KRO_ENABLE
    uint8_t i = cb_head;
    do {
        if (keyboard_report->keys[i] != 0) {
            break;
        }
        i = RO_INC(i);
    } while (i != cb_tail);
    return keyboard_report->keys[i];
#else
    return keyboard_report->keys[0];
#endif
}

void add_key_byte(report_keyboard_t* keyboard_report, uint8_t code)
{
#ifdef USB_6KRO_ENABLE
    int8_t i = cb_head;
    int8_t empty = -1;
    if (cb_count) {
        do {
            if (keyboard_report->keys[i] == code) {
                return;
            }
            if (empty == -1 && keyboard_report->keys[i] == 0) {
                empty = i;
            }
            i = RO_INC(i);
        } while (i != cb_tail);
        if (i == cb_tail) {
            if (cb_tail == cb_head) {
                // buffer is full
                if (empty == -1) {
                    // pop head when has no empty space
                    cb_head = RO_INC(cb_head);
                    cb_count--;
                }
                else {
                    // left shift when has empty space
                    uint8_t offset = 1;
                    i = RO_INC(empty);
                    do {
                        if (keyboard_report->keys[i] != 0) {
                            keyboard_report->keys[empty] = keyboard_report->keys[i];
                            keyboard_report->keys[i] = 0;
                            empty = RO_INC(empty);
                        }
                        else {
                            offset++;
                        }
                        i = RO_INC(i);
                    } while (i != cb_tail);
                    cb_tail = RO_SUB(cb_tail, offset);
                }
            }
        }
    }
    // add to tail
    keyboard_report->keys[cb_tail] = code;
    cb_tail = RO_INC(cb_tail);
    cb_count++;
#else
    int8_t i = 0;
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
#endif
}

void del_key_byte(report_keyboard_t* keyboard_report, uint8_t code)
{
#ifdef USB_6KRO_ENABLE
    uint8_t i = cb_head;
    if (cb_count) {
        do {
            if (keyboard_report->keys[i] == code) {
                keyboard_report->keys[i] = 0;
                cb_count--;
                if (cb_count == 0) {
                    // reset head and tail
                    cb_tail = cb_head = 0;
                }
                if (i == RO_DEC(cb_tail)) {
                    // left shift when next to tail
                    do {
                        cb_tail = RO_DEC(cb_tail);
                        if (keyboard_report->keys[RO_DEC(cb_tail)] != 0) {
                            break;
                        }
                    } while (cb_tail != cb_head);
                }
                break;
            }
            i = RO_INC(i);
        } while (i != cb_tail);
    }
#else
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            keyboard_report->keys[i] = 0;
        }
    }
#endif
}

#ifdef NKRO_ENABLE
void add_key_bit(report_keyboard_t* keyboard_report, uint8_t code)
{
    if ((code>>3) < KEYBOARD_REPORT_BITS) {
        keyboard_report->nkro.bits[code>>3] |= 1<<(code&7);
    } else {
        dprintf("add_key_bit: can't add: %02X\n", code);
    }
}

void del_key_bit(report_keyboard_t* keyboard_report, uint8_t code)
{
    if ((code>>3) < KEYBOARD_REPORT_BITS) {
        keyboard_report->nkro.bits[code>>3] &= ~(1<<(code&7));
    } else {
        dprintf("del_key_bit: can't del: %02X\n", code);
    }
}
#endif

void add_key_to_report(report_keyboard_t* keyboard_report, int8_t key)
{
#ifdef NKRO_ENABLE
    if (keyboard_protocol && keymap_config.nkro) {
        add_key_bit(keyboard_report, key);
        return;
    }
#endif
    add_key_byte(keyboard_report, key);
}

void del_key_from_report(report_keyboard_t* keyboard_report, uint8_t key)
{
#ifdef NKRO_ENABLE
    if (keyboard_protocol && keymap_config.nkro) {
        del_key_bit(keyboard_report, key);
        return;
    }
#endif
    del_key_byte(keyboard_report, key);
}

void clear_keys_from_report(report_keyboard_t* keyboard_report)
{
    // not clear mods
    for (int8_t i = 1; i < KEYBOARD_REPORT_SIZE; i++) {
        keyboard_report->raw[i] = 0;
    }
}