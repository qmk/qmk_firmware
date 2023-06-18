#include <stdint.h>
#include <stdbool.h>

#include "i2c_master.h"
#include "lib/i2c_helpers.h"
#include "lib/pcal6416a/pcal6416a.h"

i2c_status_t pcal_read_pin(pcal_gpio_pin pin, pcal_gpio_state* pin_state) {
    uint8_t input_register = REGISTER_FOR_PIN(pin, INPUT);
    uint8_t register_data;
    RETURN_STATUS_IF_I2C_FAIL(i2c_readReg(PCAL_ADDRESS, input_register, &register_data, 1, 20));

    *pin_state = (register_data >> GET_PIN_NUMBER(pin)) & 1;

    return I2C_STATUS_SUCCESS;
}

i2c_status_t pcal_write_pin(pcal_gpio_pin pin, pcal_gpio_state state) {
    uint8_t output_register = REGISTER_FOR_PIN(pin, OUTPUT);
    return i2c_updateRegBit(PCAL_ADDRESS, output_register, GET_PIN_NUMBER(pin), state, 20);
}

static bool is_input(pcal_gpio_dir dir) {
    if (dir == INPUT_PULLUP || dir == INPUT_PULLDOWN || dir == INPUT) return true;
    return false;
}

i2c_status_t pcal_set_pin_direction(pcal_gpio_pin pin, pcal_gpio_dir dir) {
    uint8_t direction_register = REGISTER_FOR_PIN(pin, CONFIGURATION);
    bool    input              = is_input(dir);
    RETURN_STATUS_IF_I2C_FAIL(i2c_updateRegBit(PCAL_ADDRESS, direction_register, GET_PIN_NUMBER(pin), input, 20));

    if (input) {
        uint8_t enable_biasing_register = REGISTER_FOR_PIN(pin, PULLUP_PULLDOWN_ENABLE);
        bool    biasing                 = (dir == INPUT_PULLUP || dir == INPUT_PULLDOWN);
        RETURN_STATUS_IF_I2C_FAIL(i2c_updateRegBit(PCAL_ADDRESS, enable_biasing_register, GET_PIN_NUMBER(pin), biasing, 20));

        if (biasing) {
            uint8_t biasing_direction_register = REGISTER_FOR_PIN(pin, PULLUP_PULLDOWN_SELECT);
            uint8_t biasing_direction          = (dir == INPUT_PULLUP) ? 1 : 0;
            RETURN_STATUS_IF_I2C_FAIL(i2c_updateRegBit(PCAL_ADDRESS, biasing_direction_register, GET_PIN_NUMBER(pin), biasing_direction, 20));
        }
    }

    return I2C_STATUS_SUCCESS;
}

i2c_status_t set_pin_array_direction(const pcal_gpio_pin* pins, int size, pcal_gpio_dir direction) {
    for (int i = 0; i < size; i++) {
        RETURN_STATUS_IF_I2C_FAIL(pcal_set_pin_direction(pins[i], direction));
    }

    return I2C_STATUS_SUCCESS;
}

i2c_status_t set_pin_array_state(const pcal_gpio_pin* pins, int size, pcal_gpio_state state) {
    for (int i = 0; i < size; i++) {
        RETURN_STATUS_IF_I2C_FAIL(pcal_write_pin(pins[i], state));
    }

    return I2C_STATUS_SUCCESS;
}

i2c_status_t set_pin_array_initial_state(const pcal_gpio_pin* pins, int size, pcal_gpio_state state) {
    for (int i = 0; i < size; i++) {
        RETURN_STATUS_IF_I2C_FAIL(pcal_write_pin(pins[i], state));
        RETURN_STATUS_IF_I2C_FAIL(pcal_set_pin_direction(pins[i], OUTPUT));
    }

    return I2C_STATUS_SUCCESS;
}
