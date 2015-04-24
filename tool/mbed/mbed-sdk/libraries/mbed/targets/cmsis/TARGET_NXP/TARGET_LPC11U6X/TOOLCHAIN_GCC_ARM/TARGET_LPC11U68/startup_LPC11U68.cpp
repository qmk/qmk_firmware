extern "C" {

#include "LPC11U6x.h"

#define WEAK          __attribute__ ((weak))
#define ALIAS(f)      __attribute__ ((weak, alias (#f)))
#define AFTER_VECTORS __attribute__ ((section(".after_vectors")))void ResetISR(void);

extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;


extern void __libc_init_array(void);
extern int main(void);
extern void _vStackTop(void);
extern void (* const g_pfnVectors[])(void);

     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

void PIN_INT0_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIN_INT1_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIN_INT2_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIN_INT3_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIN_INT4_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIN_INT5_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIN_INT6_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIN_INT7_IRQHandler (void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler (void) ALIAS(IntDefaultHandler);
void GINT1_IRQHandler (void) ALIAS(IntDefaultHandler);
void I2C1_IRQHandler (void) ALIAS(IntDefaultHandler);
void USART1_4_IRQHandler (void) ALIAS(IntDefaultHandler);
void USART2_3_IRQHandler (void) ALIAS(IntDefaultHandler);
void SCT0_1_IRQHandler (void) ALIAS(IntDefaultHandler);
void SSP1_IRQHandler (void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER16_0_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER16_1_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER32_0_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER32_1_IRQHandler (void) ALIAS(IntDefaultHandler);
void SSP0_IRQHandler (void) ALIAS(IntDefaultHandler);
void USART0_IRQHandler (void) ALIAS(IntDefaultHandler);
void USB_IRQHandler (void) ALIAS(IntDefaultHandler);
void USB_FIQHandler (void) ALIAS(IntDefaultHandler);
void ADCA_IRQHandler (void) ALIAS(IntDefaultHandler);
void RTC_IRQHandler (void) ALIAS(IntDefaultHandler);
void BOD_WDT_IRQHandler (void) ALIAS(IntDefaultHandler);
void FMC_IRQHandler (void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler (void) ALIAS(IntDefaultHandler);
void ADCB_IRQHandler (void) ALIAS(IntDefaultHandler);
void USBWakeup_IRQHandler (void) ALIAS(IntDefaultHandler);

__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
	// Core Level - CM0
    &_vStackTop,                     // The initial stack pointer
    ResetISR,                        // The reset handler
    NMI_Handler,                     // The NMI handler
    HardFault_Handler,               // The hard fault handler
    0,                               // Reserved
    0,                               // Reserved
    0,                               // Reserved
    0,                               // Reserved
    0,                               // Reserved
    0,                               // Reserved
    0,                               // Reserved
    SVC_Handler,                     // SVCall handler
    0,                               // Reserved
    0,                               // Reserved
    PendSV_Handler,                  // The PendSV handler
    SysTick_Handler,                 // The SysTick handler

    // Chip Level - LPC11U68
    PIN_INT0_IRQHandler,             //  0 - GPIO pin interrupt 0
    PIN_INT1_IRQHandler,             //  1 - GPIO pin interrupt 1
    PIN_INT2_IRQHandler,             //  2 - GPIO pin interrupt 2
    PIN_INT3_IRQHandler,             //  3 - GPIO pin interrupt 3
    PIN_INT4_IRQHandler,             //  4 - GPIO pin interrupt 4
    PIN_INT5_IRQHandler,             //  5 - GPIO pin interrupt 5
    PIN_INT6_IRQHandler,             //  6 - GPIO pin interrupt 6
    PIN_INT7_IRQHandler,             //  7 - GPIO pin interrupt 7
    GINT0_IRQHandler,                //  8 - GPIO GROUP0 interrupt
    GINT1_IRQHandler,                //  9 - GPIO GROUP1 interrupt
    I2C1_IRQHandler,                 // 10 - I2C1
    USART1_4_IRQHandler,             // 11 - combined USART1 & 4 interrupt
    USART2_3_IRQHandler,             // 12 - combined USART2 & 3 interrupt
    SCT0_1_IRQHandler,               // 13 - combined SCT0 and 1 interrupt
    SSP1_IRQHandler,                 // 14 - SPI/SSP1 Interrupt
    I2C0_IRQHandler,                 // 15 - I2C0
    TIMER16_0_IRQHandler,            // 16 - CT16B0 (16-bit Timer 0)
    TIMER16_1_IRQHandler,            // 17 - CT16B1 (16-bit Timer 1)
    TIMER32_0_IRQHandler,            // 18 - CT32B0 (32-bit Timer 0)
    TIMER32_1_IRQHandler,            // 19 - CT32B1 (32-bit Timer 1)
    SSP0_IRQHandler,                 // 20 - SPI/SSP0 Interrupt
    USART0_IRQHandler,               // 21 - USART0
    USB_IRQHandler,                  // 22 - USB IRQ
    USB_FIQHandler,                  // 23 - USB FIQ
    ADCA_IRQHandler,                 // 24 - ADC A(A/D Converter)
    RTC_IRQHandler,                  // 25 - Real Time CLock interrpt
    BOD_WDT_IRQHandler,              // 25 - Combined Brownout/Watchdog interrupt
    FMC_IRQHandler,                  // 27 - IP2111 Flash Memory Controller
    DMA_IRQHandler,                  // 28 - DMA interrupt
    ADCB_IRQHandler,                 // 24 - ADC B (A/D Converter)
    USBWakeup_IRQHandler,            // 30 - USB wake-up interrupt
    0,                               // 31 - Reserved
}; 
/* End Vector */

AFTER_VECTORS void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4) *pulDest++ = *pulSrc++;
}

AFTER_VECTORS void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4) *pulDest++ = 0;
}


/* Reset entry point*/
extern "C" void software_init_hook(void) __attribute__((weak));

AFTER_VECTORS void ResetISR(void) {
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;
    
    SectionTableAddr = &__data_section_table;
    
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }
    
    SystemInit();
    if (software_init_hook) 
        software_init_hook(); 
    else {
        __libc_init_array();
        main();
    }
    while (1) {;}
}

AFTER_VECTORS void NMI_Handler       (void) {}
AFTER_VECTORS void HardFault_Handler (void) {}
AFTER_VECTORS void MemManage_Handler (void) {}
AFTER_VECTORS void BusFault_Handler  (void) {}
AFTER_VECTORS void UsageFault_Handler(void) {}
AFTER_VECTORS void SVC_Handler       (void) {}
AFTER_VECTORS void DebugMon_Handler  (void) {}
AFTER_VECTORS void PendSV_Handler    (void) {}
AFTER_VECTORS void SysTick_Handler   (void) {}
AFTER_VECTORS void IntDefaultHandler (void) {}

int __aeabi_atexit(void *object, void (*destructor)(void *), void *dso_handle) {return 0;}
}

#include <stdlib.h>

void *operator new(size_t size)  {return malloc(size);}
void *operator new[](size_t size){return malloc(size);}

void operator delete(void *p)   {free(p);}
void operator delete[](void *p) {free(p);}
