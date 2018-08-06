// temporary code for test
// rgblight.c new macro test on HOST computer
// cc -o rgblight-macro-test rgblight-macro-test.c
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define _RGBM_SINGLE(sym)  RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP(sym)     RGBLIGHT_MODE_ ## sym,
enum RGBLIGHT_EFFECT_MODE {
    RGBLIGHT_MODE_zero = 0,
#include "rgblight-macro-test1.h"
    RGBLIGHT_MODE_end
};

int main(int argc, char *argv[])
{
#define _RGBM_SINGLE(sym) \
  printf( "RGBLIGHT_MODE_%s = %d\n", #sym, RGBLIGHT_MODE_ ## sym);
#define _RGBM_MULTI(sym) \
  printf( "RGBLIGHT_MODE_%s = %d-%d\n", #sym, \
          RGBLIGHT_MODE_ ## sym, \
          RGBLIGHT_MODE_ ## sym ## _end);
#define _RGBM_TMP(sym)
  #include "rgblight-macro-test1.h"
    exit(0);
}
