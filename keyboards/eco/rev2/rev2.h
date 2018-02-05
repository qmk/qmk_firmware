#ifndef REV2_H
#define REV2_H

#include "../eco.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

//void promicro_bootloader_jmp(bool program);

#define KEYMAP( \
	k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, k011, k012, k013, k014, \
	k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113, k114, \
	k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212, k213, k214, \
	k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312, k313, k314  \
	) \
	{ \
		{ k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, k011, k012, k013, k014 }, \
		{ k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113, k114 }, \
		{ k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212, k213, k214 }, \
		{ k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312, k313, k314 }  \
	}

#endif