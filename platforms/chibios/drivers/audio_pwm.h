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
#pragma once

#if !defined(AUDIO_PWM_DRIVER)
// NOTE: Timer2 seems to be used otherwise in QMK, otherwise we could default to A5 (= TIM2_CH1, with PWMD2 and alternate-function(1))
#    define AUDIO_PWM_DRIVER PWMD1
#endif

#if !defined(AUDIO_PWM_CHANNEL)
// NOTE: sticking to the STM data-sheet numbering: TIMxCH1 to TIMxCH4
// default: STM32F303CC PA8+TIM1_CH1 -> 1
#    define AUDIO_PWM_CHANNEL 1
#endif

#if !defined(AUDIO_PWM_PAL_MODE)
// pin-alternate function: see the data-sheet for which pin needs what AF to connect to TIMx_CHy
// default: STM32F303CC PA8+TIM1_CH1 -> 6
#    define AUDIO_PWM_PAL_MODE 6
#endif

#if !defined(AUDIO_STATE_TIMER)
// timer used to trigger updates in the audio-system, configured/enabled in chibios mcuconf.
// Tim6 is the default for "larger" STMs, smaller ones might not have this one (enabled) and need to switch to a different one (e.g.: STM32F103 has only Tim1-Tim4)
#    define AUDIO_STATE_TIMER GPTD6
#endif
