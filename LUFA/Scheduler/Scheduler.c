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

#include "Scheduler.h"

volatile SchedulerDelayCounter_t Scheduler_TickCounter;
volatile uint_least8_t           Scheduler_TotalTasks;

bool Scheduler_HasDelayElapsed(const uint_least16_t Delay,
                               SchedulerDelayCounter_t* const DelayCounter)
{
	SchedulerDelayCounter_t CurrentTickValue_LCL;
	SchedulerDelayCounter_t DelayCounter_LCL;

	uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
	GlobalInterruptDisable();

	CurrentTickValue_LCL = Scheduler_TickCounter;

	SetGlobalInterruptMask(CurrentGlobalInt);

	DelayCounter_LCL = *DelayCounter;

	if (CurrentTickValue_LCL >= DelayCounter_LCL)
	{
		if ((CurrentTickValue_LCL - DelayCounter_LCL) >= Delay)
		{
			*DelayCounter = CurrentTickValue_LCL;
			return true;
		}
	}
	else
	{
		if (((MAX_DELAYCTR_COUNT - DelayCounter_LCL) + CurrentTickValue_LCL) >= Delay)
		{
			*DelayCounter = CurrentTickValue_LCL;
			return true;
		}
	}

	return false;
}

void Scheduler_SetTaskMode(const TaskPtr_t Task,
                           const bool TaskStatus)
{
	TaskEntry_t* CurrTask = &Scheduler_TaskList[0];

	while (CurrTask != &Scheduler_TaskList[Scheduler_TotalTasks])
	{
		if (CurrTask->Task == Task)
		{
			CurrTask->TaskStatus = TaskStatus;
			break;
		}

		CurrTask++;
	}
}

void Scheduler_SetGroupTaskMode(const uint_least8_t GroupID,
                                const bool TaskStatus)
{
	TaskEntry_t* CurrTask = &Scheduler_TaskList[0];

	while (CurrTask != &Scheduler_TaskList[Scheduler_TotalTasks])
	{
		if (CurrTask->GroupID == GroupID)
		  CurrTask->TaskStatus = TaskStatus;

		CurrTask++;
	}
}

