#pragma once
#include QMK_KEYBOARD_H
//#include "ms_sculpt_mobile.h"
//	#define LAYOUT(k00) {{ k00 }}

#ifdef BOARD_GENERIC_STM32_F103
#define LED_ON()    do { palClearPad(GPIOC, 13) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOC, 13); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOC, 13); } while (0)
#endif