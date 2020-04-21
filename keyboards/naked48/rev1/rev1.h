#pragma once

#include "naked48.h"

#include "quantum.h"
#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

//////////////////////////////////////////////////////////////////////////////
// When only use Naked48.
//////////////////////////////////////////////////////////////////////////////
/*
 * ,------------------------------------           ------------------------------------.
 * | L00 | L01 | L02 | L03 | L04 | L05 |           | L06 | L07 | L08 | L09 | L0A | L0B |
 * |------------------------------------           ------------------------------------+
 * | L10 | L11 | L12 | L13 | L14 | L15 |           | L16 | L17 | L18 | L19 | L1A | L1B |
 * |------------------------------------           ------------------------------------+
 * | L20 | L21 | L22 | L23 | L24 | L25 |           | L26 | L17 | L28 | L29 | L2A | L2B |
 * |-----------------------------------------------------------------------------------+
 *       | L30 | L32 | L33 | L34 | L35 | L36 | L37 | L38 | L39 | L3A | L3B | L3D |
 *       |-----------------------------------------------------------------------'
 */

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A, L0B, \
    L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L1A, L1B, \
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L2A, L2B, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L3A, L3B  \
  ) \
  { \
    {  L00,  L01,  L02,  L03,  L04,  L05,  L06,  L07,  L08,  L09,  L0A,  L0B  },  \
    {  L10,  L11,  L12,  L13,  L14,  L15,  L16,  L17,  L18,  L19,  L1A,  L1B  },  \
    {  L20,  L21,  L22,  L23,  L24,  L25,  L26,  L27,  L28,  L29,  L2A,  L2B  },  \
    {  L30,  L31,  L32,  L33,  L34,  L35,  L36,  L37,  L38,  L39,  L3A,  L3B  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  }   \
  }

//////////////////////////////////////////////////////////////////////////////
// When connecting Setta21 to Naked48.
//////////////////////////////////////////////////////////////////////////////

#define LAYOUT_with_setta21( \
    L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A, L0B,    R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L1A, L1B,         R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L2A, L2B,    R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L3A, L3B,    R30,      R32,      R34, R35  \
  ) \
  { \
    {  L00,  L01,  L02,  L03,  L04,  L05,  L06,  L07,  L08,  L09,  L0A,  L0B  },  \
    {  L10,  L11,  L12,  L13,  L14,  L15,  L16,  L17,  L18,  L19,  L1A,  L1B  },  \
    {  L20,  L21,  L22,  L23,  L24,  L25,  L26,  L27,  L28,  L29,  L2A,  L2B  },  \
    {  L30,  L31,  L32,  L33,  L34,  L35,  L36,  L37,  L38,  L39,  L3A,  L3B  },  \
    {  R00,  R01,  R02,  R03,  R04,  R05,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,  R11,  R12,  R13,  R14,  R15,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {  R20,  R21,  R22,  R23,  R24,  R25,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {  R30,KC_NO,  R32,KC_NO,  R34,  R35,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  }   \
  }

//////////////////////////////////////////////////////////////////////////////
// When connecting Nafuda to Naked48.
//////////////////////////////////////////////////////////////////////////////

#define LAYOUT_with_nafuda( \
    L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A, L0B,         R01,      \
    L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L1A, L1B,    R10, R11, R12, \
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L2A, L2B,    R20, R21, R22, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L3A, L3B  \
  ) \
  { \
    {  L00,  L01,  L02,  L03,  L04,  L05,  L06,  L07,  L08,  L09,  L0A,  L0B  },  \
    {  L10,  L11,  L12,  L13,  L14,  L15,  L16,  L17,  L18,  L19,  L1A,  L1B  },  \
    {  L20,  L21,  L22,  L23,  L24,  L25,  L26,  L27,  L28,  L29,  L2A,  L2B  },  \
    {  L30,  L31,  L32,  L33,  L34,  L35,  L36,  L37,  L38,  L39,  L3A,  L3B  },  \
    {KC_NO,  R01,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {  R10,  R11,  R12,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {  R20,  R21,  R22,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  }   \
  }

