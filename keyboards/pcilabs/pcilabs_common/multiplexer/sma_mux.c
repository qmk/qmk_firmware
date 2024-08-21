#include "pcilabs_common/analogkeys.h"
#include "pcilabs_common/custom_analog.h"
#include "config.h"
#include <stdint.h>
#include "multiplexer.h"

extern const mux_t mux_index[MUXES][MUX_CHANNELS];
extern const pin_t mux_pins[MUXES];

void SMA_init(void) {
    for (uint8_t channel = 0; channel < MUX_CHANNELS; ++channel) {
        uint8_t channel_greycoded = (channel >> 1) ^ channel;
        select_mux(channel_greycoded);
        // adcStartAllConversions(&adcManager);
        for (uint8_t mux = 0; mux < MUXES; ++mux) {
            const mux_t *mux_idx = &mux_index[mux][channel_greycoded];

            if (mux_idx->row == 255 && mux_idx->col == 255) continue; // NC mux pin

            analog_key_t *key = &keys[mux_idx->row][mux_idx->col];
            for (uint8_t idx = 0; idx < SMA_SAMPLE_SIZE; idx++) {
                uint16_t raw = analogReadPin(mux_pins[mux]);
                key->SMA.sum += raw;
                key->SMA.buf[idx] = raw;
            }
        }
    }
}
