#include "bootloader.h"

#include "ch.h"
#include "hal.h"

#ifdef STM32_BOOTLOADER_ADDRESS
/* STM32 */

#if defined(STM32F0XX)
/* This code should be checked whether it runs correctly on platforms */
#define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
extern uint32_t __ram0_end__;

void bootloader_jump(void) {
  *((unsigned long *)(SYMVAL(__ram0_end__) - 4)) = 0xDEADBEEF; // set magic flag => reset handler will jump into boot loader
   NVIC_SystemReset();
}

#elif defined(STM32F3XX)
/* This code should be checked whether it runs correctly on platforms. 
 * It was added for clueboard60 BUT HAS NOT BEEN TESTED.
 * FIXME - Test this
 */
#define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
extern uint32_t __ram0_end__;

void bootloader_jump(void) {
  *((unsigned long *)(SYMVAL(__ram0_end__) - 4)) = 0xDEADBEEF; // set magic flag => reset handler will jump into boot loader
   NVIC_SystemReset();
}

#else /* defined(STM32F0XX) */
#error Check that the bootloader code works on your platform and add it to bootloader.c!
#endif /* defined(STM32F0XX) */

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
