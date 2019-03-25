//
// calculate rgblight_effect_breathe_table[] values
//
// this is host program for quantum/rgblight.c:void rgblight_effect_breathing();
//
// example:
//  $ edit util/rgblight_breathing_table_calc.c
//  $ cc -o util/rgblight_breathing_table_calc util/rgblight_breathing_table_calc.c
//  $ ./util/rgblight_breathing_table_calc > keyboards/KEYBOARD_NAME/keymaps/KEYMAP_NAME/rgblight_breathe_table.h
//
#include <stdio.h>
#include <math.h>
#include <stdint.h>

/// custumize part /////////////////////////////////////////////
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
#define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#define TABLE_SIZE                     256   // 64 or 128 or 256
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
    printf("#ifndef RGBLIGHT_EFFECT_BREATHE_TABLE\n");
    printf("#define RGBLIGHT_EFFECT_BREATHE_TABLE\n\n");
    printf("const uint8_t rgblight_effect_breathe_table[] PROGMEM = {\n");
    printf("  /* #define RGBLIGHT_EFFECT_BREATHE_CENTER   %.2f */\n", RGBLIGHT_EFFECT_BREATHE_CENTER);
    printf("  /* #define RGBLIGHT_EFFECT_BREATHE_MAX      %d */\n", RGBLIGHT_EFFECT_BREATHE_MAX);
    printf("  /* %d byte table */\n", TABLE_SIZE);
#if TABLE_SIZE == 256
    step = 1;
#elif TABLE_SIZE == 128
    step = 2;
#elif TABLE_SIZE == 64
    step = 4;
#else
    #error invalid TABLE_SIZE
#endif
    for (pos = 0; pos < 256; pos += step ) {
        printf("  0x%x%s", table[pos], pos==255?"":"," );
        if ((pos+step) % 8 == 0)
            printf("\n");
    }
    printf("};\n");
    printf("\nstatic const int table_scale = 256/sizeof(rgblight_effect_breathe_table);\n");
    printf("\n#endif /* RGBLIGHT_EFFECT_BREATHE_TABLE */\n");
    return 0;
}
