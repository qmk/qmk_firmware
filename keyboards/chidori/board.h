/* Copyright 2019 ENDO Katsuhiro <ka2hiro@kagizaraya.jp>
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
#pragma once

#define NUM_ROWS 4
#define NUM_COLS 6
#define NUM_LEDS 2

#define LED_GREEN 0
#define LED_YELLOW 1

typedef struct board_info_t      board_info_t;
typedef struct board_interface_t board_interface_t;

struct board_info_t {
    bool               master;
    bool               initialized;
    uint8_t            i2c_address;
    pin_t              row_pins[NUM_ROWS];
    pin_t              col_pins[NUM_COLS];
    pin_t              led_pins[NUM_LEDS];
    bool               led_status[NUM_LEDS];
    board_interface_t* interface;
};

struct board_interface_t {
    void (*select_row)(board_info_t* board, uint8_t row);
    void (*unselect_row)(board_info_t* board, uint8_t row);
    void (*unselect_rows)(board_info_t* board);
    bool (*read_cols_on_row)(board_info_t* board, matrix_row_t current_matrix[], uint8_t row);
    void (*set_led)(board_info_t* board, uint8_t led_index, bool status);
};

#define BOARD_I2C_TIMEOUT 20

#define GPA0 0x00
#define GPA1 0x01
#define GPA2 0x02
#define GPA3 0x03
#define GPA4 0x04
#define GPA5 0x05
#define GPA6 0x06
#define GPA7 0x07
#define GPB0 0x08
#define GPB1 0x09
#define GPB2 0x0A
#define GPB3 0x0B
#define GPB4 0x0C
#define GPB5 0x0D
#define GPB6 0x0E
#define GPB7 0x0F

//#define PORTA   0x00
//#define PORTB   0x01
#define PORT_MASK 0x08
#define PIN_MASK 0x07

#define PIN2REGISTER(reg, pin) (reg & ((pin & PORT_MASK) >> 3))
#define PIN2PORT(pin) ((pin & PORT_MASK) >> 3)
#define PIN2MASK(pin) (~(1 << PIN2INDEX(pin)))
#define PIN2INDEX(pin) (pin & ~PORT_MASK)
#define PIN2BIT(pin) (1 << PIN2INDEX(pin))

#define EXPANDER_ADDR(addr) (addr << 1)

#define EXPANDER_IODIR(pin) (0x00 | PIN2PORT(pin))
#define EXPANDER_IPOL(pin) (0x02 | PIN2PORT(pin))
#define EXPANDER_GPINTEN(pin) (0x04 | PIN2PORT(pin))
#define EXPANDER_DEFVAL(pin) (0x06 | PIN2PORT(pin))
#define EXPANDER_INTCON(pin) (0x08 | PIN2PORT(pin))
#define EXPANDER_IOCON(pin) (0x0A | PIN2PORT(pin))
#define EXPANDER_GPPU(pin) (0x0C | PIN2PORT(pin))
#define EXPANDER_INTF(pin) (0x0E | PIN2PORT(pin))
#define EXPANDER_INTCAP(pin) (0x10 | PIN2PORT(pin))
#define EXPANDER_GPIO(pin) (0x12 | PIN2PORT(pin))
#define EXPANDER_OLAT(pin) (0x14 | PIN2PORT(pin))

#define EXPANDER_IODIRA 0x00
#define EXPANDER_IODIRB 0x01
#define EXPANDER_IPOLA 0x02
#define EXPANDER_IPOLB 0x03
#define EXPANDER_GPINTENA 0x04
#define EXPANDER_GPINTENB 0x05
#define EXPANDER_DEFVALA 0x06
#define EXPANDER_DEFVALB 0x07
#define EXPANDER_INTCONA 0x08
#define EXPANDER_INTCONB 0x09
#define EXPANDER_IOCONA 0x0A
#define EXPANDER_IOCONB 0x0B
#define EXPANDER_GPPUA 0x0C
#define EXPANDER_GPPUB 0x0D
#define EXPANDER_INTFA 0x0E
#define EXPANDER_INTFB 0x0F
#define EXPANDER_INTCAPA 0x10
#define EXPANDER_INTCAPB 0x11
#define EXPANDER_GPIOA 0x12
#define EXPANDER_GPIOB 0x13
#define EXPANDER_OLATA 0x14
#define EXPANDER_OLATB 0x15

//
// Default board config
//
#ifndef NUM_BOARDS
#    define NUM_BOARDS 2
#endif

// clang-format off
#ifndef BOARD_INFOS
#if NUM_BOARDS == 2
#define BOARD_INFOS \
{ \
    { \
        true, \
        false, \
        0x00, \
        { D4, D5, D6, D7 }, \
        { D1, D0, C3, C2, C1, C0 }, \
        { B1, B2 }, \
        { false, false }, \
        NULL \
    }, \
    { \
        false, \
        false, \
        0x20, \
        { GPB4, GPB5, GPB6, GPB7 }, \
        { GPA7, GPA6, GPA5, GPA4, GPA3, GPA2 }, \
        { GPB0, GPB1 }, \
        { false, false }, \
        NULL \
    }, \
}
#elif NUM_BOARDS == 3
#define BOARD_INFOS \
{ \
    { \
        true, \
        false, \
        0x00, \
        { D4, D5, D6, D7 }, \
        { D1, D0, C3, C2, C1, C0 }, \
        { B1, B2 }, \
        { false, false }, \
        NULL \
    }, \
    { \
        false, \
        false, \
        0x20, \
        { GPB4, GPB5, GPB6, GPB7 }, \
        { GPA7, GPA6, GPA5, GPA4, GPA3, GPA2 }, \
        { GPB0, GPB1 }, \
        { false, false }, \
        NULL \
    }, \
    { \
        false, \
        false, \
        0x21, \
        { GPB4, GPB5, GPB6, GPB7 }, \
        { GPA7, GPA6, GPA5, GPA4, GPA3, GPA2 }, \
        { GPB0, GPB1 }, \
        { false, false }, \
        NULL \
    }, \
}
#endif
#endif
// clang-format on

void board_set_led_by_index(uint8_t board_index, uint8_t led_index, bool status);
bool board_read_cols_on_row(matrix_row_t current_matrix[], uint8_t row);
void board_select_row(uint8_t row);
void board_unselect_row(uint8_t row);
void board_unselect_rows(void);
void board_init(void);
