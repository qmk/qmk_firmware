#include "analogkeys.h"
#include "custom_analog.h"
#include "config.h"
#include <stdint.h>

#if MUXES == 0
extern pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS];

void SMA_init(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            analog_key_t *key = &keys[row][col];
            for (uint8_t idx = 0; idx < SMA_SAMPLE_SIZE; idx++) {
                uint16_t raw = analogReadPin(matrix_pins[row][col]);
                key->SMA.sum += raw;
                key->SMA.buf[idx] = raw;
            }
        }
    }
}
#endif

void SMA_filter(analog_key_t *key) {
    key->SMA.sum                 = key->SMA.sum - key->SMA.buf[key->SMA.index] + key->raw;
    key->SMA.buf[key->SMA.index] = key->raw;
    key->SMA.index++;
    if (key->SMA.index == SMA_SAMPLE_SIZE) key->SMA.index = 0;
    key->raw = key->SMA.sum >> SMA_SAMPLE_EXP;
}
