#ifndef REV1_H
#define REV1_H

#include "../orthodox.h"

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