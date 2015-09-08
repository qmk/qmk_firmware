#include "bootloader.h"

#include "ch.h"

#ifdef BOOTLOADER_ADDRESS
#define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
extern uint32_t __ram0_end__;

void bootloader_jump(void) {
  *((unsigned long *)(SYMVAL(__ram0_end__) - 4)) = 0xDEADBEEF; // set magic flag => reset handler will jump into boot loader
   NVIC_SystemReset();
}
#else /* BOOTLOADER_ADDRESS */
void bootloader_jump(void) {}
#endif /* BOOTLOADER_ADDRESS */

