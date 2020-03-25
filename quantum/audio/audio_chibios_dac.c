/* Copyright 2016-2019 Jack Humbert
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

#include "audio.h"
#include "ch.h"
#include "hal.h"

/*
  Audio Driver: DAC

  which utilizes the dac unit many STM32 are equipped with to output a modulated sinewave from samples stored in the dac_buffer_sine array and are passed to the hardware through DMA

  it ia also possible to have a custom sample-LUT by implementing/overriding 'dac_value_generate'
*/

static const dacsample_t dac_buffer_sine[DAC_BUFFER_SIZE] = {
    // 256 values, max 4095
    0x800, 0x832, 0x864, 0x896, 0x8c8, 0x8fa, 0x92c, 0x95e, 0x98f, 0x9c0, 0x9f1, 0xa22, 0xa52, 0xa82, 0xab1, 0xae0, 0xb0f, 0xb3d, 0xb6b, 0xb98, 0xbc5, 0xbf1, 0xc1c, 0xc47, 0xc71, 0xc9a, 0xcc3, 0xceb, 0xd12, 0xd39, 0xd5f, 0xd83, 0xda7, 0xdca, 0xded, 0xe0e, 0xe2e, 0xe4e, 0xe6c, 0xe8a, 0xea6, 0xec1, 0xedc, 0xef5, 0xf0d, 0xf24, 0xf3a, 0xf4f, 0xf63, 0xf76, 0xf87, 0xf98, 0xfa7, 0xfb5, 0xfc2, 0xfcd, 0xfd8, 0xfe1, 0xfe9, 0xff0, 0xff5, 0xff9, 0xffd, 0xffe, 0xfff, 0xffe, 0xffd, 0xff9, 0xff5, 0xff0, 0xfe9, 0xfe1, 0xfd8, 0xfcd, 0xfc2, 0xfb5, 0xfa7, 0xf98, 0xf87, 0xf76, 0xf63, 0xf4f, 0xf3a, 0xf24, 0xf0d, 0xef5, 0xedc, 0xec1, 0xea6, 0xe8a, 0xe6c, 0xe4e, 0xe2e, 0xe0e, 0xded, 0xdca, 0xda7, 0xd83, 0xd5f, 0xd39, 0xd12, 0xceb, 0xcc3, 0xc9a, 0xc71, 0xc47, 0xc1c, 0xbf1, 0xbc5, 0xb98, 0xb6b, 0xb3d, 0xb0f, 0xae0, 0xab1, 0xa82, 0xa52, 0xa22, 0x9f1, 0x9c0, 0x98f, 0x95e, 0x92c, 0x8fa, 0x8c8, 0x896, 0x864, 0x832,
    0x800, 0x7cd, 0x79b, 0x769, 0x737, 0x705, 0x6d3, 0x6a1, 0x670, 0x63f, 0x60e, 0x5dd, 0x5ad, 0x57d, 0x54e, 0x51f, 0x4f0, 0x4c2, 0x494, 0x467, 0x43a, 0x40e, 0x3e3, 0x3b8, 0x38e, 0x365, 0x33c, 0x314, 0x2ed, 0x2c6, 0x2a0, 0x27c, 0x258, 0x235, 0x212, 0x1f1, 0x1d1, 0x1b1, 0x193, 0x175, 0x159, 0x13e, 0x123, 0x10a, 0xf2,  0xdb,  0xc5,  0xb0,  0x9c,  0x89,  0x78,  0x67,  0x58,  0x4a,  0x3d,  0x32,  0x27,  0x1e,  0x16,  0xf,   0xa,   0x6,   0x2,   0x1,   0x0,   0x1,   0x2,   0x6,   0xa,   0xf,   0x16,  0x1e,  0x27,  0x32,  0x3d,  0x4a,  0x58,  0x67,  0x78,  0x89,  0x9c,  0xb0,  0xc5,  0xdb,  0xf2,  0x10a, 0x123, 0x13e, 0x159, 0x175, 0x193, 0x1b1, 0x1d1, 0x1f1, 0x212, 0x235, 0x258, 0x27c, 0x2a0, 0x2c6, 0x2ed, 0x314, 0x33c, 0x365, 0x38e, 0x3b8, 0x3e3, 0x40e, 0x43a, 0x467, 0x494, 0x4c2, 0x4f0, 0x51f, 0x54e, 0x57d, 0x5ad, 0x5dd, 0x60e, 0x63f, 0x670, 0x6a1, 0x6d3, 0x705, 0x737, 0x769, 0x79b, 0x7cd};

