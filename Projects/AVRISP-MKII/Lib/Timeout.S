#include <avr/io.h>
#include "V2Protocol.h"

.global TIMER0_COMPA_vect
TIMER0_COMPA_vect:
	sei
	push	r24
	in	r24, 0x3f
	push	r24

	in	r24, TimeoutMSRemaining
	and	r24, r24
	breq	Epilogue
	subi	r24, 0x01
	out	TimeoutMSRemaining, r24

Epilogue:
	pop	r24
	out	0x3f, r24
	pop	r24
	reti	
	
	