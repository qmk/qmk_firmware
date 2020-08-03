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

#ifndef IWRAP_H
#define IWRAP_H

#include <stdint.h>
#include <stdbool.h>
#include "host_driver.h"

/* enable iWRAP MUX mode */
#define MUX_MODE

host_driver_t *iwrap_driver(void);

void iwrap_init(void);
void iwrap_send(const char *s);
void iwrap_mux_send(const char *s);
void iwrap_buf_send(void);
void iwrap_buf_add(uint8_t c);
void iwrap_buf_del(void);

void    iwrap_call(void);
void    iwrap_kill(void);
void    iwrap_unpair(void);
void    iwrap_sleep(void);
void    iwrap_sniff(void);
void    iwrap_subrate(void);
bool    iwrap_failed(void);
uint8_t iwrap_connected(void);
uint8_t iwrap_check_connection(void);

#endif
