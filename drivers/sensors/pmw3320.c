/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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

#include "pmw3320.h"
#include "wait.h"
#include "debug.h"
#include "gpio.h"

typedef enum {
    PMW3320_REG_Product_ID          = 0x00,
    PMW3320_REG_Revision_ID         = 0x01,
    PMW3320_REG_Motion              = 0x02,
    PMW3320_REG_Delta_X             = 0x03,
    PMW3320_REG_Delta_Y             = 0x04,
    PMW3320_REG_SQUAL               = 0x05,
    PMW3320_REG_Shutter_Upper       = 0x06,
    PMW3320_REG_Shutter_Lower       = 0x07,
    PMW3320_REG_Maximum_Pixel       = 0x08,
    PMW3320_REG_Pixel_Accum         = 0x09,
    PMW3320_REG_Minimum_Pixel       = 0x0a,
    PMW3320_REG_Pixel_Grab          = 0x0b,
    PMW3320_REG_Delta_XY            = 0x0c,
    PMW3320_REG_Resolution          = 0x0d,
    PMW3320_REG_Run_Downshift       = 0x0e,
    PMW3320_REG_Rest1_Period        = 0x0f,
    PMW3320_REG_Rest1_Downshift     = 0x10,
    PMW3320_REG_Rest2_Preiod        = 0x11,
    PMW3320_REG_Rest2_Downshift     = 0x12,
    PMW3320_REG_Rest3_Period        = 0x13,
    PMW3320_REG_Min_SQ_Run          = 0x17,
    PMW3320_REG_Axis_Control        = 0x1a,
    PMW3320_REG_Performance         = 0x22,
    PMW3320_REG_Low_Motion_Jitter   = 0x23,
    PMW3320_REG_Shutter_Max_HI      = 0x36,
    PMW3320_REG_Shutter_Max_LO      = 0x37,
    PMW3320_REG_Frame_Rate          = 0x39,
    PMW3320_REG_Power_Up_Reset      = 0x3a,
    PMW3320_REG_Shutdown            = 0x3b,
    PMW3320_REG_Inverse_Revision_ID = 0x3f,
    PMW3320_REG_Led_Control         = 0x40,
    PMW3320_REG_Motion_Control      = 0x41,
    PMW3320_REG_Burst_Read_First    = 0x42,
    PMW3320_REG_Rest_Mode_Status    = 0x45,
    PMW3320_REG_Inverse_Product_ID  = 0x4f,
    PMW3320_REG_Motion_Burst        = 0x63,
} pmw3320_regs;

const pointing_device_driver_t pmw3320_driver_default = {.init = pmw3320_init, .get_report = pmw3320_get_report, .set_cpi = pmw3320_set_cpi, .get_cpi = pmw3320_get_cpi};
#if defined(PMW3320_SCLK_PIN) & defined(PMW3320_SDIO_PIN) & defined(PMW3320_CS_PIN)
const pointing_device_3wire_spi_config_t pmw3320_config_default = {.cs = PMW3320_CS_PIN, .sclk = PMW3320_SCLK_PIN, .sdio = PMW3320_SDIO_PIN};
#endif

void             pmw3320_sync(pin_t cs);
uint8_t          pmw3320_serial_read(pointing_device_3wire_spi_config_t* pmw3320_config);
void             pmw3320_serial_write(pointing_device_3wire_spi_config_t* pmw3320_config, uint8_t data);
uint8_t          pmw3320_read_reg(pointing_device_3wire_spi_config_t* pmw3320_config, pmw3320_regs reg_addr);
void             pmw3320_write_reg(pointing_device_3wire_spi_config_t* pmw3320_config, pmw3320_regs reg_addr, uint8_t data);
report_pmw3320_t pmw3320_read_burst(pointing_device_3wire_spi_config_t* pmw3320_config);

