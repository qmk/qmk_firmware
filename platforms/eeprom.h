// Copyright 2018-2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#if defined(__AVR__) && !defined(EEPROM_DRIVER)
#    include <avr/eeprom.h>
#else
#    include <stdint.h>
#    include <stdlib.h>

uint8_t  eeprom_read_byte(const uint8_t *__p);
uint16_t eeprom_read_word(const uint16_t *__p);
uint32_t eeprom_read_dword(const uint32_t *__p);
void     eeprom_read_block(void *__dst, const void *__src, size_t __n);
void     eeprom_write_byte(uint8_t *__p, uint8_t __value);
void     eeprom_write_word(uint16_t *__p, uint16_t __value);
void     eeprom_write_dword(uint32_t *__p, uint32_t __value);
void     eeprom_write_block(const void *__src, void *__dst, size_t __n);
void     eeprom_update_byte(uint8_t *__p, uint8_t __value);
void     eeprom_update_word(uint16_t *__p, uint16_t __value);
void     eeprom_update_dword(uint32_t *__p, uint32_t __value);
void     eeprom_update_block(const void *__src, void *__dst, size_t __n);
#endif

#if defined(EEPROM_CUSTOM)
#    ifndef EEPROM_SIZE
#        error EEPROM_SIZE has not been defined for custom driver.
#    endif
#    define TOTAL_EEPROM_BYTE_COUNT (EEPROM_SIZE)
#elif defined(EEPROM_TRANSIENT)
#    include "eeprom_transient.h"
#    define TOTAL_EEPROM_BYTE_COUNT (TRANSIENT_EEPROM_SIZE)
#elif defined(EEPROM_I2C)
#    include "eeprom_i2c.h"
#    define TOTAL_EEPROM_BYTE_COUNT (EXTERNAL_EEPROM_BYTE_COUNT)
#elif defined(EEPROM_SPI)
#    include "eeprom_spi.h"
#    define TOTAL_EEPROM_BYTE_COUNT (EXTERNAL_EEPROM_BYTE_COUNT)
#elif defined(EEPROM_STM32_L0_L1)
#    include "eeprom_stm32_L0_L1.h"
#    define TOTAL_EEPROM_BYTE_COUNT (STM32_ONBOARD_EEPROM_SIZE)
#elif defined(EEPROM_TEENSY)
#    include "eeprom_teensy.h"
#    define TOTAL_EEPROM_BYTE_COUNT (EEPROM_SIZE)
#elif defined(EEPROM_STM32_FLASH_EMULATED)
#    include "eeprom_stm32_defs.h"
#    define TOTAL_EEPROM_BYTE_COUNT (FEE_DENSITY_BYTES)
#elif defined(EEPROM_SAMD)
#    include "eeprom_samd.h"
#    define TOTAL_EEPROM_BYTE_COUNT (EEPROM_SIZE)
#elif defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega16U4__) || defined(__AVR_AT90USB162__) || defined(__AVR_ATtiny85__)
#    define TOTAL_EEPROM_BYTE_COUNT 512
#elif defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32A__)
#    define TOTAL_EEPROM_BYTE_COUNT 1024
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__)
#    define TOTAL_EEPROM_BYTE_COUNT 2048
#elif defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#    define TOTAL_EEPROM_BYTE_COUNT 4096
#elif defined(EEPROM_TEST_HARNESS)
#    ifndef FLASH_STM32_MOCKED
// Normal tests
#        define TOTAL_EEPROM_BYTE_COUNT 32
#    else
// Flash wear-leveling testing
#        include "eeprom_stm32_tests.h"
#        define TOTAL_EEPROM_BYTE_COUNT (EEPROM_SIZE)
#    endif
#else
#    error Unknown EEPROM driver.
#endif
