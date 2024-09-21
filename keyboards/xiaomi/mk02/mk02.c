#include "quantum.h"

void bootloader_jump(void) {
    uint32_t *magic_address = (void*)0x20000FFC;
    *magic_address = 0x626c6472;

    NVIC_SystemReset();
}
