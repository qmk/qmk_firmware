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
ISR(TIMER0_OVF_vect)
{
	clock_datetime += 1;
}

//Initialise the clock
void clock_init()
{
	//Activate overflow interrupt for timer0
	TIMSK0 |= (1<<TOIE0);

	//Use prescaler 1024
	TCCR0B |= ((1<<CS12)|(1<<CS10));

	//Activate interrupts
	sei();
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
