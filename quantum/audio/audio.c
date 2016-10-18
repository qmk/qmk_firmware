#include <stdio.h>
#include <string.h>
//#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "print.h"
#include "audio.h"
#include "keymap.h"

#include "eeconfig.h"

#define CPU_PRESCALER 8

// -----------------------------------------------------------------------------
// Timer Abstractions
// -----------------------------------------------------------------------------

// TIMSK3 - Timer/Counter #3 Interrupt Mask Register
// Turn on/off 3A interputs, stopping/enabling the ISR calls
#define ENABLE_AUDIO_COUNTER_3_ISR TIMSK3 |= _BV(OCIE3A)
#define DISABLE_AUDIO_COUNTER_3_ISR TIMSK3 &= ~_BV(OCIE3A)

// TCCR3A: Timer/Counter #3 Control Register
// Compare Output Mode (COM3An) = 0b00 = Normal port operation, OC3A disconnected from PC6
#define ENABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A |= _BV(COM3A1);
#define DISABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A &= ~(_BV(COM3A1) | _BV(COM3A0));

// Fast PWM Mode Controls
#define TIMER_3_PERIOD     ICR3
#define TIMER_3_DUTY_CYCLE OCR3A

// -----------------------------------------------------------------------------


int voices = 0;
int voice_place = 0;
float frequency = 0;
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
float    notes_rest;
bool     note_resting = false;

uint8_t current_note = 0;
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

void audio_init()
{

    // Check EEPROM
    if (!eeconfig_is_enabled())
    {
        eeconfig_init();
    }
    audio_config.raw = eeconfig_read_audio();

	// Set port PC6 (OC3A and /OC4A) as output
    DDRC |= _BV(PORTC6);

    DISABLE_AUDIO_COUNTER_3_ISR;

	// TCCR3A / TCCR3B: Timer/Counter #3 Control Registers
	// Compare Output Mode (COM3An) = 0b00 = Normal port operation, OC3A disconnected from PC6
	// Waveform Generation Mode (WGM3n) = 0b1110 = Fast PWM Mode 14 (Period = ICR3, Duty Cycle = OCR3A)
	// Clock Select (CS3n) = 0b010 = Clock / 8
    TCCR3A = (0 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
    TCCR3B = (1 << WGM33)  | (1 << WGM32)  | (0 << CS32)  | (1 << CS31) | (0 << CS30);

    audio_initialized = true;
}

void stop_all_notes()
{
    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;

    DISABLE_AUDIO_COUNTER_3_ISR;
    DISABLE_AUDIO_COUNTER_3_OUTPUT;

    playing_notes = false;
    playing_note = false;
    frequency = 0;
    volume = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        frequencies[i] = 0;
        volumes[i] = 0;
    }
}

void stop_note(float freq)
{
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
        if (voices < 0)
            voices = 0;
        if (voice_place >= voices) {
            voice_place = 0;
        }
        if (voices == 0) {
            DISABLE_AUDIO_COUNTER_3_ISR;
            DISABLE_AUDIO_COUNTER_3_OUTPUT;
            frequency = 0;
            volume = 0;
            playing_note = false;
        }
    }
}

#ifdef VIBRATO_ENABLE

