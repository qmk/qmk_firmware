#pragma once

#include "quantum.h"

//void promicro_bootloader_jmp(bool program);
/*
 * ,-----------------.
 * |     | L01 |     |
 * |-----------------+
 * | L10 | L11 | L12 |
 * |-----------------+
 * | L20 | L21 | L22 |
 * |-----------------'
 */

#define LAYOUT( \
         L01,      \
    L10, L11, L12, \
    L20, L21, L22  \
  ) \
  { \
    {KC_NO,  L01,KC_NO  },  \
    {  L10,  L11,  L12  },  \
    {  L20,  L21,  L22  }   \
  }
