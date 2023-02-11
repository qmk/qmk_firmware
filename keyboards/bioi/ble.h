/*
Copyright 2019 Basic I/O Instruments(Scott Wei) <scot.wei@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdbool.h>
#include "host_driver.h"
#include "host.h"


typedef union {
  uint32_t raw;
  struct {
    bool init : 1;
  };
} keyboard_config_t;

extern keyboard_config_t ble_config;

extern host_driver_t bluefruit_driver;
extern host_driver_t null_driver;

void send_str(const char *str);
void usart_init(void);
void module_reset(void);
