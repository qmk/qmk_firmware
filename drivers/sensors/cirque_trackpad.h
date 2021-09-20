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
} tm040040_data_t;

void            cirque_trackpad_init(void);
tm040040_data_t cirque_trackpad_read_data(void);
void            cirque_trackpad_scale_data(tm040040_data_t* coordinates, uint16_t xResolution, uint16_t yResolution);
uint16_t        cirque_trackpad_get_scale(void);
void            cirque_trackpad_set_scale(uint16_t scale);

// Cirque's 7-bit I2C Slave Address
#ifndef CIRQUE_TRACKPAD_ADDR
#    define CIRQUE_TRACKPAD_ADDR 0x2A
#endif
#ifndef CIRQUE_TRACKPAD_TIMEOUT
#    define CIRQUE_TRACKPAD_TIMEOUT 20
#endif

// Coordinate scaling values
#ifndef CIRQUE_TRACKPAD_X_LOWER
#    define CIRQUE_TRACKPAD_X_LOWER 127  // min "reachable" X value
#endif
#ifndef CIRQUE_TRACKPAD_X_UPPER
#    define CIRQUE_TRACKPAD_X_UPPER 1919  // max "reachable" X value
#endif
#ifndef CIRQUE_TRACKPAD_Y_LOWER
#    define CIRQUE_TRACKPAD_Y_LOWER 63  // min "reachable" Y value
#endif
#ifndef CIRQUE_TRACKPAD_Y_UPPER
#    define CIRQUE_TRACKPAD_Y_UPPER 1471  // max "reachable" Y value
#endif
#ifndef CIRQUE_TRACKPAD_X_RANGE
#    define CIRQUE_TRACKPAD_X_RANGE (CIRQUE_TRACKPAD_X_UPPER - CIRQUE_TRACKPAD_X_LOWER)
#endif
#ifndef CIRQUE_TRACKPAD_Y_RANGE
#    define CIRQUE_TRACKPAD_Y_RANGE (CIRQUE_TRACKPAD_Y_UPPER - CIRQUE_TRACKPAD_Y_LOWER)
#endif
