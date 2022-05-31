/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bootloader.h"

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

__attribute__((weak)) void bootloader_jump(void) {
    // http://www.pjrc.com/teensy/jump_to_bootloader.html

    cli();
    // disable watchdog, if enabled (it's not)
    // disable all peripherals
    // a shutdown call might make sense here
    UDCON  = 1;
    USBCON = (1 << FRZCLK); // disable USB
    UCSR1B = 0;
    _delay_ms(5);

#if defined(__AVR_AT90USB162__) // Teensy 1.0
    EIMSK  = 0;
    PCICR  = 0;
    SPCR   = 0;
    ACSR   = 0;
    EECR   = 0;
    TIMSK0 = 0;
    TIMSK1 = 0;
    UCSR1B = 0;
    DDRB   = 0;
    DDRC   = 0;
    DDRD   = 0;
    PORTB  = 0;
    PORTC  = 0;
    PORTD  = 0;
    asm volatile("jmp 0x3E00");
#elif defined(__AVR_ATmega32U4__)  // Teensy 2.0
    EIMSK  = 0;
    PCICR  = 0;
    SPCR   = 0;
    ACSR   = 0;
    EECR   = 0;
    ADCSRA = 0;
    TIMSK0 = 0;
    TIMSK1 = 0;
    TIMSK3 = 0;
    TIMSK4 = 0;
    UCSR1B = 0;
    TWCR   = 0;
    DDRB   = 0;
    DDRC   = 0;
    DDRD   = 0;
    DDRE   = 0;
    DDRF   = 0;
    TWCR   = 0;
    PORTB  = 0;
    PORTC  = 0;
    PORTD  = 0;
    PORTE  = 0;
    PORTF  = 0;
    asm volatile("jmp 0x7E00");
#elif defined(__AVR_AT90USB646__)  // Teensy++ 1.0
    EIMSK  = 0;
    PCICR  = 0;
    SPCR   = 0;
    ACSR   = 0;
    EECR   = 0;
    ADCSRA = 0;
    TIMSK0 = 0;
    TIMSK1 = 0;
    TIMSK2 = 0;
    TIMSK3 = 0;
    UCSR1B = 0;
    TWCR   = 0;
    DDRA   = 0;
    DDRB   = 0;
    DDRC   = 0;
    DDRD   = 0;
    DDRE   = 0;
    DDRF   = 0;
    PORTA  = 0;
    PORTB  = 0;
    PORTC  = 0;
    PORTD  = 0;
    PORTE  = 0;
    PORTF  = 0;
    asm volatile("jmp 0xFC00");
#elif defined(__AVR_AT90USB1286__) // Teensy++ 2.0
    EIMSK  = 0;
    PCICR  = 0;
    SPCR   = 0;
    ACSR   = 0;
    EECR   = 0;
    ADCSRA = 0;
    TIMSK0 = 0;
    TIMSK1 = 0;
    TIMSK2 = 0;
    TIMSK3 = 0;
    UCSR1B = 0;
    TWCR   = 0;
    DDRA   = 0;
    DDRB   = 0;
    DDRC   = 0;
    DDRD   = 0;
    DDRE   = 0;
    DDRF   = 0;
    PORTA  = 0;
    PORTB  = 0;
    PORTC  = 0;
    PORTD  = 0;
    PORTE  = 0;
    PORTF  = 0;
    asm volatile("jmp 0x1FC00");
#endif
}

__attribute__((weak)) void mcu_reset(void) {
    // setup watchdog timeout
    wdt_enable(WDTO_60MS);

    // wait for watchdog timer to trigger
    while (1) {
    }
}
