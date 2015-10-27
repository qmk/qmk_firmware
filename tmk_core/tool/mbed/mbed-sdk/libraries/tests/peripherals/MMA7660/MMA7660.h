/* Copyright (c) <year> <copyright holders>, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
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

#include "mbed.h"


#ifndef MMA7660_H
#define MMA7660_H

#define MMA7660_ADDRESS     0x98
#define MMA7660_SENSITIVITY 21.33

#define MMA7660_XOUT_R      0x00
#define MMA7660_YOUT_R      0x01
#define MMA7660_ZOUT_R      0x02
#define MMA7660_TILT_R      0x03
#define MMA7660_INT_R       0x06
#define MMA7660_MODE_R      0x07
#define MMA7660_SR_R        0x08


/** An interface for the MMA7660 triple axis accelerometer
 *
 * @code
 * //Uses the measured z-acceleration to drive leds 2 and 3 of the mbed
 *
 * #include "mbed.h"
 * #include "MMA7660.h"
 *
 * MMA7660 MMA(p28, p27);
 *
 * DigitalOut connectionLed(LED1);
 * PwmOut Zaxis_p(LED2);
 * PwmOut Zaxis_n(LED3);
 *
 * int main() {
 *     if (MMA.testConnection())
 *         connectionLed = 1;
 *
 *     while(1) {
 *         Zaxis_p = MMA.z();
 *         Zaxis_n = -MMA.z();
 *     }
 *
 * }
 * @endcode
 */
class MMA7660
{
public:
    /**
    * The 6 different orientations and unknown
    *
    * Up & Down = X-axis
    * Right & Left = Y-axis
    * Back & Front = Z-axis
    *
    */
    enum Orientation {Up, Down,
                      Right, Left,
                      Back, Front,
                      Unknown
                     };

    /**
    * Creates a new MMA7660 object
    *
    * @param sda - I2C data pin
    * @param scl - I2C clock pin
    * @param active - true (default) to enable the device, false to keep it standby
    */
    MMA7660(PinName sda, PinName scl, bool active = true);

    /**
    * Tests if communication is possible with the MMA7660
    *
    * Because the MMA7660 lacks a WHO_AM_I register, this function can only check
    * if there is an I2C device that responds to the MMA7660 address
    *
    * @param return - true for successfull connection, false for no connection
    */
    bool testConnection( void );

    /**
    * Sets the active state of the MMA7660
    *
    * Note: This is unrelated to awake/sleep mode
    *
    * @param state - true for active, false for standby
    */
    void setActive( bool state);

    /**
    * Reads acceleration data from the sensor
    *
    * When the parameter is a pointer to an integer array it will be the raw data.
    * When it is a pointer to a float array it will be the acceleration in g's
    *
    * @param data - pointer to array with length 3 where the acceleration data will be stored, X-Y-Z
    */
    void readData( int *data);
    void readData( float *data);

    /**
    * Get X-data
    *
    * @param return - X-acceleration in g's
    */
    float x( void );

    /**
    * Get Y-data
    *
    * @param return - Y-acceleration in g's
    */
    float y( void );

    /**
    * Get Z-data
    *
    * @param return - Z-acceleration in g's
    */
    float z( void );

    /**
    * Sets the active samplerate
    *
    * The entered samplerate will be rounded to nearest supported samplerate.
    * Supported samplerates are: 120 - 64 - 32 - 16 - 8 - 4 - 2 - 1 samples/second.
    *
    * @param samplerate - the samplerate that will be set
    */
    void setSampleRate(int samplerate);

    /**
    * Returns if it is on its front, back, or unknown side
    *
    * This is read from MMA7760s registers, page 12 of datasheet
    *
    * @param return - Front, Back or Unknown orientation
    */
    Orientation getSide( void );

    /**
    * Returns if it is on it left, right, down or up side
    *
    * This is read from MMA7760s registers, page 12 of datasheet
    *
    * @param return - Left, Right, Down, Up or Unknown orientation
    */
    Orientation getOrientation ( void );


private:

    /**
    * Writes data to the device
    *
    * @param adress - register address to write to
    * @param data - data to write
    */
    void write( char address, char data);

    /**
    * Read data from the device
    *
    * @param adress - register address to write to
    * @return - data from the register specified by RA
    */
    char read( char adress);

    /**
     * Read multiple regigsters from the device, more efficient than using multiple normal reads.
     *
     * @param adress - register address to write to
     * @param length - number of bytes to read
     * @param data - pointer where the data needs to be written to
     */
    void read( char adress, char *data, int length);

    /**
    * Reads single axis
    */
    float getSingle(int number);

    I2C _i2c;
    bool active;
    float samplerate;
};


#endif