void pmw3320_init(const void* config) {
    pointing_device_3wire_spi_config_t* pmw3320_config = (pointing_device_3wire_spi_config_t*)config;
    // Initialize sensor serial pins.
    gpio_set_pin_output(pmw3320_config->sclk);
    gpio_set_pin_output(pmw3320_config->sdio);
    gpio_set_pin_output(pmw3320_config->cs);

    // reboot the sensor.
    pmw3320_write_reg(pmw3320_config, PMW3320_REG_Power_Up_Reset, 0x5a);

    // wait maximum time before sensor is ready.
    // this ensures that the sensor is actually ready after reset.
    wait_ms(55);

    // read a burst from the sensor and then discard it.
    // gets the sensor ready for write commands
    // (for example, setting the dpi).
    pmw3320_read_burst(pmw3320_config);

    // Pretty sure that this shouldn't be in the driver.
    // Probably device specific?
    // Set rest mode to default
    pmw3320_write_reg(pmw3320_config, PMW3320_REG_Rest_Mode_Status, 0x00);
    // Set LED to be always on
    pmw3320_write_reg(pmw3320_config, PMW3320_REG_Led_Control, 0x4);
    // Disable rest mode
    pmw3320_write_reg(pmw3320_config, PMW3320_REG_Performance, 0x80);
}

// Perform a synchronization with sensor.
// Just as with the serial protocol, this is used by the slave to send a
// synchronization signal to the master.
void pmw3320_sync(void) {
    gpio_write_pin_low(PMW3320_CS_PIN);
    wait_us(1);
    gpio_write_pin_high(PMW3320_CS_PIN);
}

void pmw3320_cs_select(void) {
    gpio_write_pin_low(PMW3320_CS_PIN);
}

void pmw3320_cs_deselect(void) {
    gpio_write_pin_high(PMW3320_CS_PIN);
}

