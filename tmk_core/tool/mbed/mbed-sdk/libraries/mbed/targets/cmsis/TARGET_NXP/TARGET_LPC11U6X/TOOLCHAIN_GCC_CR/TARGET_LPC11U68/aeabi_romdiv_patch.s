//*****************************************************************************
// aeabi_romdiv_patch.s
//  - Provides "patch" versions of the aeabi integer divide functions to
//    replace the standard ones pulled in from the C library, which vector
//    integer divides onto the rom division functions contained in
//    specific NXP MCUs such as LPC11Uxx and LPC12xx.
//  - Note that this patching will only occur if "__USE_ROMDIVIDE" is
//    defined for the project build for both the compiler and assembler.
//*****************************************************************************
//
// Copyright(C) NXP Semiconductors, 2013
// All rights reserved.
//
// Software that is described herein is for illustrative purposes only
// which provides customers with programming information regarding the
// LPC products.  This software is supplied "AS IS" without any warranties of
// any kind, and NXP Semiconductors and its licensor disclaim any and
// all warranties, express or implied, including all implied warranties of
// merchantability, fitness for a particular purpose and non-infringement of
// intellectual property rights.  NXP Semiconductors assumes no responsibility
// or liability for the use of the software, conveys no license or rights under any
// patent, copyright, mask work right, or any other intellectual property rights in
// or to any products. NXP Semiconductors reserves the right to make changes
// in the software without notification. NXP Semiconductors also makes no
// representation or warranty that such application will be suitable for the
// specified use without further testing or modification.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation is hereby granted, under NXP Semiconductors' and its
// licensor's relevant copyrights in the software, without fee, provided that it
// is used in conjunction with NXP Semiconductors microcontrollers.  This
// copyright, permission, and disclaimer notice must appear in all copies of
// this code.
//*****************************************************************************
#if defined(__USE_ROMDIVIDE)

// Note that the romdivide "divmod" functions are not actually called from
// the below code, as these functions are actually just wrappers to the
// main romdivide "div" functions which push the quotient and remainder onto
// the stack, so as to be compatible with the way that C returns structures.
//
// This is not needed for the aeabi "divmod" functions, as the compiler
// automatically generates code that handles the return values being passed
// back in registers when it generates inline calls to __aeabi_idivmod and
// __aeabi_uidivmod routines.

	.syntax unified
	.text

// ========= __aeabi_idiv &  __aeabi_idivmod =========
	.align 2
	.section .text.__aeabi_idiv

	.global	__aeabi_idiv
	.set __aeabi_idivmod, __aeabi_idiv   // make __aeabi_uidivmod an alias
	.global __aeabi_idivmod
	.global pDivRom_idiv   // pointer to the romdivide 'idiv' functione
    .func
	.thumb_func
	.type	__aeabi_idiv, %function

__aeabi_idiv:
	push	{r4, lr}
	ldr	r3, =pDivRom_idiv
	ldr	r3, [r3, #0]     // Load address of function
	blx	r3               // Call divide function
	pop	{r4, pc}

	.endfunc

// ========  __aeabi_uidiv &  __aeabi_uidivmod ========
	.align 2

	.section .text.__aeabi_uidiv

	.global	__aeabi_uidiv
	.set __aeabi_uidivmod, __aeabi_uidiv  // make __aeabi_uidivmod an alias
	.global __aeabi_uidivmod
	.global pDivRom_uidiv	// pointer to the romdivide 'uidiv' function
    .func
	.thumb_func
	.type	__aeabi_uidiv, %function

__aeabi_uidiv:
	push	{r4, lr}
	ldr	r3, =pDivRom_uidiv
	ldr	r3, [r3, #0]      // Load address of function
	blx	r3               // Call divide function
	pop	{r4, pc}

	.endfunc

#endif // (__USE_ROMDIVIDE)
