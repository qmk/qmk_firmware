/* Copyright 2020 Jack Humbert
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

/*
Audio Driver: PWM

the duty-cycle is always kept at 50%, and the pwm-period is adjusted to match the frequency of a note to be played back.

this driver uses the chibios-PWM system to produce a square-wave on specific output pins that are connected to the PWM hardware.
The hardware directly toggles the pin via its alternate function. see your MCUs data-sheet for which pin can be driven by what timer - looking for TIMx_CHy and the corresponding alternate function.

 */

#include "audio.h"
#include "ch.h"
#include "hal.h"

#if !defined(AUDIO_PIN)
#    error "Audio feature enabled, but no pin selected - see docs/feature_audio under the ARM PWM settings"
#endif

extern bool    playing_note;
extern bool    playing_melody;
extern uint8_t note_timbre;

static PWMConfig pwmCFG = {
    .frequency = 100000, /* PWM clock frequency  */
    // CHIBIOS-BUG? can't set the initial period to <2, or the pwm (hard or software) takes ~130ms with .frequency=500000 for a pwmChangePeriod to take effect; with no output=silence in the meantime
    .period   = 2,    /* initial PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
    .callback = NULL, /* no callback, the hardware directly toggles the pin */
    .channels =
        {
#if AUDIO_PWM_CHANNEL == 4
            {PWM_OUTPUT_DISABLED, NULL},   /* channel 0 -> TIMx_CH1 */
            {PWM_OUTPUT_DISABLED, NULL},   /* channel 1 -> TIMx_CH2 */
            {PWM_OUTPUT_DISABLED, NULL},   /* channel 2 -> TIMx_CH3 */
            {PWM_OUTPUT_ACTIVE_HIGH, NULL} /* channel 3 -> TIMx_CH4 */
#elif AUDIO_PWM_CHANNEL == 3
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* TIMx_CH3 */
            {PWM_OUTPUT_DISABLED, NULL}
#elif AUDIO_PWM_CHANNEL == 2
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* TIMx_CH2 */
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_DISABLED, NULL}
#else /*fallback to CH1 */
            {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* TIMx_CH1 */
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_DISABLED, NULL}
#endif
        },
};

static float channel_1_frequency = 0.0f;
void         channel_1_set_frequency(float freq) {
    channel_1_frequency = freq;

    if (freq <= 0.0) // a pause/rest has freq=0
        return;

    pwmcnt_t period = (pwmCFG.frequency / freq);
    pwmChangePeriod(&AUDIO_PWM_DRIVER, period);
    pwmEnableChannel(&AUDIO_PWM_DRIVER, AUDIO_PWM_CHANNEL - 1,
                     // adjust the duty-cycle so that the output is for 'note_timbre' duration HIGH
                     PWM_PERCENTAGE_TO_WIDTH(&AUDIO_PWM_DRIVER, (100 - note_timbre) * 100));
}

float channel_1_get_frequency(void) {
    return channel_1_frequency;
}

void channel_1_start(void) {
    pwmStop(&AUDIO_PWM_DRIVER);
    pwmStart(&AUDIO_PWM_DRIVER, &pwmCFG);
}

void channel_1_stop(void) {
    pwmStop(&AUDIO_PWM_DRIVER);
}

static void gpt_callback(GPTDriver *gptp);
GPTConfig   gptCFG = {
    /* a whole note is one beat, which is - per definition in musical_notes.h - set to 64
       the longest note is BREAVE_DOT=128+64=192, the shortest SIXTEENTH=4
       the tempo (which might vary!) is in bpm (beats per minute)
       therefore: if the timer ticks away at .frequency = (60*64)Hz,
       and the .interval counts from 64 downwards - audio_update_state is
       called just often enough to not miss any notes
    */
    .frequency = 60 * 64,
    .callback  = gpt_callback,
};

void audio_driver_initialize(void) {
    pwmStart(&AUDIO_PWM_DRIVER, &pwmCFG);

    // connect the AUDIO_PIN to the PWM hardware
#if defined(USE_GPIOV1) // STM32F103C8
    palSetLineMode(AUDIO_PIN, PAL_MODE_ALTERNATE_PUSHPULL);
#else // GPIOv2 (or GPIOv3 for f4xx, which is the same/compatible at this command)
    palSetLineMode(AUDIO_PIN, PAL_MODE_ALTERNATE(AUDIO_PWM_PAL_MODE));
#endif

    gptStart(&AUDIO_STATE_TIMER, &gptCFG);
}

void audio_driver_start(void) {
    channel_1_stop();
    channel_1_start();

    if (playing_note || playing_melody) {
        gptStartContinuous(&AUDIO_STATE_TIMER, 64);
    }
}

void audio_driver_stop(void) {
    channel_1_stop();
    gptStopTimer(&AUDIO_STATE_TIMER);
}

/* a regular timer task, that checks the note to be currently played
 * and updates the pwm to output that frequency
 */
static void gpt_callback(GPTDriver *gptp) {
    float freq; // TODO: freq_alt

    if (audio_update_state()) {
        freq = audio_get_processed_frequency(0); // freq_alt would be index=1
        channel_1_set_frequency(freq);
    }
}
