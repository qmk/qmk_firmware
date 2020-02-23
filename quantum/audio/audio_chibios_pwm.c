/* Copyright 2019 Jack Humbert
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
#    define ARM_PWM_USE_PIN_ALTERNATE 1
#endif

#ifndef ARM_PWM_AUDIO_PORT
#    define ARM_PWM_AUDIO_PORT GPIOC
#endif
#ifndef ARM_PWM_AUDIO_PIN
#    define ARM_PWM_AUDIO_PIN 13
#endif
// -----------------------------------------------------------------------------

#define AUDIO_PIN PAL_LINE(ARM_PWM_AUDIO_PORT, ARM_PWM_AUDIO_PIN)

extern int  voices;
extern bool playing_notes;

#if !(ARM_PWM_USE_PIN_ALTERNATE)
static void pwm_audio_period_callback(PWMDriver *pwmp);
static void pwm_audio_channel_interrupt_callback(PWMDriver *pwmp);
#endif

static PWMConfig pwmCFG = {100000, /* PWM clock frequency  */
                           10,     /* initial PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
#if ARM_PWM_USE_PIN_ALTERNATE
                           NULL,
#else
                           pwm_audio_period_callback,
#endif
                           {
#if ARM_PWM_USE_PIN_ALTERNATE
                               {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* channel 0 -> TIM1-CH1 = PA8 */
#else
                               /* on the STM32F104C8B: alternate function of pin */
                               {PWM_OUTPUT_ACTIVE_HIGH, pwm_audio_channel_interrupt_callback}, /* channel 0 -> TIM1-CH1 = PA8 */
#endif
                               {PWM_OUTPUT_DISABLED, NULL}, /* channel 1 -> TIM1-CH2 = PA9 */
                               {PWM_OUTPUT_DISABLED, NULL}, /* channel 2 -> TIM1-CH3 = PA10 */
                               {PWM_OUTPUT_DISABLED, NULL}  /* channel 3 -> TIM1-CH4 = PA11 */
                           },
                           0, /* HW dependent part.*/
                           0};

static float channel_1_frequency = 0.0f;
void         channel_1_set_frequency(float freq) {
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
    pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 5000));

#if !(ARM_PWM_USE_PIN_ALTERNATE)
    pwmEnablePeriodicNotification(&PWMD1);  // enable pwm callbacks
    pwmEnableChannelNotification(&PWMD1, 0);
#endif
}

void channel_1_stop(void) { pwmStop(&PWMD1); }

#if !(ARM_PWM_USE_PIN_ALTERNATE)
static void pwm_audio_period_callback(PWMDriver *pwmp) {
    (void)pwmp;
    palClearLine(AUDIO_PIN);

    /* hm, using the pwm callback, instead of the gpt timer does not work :-(
        float freq, freq_alt;
        pwm_audio_timer_task(&freq, &freq_alt);

        if (playing_notes)
            channel_1_set_frequency(freq);
        else
            channel_1_stop();
    */
}
static void pwm_audio_channel_interrupt_callback(PWMDriver *pwmp) {
    (void)pwmp;
    palSetLine(AUDIO_PIN);  // generate a PWM signal on any pin, not neccessarily the one connected to the timer
}
#endif

static void gpt_cb8(GPTDriver *gptp);
GPTConfig   gpt8cfg1 = {.frequency = 10,
                      .callback  = gpt_cb8,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

void audio_initialize_hardware(void) {
    pwmStart(&PWMD1, &pwmCFG);

    pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 5000));

#if ARM_PWM_USE_PIN_ALTERNATE
    // on STM32F103C8B: PA8.alternate0 = output of TIM1-CH1
    palSetPadMode(GPIOA, 8, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
#else
    palSetLineMode(AUDIO_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(AUDIO_PIN);

    pwmEnablePeriodicNotification(&PWMD1);  // enable pwm callbacks
    pwmEnableChannelNotification(&PWMD1, 0);
#endif

    audio_start_hardware();
}

void audio_start_hardware(void) {
    channel_1_stop();
    channel_1_start();

    gptStart(&GPTD3, &gpt8cfg1);
    gptStartContinuous(&GPTD3, 2U);
}

void audio_stop_hardware(void) {
    channel_1_stop();
    gptStopTimer(&GPTD3);
}

/* regular timer task, that checks the note to be currently played, updates the pwm to output that frequency
 */
static void gpt_cb8(GPTDriver *gptp) {
    float freq, freq_alt;
    pwm_audio_timer_task(&freq, &freq_alt);

    if (playing_notes)
        channel_1_set_frequency(freq);
    else
        channel_1_stop();
}
