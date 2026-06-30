#include "bootloader.h"
#include <ch.h>
#include <hal.h>

__attribute__((weak)) void bootloader_jump(void) {
    /* CH579M ISP mode is usually entered by resetting with a specific pin low,
       or by executing a specific ROM function. For now, a system reset is used. */
    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    NVIC_SystemReset();
}
