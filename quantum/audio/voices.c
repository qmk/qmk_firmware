#include "voices.h"
#include "audio.h"
#include "stdlib.h"

// these are imported from audio.c
extern uint16_t envelope_index;
extern float note_timbre;
extern float polyphony_rate;
extern bool glissando;

voice_type voice = default_voice;

void set_voice(voice_type v) {
    voice = v;
}

void voice_iterate() {
    voice = (voice + 1) % number_of_voices;
}

void voice_deiterate() {
    voice = (voice - 1 + number_of_voices) % number_of_voices;
}

float voice_envelope(float frequency) {
    // envelope_index ranges from 0 to 0xFFFF, which is preserved at 880.0 Hz
    uint16_t compensated_index = (uint16_t)((float)envelope_index * (880.0 / frequency));

    switch (voice) {
        case default_voice:
            glissando = true;
            note_timbre = TIMBRE_50;
            polyphony_rate = 0;
	        break;

    #ifdef AUDIO_VOICES

        case something:
            glissando = false;
            polyphony_rate = 0;
            switch (compensated_index) {
                case 0 ... 9:
                    note_timbre = TIMBRE_12;
                    break;

                case 10 ... 19:
                    note_timbre = TIMBRE_25;
                    break;

                case 20 ... 200:
                    note_timbre = .125 + .125;
                    break;

                default:
                    note_timbre = .125;
                    break;
            }
            break;

        case drums:
            glissando = false;
            polyphony_rate = 0;
                // switch (compensated_index) {
                //     case 0 ... 10:
                //         note_timbre = 0.5;
                //         break;
                //     case 11 ... 20:
                //         note_timbre = 0.5 * (21 - compensated_index) / 10;
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
                        note_timbre = 0.5;
                        break;
                    case 11 ... 20:
                        note_timbre = 0.5 * (21 - envelope_index) / 10;
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
                        note_timbre = 0.5;
                        break;
                    case 6 ... 20:
                        note_timbre = 0.5 * (21 - envelope_index) / 15;
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
                        note_timbre = 0.5;
                        break;
                    case 16 ... 20:
                        note_timbre = 0.5 * (21 - envelope_index) / 5;
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
                        note_timbre = 0.5;
                        break;
                    case 36 ... 50:
                        note_timbre = 0.5 * (51 - envelope_index) / 15;
                        break;
                    default:
                        note_timbre = 0;
                        break;
                }

            }
            break;
        case butts_fader:
            glissando = true;
            polyphony_rate = 0;
            switch (compensated_index) {
                case 0 ... 9:
                    frequency = frequency / 4;
                    note_timbre = TIMBRE_12;
	                break;

                case 10 ... 19:
                    frequency = frequency / 2;
                    note_timbre = TIMBRE_12;
	                break;

                case 20 ... 200:
                    note_timbre = .125 - pow(((float)compensated_index - 20) / (200 - 20), 2)*.125;
	                break;

                default:
                    note_timbre = 0;
                	break;
            }
    	    break;

        // case octave_crunch:
        //     polyphony_rate = 0;
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
        //         	break;
        //     }
	       //  break;

        case duty_osc:
            // This slows the loop down a substantial amount, so higher notes may freeze
            glissando = true;
            polyphony_rate = 0;
            switch (compensated_index) {
                default:
                    #define OCS_SPEED 10
                    #define OCS_AMP   .25
                    // sine wave is slow
                    // note_timbre = (sin((float)compensated_index/10000*OCS_SPEED) * OCS_AMP / 2) + .5;
                    // triangle wave is a bit faster
                    note_timbre = (float)abs((compensated_index*OCS_SPEED % 3000) - 1500) * ( OCS_AMP / 1500 ) + (1 - OCS_AMP) / 2;
                	break;
            }
	        break;

        case duty_octave_down:
            glissando = true;
            polyphony_rate = 0;
            note_timbre = (envelope_index % 2) * .125 + .375 * 2;
            if ((envelope_index % 4) == 0)
                note_timbre = 0.5;
            if ((envelope_index % 8) == 0)
                note_timbre = 0;
            break;
        case delayed_vibrato:
            glissando = true;
            polyphony_rate = 0;
            note_timbre = TIMBRE_50;
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
        //     if ((envelope_index % 2) == 1) {
        //         note_timbre = 0.55;
        //     } else {
        //         note_timbre = 0.45;
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
        //     note_timbre = 0.5;
        //     if ((envelope_index % 3) == 0)
        //         note_timbre = 0.75;
        //     break;
        // case duty_fourth_down:
        //     note_timbre = 0.0;
        //     if ((envelope_index % 12) == 0)
        //         note_timbre = 0.75;
        //     if (((envelope_index % 12) % 4) != 1)
        //         note_timbre = 0.75;
        //     break;
        // case duty_third_down:
        //     note_timbre = 0.5;
        //     if ((envelope_index % 5) == 0)
        //         note_timbre = 0.75;
        //     break;
        // case duty_fifth_third_down:
        //     note_timbre = 0.5;
        //     if ((envelope_index % 5) == 0)
        //         note_timbre = 0.75;
        //     if ((envelope_index % 3) == 0)
        //         note_timbre = 0.25;
        //     break;

    #endif

		default:
   			break;
    }

    return frequency;
}
