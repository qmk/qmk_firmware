#include "is31fl3743a-simple.h"
#include <string.h>
#include "i2c_master.h"
#include "wait.h"

#define IS31FL3743A_PWM_REGISTER_COUNT 198
#define IS31FL3743A_SCALING_REGISTER_COUNT 198

#ifndef IS31FL3743A_I2C_TIMEOUT
#    define IS31FL3743A_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3743A_I2C_PERSISTENCE
#    define IS31FL3743A_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3743A_CONFIGURATION
#    define IS31FL3743A_CONFIGURATION 0x01
#endif

#ifndef IS31FL3743A_SW_PULLDOWN
#    define IS31FL3743A_SW_PULLDOWN IS31FL3743A_PDR_2K_OHM_SW_OFF
#endif

#ifndef IS31FL3743A_CS_PULLUP
#    define IS31FL3743A_CS_PULLUP IS31FL3743A_PUR_2K_OHM_CS_OFF
#endif

#ifndef IS31FL3743A_GLOBAL_CURRENT
#    define IS31FL3743A_GLOBAL_CURRENT 0xFF
#endif

#ifndef IS31FL3743A_SYNC_1
#    define IS31FL3743A_SYNC_1 IS31FL3743A_SYNC_NONE
#endif
#ifndef IS31FL3743A_SYNC_2
#    define IS31FL3743A_SYNC_2 IS31FL3743A_SYNC_NONE
#endif
#ifndef IS31FL3743A_SYNC_3
#    define IS31FL3743A_SYNC_3 IS31FL3743A_SYNC_NONE
#endif
#ifndef IS31FL3743A_SYNC_4
#    define IS31FL3743A_SYNC_4 IS31FL3743A_SYNC_NONE
#endif

uint8_t i2c_transfer_buffer[20] = {0xFF};

uint8_t g_pwm_buffer[IS31FL3743A_DRIVER_COUNT][IS31FL3743A_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[IS31FL3743A_DRIVER_COUNT]        = {false};
bool    g_scaling_registers_update_required[IS31FL3743A_DRIVER_COUNT] = {false};

uint8_t g_scaling_registers[IS31FL3743A_DRIVER_COUNT][IS31FL3743A_SCALING_REGISTER_COUNT];

void is31fl3743a_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    i2c_transfer_buffer[0] = reg;
    i2c_transfer_buffer[1] = data;

#if IS31FL3743A_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3743A_I2C_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, i2c_transfer_buffer, 2, IS31FL3743A_I2C_TIMEOUT) == 0) break;
    }
#else
    i2c_transmit(addr << 1, i2c_transfer_buffer, 2, IS31FL3743A_I2C_TIMEOUT);
#endif
}

void is31fl3743a_select_page(uint8_t addr, uint8_t page) {
    is31fl3743a_write_register(addr, IS31FL3743A_REG_COMMAND_WRITE_LOCK, IS31FL3743A_COMMAND_WRITE_LOCK_MAGIC);
    is31fl3743a_write_register(addr, IS31FL3743A_REG_COMMAND, page);
}

void is31fl3743a_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // Assumes page 0 is already selected.
    // If any of the transactions fails function returns false.
    // Transmit PWM registers in 12 transfers of 16 bytes.
    // i2c_transfer_buffer[] is 20 bytes

    // Iterate over the pwm_buffer contents at 16 byte intervals.
    for (int i = 0; i < IS31FL3743A_PWM_REGISTER_COUNT; i += 16) {
        i2c_transfer_buffer[0] = i + 1;
        // Copy the data from i to i+15.
        // Device will auto-increment register for data after the first byte
        // Thus this sets registers 0x00-0x0F, 0x10-0x1F, etc. in one transfer.
        memcpy(i2c_transfer_buffer + 1, pwm_buffer + i, 16);

#if IS31FL3743A_I2C_PERSISTENCE > 0
        for (uint8_t i = 0; i < IS31FL3743A_I2C_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, i2c_transfer_buffer, 17, IS31FL3743A_I2C_TIMEOUT) != 0) break;
        }
#else
        i2c_transmit(addr << 1, i2c_transfer_buffer, 17, IS31FL3743A_I2C_TIMEOUT);
#endif
    }
}

