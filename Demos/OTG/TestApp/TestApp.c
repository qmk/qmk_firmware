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
 *  Main source file for the TestApp demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "TestApp.h"

/* Scheduler Task List */
TASK_LIST
{
	{ .Task = TestApp_CheckJoystick, .TaskStatus = TASK_RUN  },
	{ .Task = TestApp_CheckButton  , .TaskStatus = TASK_RUN  },
	{ .Task = TestApp_CheckTemp    , .TaskStatus = TASK_RUN  },
	{ .Task = USB_USBTask          , .TaskStatus = TASK_RUN  },
};

/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
	
	/* Hardware initialization */
	SerialStream_Init(9600, false);
	ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_64);
	Temperature_Init();
	Joystick_Init();
	LEDs_Init();
	Buttons_Init();
	
	/* Millisecond timer initialization, with output compare interrupt enabled */
	OCR0A  = 0x7D;
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
	TIMSK0 = (1 << OCIE0A);
	
	/* Turn on interrupts */
	sei();

    /* Start-up message via USART */
	puts_P(PSTR(ESC_RESET ESC_BG_WHITE ESC_INVERSE_ON ESC_ERASE_DISPLAY
	       "LUFA Demo running.\r\n" ESC_INVERSE_OFF));

	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** ISR for the timer 0 compare vector. This ISR fires once each millisecond, and increments the
 *  scheduler tick counter.
 */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	/* Scheduler test - increment scheduler tick counter once each millisecond */
	Scheduler_TickCounter++;
}

/** Task responsible for checking the joystick position, and displaying the joystick position onto the
 *  board LEDs.
 */
TASK(TestApp_CheckJoystick)
{
	uint8_t JoyStatus_LCL = Joystick_GetStatus();
	uint8_t LEDMask       = 0;
		
	/* Test of the Joystick - change a mask in response to joystick */
	if (JoyStatus_LCL & JOY_UP)
	  LEDMask |= LEDS_LED1;
		
	if (JoyStatus_LCL & JOY_DOWN)
	  LEDMask |= LEDS_LED2;

	if (JoyStatus_LCL & JOY_LEFT)
	  LEDMask |= LEDS_LED3;

	if (JoyStatus_LCL & JOY_RIGHT)
	  LEDMask |= LEDS_LED4;
			
	if (JoyStatus_LCL & JOY_PRESS)
	  LEDMask  = LEDS_ALL_LEDS;

	/* Test of LEDs - light up in response to joystick */
	LEDs_SetAllLEDs(LEDMask);
}

/** Task responsible for checking the current temperature via the temperature sensor mounted on the
 *  board, and displaying it through the serial USART.
 */
TASK(TestApp_CheckTemp)
{
	static SchedulerDelayCounter_t DelayCounter = 10000; // Force immediate run on start-up

	/* Task runs every 10000 ticks, 10 seconds for this demo */
	if (Scheduler_HasDelayElapsed(10000, &DelayCounter))
	{
		printf_P(PSTR("Current temperature: %d Degrees Celcius\r\n\r\n"),
		         (int8_t)Temperature_GetTemperature());

		/* Reset the delay counter, ready to count another 10000 tick interval */
		Scheduler_ResetDelay(&DelayCounter);
	}	
}

/** Task responsible for checking the board's first button' position, and start-stopping other tasks and the USB
 *  interface in response to user joystick movements.
 */
TASK(TestApp_CheckButton)
{
	static SchedulerDelayCounter_t DelayCounter = 0;
	static bool                    IsPressed;
	static bool                    BlockingJoystickTask;
	
	/* Check if board button pressed (start USB) */
	if (Buttons_GetStatus() & BUTTONS_BUTTON1)
	{
		/* Debounce - check 100 ticks later to see if button is still being pressed */
		if ((IsPressed == false) && (Scheduler_HasDelayElapsed(100, &DelayCounter)))
		{
			/* Set flag, indicating that current pressed state has been handled */
			IsPressed = true;
			
			/* First start of the USB interface permanently blocks the joystick task */
			if (BlockingJoystickTask == false)
			{
				Scheduler_SetTaskMode(TestApp_CheckJoystick, TASK_STOP);
				BlockingJoystickTask = true;
			}

			/* Toggle USB interface */
			if (USB_IsInitialized == true)
			{
				USB_ShutDown();

				LEDs_SetAllLEDs(LEDS_LED1);
				puts_P(PSTR(ESC_BG_WHITE "USB Power Off.\r\n"));
				
				Scheduler_SetTaskMode(TestApp_CheckTemp, TASK_RUN);
			}
			else
			{
				Scheduler_SetTaskMode(TestApp_CheckTemp, TASK_STOP);

				LEDs_SetAllLEDs(LEDS_LED2 | LEDS_LED3);
				puts_P(PSTR(ESC_BG_YELLOW "USB Power On.\r\n"));
				
				USB_Init(USB_MODE_UID, USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL);
			}
		}
	}
    else
    {
		/* Board button not pressed - reset debounce interval counter and press handled flag */
		Scheduler_ResetDelay(&DelayCounter);
		IsPressed = false;
	}
}
