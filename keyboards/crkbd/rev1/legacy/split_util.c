/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "wait.h"

#ifdef EE_HANDS
#    include "eeconfig.h"
#endif

#ifdef USE_MATRIX_I2C
#  include "i2c_master.h"
#else
#  include "split_scomm.h"
#endif

#ifndef SPLIT_USB_TIMEOUT
#    define SPLIT_USB_TIMEOUT 2000
#endif

#ifndef SPLIT_USB_TIMEOUT_POLL
#    define SPLIT_USB_TIMEOUT_POLL 10
#endif

volatile bool isLeftHand = true;

bool waitForUsb(void) {
    for (uint8_t i = 0; i < (SPLIT_USB_TIMEOUT / SPLIT_USB_TIMEOUT_POLL); i++) {
        // This will return true if a USB connection has been established
        if (UDADDR & _BV(ADDEN)) {
            return true;
        }
        wait_ms(SPLIT_USB_TIMEOUT_POLL);
    }

    // Avoid NO_USB_STARTUP_CHECK - Disable USB as the previous checks seem to enable it somehow
    (USBCON &= ~(_BV(USBE) | _BV(OTGPADE)));

    return false;
}

__attribute__((weak)) bool is_keyboard_left(void) {
#if defined(SPLIT_HAND_PIN)
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
    setPinInput(SPLIT_HAND_PIN);
    return readPin(SPLIT_HAND_PIN);
#elif defined(EE_HANDS)
    return eeconfig_read_handedness();
#elif defined(MASTER_RIGHT)
    return !has_usb();
#endif

    return has_usb();
}

__attribute__((weak)) bool has_usb(void) {
    static enum { UNKNOWN, MASTER, SLAVE } usbstate = UNKNOWN;

    // only check once, as this is called often
    if (usbstate == UNKNOWN) {
#if defined(SPLIT_USB_DETECT)
        usbstate = waitForUsb() ? MASTER : SLAVE;
#elif defined(__AVR__)
        USBCON |= (1 << OTGPADE);  // enables VBUS pad
        wait_us(5);

        usbstate = (USBSTA & (1 << VBUS)) ? MASTER : SLAVE;  // checks state of VBUS
#else
        usbstate = MASTER;
#endif
    }

    return (usbstate == MASTER);
}

static void keyboard_master_setup(void) {

#ifdef USE_MATRIX_I2C
    i2c_init();
#else
    serial_master_init();
#endif
}

static void keyboard_slave_setup(void) {

#ifdef USE_MATRIX_I2C
    i2c_slave_init(SLAVE_I2C_ADDRESS);
#else
    serial_slave_init();
#endif
}

// this code runs before the usb and keyboard is initialized
void split_keyboard_setup(void) {
    isLeftHand = is_keyboard_left();

   if (has_usb()) {
      keyboard_master_setup();
   } else {
      keyboard_slave_setup();
   }
   sei();
}
