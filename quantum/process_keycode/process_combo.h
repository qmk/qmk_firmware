#ifndef PROCESS_COMBO_H
#define PROCESS_COMBO_H

#include <stdint.h>
#include "progmem.h"
#include "quantum.h"


typedef struct
{
    const uint16_t *keys;
    uint16_t action;        
    uint32_t state;
} combo_t;


#define COMBO_END 0
#define NUM_ELEMS(a) (sizeof(a)/sizeof 0[a])


extern combo_t key_combos[1];

bool process_combo(uint16_t keycode, keyrecord_t *record);

#endif