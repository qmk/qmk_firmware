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
 *  Macros for the V2 Protocol Packet Commands and Responses.
 */

#ifndef _V2_PROTOCOL_CONSTANTS_
#define _V2_PROTOCOL_CONSTANTS_

	/* Macros: */
		#define CMD_SIGN_ON                 0x01
		#define CMD_SET_PARAMETER           0x02
		#define CMD_GET_PARAMETER           0x03
		#define CMD_OSCCAL                  0x05
		#define CMD_LOAD_ADDRESS            0x06
		#define CMD_FIRMWARE_UPGRADE        0x07
		#define CMD_RESET_PROTECTION        0x0A
		#define CMD_ENTER_PROGMODE_ISP      0x10
		#define CMD_LEAVE_PROGMODE_ISP      0x11
		#define CMD_CHIP_ERASE_ISP          0x12
		#define CMD_PROGRAM_FLASH_ISP       0x13
		#define CMD_READ_FLASH_ISP          0x14
		#define CMD_PROGRAM_EEPROM_ISP      0x15
		#define CMD_READ_EEPROM_ISP         0x16
		#define CMD_PROGRAM_FUSE_ISP        0x17
		#define CMD_READ_FUSE_ISP           0x18
		#define CMD_PROGRAM_LOCK_ISP        0x19
		#define CMD_READ_LOCK_ISP           0x1A
		#define CMD_READ_SIGNATURE_ISP      0x1B
		#define CMD_READ_OSCCAL_ISP         0x1C
		#define CMD_SPI_MULTI               0x1D
		#define CMD_XPROG                   0x50
		#define CMD_XPROG_SETMODE           0x51

		#define STATUS_CMD_OK               0x00
		#define STATUS_CMD_TOUT             0x80
		#define STATUS_RDY_BSY_TOUT         0x81
		#define STATUS_SET_PARAM_MISSING    0x82
		#define STATUS_CMD_FAILED           0xC0
		#define STATUS_CMD_UNKNOWN          0xC9
		#define STATUS_ISP_READY            0x00
		#define STATUS_CONN_FAIL_MOSI       0x01
		#define STATUS_CONN_FAIL_RST        0x02
		#define STATUS_CONN_FAIL_SCK        0x04
		#define STATUS_TGT_NOT_DETECTED     0x10
		#define STATUS_TGT_REVERSE_INSERTED 0x20

		#define PARAM_BUILD_NUMBER_LOW      0x80
		#define PARAM_BUILD_NUMBER_HIGH     0x81
		#define PARAM_HW_VER                0x90
		#define PARAM_SW_MAJOR              0x91
		#define PARAM_SW_MINOR              0x92
		#define PARAM_VTARGET               0x94
		#define PARAM_SCK_DURATION          0x98
		#define PARAM_RESET_POLARITY        0x9E
		#define PARAM_STATUS_TGT_CONN       0xA1
		#define PARAM_DISCHARGEDELAY        0xA4

#endif
