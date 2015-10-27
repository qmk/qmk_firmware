/* mbed Microcontroller Library - Vectors 
 * Copyright (c) 2006-2009 ARM Limited. All rights reserved. 
 */

#ifndef MBED_VECTOR_DEFNS_H
#define MBED_VECTOR_DEFNS_H
 
// Assember Macros 
#ifdef __ARMCC_VERSION
#define EXPORT(x) EXPORT x
#define WEAK_EXPORT(x) EXPORT x [WEAK]
#define IMPORT(x) IMPORT x
#define LABEL(x) x
#else        
#define EXPORT(x) .global x
#define WEAK_EXPORT(x) .weak x
#define IMPORT(x) .global x
#define LABEL(x) x:        
#endif

// RealMonitor
// Requires RAM (0x40000040-0x4000011F) to be allocated by the linker

// RealMonitor entry points
#define rm_init_entry 0x7fffff91
#define rm_undef_handler 0x7fffffa0
#define rm_prefetchabort_handler 0x7fffffb0
#define rm_dataabort_handler 0x7fffffc0
#define rm_irqhandler2 0x7fffffe0
//#define rm_RunningToStopped 0x7ffff808 // ARM - MBED64
#define rm_RunningToStopped 0x7ffff820 // ARM - PHAT40

// Unofficial RealMonitor entry points and variables
#define RM_MSG_SWI 0x00940000 
#define StateP 0x40000040 

// VIC register addresses
#define VIC_Base 0xfffff000
#define VICAddress_Offset 0xf00
#define VICVectAddr0_Offset 0x100
#define VICVectAddr2_Offset 0x108
#define VICVectAddr3_Offset 0x10c
#define VICVectAddr31_Offset 0x17c
#define VICIntEnClr_Offset 0x014
#define VICIntEnClr    (*(volatile unsigned long *)(VIC_Base + 0x014))
#define VICVectAddr2   (*(volatile unsigned long *)(VIC_Base + 0x108))
#define VICVectAddr3   (*(volatile unsigned long *)(VIC_Base + 0x10C))

// ARM Mode bits and Interrupt flags in PSRs
#define Mode_USR 0x10
#define Mode_FIQ 0x11
#define Mode_IRQ 0x12
#define Mode_SVC 0x13
#define Mode_ABT 0x17
#define Mode_UND 0x1B
#define Mode_SYS 0x1F
#define I_Bit 0x80    // when I bit is set, IRQ is disabled
#define F_Bit 0x40    // when F bit is set, FIQ is disabled

// MCU RAM
#define LPC2368_RAM_ADDRESS 0x40000000	// RAM Base
#define LPC2368_RAM_SIZE 0x8000		// 32KB 

// ISR Stack Allocation
#define UND_stack_size  0x00000040
#define SVC_stack_size  0x00000040
#define ABT_stack_size  0x00000040
#define FIQ_stack_size  0x00000000
#define IRQ_stack_size  0x00000040

#define ISR_stack_size  (UND_stack_size + SVC_stack_size + ABT_stack_size + FIQ_stack_size + IRQ_stack_size)

// Full Descending Stack, so top-most stack points to just above the top of RAM
#define LPC2368_STACK_TOP (LPC2368_RAM_ADDRESS + LPC2368_RAM_SIZE)
#define USR_STACK_TOP	  (LPC2368_STACK_TOP - ISR_stack_size)

#endif
