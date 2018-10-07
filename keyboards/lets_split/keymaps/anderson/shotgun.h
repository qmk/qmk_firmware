#include "lets_split.h"

#ifndef SHOTGUN_H
#define SHOTGUN_H

typedef struct chord_t {
    uint16_t keys[2];
    uint32_t pressed[2];
    uint16_t result;
} CHORD;

extern CHORD chords[];
extern uint16_t chords_size;

void shotgun_register(uint16_t key);
void shotgun_unregister(uint16_t key);
void shotgun_process(void);

#endif
