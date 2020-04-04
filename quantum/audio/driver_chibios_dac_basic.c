/* Copyright 2016-2020 Jack Humbert
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

  which utilizes both channels of the DAC unit many STM32 are equipped with to output a modulated square-wave, from precomputed samples stored in a buffer, which is passed to the hardware through DMA


TODOS:
- channel_X_stop should respect dac conversion buffer-complete; currently the output might end up 'high' = halfway through a sample conversion
*/


#if defined(AUDIO_PIN_A4) || defined (AUDIO_PIN_ALT_A4)
// squarewave
static const dacsample_t dac_buffer_1[AUDIO_DAC_BUFFER_SIZE] = {
    // First half is max, second half is 0
    [0 ... AUDIO_DAC_BUFFER_SIZE / 2 - 1]                     = AUDIO_DAC_SAMPLE_MAX,
    [AUDIO_DAC_BUFFER_SIZE / 2 ... AUDIO_DAC_BUFFER_SIZE - 1] = 0,
};
#endif
#if defined(AUDIO_PIN_A5) || defined (AUDIO_PIN_ALT_A5)
// squarewave
static const dacsample_t dac_buffer_2[AUDIO_DAC_BUFFER_SIZE] = {
    // opposite of dac_buffer above
    [0 ... AUDIO_DAC_BUFFER_SIZE / 2 - 1]                     = 0,
    [AUDIO_DAC_BUFFER_SIZE / 2 ... AUDIO_DAC_BUFFER_SIZE - 1] = AUDIO_DAC_SAMPLE_MAX,
};
#endif


#if defined(AUDIO_PIN_A4) || defined (AUDIO_PIN_ALT_A4)
GPTConfig gpt6cfg1 = {.frequency = AUDIO_DAC_SAMPLE_RATE,
                      .callback  = NULL,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};
#endif
#if defined(AUDIO_PIN_A5) || defined (AUDIO_PIN_ALT_A5)
GPTConfig gpt7cfg1 = {.frequency = AUDIO_DAC_SAMPLE_RATE,
                      .callback  = NULL,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};
#endif

static void gpt_cb8(GPTDriver *gptp);
GPTConfig gpt8cfg1 = {.frequency = 10,
                      .callback  = gpt_cb8,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

#if defined(AUDIO_PIN_A4) || defined (AUDIO_PIN_ALT_A4)
static const DACConfig dac_conf_ch1 = {.init = AUDIO_DAC_SAMPLE_MAX, .datamode = DAC_DHRM_12BIT_RIGHT};
#endif
#if defined(AUDIO_PIN_A5) || defined (AUDIO_PIN_ALT_A5)
static const DACConfig dac_conf_ch2 = {.init = AUDIO_DAC_SAMPLE_MAX, .datamode = DAC_DHRM_12BIT_RIGHT};
#endif

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
#if defined(AUDIO_PIN_A4) || defined (AUDIO_PIN_ALT_A4)
static const DACConversionGroup dac_conv_grp_ch1 = {.num_channels = 1U, .trigger = DAC_TRG(0b000)};
#endif
#if defined(AUDIO_PIN_A5) || defined (AUDIO_PIN_ALT_A5)
static const DACConversionGroup dac_conv_grp_ch2 = {.num_channels = 1U, .trigger = DAC_TRG(0b010)};
#endif


#if defined(AUDIO_PIN_A4) || defined (AUDIO_PIN_ALT_A4)
void channel_1_start(void) {
    gptStart(&GPTD6, &gpt6cfg1);
    gptStartContinuous(&GPTD6, 2U);
}

void channel_1_stop(void) {
    gptStopTimer(&GPTD6);
}

static float channel_1_frequency = 0.0f;
void channel_1_set_frequency(float freq) {
    channel_1_frequency = freq;

    channel_1_stop();
    if (freq <= 0.0) //a pause/rest has freq=0
        return;

    gpt6cfg1.frequency = 2 * freq * AUDIO_DAC_BUFFER_SIZE;
    channel_1_start();
}
float channel_1_get_frequency(void) { return channel_1_frequency; }
#endif // AUDIO_PIN(_ALT)_A4

#if defined(AUDIO_PIN_A5) || defined (AUDIO_PIN_ALT_A5)
void channel_2_start(void) {
    gptStart(&GPTD7, &gpt7cfg1);
    gptStartContinuous(&GPTD7, 2U);
}

void channel_2_stop(void) {
    gptStopTimer(&GPTD7);
}

static float channel_2_frequency = 0.0f;
void channel_2_set_frequency(float freq) {
    channel_2_frequency = freq;

    channel_2_stop();
    if (freq <= 0.0) //a pause/rest has freq=0
        return;

    gpt7cfg1.frequency = 2 * freq * AUDIO_DAC_BUFFER_SIZE;
    channel_2_start();
}
float channel_2_get_frequency(void) { return channel_2_frequency; }
#endif // AUDIO_PIN(_ALT)_A5

static void gpt_cb8(GPTDriver *gptp) {
    if(audio_advance_state(1,gpt8cfg1.frequency)) {

#if defined(AUDIO_PIN_A4)
        channel_1_set_frequency(audio_get_processed_frequency(0));
#    if defined(AUDIO_PIN_ALT_A5)
        if (audio_get_number_of_active_tones() > 1) {
            channel_2_set_frequency(audio_get_processed_frequency(1));
        } else {
            channel_2_stop();
        }
#    endif
#endif

#if defined(AUDIO_PIN_A5)
        channel_2_set_frequency(audio_get_processed_frequency(0));
#    if defined(AUDIO_PIN_ALT_A4)
        if (audio_get_number_of_active_tones() > 1) {
            channel_1_set_frequency(audio_get_processed_frequency(1));
        } else {
            channel_1_stop();
        }
#    endif
#endif

    }
}

void audio_driver_initialize() {
#if defined(AUDIO_PIN_A4) || defined (AUDIO_PIN_ALT_A4)
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD1, &dac_conf_ch1);
    dacStartConversion(&DACD1, &dac_conv_grp_ch1, (dacsample_t *)dac_buffer_1, AUDIO_DAC_BUFFER_SIZE);
#endif
#if defined(AUDIO_PIN_A5) || defined (AUDIO_PIN_ALT_A5)
    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD2, &dac_conf_ch2);
    dacStartConversion(&DACD2, &dac_conv_grp_ch2, (dacsample_t *)dac_buffer_2, AUDIO_DAC_BUFFER_SIZE);
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
#if defined(AUDIO_PIN_A4) || defined (AUDIO_PIN_ALT_A4)
    DACD1.params->dac->CR &= ~DAC_CR_BOFF1;
    gptStart(&GPTD6, &gpt6cfg1); // initialize the timer used to trigger the DAC conversions
#endif
#if defined(AUDIO_PIN_A5) || defined (AUDIO_PIN_ALT_A5)
    DACD2.params->dac->CR &= ~DAC_CR_BOFF2;
    gptStart(&GPTD7, &gpt7cfg1);
#endif

    // start state-updater
    gptStart(&GPTD8, &gpt8cfg1);
}

void audio_driver_stop(void) {
#if defined(AUDIO_PIN_A4) || defined (AUDIO_PIN_ALT_A4)
    gptStopTimer(&GPTD6);
#endif
#if defined(AUDIO_PIN_A5) || defined (AUDIO_PIN_ALT_A5)
    gptStopTimer(&GPTD7);
#endif
    gptStopTimer(&GPTD8);
}

void audio_driver_start(void) {
    gptStartContinuous(&GPTD8, 2U);
}
