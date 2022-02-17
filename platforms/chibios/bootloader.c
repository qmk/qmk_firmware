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

#ifdef BOOTLOADER_TINYUF2

#    define DBL_TAP_MAGIC 0xf01669ef  // From tinyuf2's board_api.h

// defined by linker script
extern uint32_t _board_dfu_dbl_tap[];
#    define DBL_TAP_REG _board_dfu_dbl_tap[0]

void bootloader_jump(void) {
    DBL_TAP_REG = DBL_TAP_MAGIC;
    NVIC_SystemReset();
}

void enter_bootloader_mode_if_requested(void) { /* not needed, no two-stage reset */
}

#elif STM32_BOOTLOADER_DUAL_BANK

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

#elif defined(GD32VF103)

#    define DBGMCU_KEY_UNLOCK 0x4B5A6978
#    define DBGMCU_CMD_RESET 0x1

__IO uint32_t *DBGMCU_KEY = (uint32_t *)DBGMCU_BASE + 0x0CU;
__IO uint32_t *DBGMCU_CMD = (uint32_t *)DBGMCU_BASE + 0x08U;

__attribute__((weak)) void bootloader_jump(void) {
    /* The MTIMER unit of the GD32VF103 doesn't have the MSFRST
     * register to generate a software reset request.
     * BUT instead two undocumented registers in the debug peripheral
     * that allow issueing a software reset. WHO would need the MSFRST
     * register anyway? Source:
     * https://github.com/esmil/gd32vf103inator/blob/master/include/gd32vf103/dbg.h */
    *DBGMCU_KEY = DBGMCU_KEY_UNLOCK;
    *DBGMCU_CMD = DBGMCU_CMD_RESET;
}

void enter_bootloader_mode_if_requested(void) { /* Jumping to bootloader is not possible from user code. */
}

#elif defined(KL2x) || defined(K20x) || defined(MK66F18) || defined(MIMXRT1062)  // STM32_BOOTLOADER_DUAL_BANK // STM32_BOOTLOADER_ADDRESS
/* Kinetis */

#    if defined(BOOTLOADER_KIIBOHD)
/* Kiibohd Bootloader (MCHCK and Infinity KB) */
#        define SCB_AIRCR_VECTKEY_WRITEMAGIC 0x05FA0000
const uint8_t              sys_reset_to_loader_magic[] = "\xff\x00\x7fRESET TO LOADER\x7f\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
__attribute__((weak)) void bootloader_jump(void) {
    void *volatile vbat = (void *)VBAT;
    __builtin_memcpy(vbat, (const void *)sys_reset_to_loader_magic, sizeof(sys_reset_to_loader_magic));
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
