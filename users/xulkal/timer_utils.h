#pragma once
#include "timer.h"
#include <stdbool.h>

bool timer_expired(uint16_t last);
bool timer_expired32(uint32_t last);
