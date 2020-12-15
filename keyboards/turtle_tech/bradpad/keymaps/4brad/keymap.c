#include QMK_KEYBOARD_H
#include "midi.h"
#include "process_midi.h"

extern MidiDevice midi_device;

#define _NATURAL 0
#define _SHARP 1
#define _FLAT 2

//MIDI CC codes for generic ON/OFF swiches
//80,81,82,83
//values off = 0-63

#define OFF 0

//values on = 64-127

#define ON 127

//implementation inspo taken from here: https://github.com/luantty2/pheromone_keyboard/blob/master/keyboards/pheromone/keymaps/default/keymap.c



enum custom_keycodes {MIDI_CC80 = SAFE_RANGE, MIDI_CC81, MIDI_CC82, MIDI_CC83};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
	switch(keycode){
		case MIDI_CC80:
			if(record->event.pressed){
				midi_send_cc(&midi_device, midi_config.channel, 80, ON);
			}
			else {
				midi_send_cc(&midi_device, midi_config.channel, 80, OFF);
			}
			return true;
		case MIDI_CC81:
			if(record->event.pressed){
				midi_send_cc(&midi_device, midi_config.channel, 81, ON);
			}
			else {
				midi_send_cc(&midi_device, midi_config.channel, 81, OFF);
			}
			return true;
		case MIDI_CC82:
			if(record->event.pressed){
				midi_send_cc(&midi_device, midi_config.channel, 82, ON);
			}
			else {
				midi_send_cc(&midi_device, midi_config.channel, 82, OFF);
			}
			return true;
		case MIDI_CC83:
			if(record->event.pressed){
				midi_send_cc(&midi_device, midi_config.channel, 83, ON);
			}
			else {
				midi_send_cc(&midi_device, midi_config.channel, 83, OFF);
			}
			return true;
	}
	return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_NATURAL] = LAYOUT( 
		MI_C, MI_BENDD,   MI_BENDU,  MI_G, \
		MI_D, MIDI_CC80,  MIDI_CC81, MI_A, \
		MI_E, MIDI_CC82,  MIDI_CC83, MI_B, \
		MI_F, MI_OCTD,    MI_OCTU,   MI_C,\
		      MO(_SHARP), MO(_FLAT)),
    [_SHARP] = LAYOUT( 
		MI_Cs, KC_TRNS,  KC_TRNS,  MI_Gs, \
		MI_Ds, KC_TRNS,  KC_TRNS,  MI_As, \
		MI_F , KC_TRNS,  KC_TRNS,  MI_C , \
		MI_Fs, MI_TRNSD, MI_TRNSU, MI_Cs,\
		       KC_TRNS,  KC_TRNS),
    [_FLAT] = LAYOUT( 
		MI_B , KC_TRNS,  KC_TRNS,  MI_Gb, \
		MI_Db, KC_TRNS,  KC_TRNS,  MI_Ab, \
		MI_Eb, KC_TRNS,  KC_TRNS,  MI_Bb, \
		MI_E , MI_TRNSD, MI_TRNSU, MI_B,\
		       KC_TRNS,  KC_TRNS),
};
