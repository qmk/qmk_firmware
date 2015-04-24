#include "arm_math.h"
#include "math_helper.h"
#include <stdio.h>

#define BLOCK_SIZE          32
#define NUM_BLOCKS          10

#define TEST_LENGTH_SAMPLES (BLOCK_SIZE * NUM_BLOCKS)

#define SNR_THRESHOLD_F32   140.0f
#define NUM_TAPS            29

/* -------------------------------------------------------------------
 * The input signal and reference output (computed with MATLAB)
 * are defined externally in arm_fir_lpf_data.c.
 * ------------------------------------------------------------------- */
extern float32_t testInput_f32_1kHz_15kHz[TEST_LENGTH_SAMPLES];
extern float32_t refOutput[TEST_LENGTH_SAMPLES];

/* -------------------------------------------------------------------
 * Declare State buffer of size (numTaps + blockSize - 1)
 * ------------------------------------------------------------------- */
static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];

/* ----------------------------------------------------------------------
 * FIR Coefficients buffer generated using fir1() MATLAB function.
 * fir1(28, 6/24)
 * ------------------------------------------------------------------- */
const float32_t firCoeffs32[NUM_TAPS] = {
    -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f,
    +0.0085302217f, -0.0000000000f, -0.0173976984f, -0.0341458607f, -0.0333591565f,
    +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f,
    +0.2229246956f, +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f,
    -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f, +0.0080754303f,
    +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

/* ----------------------------------------------------------------------
 * FIR LPF Example
 * ------------------------------------------------------------------- */
int main(void) {
    /* Call FIR init function to initialize the instance structure. */
    arm_fir_instance_f32 S;
    arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], BLOCK_SIZE);

    /* ----------------------------------------------------------------------
     * Call the FIR process function for every blockSize samples
     * ------------------------------------------------------------------- */
    for (uint32_t i=0; i < NUM_BLOCKS; i++) {
        float32_t* signal =  testInput_f32_1kHz_15kHz + (i * BLOCK_SIZE);
        arm_fir_f32(&S, signal, signal, BLOCK_SIZE);
    }

    /* ----------------------------------------------------------------------
     * Compare the generated output against the reference output computed
     * in MATLAB.
     * ------------------------------------------------------------------- */
    float32_t snr = arm_snr_f32(refOutput, testInput_f32_1kHz_15kHz, TEST_LENGTH_SAMPLES);
    printf("snr: %f\n\r", snr);
    if (snr < SNR_THRESHOLD_F32) {
        printf("Failed\n\r");
    } else {
        printf("Success\n\r");
    }
}
