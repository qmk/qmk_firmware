/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include "bbaserdem.h"
#ifdef VELOCIKEY_ENABLE
    #include "velocikey.h"
#endif

// Code to print status string
void encoder_state_string(uint8_t index, uint8_t layer, char* buffer);
void encoder_state_string_long(uint8_t index, uint8_t layer, char* buffer);
// Hook to encoder stuff
bool encoder_update_user(uint8_t index, bool clockwise);
// Complicated code for what the encoder keys do when pressed
bool process_record_encoder(uint16_t keycode, keyrecord_t *record);
// Initializing the encoder array
void keyboard_post_init_encoder(void);
// Clear the encoder settings
void reset_encoder_state(void);

// Structure to keep runtime info on encoder state
typedef struct {
    uint8_t base;   // The encoder state on most layers; regular function
    uint8_t rgb;    // The encoder state on media layer; controls light settings
    uint8_t point;  // The encoder state on mouse layer; moves pointer
} encoder_state_t;
