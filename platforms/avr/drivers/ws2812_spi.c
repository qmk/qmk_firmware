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

/* This is a SPI driver for the SK6812/WS2812 RGB leds,
 * for the ATmega32U.
 *
 * It sets SPI to 8MHz and sends 11100000 for a zero,
 * or 11111110 for a one. The extra time to prepare the
 * next bit ensures the timming after each bit.
 *
 * It requires a 16MHz CPU clock, the pins PB1 and PB3
 * unused (they are part of the ISP interface, so it's not
 * uncommon), PB0 as output, and the leds connected to the
 * PB2 pin. Also, it can manage a maximum of 85 leds.
 *
 * It uses 36 bytes less than the WS2812 driver.
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include "gpio.h"
#include "ws2812.h"

#if F_CPU != 16000000L
#    error "The SPI WS2812 driver supports only the 16 MHz CPU clock"
#endif

void ws2812_setleds(LED_TYPE *ledarray, uint8_t leds) {
    // Initialize SPI for the WS2812/SK6812 driver
    // Disable interrupts, preserving the old state
    uint8_t sreg_prev = SREG;
    cli();
    // Set PB0 and PB2 as output (not doing it freezes the SPI)
    setPinOutput(B2);
    setPinOutput(B0);
    // Enable SPI, Master, set clock rate fck/2, MODE1
    SPSR = 1 << SPI2X;
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << CPHA);
    asm volatile("            mov  r24, %0\n\t"
                 "            add  r24, r24\n\t"  // r24 = leds * 2
                 "            add   %0, r24\n\t"  // %0 = leds * 3
                 "loop_byte:  ld   r24, Z+\n\t"   // r24 contains the byte to send to the led
                 "            ldi  r25, 8\n\t"    // 8 bits to send
                 "loop_bits:  ldi  r26, 0xE0\n\t" // 11100000 -> zero bit (375ns up)
                 "            sbrc r24, 7\n\t"
                 "            ldi  r26, 0xFE\n\t" // 11111110 -> one bit (875ns up)
                 "            out  0x2E, r26\n\t" // out SPDR, r26; begin the SPI transfer
                 "            add  r24, r24\n\t"  // rotate data one bit to the left
                 "wait_ready: in   r27, 0x2D\n\t" // in r27, SPSR
                 "            andi r27, 0x80\n\t" // check SPIF to know if the transfer is complete.
                 "            breq wait_ready\n\t"
                 "            subi r25, 1\n\t" // are there more bits to send in this byte?
                 "            brne loop_bits\n\t"
                 "            subi  %0, 1\n\t"
                 "            brne loop_byte\n\t"
                 :
                 : "a"(leds), "z"(ledarray));
    // restore interrupts previous state
    SREG = sreg_prev;
    _delay_us(WS2812_TRST_US);
}
