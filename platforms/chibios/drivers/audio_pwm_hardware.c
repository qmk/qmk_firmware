// Copyright 2022 Stefan Kerkmann
// Copyright 2020 Jack Humbert
// Copyright 2020 JohSchneider
// SPDX-License-Identifier: GPL-2.0-or-later

// Audio Driver: PWM the duty-cycle is always kept at 50%, and the pwm-period is
// adjusted to match the frequency of a note to be played back. This driver uses
// the chibios-PWM system to produce a square-wave on specific output pins that
// are connected to the PWM hardware. The hardware directly toggles the pin via
// its alternate function. see your MCUs data-sheet for which pin can be driven
// by what timer - looking for TIMx_CHy and the corresponding alternate
// function.

#include "audio.h"
#include "gpio.h"

#if !defined(AUDIO_PIN)
#    error "Audio feature enabled, but no pin selected - see docs/feature_audio under the ARM PWM settings"
#endif

#if !defined(AUDIO_PWM_COUNTER_FREQUENCY)
#    define AUDIO_PWM_COUNTER_FREQUENCY 100000
#endif

#ifndef AUDIO_PWM_COMPLEMENTARY_OUTPUT
#    define AUDIO_PWM_OUTPUT_MODE PWM_OUTPUT_ACTIVE_HIGH
#else
#    define AUDIO_PWM_OUTPUT_MODE PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH
#endif

extern bool    playing_note;
extern bool    playing_melody;
extern uint8_t note_timbre;

static PWMConfig pwmCFG = {.frequency = AUDIO_PWM_COUNTER_FREQUENCY, /* PWM clock frequency  */
                           .period    = 2,
                           .callback  = NULL,
                           .channels  = {[(AUDIO_PWM_CHANNEL - 1)] = {.mode = AUDIO_PWM_OUTPUT_MODE, .callback = NULL}}};

static float channel_1_frequency = 0.0f;

void channel_1_set_frequency(float freq) {
    channel_1_frequency = freq;

    if (freq <= 0.0) {
        // a pause/rest has freq=0
        return;
    }

    pwmcnt_t period = (pwmCFG.frequency / freq);
    chSysLockFromISR();
    pwmChangePeriodI(&AUDIO_PWM_DRIVER, period);
    pwmEnableChannelI(&AUDIO_PWM_DRIVER, AUDIO_PWM_CHANNEL - 1,
                      // adjust the duty-cycle so that the output is for 'note_timbre' duration HIGH
                      PWM_PERCENTAGE_TO_WIDTH(&AUDIO_PWM_DRIVER, (100 - note_timbre) * 100));
    chSysUnlockFromISR();
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

static virtual_timer_t audio_vt;
static void            audio_callback(virtual_timer_t *vtp, void *p);

// a regular timer task, that checks the note to be currently played and updates
// the pwm to output that frequency.
static void audio_callback(virtual_timer_t *vtp, void *p) {
    float freq; // TODO: freq_alt

    if (audio_update_state()) {
        freq = audio_get_processed_frequency(0); // freq_alt would be index=1
        channel_1_set_frequency(freq);
    }

    chSysLockFromISR();
    chVTSetI(&audio_vt, TIME_MS2I(16), audio_callback, NULL);
    chSysUnlockFromISR();
}

void audio_driver_initialize(void) {
    pwmStart(&AUDIO_PWM_DRIVER, &pwmCFG);

    // connect the AUDIO_PIN to the PWM hardware
#if defined(USE_GPIOV1) // STM32F103C8, RP2040
    palSetLineMode(AUDIO_PIN, AUDIO_PWM_PAL_MODE);
#else // GPIOv2 (or GPIOv3 for f4xx, which is the same/compatible at this command)
    palSetLineMode(AUDIO_PIN, PAL_MODE_ALTERNATE(AUDIO_PWM_PAL_MODE));
#endif

    chVTObjectInit(&audio_vt);
}

void audio_driver_start(void) {
    channel_1_stop();
    channel_1_start();

    if ((playing_note || playing_melody) && !chVTIsArmed(&audio_vt)) {
        // a whole note is one beat, which is - per definition in
        // musical_notes.h - set to 64 the longest note is
        // BREAVE_DOT=128+64=192, the shortest SIXTEENTH=4 the tempo (which
        // might vary!) is in bpm (beats per minute) therefore: if the timer
        // ticks away at 64Hz (~16.6ms) audio_update_state is called just often
        // enough to not miss any notes
        chVTSet(&audio_vt, TIME_MS2I(16), audio_callback, NULL);
    }
}

void audio_driver_stop(void) {
    channel_1_stop();
    chVTReset(&audio_vt);
}
