#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "i2c_master.h"
#include "mcp23X17/mcp23X17.h"
#include "print.h"

static const mcp_gpio_pin row_pins[MATRIX_ROWS] = MCP_ROW_PINS;
static const mcp_gpio_pin column_pins[MATRIX_COLS] = MCP_COL_PINS;

static void i2c_updateRegBit(uint8_t devaddr, uint8_t register_to_update, uint8_t bit, uint8_t value, uint16_t timeout) {
    uint8_t register_data;
    i2c_readReg(GPIO_EXPANDER_ADDRESS, register_to_update, &register_data, 1, timeout);

    if(value) {
        register_data |= 1 << bit;
    } else {
        register_data &= ~(1 << bit);
    }

    i2c_writeReg(GPIO_EXPANDER_ADDRESS, register_to_update, &register_data, 1, timeout);
}

static void mcp_set_pin_direction(mcp_gpio_pin pin, mcp_gpio_dir dir) {
    uint8_t register_to_update_direction = BANK0_REGISTER_FOR_PIN(pin, IODIR);

    mcp_gpio_dir normalized_direction = (dir != INPUT_PULLUP) ? dir : INPUT;
    i2c_updateRegBit(GPIO_EXPANDER_ADDRESS, register_to_update_direction, GET_PIN_NUMBER(pin), normalized_direction, 20);

    if (dir == INPUT_PULLUP) {
        uint8_t register_to_update_pullup = BANK0_REGISTER_FOR_PIN(pin, GPPU);
        i2c_updateRegBit(GPIO_EXPANDER_ADDRESS, register_to_update_pullup, GET_PIN_NUMBER(pin), normalized_direction, 20);
    }
}

mcp_gpio_state mcp_read_pin(mcp_gpio_pin pin) {
    uint8_t register_to_read = BANK0_REGISTER_FOR_PIN(pin, GPIO);
    uint8_t register_data;
    i2c_readReg(GPIO_EXPANDER_ADDRESS, register_to_read, &register_data, 1, 20);

    mcp_gpio_state pin_state = (register_data >> GET_PIN_NUMBER(pin)) & 1;

    return pin_state;
}

static void mcp_write_pin(mcp_gpio_pin pin, mcp_gpio_state state) {
    uint8_t register_to_update = BANK0_REGISTER_FOR_PIN(pin, GPIO);

    i2c_updateRegBit(GPIO_EXPANDER_ADDRESS, register_to_update, GET_PIN_NUMBER(pin), state, 20);
}

static bool update_matrix_for_row(uint8_t row, matrix_row_t current_matrix[]) {
    matrix_row_t previous_row_state = current_matrix[row];
    current_matrix[row] = 0;

    mcp_write_pin(row_pins[row], LOW);

    for (uint8_t column = 0; column < MATRIX_COLS; column++) {
        mcp_gpio_pin current_column_pin = column_pins[column];

        if(mcp_read_pin(current_column_pin) == LOW) {
            current_matrix[row] |= (1 << column);
        }
    }

    mcp_write_pin(row_pins[row], HIGH);

    return previous_row_state != current_matrix[row];
}

void matrix_init_custom(void) {
    i2c_init();

    for (uint8_t column = 0; column < MATRIX_COLS; column++)
    {
        mcp_set_pin_direction(column_pins[column], INPUT_PULLUP);
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; row++)
    {
        mcp_set_pin_direction(row_pins[row], OUTPUT);
        mcp_write_pin(row_pins[row], HIGH);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        if(update_matrix_for_row(row, current_matrix)) matrix_has_changed = true;
    }
    return matrix_has_changed;
}
