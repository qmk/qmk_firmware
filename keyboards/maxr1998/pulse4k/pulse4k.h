#pragma once

#include "quantum.h"

#define LAYOUT( \
      k00, k01, k02, \
      k10, k11, k12 \
) \
{ \
    { k00, k01, k02 }, \
    { k10, k11, k12 }, \
}

void encoder_one_update(bool clockwise);

void encoder_two_update(bool clockwise);
