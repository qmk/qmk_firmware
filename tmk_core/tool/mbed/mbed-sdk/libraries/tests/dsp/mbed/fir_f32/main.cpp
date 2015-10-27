#include "mbed.h"
#include "dsp.h"

#define BLOCK_SIZE              (32)
#define NUM_BLOCKS              (10)
#define TEST_LENGTH_SAMPLES     (BLOCK_SIZE * NUM_BLOCKS)

#define SAMPLE_RATE             (48000)

#define SNR_THRESHOLD_F32       (50.0f)

float32_t expected_output[TEST_LENGTH_SAMPLES];
float32_t          output[TEST_LENGTH_SAMPLES];

/* FIR Coefficients buffer generated using fir1() MATLAB function: fir1(28, 6/24) */
#define NUM_TAPS            29
const float32_t firCoeffs32[NUM_TAPS] = {
    -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f,
    +0.0085302217f, -0.0000000000f, -0.0173976984f, -0.0341458607f, -0.0333591565f,
    +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f,
    +0.2229246956f, +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f,
    -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f, +0.0080754303f,
    +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};
#define WARMUP    (NUM_TAPS-1)
#define DELAY     (WARMUP/2)

int main() {
    Sine_f32 sine_1KHz(  1000, SAMPLE_RATE, 1.0);
    Sine_f32 sine_15KHz(15000, SAMPLE_RATE, 0.5);
    FIR_f32<NUM_TAPS> fir(firCoeffs32);

    float32_t buffer_a[BLOCK_SIZE];
    float32_t buffer_b[BLOCK_SIZE];
    for (float32_t *sgn=output; sgn<(output+TEST_LENGTH_SAMPLES); sgn += BLOCK_SIZE) {
        sine_1KHz.generate(buffer_a);           // Generate a 1KHz sine wave
        sine_15KHz.process(buffer_a, buffer_b); // Add a 15KHz sine wave
        fir.process(buffer_b, sgn);             // FIR low pass filter: 6KHz cutoff
    }

    sine_1KHz.reset();
    for (float32_t *sgn=expected_output; sgn<(expected_output+TEST_LENGTH_SAMPLES); sgn += BLOCK_SIZE) {
        sine_1KHz.generate(sgn);        // Generate a 1KHz sine wave
    }

    float snr = arm_snr_f32(&expected_output[DELAY-1], &output[WARMUP-1], TEST_LENGTH_SAMPLES-WARMUP);
    printf("snr: %f\n\r", snr);
    if (snr < SNR_THRESHOLD_F32) {
        printf("Failed\n\r");
    } else {
        printf("Success\n\r");
    }
}
