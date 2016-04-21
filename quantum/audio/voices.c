#include "voices.h"

extern uint16_t envelope_index;
extern float note_timbre;

voice_type voice = default_voice;

void set_voice(voice_type v) {
	voice = v;
}

float voice_envelope(float frequency) {
	// envelope_index ranges from 0 to 0xFFFF, which is preserved at 880.0 Hz
    uint16_t compensated_index = (uint16_t)((float)envelope_index * (880.0 / frequency));

    switch (voice) {
    	case default_voice:
    		// nothing here on purpose
    	break;
    	case butts_fader:
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
	}

	return frequency;
}