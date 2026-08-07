/* Copyright 2016 Jack Humbert
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
#include "voices.h"
#include "audio.h"
#include "timer.h"
#include <stdlib.h>
#include <math.h>

uint8_t note_timbre      = TIMBRE_DEFAULT;
bool    glissando        = false;
bool    vibrato          = false;
float   vibrato_strength = 0.5;
float   vibrato_rate     = 0.125;

uint16_t voices_timer = 0;

#ifdef AUDIO_VOICE_DEFAULT
voice_type voice = AUDIO_VOICE_DEFAULT;
#else
voice_type voice = default_voice;
#endif

void set_voice(voice_type v) {
    voice = v;
}

void voice_iterate(void) {
    voice = (voice + 1) % number_of_voices;
}

void voice_deiterate(void) {
    voice = (voice - 1 + number_of_voices) % number_of_voices;
}

#ifdef AUDIO_VOICES
float mod(float a, int b) {
    float r = fmod(a, b);
    return r < 0 ? r + b : r;
}

// Effect: 'vibrate' a given target frequency slightly above/below its initial value
float voice_add_vibrato(float average_freq) {
    float vibrato_counter = mod(timer_read() / (100 * vibrato_rate), VIBRATO_LUT_LENGTH);

    return average_freq * pow(vibrato_lut[(int)vibrato_counter], vibrato_strength);
}

// Effect: 'slides' the 'frequency' from the starting-point, to the target frequency
float voice_add_glissando(float from_freq, float to_freq) {
    if (to_freq != 0 && from_freq < to_freq && from_freq < to_freq * pow(2, -440 / to_freq / 12 / 2)) {
        return from_freq * pow(2, 440 / from_freq / 12 / 2);
    } else if (to_freq != 0 && from_freq > to_freq && from_freq > to_freq * pow(2, 440 / to_freq / 12 / 2)) {
        return from_freq * pow(2, -440 / from_freq / 12 / 2);
    } else {
        return to_freq;
    }
}
#endif

float voice_envelope(float frequency) {
    // envelope_index ranges from 0 to 0xFFFF, which is preserved at 880.0 Hz
//    __attribute__((unused)) uint16_t compensated_index = (uint16_t)((float)envelope_index * (880.0 / frequency));
#ifdef AUDIO_VOICES
    uint16_t envelope_index    = timer_elapsed(voices_timer); // TODO: multiply in some factor?
    uint16_t compensated_index = envelope_index / 100;        // TODO: correct factor would be?
#endif

    switch (voice) {
        case default_voice:
            glissando = false;
            // note_timbre    = TIMBRE_50; //Note: leave the user the possibility to adjust the timbre with 'audio_set_timbre'
            break;

#ifdef AUDIO_VOICES

        case vibrating:
            glissando = false;
            vibrato   = true;
            break;

        case something:
            glissando = false;
            switch (compensated_index) {
                case 0 ... 9:
                    note_timbre = TIMBRE_12;
                    break;

                case 10 ... 19:
                    note_timbre = TIMBRE_25;
                    break;

                case 20 ... 200:
                    note_timbre = 12 + 12;
                    break;

                default:
                    note_timbre = 12;
                    break;
            }
            break;

        case drums:
            glissando = false;
            // switch (compensated_index) {
            //     case 0 ... 10:
            //         note_timbre = 50;
            //         break;
            //     case 11 ... 20:
            //         note_timbre = 50 * (21 - compensated_index) / 10;
            //         break;
            //     default:
            //         note_timbre = 0;
            //         break;
            // }
            // frequency = (rand() % (int)(frequency * 1.2 - frequency)) + (frequency * 0.8);

            if (frequency < 80.0) {
            } else if (frequency < 160.0) {
                // Bass drum: 60 - 100 Hz
                frequency = (rand() % (int)(40)) + 60;
                switch (envelope_index) {
                    case 0 ... 10:
                        note_timbre = 50;
                        break;
                    case 11 ... 20:
                        note_timbre = 50 * (21 - envelope_index) / 10;
                        break;
                    default:
                        note_timbre = 0;
                        break;
                }

            } else if (frequency < 320.0) {
                // Snare drum: 1 - 2 KHz
                frequency = (rand() % (int)(1000)) + 1000;
                switch (envelope_index) {
                    case 0 ... 5:
                        note_timbre = 50;
                        break;
                    case 6 ... 20:
                        note_timbre = 50 * (21 - envelope_index) / 15;
                        break;
                    default:
                        note_timbre = 0;
                        break;
                }

            } else if (frequency < 640.0) {
                // Closed Hi-hat: 3 - 5 KHz
                frequency = (rand() % (int)(2000)) + 3000;
                switch (envelope_index) {
                    case 0 ... 15:
                        note_timbre = 50;
                        break;
                    case 16 ... 20:
                        note_timbre = 50 * (21 - envelope_index) / 5;
                        break;
                    default:
                        note_timbre = 0;
                        break;
                }

            } else if (frequency < 1280.0) {
                // Open Hi-hat: 3 - 5 KHz
                frequency = (rand() % (int)(2000)) + 3000;
                switch (envelope_index) {
                    case 0 ... 35:
                        note_timbre = 50;
                        break;
                    case 36 ... 50:
                        note_timbre = 50 * (51 - envelope_index) / 15;
                        break;
                    default:
                        note_timbre = 0;
                        break;
                }
            }
            break;
        case butts_fader:
            glissando = true;
            switch (compensated_index) {
                case 0 ... 9:
                    frequency   = frequency / 4;
                    note_timbre = TIMBRE_12;
                    break;

                case 10 ... 19:
                    frequency   = frequency / 2;
                    note_timbre = TIMBRE_12;
                    break;

                case 20 ... 200:
                    note_timbre = 12 - (uint8_t)(pow(((float)compensated_index - 20) / (200 - 20), 2) * 12.5);
                    break;

                default:
                    note_timbre = 0;
                    break;
            }
            break;

            // case octave_crunch:
            //     switch (compensated_index) {
            //         case 0 ... 9:
            //         case 20 ... 24:
            //         case 30 ... 32:
            //             frequency = frequency / 2;
            //             note_timbre = TIMBRE_12;
            //         break;

            //         case 10 ... 19:
            //         case 25 ... 29:
            //         case 33 ... 35:
            //             frequency = frequency * 2;
            //             note_timbre = TIMBRE_12;
            //          break;

            //         default:
            //             note_timbre = TIMBRE_12;
            //          break;
            //     }
            //  break;

        case duty_osc:
            // This slows the loop down a substantial amount, so higher notes may freeze
            glissando = true;
            switch (compensated_index) {
                default:
#    define OCS_SPEED 10
#    define OCS_AMP .25
                    // sine wave is slow
                    // note_timbre = (sin((float)compensated_index/10000*OCS_SPEED) * OCS_AMP / 2) + .5;
                    // triangle wave is a bit faster
                    note_timbre = (uint8_t)abs((compensated_index * OCS_SPEED % 3000) - 1500) * (OCS_AMP / 1500) + (1 - OCS_AMP) / 2;
                    break;
            }
            break;

        case duty_octave_down:
            glissando   = true;
            note_timbre = (uint8_t)(100 * (envelope_index % 2) * .125 + .375 * 2);
            if ((envelope_index % 4) == 0) note_timbre = 50;
            if ((envelope_index % 8) == 0) note_timbre = 0;
            break;
        case delayed_vibrato:
            glissando   = true;
            note_timbre = TIMBRE_50;
#    define VOICE_VIBRATO_DELAY 150
#    define VOICE_VIBRATO_SPEED 50
            switch (compensated_index) {
                case 0 ... VOICE_VIBRATO_DELAY:
                    break;
                default:
                    // TODO: merge/replace with voice_add_vibrato above
                    frequency = frequency * vibrato_lut[(int)fmod((((float)compensated_index - (VOICE_VIBRATO_DELAY + 1)) / 1000 * VOICE_VIBRATO_SPEED), VIBRATO_LUT_LENGTH)];
                    break;
            }
            break;
            // case delayed_vibrato_octave:
            //     if ((envelope_index % 2) == 1) {
            //         note_timbre = 55;
            //     } else {
            //         note_timbre = 45;
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
            //     note_timbre = TIMBRE_50;
            //     if ((envelope_index % 3) == 0)
            //         note_timbre = TIMBRE_75;
            //     break;
            // case duty_fourth_down:
            //     note_timbre = 0;
            //     if ((envelope_index % 12) == 0)
            //         note_timbre = TIMBRE_75;
            //     if (((envelope_index % 12) % 4) != 1)
            //         note_timbre = TIMBRE_75;
            //     break;
            // case duty_third_down:
            //     note_timbre = TIMBRE_50;
            //     if ((envelope_index % 5) == 0)
            //         note_timbre = TIMBRE_75;
            //     break;
            // case duty_fifth_third_down:
            //     note_timbre = TIMBRE_50;
            //     if ((envelope_index % 5) == 0)
            //         note_timbre = TIMBRE_75;
            //     if ((envelope_index % 3) == 0)
            //         note_timbre = TIMBRE_25;
            //     break;

#endif // AUDIO_VOICES

        default:
            break;
    }

#ifdef AUDIO_VOICES
    if (vibrato && (vibrato_strength > 0)) {
        frequency = voice_add_vibrato(frequency);
    }

    if (glissando) {
        // TODO: where to keep track of the start-frequency?
        // frequency = voice_add_glissando(??, frequency);
    }
#endif // AUDIO_VOICES

    return frequency;
}

// Vibrato functions

void voice_set_vibrato_rate(float rate) {
    vibrato_rate = rate;
}
void voice_increase_vibrato_rate(float change) {
    vibrato_rate *= change;
}
void voice_decrease_vibrato_rate(float change) {
    vibrato_rate /= change;
}
void voice_set_vibrato_strength(float strength) {
    vibrato_strength = strength;
}
void voice_increase_vibrato_strength(float change) {
    vibrato_strength *= change;
}
void voice_decrease_vibrato_strength(float change) {
    vibrato_strength /= change;
}

// Timbre functions

void voice_set_timbre(uint8_t timbre) {
    if ((timbre > 0) && (timbre < 100)) {
        note_timbre = timbre;
    }
}
uint8_t voice_get_timbre(void) {
    return note_timbre;
}
