// Bit-banged implementation without any use of interrupts.
// Data pin must have external 1K pull-up resistor.
// Operates data pin as open-collector output.

#include "adb_blargg.h"

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Copyright 2011 Jun WAKO <wakojun@gmail.com>
// Copyright 2013 Shay Green <gblargg@gmail.com>
// See bottom of file for license

typedef uint8_t byte;

// Make loop iteration take us total, including cyc overhead of loop logic
#define delay_loop_usec( us, cyc ) \
	__builtin_avr_delay_cycles( (unsigned long) (F_CPU / 1e6 * (us) + 0.5) - (cyc) )

#if !defined(ADB_PORT) || \
	!defined(ADB_PIN)  || \
	!defined(ADB_DDR)  || \
	!defined(ADB_DATA_BIT)
	#error
#endif

enum { data_mask = 1<<ADB_DATA_BIT };

enum { adb_cmd_read  = 0x2C };
enum { adb_cmd_write = 0x28 };

// gcc is very unreliable for inlining, so use macros
#define data_lo() (ADB_DDR |= data_mask)
#define data_hi() (ADB_DDR &= ~data_mask)
#define data_in() (ADB_PIN & data_mask)

static void place_bit( byte bit )
{
	// 100 us bit cell time
	data_lo();
	_delay_us( 35 );
	
	// Difference between a 0 and 1 bit is just this 30us portion in the middle
	if ( bit )
		data_hi();
	_delay_us( 30 );
	
	data_hi();
	_delay_us( 35 );
}

static void place_bit0( void ) { place_bit( 0 ); }
static void place_bit1( void ) { place_bit( 1 ); }

static void send_byte( byte data )
{
	for ( byte n = 8; n; n-- )
	{
		place_bit( data & 0x80 );
		data <<= 1;
	}
}

static void command( byte cmd )
{
	data_lo();
	_delay_us( 800 );
	place_bit1();
	send_byte( cmd );
	place_bit0();
}

void adb_host_init( void )
{
	// Always keep port output 0, then just toggle DDR to be GND or leave it floating (high).
	ADB_DDR	 &= ~data_mask;
	ADB_PORT &= ~data_mask;
	
	#ifdef ADB_PSW_BIT
		// Weak pull-up
		ADB_PORT |=  (1<<ADB_PSW_BIT);
		ADB_DDR  &= ~(1<<ADB_PSW_BIT);
	#endif
}

bool adb_host_psw( void )
{
	#ifdef ADB_PSW_BIT
		return (ADB_PIN & (1<<ADB_PSW_BIT)) != 0;
	#else
		return true;
	#endif
}

// Waits while data == val, or until us timeout expires. Returns remaining time,
// zero if timed out.
static byte while_data( byte us, byte data )
{
	while ( data_in() == data )
	{
		delay_loop_usec( 1 /* us period */, 7 /* cycles loop overhead */ );
		if ( !--us )
			break;
	}
	return us;
}

static byte while_lo( byte us ) { return while_data( us, 0 ); }
static byte while_hi( byte us ) { return while_data( us, data_mask ); }

static uint16_t adb_host_talk( byte cmd )
{
	command( cmd );
	_delay_us( 5 );
	if ( !while_hi( 260 - 5 ) ) // avg 160
		return adb_host_nothing;
	
	// Receive start bit and 16 data bits.
	// Doing them all in loop allows consistent error checking
	uint16_t data = 0;
	byte n = 17;
	do
	{
		data <<= 1;
		enum { timeout = 130 }; // maximum bit cell time
		
		byte lo = while_lo( timeout );
		if ( !lo )
			goto error; // timeout
		
		byte hi = while_hi( lo );
		if ( !hi )
			goto error; // timeout
		
		if ( timeout-lo < lo-hi )
			data |= 1;
		else if ( n == 17 )
			goto error; // start bit is wrong
	}
	while ( --n );
	
	// duration must be split in two due to 255 limit
	if ( !while_lo( 255 ) && !while_lo( 351 - 255 ) )
		goto error;
	
	if ( while_hi( 91 ) )
		goto error;
	
	return data;
	
error:
	return adb_host_error;
}

uint16_t adb_host_kbd_recv( void )
{
	return adb_host_talk( adb_cmd_read + 0 );
}

uint16_t adb_host_kbd_modifiers( void )
{
	return adb_host_talk( adb_cmd_read + 2 );
}

void adb_host_listen( byte cmd, byte data_h, byte data_l )
{
	command( cmd );
	_delay_us( 200 );
	
	place_bit1();
	send_byte( data_h ); 
	send_byte( data_l );
	place_bit0();
}

void adb_host_kbd_led( byte led )
{
	adb_host_listen( adb_cmd_write + 2, 0, led & 0x07 );
}

/* This software is licensed with a Modified BSD License.
All of this is supposed to be Free Software, Open Source, DFSG-free,
GPL-compatible, and OK to use in both free and proprietary applications.
Additions and corrections to this file are welcome.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

* Neither the name of the copyright holders nor the names of
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE. */
