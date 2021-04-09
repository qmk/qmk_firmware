#include "bootloader.h"

#include <ch.h>
#include <hal.h>
#include "wait.h"

/* This code should be checked whether it runs correctly on platforms */
#define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
#define BOOTLOADER_MAGIC 0xDEADBEEF
#define MAGIC_ADDR (unsigned long *)(SYMVAL(__ram0_end__) - 4)

#ifndef STM32_BOOTLOADER_DUAL_BANK
#    define STM32_BOOTLOADER_DUAL_BANK FALSE
#endif

#if STM32_BOOTLOADER_DUAL_BANK

// Need pin definitions
#    include "config_common.h"

#    ifndef STM32_BOOTLOADER_DUAL_BANK_GPIO
#        error "No STM32_BOOTLOADER_DUAL_BANK_GPIO defined, don't know which pin to toggle"
#    endif

#    ifndef STM32_BOOTLOADER_DUAL_BANK_POLARITY
#        define STM32_BOOTLOADER_DUAL_BANK_POLARITY 0
#    endif

#    ifndef STM32_BOOTLOADER_DUAL_BANK_DELAY
#        define STM32_BOOTLOADER_DUAL_BANK_DELAY 100000
#    endif

extern uint32_t __ram0_end__;

__attribute__((weak)) void bootloader_jump(void) {
    // For STM32 MCUs with dual-bank flash, and we're incapable of jumping to the bootloader. The first valid flash
    // bank is executed unconditionally after a reset, so it doesn't enter DFU unless BOOT0 is high. Instead, we do
    // it with hardware...in this case, we pull a GPIO high/low depending on the configuration, connects 3.3V to
    // BOOT0's RC charging circuit, lets it charge the capacitor, and issue a system reset. See the QMK discord
    // #hardware channel pins for an example circuit.
    palSetPadMode(PAL_PORT(STM32_BOOTLOADER_DUAL_BANK_GPIO), PAL_PAD(STM32_BOOTLOADER_DUAL_BANK_GPIO), PAL_MODE_OUTPUT_PUSHPULL);
#    if STM32_BOOTLOADER_DUAL_BANK_POLARITY
    palSetPad(PAL_PORT(STM32_BOOTLOADER_DUAL_BANK_GPIO), PAL_PAD(STM32_BOOTLOADER_DUAL_BANK_GPIO));
#    else
    palClearPad(PAL_PORT(STM32_BOOTLOADER_DUAL_BANK_GPIO), PAL_PAD(STM32_BOOTLOADER_DUAL_BANK_GPIO));
#    endif

    // Wait for a while for the capacitor to charge
    wait_ms(100);

    // Issue a system reset to get the ROM bootloader to execute, with BOOT0 high
    NVIC_SystemReset();
}

void enter_bootloader_mode_if_requested(void) {}  // not needed at all, but if anybody attempts to invoke it....

#elif defined(STM32_BOOTLOADER_ADDRESS)  // STM32_BOOTLOADER_DUAL_BANK

extern uint32_t __ram0_end__;

__attribute__((weak)) void bootloader_jump(void) {
    *MAGIC_ADDR = BOOTLOADER_MAGIC;  // set magic flag => reset handler will jump into boot loader
    NVIC_SystemReset();
}

void enter_bootloader_mode_if_requested(void) {
    unsigned long *check = MAGIC_ADDR;
    if (*check == BOOTLOADER_MAGIC) {
        *check = 0;
        __set_CONTROL(0);
        __set_MSP(*(__IO uint32_t *)STM32_BOOTLOADER_ADDRESS);
        __enable_irq();

        typedef void (*BootJump_t)(void);
        BootJump_t boot_jump = *(BootJump_t *)(STM32_BOOTLOADER_ADDRESS + 4);
        boot_jump();
        while (1)
            ;
    }
}

#elif defined(KL2x) || defined(K20x)  // STM32_BOOTLOADER_DUAL_BANK // STM32_BOOTLOADER_ADDRESS
/* Kinetis */

#    if defined(BOOTLOADER_KIIBOHD)
/* Kiibohd Bootloader (MCHCK and Infinity KB) */
#        define SCB_AIRCR_VECTKEY_WRITEMAGIC 0x05FA0000
const uint8_t              sys_reset_to_loader_magic[] = "\xff\x00\x7fRESET TO LOADER\x7f\x00\xff";
__attribute__((weak)) void bootloader_jump(void) {
    __builtin_memcpy((void *)VBAT, (const void *)sys_reset_to_loader_magic, sizeof(sys_reset_to_loader_magic));
    // request reset
    SCB->AIRCR = SCB_AIRCR_VECTKEY_WRITEMAGIC | SCB_AIRCR_SYSRESETREQ_Msk;
}

#    else /* defined(BOOTLOADER_KIIBOHD) */
/* Default for Kinetis - expecting an ARM Teensy */
#        include "wait.h"
__attribute__((weak)) void bootloader_jump(void) {
    wait_ms(100);
    __BKPT(0);
}
#    endif /* defined(BOOTLOADER_KIIBOHD) */

#else /* neither STM32 nor KINETIS */
__attribute__((weak)) void bootloader_jump(void) {}
#endif
