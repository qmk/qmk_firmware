
#include "quantum.h"

#include "apidef.h"
#include "bmp_encoder.h"

#ifndef ENCODER_RESOLUTION
#    define ENCODER_RESOLUTION 4
#endif

#ifndef ENCODER_SCANTIME_MS
#define ENCODER_SCANTIME_MS 2
#endif

#if !defined(ENCODERS_PAD_A) || !defined(ENCODERS_PAD_B)
#    error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B"
#endif

#define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
static pin_t encoders_pad_b[] = ENCODERS_PAD_B;
static int32_t encoder_value[NUMBER_OF_ENCODERS] = {0};

__attribute__((weak)) void encoder_update_user(int8_t index, bool clockwise) {}

__attribute__((weak)) void encoder_update_kb(int8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}

void bmp_encoder_init(void)
{
    BMPAPI->encoder.init(ENCODER_SCANTIME_MS, encoders_pad_a, encoders_pad_b,
        NUMBER_OF_ENCODERS);
}

void bmp_encoder_read(void)
{
    int32_t encoder_diff;
    for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
        encoder_diff = BMPAPI->encoder.get_count(i);
        encoder_value[i] += encoder_diff;

        if (encoder_value[i] >= ENCODER_RESOLUTION) {
            encoder_update_kb(i, false);
        }
        if (encoder_value[i] <= -ENCODER_RESOLUTION) {
            // direction is arbitrary here, but this clockwise
            encoder_update_kb(i, true);
        }

        encoder_value[i] %= ENCODER_RESOLUTION;
    }
}
