/* mbed Microcontroller Library - RealMonitor
 * Copyright (c) 2006-2009 ARM Limited. All rights reserved. 
 */
#include "vector_defns.h"

extern void __mbed_dcc_irq(void);

/* Function: __mbed_init_realmonitor
 * Setup the RealMonitor DCC Interrupt Handlers
 */
void __mbed_init_realmonitor(void) __attribute__((weak));
void __mbed_init_realmonitor() {
    // Disable all interrupts
    VICIntEnClr = 0xffffffff;
  
    // Set DCC interrupt vector addresses
    VICVectAddr2 = (unsigned)&__mbed_dcc_irq;
    VICVectAddr3 = (unsigned)&__mbed_dcc_irq;  

    // Initialise RealMonitor
    ((void (*)(void))rm_init_entry)();
}
