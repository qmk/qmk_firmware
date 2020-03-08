/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#if defined(__AVR32__)
#include <avr32/io.h>

.section .exception_handlers, "ax", @progbits

// ================= EXCEPTION TABLE ================
.balign  0x200
.global  EVBA_Table
EVBA_Table:

.org  0x000
Exception_Unrecoverable_Exception:
	rjmp $
.org  0x004
Exception_TLB_Multiple_Hit:
	rjmp $
.org  0x008
Exception_Bus_Error_Data_Fetch:
	rjmp $
.org  0x00C
Exception_Bus_Error_Instruction_Fetch:
	rjmp $
.org  0x010
Exception_NMI:
	rjmp $
.org  0x014
Exception_Instruction_Address:
	rjmp $
.org  0x018
Exception_ITLB_Protection:
	rjmp $
.org  0x01C
Exception_OCD_Breakpoint:
	rjmp $
.org  0x020
Exception_Illegal_Opcode:
	rjmp $
.org  0x024
Exception_Unimplemented_Instruction:
	rjmp $
.org  0x028
Exception_Privilege_Violation:
	rjmp $
.org  0x02C
Exception_Floating_Point:
	rjmp $
.org  0x030
Exception_Coprocessor_Absent:
	rjmp $
.org  0x034
Exception_Data_Address_Read:
	rjmp $
.org  0x038
Exception_Data_Address_Write:
	rjmp $
.org  0x03C
Exception_DTLB_Protection_Read:
	rjmp $
.org  0x040
Exception_DTLB_Protection_Write:
	rjmp $
.org  0x044
Exception_DTLB_Modified:
	rjmp $
.org  0x050
Exception_ITLB_Miss:
	rjmp $
.org  0x060
Exception_DTLB_Miss_Read:
	rjmp $
.org  0x070
Exception_DTLB_Miss_Write:
	rjmp $
.org  0x100
Exception_Supervisor_Call:
    rjmp $
// ============== END OF EXCEPTION TABLE =============

// ============= GENERAL INTERRUPT HANDLER ===========
.balign 4
.irp    Level, 0, 1, 2, 3
Exception_INT\Level:
	mov     r12, \Level
	call    INTC_GetInterruptHandler
	mov     pc, r12
.endr
// ========= END OF GENERAL INTERRUPT HANDLER ========

// ====== GENERAL INTERRUPT HANDLER OFFSET TABLE ======
.balign 4
.global Autovector_Table
Autovector_Table:
.irp    Level, 0, 1, 2, 3
	.word ((AVR32_INTC_INT0 + \Level) << AVR32_INTC_IPR_INTLEVEL_OFFSET) | (Exception_INT\Level - EVBA_Table)
.endr
// === END OF GENERAL INTERRUPT HANDLER OFFSET TABLE ===

#endif
