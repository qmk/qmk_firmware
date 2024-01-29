/* Copyright 2019 Jack Humbert
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

#ifndef A4
#    define A4 PAL_LINE(GPIOA, 4)
#endif
#ifndef A5
#    define A5 PAL_LINE(GPIOA, 5)
#endif

/**
 * Highest value allowed sample value.

 * since the DAC is limited to 12 bit, the absolute max is 0xfff = 4095U;
 * lower values adjust the peak-voltage aka volume down.
 * adjusting this value has only an effect on a sample-buffer whose values are
 * are NOT pregenerated - see square-wave
 */
#ifndef AUDIO_DAC_SAMPLE_MAX
#    define AUDIO_DAC_SAMPLE_MAX 4095U
#endif

#if !defined(AUDIO_DAC_SAMPLE_RATE) && !defined(AUDIO_MAX_SIMULTANEOUS_TONES) && !defined(AUDIO_DAC_QUALITY_VERY_LOW) && !defined(AUDIO_DAC_QUALITY_LOW) && !defined(AUDIO_DAC_QUALITY_HIGH) && !defined(AUDIO_DAC_QUALITY_VERY_HIGH)
#    define AUDIO_DAC_QUALITY_SANE_MINIMUM
#endif

/**
 * These presets allow you to quickly switch between quality settings for
 * the DAC. The sample rate and maximum number of simultaneous tones roughly
 * has an inverse relationship - slightly higher sample rates may be possible.
 *
 * NOTE: a high sample-rate results in a higher cpu-load, which might lead to
 *       (audible) discontinuities and/or starve other processes of cpu-time
 *       (like RGB-led back-lighting, ...)
 */
#ifdef AUDIO_DAC_QUALITY_VERY_LOW
#    define AUDIO_DAC_SAMPLE_RATE 11025U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 8
#endif

#ifdef AUDIO_DAC_QUALITY_LOW
#    define AUDIO_DAC_SAMPLE_RATE 22050U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 4
#endif

#ifdef AUDIO_DAC_QUALITY_HIGH
#    define AUDIO_DAC_SAMPLE_RATE 44100U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 2
#endif

#ifdef AUDIO_DAC_QUALITY_VERY_HIGH
#    define AUDIO_DAC_SAMPLE_RATE 88200U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 1
#endif

#ifdef AUDIO_DAC_QUALITY_SANE_MINIMUM
/* a sane-minimum config: with a trade-off between cpu-load and tone-range
 *
 * the (currently) highest defined note is NOTE_B8 with 7902Hz; if we now
 * aim for an even even multiple of the buffer-size, we end up with:
 * ( roundUptoPow2(highest note / AUDIO_DAC_BUFFER_SIZE) * nyquist-rate * AUDIO_DAC_BUFFER_SIZE)
 *                              7902/256 = 30.867        *       2      * 256 ~= 16384
 * which works out (but the 'scope shows some sampling artifacts with lower harmonics :-P)
 */
#    define AUDIO_DAC_SAMPLE_RATE 16384U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 8
#endif

/**
 * Effective bit-rate of the DAC. 44.1khz is the standard for most audio - any
 * lower will sacrifice perceptible audio quality. Any higher will limit the
 * number of simultaneous tones. In most situations, a tenth (1/10) of the
 * sample rate is where notes become unbearable.
 */
#ifndef AUDIO_DAC_SAMPLE_RATE
#    define AUDIO_DAC_SAMPLE_RATE 44100U
#endif

/**
 * Size of the dac_buffer array. This controls the length of the runtime buffer
 * which accumulates the data to be sent to the DAC every few milliseconds, and
 * it does not need to correspond to the length of the wavetable for the chosen
 * waveform defined by AUDIO_DAC_SAMPLE_WAVEFORM_* in the additive DAC driver.
 * By default, this is set to be as close to 3.3 ms as possible, giving 300 DAC
 * interrupts per second. Any smaller and the interrupt load gets too heavy and
 * this results in crackling due to buffer underrun in the additive DAC driver;
 * too large and the RAM (additive driver) or flash (basic driver) usage may be
 * too high, causing build failures, and matrix scanning is liable to have long
 * periodic pauses that delay key presses or releases or fully lose short taps.
 * Large buffers also cause notes to take longer to stop after they should from
 * music mode or MIDI input.
 * This should be a power of 2 for maximum compatibility.
 */
