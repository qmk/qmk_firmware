#ifndef PROCESS_COMBO_H
#define PROCESS_COMBO_H

#include <stdint.h>
#include "progmem.h"
#include "quantum.h"

typedef struct
{
    const uint16_t *keys;
    uint16_t keycode;        
#ifdef EXTRA_EXTRA_LONG_COMBOS
    uint32_t state;
#elif EXTRA_LONG_COMBOS
    uint16_t state;
#else
    uint8_t state;
#endif
    uint16_t timer;
#ifdef COMBO_ALLOW_ACTION_KEYS
    keyrecord_t prev_record;
#else
    uint16_t prev_key;
#endif
} combo_t;


#define COMBO(ck, ca)       {.keys = &(ck)[0], .keycode = (ca)}
#define COMBO_ACTION(ck)    {.keys = &(ck)[0]}

#define COMBO_END 0
#ifndef COMBO_COUNT
#define COMBO_COUNT 0
#endif
#ifndef COMBO_TERM
#define COMBO_TERM TAPPING_TERM
#endif

bool process_combo(uint16_t keycode, keyrecord_t *record);
void matrix_scan_combo(void);
void process_combo_event(uint8_t combo_index, bool pressed);

#endif
