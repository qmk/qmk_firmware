//
// this is host program for quantum/rgblight.c:void rgblight_effect_breathing();
//
#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85
#define RGBLIGHT_EFFECT_BREATHE_MAX 255   // 0-255

int main(void) {
    int pos;
    printf("#ifdef RGBLIGHT_EFFECT_BREATHE_USE_TABLE\n");
    printf("__attribute__ ((weak))\n");
    printf("const uint8_t rgblight_effect_breathe_table[] PROGMEM = {\n");
    for (pos = 0; pos < 256; pos ++ ) {
        printf("  0x%x%s",(uint8_t)( (exp(sin((pos/255.0)*M_PI)) - RGBLIGHT_EFFECT_BREATHE_CENTER/M_E)*(RGBLIGHT_EFFECT_BREATHE_MAX/(M_E-1/M_E))),pos==255?"":"," );
        if ((pos+1) % 8 == 0)
            printf("\n");
    }
    printf("};\n");
    printf("#endif\n");

    return 0;
}
