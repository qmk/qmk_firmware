#ifndef REV1_H
#define REV1_H

#include "lets_split.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

//void promicro_bootloader_jmp(bool program);

#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06,      R06, R05, R04, R03, R02, R01, R00, \
  L10, L11, L12, L13, L14, L15,      R17, R16, R15, R14, R13, R12, R11, R10, \
  L20, L21, L22, L23, L24, L25,           R26, R25, R24, R23, R22, R21, R20, \
  L30, L31, L32, L33, L34, L35,                R35, R34, R33, R32, R31, R30, \
  L40, L41, L42, L43, L44,                          R44, R43, R42, R41, R40 \
	) \
  { \
  { L00, L01, L02, L03, L04, L05, L06 }, \
  { L10, L11, L12, L13, L14, L15 }, \
  { L20, L21, L22, L23, L24, L25 }, \
  { L30, L31, L32, L33, L34, L35 }, \
  { L40, L41, L42, L43, L44 }, \
  { R06, R05, R04, R03, R02, R01, R00 }, \
  { R17, R16, R15, R14, R13, R12, R11, R10 }, \
  { R26, R25, R24, R23, R22, R21, R20 }, \
  { R35, R34, R33, R32, R31, R30 }, \
  { R44, R43, R42, R41, R40 } \
	}

#define LAYOUT_split60 LAYOUT

#endif
