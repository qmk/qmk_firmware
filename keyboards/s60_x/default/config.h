#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

#include "config_common.h"

#define PRODUCT         S60-X
#define DESCRIPTION     q.m.k. keyboard firmware for S60-X

#define MATRIX_ROW_PINS { B7, B3, B2, B1, B0 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4, B5, B6, C6, C7, E6, F1 }
#define UNUSED_PINS { F0 }

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#endif
