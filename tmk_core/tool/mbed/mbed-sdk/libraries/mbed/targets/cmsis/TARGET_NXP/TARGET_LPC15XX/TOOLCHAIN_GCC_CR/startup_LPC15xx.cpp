extern "C" {

#include "LPC15xx.h"

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

	 void ResetISR          (void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);


void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler(void) ALIAS(IntDefaultHandler);
void FMC_IRQHandler(void) ALIAS(IntDefaultHandler);
void EEPROM_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_IRQHandler(void) ALIAS(IntDefaultHandler);
void RIT_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void MRT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_FIQHandler(void) ALIAS(IntDefaultHandler);
void USBWakeup_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0A_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0B_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_OVR_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1A_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1B_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_OVR_IRQHandler(void) ALIAS(IntDefaultHandler);
void DAC_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP0_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP1_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP2_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP3_IRQHandler(void) ALIAS(IntDefaultHandler);
void QEI_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_ALARM_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_WAKE_IRQHandler(void) ALIAS(IntDefaultHandler);


__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
	// Core Level - CM3
	&_vStackTop,                       // The initial stack pointer
	ResetISR,                          // The reset handler
	NMI_Handler,                       // The NMI handler
	HardFault_Handler,                 // The hard fault handler
	MemManage_Handler,                 // The MPU fault handler
	BusFault_Handler,                  // The bus fault handler
	UsageFault_Handler,                // The usage fault handler
	0,                                 // Reserved
	0,                                 // Reserved
	0,                                 // Reserved
	0,                                 // Reserved
	SVC_Handler,                       // SVCall handler
	DebugMon_Handler,                  // Debug monitor handler
	0,                                 // Reserved
	PendSV_Handler,                    // The PendSV handler
	SysTick_Handler,                   // The SysTick handler

    // Chip Level - LPC15xx
    WDT_IRQHandler,                    //  0 - Windowed watchdog timer
    BOD_IRQHandler,                    //  1 - BOD
    FMC_IRQHandler,                    //  2 - Flash controller
    EEPROM_IRQHandler,                 //  3 - EEPROM controller
    DMA_IRQHandler,                    //  4 - DMA
    GINT0_IRQHandler,                  //  5 - GINT0
    GINT1_IRQHandler,                  //  6 - GINT1
    PIN_INT0_IRQHandler,               //  7 - PIO INT0
    PIN_INT1_IRQHandler,               //  8 - PIO INT1
    PIN_INT2_IRQHandler,               //  9 - PIO INT2
    PIN_INT3_IRQHandler,               // 10 - PIO INT3
    PIN_INT4_IRQHandler,               // 11 - PIO INT4
    PIN_INT5_IRQHandler,               // 12 - PIO INT5
    PIN_INT6_IRQHandler,               // 13 - PIO INT6
    PIN_INT7_IRQHandler,               // 14 - PIO INT7
    RIT_IRQHandler,                    // 15 - RIT
    SCT0_IRQHandler,                   // 16 - State configurable timer
    SCT1_IRQHandler,                   // 17 - State configurable timer
    SCT2_IRQHandler,                   // 18 - State configurable timer
    SCT3_IRQHandler,                   // 19 - State configurable timer
    MRT_IRQHandler,                    // 20 - Multi-Rate Timer
    UART0_IRQHandler,                  // 21 - UART0
    UART1_IRQHandler,                  // 22 - UART1
    UART2_IRQHandler,                  // 23 - UART2
    I2C0_IRQHandler,                   // 24 - I2C0 controller
    SPI0_IRQHandler,                   // 25 - SPI0 controller
    SPI1_IRQHandler,                   // 26 - SPI1 controller
    CAN_IRQHandler,                    // 27 - C_CAN0
    USB_IRQHandler,                    // 28 - USB IRQ
    USB_FIQHandler,                    // 29 - USB FIQ
    USBWakeup_IRQHandler,              // 30 - USB wake-up
    ADC0A_IRQHandler,            	   // 31 - ADC0 sequence A completion
    ADC0B_IRQHandler,              	   // 32 - ADC0 sequence B completion
    ADC0_THCMP_IRQHandler,             // 33 - ADC0 threshold compare
    ADC0_OVR_IRQHandler,               // 34 - ADC0 overrun
    ADC1A_IRQHandler,                  // 35 - ADC1 sequence A completion
    ADC1B_IRQHandler,                  // 36 - ADC1 sequence B completion
    ADC1_THCMP_IRQHandler,             // 37 - ADC1 threshold compare
    ADC1_OVR_IRQHandler,               // 38 - ADC1 overrun
    DAC_IRQHandler,                    // 39 - DAC
    ACMP0_IRQHandler,                  // 40 - Analog Comparator 0
    ACMP1_IRQHandler,                  // 41 - Analog Comparator 1
    ACMP2_IRQHandler,                  // 42 - Analog Comparator 2
    ACMP3_IRQHandler,                  // 43 - Analog Comparator 3
    QEI_IRQHandler,                    // 44 - QEI
    RTC_ALARM_IRQHandler,              // 45 - RTC alarm
    RTC_WAKE_IRQHandler,               // 46 - RTC wake-up

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
