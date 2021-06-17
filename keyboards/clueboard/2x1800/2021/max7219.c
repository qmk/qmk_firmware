/*
 * Copyright (c) 2021 Zach White <skullydazed@gmail.com>
 * Copyright (c) 2007 Eberhard Fahle
 *
 *    max7219.c - A library for controling Leds with a MAX7219/MAX7221
 *
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 *
 *    This permission notice shall be included in all copies or
 *    substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * This driver is a port of Arduino's LedControl to QMK. The original
 * Arduino code can be found here:
 *
 * https://github.com/wayoda/LedControl
 *
 * Unlike LedControl we are using the native SPI support, you will need to
 * use the native SPI pins for your MCU. You can set the CS pin with
 * `#define MAX7219_LOAD <pin>`.
 */

#include "max7219.h"

/* Write max7219_spidata to all the max7219's
 */
void max7219_write_all(void) {
    if (spi_start(MAX7219_LOAD, false, 0, 8)) {
        for(int i = MAX_BYTES; i>0; i--) {
            dprintf("spi_write(%d)\n", max7219_spidata[i-1]);
            spi_write(max7219_spidata[i-1]);
        }
        spi_stop();
    } else {
        xprintf("Could not spi_start!\n");
    }
}

/* Write data to a single max7219
 */
void max7219_write(int device_num, volatile uint8_t opcode, volatile uint8_t data) {
    dprintf("max7219_write(%d, %d, %d)\n", device_num, opcode, data);

    // Clear the data array
    for(int i = MAX_BYTES; i>0; i--) {
        max7219_spidata[i-1]=0;
    }

    // Set our opcode and data
    uint8_t offset = device_num*2;
    max7219_spidata[offset] = data;
    max7219_spidata[offset+1] = opcode;

    // Write the data
    max7219_write_all();
}

/* Turn off all the LEDs
 */
void max7219_clear_display(int device_num) {
    dprintf("max7219_clear_display(%d);\n", device_num);

    if (device_num<0 || device_num >= MAX7219_CONTROLLERS) {
        return;
    }

    int offset = device_num * 8;

    for(int i = 0; i<8; i++) {
        max7219_led_a[offset+i] = 0;
        max7219_write(device_num, i+1, max7219_led_a[offset+i]);
    }
}

/* Enable the display test (IE turn on all 64 LEDs)
 */
void max7219_display_test(int device_num, bool enabled) {
    dprintf("max7219_display_test(%d, %d);\n", device_num, enabled);

    if (device_num<0 || device_num >= MAX7219_CONTROLLERS) {
        return;
    }

    max7219_write(device_num, OP_DISPLAYTEST, enabled);
}

/* Initialize the max7219 system and set the controller(s) to a default state.
 */
void max7219_init(void) {
    wait_ms(1500);
    dprintf("max7219_init()\n");

    //setPinOutput(MAX7219_DATA);
    //setPinOutput(MAX7219_CLK);
    setPinOutput(MAX7219_LOAD);
    writePinHigh(MAX7219_LOAD);
    spi_init();

    //for (int i=0; i<MAX7219_CONTROLLERS; i++) {
    //    max7219_shutdown(i, true);
    //}

    for (int i=0; i<MAX7219_CONTROLLERS; i++) {
        // Reset everything to defaults and enable the display
        max7219_display_test(i, false);
        max7219_set_scan_limit(i, 7);
        max7219_set_decode_mode(i, 0);
        max7219_clear_display(i);
        max7219_set_intensity(i, LED_INTENSITY);
        max7219_shutdown(i, true);
    }

    for (int i=0; i<MAX7219_CONTROLLERS; i++) {
        // Test this display
        max7219_display_test(i, true);
        wait_ms(75);
        max7219_display_test(i, false);
    }

#ifdef MAX7219_LED_TEST
    while(1) {
        for (int i=0; i<MAX7219_CONTROLLERS; i++) {
            max7219_display_test(i, true);
            wait_ms(500);
            max7219_display_test(i, false);
        }
    }
#endif

#ifdef MAX7219_LED_ITERATE
    while (1) {
        for(int col=0;col<8;col++) {
            for (int i=0; i<MAX7219_CONTROLLERS; i++) {
                for (int row=0; row<8; row++) {
                    max7219_set_led(i, row, col, true);
                    wait_ms(500);
                    max7219_set_led(i, row, col, false);
                }
            }
        }
    }
#endif
}

/* Set the decode mode of the controller. You probably don't want to change this.
 */
void max7219_set_decode_mode(int device_num, int mode) {
    dprintf("max7219_set_decode_mode(%d, %d);\n", device_num, mode);

    if (device_num<0 || device_num >= MAX7219_CONTROLLERS) {
        return;
    }

    max7219_write(device_num, OP_DECODEMODE, mode);
}

/* Set the intensity (brightness) for the LEDs.
 */
void max7219_set_intensity(int device_num, int intensity) {
    dprintf("max7219_set_intensity(%d, %d);\n", device_num, intensity);

    if (device_num<0 || device_num >= MAX7219_CONTROLLERS) {
        return;
    }

    if (intensity >= 0 && intensity<16) {
            max7219_write(device_num, OP_INTENSITY, intensity);
    }
}

/* Control a single LED.
 */
void max7219_set_led(int device_num, int row, int column, bool state) {
    dprintf("max7219_set_led(%d, %d, %d, %d);\n", device_num, row, column, state);

    int offset;
    uint8_t val = 0x00;

    if (device_num<0 || device_num >= MAX7219_CONTROLLERS) {
        xprintf("max7219_set_led: device_num out of bounds: %d\n", device_num);
        return;
    }

    if (column<0 || column>7) {
        xprintf("max7219_set_led: column (%d) out of bounds\n", column);
        return;
    }

    if (row<0 || row>7) {
        xprintf("max7219_set_led: row (%d) out of bounds\n", row);
        return;
    }

    offset = device_num*8;
    val = 0b10000000 >> column;

    if (state) {
        max7219_led_a[offset+row] = max7219_led_a[offset+row]|val;
    } else {
        val = ~val;
        max7219_led_a[offset+row] = max7219_led_a[offset+row]&val;
    }
    max7219_write(device_num, row+1, max7219_led_a[offset+row]);
}

/* Set a whole row of LEDs.
 */
void max7219_set_row(int device_num, int row, unsigned char value) {
    dprintf("max7219_set_row(%d, %d, %x);\n", device_num, row, value);
}

/* Set a whole column of LEDs.
 */
void max7219_set_col(int device_num, int col, unsigned char value) {
    dprintf("max7219_set_col(%d, %d, %x);\n", device_num, col, value);
}

/* Set the number of digits (rows) to be scanned.
 */
void max7219_set_scan_limit(int device_num, int limit) {
    dprintf("max7219_set_scan_limit(%d, %d);\n", device_num, limit);

    if (device_num<0 || device_num >= MAX7219_CONTROLLERS) {
        return;
    }

    if (limit >= 0 && limit < 8) {
        max7219_write(device_num, OP_SCANLIMIT, limit);
    }
}

/* Enable or disable the controller.
 */
void max7219_shutdown(int device_num, bool is_in_shutdown) {
    dprintf("max7219_shutdown(%d, %d);\n", device_num, is_in_shutdown);

    if (device_num<0 || device_num >= MAX7219_CONTROLLERS) {
        return;
    }

    max7219_write(device_num, OP_SHUTDOWN, is_in_shutdown);
}
