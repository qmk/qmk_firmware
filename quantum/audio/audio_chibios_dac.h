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
#pragma once

/**
 * Size of the dac_buffer arrays. All must be the same size.
 */
#define DAC_BUFFER_SIZE 256U

/**
 * Highest value allowed by our 12bit DAC.
 */
#ifndef DAC_SAMPLE_MAX
#    define DAC_SAMPLE_MAX 4095U
#endif

#if !defined(DAC_QUALITY_VERY_LOW) && !defined(DAC_QUALITY_LOW) && !defined(DAC_QUALITY_HIGH) && !defined(DAC_QUALITY_VERY_HIGH)
#    define DAC_QUALITY_SANE_MINIMUM
#endif

/**
 * These presets allow you to quickly switch between quality settings for
 * the DAC. The sample rate and maximum number of simultaneous tones roughly
 * has an inverse relationship - slightly higher sample rates may be possible.
 *
 * NOTE: a high samplerate results in a higher cpu-load, which might lead to
 *       (audible) discontinuities and/or starve other processes of cpu-time
 *       (like RGB-led backlighting, ...)
 */
#ifdef DAC_QUALITY_VERY_LOW
#    define DAC_SAMPLE_RATE 11025U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 8
#endif

#ifdef DAC_QUALITY_LOW
#    define DAC_SAMPLE_RATE 22050U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 4
#endif

#ifdef DAC_QUALITY_HIGH
#    define DAC_SAMPLE_RATE 44100U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 2
#endif

#ifdef DAC_QUALITY_VERY_HIGH
#    define DAC_SAMPLE_RATE 88200U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 1
#endif

#ifdef DAC_QUALITY_SANE_MINIMUM
/* a sane-minimum config: with a tradeoff between cpu-load and tone-range
 *
 * the (currently) highest defined note is NOTE_B8 with 7902Hz; if we now
 * aim for an even even multiple of the buffersize, we end up with:
 * ( roundUptoPow2(highest note / DAC_BUFFER_SIZE) * nyquist-rate * DAC_BUFFER_SIZE)
 *                        7902/256 = 30.867        *       2      * 256 ~= 16384
 * which works out (but the 'scope shows some sampling artifacts with lower harmonics :-P)
 */
#    define DAC_SAMPLE_RATE 16384U
#    define AUDIO_MAX_SIMULTANEOUS_TONES 8
#endif


/**
 * Effective bitrate of the DAC. 44.1khz is the standard for most audio - any
 * lower will sacrifice perceptible audio quality. Any higher will limit the
 * number of simultaneous tones. In most situations, a tenth (1/10) of the
 * sample rate is where notes become unbearable.
 */
#ifndef DAC_SAMPLE_RATE
#    define DAC_SAMPLE_RATE 44100U
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
 * setups may require a high (DAC_SAMPLE_MAX) or low (0) value here.
 */
#ifndef DAC_OFF_VALUE
#    define DAC_OFF_VALUE DAC_SAMPLE_MAX / 2
#endif

/**
 * choose pins for the speaker
 */
#if !defined(AUDIO_PIN_A4) && !defined(AUDIO_PIN_A5)
#    pragma message "Audio feature enabled, but no pin selected - see docs/feature_audio under the ARM DAC settings for available options. Falling back to A5"
#    define AUDIO_PIN_A5
//TODO: go through a breaking change, and add AUDIO_PIN=A5 to all keyboards currently using AUDIO on STM32 based boards
#endif

/**
 *user overridable sample generation/processing
 */
uint16_t dac_value_generate(void);
