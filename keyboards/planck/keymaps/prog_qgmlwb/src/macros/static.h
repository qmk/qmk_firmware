#pragma once

#include "../base.h"

enum dead_keys { NO_TILD_M = 0, NO_CIRC_M, NO_GRV_M };

bool process_static(uint16_t keycode, keyrecord_t* record);
