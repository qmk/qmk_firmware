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
 *  Simple round-robbin cooperative scheduler for use in basic projects where non real-time tasks need
 *  to be executed. Each task is executed in sequence, and can be enabled or disabled individually or as a group.
 *
 *  For a task to yield it must return, thus each task should have persistent data marked with the static attribute.
 *
 *  Usage Example:
 *  \code
 *      #include <LUFA/Scheduler/Scheduler.h>
 *      
 *      TASK(MyTask1);
 *      TASK(MyTask2);
 *      
 *      TASK_LIST
 *      {
 *      	{ Task: MyTask1, TaskStatus: TASK_RUN, GroupID: 1  },
 *      	{ Task: MyTask2, TaskStatus: TASK_RUN, GroupID: 1  },
 *      }
 *
 *      int main(void)
 *      {
 *      	Scheduler_Start();
 *      }
 *
 *      TASK(MyTask1)
 *      {
 *      	// Implementation Here
 *      }
 *
 *      TASK(MyTask2)
 *      {
 *      	// Implementation Here
 *      }
 *  \endcode
 */
 
/** @defgroup Group_Scheduler Simple Task Scheduler - LUFA/Scheduler/Scheduler.h
 *
 *  Simple round-robbin task scheduler. See Scheduler.h description for more details.
 *
 *  @{
 */
 
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		
		#include <util/atomic.h>

		#include "../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Creates a new scheduler task body or prototype. Should be used in the form:
			 *  \code
			 *      TASK(TaskName); // Prototype
			 *
			 *      TASK(TaskName)
			 *      {
			 *           // Task body
			 *      }
			 *  \endcode
			 */
			#define TASK(name)                        void name (void)
			
			/** Defines a task list array, containing one or more task entries of the type TaskEntry_t. Each task list
			 *  should be encased in curly braces and ended with a comma.
			 *
			 *  Usage Example:
			 *  \code
			 *      TASK_LIST
			 *      {
			 *           { Task: MyTask1, TaskStatus: TASK_RUN, GroupID: 1 },
			 *           // More task entries here
			 *      }
			 *  \endcode
			 */
			#define TASK_LIST                         TaskEntry_t Scheduler_TaskList[] = 
			
			/** Constant, giving the maximum delay in scheduler ticks which can be stored in a variable of type
			 *  SchedulerDelayCounter_t.
			 */
			#define TASK_MAX_DELAY                    (MAX_DELAYCTR_COUNT - 1)

			/** Task status mode constant, for passing to Scheduler_SetTaskMode() or Scheduler_SetGroupTaskMode(). */
			#define TASK_RUN                          true

			/** Task status mode constant, for passing to Scheduler_SetTaskMode() or Scheduler_SetGroupTaskMode(). */
			#define TASK_STOP                         false
			
		/* Psuedo-Functions: */
			#if defined(__DOXYGEN__)
				/** Starts the scheduler in its infinite loop, executing running tasks. This should be placed at the end
				 *  of the user application's main() function, as it can never return to the calling function.
				 */
				void Scheduler_Start(void);
				
				/** Initializes the scheduler so that the scheduler functions can be called before the scheduler itself
				 *  is started. This must be executed before any scheduler function calls other than Scheduler_Start(),
				 *  and can be omitted if no such functions could be called before the scheduler is started.
				 */
				void Scheduler_Init(void);
			#else
				#define Scheduler_Start()                 Scheduler_GoSchedule(TOTAL_TASKS);
				
				#define Scheduler_Init()                  Scheduler_InitScheduler(TOTAL_TASKS);
			#endif

		/* Type Defines: */
			/** Type define for a pointer to a scheduler task. */
			typedef void (*TaskPtr_t)(void);
			
			/** Type define for a variable which can hold a tick delay value for the scheduler up to the maximum delay
			 *  possible.
			 */
			typedef uint16_t SchedulerDelayCounter_t;
			
			/** Structure for holding a single task's information in the scheduler task list. */
			typedef struct
			{
				TaskPtr_t Task;       /**< Pointer to the task to execute. */
				bool      TaskStatus; /**< Status of the task (either TASK_RUN or TASK_STOP). */
				uint8_t   GroupID;    /**< Group ID of the task so that its status can be changed as a group. */
			} TaskEntry_t;			

		/* Global Variables: */
			/** Task entry list, containing the scheduler tasks, task statuses and group IDs. Each entry is of type
			 *  TaskEntry_t and can be manipulated as desired, although it is preferential that the proper Scheduler
			 *  functions should be used instead of direct manipulation.
			 */
			extern          TaskEntry_t               Scheduler_TaskList[];
			
			/** Contains the total number of tasks in the task list, irrespective of if the task's status is set to
			 *  TASK_RUN or TASK_STOP.
			 *
			 *  \note This value should be treated as read-only, and never altered in user-code.
			 */
			extern volatile uint8_t                   Scheduler_TotalTasks;

			/**  Contains the current scheduler tick count, for use with the delay functions. If the delay functions
			 *   are used in the user code, this should be incremented each tick period so that the delays can be
			 *   calculated.
			 */
			extern volatile SchedulerDelayCounter_t   Scheduler_TickCounter;

		/* Inline Functions: */
			/** Resets the delay counter value to the current tick count. This should be called to reset the period
			 *  for a delay in a task which is dependant on the current tick value.
			 *
			 *  \param DelayCounter  Counter which is storing the starting tick count for a given delay.
			 */
			static inline void Scheduler_ResetDelay(SchedulerDelayCounter_t* const DelayCounter)
			                                        ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline void Scheduler_ResetDelay(SchedulerDelayCounter_t* const DelayCounter)
			{
				ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
				{
					*DelayCounter = Scheduler_TickCounter;
				}
			}
		
		/* Function Prototypes: */
			/** Determines if the given tick delay has elapsed, based on the given .
			 *
			 *  \param Delay         The delay to test for, measured in ticks
			 *  \param DelayCounter  The counter which is storing the starting tick value for the delay
			 *
			 *  \return Boolean true if the delay has elapsed, false otherwise
			 *
			 *  Usage Example:
			 *  \code
			 *      static SchedulerDelayCounter_t DelayCounter = 10000; // Force immediate run on start-up
			 *				 
			 *      // Task runs every 10000 ticks, 10 seconds for this demo
			 *      if (Scheduler_HasDelayElapsed(10000, &DelayCounter))
			 *      {
			 *           // Code to execute after delay interval elapsed here
			 *      }
			 *  \endcode
			 */
			bool Scheduler_HasDelayElapsed(const uint16_t Delay,
			                               SchedulerDelayCounter_t* const DelayCounter)
										   ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(2);
			
			/** Sets the task mode for a given task.
			 *
			 *  \param Task        Name of the task whose status is to be changed
			 *  \param TaskStatus  New task status for the task (TASK_RUN or TASK_STOP)
			 */
			void Scheduler_SetTaskMode(const TaskPtr_t Task, const bool TaskStatus);
			
			/** Sets the task mode for a given task group ID, allowing for an entire group of tasks to have their
			 *  statuses changed at once.
			 *
			 *  \param GroupID     Value of the task group ID whose status is to be changed
			 *  \param TaskStatus  New task status for tasks in the specified group (TASK_RUN or TASK_STOP)
			 */
			void Scheduler_SetGroupTaskMode(const uint8_t GroupID, const bool TaskStatus);

	/* Private Interface - For use in library only: */		
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define TOTAL_TASKS                       (sizeof(Scheduler_TaskList) / sizeof(TaskEntry_t))
			#define MAX_DELAYCTR_COUNT                0xFFFF

		/* Inline Functions: */
			static inline void Scheduler_InitScheduler(const uint8_t TotalTasks) ATTR_ALWAYS_INLINE;
			static inline void Scheduler_InitScheduler(const uint8_t TotalTasks)
			{
				Scheduler_TotalTasks = TotalTasks;
			}
		
			static inline void Scheduler_GoSchedule(const uint8_t TotalTasks) ATTR_NO_RETURN ATTR_ALWAYS_INLINE;
			static inline void Scheduler_GoSchedule(const uint8_t TotalTasks)
			{
				Scheduler_InitScheduler(TotalTasks);

				for (;;)
				{
					TaskEntry_t* CurrTask = &Scheduler_TaskList[0];
					
					while (CurrTask != &Scheduler_TaskList[TotalTasks])
					{
						if (CurrTask->TaskStatus == TASK_RUN)
						  CurrTask->Task();

						CurrTask++;
					}
				}
			}
	#endif
		
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
