extern "C" {

#include "LPC11Uxx.h"

#define WEAK          __attribute__ ((weak))
#define ALIAS(f)      __attribute__ ((weak, alias (#f)))
#define AFTER_VECTORS __attribute__ ((section(".after_vectors")))

     void ResetISR            (void);
WEAK void NMI_Handler         (void);
WEAK void HardFault_Handler   (void);
WEAK void SVC_Handler         (void);
WEAK void PendSV_Handler      (void);
WEAK void SysTick_Handler     (void);
WEAK void IntDefaultHandler   (void);
     void FLEX_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
     void FLEX_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
     void FLEX_INT2_IRQHandler(void) ALIAS(IntDefaultHandler);
     void FLEX_INT3_IRQHandler(void) ALIAS(IntDefaultHandler);
     void FLEX_INT4_IRQHandler(void) ALIAS(IntDefaultHandler);
     void FLEX_INT5_IRQHandler(void) ALIAS(IntDefaultHandler);
     void FLEX_INT6_IRQHandler(void) ALIAS(IntDefaultHandler);
     void FLEX_INT7_IRQHandler(void) ALIAS(IntDefaultHandler);
     void GINT0_IRQHandler    (void) ALIAS(IntDefaultHandler);
     void GINT1_IRQHandler    (void) ALIAS(IntDefaultHandler);
     void SSP1_IRQHandler     (void) ALIAS(IntDefaultHandler);
     void I2C_IRQHandler      (void) ALIAS(IntDefaultHandler);
     void TIMER16_0_IRQHandler(void) ALIAS(IntDefaultHandler);
     void TIMER16_1_IRQHandler(void) ALIAS(IntDefaultHandler);
     void TIMER32_0_IRQHandler(void) ALIAS(IntDefaultHandler);
     void TIMER32_1_IRQHandler(void) ALIAS(IntDefaultHandler);
     void SSP0_IRQHandler     (void) ALIAS(IntDefaultHandler);
     void UART_IRQHandler     (void) ALIAS(IntDefaultHandler);
     void USB_IRQHandler      (void) ALIAS(IntDefaultHandler);
     void USB_FIQHandler      (void) ALIAS(IntDefaultHandler);
     void ADC_IRQHandler      (void) ALIAS(IntDefaultHandler);
     void WDT_IRQHandler      (void) ALIAS(IntDefaultHandler);
     void BOD_IRQHandler      (void) ALIAS(IntDefaultHandler);
     void FMC_IRQHandler      (void) ALIAS(IntDefaultHandler);
     void USBWakeup_IRQHandler(void) ALIAS(IntDefaultHandler);

extern void __libc_init_array(void);
extern int main(void);
extern void _vStackTop(void);

extern void (* const g_pfnVectors[])(void);
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    &_vStackTop,
    ResetISR,
    NMI_Handler,
    HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,
    FLEX_INT0_IRQHandler,
    FLEX_INT1_IRQHandler,
    FLEX_INT2_IRQHandler,
    FLEX_INT3_IRQHandler,
    FLEX_INT4_IRQHandler,
    FLEX_INT5_IRQHandler,
    FLEX_INT6_IRQHandler,
    FLEX_INT7_IRQHandler,
    GINT0_IRQHandler,
    GINT1_IRQHandler,
    0,
    0,
    0,
    0,
    SSP1_IRQHandler,
    I2C_IRQHandler,
    TIMER16_0_IRQHandler,
    TIMER16_1_IRQHandler,
    TIMER32_0_IRQHandler,
    TIMER32_1_IRQHandler,
    SSP0_IRQHandler,
    UART_IRQHandler,
    USB_IRQHandler,
    USB_FIQHandler,
    ADC_IRQHandler,
    WDT_IRQHandler,
    BOD_IRQHandler,
    FMC_IRQHandler,
    0,
    0,
    USBWakeup_IRQHandler,
    0,
};

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

extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table_end;

extern "C" void software_init_hook(void) __attribute__((weak));

AFTER_VECTORS void ResetISR(void) {
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;
    
    // Data Init
    SectionTableAddr = &__data_section_table;
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    
    // BSS Init
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }
    
    SystemInit();
    if (software_init_hook) // give control to the RTOS
        software_init_hook(); // this will also call __libc_init_array
    else {
        __libc_init_array();
        main();
    }
    while (1) {;}
}

AFTER_VECTORS void NMI_Handler      (void) {while(1){}}
AFTER_VECTORS void HardFault_Handler(void) {while(1){}}
AFTER_VECTORS void SVC_Handler      (void) {while(1){}}
AFTER_VECTORS void PendSV_Handler   (void) {while(1){}}
AFTER_VECTORS void SysTick_Handler  (void) {while(1){}}
AFTER_VECTORS void IntDefaultHandler(void) {while(1){}}

#include <stdlib.h>

void *operator new  (size_t size) {return malloc(size);}
void *operator new[](size_t size) {return malloc(size);}

void operator delete  (void *p) {free(p);}
void operator delete[](void *p) {free(p);}

int __aeabi_atexit(void *object, void (*destructor)(void *), void *dso_handle) {
    return 0;
}

}
