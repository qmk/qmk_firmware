/* Copyright 2020 Dimitris Papavasiliou <dpapavas@protonmail.ch>
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <spi_master.h>

#include "quantum.h"
#include "split_util.h"
#include "timer.h"

#include "lagrange.h"

struct led_context {
    led_t led_state;
    layer_state_t layer_state;
};

uint8_t transceive(uint8_t b) {
    for (SPDR = b ; !(SPSR & _BV(SPIF)) ; );
    return SPDR;
}

/* The SPI bus, doens't have any form of protocol built in, so when
 * the other side isn't present, any old noise on the line will appear
 * as matrix data.  To avoid interpreting data as keystrokes, we do a
 * simple n-way (8-way here) handshake before each scan, where each
 * side sends a prearranged sequence of bytes. */

void shake_hands(bool master) {
    const uint8_t m = master ? 0xf8 : 0;
    const uint8_t a = 0xa8 ^ m, b = 0x50 ^ m;

    uint8_t i;

    i = SPSR;
    i = SPDR;

    do {
        /* Cylcling the SS pin on each attempt is necessary, as it
         * resets the AVR's SPI core and guarantees proper
         * alignment. */

        if (master) {
            writePinLow(SPI_SS_PIN);
        }

        for (i = 0 ; i < 8 ; i += 1) {
            if (transceive(a + i) != b + i) {
                break;
            }
        }

        if (master) {
            writePinHigh(SPI_SS_PIN);
        }
    } while (i < 8);
}

bool transport_master(matrix_row_t matrix[]) {
    const struct led_context context = {
        host_keyboard_led_state(),
        layer_state
    };

    uint8_t i;

    /* Shake hands and then receive the matrix from the other side,
     * while transmitting LED and layer states. */

    shake_hands(true);

    spi_start(SPI_SS_PIN, 0, 0, 4);

    for (i = 0 ; i < sizeof(matrix_row_t[MATRIX_ROWS / 2]) ; i += 1) {
        spi_status_t x;

        x = spi_write(i < sizeof(struct led_context) ?
                      ((uint8_t *)&context)[i] : 0);

        if (x == SPI_STATUS_TIMEOUT) {
            return false;
        }

        ((uint8_t *)matrix)[i] = (uint8_t)x;
    }

    spi_stop();

    return true;
}

void transport_slave(matrix_row_t matrix[]) {
    static struct led_context context;
    struct led_context new_context;

    uint8_t i;

    /* Do the reverse of master above.  Note that timing is critical,
     * so interrupts must be turned off. */

    cli();
    shake_hands(false);

    for (i = 0 ; i < sizeof(matrix_row_t[MATRIX_ROWS / 2]) ; i += 1) {
        uint8_t b;

        b = transceive(((uint8_t *)matrix)[i]);

        if (i < sizeof(struct led_context)) {
            ((uint8_t *)&new_context)[i] = b;
        }
    }

    sei();

    /* Update the layer and LED state if necessary. */

    if (!isLeftHand) {
        if (context.led_state.raw != new_context.led_state.raw) {
            context.led_state.raw = new_context.led_state.raw;
            led_update_kb(context.led_state);
        }

        if (context.layer_state != new_context.layer_state) {
            context.layer_state = new_context.layer_state;
            layer_state_set_kb(context.layer_state);
        }
    }
}

void transport_master_init(void) {
    /* We need to set the SS pin as output as the handshake logic
     * above depends on it and the SPI master driver won't do it
     * before we call spi_start(). */

    writePinHigh(SPI_SS_PIN);
    setPinOutput(SPI_SS_PIN);

    spi_init();

    shake_hands(true);
}

void transport_slave_init(void) {
    /* The datasheet isn't very clear on whether the internal pull-up
     * is selectable when the SS pin is used by the SPI slave, but
     * experimentations shows that it is, at least on the ATMega32u4.
     * We enable the pull-up to guard against the case where both
     * halves end up as slaves.  In that case the SS pin would
     * otherwise be floating and free to fluctuate due to picked up
     * noise, etc. When reading low it would make both halves think
     * they're asserted making the MISO pin an output on both ends and
     * leading to potential shorts. */

    setPinInputHigh(SPI_SS_PIN);
    setPinInput(SPI_SCK_PIN);
    setPinInput(SPI_MOSI_PIN);
    setPinOutput(SPI_MISO_PIN);

    SPCR = _BV(SPE);

    shake_hands(false);
}