#ifndef AUDIO_DAC_BUFFER_SIZE
#    if AUDIO_DAC_SAMPLE_RATE < 5100U
#        define AUDIO_DAC_BUFFER_SIZE 16U
#    elif AUDIO_DAC_SAMPLE_RATE < 9900U
#        define AUDIO_DAC_BUFFER_SIZE 32U
#    elif AUDIO_DAC_SAMPLE_RATE < 19500U
#        define AUDIO_DAC_BUFFER_SIZE 64U
#    elif AUDIO_DAC_SAMPLE_RATE < 38700U
#        define AUDIO_DAC_BUFFER_SIZE 128U
#    else
#        define AUDIO_DAC_BUFFER_SIZE 256U
#    endif
#endif

/**
 * The number of tones that can be played simultaneously. If too high a value
 * is used here, the keyboard will freeze and glitch-out when that many tones
 * are being played.
 */
#ifndef AUDIO_MAX_SIMULTANEOUS_TONES
#    define AUDIO_MAX_SIMULTANEOUS_TONES 2
#endif

/**
 * The default value of the DAC when not playing anything. Certain hardware
 * setups may require a high (AUDIO_DAC_SAMPLE_MAX) or low (0) value here.
 * Since multiple added sine waves tend to oscillate around the midpoint,
 * and possibly never/rarely reach either 0 of MAX, 1/2 MAX can be a
 * reasonable default value.
 */
#ifndef AUDIO_DAC_OFF_VALUE
#    define AUDIO_DAC_OFF_VALUE AUDIO_DAC_SAMPLE_MAX / 2
#endif

#if AUDIO_DAC_OFF_VALUE > AUDIO_DAC_SAMPLE_MAX
#    error "AUDIO_DAC: OFF_VALUE may not be larger than SAMPLE_MAX"
#endif

/**
 * Check to see if the DAC triggers are set.
 * If not set them to the defaults for based on the detected MCU family.
 * If no family is set issue a info message to aid potential debug and default
 * to the Setting for a STM32F303.
 *
 * Here are all the values for DAC_TRG (TSEL in the ref manual) for the STM32F303
 * TIM15_TRGO 0b011
 * TIM2_TRGO  0b100
 * TIM3_TRGO  0b001
 * TIM6_TRGO  0b000
 * TIM7_TRGO  0b010
 * EXTI9      0b110
 * SWTRIG     0b111
 *
 * Other MCUs may vary and the relevant values can be found in there ref manuals
 */
#if !defined(AUDIO_DAC_CH1_TRIGGER)
#    if defined(QMK_MCU_SERIES_STM32G4XX)
#        define AUDIO_DAC_CH1_TRIGGER 0b0111
#    else
#        define AUDIO_DAC_CH1_TRIGGER 0b000
#        if !defined(QMK_MCU_SERIES_STM32F0XX) && !defined(QMK_MCU_SERIES_STM32F3XX) && !defined(QMK_MCU_SERIES_STM32L0XX) && !defined(QMK_MCU_SERIES_STM32L4XX) && !defined(QMK_MCU_SERIES_GD32VF103)
#            pragma message "Default trigger value assigned for AUDIO_DAC_CH1_TRIGGER please ensure this is correct for your MCU"
#        endif
#    endif
#endif

#if !defined(AUDIO_DAC_CH2_TRIGGER)
#    if defined(QMK_MCU_SERIES_STM32G4XX)
#        define AUDIO_DAC_CH2_TRIGGER 0b0010
#    else
#        define AUDIO_DAC_CH2_TRIGGER 0b010
#        if !defined(QMK_MCU_SERIES_STM32F0XX) && !defined(QMK_MCU_SERIES_STM32F3XX) && !defined(QMK_MCU_SERIES_STM32L0XX) && !defined(QMK_MCU_SERIES_STM32L4XX) && !defined(QMK_MCU_SERIES_GD32VF103)
#            pragma message "Default trigger value assigned for AUDIO_DAC_CH2_TRIGGER please ensure this is correct for your MCU"
#        endif
#    endif
#endif

/**
 *user overridable sample generation/processing
 */
uint16_t dac_value_generate(void);
