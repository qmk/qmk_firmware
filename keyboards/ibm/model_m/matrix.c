/* Copyright 2024 Richard George
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

#include "matrix.h"
#include "quantum.h"
#include "spi_master.h"
#include "gpio.h"

// MCP23S17 register addresses
#define MCP23S17_IODIRA 0x00 // I/O Direction Register A
#define MCP23S17_IODIRB 0x01 // I/O Direction Register B
#define MCP23S17_GPPUA 0x0C  // Pull-Up Resistor Configuration Register A
#define MCP23S17_GPIOA 0x12  // General Purpose I/O Port A
#define MCP23S17_GPIOB 0x13  // General Purpose I/O Port B
#define MCP23S17_OLATA 0x14  // Output Latch A
#define MCP23S17_OLATB 0x15  // Output Latch B
#define MCP23S17_IOCON 0x0A  // I/O Configuration Register (BANK=0 default)

// MCP23S17 command byte (device address + read/write bit)
#define MCP23S17_CMD_WRITE(addr) (0x40 | ((addr) << 1))
#define MCP23S17_CMD_READ(addr) (0x41 | ((addr) << 1))

// MCP23S17 chip select pins (for two expanders)
#define MCP23S17_CS1 (uint8_t) MCP23S17_CS1_PIN // CS for expander A (columns), address 0x01
#define MCP23S17_CS2 (uint8_t) MCP23S17_CS2_PIN // CS for expander B (rows), address 0x00

// MCP23S17 register read/write functions
static void    mcp23s17_init_expander(uint8_t cs_pin, uint8_t addr, uint8_t iodir_a, uint8_t iodir_b);
static void    mcp23s17_write_reg(uint8_t cs_pin, uint8_t addr, uint8_t reg_addr, uint8_t data);
static uint8_t mcp23s17_read_reg(uint8_t cs_pin, uint8_t addr, uint8_t reg_addr);

// Matrix scanning via MCP23S17 port expanders
static void         select_col(uint8_t col);
static void         unselect_cols(void);
static matrix_row_t read_rows(void);

void keyboard_pre_init_kb(void) {
    // Initialize SPI master
    spi_init();

    // Set chip select pins as output
    gpio_set_pin_output(MCP23S17_CS1);
    gpio_set_pin_output(MCP23S17_CS2);

    // Deselect both chips (active low, so write HIGH)
    gpio_write_pin_high(MCP23S17_CS1);
    gpio_write_pin_high(MCP23S17_CS2);

    keyboard_pre_init_user();
}

//------------------------------------------------------------------------------
// Custom Matrix Implementation
//------------------------------------------------------------------------------

void matrix_init_custom(void) {
    // Initialize MCP23S17 expanders here so they're ready before bootmagic runs.

    // Enable HAEN (Hardware Address Enable) on both expanders so they only
    // respond to their assigned address (bit 3 of IOCON, register 0x0A).
    // Use address 0x00 for the initial write (before HAEN is enabled).
    mcp23s17_write_reg(MCP23S17_CS2, 0x00, MCP23S17_IOCON, 0x08);
    mcp23s17_write_reg(MCP23S17_CS1, 0x00, MCP23S17_IOCON, 0x08);

    // Expander B (CS2, addr 0x00) - Short 8-pin connector (Rows), all inputs
    mcp23s17_init_expander(MCP23S17_CS2, 0x00, 0xFF, 0xFF);
    // Enable pull-ups on row expander GPA0-GPA7
    mcp23s17_write_reg(MCP23S17_CS2, 0x00, MCP23S17_GPPUA, 0xFF);

    // Expander A (CS1, addr 0x01) - Long 16-pin connector (Columns)
    // First init as all outputs with OLAT=0xFF (HIGH) so the output latches are set,
    // then switch to all inputs (high-impedance) for diodeless-safe scanning.
    mcp23s17_init_expander(MCP23S17_CS1, 0x01, 0x00, 0x00);
    mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_IODIRA, 0xFF);
    mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_IODIRB, 0xFF);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    unselect_cols();
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        wait_us(30); // Let signals settle

        matrix_row_t rows = read_rows();

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = (current_matrix[row] >> col) & 1;
            bool curr_bit = !((rows >> row) & 1);

            if (prev_bit != curr_bit) {
                changed = true;
            }

            if (curr_bit) {
                current_matrix[row] |= (1 << col);
            } else {
                current_matrix[row] &= ~(1 << col);
            }
        }
    }
    unselect_cols();

    return changed;
}

//------------------------------------------------------------------------------
// MCP23S17 Hardware Interface
//------------------------------------------------------------------------------

static void mcp23s17_init_expander(uint8_t cs_pin, uint8_t addr, uint8_t iodir_a, uint8_t iodir_b) {
    // Set I/O direction registers
    mcp23s17_write_reg(cs_pin, addr, MCP23S17_IODIRA, iodir_a);
    mcp23s17_write_reg(cs_pin, addr, MCP23S17_IODIRB, iodir_b);

    // Set output latches HIGH (inactive) so columns default to non-driven state
    if (iodir_a == 0x00) {
        mcp23s17_write_reg(cs_pin, addr, MCP23S17_OLATA, 0xFF);
    }
    if (iodir_b == 0x00) {
        mcp23s17_write_reg(cs_pin, addr, MCP23S17_OLATB, 0xFF);
    }
}

static void mcp23s17_write_reg(uint8_t cs_pin, uint8_t addr, uint8_t reg_addr, uint8_t data) {
    // Start SPI transaction: MSB first, mode 0, divisor 16 (1MHz on 16MHz Pro Micro)
    if (spi_start(cs_pin, false, 0, 16)) {
        // Send command byte (device address + write bit)
        spi_write(MCP23S17_CMD_WRITE(addr));
        // Send register address
        spi_write(reg_addr);
        // Send data
        spi_write(data);
        // End SPI transaction
        spi_stop();
    }
}

static uint8_t mcp23s17_read_reg(uint8_t cs_pin, uint8_t addr, uint8_t reg_addr) {
    uint8_t data = 0;

    // Start SPI transaction: MSB first, mode 0, divisor 16 (1MHz on 16MHz Pro Micro)
    if (spi_start(cs_pin, false, 0, 16)) {
        // Send command byte (device address + read bit)
        spi_write(MCP23S17_CMD_READ(addr));
        // Send register address
        spi_write(reg_addr);
        // Read data
        data = spi_read();
        // End SPI transaction
        spi_stop();
    }

    return data;
}

//------------------------------------------------------------------------------
// Matrix Scanning: Column Selection + Row Reading via Port Expanders
//------------------------------------------------------------------------------

static void select_col(uint8_t col) {
    // Expander A (addr 0x01, columns)
    // For a diodeless matrix, inactive columns must be high-impedance (input mode),
    // NOT driven HIGH. Driving inactive columns HIGH creates sneak paths when two
    // pressed keys share a row (current path: inactive HIGH -> switch -> row -> switch -> active LOW).
    //
    // Sequence:
    //   1. Set ALL columns to input (high-Z) — ensures no old column is still driven
    //   2. Write the output latch (GPIO) with the new column's value (LOW)
    //   3. Set only the active column as output — pin drives the latch value immediately
    //
    // This avoids the glitch where GPIO changes while the old column is still an output,
    // which would briefly drive it HIGH and create a sneak path.

    mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_IODIRA, 0xFF);
    mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_IODIRB, 0xFF);

    if (col < 8) {
        mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_GPIOA, ~(1 << col));
        mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_IODIRA, ~(1 << col));
    } else {
        mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_GPIOB, ~(1 << (col - 8)));
        mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_IODIRB, ~(1 << (col - 8)));
    }
    wait_us(1);
}

static void unselect_cols(void) {
    // Set all columns to input (high-impedance) to avoid contention
    mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_IODIRA, 0xFF);
    mcp23s17_write_reg(MCP23S17_CS1, 0x01, MCP23S17_IODIRB, 0xFF);
}

static matrix_row_t read_rows(void) {
    // Expander B (addr 0x00, rows)
    // Read GPA0-GPA7 from row expander
    uint8_t row_data = mcp23s17_read_reg(MCP23S17_CS2, 0x00, MCP23S17_GPIOA);
    return row_data;
}