/*
static const dacsample_t dac_buffer_triangle[DAC_BUFFER_SIZE] = {
    // 256 values, max 4095
    0x20,  0x40,  0x60,  0x80,  0xa0,  0xc0,  0xe0,  0x100, 0x120, 0x140, 0x160, 0x180, 0x1a0, 0x1c0, 0x1e0, 0x200, 0x220, 0x240, 0x260, 0x280, 0x2a0, 0x2c0, 0x2e0, 0x300, 0x320, 0x340, 0x360, 0x380, 0x3a0, 0x3c0, 0x3e0, 0x400, 0x420, 0x440, 0x460, 0x480, 0x4a0, 0x4c0, 0x4e0, 0x500, 0x520, 0x540, 0x560, 0x580, 0x5a0, 0x5c0, 0x5e0, 0x600, 0x620, 0x640, 0x660, 0x680, 0x6a0, 0x6c0, 0x6e0, 0x700, 0x720, 0x740, 0x760, 0x780, 0x7a0, 0x7c0, 0x7e0, 0x800, 0x81f, 0x83f, 0x85f, 0x87f, 0x89f, 0x8bf, 0x8df, 0x8ff, 0x91f, 0x93f, 0x95f, 0x97f, 0x99f, 0x9bf, 0x9df, 0x9ff, 0xa1f, 0xa3f, 0xa5f, 0xa7f, 0xa9f, 0xabf, 0xadf, 0xaff, 0xb1f, 0xb3f, 0xb5f, 0xb7f, 0xb9f, 0xbbf, 0xbdf, 0xbff, 0xc1f, 0xc3f, 0xc5f, 0xc7f, 0xc9f, 0xcbf, 0xcdf, 0xcff, 0xd1f, 0xd3f, 0xd5f, 0xd7f, 0xd9f, 0xdbf, 0xddf, 0xdff, 0xe1f, 0xe3f, 0xe5f, 0xe7f, 0xe9f, 0xebf, 0xedf, 0xeff, 0xf1f, 0xf3f, 0xf5f, 0xf7f, 0xf9f, 0xfbf, 0xfdf, 0xfff,
    0xfdf, 0xfbf, 0xf9f, 0xf7f, 0xf5f, 0xf3f, 0xf1f, 0xeff, 0xedf, 0xebf, 0xe9f, 0xe7f, 0xe5f, 0xe3f, 0xe1f, 0xdff, 0xddf, 0xdbf, 0xd9f, 0xd7f, 0xd5f, 0xd3f, 0xd1f, 0xcff, 0xcdf, 0xcbf, 0xc9f, 0xc7f, 0xc5f, 0xc3f, 0xc1f, 0xbff, 0xbdf, 0xbbf, 0xb9f, 0xb7f, 0xb5f, 0xb3f, 0xb1f, 0xaff, 0xadf, 0xabf, 0xa9f, 0xa7f, 0xa5f, 0xa3f, 0xa1f, 0x9ff, 0x9df, 0x9bf, 0x99f, 0x97f, 0x95f, 0x93f, 0x91f, 0x8ff, 0x8df, 0x8bf, 0x89f, 0x87f, 0x85f, 0x83f, 0x81f, 0x800, 0x7e0, 0x7c0, 0x7a0, 0x780, 0x760, 0x740, 0x720, 0x700, 0x6e0, 0x6c0, 0x6a0, 0x680, 0x660, 0x640, 0x620, 0x600, 0x5e0, 0x5c0, 0x5a0, 0x580, 0x560, 0x540, 0x520, 0x500, 0x4e0, 0x4c0, 0x4a0, 0x480, 0x460, 0x440, 0x420, 0x400, 0x3e0, 0x3c0, 0x3a0, 0x380, 0x360, 0x340, 0x320, 0x300, 0x2e0, 0x2c0, 0x2a0, 0x280, 0x260, 0x240, 0x220, 0x200, 0x1e0, 0x1c0, 0x1a0, 0x180, 0x160, 0x140, 0x120, 0x100, 0xe0,  0xc0,  0xa0,  0x80,  0x60,  0x40,  0x20,  0x0};

static const dacsample_t dac_buffer_square[DAC_BUFFER_SIZE] = {
    // First half is max, second half is 0
    [0 ... DAC_BUFFER_SIZE / 2 - 1]               = DAC_SAMPLE_MAX,
    [DAC_BUFFER_SIZE / 2 ... DAC_BUFFER_SIZE - 1] = 0,
};

// four steps: 0, 1/3, 2/3 and 1
static const dacsample_t dac_buffer_staircase[DAC_BUFFER_SIZE] = {
    [0 ... DAC_BUFFER_SIZE/3 -1 ] = 0,
    [DAC_BUFFER_SIZE / 4 ... DAC_BUFFER_SIZE / 2 -1 ] = DAC_SAMPLE_MAX / 3,
    [DAC_BUFFER_SIZE / 2 ... 3 * DAC_BUFFER_SIZE / 4 -1 ] = 2 * DAC_SAMPLE_MAX / 3,
    [3 * DAC_BUFFER_SIZE / 4 ... DAC_BUFFER_SIZE -1 ] = DAC_SAMPLE_MAX,
}
*/

