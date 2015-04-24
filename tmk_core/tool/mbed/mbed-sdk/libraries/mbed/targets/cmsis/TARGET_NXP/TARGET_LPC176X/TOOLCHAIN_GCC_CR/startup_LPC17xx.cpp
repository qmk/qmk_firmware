extern "C" {

#include "LPC17xx.h"

#define WEAK          __attribute__ ((weak))
#define ALIAS(f)      __attribute__ ((weak, alias (#f)))
#define AFTER_VECTORS __attribute__ ((section(".after_vectors")))

extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

extern void __libc_init_array(void);
extern int main(void);
extern void _vStackTop(void);
extern void (* const g_pfnVectors[])(void);

     void ResetISR          (void);
WEAK void NMI_Handler       (void);
WEAK void HardFault_Handler (void);
WEAK void MemManage_Handler (void);
WEAK void BusFault_Handler  (void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler       (void);
WEAK void DebugMon_Handler  (void);
WEAK void PendSV_Handler    (void);
WEAK void SysTick_Handler   (void);
WEAK void IntDefaultHandler (void);

void WDT_IRQHandler        (void) ALIAS(IntDefaultHandler);
void TIMER0_IRQHandler     (void) ALIAS(IntDefaultHandler);
void TIMER1_IRQHandler     (void) ALIAS(IntDefaultHandler);
void TIMER2_IRQHandler     (void) ALIAS(IntDefaultHandler);
void TIMER3_IRQHandler     (void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler      (void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler      (void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler      (void) ALIAS(IntDefaultHandler);
void UART3_IRQHandler      (void) ALIAS(IntDefaultHandler);
void PWM1_IRQHandler       (void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler       (void) ALIAS(IntDefaultHandler);
void I2C1_IRQHandler       (void) ALIAS(IntDefaultHandler);
void I2C2_IRQHandler       (void) ALIAS(IntDefaultHandler);
void SPI_IRQHandler        (void) ALIAS(IntDefaultHandler);
void SSP0_IRQHandler       (void) ALIAS(IntDefaultHandler);
void SSP1_IRQHandler       (void) ALIAS(IntDefaultHandler);
void PLL0_IRQHandler       (void) ALIAS(IntDefaultHandler);
void RTC_IRQHandler        (void) ALIAS(IntDefaultHandler);
void EINT0_IRQHandler      (void) ALIAS(IntDefaultHandler);
void EINT1_IRQHandler      (void) ALIAS(IntDefaultHandler);
void EINT2_IRQHandler      (void) ALIAS(IntDefaultHandler);
void EINT3_IRQHandler      (void) ALIAS(IntDefaultHandler);
void ADC_IRQHandler        (void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler        (void) ALIAS(IntDefaultHandler);
void USB_IRQHandler        (void) ALIAS(IntDefaultHandler);
void CAN_IRQHandler        (void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler        (void) ALIAS(IntDefaultHandler);
void I2S_IRQHandler        (void) ALIAS(IntDefaultHandler);
void ENET_IRQHandler       (void) ALIAS(IntDefaultHandler);
void RIT_IRQHandler        (void) ALIAS(IntDefaultHandler);
void MCPWM_IRQHandler      (void) ALIAS(IntDefaultHandler);
void QEI_IRQHandler        (void) ALIAS(IntDefaultHandler);
void PLL1_IRQHandler       (void) ALIAS(IntDefaultHandler);
void USBActivity_IRQHandler(void) ALIAS(IntDefaultHandler);
void CANActivity_IRQHandler(void) ALIAS(IntDefaultHandler);

__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    &_vStackTop, ResetISR, NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WDT_IRQHandler,
    TIMER0_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    TIMER3_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    UART2_IRQHandler,
    UART3_IRQHandler,
    PWM1_IRQHandler,
    I2C0_IRQHandler,
    I2C1_IRQHandler,
    I2C2_IRQHandler,
    SPI_IRQHandler,
    SSP0_IRQHandler,
    SSP1_IRQHandler,
    PLL0_IRQHandler,
    RTC_IRQHandler,
    EINT0_IRQHandler,
    EINT1_IRQHandler,
    EINT2_IRQHandler,
    EINT3_IRQHandler,
    ADC_IRQHandler,
    BOD_IRQHandler,
    USB_IRQHandler,
    CAN_IRQHandler,
    DMA_IRQHandler,
    I2S_IRQHandler,
    ENET_IRQHandler,
    RIT_IRQHandler,
    MCPWM_IRQHandler,
    QEI_IRQHandler,
    PLL1_IRQHandler,
    USBActivity_IRQHandler,
    CANActivity_IRQHandler,
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
    if (software_init_hook) // give control to the RTOS
        software_init_hook(); // this will also call __libc_init_array
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
