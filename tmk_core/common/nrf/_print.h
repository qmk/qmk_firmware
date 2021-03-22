/*
Copyright 2021 Sekigon

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
#include "nrf/printf.h"

#define print(s) tfp_printf(s)
#define println(s) tfp_printf(s "\r\n")
#define xprintf tfp_printf
#define uprint(s) tfp_printf(s)
#define uprintln(s) tfp_printf(s "\r\n")
#define uprintf tfp_printf
