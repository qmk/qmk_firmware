#pragma once

#include "quantum.h"

#include <stdint.h>

enum digitizer_status { DZ_INITIALIZED = 1, DZ_UPDATED = 2 };

typedef struct {
    int8_t tipswitch;
    int8_t inrange;
    uint8_t id;
    float x;
    float y;
    uint8_t status : 2;
} digitizer_t;

extern digitizer_t digitizer;

void host_digitizer_send(digitizer_t *digitizer);
