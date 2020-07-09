/*
 * APA102 lib V1.0a
 *
 * Controls APA102 RGB-LEDs
 * Author: Mikkel (Duckle29 on GitHub)
 *
 * Dec 22th, 2017  v1.0a Initial Version
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

#include "apa102.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

// Setleds for standard RGB
void inline apa102_setleds(LED_TYPE *ledarray, uint16_t leds) { apa102_setleds_pin(ledarray, leds, _BV(RGB_DI_PIN & 0xF), _BV(RGB_CLK_PIN & 0xF)); }

void static inline apa102_setleds_pin(LED_TYPE *ledarray, uint16_t leds, uint8_t pinmask_DI, uint8_t pinmask_CLK) {
    setPinOutput(RGB_DI_PIN);
    setPinOutput(RGB_CLK_PIN);

    apa102_send_array((uint8_t *)ledarray, leds)
}

void apa102_send_array(uint8_t *data, uint16_t leds) {  // Data is struct of 3 bytes. RGB - leds is number of leds in data
    apa102_start_frame();
    while (leds--) {
        apa102_send_frame(0xFF000000 | (data->b << 16) | (data->g << 8) | data->r);
        data++;
    }
    apa102_end_frame(leds);
}

void apa102_send_frame(uint32_t frame) {
    for (uint32_t i = 0xFF; i > 0;) {
        apa102_send_byte(frame & i);
        i = i << 8;
    }
}

void apa102_start_frame() { apa102_send_frame(0); }

void apa102_end_frame(uint16_t leds) {
    // This function has been taken from: https://github.com/pololu/apa102-arduino/blob/master/APA102.h
    // and adapted. The code is MIT licensed. I think thats compatible?

    // We need to send some more bytes to ensure that all the LEDs in the
    // chain see their new color and start displaying it.
    //
    // The data stream seen by the last LED in the chain will be delayed by
    // (count - 1) clock edges, because each LED before it inverts the clock
    // line and delays the data by one clock edge.  Therefore, to make sure
    // the last LED actually receives the data we wrote, the number of extra
    // edges we send at the end of the frame must be at least (count - 1).
    // For the APA102C, that is sufficient.
    //
    // The SK9822 only updates after it sees 32 zero bits followed by one more
    // rising edge.  To avoid having the update time depend on the color of
    // the last LED, we send a dummy 0xFF byte.  (Unfortunately, this means
    // that partial updates of the beginning of an LED strip are not possible;
    // the LED after the last one you are trying to update will be black.)
    // After that, to ensure that the last LED in the chain sees 32 zero bits
    // and a rising edge, we need to send at least 65 + (count - 1) edges.  It
    // is sufficent and simpler to just send (5 + count/16) bytes of zeros.
    //
    // We are ignoring the specification for the end frame in the APA102/SK9822
    // datasheets because it does not actually ensure that all the LEDs will
    // start displaying their new colors right away.

    apa102_send_byte(0xFF);
    for (uint16_t i = 0; i < 5 + leds / 16; i++) {
        apa102_send_byte(0);
    }
}

void apa102_send_byte(uint8_t byte) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        writePin(RGB_DI_PIN, !!(byte & (1 << (7 - i))));
        writePinHigh(RGB_CLK_PIN);
    }
}
