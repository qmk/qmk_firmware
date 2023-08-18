/* Copyright 2023 ebastler and elpekenin
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

#include "pca9555.h"
#include "quantum.h"

// PCA9555 i2c address, 0x20: A0 = 0, A1 = 0, A2 = 0
#define IC1 0x20

// Define how long to wait to reach the IO expander after connection loss again
// Since this board is modular, it should not spam unnecessary i2c requests if used without a module
#define RETRY_TIMESPAN 2000

typedef enum {
    PLUGGED,
    DOUBTFUL,
    UNPLUGGED
} expander_status_t;

void pca9555_setup(void) {
    // Initialize the expander, no need to set ports to inputs as that is the default behavior
    pca9555_init(IC1);
}

void matrix_init_custom(void) {
    // Encoder pushbutton on the MCU is connected to PD2
    setPinInputHigh(D2);
    pca9555_setup();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    static expander_status_t status      = DOUBTFUL;
    static uint32_t          retry_timer = 0;

    // initialize one byte filled with 1
    uint8_t pin_states = 0xFF;
    
    
    if (status != UNPLUGGED || timer_elapsed32(retry_timer) > RETRY_TIMESPAN) {
        // If the chip was unplugged before, it needs to be re-initialized
        if(status==UNPLUGGED) {
            pca9555_setup();
        }
        // Read the entire port into this byte, 1 = not pressed, 0 = pressed
        bool ret = pca9555_readPins(IC1, PCA9555_PORT0, &pin_states);

        // Update state
        if (ret) {
            status = PLUGGED;
        } else {
            switch (status) {
                case PLUGGED:
                    status = DOUBTFUL;
                    break;

                case DOUBTFUL:
                    status = UNPLUGGED;
                    break;

                // If we've diagnosed as unplugged, update timer to not read I2C
                case UNPLUGGED:
                    retry_timer = timer_read32();
            }
        }
    }

    // Shift pin states by 1 to make room for the switch connected to the MCU, then OR them together and invert (as QMK uses inverted logic compared to the electrical levels)
    matrix_row_t data = ~(pin_states << 1 | readPin(D2));

    bool changed = current_matrix[0] != data;
    current_matrix[0] = data;

    return changed;
}