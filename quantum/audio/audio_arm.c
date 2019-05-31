/* Copyright 2016 Jack Humbert
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

#include "audio.h"
#include "ch.h"
#include "hal.h"

#include <string.h>
#include "print.h"
#include "keymap.h"

#include "eeconfig.h"

// -----------------------------------------------------------------------------

int voices = 0;
int voice_place = 0;
float frequency = 0;
float frequency_alt = 0;
int volume = 0;
long position = 0;

float frequencies[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int volumes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool sliding = false;

float place = 0;

uint8_t * sample;
uint16_t sample_length = 0;

bool     playing_notes = false;
bool     playing_note = false;
float    note_frequency = 0;
float    note_length = 0;
uint8_t  note_tempo = TEMPO_DEFAULT;
float    note_timbre = TIMBRE_DEFAULT;
uint16_t note_position = 0;
float (* notes_pointer)[][2];
uint16_t notes_count;
bool     notes_repeat;
bool     note_resting = false;

uint16_t current_note = 0;
uint8_t rest_counter = 0;

#ifdef VIBRATO_ENABLE
float vibrato_counter = 0;
float vibrato_strength = .5;
float vibrato_rate = 0.125;
#endif

float polyphony_rate = 0;

static bool audio_initialized = false;

audio_config_t audio_config;

uint16_t envelope_index = 0;
bool glissando = true;

#ifndef STARTUP_SONG
    #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif
float startup_song[][2] = STARTUP_SONG;

#define DAC_BUFFER_SIZE 256U
#ifndef DAC_SAMPLE_MAX
#define DAC_SAMPLE_MAX  4095U
#endif

#define DAC_SAMPLE_RATE 44100U

GPTConfig gpt7cfg1 = {
  .frequency    = DAC_SAMPLE_RATE,
  .callback     = NULL,
  .cr2          = TIM_CR2_MMS_1,    /* MMS = 010 = TRGO on Update Event.    */
  .dier         = 0U
};

