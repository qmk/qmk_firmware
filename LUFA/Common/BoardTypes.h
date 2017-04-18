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

/** \file
 *  \brief Supported pre-made board hardware defines.
 *
 *  \copydetails Group_BoardTypes
 *
 *  \note Do not include this file directly, rather include the Common.h header file instead to gain this file's
 *        functionality.
 */

/** \ingroup Group_Common
 *  \defgroup Group_BoardTypes Board Types
 *  \brief Supported pre-made board hardware defines.
 *
 *  Board macros for indicating the chosen physical board hardware to the library. These macros should be used when
 *  defining the \c BOARD token to the chosen hardware via the \c -D switch in the project makefile. If a custom
 *  board is used, the \ref BOARD_NONE or \ref BOARD_USER values should be selected.
 *
 *  @{
 */

#ifndef __LUFA_BOARDTYPES_H__
#define __LUFA_BOARDTYPES_H__

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_COMMON_H)
			#error Do not include this file directly. Include LUFA/Common/Common.h instead to gain this functionality.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Selects the user-defined board drivers, which should be placed in the user project's folder
			 *  under a directory named \c /Board/. Each board driver should be named identically to the LUFA
			 *  master board driver (i.e., driver in the \c LUFA/Drivers/Board directory) so that the library
			 *  can correctly identify it.
			 */
			#define BOARD_USER                 0

			/** Disables board drivers when operation will not be adversely affected (e.g. LEDs) - use of board drivers
			 *  such as the Joystick driver, where the removal would adversely affect the code's operation is still disallowed. */
			#define BOARD_NONE                 1

			/** Selects the USBKEY specific board drivers, including Temperature, Button, Dataflash, Joystick and LED drivers. */
			#define BOARD_USBKEY               2

			/** Selects the STK525 specific board drivers, including Temperature, Button, Dataflash, Joystick and LED drivers. */
			#define BOARD_STK525               3

			/** Selects the STK526 specific board drivers, including Temperature, Button, Dataflash, Joystick and LED drivers. */
			#define BOARD_STK526               4

			/** Selects the RZUSBSTICK specific board drivers, including the driver for the boards LEDs. */
			#define BOARD_RZUSBSTICK           5

			/** Selects the ATAVRUSBRF01 specific board drivers, including the driver for the board LEDs. */
			#define BOARD_ATAVRUSBRF01         6

			/** Selects the BUMBLEB specific board drivers, using the officially recommended peripheral layout. */
			#define BOARD_BUMBLEB              7

			/** Selects the XPLAIN (Revision 2 or newer) specific board drivers, including LED and Dataflash drivers. */
			#define BOARD_XPLAIN               8

			/** Selects the XPLAIN (Revision 1) specific board drivers, including LED and Dataflash drivers. */
			#define BOARD_XPLAIN_REV1          9

			/** Selects the EVK527 specific board drivers, including Temperature, Button, Dataflash, Joystick and LED drivers. */
			#define BOARD_EVK527               10

			/** Selects the Teensy version 1.x specific board drivers, including the driver for the board LEDs. */
			#define BOARD_TEENSY               11

			/** Selects the USBTINY MKII specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_USBTINYMKII          12

			/** Selects the Benito specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_BENITO               13

			/** Selects the JM-DB-U2 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_JMDBU2               14

			/** Selects the Olimex AVR-USB-162 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_OLIMEX162            15

			/** Selects the UDIP specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_UDIP                 16

			/** Selects the BUI specific board drivers, including the driver for the board LEDs. */
			#define BOARD_BUI                  17

			/** Selects the Arduino Uno specific board drivers, including the driver for the board LEDs. */
			#define BOARD_UNO                  18

			/** Selects the Busware CUL V3 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_CULV3                19

			/** Selects the Blackcat USB JTAG specific board drivers, including the driver for the board LEDs. */
			#define BOARD_BLACKCAT             20

			/** Selects the Maximus specific board drivers, including the driver for the board LEDs. */
			#define BOARD_MAXIMUS              21

			/** Selects the Minimus specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_MINIMUS              22

			/** Selects the Adafruit U4 specific board drivers, including the Button driver. */
			#define BOARD_ADAFRUITU4           23

			/** Selects the Microsin AVR-USB162 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_MICROSIN162          24

			/** Selects the Kernel Concepts USBFOO specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_USBFOO               25

			/** Selects the Sparkfun ATMEGA8U2 specific board drivers, including the driver for the board LEDs. */
			#define BOARD_SPARKFUN8U2          26

			/** Selects the Atmel EVK1101 specific board drivers, including the Button, Joystick and LED drivers. */
			#define BOARD_EVK1101              27

			/** Selects the Busware TUL specific board drivers, including the Button and LED drivers. */
			#define BOARD_TUL                  28

			/** Selects the Atmel EVK1100 specific board drivers, including the Button, Joystick and LED drivers. */
			#define BOARD_EVK1100              29

			/** Selects the Atmel EVK1104 specific board drivers, including the Button and LED drivers. */
			#define BOARD_EVK1104              30

			/** Selects the Atmel XMEGA A3BU Xplained specific board drivers, including Dataflash, Button and LED drivers. */
			#define BOARD_A3BU_XPLAINED        31

			/** Selects the Teensy version 2.x specific board drivers, including the driver for the board LEDs. */
			#define BOARD_TEENSY2              32

			/** Selects the USB2AX version 1 and 2 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_USB2AX               33

			/** Selects the USB2AX version 3 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_USB2AX_V3            34

			/** Selects the Micropendous 32U2 specific board drivers, including the Button and LED drivers. */
			#define BOARD_MICROPENDOUS_32U2    35

			/** Selects the Micropendous A specific board drivers, including the driver for the board Button. */
			#define BOARD_MICROPENDOUS_A       36

			/** Selects the Micropendous 1 specific board drivers, including the driver for the board Button. */
			#define BOARD_MICROPENDOUS_1       37

			/** Selects the Micropendous 2 specific board drivers, including the driver for the board Button. */
			#define BOARD_MICROPENDOUS_2       38

			/** Selects the Micropendous 3 specific board drivers, including the driver for the board Button. */
			#define BOARD_MICROPENDOUS_3       39

			/** Selects the Micropendous 4 specific board drivers, including the driver for the board Button. */
			#define BOARD_MICROPENDOUS_4       40

			/** Selects the Micropendous DIP specific board drivers, including the driver for the board Button. */
			#define BOARD_MICROPENDOUS_DIP     41

			/** Selects the Micropendous (Arduino-like) revision 1 specific board drivers, including the Button and LED drivers. */
			#define BOARD_MICROPENDOUS_REV1    42

			/** Selects the Micropendous (Arduino-like) revision 2 specific board drivers, including the Button and LED drivers. */
			#define BOARD_MICROPENDOUS_REV2    43

			/** Selects the XMEGA B1 Xplained specific board drivers, including the Button and LED drivers. */
			#define BOARD_B1_XPLAINED          44

			/** Selects the Bitwizard Multio specific board drivers, including the driver for the board LEDs. */
			#define BOARD_MULTIO               45

			/** Selects the Bitwizard Big-Multio specific board drivers, including the driver for the board LEDs. */
			#define BOARD_BIGMULTIO            46

			/** Selects the DorkbotPDX Duce specific board drivers, including the driver for the board LEDs. */
			#define BOARD_DUCE                 47

			/** Selects the Olimex AVR-USB-32U4 specific board drivers, including the Button and LED drivers. */
			#define BOARD_OLIMEX32U4           48

			/** Selects the Olimex AVR-USB-T32U4 specific board drivers, including the Button and LED drivers. */
			#define BOARD_OLIMEXT32U4          49

			/** Selects the Olimex AVR-ISP-MK2 specific board drivers, including the Button and LED drivers. */
			#define BOARD_OLIMEXISPMK2         50

			/** Selects the Arduino Leonardo specific board drivers, including the driver for the board LEDs. */
			#define BOARD_LEONARDO             51

			/** Selects the UC3-A3 Xplained specific board drivers, including the Button and LED drivers. */
			#define BOARD_UC3A3_XPLAINED       52

			/** Selects the USB2AX version 3.1 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_USB2AX_V31           53

			/** Selects the Stange-ISP specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_STANGE_ISP           54

			/** Selects the XMEGA C3 XPLAINED specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_C3_XPLAINED          55

			/** Selects the U2S specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_U2S                  56

			/** Selects the Arduino YUN specific board drivers, including the driver for the board LEDs. */
			#define BOARD_YUN                  57

			/** Selects the Arduino Micro specific board drivers, including the driver for the board LEDs. */
			#define BOARD_MICRO                58

			/** Selects the Pololu A-Star Micro specific board drivers, including the driver for the board LEDs. */
			#define BOARD_POLOLUMICRO          59

			/** Selects the Atmel Xplained-MINI specific board drivers, including the driver for the board LEDs. */
			#define BOARD_XPLAINED_MINI        60

			#if !defined(__DOXYGEN__)
				#define BOARD_                 BOARD_NONE

				#if !defined(BOARD)
					#define BOARD              BOARD_NONE
				#endif
			#endif

#endif

/** @} */

