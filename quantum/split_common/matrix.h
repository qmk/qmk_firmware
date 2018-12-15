#ifndef SPLIT_COMMON_MATRIX_H
#define SPLIT_COMMON_MATRIX_H

#include <common/matrix.h>

#ifdef RGBLIGHT_ENABLE
#   include "rgblight.h"
#endif

typedef struct _Serial_m2s_buffer_t {
#ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#endif
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    //not yet rgblight_config_t rgblight_config;
#endif
} Serial_m2s_buffer_t;

extern volatile Serial_m2s_buffer_t serial_m2s_buffer;

void serial_master_init(void);
void serial_slave_init(void);

#endif
