#ifndef TEENSY_3_6_ONEKEY_H
#define TEENSY_3_6_ONEKEY_H
#include "chibios_test.h"
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "ch_test.h"

#include "chprintf.h"
#include "shell.h"

#if defined(HAL_USE_SDC)
#include "fatfs/src/ff.h"
#endif

int local_fatfs_init(void);
#define LAYOUT(k00) {{ k00 }}

#endif
