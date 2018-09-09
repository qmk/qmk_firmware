#include "bootloader.h"

#include "ch.h"
#include "hal.h"

#ifdef STM32_BOOTLOADER_ADDRESS
/* STM32 */

/* This code should be checked whether it runs correctly on platforms */
#define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
extern uint32_t __ram0_end__;
#define BOOTLOADER_MAGIC 0xDEADBEEF
#define MAGIC_ADDR (unsigned long*)(SYMVAL(__ram0_end__) - 4)


/** \brief Jump to the bootloader
 *
 * FIXME: needs doc
 */
void bootloader_jump(void) {
  *MAGIC_ADDR = BOOTLOADER_MAGIC; // set magic flag => reset handler will jump into boot loader
   NVIC_SystemReset();
}

/** \brief Enter bootloader mode if requested
 *
 * FIXME: needs doc
 */
void enter_bootloader_mode_if_requested(void)  {
  unsigned long* check = MAGIC_ADDR;
  if(*check == BOOTLOADER_MAGIC)  {
    *check = 0;
    __set_CONTROL(0);
    __set_MSP(*(__IO uint32_t*)STM32_BOOTLOADER_ADDRESS);
    __enable_irq();

    typedef void (*BootJump_t)(void);
    BootJump_t boot_jump = *(BootJump_t*)(STM32_BOOTLOADER_ADDRESS + 4);
    boot_jump();
    while(1);
  }
 }

#elif defined(KL2x) || defined(K20x) /* STM32_BOOTLOADER_ADDRESS */
/* Kinetis */

#if defined(KIIBOHD_BOOTLOADER)
/* Kiibohd Bootloader (MCHCK and Infinity KB) */
#define SCB_AIRCR_VECTKEY_WRITEMAGIC 0x05FA0000
const uint8_t sys_reset_to_loader_magic[] = "\xff\x00\x7fRESET TO LOADER\x7f\x00\xff";
void bootloader_jump(void) {
  __builtin_memcpy((void *)VBAT, (const void *)sys_reset_to_loader_magic, sizeof(sys_reset_to_loader_magic));
  // request reset
  SCB->AIRCR = SCB_AIRCR_VECTKEY_WRITEMAGIC | SCB_AIRCR_SYSRESETREQ_Msk;
}

#else /* defined(KIIBOHD_BOOTLOADER) */
/* Default for Kinetis - expecting an ARM Teensy */
#include "wait.h"
void bootloader_jump(void) {
	wait_ms(100);
	__BKPT(0);
}
#endif /* defined(KIIBOHD_BOOTLOADER) */

#else /* neither STM32 nor KINETIS */
__attribute__((weak))
void bootloader_jump(void) {}
#endif
