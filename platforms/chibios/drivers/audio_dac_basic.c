/* Copyright 2016-2020 Jack Humbert
 * Copyright 2020 JohSchneider
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

// Need to disable GCC's "tautological-compare" warning for this file, as it causes issues when running `KEEP_INTERMEDIATES=yes`. Corresponding pop at the end of the file.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"

/*
  Audio Driver: DAC

  which utilizes both channels of the DAC unit many STM32 are equipped with to output a modulated square-wave, from precomputed samples stored in a buffer, which is passed to the hardware through DMA

  this driver can either be used to drive to separate speakers, wired to A4+Gnd and A5+Gnd, which allows two tones to be played simultaneously
  OR
  one speaker wired to A4+A5 with the AUDIO_PIN_ALT_AS_NEGATIVE define set - see docs/feature_audio

*/

#if !defined(AUDIO_PIN)
#    pragma message "Audio feature enabled, but no suitable pin selected as AUDIO_PIN - see docs/feature_audio under 'ARM (DAC basic)' for available options."
// TODO: make this an 'error' instead; go through a breaking change, and add AUDIO_PIN A5 to all keyboards currently using AUDIO on STM32 based boards? - for now: set the define here
#    define AUDIO_PIN A5
#endif
// check configuration for ONE speaker, connected to both DAC pins
#if defined(AUDIO_PIN_ALT_AS_NEGATIVE) && !defined(AUDIO_PIN_ALT)
#    error "Audio feature: AUDIO_PIN_ALT_AS_NEGATIVE set, but no pin configured as AUDIO_PIN_ALT"
#endif

#ifndef AUDIO_PIN_ALT
// no ALT pin defined is valid, but the c-ifs below need some value set
#    define AUDIO_PIN_ALT -1
#endif

#if !defined(AUDIO_STATE_TIMER)
#    define AUDIO_STATE_TIMER GPTD8
#endif

// square-wave
static const dacsample_t dac_buffer_1[AUDIO_DAC_BUFFER_SIZE] = {
    // First half is max, second half is 0
    [0 ... AUDIO_DAC_BUFFER_SIZE / 2 - 1]                     = AUDIO_DAC_SAMPLE_MAX,
    [AUDIO_DAC_BUFFER_SIZE / 2 ... AUDIO_DAC_BUFFER_SIZE - 1] = 0,
};

// square-wave
static const dacsample_t dac_buffer_2[AUDIO_DAC_BUFFER_SIZE] = {
    // opposite of dac_buffer above
    [0 ... AUDIO_DAC_BUFFER_SIZE / 2 - 1]                     = 0,
    [AUDIO_DAC_BUFFER_SIZE / 2 ... AUDIO_DAC_BUFFER_SIZE - 1] = AUDIO_DAC_SAMPLE_MAX,
};

GPTConfig gpt6cfg1 = {.frequency = AUDIO_DAC_SAMPLE_RATE,
                      .callback  = NULL,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};
GPTConfig gpt7cfg1 = {.frequency = AUDIO_DAC_SAMPLE_RATE,
                      .callback  = NULL,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

static void gpt_audio_state_cb(GPTDriver *gptp);
GPTConfig   gptStateUpdateCfg = {.frequency = 10,
                               .callback  = gpt_audio_state_cb,
                               .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                               .dier      = 0U};

static const DACConfig dac_conf_ch1 = {.init = AUDIO_DAC_OFF_VALUE, .datamode = DAC_DHRM_12BIT_RIGHT};
static const DACConfig dac_conf_ch2 = {.init = AUDIO_DAC_OFF_VALUE, .datamode = DAC_DHRM_12BIT_RIGHT};

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
static const DACConversionGroup dac_conv_grp_ch1 = {.num_channels = 1U, .trigger = DAC_TRG(0b000)};
static const DACConversionGroup dac_conv_grp_ch2 = {.num_channels = 1U, .trigger = DAC_TRG(0b010)};

void channel_1_start(void) {
    gptStart(&GPTD6, &gpt6cfg1);
    gptStartContinuous(&GPTD6, 2U);
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
}

void channel_1_stop(void) {
    gptStopTimer(&GPTD6);
    palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOA, 4);
}

static float channel_1_frequency = 0.0f;
void         channel_1_set_frequency(float freq) {
    channel_1_frequency = freq;

    channel_1_stop();
    if (freq <= 0.0) // a pause/rest has freq=0
        return;

    gpt6cfg1.frequency = 2 * freq * AUDIO_DAC_BUFFER_SIZE;
    channel_1_start();
}
float channel_1_get_frequency(void) {
    return channel_1_frequency;
}

void channel_2_start(void) {
    gptStart(&GPTD7, &gpt7cfg1);
    gptStartContinuous(&GPTD7, 2U);
    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);
}

