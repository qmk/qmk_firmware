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
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "matrix.h"
#include "quantum.h"
#include "board.h"
#include "i2c_master.h"

static board_info_t  boards[NUM_BOARDS] = BOARD_INFOS;
static board_info_t* master_board       = NULL;

static bool          board_is_master(board_info_t* board);
static bool          board_is_initialized(board_info_t* board);
static board_info_t* get_board_by_index(uint8_t board_index);
static uint8_t       board_merge_led_config(board_info_t* board, uint8_t iodir);
static uint8_t       board_merge_led_status(board_info_t* board, uint8_t data);
static void          board_master_init(void);
static void          board_slave_init(void);

//
// board interface
//
static void board_select_master_row(board_info_t* board, uint8_t row);
static void board_unselect_master_row(board_info_t* board, uint8_t row);
static void board_unselect_master_rows(board_info_t* board);
static bool board_read_cols_on_master_row(board_info_t* board, matrix_row_t current_matrix[], uint8_t row);
static void board_set_master_led(board_info_t* board, uint8_t led_index, bool status);
static void board_select_slave_row(board_info_t* board, uint8_t row);
static void board_unselect_slave_row(board_info_t* board, uint8_t row);
static void board_unselect_slave_rows(board_info_t* board);
static bool board_read_cols_on_slave_row(board_info_t* board, matrix_row_t current_matrix[], uint8_t row);
static void board_set_slave_led(board_info_t* board, uint8_t led_index, bool status);

static board_interface_t master_interface = {board_select_master_row, board_unselect_master_row, board_unselect_master_rows, board_read_cols_on_master_row, board_set_master_led};
static board_interface_t slave_interface  = {board_select_slave_row, board_unselect_slave_row, board_unselect_slave_rows, board_read_cols_on_slave_row, board_set_slave_led};

static board_interface_t* get_interface(board_info_t* board) {
    if (board_is_master(board)) {
        return &master_interface;
    }
    return &slave_interface;
}

static void board_set_master_led(board_info_t* board, uint8_t led_index, bool status) {
    pin_t pin                    = board->led_pins[led_index];
    board->led_status[led_index] = status;
    setPinOutput(pin);
    status ? writePinHigh(pin) : writePinLow(pin);
}

static void board_set_slave_led(board_info_t* board, uint8_t led_index, bool status) {
    board->led_status[led_index] = status;
    uint8_t iodir                = board_merge_led_config(board, 0xff);
    uint8_t data                 = board_merge_led_status(board, 0x00);
    i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_IODIRB, (const uint8_t*)&iodir, sizeof(iodir), BOARD_I2C_TIMEOUT);
    i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_OLATB, (const uint8_t*)&data, sizeof(data), BOARD_I2C_TIMEOUT);
}

static uint8_t board_merge_led_config(board_info_t* board, uint8_t iodir) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        iodir &= PIN2MASK(board->led_pins[i]);
    }
    return iodir;
}

static bool board_slave_config(board_info_t* board) {
    uint8_t      set   = 0xff;
    uint8_t      clear = 0x00;
    i2c_status_t res   = 0;

    // Set to input
    res = i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_IODIRA, (const uint8_t*)&set, sizeof(set), BOARD_I2C_TIMEOUT);
    if (res < 0) return false;
    // RESTRICTION: LEDs only on PORT B.
    set = board_merge_led_config(board, set);
    res = i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_IODIRB, (const uint8_t*)&set, sizeof(set), BOARD_I2C_TIMEOUT);
    if (res < 0) return false;
    set = 0xff;

    // Pull up for input - enable
    res = i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_GPPUA, (const uint8_t*)&set, sizeof(set), BOARD_I2C_TIMEOUT);
    if (res < 0) return false;
    res = i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_GPPUB, (const uint8_t*)&set, sizeof(set), BOARD_I2C_TIMEOUT);
    if (res < 0) return false;

    // Disable interrupt
    res = i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_GPINTENA, (const uint8_t*)&clear, sizeof(clear), BOARD_I2C_TIMEOUT);
    if (res < 0) return false;
    res = i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_GPINTENB, (const uint8_t*)&clear, sizeof(clear), BOARD_I2C_TIMEOUT);
    if (res < 0) return false;

    // Polarity - same logic
    res = i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_IPOLA, (const uint8_t*)&clear, sizeof(clear), BOARD_I2C_TIMEOUT);
    if (res < 0) return false;
    res = i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_IPOLB, (const uint8_t*)&clear, sizeof(clear), BOARD_I2C_TIMEOUT);
    if (res < 0) return false;

    return true;
}

