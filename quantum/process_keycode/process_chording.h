#ifndef PROCESS_CHORDING_H
#define PROCESS_CHORDING_H

#include "quantum.h"

// Chording stuff
#define CHORDING_MAX 4
bool chording = false;

uint8_t chord_keys[CHORDING_MAX] = {0};
uint8_t chord_key_count = 0;
uint8_t chord_key_down = 0;

bool process_chording(uint16_t keycode, keyrecord_t *record);

#endif