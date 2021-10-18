 /* Copyright 2021 OpenAnnePro community 
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 
  
#include <string.h>
#include "hal.h"

#define bkpt() __asm volatile("BKPT #0\n")
OSAL_IRQ_HANDLER(HardFault_Handler) {
    // Copy to local variables (not pointers) to allow GDB "i loc" to directly show the info
    struct port_extctx     ctx;
    volatile unsigned long _CFSR;
    volatile unsigned long _HFSR;
    volatile unsigned long _DFSR;
    volatile unsigned long _AFSR;
    volatile unsigned long _BFAR;
    volatile unsigned long _MMAR;
    // Get thread context. Contains main registers including PC and LR
    memcpy(&ctx, (void *)__get_PSP(), sizeof(struct port_extctx));
    (void)ctx;

    // Configurable Fault Status Register
    // Consists of MMSR, BFSR and UFSR
    _CFSR = (*((volatile unsigned long *)(0xE000ED28)));
    (void)(_CFSR);

    // Hard Fault Status Register
    _HFSR = (*((volatile unsigned long *)(0xE000ED2C)));
    (void)(_HFSR);

    // Debug Fault Status Register
    _DFSR = (*((volatile unsigned long *)(0xE000ED30)));
    (void)(_DFSR);

    // Auxiliary Fault Status Register
    _AFSR = (*((volatile unsigned long *)(0xE000ED3C)));
    (void)(_AFSR);

    // Read the Fault Address Registers. These may not contain valid values.
    // Check BFARVALID/MMARVALID to see if they are valid values
    // MemManage Fault Address Register
    _MMAR = (*((volatile unsigned long *)(0xE000ED34)));
    (void)(_MMAR);
    // Bus Fault Address Register
    _BFAR = (*((volatile unsigned long *)(0xE000ED38)));
    (void)(_BFAR);
    // Cause debugger to stop. Ignored if no debugger is attached
    bkpt();
    NVIC_SystemReset();  // If no debugger connected, just reset the board
}
