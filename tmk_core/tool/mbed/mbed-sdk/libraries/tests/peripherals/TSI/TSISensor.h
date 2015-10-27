/* Freescale Semiconductor Inc.
 * (c) Copyright 2004-2005 Freescale Semiconductor, Inc.
 * (c) Copyright 2001-2004 Motorola, Inc.
 *
 * mbed Microcontroller Library
 * (c) Copyright 2009-2012 ARM Limited.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef TSISENSOR_H
#define TSISENSOR_H

/**
* TSISensor example
*
* @code
* #include "mbed.h"
* #include "TSISensor.h"
*
* int main(void) {
*    DigitalOut led(LED_GREEN);
*    TSISensor tsi;
*
*    while (true) {
*        printf("slider percentage: %f%\r\n", tsi.readPercentage());
*        printf("slider distance: %dmm\r\n", tsi.readDistance());
*        wait(1);
*        led = !led;
*    }
* }
* @endcode
*/
class TSISensor {
public:
    /**
     *   Initialize the TSI Touch Sensor
     */
    TSISensor();

    /**
     * Read Touch Sensor percentage value
     *
     * @returns percentage value between [0 ... 1]
     */
    float readPercentage();

    /**
     * Read Touch Sensor distance
     *
     * @returns distance in mm. The value is between [0 ... 40]
     */
    uint8_t readDistance();

private:
    void sliderRead(void);
    void selfCalibration(void);
};

#endif
