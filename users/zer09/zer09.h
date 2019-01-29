#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum custom_keycodes {
  CK_SAFE = SAFE_RANGE,
  RGUP,
  RGDWN,
  YREG,
  NEW_SAFE_RANGE
};

#define _______ KC_TRNS
#define KC_RGUP RGUP
#define KC_RGDWN RGDWN
#define KC_YREG YREG

#define _BL 0 // The base layer
#define _UL 1 // The up layer
#define _DL 2 // The down layer
#define _VL 3 // The shifted up layer
#define _AL 4 // The assorted layer
#define _GM 5

#endif
