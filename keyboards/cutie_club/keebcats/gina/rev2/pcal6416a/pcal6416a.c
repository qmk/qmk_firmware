#include <stdint.h>
#include <stdbool.h>

#include "i2c_master.h"
#include "lib/i2c_helpers.h"
#include "pcal6416a/pcal6416a.h"

pcal_gpio_state pcal_read_pin(pcal_gpio_pin pin) {
    uint8_t input_register = REGISTER_FOR_PIN(pin, INPUT);
    uint8_t register_data;
    i2c_readReg(PCAL_ADDRESS, input_register, &register_data, 1, 20);

    pcal_gpio_state pin_state = (register_data >> GET_PIN_NUMBER(pin)) & 1;
    return pin_state;
}

void pcal_write_pin(pcal_gpio_pin pin, pcal_gpio_state state) {
    uint8_t output_register = REGISTER_FOR_PIN(pin, OUTPUT);
    i2c_updateRegBit(PCAL_ADDRESS, output_register, GET_PIN_NUMBER(pin), state, 20);
}

static bool is_input(pcal_gpio_dir dir) {
    if(dir == INPUT_PULLUP || dir == INPUT_PULLDOWN || dir == INPUT) return true;
    return false;
}

void pcal_set_pin_direction(pcal_gpio_pin pin, pcal_gpio_dir dir) {
    uint8_t direction_register = REGISTER_FOR_PIN(pin, CONFIGURATION);
    bool input = is_input(dir);
    i2c_updateRegBit(PCAL_ADDRESS, direction_register, GET_PIN_NUMBER(pin), input, 20);

    if(input) {
        uint8_t enable_biasing_register = REGISTER_FOR_PIN(pin, PULLUP_PULLDOWN_ENABLE);
        bool biasing = (dir == INPUT_PULLUP || dir == INPUT_PULLDOWN);
        i2c_updateRegBit(PCAL_ADDRESS, enable_biasing_register, GET_PIN_NUMBER(pin), biasing, 20);

        if (biasing) {
            uint8_t biasing_direction_register = REGISTER_FOR_PIN(pin, PULLUP_PULLDOWN_SELECT);
            uint8_t biasing_direction = (dir == INPUT_PULLUP) ? 1 : 0;
            i2c_updateRegBit(PCAL_ADDRESS, biasing_direction_register, GET_PIN_NUMBER(pin), biasing_direction, 20);
        }
    }
}

void set_pin_array_direction(const pcal_gpio_pin* pins, int size, pcal_gpio_dir direction) {
    for(int i = 0; i < size; i++) {
        pcal_set_pin_direction(pins[i], direction);
    }
}

void set_pin_array_state(const pcal_gpio_pin* pins, int size, pcal_gpio_state state) {
    for(int i = 0; i < size; i++) {
        pcal_write_pin(pins[i], state);
    }
}

void set_pin_array_initial_state(const pcal_gpio_pin* pins, int size, pcal_gpio_state state) {
    for(int i = 0; i < size; i++) {
        pcal_write_pin(pins[i], state);
        pcal_set_pin_direction(pins[i], OUTPUT);
    }
}
