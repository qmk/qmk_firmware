/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bootloader.h"


void bootloader_jump(void) {
    cli();
    // This makes custom USBasploader come up.
    MCUSR = 0;

    // ATmega168PA
    // initialize ports
    PORTB = 0; PORTC= 0; PORTD = 0;
    DDRB = 0; DDRC= 0; DDRD = 0;

    // disable interrupts
    EIMSK = 0; EECR = 0; SPCR = 0;
    ACSR = 0; SPMCSR = 0; WDTCSR = 0; PCICR = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0;
    ADCSRA = 0; TWCR = 0; UCSR0B = 0;
    
    // Boot Loader Section Start Address:
    // BOOTSZ       Size        Address
    // (lock bit)   (word)      (word)      (byte)
    // '11'         128         0x1F80      0x3F00
    // '10'         256         0x1F00      0x3E00
    // '01'         512         0x1E00      0x3C00
    // '00'         1024        0x1C00      0x3800
    asm volatile("jmp 0x3800");
}
