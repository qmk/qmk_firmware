/*
Copyright 2021 Thomas Weißschuh <thomas@t-8ch.de>

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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "report.h"

void     programmable_button_clear(void);
void     programmable_button_send(void);
void     programmable_button_on(uint8_t index);
void     programmable_button_off(uint8_t index);
bool     programmable_button_is_on(uint8_t index);
uint32_t programmable_button_get_report(void);
void     programmable_button_set_report(uint32_t report);