static const dacsample_t dac_buffer[DAC_BUFFER_SIZE] = {
  // First half is max, second half is 0
  // [0                 ... DAC_BUFFER_SIZE/2-1] = DAC_SAMPLE_MAX,
  // [DAC_BUFFER_SIZE/2 ... DAC_BUFFER_SIZE  -1] = 0,

  // 100 values, max 4095
  // 0x800,0x880,0x900,0x97f,0x9fd,0xa78,0xaf1,0xb67,
  // 0xbda,0xc49,0xcb3,0xd19,0xd79,0xdd4,0xe29,0xe78,
  // 0xec0,0xf02,0xf3c,0xf6f,0xf9b,0xfbf,0xfdb,0xfef,
  // 0xffb,0xfff,0xffb,0xfef,0xfdb,0xfbf,0xf9b,0xf6f,
  // 0xf3c,0xf02,0xec0,0xe78,0xe29,0xdd4,0xd79,0xd19,
  // 0xcb3,0xc49,0xbda,0xb67,0xaf1,0xa78,0x9fd,0x97f,
  // 0x900,0x880,0x800,0x77f,0x6ff,0x680,0x602,0x587,
  // 0x50e,0x498,0x425,0x3b6,0x34c,0x2e6,0x286,0x22b,
  // 0x1d6,0x187,0x13f,0xfd,0xc3,0x90,0x64,0x40,
  // 0x24,0x10,0x4,0x0,0x4,0x10,0x24,0x40,
  // 0x64,0x90,0xc3,0xfd,0x13f,0x187,0x1d6,0x22b,
  // 0x286,0x2e6,0x34c,0x3b6,0x425,0x498,0x50e,0x587,
  // 0x602,0x680,0x6ff,0x77f,0x800

  // 256 values, max 4095
  0x800,0x832,0x864,0x896,0x8c8,0x8fa,0x92c,0x95e,
  0x98f,0x9c0,0x9f1,0xa22,0xa52,0xa82,0xab1,0xae0,
  0xb0f,0xb3d,0xb6b,0xb98,0xbc5,0xbf1,0xc1c,0xc47,
  0xc71,0xc9a,0xcc3,0xceb,0xd12,0xd39,0xd5f,0xd83,
  0xda7,0xdca,0xded,0xe0e,0xe2e,0xe4e,0xe6c,0xe8a,
  0xea6,0xec1,0xedc,0xef5,0xf0d,0xf24,0xf3a,0xf4f,
  0xf63,0xf76,0xf87,0xf98,0xfa7,0xfb5,0xfc2,0xfcd,
  0xfd8,0xfe1,0xfe9,0xff0,0xff5,0xff9,0xffd,0xffe,
  0xfff,0xffe,0xffd,0xff9,0xff5,0xff0,0xfe9,0xfe1,
  0xfd8,0xfcd,0xfc2,0xfb5,0xfa7,0xf98,0xf87,0xf76,
  0xf63,0xf4f,0xf3a,0xf24,0xf0d,0xef5,0xedc,0xec1,
  0xea6,0xe8a,0xe6c,0xe4e,0xe2e,0xe0e,0xded,0xdca,
  0xda7,0xd83,0xd5f,0xd39,0xd12,0xceb,0xcc3,0xc9a,
  0xc71,0xc47,0xc1c,0xbf1,0xbc5,0xb98,0xb6b,0xb3d,
  0xb0f,0xae0,0xab1,0xa82,0xa52,0xa22,0x9f1,0x9c0,
  0x98f,0x95e,0x92c,0x8fa,0x8c8,0x896,0x864,0x832,
  0x800,0x7cd,0x79b,0x769,0x737,0x705,0x6d3,0x6a1,
  0x670,0x63f,0x60e,0x5dd,0x5ad,0x57d,0x54e,0x51f,
  0x4f0,0x4c2,0x494,0x467,0x43a,0x40e,0x3e3,0x3b8,
  0x38e,0x365,0x33c,0x314,0x2ed,0x2c6,0x2a0,0x27c,
  0x258,0x235,0x212,0x1f1,0x1d1,0x1b1,0x193,0x175,
  0x159,0x13e,0x123,0x10a,0xf2,0xdb,0xc5,0xb0,
  0x9c,0x89,0x78,0x67,0x58,0x4a,0x3d,0x32,
  0x27,0x1e,0x16,0xf,0xa,0x6,0x2,0x1,
  0x0,0x1,0x2,0x6,0xa,0xf,0x16,0x1e,
  0x27,0x32,0x3d,0x4a,0x58,0x67,0x78,0x89,
  0x9c,0xb0,0xc5,0xdb,0xf2,0x10a,0x123,0x13e,
  0x159,0x175,0x193,0x1b1,0x1d1,0x1f1,0x212,0x235,
  0x258,0x27c,0x2a0,0x2c6,0x2ed,0x314,0x33c,0x365,
  0x38e,0x3b8,0x3e3,0x40e,0x43a,0x467,0x494,0x4c2,
  0x4f0,0x51f,0x54e,0x57d,0x5ad,0x5dd,0x60e,0x63f,
  0x670,0x6a1,0x6d3,0x705,0x737,0x769,0x79b,0x7cd

};

#define DAC_VOICES_MAX 5

dacsample_t dac_buffer_lr[DAC_BUFFER_SIZE] = { DAC_SAMPLE_MAX / 2 };