void is31fl3743a_init_drivers(void) {
    i2c_init();

    is31fl3743a_init(IS31FL3743A_I2C_ADDRESS_1, IS31FL3743A_SYNC_1);
#if defined(IS31FL3743A_I2C_ADDRESS_2)
    is31fl3743a_init(IS31FL3743A_I2C_ADDRESS_2, IS31FL3743A_SYNC_2);
#    if defined(IS31FL3743A_I2C_ADDRESS_3)
    is31fl3743a_init(IS31FL3743A_I2C_ADDRESS_3, IS31FL3743A_SYNC_3);
#        if defined(IS31FL3743A_I2C_ADDRESS_4)
    is31fl3743a_init(IS31FL3743A_I2C_ADDRESS_4, IS31FL3743A_SYNC_4);
#        endif
#    endif
#endif

    for (int i = 0; i < IS31FL3743A_LED_COUNT; i++) {
        is31fl3743a_set_scaling_register(i, 0xFF);
    }

    is31fl3743a_update_scaling_registers(IS31FL3743A_I2C_ADDRESS_1, 0);
#if defined(IS31FL3743A_I2C_ADDRESS_2)
    is31fl3743a_update_scaling_registers(IS31FL3743A_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3743A_I2C_ADDRESS_3)
    is31fl3743a_update_scaling_registers(IS31FL3743A_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3743A_I2C_ADDRESS_4)
    is31fl3743a_update_scaling_registers(IS31FL3743A_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}

void is31fl3743a_init(uint8_t addr, uint8_t sync) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    is31fl3743a_select_page(addr, IS31FL3743A_COMMAND_SCALING);

    // Turn off all LEDs.
    for (int i = 0; i < IS31FL3743A_SCALING_REGISTER_COUNT; i++) {
        is31fl3743a_write_register(addr, i + 1, 0x00);
    }

    is31fl3743a_select_page(addr, IS31FL3743A_COMMAND_PWM);

    for (int i = 0; i < IS31FL3743A_PWM_REGISTER_COUNT; i++) {
        is31fl3743a_write_register(addr, i + 1, 0x00);
    }

    is31fl3743a_select_page(addr, IS31FL3743A_COMMAND_FUNCTION);

    is31fl3743a_write_register(addr, IS31FL3743A_FUNCTION_REG_PULLDOWNUP, (IS31FL3743A_SW_PULLDOWN << 4) | IS31FL3743A_CS_PULLUP);
    is31fl3743a_write_register(addr, IS31FL3743A_FUNCTION_REG_GLOBAL_CURRENT, IS31FL3743A_GLOBAL_CURRENT);
    is31fl3743a_write_register(addr, IS31FL3743A_FUNCTION_REG_SPREAD_SPECTRUM, (sync & 0b11) << 6);
    is31fl3743a_write_register(addr, IS31FL3743A_FUNCTION_REG_CONFIGURATION, IS31FL3743A_CONFIGURATION);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3743a_set_value(int index, uint8_t value) {
    is31fl3743a_led_t led;
    if (index >= 0 && index < IS31FL3743A_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3743a_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.v] == value) {
            return;
        }
        g_pwm_buffer_update_required[led.driver] = true;
        g_pwm_buffer[led.driver][led.v]          = value;
    }
}

void is31fl3743a_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3743A_LED_COUNT; i++) {
        is31fl3743a_set_value(i, value);
    }
}

void is31fl3743a_set_scaling_register(uint8_t index, uint8_t value) {
    is31fl3743a_led_t led;
    memcpy_P(&led, (&g_is31fl3743a_leds[index]), sizeof(led));

    g_scaling_registers[led.driver][led.v] = value;

    g_scaling_registers_update_required[led.driver] = true;
}

void is31fl3743a_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        is31fl3743a_select_page(addr, IS31FL3743A_COMMAND_PWM);

        is31fl3743a_write_pwm_buffer(addr, g_pwm_buffer[index]);
    }

    g_pwm_buffer_update_required[index] = false;
}

void is31fl3743a_update_scaling_registers(uint8_t addr, uint8_t index) {
    if (g_scaling_registers_update_required[index]) {
        is31fl3743a_select_page(addr, IS31FL3743A_COMMAND_SCALING);

        for (int i = 0; i < IS31FL3743A_SCALING_REGISTER_COUNT; i++) {
            is31fl3743a_write_register(addr, i + 1, g_scaling_registers[index][i]);
        }
        g_scaling_registers_update_required[index] = false;
    }
}

void is31fl3743a_flush(void) {
    is31fl3743a_update_pwm_buffers(IS31FL3743A_I2C_ADDRESS_1, 0);
#if defined(IS31FL3743A_I2C_ADDRESS_2)
    is31fl3743a_update_pwm_buffers(IS31FL3743A_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3743A_I2C_ADDRESS_3)
    is31fl3743a_update_pwm_buffers(IS31FL3743A_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3743A_I2C_ADDRESS_4)
    is31fl3743a_update_pwm_buffers(IS31FL3743A_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}
