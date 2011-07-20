/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <avr/interrupt.h>
#include "usb_keycodes.h"
#include "usb_keyboard.h"
#if defined(MOUSEKEY_ENABLE) || defined(PS2_MOUSE_ENABLE)
#include "usb_mouse.h"
#endif
#ifdef USB_EXTRA_ENABLE
#include "usb_extra.h"
#endif
#include "debug.h"
#include "host.h"
#include "util.h"


#ifdef USB_NKRO_ENABLE
bool keyboard_nkro = false;
#endif

static report_keyboard_t report0;
static report_keyboard_t report1;
report_keyboard_t *keyboard_report = &report0;
report_keyboard_t *keyboard_report_prev = &report1;

static inline void add_key_byte(uint8_t code);
static inline void add_key_bit(uint8_t code);


uint8_t host_keyboard_leds(void)
{
    return usb_keyboard_leds;
}

/* keyboard report operations */
void host_add_key(uint8_t key)
{
#ifdef USB_NKRO_ENABLE
    if (keyboard_nkro) {
        add_key_bit(key);
        return;
    }
#endif
    add_key_byte(key);
}

void host_add_mod_bit(uint8_t mod)
{
    keyboard_report->mods |= mod;
}

void host_set_mods(uint8_t mods)
{
    keyboard_report->mods = mods;
}

void host_add_code(uint8_t code)
{
    if (IS_MOD(code)) {
        host_add_mod_bit(MOD_BIT(code));
    } else {
        host_add_key(code);
    }
}

void host_swap_keyboard_report(void)
{
    uint8_t sreg = SREG;
    cli();
    report_keyboard_t *tmp = keyboard_report_prev;
    keyboard_report_prev = keyboard_report;
    keyboard_report = tmp;
    SREG = sreg;
}

void host_clear_keyboard_report(void)
{
    keyboard_report->mods = 0;
    for (int8_t i = 0; i < REPORT_KEYS; i++) {
        keyboard_report->keys[i] = 0;
    }
}

uint8_t host_has_anykey(void)
{
    uint8_t cnt = 0;
    for (int i = 0; i < REPORT_KEYS; i++) {
        if (keyboard_report->keys[i])
            cnt++;
    }
    return cnt;
}

uint8_t host_get_first_key(void)
{
#ifdef USB_NKRO_ENABLE
    if (keyboard_nkro) {
        uint8_t i = 0;
        for (; i < REPORT_KEYS && !keyboard_report->keys[i]; i++)
            ;
        return i<<3 | biton(keyboard_report->keys[i]);
    }
#endif
    return keyboard_report->keys[0];
}


void host_send_keyboard_report(void)
{
    usb_keyboard_send_report(keyboard_report);
}

#if defined(MOUSEKEY_ENABLE) || defined(PS2_MOUSE_ENABLE)
void host_mouse_send(report_mouse_t *report)
{
    usb_mouse_send(report->x, report->y, report->v, report->h, report->buttons);
}
#endif

#ifdef USB_EXTRA_ENABLE
void host_system_send(uint16_t data)
{
    usb_extra_system_send(data);
}

void host_consumer_send(uint16_t data)
{
    static uint16_t last_data = 0;
    if (data == last_data) return;
    last_data = data;

    usb_extra_consumer_send(data);
}
#endif


static inline void add_key_byte(uint8_t code)
{
    // TODO: fix ugly code
    int8_t i = 0;
    int8_t empty = -1;
    for (; i < REPORT_KEYS; i++) {
        if (keyboard_report_prev->keys[i] == code) {
            keyboard_report->keys[i] = code;
            break;
        }
        if (empty == -1 &&
                keyboard_report_prev->keys[i] == 0 &&
                keyboard_report->keys[i] == 0) {
            empty = i;
        }
    }
    if (i == REPORT_KEYS) {
        if (empty != -1) {
            keyboard_report->keys[empty] = code;
        }
    }
}

static inline void add_key_bit(uint8_t code)
{
    if ((code>>3) < REPORT_KEYS) {
        keyboard_report->keys[code>>3] |= 1<<(code&7);
    } else {
        debug("add_key_bit: can't add: "); phex(code); debug("\n");
    }
}
