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
#include <stdio.h>
#include "mbed_interface.h"

#include "gpio_api.h"
#include "wait_api.h"
#include "semihost_api.h"
#include "mbed_error.h"
#include "toolchain.h"

#if DEVICE_SEMIHOST

// return true if a debugger is attached, indicating mbed interface is connected
int mbed_interface_connected(void) {
    return semihost_connected();
}

int mbed_interface_reset(void) {
    if (mbed_interface_connected()) {
        semihost_reset();
        return 0;
    } else {
        return -1;
    }
}

WEAK int mbed_interface_uid(char *uid) {
    if (mbed_interface_connected()) {
        return semihost_uid(uid); // Returns 0 if successful, -1 on failure
    } else {
        uid[0] = 0;
        return -1;
    }
}

int mbed_interface_disconnect(void) {
    int res;
    if (mbed_interface_connected()) {
        if ((res = semihost_disabledebug()) != 0)
            return res;
        while (mbed_interface_connected());
        return 0;
    } else {
        return -1;
    }
}

int mbed_interface_powerdown(void) {
    int res;
    if (mbed_interface_connected()) {
        if ((res = semihost_powerdown()) != 0)
            return res;
        while (mbed_interface_connected());
        return 0;
    } else {
        return -1;
    }
}

// for backward compatibility
void mbed_reset(void) {
    mbed_interface_reset();
}

WEAK int mbed_uid(char *uid) {
    return mbed_interface_uid(uid);
}
#endif

WEAK void mbed_mac_address(char *mac) {
#if DEVICE_SEMIHOST
    char uid[DEVICE_ID_LENGTH + 1];
    int i;

    // if we have a UID, extract the MAC
    if (mbed_interface_uid(uid) == 0) {
        char *p = uid;
#if defined(DEVICE_MAC_OFFSET)
        p += DEVICE_MAC_OFFSET;
#endif
        for (i=0; i<6; i++) {
            int byte;
            sscanf(p, "%2x", &byte);
            mac[i] = byte;
            p += 2;
        }
        mac[0] &= ~0x01;    // reset the IG bit in the address; see IEE 802.3-2002, Section 3.2.3(b)
    } else {  // else return a default MAC
#endif
        mac[0] = 0x00;
        mac[1] = 0x02;
        mac[2] = 0xF7;
        mac[3] = 0xF0;
        mac[4] = 0x00;
        mac[5] = 0x00;
#if DEVICE_SEMIHOST
    }
#endif
}
