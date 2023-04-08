#pragma once

#include "quantum.h"

#define ENCODER_LAYOUT( \
  E10, E11, \
  E20, E21 \
) \
{ \
  { E10, E11 }, \
  { E20, E21 } \
}

#define EXTRA_ENCODER_LAYOUT( \
  E10, E11, \
  E20, E21, \
  E30, E31, \
  E40, E41, \
  E50, E51, \
  E60, E61  \
) \
{ \
  { E10, E11 }, \
  { E20, E21 }, \
  { E30, E31 }, \
  { E40, E41 }, \
  { E50, E51 }, \
  { E60, E61 } \
}