void channel_2_stop(void) {
    gptStopTimer(&GPTD7);
    palSetPadMode(GPIOA, 5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOA, 5);
}

static float channel_2_frequency = 0.0f;
void         channel_2_set_frequency(float freq) {
    channel_2_frequency = freq;

    channel_2_stop();
    if (freq <= 0.0) // a pause/rest has freq=0
        return;

    gpt7cfg1.frequency = 2 * freq * AUDIO_DAC_BUFFER_SIZE;
    channel_2_start();
}
float channel_2_get_frequency(void) {
    return channel_2_frequency;
}

static void gpt_audio_state_cb(GPTDriver *gptp) {
    if (audio_update_state()) {
#if defined(AUDIO_PIN_ALT_AS_NEGATIVE)
        // one piezo/speaker connected to both audio pins, the generated square-waves are inverted
        channel_1_set_frequency(audio_get_processed_frequency(0));
        channel_2_set_frequency(audio_get_processed_frequency(0));

#else // two separate audio outputs/speakers
      // primary speaker on A4, optional secondary on A5
        if (AUDIO_PIN == A4) {
            channel_1_set_frequency(audio_get_processed_frequency(0));
            if (AUDIO_PIN_ALT == A5) {
                if (audio_get_number_of_active_tones() > 1) {
                    channel_2_set_frequency(audio_get_processed_frequency(1));
                } else {
                    channel_2_stop();
                }
            }
        }

        // primary speaker on A5, optional secondary on A4
        if (AUDIO_PIN == A5) {
            channel_2_set_frequency(audio_get_processed_frequency(0));
            if (AUDIO_PIN_ALT == A4) {
                if (audio_get_number_of_active_tones() > 1) {
                    channel_1_set_frequency(audio_get_processed_frequency(1));
                } else {
                    channel_1_stop();
                }
            }
        }
#endif
    }
}

void audio_driver_initialize(void) {
    if ((AUDIO_PIN == A4) || (AUDIO_PIN_ALT == A4)) {
        palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
        dacStart(&DACD1, &dac_conf_ch1);

        // initial setup of the dac-triggering timer is still required, even
        // though it gets reconfigured and restarted later on
        gptStart(&GPTD6, &gpt6cfg1);
    }

    if ((AUDIO_PIN == A5) || (AUDIO_PIN_ALT == A5)) {
        palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);
        dacStart(&DACD2, &dac_conf_ch2);

        gptStart(&GPTD7, &gpt7cfg1);
    }

    /* enable the output buffer, to directly drive external loads with no additional circuitry
     *
     * see: AN4566 Application note: Extending the DAC performance of STM32 microcontrollers
     * Note: Buffer-Off bit -> has to be set 0 to enable the output buffer
     * Note: enabling the output buffer imparts an additional dc-offset of a couple mV
     *
     * this is done here, reaching directly into the stm32 registers since chibios has not implemented BOFF handling yet
     * (see: chibios/os/hal/ports/STM32/todo.txt '- BOFF handling in DACv1.'
     */
    DACD1.params->dac->CR &= ~DAC_CR_BOFF1;
    DACD2.params->dac->CR &= ~DAC_CR_BOFF2;

    // start state-updater
    gptStart(&AUDIO_STATE_TIMER, &gptStateUpdateCfg);
}

void audio_driver_stop(void) {
    if ((AUDIO_PIN == A4) || (AUDIO_PIN_ALT == A4)) {
        gptStopTimer(&GPTD6);

        // stop the ongoing conversion and put the output in a known state
        dacStopConversion(&DACD1);
        dacPutChannelX(&DACD1, 0, AUDIO_DAC_OFF_VALUE);
    }

    if ((AUDIO_PIN == A5) || (AUDIO_PIN_ALT == A5)) {
        gptStopTimer(&GPTD7);

        dacStopConversion(&DACD2);
        dacPutChannelX(&DACD2, 0, AUDIO_DAC_OFF_VALUE);
    }
    gptStopTimer(&AUDIO_STATE_TIMER);
}

void audio_driver_start(void) {
    if ((AUDIO_PIN == A4) || (AUDIO_PIN_ALT == A4)) {
        dacStartConversion(&DACD1, &dac_conv_grp_ch1, (dacsample_t *)dac_buffer_1, AUDIO_DAC_BUFFER_SIZE);
    }
    if ((AUDIO_PIN == A5) || (AUDIO_PIN_ALT == A5)) {
        dacStartConversion(&DACD2, &dac_conv_grp_ch2, (dacsample_t *)dac_buffer_2, AUDIO_DAC_BUFFER_SIZE);
    }
    gptStartContinuous(&AUDIO_STATE_TIMER, 2U);
}

#pragma GCC diagnostic pop
