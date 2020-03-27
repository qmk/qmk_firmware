/* Copyright 2020 Jack Humbert
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

this driver uses the chibios-PWM system to produce a squarewave on a given output pin.
Either in software through a pwm callback and set/clear; or through the pwm hardware which directly toggles the pin via its alternate function. see your MCUs datasheet for which pin can be driven by what timer - looking for TIMx_CHy and the corresponding alternate function.

 */


/* STM32F103C8 Setup:
halconf.h:
#define HAL_USE_PWM                 TRUE
#define HAL_USE_PAL                 TRUE
#define HAL_USE_GPT                 TRUE

mcuconf.h:
#define STM32_PWM_USE_TIM1                  TRUE
#define STM32_GPT_USE_TIM3                  TRUE

used pin: PA8 (alternate0: TIM1_CH1)

from the datasheet for STM32F103C8: alternate function of pin
TIM1_CH1 = PA8 <-
TIM1_CH2 = PA9
TIM1_CH3 = PA10
TIM1_CH4 = PA11

so adding to config.h:
#define AUDIO_PIN A8
#define AUDIO_PWM_PINALTERNATE_TIMER 1
#define AUDIO_PWM_PINALTERNATE_TIMERCHANNEL 1
*/

#include "audio.h"
#include "ch.h"
#include "hal.h"


#if defined (AUDIO_DRIVER_PWM)
#    if !defined(AUDIO_PIN)
#        error "Audio feature enabled, but no pin selected - see docs/feature_audio under the ARM PWM settings"
#    endif
#endif


// some preprocessor trickery to get the corresponding chibios-PWMDriver
#define TO_CHIBIOS_PWMD_PASTE(t) (PWMD##t)
#define TO_CHIBIOS_PWMD_EVAL(t) TO_CHIBIOS_PWMD_PASTE(t)
#define PWMD TO_CHIBIOS_PWMD_EVAL(AUDIO_PWM_PINALTERNATE_TIMER)

extern int  active_tones;
extern bool playing_note;
extern bool playing_notes;

#if defined(AUDIO_DRIVER_PWM)
static void pwm_audio_period_callback(PWMDriver *pwmp);
static void pwm_audio_channel_interrupt_callback(PWMDriver *pwmp);
#endif // AUDIO_DRIVER_PWM