float mod(float a, int b)
{
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

ISR(TIMER3_COMPA_vect)
{
	float freq;

	if (playing_note) {
		if (voices > 0) {
			if (polyphony_rate > 0) {
				if (voices > 1) {
					voice_place %= voices;
					if (place++ > (frequencies[voice_place] / polyphony_rate / CPU_PRESCALER)) {
						voice_place = (voice_place + 1) % voices;
						place = 0.0;
					}
				}

				#ifdef VIBRATO_ENABLE
					if (vibrato_strength > 0) {
						freq = vibrato(frequencies[voice_place]);
					} else {
						freq = frequencies[voice_place];
					}
				#else
					freq = frequencies[voice_place];
				#endif
			} else {
				if (frequency != 0 && frequency < frequencies[voices - 1] && frequency < frequencies[voices - 1] * pow(2, -440/frequencies[voices - 1]/12/2)) {
					frequency = frequency * pow(2, 440/frequency/12/2);
				} else if (frequency != 0 && frequency > frequencies[voices - 1] && frequency > frequencies[voices - 1] * pow(2, 440/frequencies[voices - 1]/12/2)) {
					frequency = frequency * pow(2, -440/frequency/12/2);
				} else {
					frequency = frequencies[voices - 1];
				}

				#ifdef VIBRATO_ENABLE
					if (vibrato_strength > 0) {
						freq = vibrato(frequency);
					} else {
						freq = frequency;
					}
				#else
					freq = frequency;
				#endif
			}

			if (envelope_index < 65535) {
				envelope_index++;
			}

			freq = voice_envelope(freq);

			if (freq < 30.517578125) {
				freq = 30.52;
			}

			TIMER_3_PERIOD = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
			TIMER_3_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
		}
	}

	if (playing_notes) {
		if (note_frequency > 0) {
			#ifdef VIBRATO_ENABLE
				if (vibrato_strength > 0) {
					freq = vibrato(note_frequency);
				} else {
					freq = note_frequency;
				}
			#else
					freq = note_frequency;
			#endif

			if (envelope_index < 65535) {
				envelope_index++;
			}
			freq = voice_envelope(freq);

			TIMER_3_PERIOD = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
			TIMER_3_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
		} else {
			TIMER_3_PERIOD = 0;
			TIMER_3_DUTY_CYCLE = 0;
		}

		note_position++;
		bool end_of_note = false;
		if (TIMER_3_PERIOD > 0) {
			end_of_note = (note_position >= (note_length / TIMER_3_PERIOD * 0xFFFF));
		} else {
			end_of_note = (note_position >= (note_length * 0x7FF));
		}

		if (end_of_note) {
			current_note++;
			if (current_note >= notes_count) {
				if (notes_repeat) {
					current_note = 0;
				} else {
					DISABLE_AUDIO_COUNTER_3_ISR;
					DISABLE_AUDIO_COUNTER_3_OUTPUT;
					playing_notes = false;
					return;
				}
			}
			if (!note_resting && (notes_rest > 0)) {
				note_resting = true;
				note_frequency = 0;
				note_length = notes_rest;
				current_note--;
			} else {
				note_resting = false;
				envelope_index = 0;
				note_frequency = (*notes_pointer)[current_note][0];
				note_length = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
			}

			note_position = 0;
		}
	}

	if (!audio_config.enable) {
		playing_notes = false;
		playing_note = false;
	}
}

void play_note(float freq, int vol) {

    if (!audio_initialized) {
        audio_init();
    }

	if (audio_config.enable && voices < 8) {
	    DISABLE_AUDIO_COUNTER_3_ISR;

	    // Cancel notes if notes are playing
	    if (playing_notes)
	        stop_all_notes();

	    playing_note = true;

	    envelope_index = 0;

	    if (freq > 0) {
	        frequencies[voices] = freq;
	        volumes[voices] = vol;
	        voices++;
	    }

        ENABLE_AUDIO_COUNTER_3_ISR;
        ENABLE_AUDIO_COUNTER_3_OUTPUT;
	}

}

void play_notes(float (*np)[][2], uint16_t n_count, bool n_repeat, float n_rest)
{

    if (!audio_initialized) {
        audio_init();
    }

	if (audio_config.enable) {

	    DISABLE_AUDIO_COUNTER_3_ISR;

		// Cancel note if a note is playing
	    if (playing_note)
	        stop_all_notes();

	    playing_notes = true;

	    notes_pointer = np;
	    notes_count = n_count;
	    notes_repeat = n_repeat;
	    notes_rest = n_rest;

	    place = 0;
	    current_note = 0;

        note_frequency = (*notes_pointer)[current_note][0];
        note_length = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
	    note_position = 0;


        ENABLE_AUDIO_COUNTER_3_ISR;
        ENABLE_AUDIO_COUNTER_3_OUTPUT;
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
    if (audio_config.enable)
        audio_on_user();
}

void audio_on(void) {
    audio_config.enable = 1;
    eeconfig_update_audio(audio_config.raw);
    audio_on_user();
}

void audio_off(void) {
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