static void board_slave_init(void) {
    i2c_init();
    _delay_ms(500);

    for (uint8_t i = 0; i < NUM_BOARDS; i++) {
        board_info_t* board = &boards[i];
        if (board_is_master(board)) {
            continue;
        }
        if (i2c_start(EXPANDER_ADDR(board->i2c_address), BOARD_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
            continue;
        }
        i2c_stop();
        if (board_slave_config(board)) {
            board->initialized = true;
        }
    }
}

inline bool board_is_master(board_info_t* board) {
    if (board) {
        return board->master;
    }
    return false;
}

inline uint8_t matrix2board(uint8_t row) { return row % NUM_ROWS; }

inline uint8_t board_index(uint8_t row) { return row / NUM_ROWS; }

static board_info_t* get_master_board(void) {
    if (master_board == NULL) {
        for (uint8_t i = 0; i < NUM_BOARDS; i++) {
            if (boards[i].master) {
                master_board = &boards[i];
                return master_board;
            }
        }
    }
    return NULL;
}

inline bool board_is_initialized(board_info_t* board) { return board == NULL ? false : board->initialized; }

static board_info_t* get_board_by_index(uint8_t board_index) {
    if (board_index >= 0 && board_index < NUM_BOARDS) {
        if (!board_is_initialized(&boards[board_index])) {
            return NULL;
        }
        return &boards[board_index];
    }
    return NULL;
}

static board_info_t* get_board(uint8_t row) {
    uint8_t idx = board_index(row);
    if (idx >= 0 && idx < NUM_BOARDS) {
        if (!board_is_initialized(&boards[idx])) {
            return NULL;
        }
        return &boards[idx];
    }
    return NULL;
}

static uint8_t board_merge_led_status(board_info_t* board, uint8_t data) {
    if (!board_is_initialized(board)) {
        return data;
    }
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        bool status = board->led_status[i];
        if (status) {
            data |= (uint8_t)1 << PIN2INDEX(board->led_pins[i]);
        } else {
            data &= PIN2MASK(board->led_pins[i]);
        }
    }
    return data;
}

//
// Functions for slave
//
static uint8_t board_read_slave_cols(board_info_t* board) {
    if (!board_is_initialized(board)) {
        return 0xff;
    }
    uint8_t      data = 0xff;
    i2c_status_t res  = i2c_readReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_GPIOA, &data, sizeof(data), BOARD_I2C_TIMEOUT);
    return (res < 0) ? 0xff : data;
}

static void board_select_slave_row(board_info_t* board, uint8_t board_row) {
    if (!board_is_initialized(board)) {
        return;
    }
    uint8_t pin    = board->row_pins[board_row];
    uint8_t iodir  = board_merge_led_config(board, PIN2MASK(pin));
    uint8_t status = board_merge_led_status(board, PIN2MASK(pin));
    i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_IODIRB, (const uint8_t*)&iodir, sizeof(iodir), BOARD_I2C_TIMEOUT);
    i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_OLATB, (const uint8_t*)&status, sizeof(status), BOARD_I2C_TIMEOUT);
}

static void board_unselect_slave_rows(board_info_t* board) {
    if (!board_is_initialized(board)) {
        return;
    }
    uint8_t iodir = board_merge_led_config(board, 0xff);
    uint8_t data  = board_merge_led_status(board, 0x00);
    i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_IODIRB, (const uint8_t*)&iodir, sizeof(iodir), BOARD_I2C_TIMEOUT);
    i2c_writeReg(EXPANDER_ADDR(board->i2c_address), EXPANDER_OLATB, (const uint8_t*)&data, sizeof(data), BOARD_I2C_TIMEOUT);
}

