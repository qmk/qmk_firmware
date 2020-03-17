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

/* STM32F103C Setup:
halconf.h:
#define HAL_USE_PWM                 TRUE
#define HAL_USE_PAL                 TRUE
#define HAL_USE_GPT                 TRUE

mcuconf.h:
#define STM32_PWM_USE_TIM1                  TRUE
#define STM32_GPT_USE_TIM3                  TRUE

used pin: PA8 (alternate0: Tim1_Ch1)

from the datasheet for STM32F104C8B: alternate function of pin
TIM1_CH1 = PA8
TIM1_CH2 = PA9
TIM1_CH3 = PA10
TIM1_CH4 = PA11


to use another hardware-pwm pin:
- check the datasheet for the timer_channel and the alternate-function
- replace PWMDx with the required timer
- reorder the PCMConfig.channels to match the TIMx_CHy (the stm datasheets usually have CH1 to CH4)
- set the pin to the appropiate alternate function (beware: differences in chibios GPIOv1, v2, ...)
*/

#include "audio.h"
#include "ch.h"
#include "hal.h"

#include <string.h>
#include "print.h"

/* either use the direct hardware connection of Timer1-Channel1 to GPIOA.8
   via the pins alternate-function to drive a piezo speaker
   OR set this define to zero and have the timer callbacks toggle your pin of choice
*/
#ifndef ARM_PWM_USE_PIN_ALTERNATE
#    define ARM_PWM_USE_PIN_ALTERNATE 0
#endif

#ifndef ARM_PWM_AUDIO_PIN
#    define ARM_PWM_AUDIO_PIN A10
#endif
// -----------------------------------------------------------------------------

extern int  voices;
extern bool playing_notes;

#if !(ARM_PWM_USE_PIN_ALTERNATE)
static void pwm_audio_period_callback(PWMDriver *pwmp);
static void pwm_audio_channel_interrupt_callback(PWMDriver *pwmp);
#endif

static PWMConfig pwmCFG = {.frequency = 100000, /* PWM clock frequency  */
                           .period = 0,     /* initial PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
#if ARM_PWM_USE_PIN_ALTERNATE
                           .callback = NULL, // no callback, the hardware directly toggles the pin
#else
                           .callback = pwm_audio_period_callback,
#endif
                           .channels = {
#if ARM_PWM_USE_PIN_ALTERNATE
                               {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* channel 0 -> TIM1_CH1 */
#else
                               {PWM_OUTPUT_ACTIVE_HIGH, pwm_audio_channel_interrupt_callback}, /* channel 0 -> TIM1_CH1 */
#endif
                               {PWM_OUTPUT_DISABLED, NULL}, /* channel 1 -> TIM1_CH2 */
                               {PWM_OUTPUT_DISABLED, NULL}, /* channel 2 -> TIM1_CH3 */
                               {PWM_OUTPUT_DISABLED, NULL}  /* channel 3 -> TIM1_CH4 */
                           },
                           };

static float channel_1_frequency = 0.0f;
void channel_1_set_frequency(float freq) {
    if (freq == channel_1_frequency) return;

    channel_1_frequency = freq;

    pwmcnt_t period = (pwmCFG.frequency / freq);
    pwmChangePeriod(&PWMD1, period);
    pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 5000));
}

float channel_1_get_frequency(void) { return channel_1_frequency; }

void channel_1_start(void) {
    pwmStop(&PWMD1);
    pwmStart(&PWMD1, &pwmCFG);

#if !(ARM_PWM_USE_PIN_ALTERNATE)
    pwmEnablePeriodicNotification(&PWMD1);
    pwmEnableChannelNotification(&PWMD1, 0);
#endif
}

void channel_1_stop(void) {
    pwmStop(&PWMD1);

#if !(ARM_PWM_USE_PIN_ALTERNATE)
    palClearLine(ARM_PWM_AUDIO_PIN); // leave the line low, after last note was played
#endif
}

#if !(ARM_PWM_USE_PIN_ALTERNATE)
static void pwm_audio_period_callback(PWMDriver *pwmp) {
    (void)pwmp;
    palClearLine(ARM_PWM_AUDIO_PIN);

    /* hm, using the pwm callback, instead of the gpt timer does not work :-(
        float freq, freq_alt;
        pwm_audio_timer_task(&freq, &freq_alt);

        if (playing_notes)
            channel_1_set_frequency(freq);
        else
            channel_1_stop();
    //*/
}
static void pwm_audio_channel_interrupt_callback(PWMDriver *pwmp) {
    (void)pwmp;
    palSetLine(ARM_PWM_AUDIO_PIN);  // generate a PWM signal on any pin, not neccessarily the one connected to the timer
}
#endif

static void gpt_callback(GPTDriver *gptp);
GPTConfig   gptCFG = {.frequency = 10,
                      .callback  = gpt_callback,
};

void audio_initialize_hardware(void) {
    pwmStart(&PWMD1, &pwmCFG);

#if ARM_PWM_USE_PIN_ALTERNATE
#    ifdef PAL_MODE_STM32_ALTERNATE_PUSHPULL
	//TODO: is there a better way to differentiate between chibios GPIOv1 and GPIOv2?
    palSetLineMode(A8, PAL_MODE_STM32_ALTERNATE_PUSHPULL); //f103 with GPIOv1
#    else
    palSetLineMode(A8, PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(6) );//f303xx with GPIOV2
#    endif
#else
    palSetLineMode(ARM_PWM_AUDIO_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(ARM_PWM_AUDIO_PIN);

    pwmEnablePeriodicNotification(&PWMD1); // enable pwm callbacks
    pwmEnableChannelNotification(&PWMD1, 0);
#endif

    gptStart(&GPTD6, &gptCFG);
}

void audio_start_hardware(void) {
    channel_1_stop();
    channel_1_start();
    gptStartContinuous(&GPTD6, 3U); // interval-ticks adjusts the note playback rate (++ for slower, -- for faster)
}

void audio_stop_hardware(void) {
    channel_1_stop();
    gptStopTimer(&GPTD6);
}

/* a regular timer task, that checks the note to be currently played
 * and updates the pwm to output that frequency
 */
static void gpt_callback(GPTDriver *gptp) {
    float freq, freq_alt;
    pwm_audio_timer_task(&freq, &freq_alt);

    if (playing_notes)
        channel_1_set_frequency(freq);
    else
        channel_1_stop();
}
