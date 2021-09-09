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

void            cirque_tm040040_init(void);
tm040040_data_t cirque_tm040040_read_data(void);
void            cirque_tm040040_scale_data(tm040040_data_t* coordinates, uint16_t xResolution, uint16_t yResolution);

// Cirque's 7-bit I2C Slave Address
#ifndef CIRQUE_TM040040_ADDR
#    define CIRQUE_TM040040_ADDR 0x2A
#endif
#ifndef CIRQUE_TM040040_TIMEOUT
#    define CIRQUE_TM040040_TIMEOUT 20
#endif

// Coordinate scaling values
#ifndef PINNACLE_XMAX
#    define PINNACLE_XMAX 2047  // max value Pinnacle can report for X
#endif
#ifndef PINNACLE_YMAX
#    define PINNACLE_YMAX 1535  // max value Pinnacle can report for Y
#endif
#ifndef PINNACLE_X_LOWER
#    define PINNACLE_X_LOWER 127  // min "reachable" X value
#endif
#ifndef PINNACLE_X_UPPER
#    define PINNACLE_X_UPPER 1919  // max "reachable" X value
#endif
#ifndef PINNACLE_Y_LOWER
#    define PINNACLE_Y_LOWER 63  // min "reachable" Y value
#endif
#ifndef PINNACLE_Y_UPPER
#    define PINNACLE_Y_UPPER 1471  // max "reachable" Y value
#endif
#ifndef PINNACLE_X_RANGE
#    define PINNACLE_X_RANGE (PINNACLE_X_UPPER - PINNACLE_X_LOWER)
#endif
#ifndef PINNACLE_Y_RANGE
#    define PINNACLE_Y_RANGE (PINNACLE_Y_UPPER - PINNACLE_Y_LOWER)
#endif
