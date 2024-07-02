/* Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2023 customMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* This library is only valid for STM32 processors.
 * This library follows the convention of the AVR i2c_master library.
 * As a result addresses are expected to be already shifted (addr << 1).
 * I2CD1 is the default driver which corresponds to pins B6 and B7. This
 * can be changed.
 * Please ensure that HAL_USE_I2C is TRUE in the halconf.h file and that
 * STM32_I2C_USE_I2C1 is TRUE in the mcuconf.h file. Pins B6 and B7 are used
 * but using any other I2C pins should be trivial.
 */

#include "i2c_master.h"
#include "gpio.h"
#include "chibios_config.h"
#include <string.h>
#include <ch.h>
#include <hal.h>

static const I2CConfig _i2cx_config = {
#if defined(USE_I2CV1_CONTRIB)
    _I2Cx_CLOCK_SPEED,
#elif defined(USE_I2CV1)
    _I2Cx_OPMODE,
    _I2Cx_CLOCK_SPEED,
    _I2Cx_DUTY_CYCLE,
#elif defined(WB32F3G71xx) || defined(WB32FQ95xx)
    _I2Cx_OPMODE,
    _I2Cx_CLOCK_SPEED,
#else
    // This configures the I2C clock to 400khz assuming a 72Mhz clock
    // For more info : https://www.st.com/en/embedded-software/stsw-stm32126.html
    STM32_TIMINGR_PRESC(_I2Cx_TIMINGR_PRESC) | STM32_TIMINGR_SCLDEL(_I2Cx_TIMINGR_SCLDEL) | STM32_TIMINGR_SDADEL(_I2Cx_TIMINGR_SDADEL) | STM32_TIMINGR_SCLH(_I2Cx_TIMINGR_SCLH) | STM32_TIMINGR_SCLL(_I2Cx_TIMINGR_SCLL), 0, 0
#endif
};

/**
 * @brief Handles any I2C error condition by stopping the I2C peripheral and
 * aborting any ongoing transactions. Furthermore ChibiOS status codes are
 * converted into QMK codes.
 *
 * @param status ChibiOS specific I2C status code
 * @return i2c_status_t QMK specific I2C status code
 */
static i2c_status_t _i2cx_epilogue(const msg_t status) {
    if (status == MSG_OK) {
        return I2C_STATUS_SUCCESS;
    }

    // From ChibiOS HAL: "After a timeout the driver must be stopped and
    // restarted because the bus is in an uncertain state." We also issue that
    // hard stop in case of any error.
    i2cStop(&_I2Cx_DRIVER);

    return status == MSG_TIMEOUT ? I2C_STATUS_TIMEOUT : I2C_STATUS_ERROR;
}

__attribute__((weak)) void _i2cx_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        palSetLineMode(_I2Cx_SCL_PIN, PAL_MODE_INPUT);
        palSetLineMode(_I2Cx_SDA_PIN, PAL_MODE_INPUT);

        chThdSleepMilliseconds(10);
#if defined(USE_GPIOV1)
        palSetLineMode(_I2Cx_SCL_PIN, _I2Cx_SCL_PAL_MODE);
        palSetLineMode(_I2Cx_SDA_PIN, _I2Cx_SDA_PAL_MODE);
#else
        palSetLineMode(_I2Cx_SCL_PIN, PAL_MODE_ALTERNATE(_I2Cx_SCL_PAL_MODE) | PAL_OUTPUT_TYPE_OPENDRAIN);
        palSetLineMode(_I2Cx_SDA_PIN, PAL_MODE_ALTERNATE(_I2Cx_SDA_PAL_MODE) | PAL_OUTPUT_TYPE_OPENDRAIN);
#endif
    }
}

i2c_status_t _i2cx_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout) {
    i2cStart(&_I2Cx_DRIVER, &_i2cx_config);
    msg_t status = i2cMasterTransmitTimeout(&_I2Cx_DRIVER, (address >> 1), data, length, 0, 0, TIME_MS2I(timeout));
    return _i2cx_epilogue(status);
}

i2c_status_t _i2cx_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout) {
    i2cStart(&_I2Cx_DRIVER, &_i2cx_config);
    msg_t status = i2cMasterReceiveTimeout(&_I2Cx_DRIVER, (address >> 1), data, length, TIME_MS2I(timeout));
    return _i2cx_epilogue(status);
}

i2c_status_t _i2cx_write_register(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout) {
    i2cStart(&_I2Cx_DRIVER, &_i2cx_config);

    uint8_t complete_packet[length + 1];
    for (uint16_t i = 0; i < length; i++) {
        complete_packet[i + 1] = data[i];
    }
    complete_packet[0] = regaddr;

    msg_t status = i2cMasterTransmitTimeout(&_I2Cx_DRIVER, (devaddr >> 1), complete_packet, length + 1, 0, 0, TIME_MS2I(timeout));
    return _i2cx_epilogue(status);
}

i2c_status_t _i2cx_write_register16(uint8_t devaddr, uint16_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout) {
    i2cStart(&_I2Cx_DRIVER, &_i2cx_config);

    uint8_t complete_packet[length + 2];
    for (uint16_t i = 0; i < length; i++) {
        complete_packet[i + 2] = data[i];
    }
    complete_packet[0] = regaddr >> 8;
    complete_packet[1] = regaddr & 0xFF;

    msg_t status = i2cMasterTransmitTimeout(&_I2Cx_DRIVER, (devaddr >> 1), complete_packet, length + 2, 0, 0, TIME_MS2I(timeout));
    return _i2cx_epilogue(status);
}

i2c_status_t _i2cx_read_register(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
    i2cStart(&_I2Cx_DRIVER, &_i2cx_config);
    msg_t status = i2cMasterTransmitTimeout(&_I2Cx_DRIVER, (devaddr >> 1), &regaddr, 1, data, length, TIME_MS2I(timeout));
    return _i2cx_epilogue(status);
}

i2c_status_t _i2cx_read_register16(uint8_t devaddr, uint16_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
    i2cStart(&_I2Cx_DRIVER, &_i2cx_config);
    uint8_t register_packet[2] = {regaddr >> 8, regaddr & 0xFF};
    msg_t   status             = i2cMasterTransmitTimeout(&_I2Cx_DRIVER, (devaddr >> 1), register_packet, 2, data, length, TIME_MS2I(timeout));
    return _i2cx_epilogue(status);
}

__attribute__((weak)) i2c_status_t _i2cx_ping_address(uint8_t address, uint16_t timeout) {
    // ChibiOS does not provide low level enough control to check for an ack.
    // Best effort instead tries reading register 0 which will either succeed or timeout.
    // This approach may produce false negative results for I2C devices that do not respond to a register 0 read request.
    uint8_t data = 0;
    return _i2cx_read_register(address, 0, &data, sizeof(data), timeout);
}
