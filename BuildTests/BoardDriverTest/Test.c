/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#include <LUFA/Common/Common.h>
#include <LUFA/Drivers/Board/Board.h>
#include <LUFA/Drivers/Board/Buttons.h>
#include <LUFA/Drivers/Board/Dataflash.h>
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/Board/Joystick.h>

#if defined(BOARD_HAS_BUTTONS) == defined(BOARD_DUMMY_BUTTONS_IMPLEMENTATION)
	#error Mismatch between BOARD_HAS_BUTTONS and implementation.
#endif

#if defined(BOARD_HAS_DATAFLASH) == defined(BOARD_DUMMY_DATAFLASH_IMPLEMENTATION)
	#error Mismatch between BOARD_HAS_DATAFLASH and implementation.
#endif

#if defined(BOARD_HAS_LEDS) == defined(BOARD_DUMMY_LEDS_IMPLEMENTATION)
	#error Mismatch between BOARD_HAS_LEDS and implementation.
#endif

#if defined(BOARD_HAS_JOYSTICK) == defined(BOARD_DUMMY_JOYSTICK_IMPLEMENTATION)
	#error Mismatch between BOARD_HAS_JOYSTICK and implementation.
#endif

int main(void)
{
	uint_reg_t Dummy;

	/* =============================
	 *     Buttons Compile Check
	 * ============================= */
	// cppcheck-suppress redundantAssignment
	Dummy = BUTTONS_BUTTON1;
	Buttons_Init();
	// cppcheck-suppress redundantAssignment
	Dummy = Buttons_GetStatus();
	Buttons_Disable();

	/* =============================
	 *    Dataflash Compile Check
	 * ============================= */
	// cppcheck-suppress redundantAssignment
	Dummy = DATAFLASH_TOTALCHIPS + DATAFLASH_NO_CHIP + DATAFLASH_CHIP1 + DATAFLASH_PAGE_SIZE + DATAFLASH_PAGES;
	Dataflash_Init();
	Dataflash_TransferByte(0);
	Dataflash_SendByte(0);
	// cppcheck-suppress redundantAssignment
	Dummy = Dataflash_ReceiveByte();
	// cppcheck-suppress redundantAssignment
	Dummy = Dataflash_GetSelectedChip();
	Dataflash_SelectChip(DATAFLASH_CHIP1);
	Dataflash_DeselectChip();
	Dataflash_SelectChipFromPage(0);
	Dataflash_ToggleSelectedChipCS();
	Dataflash_WaitWhileBusy();
	Dataflash_SendAddressBytes(0, 0);

	/* =============================
	 *       LEDs Compile Check
	 * ============================= */
	// cppcheck-suppress redundantAssignment
	Dummy = LEDS_LED1 + LEDS_LED2 + LEDS_LED3 + LEDS_LED4;
	LEDs_Init();
	LEDs_TurnOnLEDs(LEDS_ALL_LEDS);
	LEDs_TurnOffLEDs(LEDS_ALL_LEDS);
	LEDs_SetAllLEDs(LEDS_ALL_LEDS);
	LEDs_ChangeLEDs(LEDS_ALL_LEDS, LEDS_NO_LEDS);
	LEDs_ToggleLEDs(LEDS_ALL_LEDS);
	// cppcheck-suppress redundantAssignment
	Dummy = LEDs_GetLEDs();
	LEDs_Disable();

	/* =============================
	 *     Joystick Compile Check
	 * ============================= */
	// cppcheck-suppress redundantAssignment
	Dummy = JOY_LEFT + JOY_RIGHT + JOY_UP + JOY_DOWN + JOY_PRESS;
	Joystick_Init();
	// cppcheck-suppress redundantAssignment
	Dummy = Joystick_GetStatus();
	Joystick_Disable();

	(void)Dummy;
}


