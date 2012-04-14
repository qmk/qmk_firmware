/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

; Bootloader API Jump Table
.section .apitable, "ax"

; Trampolines to actual API implementations if the target address is outside the
; range of a rjmp instruction (can happen with large bootloader sections)
.org 0
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
BootloaderAPU_UNUSED:
	ret

; API function jump table
.org (96 - 32)
.global BootloaderAPI_JumpTable
BootloaderAPI_JumpTable:
	rjmp BootloaderAPI_ErasePage_Trampoline
	rjmp BootloaderAPI_WritePage_Trampoline
	rjmp BootloaderAPI_FillWord_Trampoline
	rjmp BootloaderAPI_ReadSignature_Trampoline
	rjmp BootloaderAPI_ReadFuse_Trampoline
	rjmp BootloaderAPI_ReadLock_Trampoline
	rjmp BootloaderAPI_WriteLock_Trampoline
	rjmp BootloaderAPU_UNUSED ; UNUSED ENTRY
	rjmp BootloaderAPU_UNUSED ; UNUSED ENTRY
	rjmp BootloaderAPU_UNUSED ; UNUSED ENTRY
	rjmp BootloaderAPU_UNUSED ; UNUSED ENTRY
	rjmp BootloaderAPU_UNUSED ; UNUSED ENTRY

; Bootloader table signatures and information
.org (96 - 8)
BootloaderAPI_Signatures:
.global BootloaderAPI_Signatures
	.long BOOT_START_ADDR ; Start address of the bootloader
	.word 0xCDC1 ; Signature for the CDC class bootloader, V1
	.word 0xDCFB ; Signature for a LUFA class bootloader
