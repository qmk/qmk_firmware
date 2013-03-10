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

#ifndef EECONFIG_H
#define EECONFIG_H

#include <stdint.h>

#define EECONFIG_MAGIC_NUMBER                   (uint16_t)0xFEED

/* eeprom parameteter address */
#define EECONFIG_MAGIC                          (uint16_t *)0
#define EECONFIG_DEBUG                          (uint8_t *)2
#define EECONFIG_DEFAULT_LAYER                  (uint8_t *)3
#define EECONFIG_KEYCONF                        (uint8_t *)4
#define EECONFIG_MOUSEKEY_ACCEL                 (uint8_t *)5


/* debug bit */
#define EECONFIG_DEBUG_ENABLE                   (1<<0)
#define EECONFIG_DEBUG_MATRIX                   (1<<1)
#define EECONFIG_DEBUG_KEYBOARD                 (1<<2)
#define EECONFIG_DEBUG_MOUSE                    (1<<3)

/* keyconf bit */
#define EECONFIG_KEYCONF_SWAP_CONTROL_CAPSLOCK     (1<<0)
#define EECONFIG_KEYCONF_CAPSLOCK_TO_CONTROL       (1<<1)
#define EECONFIG_KEYCONF_SWAP_LALT_LGUI            (1<<2)
#define EECONFIG_KEYCONF_SWAP_RALT_RGUI            (1<<3)
#define EECONFIG_KEYCONF_NO_GUI                    (1<<4)
#define EECONFIG_KEYCONF_SWAP_GRAVE_ESC            (1<<5)
#define EECONFIG_KEYCONF_SWAP_BACKSLASH_BACKSPACE  (1<<6)


/* XXX: Not portable. Bit field order depends on implementation */
typedef union {
    uint8_t raw;
    struct {
        bool swap_control_capslock:1;
        bool capslock_to_control:1;
        bool swap_lalt_lgui:1;
        bool swap_ralt_rgui:1;
        bool no_gui:1;
        bool swap_grave_esc:1;
        bool swap_backslash_backspace:1;
        bool reserved:1;
    };
} keyconf;

bool eeconfig_initialized(void);

void eeconfig_init(void);

uint8_t eeconfig_read_debug(void);
void eeconfig_write_debug(uint8_t val);

uint8_t eeconfig_read_defalt_layer(void);
void eeconfig_write_defalt_layer(uint8_t val);

uint8_t eeconfig_read_keyconf(void);
void eeconfig_write_keyconf(uint8_t val);

#endif
