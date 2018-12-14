#ifndef HANDWIRED_H
#define HANDWIRED_H

#include "jian.h"
#include "quantum.h"

#define XXX KC_NO
#define ___ KC_TRNS

#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06,    R06, R05, R04, R03, R02, R01, R00, \
       L11, L12, L13, L14, L15, L16,    R16, R15, R14, R13, R12, R11, \
       L21, L22, L23, L24, L25, L26,    R26, R25, R24, R23, R22, R21, \
                      L34, L35, L36,    R36, R35, R34 \
) \
{ \
  {L00, L01, L02, L03, L04, L05, L06,   R06, R05, R04, R03, R02, R01, R00}, \
  {XXX, L11, L12, L13, L14, L15, L16,   R16, R15, R14, R13, R12, R11, XXX}, \
  {XXX, L21, L22, L23, L24, L25, L26,   R26, R25, R24, R23, R22, R21, XXX}, \
  {XXX, XXX, XXX, XXX, L34, L35, L36,   R36, R35, R34, XXX, XXX, XXX, XXX} \
}
#define LAYOUT_handwired LAYOUT

//void promicro_bootloader_jmp(bool program);

#endif // HANDWIRED_H
