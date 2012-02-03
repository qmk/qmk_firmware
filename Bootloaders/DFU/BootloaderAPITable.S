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
.org 0

; API function jump table
.global BootloaderAPI_JumpTable
BootloaderAPI_JumpTable:
	rjmp BootloaderAPI_ErasePage
	rjmp BootloaderAPI_WritePage
	rjmp BootloaderAPI_FillWord
	rjmp BootloaderAPI_ReadSignature
	rjmp BootloaderAPI_ReadFuse
	rjmp BootloaderAPI_ReadLock
	rjmp BootloaderAPI_WriteLock

; Bootloader table signature
.org 30
	.word 0xDCFB
