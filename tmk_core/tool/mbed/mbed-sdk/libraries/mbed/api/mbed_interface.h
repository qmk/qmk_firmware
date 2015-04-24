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
#ifndef MBED_INTERFACE_H
#define MBED_INTERFACE_H

#include "device.h"

/* Mbed interface mac address
 * if MBED_MAC_ADD_x are zero, interface uid sets mac address,
 * otherwise MAC_ADD_x are used.
 */
#define MBED_MAC_ADDR_INTERFACE 0x00
#define MBED_MAC_ADDR_0  MBED_MAC_ADDR_INTERFACE
#define MBED_MAC_ADDR_1  MBED_MAC_ADDR_INTERFACE
#define MBED_MAC_ADDR_2  MBED_MAC_ADDR_INTERFACE
#define MBED_MAC_ADDR_3  MBED_MAC_ADDR_INTERFACE
#define MBED_MAC_ADDR_4  MBED_MAC_ADDR_INTERFACE
#define MBED_MAC_ADDR_5  MBED_MAC_ADDR_INTERFACE
#define MBED_MAC_ADDRESS_SUM (MBED_MAC_ADDR_0 | MBED_MAC_ADDR_1 | MBED_MAC_ADDR_2 | MBED_MAC_ADDR_3 | MBED_MAC_ADDR_4 | MBED_MAC_ADDR_5)

#ifdef __cplusplus
extern "C" {
#endif

#if DEVICE_SEMIHOST

/** Functions to control the mbed interface
 *
 * mbed Microcontrollers have a built-in interface to provide functionality such as
 * drag-n-drop download, reset, serial-over-usb, and access to the mbed local file
 * system. These functions provide means to control the interface suing semihost
 * calls it supports.
 */

/** Determine whether the mbed interface is connected, based on whether debug is enabled
 *
 *  @returns
 *    1 if interface is connected,
 *    0 otherwise
 */
int mbed_interface_connected(void);

/** Instruct the mbed interface to reset, as if the reset button had been pressed
 *
 *  @returns
 *    1 if successful,
 *    0 otherwise (e.g. interface not present)
 */
int mbed_interface_reset(void);

/** This will disconnect the debug aspect of the interface, so semihosting will be disabled.
 * The interface will still support the USB serial aspect
 *
 *  @returns
 *    0 if successful,
 *   -1 otherwise (e.g. interface not present)
 */
int mbed_interface_disconnect(void);

/** This will disconnect the debug aspect of the interface, and if the USB cable is not
 * connected, also power down the interface. If the USB cable is connected, the interface
 * will remain powered up and visible to the host
 *
 *  @returns
 *    0 if successful,
 *   -1 otherwise (e.g. interface not present)
 */
int mbed_interface_powerdown(void);

/** This returns a string containing the 32-character UID of the mbed interface
 *  This is a weak function that can be overwritten if required
 *
 *  @param uid A 33-byte array to write the null terminated 32-byte string
 *
 *  @returns
 *    0 if successful,
 *   -1 otherwise (e.g. interface not present)
 */
int mbed_interface_uid(char *uid);

#endif

/** This returns a unique 6-byte MAC address, based on the interface UID
 * If the interface is not present, it returns a default fixed MAC address (00:02:F7:F0:00:00)
 *
 * This is a weak function that can be overwritten if you want to provide your own mechanism to
 * provide a MAC address.
 *
 *  @param mac A 6-byte array to write the MAC address
 */
void mbed_mac_address(char *mac);

/** Cause the mbed to flash the BLOD (Blue LEDs Of Death) sequence
 */
void mbed_die(void);

#ifdef __cplusplus
}
#endif

#endif
