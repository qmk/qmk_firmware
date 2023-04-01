/* Copyright 2023 Purdea Andrei
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

#include "quantum.h"
#include <hardware/spi.h>
#include <hardware/gpio.h>
#include <hardware/structs/pads_qspi.h>

#define SHIFTREG_SHLD GP27

matrix_row_t previous_matrix[MATRIX_ROWS];

static inline void setPinOutput_writeLow(pin_t pin) {
    setPinOutput(pin);
    writePinLow(pin);
}

void matrix_init_custom(void) {
    for (int i=0; i<=7; i++)
    {
        setPinInputHigh(i);
    }
    for (int i=8; i<=19; i++)
    {
        writePinLow(i);
        setPinInputHigh(i);
    }
    spi_init(spi1, 5000000);
    spi_cpol_t cccpol = 1;
    spi_cpha_t cccpha = 0;
    spi_set_format(spi1, 8, cccpol, cccpha, SPI_MSB_FIRST);
    gpio_set_function(26, GPIO_FUNC_SPI); // SCK
    gpio_set_function(24, GPIO_FUNC_SPI); // RX (MISO)
    writePinLow(SHIFTREG_SHLD);
    setPinOutput(SHIFTREG_SHLD);

    for (int gpio=0;gpio<NUM_BANK0_GPIOS;gpio++) {
        gpio_set_drive_strength(gpio, GPIO_DRIVE_STRENGTH_2MA);
    }

    for (int gpio=0;gpio<NUM_QSPI_GPIOS;gpio++) {
        pads_qspi_hw->io[gpio] &= ~((3 << 4) | (1 << 0));
    }

}

bool matrix_has_it_changed(const matrix_row_t current_matrix[]) {
    bool changed = false;
    for (uint8_t row=0; row<MATRIX_ROWS; row++)
    {
        if (previous_matrix[row] != current_matrix[row]) changed = true;
        previous_matrix[row] = current_matrix[row];
    }
    return changed;
}

#ifdef DONT_USE_LOOKUP_TABLE_SOLUTION
// The following is about twice as slow as the lookup table solution:
uint8_t reverse_bitorder(uint8_t value) {
    const uint8_t evenbits = 0b01010101;
    const uint8_t groups_of_two_bits = 0b00110011;
    value = ((value & evenbits) << 1) |
            ((value >> 1) & evenbits);
    value = ((value & groups_of_two_bits) << 2) |
            ((value >> 2) & groups_of_two_bits);
    value = ((value & 0b00001111) << 4) |
            (value >> 4);
    return value;
}
#else
/*
# reverse_bits_lookup_table was generated with the following python script:
def rev(value):
    evenbits = 0b01010101
    groups_of_two_bits = 0b00110011
    value = ((value & evenbits) << 1) | \
            ((value >> 1) & evenbits)
    value = ((value & groups_of_two_bits) << 2) | \
            ((value >> 2) & groups_of_two_bits)
    value = ((value & 0b00001111) << 4) | \
            (value >> 4)
    return value


vals = [f"0x{rev(i):02x}" for i in range(256)]
while vals:
    print("    " + (", ".join(vals[:10])) + ",")
    del vals[:10]
*/

const uint8_t reverse_bits_lookup_table[] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90,
    0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0, 0x08, 0x88, 0x48, 0xc8,
    0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8,
    0x78, 0xf8, 0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4, 0x0c, 0x8c,
    0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc,
    0x3c, 0xbc, 0x7c, 0xfc, 0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2,
    0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a,
    0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa, 0x06, 0x86, 0x46, 0xc6,
    0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6,
    0x76, 0xf6, 0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x01, 0x81,
    0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1,
    0x31, 0xb1, 0x71, 0xf1, 0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9,
    0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95,
    0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, 0x0d, 0x8d, 0x4d, 0xcd,
    0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd,
    0x7d, 0xfd, 0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3, 0x0b, 0x8b,
    0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb,
    0x3b, 0xbb, 0x7b, 0xfb, 0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7,
    0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f,
    0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

uint8_t reverse_bitorder(uint8_t value) {
    return reverse_bits_lookup_table[value];
}
#endif

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    uint8_t data;
    for (int row=0; row<12; row++) {
        setPinOutput_writeLow(8 + row);
        matrix_output_select_delay();
        writePinHigh(SHIFTREG_SHLD);
        uint8_t high_byte = gpio_get_all() & 0xff;
        setPinInputHigh(8 + row);
        spi_read_blocking(spi1, 0, &data, 1);
        writePinLow(SHIFTREG_SHLD);
        matrix_row_t current_row_value = ~(reverse_bitorder(data) | (reverse_bitorder(high_byte) << 8));
        matrix_output_unselect_delay(row, current_row_value != 0);
        current_matrix[row] = current_row_value;
    }
    return matrix_has_it_changed(current_matrix);
}