float dac_if[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

/*
 * DAC streaming callback.
 */
static void end_cb1(DACDriver * dacp, dacsample_t * samples, size_t rows) {

  (void)dacp;
  //(void)dac_buffer;

  int working_voices = voices;
  if (working_voices > DAC_VOICES_MAX)
    working_voices = DAC_VOICES_MAX;

  for (int s = 0; s < rows; s++) {
    if (working_voices > 0) {
      uint16_t sample_sum = 0;
      for (int i = 0; i < working_voices; i++) {
        dac_if[i] = dac_if[i] + ((frequencies[i]*(float)DAC_BUFFER_SIZE)/(float)DAC_SAMPLE_RATE*1.5);
        while(dac_if[i] >= DAC_BUFFER_SIZE)
          dac_if[i] = dac_if[i] - DAC_BUFFER_SIZE;
        // sine
        sample_sum += dac_buffer[(uint16_t)round(dac_if[i])] / working_voices;
        // rising triangle
        // sample_sum += (uint16_t)round((dac_if[i] * DAC_SAMPLE_MAX) / DAC_BUFFER_SIZE / working_voices );
        // square (max 5 voices)
        // sample_sum += ((dac_if[i] > (DAC_BUFFER_SIZE / 2)) ? DAC_SAMPLE_MAX / working_voices: 0);
      }
      samples[s] = sample_sum;
    } else {
      samples[s] = DAC_SAMPLE_MAX / 2;
    }
  }
}

/*
 * DAC error callback.
 */
static void error_cb1(DACDriver *dacp, dacerror_t err) {

  (void)dacp;
  (void)err;

  chSysHalt("DAC failure");
}

static const DACConfig dac1cfg1 = {
  .init         = DAC_SAMPLE_MAX,
  .datamode     = DAC_DHRM_12BIT_RIGHT
};

static const DACConversionGroup dacgrpcfg1 = {
  .num_channels = 1U,
  .end_cb       = end_cb1,
  .error_cb     = error_cb1,
  .trigger      = DAC_TRG(0)
};

void audio_init() {

  if (audio_initialized) {
    return;
  }

  // Check EEPROM
  #if defined(STM32_EEPROM_ENABLE) || defined(PROTOCOL_ARM_ATSAM) || defined(EEPROM_SIZE)
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }
    audio_config.raw = eeconfig_read_audio();
#else // ARM EEPROM
    audio_config.enable = true;
  #ifdef AUDIO_CLICKY_ON
    audio_config.clicky_enable = true;
  #endif
#endif // ARM EEPROM

  palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG );
  // palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG );
  palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL );
  palSetPad(GPIOA, 4);

  // dacStart(&DACD1, &dac1cfg1);
  // dacStartConversion(&DACD1, &dacgrpcfg1, dac_buffer_lr, 1);
  dacStart(&DACD2, &dac1cfg1);
  dacStartConversion(&DACD2, &dacgrpcfg1, dac_buffer_lr, DAC_BUFFER_SIZE);

  gptStart(&GPTD6, &gpt7cfg1);
  gptStartContinuous(&GPTD6, 2U);
  // gptStart(&GPTD7, &gpt7cfg1);
  // gptStartContinuous(&GPTD7, 2U);

  audio_initialized = true;

  if (audio_config.enable) {
    PLAY_SONG(startup_song);
  } else {
    stop_all_notes();
  }

}

void stop_all_notes() {
    dprintf("audio stop all notes");

    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;

    gptStopTimer(&GPTD8);

    playing_notes = false;
    playing_note = false;
    frequency = 0;
    frequency_alt = 0;
    volume = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        frequencies[i] = 0;
        volumes[i] = 0;
    }
}

void stop_note(float freq) {
  dprintf("audio stop note freq=%d", (int)freq);

  if (playing_note) {
    if (!audio_initialized) {
      audio_init();
    }
    for (int i = 7; i >= 0; i--) {
      if (frequencies[i] == freq) {
        frequencies[i] = 0;
        volumes[i] = 0;
        for (int j = i; (j < 7); j++) {
          frequencies[j] = frequencies[j+1];
          frequencies[j+1] = 0;
          volumes[j] = volumes[j+1];
          volumes[j+1] = 0;
        }
        break;
      }
    }
    voices--;
    if (voices < 0) {
      voices = 0;
    }
    if (voice_place >= voices) {
      voice_place = 0;
    }
    if (voices == 0) {
      frequency = 0;
      frequency_alt = 0;
      volume = 0;
      playing_note = false;
    }
  }
}

