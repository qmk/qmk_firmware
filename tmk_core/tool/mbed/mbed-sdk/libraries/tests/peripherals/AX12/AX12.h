/* mbed AX-12+ Servo Library
 *
 * Copyright (c) 2010, cstyles (http://mbed.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MBED_AX12_H
#define MBED_AX12_H

#include "mbed.h"

#define AX12_WRITE_DEBUG 1
#define AX12_READ_DEBUG 1
#define AX12_TRIGGER_DEBUG 1
#define AX12_DEBUG 1

#define AX12_REG_ID 0x3
#define AX12_REG_BAUD 0x4
#define AX12_REG_CW_LIMIT 0x06
#define AX12_REG_CCW_LIMIT 0x08
#define AX12_REG_GOAL_POSITION 0x1E
#define AX12_REG_MOVING_SPEED 0x20
#define AX12_REG_VOLTS 0x2A
#define AX12_REG_TEMP 0x2B
#define AX12_REG_MOVING 0x2E
#define AX12_REG_POSITION 0x24

#define AX12_MODE_POSITION  0
#define AX12_MODE_ROTATION  1

#define AX12_CW 1
#define AX12_CCW 0

/** Servo control class, based on a PwmOut
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "AX12.h"
 *
 * int main() {
 *
 *   AX12 myax12 (p9, p10, 1);
 *
 *   while (1) {
 *       myax12.SetGoal(0);    // go to 0 degrees
 *       wait (2.0);
 *       myax12.SetGoal(300);  // go to 300 degrees
 *       wait (2.0);
 *   }
 * }
 * @endcode
 */
class AX12 {

public:

    /** Create an AX12 servo object connected to the specified serial port, with the specified ID
     *
     * @param pin tx pin
     * @param pin rx pin
     * @param int ID, the Bus ID of the servo 1-255
     */
    AX12(PinName tx, PinName rx, int ID, int baud=1000000);

    /** Set the mode of the servo
     * @param mode
     *    0 = Positional, default
     *    1 = Continuous rotation
     */
    int SetMode(int mode);

    /** Set baud rate of all attached servos
     * @param mode
     *    0x01 = 1,000,000 bps
     *    0x03 =   500,000 bps
     *    0x04 =   400,000 bps
     *    0x07 =   250,000 bps
     *    0x09 =   200,000 bps
     *    0x10 =   115,200 bps
     *    0x22 =    57,600 bps
     *    0x67 =    19,200 bps
     *    0xCF =     9,600 bp
     */
    int SetBaud(int baud);


    /** Set goal angle in integer degrees, in positional mode
     *
     * @param degrees 0-300
     * @param flags, defaults to 0
     *    flags[0] = blocking, return when goal position reached
     *    flags[1] = register, activate with a broadcast trigger
     *
     */
    int SetGoal(int degrees, int flags = 0);


    /** Set the speed of the servo in continuous rotation mode
     *
     * @param speed, -1.0 to 1.0
     *   -1.0 = full speed counter clock wise
     *    1.0 = full speed clock wise
     */
    int SetCRSpeed(float speed);


    /** Set the clockwise limit of the servo
     *
     * @param degrees, 0-300
     */
    int SetCWLimit(int degrees);

    /** Set the counter-clockwise limit of the servo
     *
     * @param degrees, 0-300
     */
    int SetCCWLimit(int degrees);

    // Change the ID

    /** Change the ID of a servo
     *
     * @param CurentID 1-255
     * @param NewID 1-255
     *
     * If a servo ID is not know, the broadcast address of 0 can be used for CurrentID.
     * In this situation, only one servo should be connected to the bus
     */
    int SetID(int CurrentID, int NewID);


    /** Poll to see if the servo is moving
     *
     * @returns true is the servo is moving
     */
    int isMoving(void);

    /** Send the broadcast "trigger" command, to activate any outstanding registered commands
     */
    void trigger(void);

    /** Read the current angle of the servo
     *
     * @returns float in the range 0.0-300.0
     */
    float GetPosition();

    /** Read the temperature of the servo
     *
     * @returns float temperature
     */
    float GetTemp(void);

    /** Read the supply voltage of the servo
     *
     * @returns float voltage
     */
    float GetVolts(void);

    int read(int ID, int start, int length, char* data);
    int write(int ID, int start, int length, char* data, int flag=0);

private :

    SerialHalfDuplex _ax12;
    int _ID;
    int _baud;


};

#endif
