//
// calculate rgblight_effect_breath_table[] values
//
// this is host program for quantum/rgblight.c:void rgblight_effect_breathing();
//
#include <stdio.h>
#include <math.h>
#include <stdint.h>

/// custumize part /////////////////////////////////////////////
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
#define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#define TABLE_SIZE                     128   // 64 or 128 or 256
////////////////////////////////////////////////////////////////

int main(void) {
    int pos, step;
    int table[256];
    for (pos = 0; pos < 256; pos ++ ) {
        table[pos] = (uint8_t)(
              (exp(sin((pos/255.0)*M_PI))- RGBLIGHT_EFFECT_BREATHE_CENTER/M_E)
              * (RGBLIGHT_EFFECT_BREATHE_MAX/(M_E-1/M_E))
              );
    }
    printf("#ifdef RGBLIGHT_EFFECT_BREATH_TABLE\n");
    printf("__attribute__ ((weak))\n");
    printf("const uint8_t rgblight_effect_breath_table[] PROGMEM = {\n");
    printf("  /* %d byte table */\n", TABLE_SIZE);
#if TABLE_SIZE == 256
    step = 1;
#endif
#if TABLE_SIZE == 128
    step = 2;
#endif
#if TABLE_SIZE == 64
    step = 4;
#endif
    for (pos = 0; pos < 256; pos += step ) {
        printf("  0x%x%s", table[pos], pos==255?"":"," );
        if ((pos+step) % 8 == 0)
            printf("\n");
    }
    printf("};\n");
    printf("\nstatic const table_scale = 256/sizeof(rgblight_effect_breath_table);\n");
    printf("#endif\n");
    return 0;
}
