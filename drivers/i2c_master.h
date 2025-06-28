// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

/**
 * \file
 *
 * \defgroup i2c_master I2C Master API
 *
 * \brief API to communicate with I2C devices.
 * \{
 */

typedef int16_t i2c_status_t;

#define I2C_STATUS_SUCCESS (0)
#define I2C_STATUS_ERROR (-1)
#define I2C_STATUS_TIMEOUT (-2)

#define I2C_TIMEOUT_IMMEDIATE (0)
#define I2C_TIMEOUT_INFINITE (0xFFFF)

/**
 * \brief Initialize the I2C driver. This function must be called only once, before any of the below functions can be called.
 *
 * This function is weakly defined, meaning it can be overridden if necessary for your particular use case.
 */
void i2c_init(void);

/**
 * \brief Send multiple bytes to the selected I2C device.
 *
 * \param address The 7-bit I2C address of the device.
 * \param data A pointer to the data to transmit.
 * \param length The number of bytes to write. Take care not to overrun the length of `data`.
 * \param timeout The time in milliseconds to wait for a response from the target device.
 *
 * \return `I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
 */
i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout);

#if defined(__AVR__) || defined(__DOXYGEN__)
/**
 * \brief Send multiple bytes from PROGMEM to the selected I2C device.
 *
 * On ARM devices, this function is simply an alias for i2c_transmit(address, data, length, timeout).
 *
 * \param address The 7-bit I2C address of the device.
 * \param data A pointer to the data to transmit.
 * \param length The number of bytes to write. Take care not to overrun the length of `data`.
 * \param timeout The time in milliseconds to wait for a response from the target device.
 *
 * \return `I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
 */
i2c_status_t i2c_transmit_P(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout);
#else
#    define i2c_transmit_P(address, data, length, timeout) i2c_transmit(address, data, length, timeout)
#endif

/**
 * \brief Receive multiple bytes from the selected I2C device.
 *
 * \param address The 7-bit I2C address of the device.
 * \param data A pointer to a buffer to read into.
 * \param length The number of bytes to read. Take care not to overrun the length of `data`.
 * \param timeout The time in milliseconds to wait for a response from the target device.
 *
 * \return `I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
 */
i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);

/**
 * \brief Write to a register with an 8-bit address on the I2C device.
 *
 * \param devaddr The 7-bit I2C address of the device.
 * \param regaddr The register address to write to.
 * \param data A pointer to the data to transmit.
 * \param length The number of bytes to write. Take care not to overrun the length of `data`.
 * \param timeout The time in milliseconds to wait for a response from the target device.
 *
 * \return `I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
 */
i2c_status_t i2c_write_register(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout);

/**
 * \brief Write to a register with a 16-bit address (big endian) on the I2C device.
 *
 * \param devaddr The 7-bit I2C address of the device.
 * \param regaddr The register address to write to.
 * \param data A pointer to the data to transmit.
 * \param length The number of bytes to write. Take care not to overrun the length of `data`.
 * \param timeout The time in milliseconds to wait for a response from the target device.
 *
 * \return `I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
 */
i2c_status_t i2c_write_register16(uint8_t devaddr, uint16_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout);

/**
 * \brief Read from a register with an 8-bit address on the I2C device.
 *
 * \param devaddr The 7-bit I2C address of the device.
 * \param regaddr The register address to read from.
 * \param data A pointer to a buffer to read into.
 * \param length The number of bytes to read. Take care not to overrun the length of `data`.
 * \param timeout The time in milliseconds to wait for a response from the target device.
 *
 * \return `I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
 */
i2c_status_t i2c_read_register(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);

/**
 * \brief Read from a register with a 16-bit address (big endian) on the I2C device.
 *
 * \param devaddr The 7-bit I2C address of the device.
 * \param regaddr The register address to read from.
 * \param data A pointer to a buffer to read into.
 * \param length The number of bytes to read. Take care not to overrun the length of `data`.
 * \param timeout The time in milliseconds to wait for a response from the target device.
 *
 * \return `I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
 */
i2c_status_t i2c_read_register16(uint8_t devaddr, uint16_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);

/**
 * \brief Ping the I2C bus for a specific address.
 *
 * On ChibiOS a "best effort" attempt is made by reading a single byte from register 0 at the given address. This should generally work except for I2C devices that do not not respond to a register 0 read request, which will result in a false negative result (unsuccessful response to ping attempt).
 *
 * This function is weakly defined, meaning it can be overridden if necessary for your particular use case.
 *
 * \param address The 7-bit I2C address of the device.
 * \param timeout The time in milliseconds to wait for a response from the target device.
 *
 * \return `I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
 */
i2c_status_t i2c_ping_address(uint8_t address, uint16_t timeout);

/** \} */
