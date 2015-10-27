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
#include "gpio_api.h"
#include "wait_api.h"
#include "C027_api.h"

static gpio_t mdmEn, mdmLvlOe, mdmILvlOe, mdmUsbDet;
static gpio_t gpsEn;

void c027_init(void) {
    gpio_t led, mdmRts, mdmRst, gpsRst, mdmPwrOn;
    // start with modem disabled 
    gpio_init_out_ex(&mdmEn,     MDMEN,     0);
    gpio_init_out_ex(&mdmRst,    MDMRST,    1);
    gpio_init_out_ex(&mdmPwrOn,  MDMPWRON,  1);
    gpio_init_out_ex(&mdmLvlOe,  MDMLVLOE,  1); // LVLEN:  1=disabled
    gpio_init_out_ex(&mdmILvlOe, MDMILVLOE, 0); // ILVLEN: 0=disabled
    gpio_init_out_ex(&mdmUsbDet, MDMUSBDET, 0);
    gpio_init_out_ex(&mdmRts,    MDMRTS,    0);
    // start with gps disabled 
    gpio_init_out_ex(&gpsEn,     GPSEN,     0);
    gpio_init_out_ex(&gpsRst,    GPSRST,    1);
    // led should be off
    gpio_init_out_ex(&led,       LED,       0);
    
    wait_ms(50); // when USB cable is inserted the interface chip issues 
}

void c027_mdm_powerOn(int usb) {
    // turn on the mode by enabling power with power on pin low and correct USB detect level
    gpio_write(&mdmUsbDet, usb ? 1 : 0);  // USBDET: 0=disabled, 1=enabled
    if (!gpio_read(&mdmEn)) { // enable modem
        gpio_write(&mdmEn, 1);        // LDOEN:  1=on
        wait_ms(1);                   // wait until supply switched off
        // now we can safely enable the level shifters
        gpio_write(&mdmLvlOe, 0);      // LVLEN:  0=enabled (uart/gpio)
        if (gpio_read(&gpsEn)) 
            gpio_write(&mdmILvlOe, 1); // ILVLEN: 1=enabled (i2c)
    }
}

void c027_mdm_powerOff(void) {
    if (gpio_read(&mdmEn)) {
        // diable all level shifters
        gpio_write(&mdmILvlOe, 0);  // ILVLEN: 0=disabled (i2c)
        gpio_write(&mdmLvlOe, 1);   // LVLEN:  1=disabled (uart/gpio)
        gpio_write(&mdmUsbDet, 0);  // USBDET: 0=disabled
        // now we can savely switch off the ldo
        gpio_write(&mdmEn, 0);      // LDOEN:  0=off
    }
}        

void c027_gps_powerOn(void) {
    if (!gpio_read(&gpsEn)) {
        // switch on power supply
        gpio_write(&gpsEn, 1);          // LDOEN: 1=on
        wait_ms(1);                     // wait until supply switched off
        if (gpio_read(&mdmEn)) 
            gpio_write(&mdmILvlOe, 1);  // ILVLEN: 1=enabled (i2c)
    }
}

void c027_gps_powerOff(void) {
    if (gpio_read(&gpsEn)) {
        gpio_write(&mdmILvlOe, 0);  // ILVLEN: 0=disabled (i2c)
        gpio_write(&gpsEn, 0);      // LDOEN: 0=off
    }
}
