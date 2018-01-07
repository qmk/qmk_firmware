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
#include "voices.h"
#include "audio.h"
#include "stdlib.h"

// these are imported from audio.c
extern uint16_t envelope_index[NUMBER_OF_TIMERS];
extern float note_timbre[NUMBER_OF_TIMERS];
extern float polyphony_rate;
extern bool glissando[NUMBER_OF_TIMERS];

voice_type voice[NUMBER_OF_TIMERS] = {default_voice};

void set_all_voices(voice_type v) {
    for (uint8_t i = 0; i < NUMBER_OF_TIMERS; i++) {
        voice[i] = v;
    }
}

void all_voices_iterate(void) {
    for (uint8_t i = 0; i < NUMBER_OF_TIMERS; i++) {
        voice[i] = (voice[i] + 1) % number_of_voices;
    }
}

void all_voices_deiterate(void) {
    for (uint8_t i = 0; i < NUMBER_OF_TIMERS; i++) {
        voice[i] = (voice[i] - 1 + number_of_voices) % number_of_voices;
    }
}

void set_voice(voice_type v, uint8_t timer_index) {
    voice[timer_index] = v;
}

void voice_iterate(uint8_t timer_index) {
    voice[timer_index] = (voice[timer_index] + 1) % number_of_voices;
}

void voice_deiterate(uint8_t timer_index) {
    voice[timer_index] = (voice[timer_index] - 1 + number_of_voices) % number_of_voices;
}