static void board_unselect_slave_row(board_info_t* board, uint8_t board_row) { board_unselect_slave_rows(board); }

/*
 * row : matrix row (not board row)
 */
static bool board_read_cols_on_slave_row(board_info_t* board, matrix_row_t current_matrix[], uint8_t row) {
    matrix_row_t last_row_value = current_matrix[row];
    current_matrix[row]         = 0;

    uint8_t board_row = matrix2board(row);
    board_select_slave_row(board, board_row);
    wait_us(30);

    uint8_t cols = board_read_slave_cols(board);
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        uint8_t pin       = board->col_pins[col_index];
        uint8_t pin_state = cols & PIN2BIT(pin);
        current_matrix[row] |= pin_state ? 0 : (1 << col_index);
    }
    board_unselect_slave_row(board, board_row);

    return (last_row_value != current_matrix[row]);
}

//
// Functions for master board
//
static void board_select_master_row(board_info_t* board, uint8_t board_row) {
    setPinOutput(board->row_pins[board_row]);
    writePinLow(board->row_pins[board_row]);
}

static void board_unselect_master_row(board_info_t* board, uint8_t board_row) { setPinInputHigh(board->row_pins[board_row]); }

static void board_unselect_master_rows(board_info_t* board) {
    if (!board) {
        return;
    }
    for (uint8_t x = 0; x < NUM_ROWS; x++) {
        setPinInput(board->row_pins[x]);
    }
}

/*
 * row : matrix row (not board row)
 */
static bool board_read_cols_on_master_row(board_info_t* board, matrix_row_t current_matrix[], uint8_t row) {
    matrix_row_t last_row_value = current_matrix[row];
    current_matrix[row]         = 0;

    uint8_t board_row = matrix2board(row);
    board_select_master_row(board, board_row);
    wait_us(30);

    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        uint8_t pin_state = readPin(board->col_pins[col_index]);
        current_matrix[row] |= pin_state ? 0 : (1 << col_index);
    }
    board_unselect_master_row(board, board_row);

    return (last_row_value != current_matrix[row]);
}

static void board_master_init(void) {
    board_info_t* board = get_master_board();
    if (!board) {
        return;
    }
    for (uint8_t x = 0; x < NUM_COLS; x++) {
        setPinInputHigh(board->col_pins[x]);
    }
    board->initialized = true;
}

static void board_setup(void) {
    for (uint8_t i = 0; i < NUM_BOARDS; i++) {
        board_info_t* board = &boards[i];
        board->interface    = get_interface(board);
    }
}

//
// Public functions
//

// NOTE: Do not call this while matrix scanning...
void board_set_led_by_index(uint8_t board_index, uint8_t led_index, bool status) {
    board_info_t* board = get_board_by_index(board_index);
    if (!board) return;
    if (led_index < 0 || led_index > NUM_LEDS) return;
    (*board->interface->set_led)(board, led_index, status);
}

bool board_read_cols_on_row(matrix_row_t current_matrix[], uint8_t row) {
    bool          result = false;
    board_info_t* board  = get_board(row);
    if (!board) {
        return false;
    }
    result = (*board->interface->read_cols_on_row)(board, current_matrix, row);
    return result;
}

void board_select_row(uint8_t row) {
    board_info_t* board = get_board(row);
    if (!board) {
        return;
    }
    uint8_t board_row = matrix2board(row);
    (*board->interface->select_row)(board, board_row);
}

void board_unselect_row(uint8_t row) {
    board_info_t* board = get_board(row);
    if (!board) {
        return;
    }
    uint8_t board_row = matrix2board(row);
    (*board->interface->unselect_row)(board, board_row);
}

void board_unselect_rows(void) {
    for (uint8_t i = 0; i < NUM_BOARDS; i++) {
        board_info_t* board = &boards[i];
        (*board->interface->unselect_rows)(board);
    }
}

void board_init(void) {
    board_setup();
    board_master_init();
    board_slave_init();
    board_unselect_rows();
}
