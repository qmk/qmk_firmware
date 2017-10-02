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
#include "action_layer.h"
#include "timer.h"
#include "keycode_config.h"

extern keymap_config_t keymap_config;


static uint8_t real_mods = 0;
static uint8_t weak_mods = 0;
static uint8_t macro_mods = 0;

#ifdef USB_6KRO_ENABLE
#define RO_ADD(a, b) ((a + b) % KEYBOARD_REPORT_KEYS)
#define RO_SUB(a, b) ((a - b + KEYBOARD_REPORT_KEYS) % KEYBOARD_REPORT_KEYS)
#define RO_INC(a) RO_ADD(a, 1)
#define RO_DEC(a) RO_SUB(a, 1)
static int8_t cb_head = 0;
static int8_t cb_tail = 0;
static int8_t cb_count = 0;
#endif

// TODO: pointer variable is not needed
//report_keyboard_t keyboard_report = {};
report_keyboard_t *keyboard_report = &(report_keyboard_t){};

extern inline void add_key(uint8_t key);
extern inline void del_key(uint8_t key);
extern inline void clear_keys(void);

#ifndef NO_ACTION_ONESHOT
static int8_t oneshot_mods = 0;
static int8_t oneshot_locked_mods = 0;
int8_t get_oneshot_locked_mods(void) { return oneshot_locked_mods; }
void set_oneshot_locked_mods(int8_t mods) { oneshot_locked_mods = mods; }
void clear_oneshot_locked_mods(void) { oneshot_locked_mods = 0; }
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
static int16_t oneshot_time = 0;
bool has_oneshot_mods_timed_out(void) {
  return TIMER_DIFF_16(timer_read(), oneshot_time) >= ONESHOT_TIMEOUT;
}
#else
bool has_oneshot_mods_timed_out(void) {
    return false;
}
#endif
#endif

/* oneshot layer */
#ifndef NO_ACTION_ONESHOT
/* oneshot_layer_data bits
* LLLL LSSS
* where:
*   L => are layer bits
*   S => oneshot state bits
*/
static int8_t oneshot_layer_data = 0;

inline uint8_t get_oneshot_layer(void) { return oneshot_layer_data >> 3; }
inline uint8_t get_oneshot_layer_state(void) { return oneshot_layer_data & 0b111; }

#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
static int16_t oneshot_layer_time = 0;
inline bool has_oneshot_layer_timed_out() {
    return TIMER_DIFF_16(timer_read(), oneshot_layer_time) >= ONESHOT_TIMEOUT &&
        !(get_oneshot_layer_state() & ONESHOT_TOGGLED);
}
#endif

/* Oneshot layer */
void set_oneshot_layer(uint8_t layer, uint8_t state)
{
    oneshot_layer_data = layer << 3 | state;
    layer_on(layer);
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = timer_read();
#endif
}
void reset_oneshot_layer(void) {
    oneshot_layer_data = 0;
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = 0;
#endif
}
void clear_oneshot_layer_state(oneshot_fullfillment_t state)
{
    uint8_t start_state = oneshot_layer_data;
    oneshot_layer_data &= ~state;
    if (!get_oneshot_layer_state() && start_state != oneshot_layer_data) {
        layer_off(get_oneshot_layer());
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = 0;
#endif
    }
}
bool is_oneshot_layer_active(void)
{
    return get_oneshot_layer_state();
}
#endif

void send_keyboard_report(void) {
    keyboard_report->mods  = real_mods;
    keyboard_report->mods |= weak_mods;
    keyboard_report->mods |= macro_mods;
#ifndef NO_ACTION_ONESHOT
    if (oneshot_mods) {
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        if (has_oneshot_mods_timed_out()) {
            dprintf("Oneshot: timeout\n");
            clear_oneshot_mods();
        }
#endif
        keyboard_report->mods |= oneshot_mods;
        if (has_anykey(keyboard_report)) {
            clear_oneshot_mods();
        }
    }

#endif
    host_keyboard_send(keyboard_report);
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

/* macro modifier */
uint8_t get_macro_mods(void) { return macro_mods; }
void add_macro_mods(uint8_t mods) { macro_mods |= mods; }
void del_macro_mods(uint8_t mods) { macro_mods &= ~mods; }
void set_macro_mods(uint8_t mods) { macro_mods = mods; }
void clear_macro_mods(void) { macro_mods = 0; }

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
uint8_t get_oneshot_mods(void)
{
    return oneshot_mods;
}
#endif

/*
 * inspect keyboard state
 */
uint8_t has_anymod(void)
{
    return bitpop(real_mods);
}