float voice_envelope(float frequency, uint8_t timer_index) {
    // envelope_index[timer_index] ranges from 0 to 0xFFFF, which is preserved at 880.0 Hz
    __attribute__ ((unused))
    uint16_t compensated_index = (uint16_t)((float)envelope_index[timer_index] * (880.0 / frequency));

    switch (voice[timer_index]) {
        case default_voice:
            glissando[timer_index] = false;
            note_timbre[timer_index] = TIMBRE_50;
            polyphony_rate = 0;
	        break;

    #ifdef AUDIO_VOICES

        case something:
            glissando[timer_index] = false;
            polyphony_rate = 0;
            switch (compensated_index) {
                case 0 ... 9:
                    note_timbre[timer_index] = TIMBRE_12;
                    break;

                case 10 ... 19:
                    note_timbre[timer_index] = TIMBRE_25;
                    break;

                case 20 ... 200:
                    note_timbre[timer_index] = .125 + .125;
                    break;

                default:
                    note_timbre[timer_index] = .125;
                    break;
            }
            break;

        case drums:
            glissando[timer_index] = false;
            polyphony_rate = 0;
                // switch (compensated_index) {
                //     case 0 ... 10:
                //         note_timbre[timer_index] = 0.5;
                //         break;
                //     case 11 ... 20:
                //         note_timbre[timer_index] = 0.5 * (21 - compensated_index) / 10;
                //         break;
                //     default:
                //         note_timbre[timer_index] = 0;
                //         break;
                // }
                // frequency = (rand() % (int)(frequency * 1.2 - frequency)) + (frequency * 0.8);

            if (frequency < 80.0) {

            } else if (frequency < 160.0) {

                // Bass drum: 60 - 100 Hz
                frequency = (rand() % (int)(40)) + 60;
                switch (envelope_index[timer_index]) {
                    case 0 ... 10:
                        note_timbre[timer_index] = 0.5;
                        break;
                    case 11 ... 20:
                        note_timbre[timer_index] = 0.5 * (21 - envelope_index[timer_index]) / 10;
                        break;
                    default:
                        note_timbre[timer_index] = 0;
                        break;
                }

            } else if (frequency < 320.0) {


                // Snare drum: 1 - 2 KHz
                frequency = (rand() % (int)(1000)) + 1000;
                switch (envelope_index[timer_index]) {
                    case 0 ... 5:
                        note_timbre[timer_index] = 0.5;
                        break;
                    case 6 ... 20:
                        note_timbre[timer_index] = 0.5 * (21 - envelope_index[timer_index]) / 15;
                        break;
                    default:
                        note_timbre[timer_index] = 0;
                        break;
                }

            } else if (frequency < 640.0) {

                // Closed Hi-hat: 3 - 5 KHz
                frequency = (rand() % (int)(2000)) + 3000;
                switch (envelope_index[timer_index]) {
                    case 0 ... 15:
                        note_timbre[timer_index] = 0.5;
                        break;
                    case 16 ... 20:
                        note_timbre[timer_index] = 0.5 * (21 - envelope_index[timer_index]) / 5;
                        break;
                    default:
                        note_timbre[timer_index] = 0;
                        break;
                }

            } else if (frequency < 1280.0) {

                // Open Hi-hat: 3 - 5 KHz
                frequency = (rand() % (int)(2000)) + 3000;
                switch (envelope_index[timer_index]) {
                    case 0 ... 35:
                        note_timbre[timer_index] = 0.5;
                        break;
                    case 36 ... 50:
                        note_timbre[timer_index] = 0.5 * (51 - envelope_index[timer_index]) / 15;
                        break;
                    default:
                        note_timbre[timer_index] = 0;
                        break;
                }

            }
            break;
        case butts_fader:
            glissando[timer_index] = true;
            polyphony_rate = 0;
            switch (compensated_index) {
                case 0 ... 9:
                    frequency = frequency / 4;
                    note_timbre[timer_index] = TIMBRE_12;
	                break;

                case 10 ... 19:
                    frequency = frequency / 2;
                    note_timbre[timer_index] = TIMBRE_12;
	                break;

                case 20 ... 200:
                    note_timbre[timer_index] = .125 - pow(((float)compensated_index - 20) / (200 - 20), 2)*.125;
	                break;

                default:
                    note_timbre[timer_index] = 0;
                	break;
            }
    	    break;

        case octave_crunch:
            polyphony_rate = 0;
            switch (compensated_index) {
                case 0 ... 9:
                case 20 ... 24:
                case 30 ... 32:
                    frequency = frequency / 2;
                    note_timbre[timer_index] = TIMBRE_12;
                break;

                case 10 ... 19:
                case 25 ... 29:
                case 33 ... 35:
                    frequency = frequency * 2;
                    note_timbre[timer_index] = TIMBRE_12;
	                break;

                default:
                    note_timbre[timer_index] = TIMBRE_12;
                	break;
            }
	        break;

        case duty_osc:
            // This slows the loop down a substantial amount, so higher notes may freeze
            glissando[timer_index] = true;
            polyphony_rate = 0;
            switch (compensated_index) {
                default:
                    #define OCS_SPEED 10
                    #define OCS_AMP   .25
                    // sine wave is slow
                    // note_timbre[timer_index] = (sin((float)compensated_index/10000*OCS_SPEED) * OCS_AMP / 2) + .5;
                    // triangle wave is a bit faster
                    note_timbre[timer_index] = (float)abs((compensated_index*OCS_SPEED % 3000) - 1500) * ( OCS_AMP / 1500 ) + (1 - OCS_AMP) / 2;
                	break;
            }
	        break;

        case duty_octave_down:
            glissando[timer_index] = true;
            polyphony_rate = 0;
            note_timbre[timer_index] = (envelope_index[timer_index] % 2) * .125 + .375 * 2;
            if ((envelope_index[timer_index] % 4) == 0)
                note_timbre[timer_index] = 0.5;
            if ((envelope_index[timer_index] % 8) == 0)
                note_timbre[timer_index] = 0;
            break;
        case delayed_vibrato:
            glissando[timer_index] = true;
            polyphony_rate = 0;
            note_timbre[timer_index] = TIMBRE_50;
            #define VOICE_VIBRATO_DELAY 150
            #define VOICE_VIBRATO_SPEED 50
            switch (compensated_index) {
                case 0 ... VOICE_VIBRATO_DELAY:
                    break;
                default:
                    frequency = frequency * vibrato_lut[(int)fmod((((float)compensated_index - (VOICE_VIBRATO_DELAY + 1))/1000*VOICE_VIBRATO_SPEED), VIBRATO_LUT_LENGTH)];
                    break;
            }
            break;
        // case delayed_vibrato_octave:
        //     polyphony_rate = 0;
        //     if ((envelope_index[timer_index] % 2) == 1) {
        //         note_timbre[timer_index] = 0.55;
        //     } else {
        //         note_timbre[timer_index] = 0.45;
        //     }
        //     #define VOICE_VIBRATO_DELAY 150
        //     #define VOICE_VIBRATO_SPEED 50
        //     switch (compensated_index) {
        //         case 0 ... VOICE_VIBRATO_DELAY:
        //             break;
        //         default:
        //             frequency = frequency * VIBRATO_LUT[(int)fmod((((float)compensated_index - (VOICE_VIBRATO_DELAY + 1))/1000*VOICE_VIBRATO_SPEED), VIBRATO_LUT_LENGTH)];
        //             break;
        //     }
        //     break;
        // case duty_fifth_down:
        //     note_timbre[timer_index] = 0.5;
        //     if ((envelope_index[timer_index] % 3) == 0)
        //         note_timbre[timer_index] = 0.75;
        //     break;
        // case duty_fourth_down:
        //     note_timbre[timer_index] = 0.0;
        //     if ((envelope_index[timer_index] % 12) == 0)
        //         note_timbre[timer_index] = 0.75;
        //     if (((envelope_index[timer_index] % 12) % 4) != 1)
        //         note_timbre[timer_index] = 0.75;
        //     break;
        // case duty_third_down:
        //     note_timbre[timer_index] = 0.5;
        //     if ((envelope_index[timer_index] % 5) == 0)
        //         note_timbre[timer_index] = 0.75;
        //     break;
        // case duty_fifth_third_down:
        //     note_timbre[timer_index] = 0.5;
        //     if ((envelope_index[timer_index] % 5) == 0)
        //         note_timbre[timer_index] = 0.75;
        //     if ((envelope_index[timer_index] % 3) == 0)
        //         note_timbre[timer_index] = 0.25;
        //     break;

    #endif

		default:
   			break;
    }

    return frequency;
}
