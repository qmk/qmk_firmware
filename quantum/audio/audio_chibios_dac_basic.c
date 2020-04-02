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


// squarewave
static const dacsample_t dac_buffer_1[DAC_BUFFER_SIZE] = {
    // First half is max, second half is 0
    [0 ... DAC_BUFFER_SIZE / 2 - 1]               = DAC_SAMPLE_MAX,
    [DAC_BUFFER_SIZE / 2 ... DAC_BUFFER_SIZE - 1] = 0,
};

// squarewave
static const dacsample_t dac_buffer_2[DAC_BUFFER_SIZE] = {
    // opposite of dac_buffer above
    [0 ... DAC_BUFFER_SIZE / 2 - 1]               = 0,
    [DAC_BUFFER_SIZE / 2 ... DAC_BUFFER_SIZE - 1] = DAC_SAMPLE_MAX,
};



GPTConfig gpt6cfg1 = {.frequency = 440U * DAC_BUFFER_SIZE,
                      .callback  = NULL,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

GPTConfig gpt7cfg1 = {.frequency = 440U * DAC_BUFFER_SIZE,
                      .callback  = NULL,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

static void gpt_cb8(GPTDriver *gptp);
GPTConfig gpt8cfg1 = {.frequency = 10,
                      .callback  = gpt_cb8,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

/*
// DAC streaming callback.
//size_t      nz = 0;
static void end_cb1(DACDriver *dacp) {
    (void)dacp;
//    nz++;
//    if ((nz % 1000) == 0) {
//        palTogglePad(GPIOD, GPIOD_LED3);
//    }
}

// DAC error callback.
static void error_cb1(DACDriver *dacp, dacerror_t err) {
    (void)dacp;
    (void)err;

    chSysHalt("DAC failure");
}
*/

static const DACConfig dac_conf_ch1 = {.init = DAC_SAMPLE_MAX, .datamode = DAC_DHRM_12BIT_RIGHT};
static const DACConfig dac_conf_ch2 = {.init = DAC_SAMPLE_MAX, .datamode = DAC_DHRM_12BIT_RIGHT};

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
static const DACConversionGroup dac_conv_grp_ch1 = {.num_channels = 1U, /* .end_cb = end_cb1, .error_cb = error_cb1, */ .trigger = DAC_TRG(0b000)};
static const DACConversionGroup dac_conv_grp_ch2 = {.num_channels = 1U, /* .end_cb = end_cb1, .error_cb = error_cb1, */ .trigger = DAC_TRG(0b010)};



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

    gpt6cfg1.frequency = 2 * freq * DAC_BUFFER_SIZE;
    channel_1_start();
}
float channel_1_get_frequency(void) { return channel_1_frequency; }


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

    gpt7cfg1.frequency = 2 * freq * DAC_BUFFER_SIZE;
    channel_2_start();
}
float channel_2_get_frequency(void) { return channel_2_frequency; }


static void gpt_cb8(GPTDriver *gptp) {
    // state_recently_changed =
    if(audio_advance_state(1,gpt8cfg1.frequency)) {
        channel_1_set_frequency(audio_get_processed_frequency(0));
        if (audio_get_number_of_active_tones() > 1) {
            channel_2_set_frequency(audio_get_processed_frequency(1));
        } else {
            channel_2_stop();
        }        
    }
}

void audio_initialize_hardware() {
//#if defined(AUDIO_PIN_A4)
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD1, &dac_conf_ch1);
    dacStartConversion(&DACD1, &dac_conv_grp_ch1, (dacsample_t *)dac_buffer_1, DAC_BUFFER_SIZE);
//#endif
//#if defined(AUDIO_PIN_A5)
    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD2, &dac_conf_ch2);
    dacStartConversion(&DACD2, &dac_conv_grp_ch2, (dacsample_t *)dac_buffer_2, DAC_BUFFER_SIZE);
//#endif

    /* enable the output buffer, to directly drive external loads with no additional circuitry
     *
     * see: AN4566 Application note: Extending the DAC performance of STM32 microcontrollers
     * Note: Buffer-Off bit -> has to be set 0 to enable the output buffer
     * Note: enabling the output buffer imparts an additional dc-offset of a couple mV
     *
     * this is done here, reaching directly into the stm32 registers since chibios has not implemented BOFF handling yet
     * (see: chibios/os/hal/ports/STM32/todo.txt '- BOFF handling in DACv1.'
     */
//#if defined(AUDIO_PIN_A4)
    DACD1.params->dac->CR &= ~DAC_CR_BOFF1;
//#endif
//#if defined(AUDIO_PIN_A5)
    DACD2.params->dac->CR &= ~DAC_CR_BOFF2;
//#endif

    // initialize both timers used to trigger the DAC conversions
    gptStart(&GPTD6, &gpt6cfg1);
    gptStart(&GPTD7, &gpt7cfg1);

    // start state-updater
    gptStart(&GPTD8, &gpt8cfg1);
}

void audio_stop_hardware(void) {
    gptStopTimer(&GPTD6);
    gptStopTimer(&GPTD7);
    gptStopTimer(&GPTD8);
}

void audio_start_hardware(void) {
    gptStartContinuous(&GPTD8, 2U);
}
