#include "m65.h"



#ifdef KEYBOARD_m65_rev1
void keyboard_pre_init_kb(void){
    // Workaround for reversible pcb/mcu
    palSetLineMode(C13, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(B9, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(B8, PAL_MODE_OUTPUT_OPENDRAIN);

    keyboard_pre_init_user();
}

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP | AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
}
#endif
