/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_I2C_SLAVE_H
#define MBED_I2C_SLAVE_H

#include "platform.h"

#if DEVICE_I2CSLAVE

#include "i2c_api.h"

namespace mbed {

/** An I2C Slave, used for communicating with an I2C Master device
 *
 * Example:
 * @code
 * // Simple I2C responder
 * #include <mbed.h>
 *
 * I2CSlave slave(p9, p10);
 *
 * int main() {
 *     char buf[10];
 *     char msg[] = "Slave!";
 *
 *     slave.address(0xA0);
 *     while (1) {
 *         int i = slave.receive();
 *         switch (i) {
 *             case I2CSlave::ReadAddressed:
 *                 slave.write(msg, strlen(msg) + 1); // Includes null char
 *                 break;
 *             case I2CSlave::WriteGeneral:
 *                 slave.read(buf, 10);
 *                 printf("Read G: %s\n", buf);
 *                 break;
 *             case I2CSlave::WriteAddressed:
 *                 slave.read(buf, 10);
 *                 printf("Read A: %s\n", buf);
 *                 break;
 *         }
 *         for(int i = 0; i < 10; i++) buf[i] = 0;    // Clear buffer
 *     }
 * }
 * @endcode
 */
class I2CSlave {

public:
    enum RxStatus {
        NoData         = 0,
        ReadAddressed  = 1,
        WriteGeneral   = 2,
        WriteAddressed = 3
    };

    /** Create an I2C Slave interface, connected to the specified pins.
     *
     *  @param sda I2C data line pin
     *  @param scl I2C clock line pin
     */
    I2CSlave(PinName sda, PinName scl);

    /** Set the frequency of the I2C interface
     *
     *  @param hz The bus frequency in hertz
     */
    void frequency(int hz);

    /** Checks to see if this I2C Slave has been addressed.
     *
     *  @returns
     *  A status indicating if the device has been addressed, and how
     *  - NoData            - the slave has not been addressed
     *  - ReadAddressed     - the master has requested a read from this slave
     *  - WriteAddressed    - the master is writing to this slave
     *  - WriteGeneral      - the master is writing to all slave
     */
    int receive(void);

    /** Read from an I2C master.
     *
     *  @param data pointer to the byte array to read data in to
     *  @param length maximum number of bytes to read
     *
     *  @returns
     *       0 on success,
     *   non-0 otherwise
     */
    int read(char *data, int length);

    /** Read a single byte from an I2C master.
     *
     *  @returns
     *    the byte read
     */
    int read(void);

    /** Write to an I2C master.
     *
     *  @param data pointer to the byte array to be transmitted
     *  @param length the number of bytes to transmite
     *
     *  @returns
     *       0 on success,
     *   non-0 otherwise
     */
    int write(const char *data, int length);

    /** Write a single byte to an I2C master.
     *
     *  @data the byte to write
     *
     *  @returns
     *    '1' if an ACK was received,
     *    '0' otherwise
     */
    int write(int data);

    /** Sets the I2C slave address.
     *
     *  @param address The address to set for the slave (ignoring the least
     *  signifcant bit). If set to 0, the slave will only respond to the
     *  general call address.
     */
    void address(int address);

    /** Reset the I2C slave back into the known ready receiving state.
     */
    void stop(void);

protected:
    i2c_t _i2c;
};

} // namespace mbed

#endif

#endif
