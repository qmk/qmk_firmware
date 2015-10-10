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

#else /* defined(STM32F0XX) */
#error Check that the bootloader code works on your platform and add it to bootloader.c!
#endif /* defined(STM32F0XX) */

#elif defined(KL2x) || defined(K20x) /* STM32_BOOTLOADER_ADDRESS */
/* Kinetis */

void bootloader_jump(void) {
	chThdSleepMilliseconds(100);
	__BKPT(0);
}

#else /* neither STM32 nor KINETIS */
void bootloader_jump(void) {}
#endif