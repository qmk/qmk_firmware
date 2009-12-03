/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

/** \file
 *
 *  Header file for PDIProtocol.c.
 */

#ifndef _PDI_PROTOCOL_
#define _PDI_PROTOCOL_

	/* Includes: */
		#include <avr/io.h>
		#include <stdio.h>
	
		#include "V2Protocol.h"
		#include "PDITarget.h"

	/* Preprocessor Checks: */
		#if BOARD == BOARD_XPLAIN
			#undef  ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_PDI_PROTOCOL)
				#define ENABLE_PDI_PROTOCOL
			#endif
		#endif

	/* Macros: */
		#define XPRG_CMD_ENTER_PROGMODE             0x01
		#define XPRG_CMD_LEAVE_PROGMODE             0x02
		#define XPRG_CMD_ERASE                      0x03
		#define XPRG_CMD_WRITE_MEM                  0x04
		#define XPRG_CMD_READ_MEM                   0x05
		#define XPRG_CMD_CRC                        0x06
		#define XPRG_CMD_SET_PARAM                  0x07

		#define XPRG_MEM_TYPE_APPL                  1
		#define XPRG_MEM_TYPE_BOOT                  2
		#define XPRG_MEM_TYPE_EEPROM                3
		#define XPRG_MEM_TYPE_FUSE                  4
		#define XPRG_MEM_TYPE_LOCKBITS              5
		#define XPRG_MEM_TYPE_USERSIG               6
		#define XPRG_MEM_TYPE_FACTORY_CALIBRATION   7

		#define XPRG_ERASE_CHIP                     1
		#define XPRG_ERASE_APP                      2
		#define XPRG_ERASE_BOOT                     3
		#define XPRG_ERASE_EEPROM                   4
		#define XPRG_ERASE_APP_PAGE                 5
		#define XPRG_ERASE_BOOT_PAGE                6
		#define XPRG_ERASE_EEPROM_PAGE              7
		#define XPRG_ERASE_USERSIG                  8

		#define XPRG_MEM_WRITE_ERASE                0
		#define XPRG_MEM_WRITE_WRITE                1

		#define XPRG_CRC_APP                        1
		#define XPRG_CRC_BOOT                       2
		#define XPRG_CRC_FLASH                      3

		#define XPRG_ERR_OK                         0
		#define XPRG_ERR_FAILED                     1
		#define XPRG_ERR_COLLISION                  2
		#define XPRG_ERR_TIMEOUT                    3

		#define XPRG_PARAM_NVMBASE                  0x01
		#define XPRG_PARAM_EEPPAGESIZE              0x02
		
	/* Function Prototypes: */
		void PDIProtocol_XPROG_SetMode(void);
		void PDIProtocol_XPROG_Command(void);
		
		#if defined(INCLUDE_FROM_PDIPROTOCOL_C)
			static void PDIProtocol_EnterXPROGMode(void);
			static void PDIProtocol_LeaveXPROGMode(void);
			static void PDIProtocol_SetParam(void);
			static void PDIProtocol_Erase(void);
			static void PDIProtocol_WriteMemory(void);
			static void PDIProtocol_ReadMemory(void);
			static void PDIProtocol_ReadCRC(void);
		#endif
		
#endif
