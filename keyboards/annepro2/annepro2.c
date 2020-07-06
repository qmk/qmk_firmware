#include "ch.h"
#include "hal.h"
#include "annepro2.h"
#include "qmk_ap2_led.h"

/**
 * @brief   Driver default configuration.
 */
static const SerialConfig ledUartConfig = {
  .speed = 115200,
};

static uint8_t ledMcuWakeup[11] = {
0x7b, 0x10, 0x43, 0x10, 0x03, 0, 0, 0x7d, 0x02, 0x01, 0x02
};

uint16_t annepro2LedMatrix[MATRIX_ROWS * MATRIX_COLS] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void OVERRIDE matrix_init_kb(void) {
    // Start uart
    sdStart(&SD0, &ledUartConfig);
    sdWrite(&SD0, ledMcuWakeup, 11);

    matrix_init_user();
}

void annepro2LedDisable(void)
{
    sdPut(&SD0, CMD_LED_OFF);
}

void annepro2LedEnable(void)
{
    sdPut(&SD0, CMD_LED_ON);
}

void annepro2LedUpdate(uint8_t row, uint8_t col)
{
    sdPut(&SD0, CMD_LED_SET);
    sdPut(&SD0, row);
    sdPut(&SD0, col);
    sdWrite(&SD0, (uint8_t *)&annepro2LedMatrix[row * MATRIX_COLS + col], sizeof(uint16_t));
}

void annepro2LedUpdateRow(uint8_t row)
{
    sdPut(&SD0, CMD_LED_SET_ROW);
    sdPut(&SD0, row);
    sdWrite(&SD0, (uint8_t *)&annepro2LedMatrix[row * MATRIX_COLS], sizeof(uint16_t) * MATRIX_COLS);
}

bool OVERRIDE led_update_kb(led_t status) {
    annepro2LedMatrix[2 * MATRIX_COLS] = status.caps_lock ? 0x4FF : 0;
    annepro2LedUpdate(2, 0);
    return led_update_user(status);
}

bool OVERRIDE process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}
