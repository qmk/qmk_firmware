
#pragma once
#include <stdint.h>
#include "analogkeys.h"

void initialize_SMA_filter(hybrid_key_t key, uint8_t samplesExponent);

uint16_t SMA_filter(hybrid_key_t key, uint16_t value);
