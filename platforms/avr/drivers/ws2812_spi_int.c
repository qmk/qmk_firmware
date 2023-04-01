/*
 * (C) 2023 Raster Software Vigo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

/* This is an interrupt-driven SPI driver for the
 * WS2812/SK6812 RGB leds, for the ATmega32U.
 *
 * It sets SPI to 8MHz and sends 11100000 for a zero
 * and 11111110 for a one. The time used by the ISR
 * to prepare the next bit ensures the timming after
 * each bit.
 *
 * It requires a 16MHz CPU clock and the pins PB1 and PB3
 * unused (they are part of the ISP interface, so it's not
 * uncommon), and the leds connected to the PB2 pin. Also,
 * it can manage a maximum of 85 leds.
 *
 * It uses 40 bytes more than the WS2812 driver, but being interrupt
 * based, allows to multiplex the LEDs with other tasks.
 */

#include <avr/interrupt.h>
#include "rgblight.h"

uint8_t *led_data;
uint8_t  nbytes;
uint8_t  remaining_bits;

void ws2812_setleds(LED_TYPE *ledarray, uint16_t leds) {
    led_data       = (uint8_t *)ledarray;
    nbytes         = 3 * leds;
    remaining_bits = 8;
    // Initialize SPI for the WS2812/SK6812 driver
    // Set PB2 and PB0 as output (not doing it freezes the SPI)
    DDRB |= (1 << PB2);
    DDRB |= (1 << PB0);
    // Enable SPI, Master, set clock rate fck/2, MODE1, and enable interrupts
    SPSR = (1 << SPI2X);
    SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << CPHA);
    SPDR = 0; // send a byte to trigger an interrupt and begin the process
}

ISR(SPI_STC_vect, ISR_NAKED) {                //                                    "naked" ISR; we have to preserve any register that we use.
    asm volatile("        push r25\n\t"       //                                    Using assembly code is better to reduce the duration of the ISR to the bare minimum.
                 "        in   r25, 0x3F\n\t" //                                    preserve the SREG status register
                 "        push r25\n\t"
                 "        push r24\n\t" //                                          preserve r24 and r25
                 "        push r30\n\t"
                 "        push r31\n\t" //                                          preserve Z (r30/r31)
                 "        lds  r30, led_data\n\t"
                 "        lds  r31, led_data+1\n\t"     // uint8_t *Z = led_data;   read the address of the byte to send
                 "        ld   r24, Z\n\t"              // if (*Z & 0x80)           read the byte to send
                 "        ldi  r25, 0xE0\n\t"           //     r25 = 0xE0;          11100000 -> zero bit (375ns up)
                 "        sbrc r24, 7\n\t"              // else
                 "        ldi  r25, 0xFE\n\t"           //     r25 = 0xFE;          11111110 -> one bit (875ns up)
                 "        add  r24, r24\n\t"            // *Z <<= 2;                rotate the current byte one bit to the left
                 "        st   Z+, r24\n\t"             // Z++;                     store it in memory and point to the next byte (the incremented value won't be
                 "        lds  r24, remaining_bits\n\t" //                          stored unless there are no more bits, so this saves one instruction)
                 "        subi r24, 1\n\t"              // remaining_bits--;
                 "        breq no_more_bits\n\t"        // if remaining_bits == 0   are there more bits to send?
                 "        sts  remaining_bits, r24\n\t" //     goto no_more_bits    yes -> store the new number of bits and continue
                 "exit_isr:\n\t"
                 "        pop  r31\n\t" //                                          restore the registers
                 "        pop  r30\n\t"
                 "        pop  r24\n\t"
                 "        out  0x2E, r25\n\t" //           SPDR = r25               and at the very last moment, send the new bit. That way, the main code will
                 "        pop  r25\n\t"       //                                    have the maximum possible time to do other things before the next interrupt.
                 "        out  0x3F, r25\n\t"
                 "        pop  r25\n\t"
                 "        reti\n\t"
                 "no_more_bits:\n\t"
                 "        ldi  r24, 8\n\t"              //                          no more bits to send from the current byte; so we will send 8 more
                 "        sts  remaining_bits, r24\n\t" // remaining_bits = 8;
                 "        sts  led_data, r30\n\t"       // led_data = Z;            store the pointer to the next byte
                 "        sts  led_data+1, r31\n\t"     //                          (it was incremented previously, so we save one instruction)
                 "        lds  r24, nbytes\n\t"
                 "        subi r24, 1\n\t"
                 "        sts  nbytes, r24\n\t" //         nbytes--;                one byte less to send
                 "        brne exit_isr\n\t"    //         if nbytes == 0           if there are more bytes to send, just exit the ISR
                 "        in   r24, 0x2C\n\t"   //             goto exit_isr
                 "        andi r24, 0x7F\n\t"
                 "        out  0x2C, r24\n\t" //           SPCR &= ~(1<<SPIE)       but if there aren't more, disable the interrupts
                 "        rjmp exit_isr\n\t");
}
