#pragma once

#ifdef KEYBOARD_handwired_dactyl_manuform_4x5
    #include "4x5.h"
#elif KEYBOARD_handwired_dactyl_manuform_4x6
    #include "4x6.h"
#elif KEYBOARD_handwired_dactyl_manuform_5x6
    #include "5x6.h"
#elif KEYBOARD_handwired_dactyl_manuform_5x7
    #include "5x7.h"
#elif KEYBOARD_handwired_dactyl_manuform_6x6
    #include "6x6.h"
#elif KEYBOARD_handwired_dactyl_manuform_dmote_62key
    #include "62key.h"
#endif

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif
