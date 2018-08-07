// temporary code for test
// rgblight.c new macro test on HOST computer
// cc -o rgblight-macro-test rgblight-macro-test.c
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef RGBLIGHT_ANIMATIONS
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   #define RGBLIGHT_EFFECT_RGB_TEST
   #define RGBLIGHT_EFFECT_ALTERNATING
   #define RGBLIGHT_USE_TIMER
#endif

#define _RGBM_SINGLE_STATIC(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_SINGLE_DYNAMIC(sym)  RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI_STATIC(sym)    RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI_DYNAMIC(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP_STATIC(sym)      RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP_DYNAMIC(sym)     RGBLIGHT_MODE_ ## sym,
enum RGBLIGHT_EFFECT_MODE {
    RGBLIGHT_MODE_zero = 0,
#include "rgblight-macro-test2.h"
    RGBLIGHT_MODE_last
};

#define RGBLIGHT_MODES (RGBLIGHT_MODE_last-1)


#define _RGBM_SINGLE_STATIC(sym)
#define _RGBM_SINGLE_DYNAMIC(sym)  RGBLIGHT_DYNAMIC_ ## sym,
#define _RGBM_MULTI_STATIC(sym)
#define _RGBM_MULTI_DYNAMIC(sym)   RGBLIGHT_DYNAMIC_ ## sym,
#define _RGBM_TMP_STATIC(sym)
#define _RGBM_TMP_DYNAMIC(sym)     RGBLIGHT_DYNAMIC_ ## sym,
enum RGBLIGHT_DYNAMIC_MODE {
#include "rgblight-macro-test2.h"
    RGBLIGHT_DYNAMIC_last
};

#define _RGBM_SINGLE_STATIC(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_SINGLE_DYNAMIC(sym)
#define _RGBM_MULTI_STATIC(sym)    RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI_DYNAMIC(sym)
#define _RGBM_TMP_STATIC(sym)      RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP_DYNAMIC(sym)
static uint8_t static_effect_table [] = {
#include "rgblight-macro-test2.h"
};

static inline int is_static_effect(uint8_t mode) {
    return memchr(static_effect_table, mode, sizeof(static_effect_table)) != NULL;
}

int main(int argc, char *argv[])
{
#define _RGBM_SINGLE_STATIC(sym) \
  printf( "RGBLIGHT_MODE_%s (st) = %d\n", #sym, RGBLIGHT_MODE_ ## sym);
#define _RGBM_SINGLE_DYNAMIC(sym) \
  printf( "RGBLIGHT_MODE_%s = %d\n", #sym, RGBLIGHT_MODE_ ## sym);
#define _RGBM_MULTI_STATIC(sym) \
  printf( "RGBLIGHT_MODE_%s (st) = %d-%d\n", #sym, \
          RGBLIGHT_MODE_ ## sym, \
          RGBLIGHT_MODE_ ## sym ## _end);
#define _RGBM_MULTI_DYNAMIC(sym) \
  printf( "RGBLIGHT_MODE_%s = %d-%d\n", #sym, \
          RGBLIGHT_MODE_ ## sym, \
          RGBLIGHT_MODE_ ## sym ## _end);
#define _RGBM_TMP_STATIC(sym)
#define _RGBM_TMP_DYNAMIC(sym)
  #include "rgblight-macro-test2.h"

    printf("RGBLIGHT_MODES = %d\n", RGBLIGHT_MODES);
    printf("RGBLIGHT_DYNAMIC_last = %d\n", RGBLIGHT_DYNAMIC_last);
    for( int i=0; i < sizeof(static_effect_table); i++ ) {
	printf("static table %d %d\n", i, static_effect_table[i]);
    }

    for( int i = 1; i <= RGBLIGHT_MODES+1; i++ ) {
	printf("%2d is %s\n", i, is_static_effect(i)?"static":"dynamic");
    }

    exit(0);
}
