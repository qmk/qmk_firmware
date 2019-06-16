#ifndef REV1_H
#define REV1_H

#include "../adron_pad.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

//void promicro_bootloader_jmp(bool program);

#define LAYOUT( \
	K00, \
    K01, \
    K02  \
	) \
	{ \
		{ K00, KC_NO, KC_NO }, \
		{ KC_NO, K01, KC_NO }, \
		{ KC_NO, KC_NO, K02 }, \
	}

#endif