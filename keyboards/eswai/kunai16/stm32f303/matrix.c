#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"

#define I2C1_SCL_BANK GPIOB
#define I2C1_SDA_BANK GPIOB
#define I2C1_SCL 8
#define I2C1_SDA 9

#define I2C2_SCL_BANK GPIOA
#define I2C2_SDA_BANK GPIOA
#define I2C2_SCL 9
#define I2C2_SDA 10

#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 7U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 38U
#define I2C1_TIMINGR_SCLL 129U
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PAL_MODE 4

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static uint8_t matrix_row_read[2] = { 0xff, 0xff };

// Address / Row config
static const uint8_t addresses[MATRIX_ROWS] = { 0b0100000, 0b0100001, 0b0100000, 0b0100001 };
static I2CDriver* i2cDrivers[MATRIX_ROWS] = { &I2CD1, &I2CD1, &I2CD2, &I2CD2 };

static uint8_t read_command = 0;

static matrix_row_t read_cols(uint8_t row);
static void init_cols(void);

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

/*
 * I2C1 config.
 */
static const I2CConfig i2ccfg = {
    // This configures the I2C clock to 400khz assuming a 72Mhz clock
    // For more info : https://www.st.com/en/embedded-software/stsw-stm32126.html
    STM32_TIMINGR_PRESC(I2C1_TIMINGR_PRESC) | STM32_TIMINGR_SCLDEL(I2C1_TIMINGR_SCLDEL) | STM32_TIMINGR_SDADEL(I2C1_TIMINGR_SDADEL) | STM32_TIMINGR_SCLH(I2C1_TIMINGR_SCLH) | STM32_TIMINGR_SCLL(I2C1_TIMINGR_SCLL), 0, 0
};

void matrix_init(void)
{
    // initialize row and col
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_init_user();
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        wait_us(30);
        matrix_row_t cols = read_cols(i);
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
    }

    if (debouncing) {
        if (--debouncing) {
            wait_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

/* Column pin configuration
 */
static void init_cols(void)
{
    palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_INPUT);
    palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_INPUT);
    palSetPadMode(I2C2_SCL_BANK, I2C2_SCL, PAL_MODE_INPUT);
    palSetPadMode(I2C2_SDA_BANK, I2C2_SDA, PAL_MODE_INPUT);

    chThdSleepMilliseconds(10);

    palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
    palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
    palSetPadMode(I2C2_SCL_BANK, I2C2_SCL, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
    palSetPadMode(I2C2_SDA_BANK, I2C2_SDA, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(uint8_t row)
{
    msg_t status = MSG_OK;

    i2cStart(i2cDrivers[row], &i2ccfg);

    status = i2cMasterTransmit(i2cDrivers[row], addresses[row], &read_command, 1, NULL, 0);

    if (MSG_OK != status) {
        // i2cflags_t error_code;
        // error_code = i2cGetErrors(i2cDrivers[row]);
        // printf("I2C TX Error: %x\n", error_code);
        return (matrix_row_t)0;
    }

    status = i2cMasterReceive(i2cDrivers[row], addresses[row], matrix_row_read, 2);

    if (MSG_OK != status) {
        // i2cflags_t error_code;
        // error_code = i2cGetErrors(i2cDrivers[row]);
        // printf("I2C RX Error: %x\n", error_code);
        return (matrix_row_t)0;
    }

    uint8_t low = ~matrix_row_read[0];
    uint8_t high = ~matrix_row_read[1];

    return high<<8 | low;
}

