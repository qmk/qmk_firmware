#ifndef KINESIS_H
#define KINESIS_H

#ifdef KEYBOARD_kinesis_alvicstep
	#include "alvicstep.h"
#endif
#ifdef KEYBOARD_kinesis_stapelberg
	#include "stapelberg.h"
#endif
#ifdef KEYBOARD_kinesis_kint2pp
	#include "kint2pp.h"
#endif
#ifdef KEYBOARD_kinesis_nguyenvietyen
	#include "nguyenvietyen.h"
#endif

#include "quantum.h"


void all_led_off(void);
void all_led_on(void);
void num_lock_led_on(void);
void caps_lock_led_on(void);
void scroll_lock_led_on(void);
void keypad_led_on(void);



#endif
