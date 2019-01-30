/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2019 Clueboard
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


#ifndef IS31FL3235A_DRIVER_H
#define IS31FL3235A_DRIVER_H


// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b0111111 AD <-> VCC
// 0b0111110 AD <-> SDA
// 0b0111101 AD <-> SCL
// 0b0111100 AD <-> GND
#ifndef IS31FL3235A_COUNT
    #define IS31FL3235A_COUNT 1
#endif
#ifndef IS31FL3235A_DRIVER_ADDR_1
    #define IS31FL3235A_DRIVER_ADDR_1 0b0111111
    //#define IS31FL3235A_DRIVER_ADDR_1 0x7E
#endif
#ifndef IS31FL3235A_DRIVER_ADDR_2
    #define IS31FL3235A_DRIVER_ADDR_2 0b0111110
#endif
#ifndef IS31FL3235A_DRIVER_ADDR_3
    #define IS31FL3235A_DRIVER_ADDR_3 0b0111101
#endif
#ifndef IS31FL3235A_DRIVER_ADDR_4
    #define IS31FL3235A_DRIVER_ADDR_4 0b0111100
#endif

// This is the max number of LEDs this driver supports per IC
#define IS31FL3235A_LED_MAX 28
#ifndef IS31FL3235A_LED_COUNT
    #define IS31FL3235A_LED_COUNT IS31FL3235A_LED_MAX
#endif

// Registers we will need to write to
#define ISSI_REG_SHUTDOWN 0x00        // Control the software shutdown state of the controller
#define ISSI_REG_GLOBAL_CONTROL 0x4A  // Write 0 for normal operation, 1 to shutdown all LEDs
#define ISSI_REG_OUTPUT_FREQ 0x4B     // Write 0 for 3kHz PWM, 1 for 22kHz
#define ISSI_REG_RESET_REG 0x4F       // Write 0 to reset all registers to default value


void IS31FL3235A_init(uint8_t addr);
void IS31FL3235A_write_register(uint8_t addr, uint8_t reg, uint8_t data);
void IS31FL3235A_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer);

void IS31FL3235A_set_value(int index, uint8_t value);
void IS31FL3235A_set_value_all(uint8_t value);

void IS31FL3235A_set_led_control_register(uint8_t index, bool value);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void IS31FL3235A_update_pwm_buffers(uint8_t addr, uint8_t index);
void IS31FL3235A_update_led_control_registers(uint8_t addr, uint8_t index);

// The address for each LED in the is31fl3235a's Control Register
enum control_register {
    CR_OUT1 = 0x2A,
    CR_OUT2,
    CR_OUT3,
    CR_OUT4,
    CR_OUT5,
    CR_OUT6,
    CR_OUT7,
    CR_OUT8,
    CR_OUT9,
    CR_OUT10,
    CR_OUT11,
    CR_OUT12,
    CR_OUT13,
    CR_OUT14,
    CR_OUT15,
    CR_OUT16,
    CR_OUT17,
    CR_OUT18,
    CR_OUT19,
    CR_OUT20,
    CR_OUT21,
    CR_OUT22,
    CR_OUT23,
    CR_OUT24,
    CR_OUT25,
    CR_OUT26,
    CR_OUT27,
    CR_OUT28
};

// The address for each LED in the is31fl3235a's PWM Register
enum pwm_register {
    OUT1 = 0x05,
    OUT2,
    OUT3,
    OUT4,
    OUT5,
    OUT6,
    OUT7,
    OUT8,
    OUT9,
    OUT10,
    OUT11,
    OUT12,
    OUT13,
    OUT14,
    OUT15,
    OUT16,
    OUT17,
    OUT18,
    OUT19,
    OUT20,
    OUT21,
    OUT22,
    OUT23,
    OUT24,
    OUT25,
    OUT26,
    OUT27,
    OUT28
};

#endif // IS31FL3235A_DRIVER_H
