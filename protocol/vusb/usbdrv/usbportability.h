/* Name: usbportability.h
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Christian Starkjohann
 * Creation Date: 2008-06-17
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: usbportability.h 785 2010-05-30 17:57:07Z cs $
 */

/*
General Description:
This header is intended to contain all (or at least most of) the compiler
and library dependent stuff. The C code is written for avr-gcc and avr-libc.
The API of other development environments is converted to gcc's and avr-libc's
API by means of defines.

This header also contains all system includes since they depend on the
development environment.

Thanks to Oleg Semyonov for his help with the IAR tools port!
*/

#ifndef __usbportability_h_INCLUDED__
#define __usbportability_h_INCLUDED__

/* We check explicitly for IAR and CodeVision. Default is avr-gcc/avr-libc. */

/* ------------------------------------------------------------------------- */
#if defined __IAR_SYSTEMS_ICC__ || defined __IAR_SYSTEMS_ASM__  /* check for IAR */
/* ------------------------------------------------------------------------- */

#ifndef ENABLE_BIT_DEFINITIONS
#   define ENABLE_BIT_DEFINITIONS	1   /* Enable bit definitions */
#endif

/* Include IAR headers */
#include <ioavr.h>
#ifndef __IAR_SYSTEMS_ASM__
#   include <inavr.h>
#endif

#define __attribute__(arg)  /* not supported on IAR */

#ifdef __IAR_SYSTEMS_ASM__
#   define __ASSEMBLER__    /* IAR does not define standard macro for asm */
#endif

#ifdef __HAS_ELPM__
#   define PROGMEM __farflash
#else
#   define PROGMEM __flash
#endif

#define USB_READ_FLASH(addr)    (*(PROGMEM char *)(addr))

/* The following definitions are not needed by the driver, but may be of some
 * help if you port a gcc based project to IAR.
 */
#define cli()       __disable_interrupt()
#define sei()       __enable_interrupt()
#define wdt_reset() __watchdog_reset()
#define _BV(x)      (1 << (x))

/* assembler compatibility macros */
#define nop2    rjmp    $+2 /* jump to next instruction */
#define XL      r26
#define XH      r27
#define YL      r28
#define YH      r29
#define ZL      r30
#define ZH      r31
#define lo8(x)  LOW(x)
#define hi8(x)  (((x)>>8) & 0xff)   /* not HIGH to allow XLINK to make a proper range check */

/* Depending on the device you use, you may get problems with the way usbdrv.h
 * handles the differences between devices. Since IAR does not use #defines
 * for MCU registers, we can't check for the existence of a particular
 * register with an #ifdef. If the autodetection mechanism fails, include
 * definitions for the required USB_INTR_* macros in your usbconfig.h. See
 * usbconfig-prototype.h and usbdrv.h for details.
 */

/* ------------------------------------------------------------------------- */
#elif __CODEVISIONAVR__ /* check for CodeVision AVR */
/* ------------------------------------------------------------------------- */
/* This port is not working (yet) */

/* #define F_CPU   _MCU_CLOCK_FREQUENCY_    seems to be defined automatically */

#include <io.h>
#include <delay.h>

#define __attribute__(arg)  /* not supported on IAR */

#define PROGMEM                 __flash
#define USB_READ_FLASH(addr)    (*(PROGMEM char *)(addr))

#ifndef __ASSEMBLER__
static inline void  cli(void)
{
    #asm("cli");
}
static inline void  sei(void)
{
    #asm("sei");
}
#endif
#define _delay_ms(t)    delay_ms(t)
#define _BV(x)          (1 << (x))
#define USB_CFG_USE_SWITCH_STATEMENT 1  /* macro for if() cascase fails for unknown reason */

#define macro   .macro
#define endm    .endmacro
#define nop2    rjmp    .+0 /* jump to next instruction */

/* ------------------------------------------------------------------------- */
#else   /* default development environment is avr-gcc/avr-libc */
/* ------------------------------------------------------------------------- */

#include <avr/io.h>
#ifdef __ASSEMBLER__
#   define _VECTOR(N)   __vector_ ## N   /* io.h does not define this for asm */
#else
#   include <avr/pgmspace.h>
#endif

#if USB_CFG_DRIVER_FLASH_PAGE
#   define USB_READ_FLASH(addr)    pgm_read_byte_far(((long)USB_CFG_DRIVER_FLASH_PAGE << 16) | (long)(addr))
#else
#   define USB_READ_FLASH(addr)    pgm_read_byte(addr)
#endif

#define macro   .macro
#define endm    .endm
#define nop2    rjmp    .+0 /* jump to next instruction */

#endif  /* development environment */

/* for conveniecne, ensure that PRG_RDB exists */
#ifndef PRG_RDB
#   define PRG_RDB(addr)    USB_READ_FLASH(addr)
#endif
#endif  /* __usbportability_h_INCLUDED__ */
