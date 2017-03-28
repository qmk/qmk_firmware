#ifndef REV2_H
#define REV2_H

#include "../lets_split.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#ifdef SSD1306OLED
extern bool iota_gfx_init(void);
extern void iota_gfx_task(void);
extern bool iota_gfx_off(void);
extern bool iota_gfx_on(void);
extern void iota_gfx_flush(void);
extern void iota_gfx_write_char(uint8_t c);
extern void iota_gfx_write(const char *data);
extern void iota_gfx_write_P(const char *data);
extern void iota_gfx_clear_screen(void);
#endif
#endif

//void promicro_bootloader_jmp(bool program);

#ifndef FLIP_HALF
//Standard Keymap
#define KEYMAP( \
	k40, k41, k42, k43, k44, k45, k05, k04, k03, k02, k01, k00, \
	k50, k51, k52, k53, k54, k55, k15, k14, k13, k12, k11, k10, \
	k60, k61, k62, k63, k64, k65, k25, k24, k23, k22, k21, k20, \
	k70, k71, k72, k73, k74, k75, k35, k34, k33, k32, k31, k30 \
	) \
	{ \
		{ k45, k44, k43, k42, k41, k40 }, \
		{ k55, k54, k53, k52, k51, k50 }, \
		{ k65, k64, k63, k62, k61, k60 }, \
		{ k75, k74, k73, k72, k71, k70 }, \
		{ k00, k01, k02, k03, k04, k05 }, \
		{ k10, k11, k12, k13, k14, k15 }, \
		{ k20, k21, k22, k23, k24, k25 }, \
		{ k30, k31, k32, k33, k34, k35 } \
	}

#else
// Keymap with one side flipped
#define KEYMAP( \
	k00, k01, k02, k03, k04, k05, k40, k41, k42, k43, k44, k45, \
	k10, k11, k12, k13, k14, k15, k50, k51, k52, k53, k54, k55, \
	k20, k21, k22, k23, k24, k25, k60, k61, k62, k63, k64, k65, \
	k30, k31, k32, k33, k34, k35, k70, k71, k72, k73, k74, k75 \
	) \
	{ \
		{ k00, k01, k02, k03, k04, k05 }, \
		{ k10, k11, k12, k13, k14, k15 }, \
		{ k20, k21, k22, k23, k24, k25 }, \
		{ k30, k31, k32, k33, k34, k35 }, \
		{ k45, k44, k43, k42, k41, k40 }, \
		{ k55, k54, k53, k52, k51, k50 }, \
		{ k65, k64, k63, k62, k61, k60 }, \
		{ k75, k74, k73, k72, k71, k70 } \
	}
#endif


#endif