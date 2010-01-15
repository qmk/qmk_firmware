#include "global-conf.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "clock-arch.h"

//Counted time
volatile clock_time_t clock_datetime = 0;

//Overflow interrupt
ISR(TIMER1_COMPA_vect)
{
	clock_datetime += 1;
}

//Initialise the clock
void clock_init()
{
	OCR1A  = ((F_CPU / 1024) / 100);
	TCCR1A = (1 << WGM12);
	TCCR1B = ((1 << CS12) | (1 << CS10));
	TIMSK1 = (1 << OCIE1A);
}

//Return time
clock_time_t clock_time()
{
	clock_time_t time;

	cli();
		time = clock_datetime;
	sei();

	return time;
}
