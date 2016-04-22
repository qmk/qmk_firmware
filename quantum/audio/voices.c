#include "voices.h"
#include "stdlib.h"

// these are imported from audio.c
extern uint16_t envelope_index;
extern float note_timbre;
extern float polyphony_rate;

voice_type voice = duty_osc;

void set_voice(voice_type v) {
    voice = v;
}

void voice_iterate() {
    voice = (voice + 1) % number_of_voices;
}

void voice_deiterate() {
    voice = (voice - 1) % number_of_voices;
}

float voice_envelope(float frequency) {
    // envelope_index ranges from 0 to 0xFFFF, which is preserved at 880.0 Hz
    uint16_t compensated_index = (uint16_t)((float)envelope_index * (880.0 / frequency));

    switch (voice) {
        case default_voice:
            note_timbre = TIMBRE_50;
            polyphony_rate = 0;
	        break;

        case butts_fader:
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

        case octave_crunch:
            polyphony_rate = 0;
            switch (compensated_index) {
                case 0 ... 9:
                case 20 ... 24:
                case 30 ... 32:
                    frequency = frequency / 2;
                    note_timbre = TIMBRE_12;
                break;

                case 10 ... 19:
                case 25 ... 29:
                case 33 ... 35:
                    frequency = frequency * 2;
                    note_timbre = TIMBRE_12;
	                break;

                default:
                    note_timbre = TIMBRE_12;
                	break;
            }
	        break;

        case duty_osc:
            // This slows the loop down a substantial amount, so higher notes may freeze
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
            polyphony_rate = 0;
            note_timbre = (envelope_index % 2) * .125 + .375 * 2;
            if ((envelope_index % 4) == 0)
                note_timbre = 0.5;
            if ((envelope_index % 8) == 0)
                note_timbre = 0;
            break;
        case duty_fifth_down:
            note_timbre = 0.5;
            if ((envelope_index % 5) == 0)
                note_timbre = 0.75;
            break;
        case duty_fourth_down:
            if ((envelope_index % 12) == 0)
                note_timbre = 0.25;
            else
                note_timbre = 0.5;
            break;

		default:
   			break;
    }

    return frequency;
}