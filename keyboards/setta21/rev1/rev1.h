#pragma once

#include "setta21.h"

#define LAYOUT_numpad_6x4( \
       L05, L15, L25, L35, \
       L04, L14, L24, L34, \
       L03, L13, L23,      \
       L02, L12, L22, L32, \
       L01, L11, L21,      \
       L00,      L20, L30  \
  ) \
  { \
    {  L00,  L01,  L02,  L03,  L04,  L05  },  \
    {KC_NO,  L11,  L12,  L13,  L14,  L15  },  \
    {  L20,  L21,  L22,  L23,  L24,  L25  },  \
    {  L30,KC_NO,  L32,KC_NO,  L34,  L35  }   \
  }