#ifdef VIBRATO_ENABLE

float mod(float a, int b) {
  float r = fmod(a, b);
  return r < 0 ? r + b : r;
}

float vibrato(float average_freq) {
  #ifdef VIBRATO_STRENGTH_ENABLE
    float vibrated_freq = average_freq * pow(vibrato_lut[(int)vibrato_counter], vibrato_strength);
  #else
    float vibrated_freq = average_freq * vibrato_lut[(int)vibrato_counter];
  #endif
  vibrato_counter = mod((vibrato_counter + vibrato_rate * (1.0 + 440.0/average_freq)), VIBRATO_LUT_LENGTH);
  return vibrated_freq;
}

#endif


void play_note(float freq, int vol) {

  dprintf("audio play note freq=%d vol=%d", (int)freq, vol);

  if (!audio_initialized) {
      audio_init();
  }

  if (audio_config.enable && voices < 8) {

     // Cancel notes if notes are playing
    if (playing_notes) {
      stop_all_notes();
    }

    playing_note = true;

    envelope_index = 0;

    if (freq > 0) {
      frequencies[voices] = freq;
      volumes[voices] = vol;
      voices++;
    }

  }

}

void play_notes(float (*np)[][2], uint16_t n_count, bool n_repeat) {

  if (!audio_initialized) {
    audio_init();
  }

  if (audio_config.enable) {

    // Cancel note if a note is playing
    if (playing_note) {
      stop_all_notes();
    }

    playing_notes = true;

    notes_pointer = np;
    notes_count = n_count;
    notes_repeat = n_repeat;

    place = 0;
    current_note = 0;

    note_frequency = (*notes_pointer)[current_note][0];
    note_length = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
    note_position = 0;

  }
}

bool is_playing_notes(void) {
  return playing_notes;
}

bool is_audio_on(void) {
  return (audio_config.enable != 0);
}

void audio_toggle(void) {
  audio_config.enable ^= 1;
  eeconfig_update_audio(audio_config.raw);
  if (audio_config.enable) {
    audio_on_user();
  }
}

void audio_on(void) {
  audio_config.enable = 1;
  eeconfig_update_audio(audio_config.raw);
  audio_on_user();
}

void audio_off(void) {
  stop_all_notes();
  audio_config.enable = 0;
  eeconfig_update_audio(audio_config.raw);
}

#ifdef VIBRATO_ENABLE

// Vibrato rate functions

void set_vibrato_rate(float rate) {
  vibrato_rate = rate;
}

void increase_vibrato_rate(float change) {
  vibrato_rate *= change;
}

void decrease_vibrato_rate(float change) {
  vibrato_rate /= change;
}

#ifdef VIBRATO_STRENGTH_ENABLE

void set_vibrato_strength(float strength) {
  vibrato_strength = strength;
}

void increase_vibrato_strength(float change) {
  vibrato_strength *= change;
}

void decrease_vibrato_strength(float change) {
  vibrato_strength /= change;
}

#endif  /* VIBRATO_STRENGTH_ENABLE */

#endif /* VIBRATO_ENABLE */

// Polyphony functions

void set_polyphony_rate(float rate) {
  polyphony_rate = rate;
}

void enable_polyphony() {
  polyphony_rate = 5;
}

void disable_polyphony() {
  polyphony_rate = 0;
}

void increase_polyphony_rate(float change) {
  polyphony_rate *= change;
}

void decrease_polyphony_rate(float change) {
  polyphony_rate /= change;
}

// Timbre function

void set_timbre(float timbre) {
  note_timbre = timbre;
}

// Tempo functions

void set_tempo(uint8_t tempo) {
  note_tempo = tempo;
}

void decrease_tempo(uint8_t tempo_change) {
  note_tempo += tempo_change;
}

void increase_tempo(uint8_t tempo_change) {
  if (note_tempo - tempo_change < 10) {
    note_tempo = 10;
  } else {
    note_tempo -= tempo_change;
  }
}
