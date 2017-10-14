/*
This is the header file for the subproject

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger

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

#ifndef REV1_H
#define REV1_H

#include "orthodox.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

//void promicro_bootloader_jmp(bool program);

#define KEYMAP( \
	L00, L01, L02, L03, L04, L05,                     		  R00, R01, R02, R03, R04, R05, \
	L10, L11, L12, L13, L14, L15, L16, L17,	L18, R10, R11, R12, R13, R14, R15, R16, R17, R18,  \
	L20, L21, L22, L23, L24, L25, L26, L27, L28, R20, R21, R22, R23, R24, R25, R26, R27, R28 \
	) \
	{ \
		{ L00, L01, L02, L03, L04, L05 }, \
		{ L10, L11, L12, L13, L14, L15, L16, L17, L18}, \
		{ L20, L21, L22, L23, L24, L25, L26, L27, L28 }, \
		{ R05, R04, R03, R02, R01, R00 }, \
		{ R18, R17, R16, R15, R14, R13, R12, R11, R10 }, \
		{ R28, R27, R26, R25, R24, R23, R22, R21, R20 } \
	}

#endif