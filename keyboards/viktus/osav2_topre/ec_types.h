// ec_types.h
#ifndef EC_TYPES_H
#define EC_TYPES_H

#include <stdint.h>

typedef struct {
    uint16_t reset_pt;
    uint16_t actuation_pt;
} ec_config_t;

typedef struct {
    uint8_t row;
    uint8_t col;
} KeyPosition;

typedef struct {
    const KeyPosition* key_position;
    ec_config_t        key_level;
} KeyConfig;

#endif // EC_TYPES_H