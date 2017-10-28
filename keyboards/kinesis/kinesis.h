#ifndef KINESIS_H
#define KINESIS_H

#ifdef SUBPROJECT_alvicstep
	#include "alvicstep.h"
#endif
#ifdef SUBPROJECT_stapelberg
	#include "stapelberg.h"
#endif

#include "quantum.h"


void all_led_off(void);
void all_led_on(void);
void num_lock_led_on(void);
void caps_lock_led_on(void);
void scroll_lock_led_on(void);
void keypad_led_on(void);



#endif
