/*
Copyright 2018 Massdrop Inc.

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

#ifndef _D51_UTIL_H_
#define _D51_UTIL_H_

#include "samd51j18a.h"

//TODO: PS: Should bring these ports out to keyboard level configuration

//Debug LED PA27
#define led_ena REG_PORT_DIRSET0 = 0x08000000; //PA27 Output
#define led_on  REG_PORT_OUTSET0 = 0x08000000; //PA27 High
#define led_off REG_PORT_OUTCLR0 = 0x08000000; //PA27 Low

//Debug Port PB30
#define m15_ena REG_PORT_DIRSET1 = 0x40000000; //PB30 Output
#define m15_on  REG_PORT_OUTSET1 = 0x40000000; //PB30 High
#define m15_off REG_PORT_OUTCLR1 = 0x40000000; //PB30 Low

#define m15_loop(x) {uint8_t t=x; while(t--){m15_on;m15_off}}

#endif //_D51_UTIL_H_
