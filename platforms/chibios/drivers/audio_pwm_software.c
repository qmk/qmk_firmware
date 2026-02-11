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

this driver uses the chibios-PWM system to produce a square-wave on any given output pin in software
- a pwm callback is used to set/clear the configured pin.

 */
#include "audio.h"
#include "gpio.h"

#if !defined(AUDIO_PIN)
#    error "Audio feature enabled, but no pin selected - see docs/feature_audio under the ARM PWM settings"
#endif
extern bool    playing_note;
extern bool    playing_melody;
extern uint8_t note_timbre;

static void pwm_audio_period_callback(PWMDriver *pwmp);
static void pwm_audio_channel_interrupt_callback(PWMDriver *pwmp);

static PWMConfig pwmCFG = {
    .frequency = 100000, /* PWM clock frequency  */
    // CHIBIOS-BUG? can't set the initial period to <2, or the pwm (hard or software) takes ~130ms with .frequency=500000 for a pwmChangePeriod to take effect; with no output=silence in the meantime
    .period   = 2, /* initial PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
    .callback = pwm_audio_period_callback,
    .channels =
        {
            // software-PWM just needs another callback on any channel
            {PWM_OUTPUT_ACTIVE_HIGH, pwm_audio_channel_interrupt_callback}, /* channel 0 -> TIMx_CH1 */
            {PWM_OUTPUT_DISABLED, NULL},                                    /* channel 1 -> TIMx_CH2 */
            {PWM_OUTPUT_DISABLED, NULL},                                    /* channel 2 -> TIMx_CH3 */
            {PWM_OUTPUT_DISABLED, NULL}                                     /* channel 3 -> TIMx_CH4 */
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

    pwmEnablePeriodicNotification(&AUDIO_PWM_DRIVER);
    pwmEnableChannelNotification(&AUDIO_PWM_DRIVER, AUDIO_PWM_CHANNEL - 1);
}

void channel_1_stop(void) {
    pwmStop(&AUDIO_PWM_DRIVER);

    palClearLine(AUDIO_PIN); // leave the line low, after last note was played

#if defined(AUDIO_PIN_ALT) && defined(AUDIO_PIN_ALT_AS_NEGATIVE)
    palClearLine(AUDIO_PIN_ALT); // leave the line low, after last note was played
#endif
}

// generate a PWM signal on any pin, not necessarily the one connected to the timer
static void pwm_audio_period_callback(PWMDriver *pwmp) {
    (void)pwmp;
    palClearLine(AUDIO_PIN);

#if defined(AUDIO_PIN_ALT) && defined(AUDIO_PIN_ALT_AS_NEGATIVE)
    palSetLine(AUDIO_PIN_ALT);
#endif
}
static void pwm_audio_channel_interrupt_callback(PWMDriver *pwmp) {
    (void)pwmp;
    if (channel_1_frequency > 0) {
        palSetLine(AUDIO_PIN); // generate a PWM signal on any pin, not necessarily the one connected to the timer
#if defined(AUDIO_PIN_ALT) && defined(AUDIO_PIN_ALT_AS_NEGATIVE)
        palClearLine(AUDIO_PIN_ALT);
#endif
    }
}

static void gpt_callback(GPTDriver *gptp);
GPTConfig   gptCFG = {
    /* a whole note is one beat, which is - per definition in musical_notes.h - set to 64
       the longest note is BREAVE_DOT=128+64=192, the shortest SIXTEENTH=4
       the tempo (which might vary!) is in bpm (beats per minute)
       therefore: if the timer ticks away at .frequency = (60*64)Hz,
       and the .interval counts from 64 downwards - audio_update_state is
       called just often enough to not miss anything
    */
      .frequency = 60 * 64,
      .callback  = gpt_callback,
};

void audio_driver_initialize_impl(void) {
    pwmStart(&AUDIO_PWM_DRIVER, &pwmCFG);

    palSetLineMode(AUDIO_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(AUDIO_PIN);

#if defined(AUDIO_PIN_ALT) && defined(AUDIO_PIN_ALT_AS_NEGATIVE)
    palSetLineMode(AUDIO_PIN_ALT, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(AUDIO_PIN_ALT);
#endif

    pwmEnablePeriodicNotification(&AUDIO_PWM_DRIVER); // enable pwm callbacks
    pwmEnableChannelNotification(&AUDIO_PWM_DRIVER, AUDIO_PWM_CHANNEL - 1);

    gptStart(&AUDIO_STATE_TIMER, &gptCFG);
}

void audio_driver_start_impl(void) {
    channel_1_stop();
    channel_1_start();

    if (playing_note || playing_melody) {
        gptStartContinuous(&AUDIO_STATE_TIMER, 64);
    }
}

void audio_driver_stop_impl(void) {
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
