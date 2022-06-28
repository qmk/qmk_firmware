#include QMK_KEYBOARD_H
#include "i2c_master.h"

extern i2c_status_t mcp23018_status;
#define I2C_TIMEOUT 1000

// For a better understanding of the i2c protocol, this is a good read:
// https://www.robot-electronics.co.uk/i2c-tutorial

// I2C address:
// http://ww1.microchip.com/downloads/en/devicedoc/22103a.pdf
// All address pins of the mcp23018 are connected to the ground
// | 0  | 1  | 0  | 0  | A2 | A1 | A0 |
// | 0  | 1  | 0  | 0  | 0  | 0  | 0  |
#define I2C_ADDR 0b0100000
#define I2C_ADDR_WRITE ((I2C_ADDR << 1) | I2C_WRITE)
#define I2C_ADDR_READ ((I2C_ADDR << 1) | I2C_READ)

// Register addresses with IOCON.BANK = 0
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C  // GPIO pull-up resistor register
#define GPPUB 0x0D
#define GPIOA 0x12  // general purpose i/o port register (write modifies OLAT)
#define GPIOB 0x13
#define OLATA 0x14  // output latch register
#define OLATB 0x15

#define ROW_POS { 0b01000000, 0b10000000, 0b01000000, 0b10000000, 0b00000100, 0b00010000, 0b00100000, 0b00000010, 0b00001000 }

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = I2C_ADDR;

uint8_t init_mcp23018(void) {
    print("starting init");
    mcp23018_status = I2C_ADDR;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        wait_ms(I2C_TIMEOUT);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    // This means: We are reading GPIOB 0-5
    // This means: we will write to GPIOA 0-7 and GPIOB 6&7 (in select_rows) 
    uint8_t buf[]   = {IODIRA, 0b00000000, 0b00111111};
    mcp23018_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);
    if (!mcp23018_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        // This means: we will read all the bits on GPIOA
        // This means: we will write to the pins 0-4 on GPIOB (in select_rows)
        uint8_t pullup_buf[] = {GPPUA, 0b00000000, 0b00111111};
        mcp23018_status      = i2c_transmit(I2C_ADDR_WRITE, pullup_buf, sizeof(pullup_buf), I2C_TIMEOUT);
    }
    return mcp23018_status;
}

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];  // debounced values

static matrix_row_t read_cols(void);
static void select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;

void matrix_init_custom(void) {
    // initialize row and col
    mcp23018_status = init_mcp23018();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}


void matrix_power_up(void) {
    // initialize row and col
    mcp23018_status = init_mcp23018();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}


// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_matrix_row(matrix_row_t current_matrix[], uint8_t index) {
    matrix_row_t temp = read_cols(index);
    if (current_matrix[index] != temp) {
        current_matrix[index] = temp;
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (mcp23018_status) {  // if there was an error
        if (++mcp23018_reset_loop == 0) {
            dprint("Trying to reset MCP23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                dprint("MCP23018 Not responding\n");
            } else {
                dprint("MCP23018 Attached\n");
            }
        }
    }

    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);

        changed |= store_matrix_row(current_matrix, i);

    }

    return changed;
}


static matrix_row_t read_cols(void) {
    if (mcp23018_status) {  // if there was an error
        return 0;
    } else {
        uint8_t buf[]   = {GPIOB};
        mcp23018_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);
        // We read all the pins on GPIOB.
        // The initial state was all ones and any depressed key at a given column for the currently selected row will have its bit flipped to zero.
        // The return value is a row as represented in the generic matrix code were the rightmost bits represent the lower columns and zeroes represent non-depressed keys while ones represent depressed keys.
        uint8_t data[] = {0};
        if (!mcp23018_status) {
            mcp23018_status = i2c_receive(I2C_ADDR_READ, data, sizeof(data), I2C_TIMEOUT);
            // takes the resulting data and sets the two rows in this buffer to 1 to 
            // ensure they don't get read as low cols if they are currently selected
            data[0] |= 0b00000011
            // Since the pins connected to eact columns are sequential, and counting from zero up (col 0 -> GPIOB0...col 5 -> GPIOB5), the only transformation needed is a bitwise not to swap all zeroes and ones.
            data[0]  = ~(data[0]);
        }
        return data[0];
    }
}


static void select_row(uint8_t row) {
    // select on mcp23017
    uint8_t row_pos[MATRIX_ROWS] = ROW_POS
    if (mcp23018_status) {  // if there was an error
                            // do nothing
    } else {
        // Select the desired row by writing a byte for the entire GPIOA bus where only the bit representing the row we want to select is a zero (write instruction) and every other bit is a one.
        if (row > 1) {
            uint8_t buf[]   = {GPIOA, 0xFF & ~(row_pos[row])};
        } else {
            uint8_t buf[]   = {GPIOB, 0xFF & ~(row_pos[row])};
        }
        mcp23018_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);
    }
}
