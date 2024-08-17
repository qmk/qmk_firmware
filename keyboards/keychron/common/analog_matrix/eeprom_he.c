/* Copyright 2019 Nick Brassel (tzarc)
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

#include <stdint.h>
#include <string.h>
#if defined(EXTERNAL_EEPROM_WP_PIN)
#    include "gpio.h"
#endif
#    include "eeprom_he.h"

/*
    Note that the implementations of eeprom_XXXX_YYYY on AVR are normally
    provided by avr-libc. The same functions are reimplemented below and are
    rerouted to the external i2c equivalent.

    Seemingly, as this is compiled from within QMK, the object file generated
    during the build overrides the avr-libc implementation during the linking
    stage.

    On other platforms such as ARM, there are no provided implementations, so
    there is nothing to override during linkage.
*/

#include "wait.h"
#include "i2c_master.h"
#include "eeprom.h"
#include "eeprom_he.h"

// #define DEBUG_EEPROM_OUTPUT

#if defined(CONSOLE_ENABLE) && defined(DEBUG_EEPROM_OUTPUT)
#    include "timer.h"
#    include "debug.h"
#endif // DEBUG_EEPROM_OUTPUT

#ifdef USE_GPIOV1
#    ifndef I2C1_SCL_PAL_MODE
#        define I2C1_SCL_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#    endif
#    ifndef I2C1_SDA_PAL_MODE
#        define I2C1_SDA_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#    endif
#else
// The default PAL alternate modes are used to signal that the pins are used for I2C
#    ifndef I2C1_SCL_PAL_MODE
#        define I2C1_SCL_PAL_MODE 4
#    endif
#    ifndef I2C1_SDA_PAL_MODE
#        define I2C1_SDA_PAL_MODE 4
#    endif
#endif

static inline void fill_target_address(uint8_t *buffer, const void *addr) {
    uintptr_t p = (uintptr_t)addr;
    for (int i = 0; i < EXTERNAL_EEPROM_ADDRESS_SIZE; ++i) {
        buffer[EXTERNAL_EEPROM_ADDRESS_SIZE - 1 - i] = p & 0xFF;
        p >>= 8;
    }
}

/* Override i2c_init */
void i2c_init(void) {
    // Try releasing special pins for a short time
    palSetLineMode(I2C1_SCL_PIN, PAL_MODE_INPUT);
    palSetLineMode(I2C1_SDA_PIN, PAL_MODE_INPUT);

    chThdSleepMilliseconds(10);
#if defined(USE_GPIOV1)
    palSetLineMode(I2C1_SCL_PIN, I2C1_SCL_PAL_MODE);
    palSetLineMode(I2C1_SDA_PIN, I2C1_SDA_PAL_MODE);
#else
    palSetLineMode(I2C1_SCL_PIN, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_OUTPUT_TYPE_OPENDRAIN);
    palSetLineMode(I2C1_SDA_PIN, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_OUTPUT_TYPE_OPENDRAIN);
#endif
}

void he_eeprom_driver_init(void) {

    i2c_init();
#if defined(EXTERNAL_EEPROM_WP_PIN)
    /* We are setting the WP pin to high in a way that requires at least two bit-flips to change back to 0 */
    writePin(EXTERNAL_EEPROM_WP_PIN, 1);
    setPinInputHigh(EXTERNAL_EEPROM_WP_PIN);
#endif
}

void he_eeprom_driver_erase(void) {

#if defined(CONSOLE_ENABLE) && defined(DEBUG_EEPROM_OUTPUT)
    uint32_t start = timer_read32();
#endif

    uint8_t buf[EXTERNAL_EEPROM_PAGE_SIZE];
    memset(buf, 0x00, EXTERNAL_EEPROM_PAGE_SIZE);
    for (uint32_t addr = 0; addr < EXTERNAL_EEPROM_BYTE_COUNT; addr += EXTERNAL_EEPROM_PAGE_SIZE) {
        he_eeprom_write_block(buf, (void *)(uintptr_t)addr, EXTERNAL_EEPROM_PAGE_SIZE);
    }
}

void he_eeprom_read_block(void *buf, const void *addr, size_t len) {

    uint8_t complete_packet[EXTERNAL_EEPROM_ADDRESS_SIZE];
    fill_target_address(complete_packet, addr);

    i2c_transmit(EXTERNAL_EEPROM_I2C_ADDRESS((uintptr_t)addr), complete_packet, EXTERNAL_EEPROM_ADDRESS_SIZE, 100);
    i2c_receive(EXTERNAL_EEPROM_I2C_ADDRESS((uintptr_t)addr), buf, len, 100);
}

void he_eeprom_write_block(const void *buf, void *addr, size_t len) {

    uint8_t   complete_packet[EXTERNAL_EEPROM_ADDRESS_SIZE + EXTERNAL_EEPROM_PAGE_SIZE];
    uint8_t * read_buf    = (uint8_t *)buf;
    uintptr_t target_addr = (uintptr_t)addr;

#if defined(EXTERNAL_EEPROM_WP_PIN)
    setPinOutput(EXTERNAL_EEPROM_WP_PIN);
    writePin(EXTERNAL_EEPROM_WP_PIN, 0);
#endif

    while (len > 0) {
        uintptr_t page_offset  = target_addr % EXTERNAL_EEPROM_PAGE_SIZE;
        int       write_length = EXTERNAL_EEPROM_PAGE_SIZE - page_offset;
        if (write_length > len) {
            write_length = len;
        }

        fill_target_address(complete_packet, (const void *)target_addr);
        for (uint8_t i = 0; i < write_length; i++) {
            complete_packet[EXTERNAL_EEPROM_ADDRESS_SIZE + i] = read_buf[i];
        }

        i2c_transmit(EXTERNAL_EEPROM_I2C_ADDRESS((uintptr_t)addr), complete_packet, EXTERNAL_EEPROM_ADDRESS_SIZE + write_length, 100);
        wait_ms(EXTERNAL_EEPROM_WRITE_TIME);

        read_buf += write_length;
        target_addr += write_length;
        len -= write_length;
    }

#if defined(EXTERNAL_EEPROM_WP_PIN)
    /* We are setting the WP pin to high in a way that requires at least two bit-flips to change back to 0 */
    writePin(EXTERNAL_EEPROM_WP_PIN, 1);
    setPinInputHigh(EXTERNAL_EEPROM_WP_PIN);
#endif
}
