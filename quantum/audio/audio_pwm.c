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

#define PI 3.14159265

#define CPU_PRESCALER 8


// Timer Abstractions

// TIMSK3 - Timer/Counter #3 Interrupt Mask Register
// Turn on/off 3A interputs, stopping/enabling the ISR calls
#define ENABLE_AUDIO_COUNTER_3_ISR TIMSK3 |= _BV(OCIE3A)
#define DISABLE_AUDIO_COUNTER_3_ISR TIMSK3 &= ~_BV(OCIE3A)


// TCCR3A: Timer/Counter #3 Control Register
// Compare Output Mode (COM3An) = 0b00 = Normal port operation, OC3A disconnected from PC6
#define ENABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A |= _BV(COM3A1);
#define DISABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A &= ~(_BV(COM3A1) | _BV(COM3A0));


#define NOTE_PERIOD ICR3
#define NOTE_DUTY_CYCLE OCR3A


#ifdef PWM_AUDIO
    #include "wave.h"
    #define SAMPLE_DIVIDER 39
    #define SAMPLE_RATE (2000000.0/SAMPLE_DIVIDER/2048)
    // Resistor value of 1/ (2 * PI * 10nF * (2000000 hertz / SAMPLE_DIVIDER / 10)) for 10nF cap

    float places[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint16_t place_int = 0;
    bool repeat = true;
#endif

void delay_us(int count) {
  while(count--) {
    _delay_us(1);
  }
}

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
// float freq = 0;

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

void audio_init() {

    // Check EEPROM
    if (!eeconfig_is_enabled())
    {
        eeconfig_init();
    }
    audio_config.raw = eeconfig_read_audio();

    #ifdef PWM_AUDIO

        PLLFRQ = _BV(PDIV2);
        PLLCSR = _BV(PLLE);
        while(!(PLLCSR & _BV(PLOCK)));
        PLLFRQ |= _BV(PLLTM0); /* PCK 48MHz */

        /* Init a fast PWM on Timer4 */
        TCCR4A = _BV(COM4A0) | _BV(PWM4A); /* Clear OC4A on Compare Match */
        TCCR4B = _BV(CS40); /* No prescaling => f = PCK/256 = 187500Hz */
        OCR4A = 0;

        /* Enable the OC4A output */
        DDRC |= _BV(PORTC6);

        DISABLE_AUDIO_COUNTER_3_ISR; // Turn off 3A interputs

        TCCR3A = 0x0; // Options not needed
        TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32); // 64th prescaling and CTC
        OCR3A = SAMPLE_DIVIDER - 1; // Correct count/compare, related to sample playback

    #else

    	// Set port PC6 (OC3A and /OC4A) as output
        DDRC |= _BV(PORTC6);

        DISABLE_AUDIO_COUNTER_3_ISR;

		// TCCR3A / TCCR3B: Timer/Counter #3 Control Registers
		// Compare Output Mode (COM3An) = 0b00 = Normal port operation, OC3A disconnected from PC6
		// Waveform Generation Mode (WGM3n) = 0b1110 = Fast PWM Mode 14 (Period = ICR3, Duty Cycle = OCR3A)
		// Clock Select (CS3n) = 0b010 = Clock / 8
        TCCR3A = (0 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
        TCCR3B = (1 << WGM33)  | (1 << WGM32)  | (0 << CS32)  | (1 << CS31) | (0 << CS30);

    #endif

    audio_initialized = true;
}

void stop_all_notes() {
    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;
    #ifdef PWM_AUDIO
	    DISABLE_AUDIO_COUNTER_3_ISR;
    #else
        DISABLE_AUDIO_COUNTER_3_ISR;
        DISABLE_AUDIO_COUNTER_3_OUTPUT;
    #endif

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
        #ifdef PWM_AUDIO
            freq = freq / SAMPLE_RATE;
        #endif
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
            #ifdef PWM_AUDIO
                DISABLE_AUDIO_COUNTER_3_ISR;
            #else
                DISABLE_AUDIO_COUNTER_3_ISR;
                DISABLE_AUDIO_COUNTER_3_OUTPUT;
            #endif
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
    if (playing_note) {
        #ifdef PWM_AUDIO
            if (voices == 1) {
                // SINE
                OCR4A = pgm_read_byte(&sinewave[(uint16_t)place]) >> 2;

                // SQUARE
                // if (((int)place) >= 1024){
                //     OCR4A = 0xFF >> 2;
                // } else {
                //     OCR4A = 0x00;
                // }

                // SAWTOOTH
                // OCR4A = (int)place / 4;

                // TRIANGLE
                // if (((int)place) >= 1024) {
                //     OCR4A = (int)place / 2;
                // } else {
                //     OCR4A = 2048 - (int)place / 2;
                // }

                place += frequency;

                if (place >= SINE_LENGTH)
                    place -= SINE_LENGTH;

            } else {
                int sum = 0;
                for (int i = 0; i < voices; i++) {
                    // SINE
                    sum += pgm_read_byte(&sinewave[(uint16_t)places[i]]) >> 2;

                    // SQUARE
                    // if (((int)places[i]) >= 1024){
                    //     sum += 0xFF >> 2;
                    // } else {
                    //     sum += 0x00;
                    // }

                    places[i] += frequencies[i];

                    if (places[i] >= SINE_LENGTH)
                        places[i] -= SINE_LENGTH;
                }
                OCR4A = sum;
            }
        #else
            if (voices > 0) {
                float freq;
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
                    #else
                    {
                    #endif
                        freq = frequencies[voice_place];
                    }
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
                    #else
                    {
                    #endif
                        freq = frequency;
                    }
                }

                if (envelope_index < 65535) {
                    envelope_index++;
                }
                freq = voice_envelope(freq);

                if (freq < 30.517578125)
                    freq = 30.52;
                NOTE_PERIOD = (int)(((double)F_CPU) / (freq * CPU_PRESCALER)); // Set max to the period
                NOTE_DUTY_CYCLE = (int)((((double)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre); // Set compare to half the period
            }
        #endif
    }

    // SAMPLE
    // OCR4A = pgm_read_byte(&sample[(uint16_t)place_int]);

    // place_int++;

    // if (place_int >= sample_length)
    //     if (repeat)
    //         place_int -= sample_length;
    //     else
    //         DISABLE_AUDIO_COUNTER_3_ISR;


    if (playing_notes) {
        #ifdef PWM_AUDIO
            OCR4A = pgm_read_byte(&sinewave[(uint16_t)place]) >> 0;

            place += note_frequency;
            if (place >= SINE_LENGTH)
                place -= SINE_LENGTH;
        #else
            if (note_frequency > 0) {
                float freq;

                #ifdef VIBRATO_ENABLE
                if (vibrato_strength > 0) {
                    freq = vibrato(note_frequency);
                } else {
                #else
                {
                #endif
                    freq = note_frequency;
                }

                if (envelope_index < 65535) {
                    envelope_index++;
                }
                freq = voice_envelope(freq);

                NOTE_PERIOD = (int)(((double)F_CPU) / (freq * CPU_PRESCALER)); // Set max to the period
                NOTE_DUTY_CYCLE = (int)((((double)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre); // Set compare to half the period
            } else {
                NOTE_PERIOD = 0;
                NOTE_DUTY_CYCLE = 0;
            }
        #endif


        note_position++;
        bool end_of_note = false;
        if (NOTE_PERIOD > 0)
            end_of_note = (note_position >= (note_length / NOTE_PERIOD * 0xFFFF));
        else
            end_of_note = (note_position >= (note_length * 0x7FF));
        if (end_of_note) {
            current_note++;
            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    #ifdef PWM_AUDIO
                        DISABLE_AUDIO_COUNTER_3_ISR;
                    #else
                        DISABLE_AUDIO_COUNTER_3_ISR;
                        DISABLE_AUDIO_COUNTER_3_OUTPUT;
                    #endif
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
                #ifdef PWM_AUDIO
                    note_frequency = (*notes_pointer)[current_note][0] / SAMPLE_RATE;
                    note_length = (*notes_pointer)[current_note][1] * (((float)note_tempo) / 100);
                #else
                    envelope_index = 0;
                    note_frequency = (*notes_pointer)[current_note][0];
                    note_length = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
                #endif
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

	    #ifdef PWM_AUDIO
	        freq = freq / SAMPLE_RATE;
	    #endif
	    if (freq > 0) {
	        frequencies[voices] = freq;
	        volumes[voices] = vol;
	        voices++;
	    }

	    #ifdef PWM_AUDIO
	        ENABLE_AUDIO_COUNTER_3_ISR;
	    #else
	        ENABLE_AUDIO_COUNTER_3_ISR;
	        ENABLE_AUDIO_COUNTER_3_OUTPUT;
	    #endif
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

	    #ifdef PWM_AUDIO
	        note_frequency = (*notes_pointer)[current_note][0] / SAMPLE_RATE;
	        note_length = (*notes_pointer)[current_note][1] * (((float)note_tempo) / 100);
	    #else
	        note_frequency = (*notes_pointer)[current_note][0];
	        note_length = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
	    #endif
	    note_position = 0;


	    #ifdef PWM_AUDIO
	        ENABLE_AUDIO_COUNTER_3_ISR;
	    #else
	        ENABLE_AUDIO_COUNTER_3_ISR;
	        ENABLE_AUDIO_COUNTER_3_OUTPUT;
	    #endif
	}

}

#ifdef PWM_AUDIO
void play_sample(uint8_t * s, uint16_t l, bool r) {
    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable) {
        DISABLE_AUDIO_COUNTER_3_ISR;
        stop_all_notes();
        place_int = 0;
        sample = s;
        sample_length = l;
        repeat = r;

        ENABLE_AUDIO_COUNTER_3_ISR;
    }
}
#endif


void audio_toggle(void) {
    audio_config.enable ^= 1;
    eeconfig_update_audio(audio_config.raw);
}

void audio_on(void) {
    audio_config.enable = 1;
    eeconfig_update_audio(audio_config.raw);
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


//------------------------------------------------------------------------------
// Override these functions in your keymap file to play different tunes on
// startup and bootloader jump
__attribute__ ((weak))
void play_startup_tone()
{
}

__attribute__ ((weak))
void play_goodbye_tone()
{
}
//------------------------------------------------------------------------------
