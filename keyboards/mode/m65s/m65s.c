/*
 Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

#include "m65s.h"
#include <ch.h>
#include <hal.h>
#include <i2c_master.h>


#define LED_PIN_ON_STATE 1
void led_init_ports(void) {

/** If the OPENDRAIN_INDICATORS option is not defined in config.h, the indicator
    pins default to push-pull output. Else, they are defined as open-drain. The
    pin mode configuration is done through the INDICATOR_PIN_MODE which is 
    attributed right at the beggining. **/

#ifndef OPENDRAIN_INDICATORS
#    define INDICATOR_PIN_MODE PAL_MODE_OUTPUT_PUSHPULL
#else
#    define INDICATOR_PIN_MODE PAL_MODE_OUTPUT_OPENDRAIN
	
#endif

#ifdef LED_NUM_LOCK_PIN
    palSetLineMode(LED_NUM_LOCK_PIN, INDICATOR_PIN_MODE);
#endif
#ifdef LED_CAPS_LOCK_PIN
    palSetLineMode(LED_CAPS_LOCK_PIN, INDICATOR_PIN_MODE);
#endif
#ifdef LED_SCROLL_LOCK_PIN
    palSetLineMode(LED_SCROLL_LOCK_PIN, INDICATOR_PIN_MODE);
#endif
#ifdef LED_COMPOSE_PIN
    palSetLineMode(LED_COMPOSE_PIN, INDICATOR_PIN_MODE);
#endif
#ifdef LED_KANA_PIN
    palSetLineMode(LED_KANA_PIN, INDICATOR_PIN_MODE);
#endif
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        writePin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
    }
    return res;
}

void board_init_i2c1(void) {
    static const I2CConfig i2cconfig = { OPMODE_I2C, 400000, FAST_DUTY_CYCLE_2, };
    uint8_t txdata[2] = { 0x00, 0x00 };
    uint8_t rxdata[2] = { 0x00, 0x00 };
    palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_MODE_ALTERNATE | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_MODE_ALTERNATE | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST);
    i2cStart(&I2CD1, &i2cconfig);
    msg_t status = i2cMasterTransmitTimeout(&I2CD1, 0b1010000, txdata, sizeof(txdata), rxdata, sizeof(rxdata), TIME_MS2I(1000));
    i2cflags_t err = i2cGetErrors(&I2CD1);
    i2cStop(&I2CD1);
    (void)status;
    (void)err;
}

void board_init(void) {
    chSysInit();
    board_init_i2c1();
    palSetPadMode(GPIOB, 10, PAL_MODE_INPUT);
    palSetPadMode(GPIOB, 9, PAL_MODE_INPUT);

    // board_init_i2c2();
   // while(1);
}
