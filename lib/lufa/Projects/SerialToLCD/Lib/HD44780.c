/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2012  Simon Foster (simon.foster [at] inbox [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "HD44780.h"

static void HD44780_WriteNibble(const uint8_t nib)
{
	/* Read PORTD and clear the ENABLE and PD0..3 bits
	   then OR in the data */

	PORTD = (PORTD & ~(ENABLE | LO4_MASK)) | (nib & LO4_MASK);

	/* Enforce address setup time (tAS) 60ns
	   60 @ 16MHz = <1
	   Let's us a few NOPs for good measure */
	asm volatile("nop\n\t"
	             "nop\n\t"
	             :: );

	/* Take enable high and enforce Enable High time (tEH=450ns)
	   450ns @ 16MHz = 7.2 => 7 NOPs */

	PORTD |= ENABLE;

	asm volatile("nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             :: );

	/* Take enable low and enforce Enable Low time (tEL=500ns)
	   500ns @ 16MHz = 8.0 => 7 NOPs */
	PORTD &= ~ENABLE;

	asm volatile("nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             "nop\n\t"
	             :: );
}

static void HD44780_WriteByte(const uint8_t c)
{
	HD44780_WriteNibble(HI4(c));
	HD44780_WriteNibble(LO4(c));
}

static void HD44780_PowerUp4Bit(void)
{
	/* Wait for more than 40 ms after VCC rises to 2.7 V */
	_delay_ms(40);
	HD44780_WriteNibble(0x03);        // FN_SET 8-bit

	/* Wait for more than 4.1 ms */
	_delay_ms(5);
	HD44780_WriteNibble(0x03);        // FN_SET 8-bit

	/* Wait for more than 100 µs */
	_delay_us(100);
	HD44780_WriteNibble(0x03);        // FN_SET 8-bit

	/* From now on we must allow 40us for each command */
	_delay_us(50);
	HD44780_WriteNibble(0x02);        // FN_SET 4-bit

	/* The LCD is now in 4-bit mode so we can continue
	   using the 4-bit API */
	_delay_us(50);
}

void HD44780_Initialize(void)
{
	PORTD &= ~ALL_BITS;
	DDRD  |=  ALL_BITS;
	HD44780_PowerUp4Bit();
}

void HD44780_WriteCommand(const uint8_t c)
{
	PORTD &= ~RS;
	HD44780_WriteByte(c);
	_delay_us(50);
}

void HD44780_WriteData(const uint8_t c)
{
	PORTD |=  RS;
	HD44780_WriteByte(c);
	PORTD &= ~RS;
	_delay_us(50);
}
