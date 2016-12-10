#ifndef PROCESS_COMBO_H
#define PROCESS_COMBO_H

#include <stdint.h>
#include "progmem.h"
#include "quantum.h"

#ifndef COMBO_TERM
#define COMBO_TERM TAPPING_TERM
#endif

typedef struct
{
    const uint16_t *keys;
    uint16_t action;        
    uint32_t state;
#if COMBO_TERM
    uint16_t timer;
    uint16_t key;
#endif
} combo_t;


#if COMBO_TERM
#define COMBO(ck, ca) {.keys = &(ck)[0], .action = (ca), .state = 0, .timer = 0, .key = 0}
#else
#define COMBO(ck, ca) {.keys = &(ck)[0], .action = (ca), .state = 0 }
#endif
#define COMBO_END 0
#ifndef COMBO_COUNT
#define COMBO_COUNT 0
#endif

extern combo_t key_combos[COMBO_COUNT];

bool process_combo(uint16_t keycode, keyrecord_t *record);
void matrix_scan_combo(void);

#endif