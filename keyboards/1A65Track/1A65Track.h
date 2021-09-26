#pragma once

#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

#define ___ KC_NO

#define LAYOUT_65( \
	L00, L01, L02, L03, L04, L05, L06, L07, 	  R01, R02, R03, R04, R05, R06, R07, R08, \
	L10, L11, L12, L13, L14, L15, L16,       R10, R11, R12, R13, R14, R15, R16, R17, R18, \
	L20, L21, L22, L23, L24, L25, L26,  		  R20, R21, R22, R23, R24, R25, R26, R27, \
	L30, L31, L32, L33, L34, L35, L36,  		  R30, R31, R32, R33, R34, R35, R36,  \
	L40, L41, L42, L43, L44, L45, L46, 		 R40, R41, R42, R43, R44, R45, R46, R47 \
) \
{ \
	{ L00, L01, L02, L03, L04, L05, L06, L07, ___ }, \
	{ L10, L11, L12, L13, L14, L15, L16, ___, ___ }, \
	{ L20, L21, L22, L23, L24, L25, L26, ___, ___ }, \
	{ L30, L31, L32, L33, L34, L35, L36, ___, ___ }, \
	{ L40, L41, L42, L43, L44, L45, L46, ___, ___ }, \
	{ ___, R01, R02, R03, R04, R05, R06, R07, R08 }, \
	{ R10, R11, R12, R13, R14, R15, R16, R17, R18 }, \
	{ R20, R21, R22, R23, R24, R25, R26, R27, ___ }, \
	{ R30, R31, R32, R33, R34, R35, R36, ___, ___ }, \
	{ R40, R41, R42, R43, R44, R45, R46, R47, ___ }  \
}

enum custom_keycodes {
    KC_SCROLLY = SAFE_RANGE,
	KC_SCROLLX,
    KC_CPI_1,
	UCFEMAIL,
	GMAIL,
	SBRC,
	CBRC
};

typedef union {
  uint32_t raw;
  struct {
    uint16_t cpi;
  };
} config_65Track_t;
