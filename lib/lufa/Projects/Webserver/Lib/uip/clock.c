#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <LUFA/Common/Common.h>

#include "clock.h"

//Counted time
volatile clock_time_t clock_datetime = 0;

//Overflow interrupt
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	clock_datetime += 1;
}

//Initialise the clock
void clock_init()
{
	OCR1A  = (((F_CPU / 1024) / 100) - 1);
	TCCR1B = ((1 << WGM12) | (1 << CS12) | (1 << CS10));
	TIMSK1 = (1 << OCIE1A);
}

//Return time
clock_time_t clock_time()
{
	clock_time_t time;

	GlobalInterruptDisable();
	time = clock_datetime;
	GlobalInterruptEnable();

	return time;
}