uint8_t pmw3320_serial_read(void) {
    gpio_set_pin_input(PMW3320_SDIO_PIN);
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; ++i) {
        gpio_write_pin_low(PMW3320_SCLK_PIN);
        wait_us(1);

        byte = (byte << 1) | gpio_read_pin(PMW3320_SDIO_PIN);

        gpio_write_pin_high(PMW3320_SCLK_PIN);
        void pmw3320_sync(pin_t cs) {
            gpio_write_pin_low(cs);
            wait_us(1);
            gpio_write_pin_high(cs);
        }

        void pmw3320_cs_select(pin_t cs) {
            gpio_write_pin_low(cs);
        }

        void pmw3320_cs_deselect(pin_t cs) {
            gpio_write_pin_high(cs);
        }

        uint8_t pmw3320_serial_read(pointing_device_3wire_spi_config_t * pmw3320_config) {
            setPinInput(pmw3320_config->sdio);
            uint8_t byte = 0;

            for (uint8_t i = 0; i < 8; ++i) {
                gpio_write_pin_low(pmw3320_config->sclk);
                wait_us(1);

                byte = (byte << 1) | readPin(pmw3320_config->sdio);

                gpio_write_pin_high(pmw3320_config->sclk);
                wait_us(1);
            }

            return byte;
        }

        void pmw3320_serial_write(pointing_device_3wire_spi_config_t * pmw3320_config, uint8_t data) {
            gpio_set_pin_output(pmw3320_config->sdio);

            for (int8_t b = 7; b >= 0; b--) {
                gpio_write_pin_low(pmw3320_config->sclk);

                if (data & (1 << b))
                    gpio_write_pin_high(pmw3320_config->sdio);
                else
                    gpio_write_pin_low(pmw3320_config->sdio);

                wait_us(2);

                gpio_write_pin_high(pmw3320_config->sclk);
            }

            // This was taken from ADNS5050 driver.
            // There's no any info in PMW3320 datasheet about this...
            // tSWR. See page 15 of the ADNS5050 spec sheet.
            // Technically, this is only necessary if the next operation is an SDIO
            // read. This is not guaranteed to be the case, but we're being lazy.
            wait_us(4);

            // Note that tSWW is never necessary. All write operations require at
            // least 32us, which exceeds tSWW, so there's never a need to wait for it.
        }

        // Read a byte of data from a register on the sensor.
        uint8_t pmw3320_read_reg(pointing_device_3wire_spi_config_t * pmw3320_config, pmw3320_regs reg_addr) {
            pmw3320_cs_select(pmw3320_config->cs);

            pmw3320_serial_write(pmw3320_config, reg_addr);

            uint8_t byte = pmw3320_serial_read(pmw3320_config);

            // This was taken directly from ADNS5050 driver...
            // tSRW & tSRR. See page 15 of the ADNS5050 spec sheet.
            // Technically, this is only necessary if the next operation is an SDIO
            // read or write. This is not guaranteed to be the case.
            // Honestly, this wait could probably be removed.
            wait_us(1);

            pmw3320_cs_deselect(pmw3320_config->cs);

            return byte;
        }

        void pmw3320_write_reg(pointing_device_3wire_spi_config_t * pmw3320_config, pmw3320_regs reg_addr, uint8_t data) {
            pmw3320_cs_select(pmw3320_config->cs);
            pmw3320_serial_write(pmw3320_config, 0b10000000 | reg_addr);
            pmw3320_serial_write(pmw3320_config, data);
            pmw3320_cs_deselect(pmw3320_config->cs);
        }

        report_pmw3320_t pmw3320_read_burst(pointing_device_3wire_spi_config_t * pmw3320_config) {
            pmw3320_cs_select(pmw3320_config->cs);

            report_pmw3320_t data;
            data.dx = 0;
            data.dy = 0;

            pmw3320_serial_write(pmw3320_config, PMW3320_REG_Motion_Burst);

            uint8_t x = pmw3320_serial_read(pmw3320_config);
            uint8_t y = pmw3320_serial_read(pmw3320_config);

            // Probably burst mode may include contents of delta_xy register,
            // which contain HI parts of x/y deltas, but I had no luck finding it.
            // Probably it's required to activate 12-bit mode to access this data.
            // So we end burst mode early to not read unneeded information.
            pmw3320_cs_deselect(pmw3320_config->cs);

            data.dx = paw3320_convert_twoscomp(x);
            data.dy = paw3320_convert_twoscomp(y);

            return data;
        }

        // Convert a two's complement byte from an unsigned data type into a signed
        // data type.
        int8_t paw3320_convert_twoscomp(uint8_t data) {
            if ((data & 0x80) == 0x80)
                return -128 + (data & 0x7F);
            else
                return data;
        }

        uint16_t pmw3320_get_cpi(const void* config) {
            pointing_device_3wire_spi_config_t* pmw3320_config = (pointing_device_3wire_spi_config_t*)config;

            uint8_t cpival = pmw3320_read_reg(pmw3320_config, PMW3320_REG_Resolution);
            // 0x1F is an inversion of 0x20 which is 0b100000
            return (uint16_t)((cpival & 0x1F) * PMW3320_CPI_STEP);
        }

        void pmw3320_set_cpi(const void* config, uint16_t cpi) {
            pointing_device_3wire_spi_config_t* pmw3320_config = (pointing_device_3wire_spi_config_t*)config;

            uint8_t cpival = constrain((cpi / PMW3320_CPI_STEP), (PMW3320_CPI_MIN / PMW3320_CPI_STEP), (PMW3320_CPI_MAX / PMW3320_CPI_STEP)) - 1U;

            // Fifth bit is probably a control bit.
            // PMW3320 datasheet don't have any info on this, so this is a pure guess.
            pmw3320_write_reg(pmw3320_config, PMW3320_REG_Resolution, 0x20 | cpival);
        }

        bool pmw3320_check_signature(pointing_device_3wire_spi_config_t * pmw3320_config) {
            uint8_t pid  = pmw3320_read_reg(pmw3320_config, PMW3320_REG_Product_ID);
            uint8_t pid2 = pmw3320_read_reg(pmw3320_config, PMW3320_REG_Inverse_Product_ID);

            return (pid == 0x3b && pid2 == 0xc4);
        }

        report_mouse_t pmw3320_get_report(const void* config) {
            pointing_device_3wire_spi_config_t* pmw3320_config = (pointing_device_3wire_spi_config_t*)config;
            report_pmw3320_t                    data           = pmw3320_read_burst(pmw3320_config);
            report_mouse_t                      mouse_report   = {0};

            if (data.dx != 0 || data.dy != 0) {
                pd_dprintf("Raw ] X: %d, Y: %d\n", data.dx, data.dy);
                mouse_report.x = (mouse_xy_report_t)data.dx;
                mouse_report.y = (mouse_xy_report_t)data.dy;
            }

            return mouse_report;
        }
