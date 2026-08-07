#include "quantum.h"

void bootloader_jump(void) {
    // This board doesn't use the "standard" stm32duino bootloader, and no information is available regarding how to enter bootloader mode. All we can do here is reset.
    NVIC_SystemReset();
}
