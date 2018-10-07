#include "solid.h"

uint32_t solid_color = 0;

void solid_start(uint32_t color) {
    solid_color = color;
}

void solid_process(void) {
    rgblight_setrgb(
            (solid_color >> 16) & 0xFF,
            (solid_color >> 8) & 0xFF,
            solid_color & 0xFF
    );
}