static dacsample_t dac_buffer_empty[DAC_BUFFER_SIZE] = {DAC_OFF_VALUE};

/* keep track of the sample position for for each voice/frequency */
static float dac_if[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

/**
 * Generation of the waveform being passed to the callback. Declared weak so users
 * can override it with their own waveforms/noises.
 */
__attribute__((weak)) uint16_t dac_value_generate(void) {
    uint16_t value          = DAC_OFF_VALUE;
    uint8_t  working_voices = audio_get_number_of_active_voices();
    if (working_voices > AUDIO_VOICES_MAX) working_voices = AUDIO_VOICES_MAX;

    if (working_voices > 0) {
        uint16_t value_avg = 0;
        for (uint8_t i = 0; i < working_voices; i++) {
            dac_if[i] = dac_if[i] +
                ((audio_get_frequency(i) //TODO: replace by glissando+vibrator+.. variant
                  * DAC_BUFFER_SIZE) / DAC_SAMPLE_RATE)
                * 2/3; /*Note: necessary to get the correct frequencies on the
                         DAC output (as measured with an oscilloscope), since
                         the gpt timer runs with 3*DAC_SAMPLE_RATE; and the DAC
                         callback is called twice per conversion.*/

            // Needed because % doesn't work with floats
            while (dac_if[i] >= (DAC_BUFFER_SIZE)) dac_if[i] = dac_if[i] - DAC_BUFFER_SIZE;

            // Wavetable generation/lookup
            uint16_t dac_i = (uint16_t)dac_if[i];
            // SINE
            value_avg += dac_buffer_sine[dac_i] / working_voices;// / 3;
            // TRIANGLE
//            value_avg += dac_buffer_triangle[dac_i] / working_voices / 3;
            // SQUARE
//            value_avg += dac_buffer_square[dac_i] / working_voices / 3;
            //NOTE: combination of these three waveforms is more exemplary - and doesn't sound particularly good :-P

            // STAIRS
            //value_avg = dac_buffer_staircase[dac_i] / working_voices;
        }
        value = value_avg;
    }
    return value;
}

/**
 * DAC streaming callback. Does all of the main computing for playing songs.
 *
 * Note: chibios calls this CB twice: during the 'half buffer event', and the 'full buffer event'.
 */
static void dac_end(DACDriver *dacp){
    dacsample_t *sample_p = (dacp)->samples;

    // work on the other half of the buffer
    if (dacIsBufferComplete(dacp)) {
        sample_p += DAC_BUFFER_SIZE/2; // 'half_index'
    }

    for (uint8_t s = 0; s < DAC_BUFFER_SIZE/2; s++) {
        sample_p[s] = dac_value_generate();
    }

    // update audio internal state (note position, current_note, voices, ...)
    audio_advance_note(
        DAC_BUFFER_SIZE/2,
        DAC_SAMPLE_RATE/ (64*2.0f/3)
        /* End of the note: 64 is the number of 'units' of a whole note, 3 comes
           from the gpttimer: DAC_SAMPLE_RATE * 3; 2 from the callback beeing
           called twice per sample conversion.
           with a TEMPO set to 60 a whole note lasts exactly one second */
        );
}

static void dac_error(DACDriver *dacp, dacerror_t err) {
    (void)dacp;
    (void)err;

    chSysHalt("DAC failure. halp");
}

static const GPTConfig gpt6cfg1 = {.frequency = DAC_SAMPLE_RATE * 3,
                                   .callback  = NULL,
                                   .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.  */
                                   .dier      = 0U};

static const DACConfig dac_conf = {.init = DAC_SAMPLE_MAX, .datamode = DAC_DHRM_12BIT_RIGHT};

/**
 * @note The DAC_TRG(0) here selects the Timer 6 TRGO event, which is triggered
 * on the rising edge after 3 APB1 clock cycles, causing our gpt6cfg1.frequency
 * to be a third of what we expect.
 *
 * Here are all the values for DAC_TRG (TSEL in the ref manual)
 * TIM15_TRGO 0b011
 * TIM2_TRGO  0b100
 * TIM3_TRGO  0b001
 * TIM6_TRGO  0b000
 * TIM7_TRGO  0b010
 * EXTI9      0b110
 * SWTRIG     0b111
 */
static const DACConversionGroup dac_conv_cfg = {.num_channels = 1U, .end_cb = dac_end, .error_cb = dac_error, .trigger = DAC_TRG(0b000)};

void audio_initialize_hardware() {
#if defined(A4_AUDIO)
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD1, &dac_conf);
    dacStartConversion(&DACD1, &dac_conv_cfg, dac_buffer_empty, DAC_BUFFER_SIZE);
#endif
#if defined(A5_AUDIO)
    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD2, &dac_conf);
    dacStartConversion(&DACD2, &dac_conv_cfg, dac_buffer_empty, DAC_BUFFER_SIZE);
#endif

    /* enable the output buffer, to directly drive external loads with no additional circuitry
     *
     * see: AN4566 Application note: Extending the DAC performance of STM32 microcontrollers
     * Note: Buffer-Off bit -> has to be set 0 to enable the output buffer
     * Note: enabling the output buffer imparts an additional dc-offset of a couple mV
     *
     * this is done here, reaching directly into the stm32 registers since chibios has not implemented BOFF handling yet
     * (see: chibios/os/hal/ports/STM32/todo.txt '- BOFF handling in DACv1.'
     */
#if defined(A4_AUDIO)
    DACD1.params->dac->CR &= ~DAC_CR_BOFF1;
#endif
#if defined(A5_AUDIO)
    DACD2.params->dac->CR &= ~DAC_CR_BOFF2;
#endif

    gptStart(&GPTD6, &gpt6cfg1);
    gptStartContinuous(&GPTD6, 2U);
}

void audio_stop_hardware(void) {}

void audio_start_hardware(void) {}
