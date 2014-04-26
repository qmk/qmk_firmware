/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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
#include "host.h"
#include "report.h"
#include "debug.h"
#include "action_util.h"
#include "timer.h"

static inline void add_key_byte(uint8_t code);
static inline void del_key_byte(uint8_t code);
#ifdef NKRO_ENABLE
static inline void add_key_bit(uint8_t code);
static inline void del_key_bit(uint8_t code);
#endif

static uint8_t real_mods = 0;
static uint8_t weak_mods = 0;


// TODO: pointer variable is not needed
//report_keyboard_t keyboard_report = {};
report_keyboard_t *keyboard_report = &(report_keyboard_t){};

#ifndef NO_ACTION_ONESHOT
static int8_t oneshot_mods = 0;
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
static int16_t oneshot_time = 0;
#endif
#endif


void send_keyboard_report(void) {
    keyboard_report->mods  = real_mods;
    keyboard_report->mods |= weak_mods;
#ifndef NO_ACTION_ONESHOT
    if (oneshot_mods) {
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        if (TIMER_DIFF_16(timer_read(), oneshot_time) >= ONESHOT_TIMEOUT) {
            dprintf("Oneshot: timeout\n");
            clear_oneshot_mods();
        }
#endif
        keyboard_report->mods |= oneshot_mods;
        if (has_anykey()) {
            clear_oneshot_mods();
        }
    }
#endif
    host_keyboard_send(keyboard_report);
}

/* key */
void add_key(uint8_t key)
{
#ifdef NKRO_ENABLE
    if (keyboard_nkro) {
        add_key_bit(key);
        return;
    }
#endif
    add_key_byte(key);
}

void del_key(uint8_t key)
{
#ifdef NKRO_ENABLE
    if (keyboard_nkro) {
        del_key_bit(key);
        return;
    }
#endif
    del_key_byte(key);
}

void clear_keys(void)
{
    // not clear mods
    for (int8_t i = 1; i < REPORT_SIZE; i++) {
        keyboard_report->raw[i] = 0;
    }
}


/* modifier */
uint8_t get_mods(void) { return real_mods; }
void add_mods(uint8_t mods) { real_mods |= mods; }
void del_mods(uint8_t mods) { real_mods &= ~mods; }
void set_mods(uint8_t mods) { real_mods = mods; }
void clear_mods(void) { real_mods = 0; }

/* weak modifier */
uint8_t get_weak_mods(void) { return weak_mods; }
void add_weak_mods(uint8_t mods) { weak_mods |= mods; }
void del_weak_mods(uint8_t mods) { weak_mods &= ~mods; }
void set_weak_mods(uint8_t mods) { weak_mods = mods; }
void clear_weak_mods(void) { weak_mods = 0; }

/* Oneshot modifier */
#ifndef NO_ACTION_ONESHOT
void set_oneshot_mods(uint8_t mods)
{
    oneshot_mods = mods;
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_time = timer_read();
#endif
}
void clear_oneshot_mods(void)
{
    oneshot_mods = 0;
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_time = 0;
#endif
}
#endif




/*
 * inspect keyboard state
 */
uint8_t has_anykey(void)
{
    uint8_t cnt = 0;
    for (uint8_t i = 1; i < REPORT_SIZE; i++) {
        if (keyboard_report->raw[i])
            cnt++;
    }
    return cnt;
}

uint8_t has_anymod(void)
{
    return bitpop(real_mods);
}

uint8_t get_first_key(void)
{
#ifdef NKRO_ENABLE
    if (keyboard_nkro) {
        uint8_t i = 0;
        for (; i < REPORT_BITS && !keyboard_report->nkro.bits[i]; i++)
            ;
        return i<<3 | biton(keyboard_report->nkro.bits[i]);
    }
#endif
    return keyboard_report->keys[0];
}



/* local functions */
static inline void add_key_byte(uint8_t code)
{
    int8_t i = 0;
    int8_t empty = -1;
    for (; i < REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            break;
        }
        if (empty == -1 && keyboard_report->keys[i] == 0) {
            empty = i;
        }
    }
    if (i == REPORT_KEYS) {
        if (empty != -1) {
            keyboard_report->keys[empty] = code;
        }
    }
}

static inline void del_key_byte(uint8_t code)
{
    for (uint8_t i = 0; i < REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            keyboard_report->keys[i] = 0;
        }
    }
}

#ifdef NKRO_ENABLE
static inline void add_key_bit(uint8_t code)
{
    if ((code>>3) < REPORT_BITS) {
        keyboard_report->nkro.bits[code>>3] |= 1<<(code&7);
    } else {
        dprintf("add_key_bit: can't add: %02X\n", code);
    }
}

static inline void del_key_bit(uint8_t code)
{
    if ((code>>3) < REPORT_BITS) {
        keyboard_report->nkro.bits[code>>3] &= ~(1<<(code&7));
    } else {
        dprintf("del_key_bit: can't del: %02X\n", code);
    }
}
#endif
