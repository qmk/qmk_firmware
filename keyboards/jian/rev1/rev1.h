#ifndef REV1_H
#define REV1_H

#include "jian.h"
#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

#define XXX KC_NO
#define ___ KC_TRNS
#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06,    R06, R05, R04, R03, R02, R01, R00, \
       L11, L12, L13, L14, L15, L16,    R16, R15, R14, R13, R12, R11, \
       L21, L22, L23, L24, L25, L26,    R26, R25, R24, R23, R22, R21, \
                      L34, L35, L36,    R36, R35, R34 \
) \
{ \
  {L00, L01, L02, L03, L04, L05, L06}, \
  {___, L11, L12, L13, L14, L15, L16}, \
  {___, L21, L22, L23, L24, L25, L26}, \
  {___, ___, ___, ___, L34, L35, L36}, \
  {R00, R01, R02, R03, R04, R05, R06}, \
  {___, R11, R12, R13, R14, R15, R16}, \
  {___, R21, R22, R23, R24, R25, R26}, \
  {___, ___, ___, ___, R34, R35, R36} \
}

#define SYMM_LAYOUT( \
  K00, K01, K02, K03, K04, K05, K06, \
       K11, K12, K13, K14, K15, K16, \
       K21, K22, K23, K24, K25, K26, \
                      K34, K35, K36 \
) \
{ \
  {K00, K01, K02, K03, K04, K05, K06}, \
  {___, K11, K12, K13, K14, K15, K16}, \
  {___, K21, K22, K23, K24, K25, K26}, \
  {___, ___, ___, ___, K34, K35, K36}, \
  {K00, K01, K02, K03, K04, K05, K06}, \
  {___, K11, K12, K13, K14, K15, K16}, \
  {___, K21, K22, K23, K24, K25, K26}, \
  {___, ___, ___, ___, K34, K35, K36} \
}

#ifdef DIPS_ENABLE
#define LAYOUT_DIPS( \
  DL0, DL1, DL2, DL3, DL4, DL5, \
  DR5, DR4, DR3, DR2, DR1, DR0  \
) \
{ \
  {___, ___, ___, ___, ___, ___, ___}, \
  {DL0, ___, ___, ___, ___, ___, ___}, \
  {DL1, ___, ___, ___, ___, ___, ___}, \
  {DL2, DL3, DL4, DL5, ___, ___, ___}, \
  {___, ___, ___, ___, ___, ___, ___}, \
  {DR0, ___, ___, ___, ___, ___, ___}, \
  {DR1, ___, ___, ___, ___, ___, ___}, \
  {DR2, DR3, DR4, DR5, ___, ___, ___}, \
}
#endif // DIPS_ENABLE

#define LAYOUT_jian LAYOUT

//void promicro_bootloader_jmp(bool program);


#endif //REV1_H
