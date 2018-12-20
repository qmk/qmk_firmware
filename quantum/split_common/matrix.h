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
    rgblight_config_t rgblight_config; //not yet use
    //
    // When MCUs on both sides drive their respective RGB LED chains,
    // it is necessary to synchronize, so it is necessary to communicate RGB information.
    // In that case, define the RGBLIGHT_SPLIT macro.
    //
    // Otherwise, if the master side MCU drives both sides RGB LED chains,
    // there is no need to communicate.
#endif
} Serial_m2s_buffer_t;

extern volatile Serial_m2s_buffer_t serial_m2s_buffer;

void serial_master_init(void);
void serial_slave_init(void);

#endif
