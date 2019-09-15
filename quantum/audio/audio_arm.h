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

#include "ch.h"

/**
 * Size of the dac_buffer arrays. All must be the same size.
 */
#define DAC_BUFFER_SIZE 256U

/**
 * Highest value allowed by our 12bit DAC.
 */
#ifndef DAC_SAMPLE_MAX
  #define DAC_SAMPLE_MAX  4095U
#endif

// #define DAC_LOW_QUALITY

/**
 * These presets allow you to quickly switch between quality/voice settings for
 * the DAC. The sample rate and number of voices roughly has an inverse
 * relationship - slightly higher sample rates may be possible.
 */
#ifdef DAC_VERY_LOW_QUALITY
  #define DAC_SAMPLE_RATE 11025U
  #define DAC_VOICES_MAX 8
#endif

#ifdef DAC_LOW_QUALITY
  #define DAC_SAMPLE_RATE 22050U
  #define DAC_VOICES_MAX 4
#endif

#ifdef DAC_HIGH_QUALITY
  #define DAC_SAMPLE_RATE 44100U
  #define DAC_VOICES_MAX 2
#endif

#ifdef DAC_VERY_HIGH_QUALITY
  #define DAC_SAMPLE_RATE 88200U
  #define DAC_VOICES_MAX 1
#endif

/**
 * Effective bitrate of the DAC. 44.1khz is the standard for most audio - any
 * lower will sacrifice perceptible audio quality. Any higher will limit the
 * number of simultaneous voices. In most situations, a tenth (1/10) of the
 * sample rate is where notes become unbearable.
 */
#ifndef DAC_SAMPLE_RATE
  #define DAC_SAMPLE_RATE 44100U
#endif

/**
 * The number of voices (in polyphony) that are supported. If too high a value
 * is used here, the keyboard will freeze and glitch-out when that many voices
 * are being played.
 */
#ifndef DAC_VOICES_MAX
  #define DAC_VOICES_MAX 2
#endif

/**
 * The default value of the DAC when not playing anything. Certain hardware
 * setups may require a high (DAC_SAMPLE_MAX) or low (0) value here.
 */
#ifndef DAC_OFF_VALUE
  #define DAC_OFF_VALUE DAC_SAMPLE_MAX / 2
#endif

/**
 * choose pins for the speaker
 */
#ifndef A4_AUDIO
  #define A4_AUDIO
//#define A5_AUDIO
#endif

uint8_t dac_number_of_voices(void);
float dac_get_frequency(uint8_t index);
uint16_t dac_value_generate(void);
void dac_setup_note(void);