static PWMConfig pwmCFG = {.frequency = 100000, /* PWM clock frequency  */
                           //CHIBIOS-BUG? can't set the initial period to <2, or the pwm (hard or software) takes ~130ms with .frequency=500000 for a pwmChangePeriod to take effect; with no ouput=silence in the meantime
                           .period = 2,     /* initial PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
#if defined(AUDIO_DRIVER_PWM_PIN_ALTERNATE)
                           .callback = NULL, // no callback, the hardware directly toggles the pin
#else // AUDIO_DRIVER_PWM
                           .callback = pwm_audio_period_callback,
#endif
                           .channels = {
#if AUDIO_DRIVER_PWM_PIN_ALTERNATE
#    if AUDIO_PWM_PINALTERNATE_TIMERCHANNEL == 4
                               {PWM_OUTPUT_DISABLED, NULL},   /* channel 0 -> TIMx_CH1 */
                               {PWM_OUTPUT_DISABLED, NULL},   /* channel 1 -> TIMx_CH2 */
                               {PWM_OUTPUT_DISABLED, NULL},   /* channel 2 -> TIMx_CH3 */
                               {PWM_OUTPUT_ACTIVE_HIGH, NULL} /* channel 3 -> TIMx_CH4 */
#    elif AUDIO_PWM_PINALTERNATE_TIMERCHANNEL == 3
                               {PWM_OUTPUT_DISABLED, NULL},
                               {PWM_OUTPUT_DISABLED, NULL},
                               {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* TIMx_CH3 */
                               {PWM_OUTPUT_DISABLED, NULL}
#    elif AUDIO_PWM_PINALTERNATE_TIMERCHANNEL == 2
                               {PWM_OUTPUT_DISABLED, NULL},
                               {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* TIMx_CH2 */
                               {PWM_OUTPUT_DISABLED, NULL},
                               {PWM_OUTPUT_DISABLED, NULL}
#    else /*fallback to CH1 */
                               {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* TIMx_CH1 */
                               {PWM_OUTPUT_DISABLED, NULL},
                               {PWM_OUTPUT_DISABLED, NULL},
                               {PWM_OUTPUT_DISABLED, NULL}
#    endif // AUDIO_DRIVER_PWM_PIN_ALTERNATE_CHANNEL
#else // AUDIO_DRIVER_PWM
                               // software-PWM just needs another callback on any channel
                               {PWM_OUTPUT_ACTIVE_HIGH, pwm_audio_channel_interrupt_callback}, /* channel 0 -> TIMx_CH1 */
                               {PWM_OUTPUT_DISABLED, NULL}, /* channel 1 -> TIMx_CH2 */
                               {PWM_OUTPUT_DISABLED, NULL}, /* channel 2 -> TIMx_CH3 */
                               {PWM_OUTPUT_DISABLED, NULL}  /* channel 3 -> TIMx_CH4 */
#endif
                           },
                       };


static float channel_1_frequency = 0.0f;
void channel_1_set_frequency(float freq) {
//    if (freq == channel_1_frequency) return;
    //TODO: interrupt same-frequency notes?

    channel_1_frequency = freq;

    if (freq <= 0.0) //a pause/rest has freq=0
        return;

    pwmcnt_t period = (pwmCFG.frequency / freq);
    pwmChangePeriod(&PWMD, period);
    pwmEnableChannel(
                     &PWMD,
                     AUDIO_PWM_PINALTERNATE_TIMERCHANNEL -1,
                     PWM_PERCENTAGE_TO_WIDTH(&PWMD, 5000) /*TODO: adjust by timbre */
                     );
}

float channel_1_get_frequency(void) { return channel_1_frequency; }

void channel_1_start(void) {
    pwmStop(&PWMD);
    pwmStart(&PWMD, &pwmCFG);

#if defined(AUDIO_DRIVER_PWM)
    pwmEnablePeriodicNotification(&PWMD);
    pwmEnableChannelNotification(&PWMD, AUDIO_PWM_PINALTERNATE_TIMERCHANNEL-1);
#endif
}

void channel_1_stop(void) {
    pwmStop(&PWMD);

#if defined(AUDIO_DRIVER_PWM)
    palClearLine(AUDIO_PIN); // leave the line low, after last note was played
#endif
}

#if defined(AUDIO_DRIVER_PWM)
// generate a PWM signal on any pin, not neccessarily the one connected to the timer
static void pwm_audio_period_callback(PWMDriver *pwmp) {
    (void)pwmp;
    palClearLine(AUDIO_PIN);
}
static void pwm_audio_channel_interrupt_callback(PWMDriver *pwmp) {
    (void)pwmp;
    if (channel_1_frequency > 0)
        palSetLine(AUDIO_PIN);  // generate a PWM signal on any pin, not neccessarily the one connected to the timer
}
#endif // AUDIO_DRIVER_PWM

static void gpt_callback(GPTDriver *gptp);
GPTConfig   gptCFG = {
    /* a whole note is one beat, which is - per definition in musical_notes.h - set to 64
       the longest note is BREAVE_DOT=128+64=192, the shortest SIXTEENTH=4
       the tempo (which might vary!) is in bpm (beats per minute)
       therefore: if the timer ticks away at .frequency = (60*64)Hz,
       and the .intervall counts from 64 downwards - all we need to do is increment the
       note_position on each callback, and have the note_lengt = duration*tempo compare
       against that; hence: audio_advance_note(step=1, end=1)
    */
    .frequency = 60 * 64,
    .callback  = gpt_callback,
};

void audio_initialize_hardware(void) {
    pwmStart(&PWMD, &pwmCFG);

#if defined(AUDIO_DRIVER_PWM_PIN_ALTERNATE)
#    if defined(USE_GPIOV1) // STM32F103C8
    palSetLineMode(AUDIO_PIN, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
#    else // GPIOv2 (or GPIOv3 for f4xx, which is the same/compatible at this command)
    palSetLineMode(AUDIO_PIN, PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(AUDIO_PWM_PINALTERNATE_FUNCTION));
#    endif
#else // AUDIO_DRIVER_PWM
    palSetLineMode(AUDIO_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(AUDIO_PIN);

    pwmEnablePeriodicNotification(&PWMD); // enable pwm callbacks
    pwmEnableChannelNotification(&PWMD, AUDIO_PWM_PINALTERNATE_TIMERCHANNEL-1);
#endif // AUDIO_DRIVER_PWM

    gptStart(&GPTD6, &gptCFG);
}

void audio_start_hardware(void) {
    float freq;// TODO: freq_alt
    channel_1_stop();
    channel_1_start();

    if (playing_note) {
        freq = audio_get_processed_frequency(0);
        channel_1_set_frequency(freq);
    }
    if (playing_notes) {
        gptStartContinuous(&GPTD6, 64);
    }
}

void audio_stop_hardware(void) {
    channel_1_stop();
    gptStopTimer(&GPTD6);
}

/* a regular timer task, that checks the note to be currently played
 * and updates the pwm to output that frequency
 */
static void gpt_callback(GPTDriver *gptp) {
    float freq;// TODO: freq_alt

    if (audio_advance_note(1, 1)) {
        freq = audio_get_processed_frequency(0); // freq_alt would be index=1
        channel_1_set_frequency(freq);
    }
}
