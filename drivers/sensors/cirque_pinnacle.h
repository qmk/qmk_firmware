// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license

#pragma once

#include <stdint.h>
#include "i2c_master.h"

// Convenient way to store and access measurements
typedef struct {
    uint16_t xValue;
    uint16_t yValue;
    uint16_t zValue;
    uint8_t  buttonFlags;
    bool     touchDown;
} pinnacle_data_t;

void            cirque_pinnacle_init(void);
pinnacle_data_t cirque_pinnacle_read_data(void);
void            cirque_pinnacle_scale_data(pinnacle_data_t* coordinates, uint16_t xResolution, uint16_t yResolution);
uint16_t        cirque_pinnacle_get_scale(void);
void            cirque_pinnacle_set_scale(uint16_t scale);

// Cirque's 7-bit I2C Slave Address
#ifndef CIRQUE_PINNACLE_ADDR
#    define CIRQUE_PINNACLE_ADDR 0x2A
#endif
#ifndef CIRQUE_PINNACLE_TIMEOUT
#    define CIRQUE_PINNACLE_TIMEOUT 20
#endif

// Coordinate scaling values
#ifndef CIRQUE_PINNACLE_X_LOWER
#    define CIRQUE_PINNACLE_X_LOWER 127  // min "reachable" X value
#endif
#ifndef CIRQUE_PINNACLE_X_UPPER
#    define CIRQUE_PINNACLE_X_UPPER 1919  // max "reachable" X value
#endif
#ifndef CIRQUE_PINNACLE_Y_LOWER
#    define CIRQUE_PINNACLE_Y_LOWER 63  // min "reachable" Y value
#endif
#ifndef CIRQUE_PINNACLE_Y_UPPER
#    define CIRQUE_PINNACLE_Y_UPPER 1471  // max "reachable" Y value
#endif
#ifndef CIRQUE_PINNACLE_X_RANGE
#    define CIRQUE_PINNACLE_X_RANGE (CIRQUE_PINNACLE_X_UPPER - CIRQUE_PINNACLE_X_LOWER)
#endif
#ifndef CIRQUE_PINNACLE_Y_RANGE
#    define CIRQUE_PINNACLE_Y_RANGE (CIRQUE_PINNACLE_Y_UPPER - CIRQUE_PINNACLE_Y_LOWER)
#endif
