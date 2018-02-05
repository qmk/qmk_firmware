/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

; Trampolines to actual API implementations if the target address is outside the
; range of a rjmp instruction (can happen with large bootloader sections)
.section .apitable_trampolines, "ax"
.global BootloaderAPI_Trampolines
BootloaderAPI_Trampolines:

	BootloaderAPI_ErasePage_Trampoline:
		jmp BootloaderAPI_ErasePage
	BootloaderAPI_WritePage_Trampoline:
		jmp BootloaderAPI_WritePage
	BootloaderAPI_FillWord_Trampoline:
		jmp BootloaderAPI_FillWord
	BootloaderAPI_ReadSignature_Trampoline:
		jmp BootloaderAPI_ReadSignature
	BootloaderAPI_ReadFuse_Trampoline:
		jmp BootloaderAPI_ReadFuse
	BootloaderAPI_ReadLock_Trampoline:
		jmp BootloaderAPI_ReadLock
	BootloaderAPI_WriteLock_Trampoline:
		jmp BootloaderAPI_WriteLock
	BootloaderAPI_UNUSED1:
		ret
	BootloaderAPI_UNUSED2:
		ret
	BootloaderAPI_UNUSED3:
		ret
	BootloaderAPI_UNUSED4:
		ret
	BootloaderAPI_UNUSED5:
		ret



; API function jump table
.section .apitable_jumptable, "ax"
.global BootloaderAPI_JumpTable
BootloaderAPI_JumpTable:

	rjmp BootloaderAPI_ErasePage_Trampoline
	rjmp BootloaderAPI_WritePage_Trampoline
	rjmp BootloaderAPI_FillWord_Trampoline
	rjmp BootloaderAPI_ReadSignature_Trampoline
	rjmp BootloaderAPI_ReadFuse_Trampoline
	rjmp BootloaderAPI_ReadLock_Trampoline
	rjmp BootloaderAPI_WriteLock_Trampoline
	rjmp BootloaderAPI_UNUSED1 ; UNUSED ENTRY 1
	rjmp BootloaderAPI_UNUSED2 ; UNUSED ENTRY 2
	rjmp BootloaderAPI_UNUSED3 ; UNUSED ENTRY 3
	rjmp BootloaderAPI_UNUSED4 ; UNUSED ENTRY 4
	rjmp BootloaderAPI_UNUSED5 ; UNUSED ENTRY 5



; Bootloader table signatures and information
.section .apitable_signatures, "ax"
.global BootloaderAPI_Signatures
BootloaderAPI_Signatures:

	.long BOOT_START_ADDR ; Start address of the bootloader
	.word 0xDF10 ; Signature for the DFU class bootloader, V1
	.word 0xDCFB ; Signature for a LUFA class bootloader
