#include "ch.h"
#include "hal.h"
#include "annepro2.h"

/**
 * @brief   Driver default configuration.
 */
static const SerialConfig ledUartConfig = {
  .speed = 115200,
};

static uint8_t ledMcuWakeup[11] = {
0x7b, 0x10, 0x43, 0x10, 0x03, 0, 0, 0x7d, 0x02, 0x01, 0x02
};

void OVERRIDE matrix_init_kb(void) {
    // Start uart
    sdStart(&SD0, &ledUartConfig);
    sdWrite(&SD0, ledMcuWakeup, 11);

    matrix_init_user();
}

bool OVERRIDE process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}
