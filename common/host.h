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

#ifndef HOST_H
#define HOST_H

#include <stdint.h>
#include "report.h"
#include "host_driver.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef NKRO_ENABLE
extern bool keyboard_nkro;
#endif

extern report_keyboard_t *keyboard_report;
extern report_keyboard_t *keyboard_report_prev;


void host_set_driver(host_driver_t *driver);
host_driver_t *host_get_driver(void);
uint8_t host_keyboard_leds(void);

/* new interface */
void host_register_key(uint8_t key);
void host_unregister_key(uint8_t key);

/* keyboard report operations */
void host_add_key(uint8_t key);
void host_del_key(uint8_t key);
void host_add_mod_bit(uint8_t mod);
void host_del_mod_bit(uint8_t mod);
void host_set_mods(uint8_t mods);
void host_add_code(uint8_t code);
void host_del_code(uint8_t code);
void host_swap_keyboard_report(void);
void host_clear_keyboard_report(void);
uint8_t host_has_anykey(void);
uint8_t host_get_first_key(void);


void host_send_keyboard_report(void);
void host_mouse_send(report_mouse_t *report);
void host_system_send(uint16_t data);
void host_consumer_send(uint16_t data);

#ifdef __cplusplus
}
#endif

#endif
