/* Copyright 2025 TS Design Works LLC
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
 #pragma once

 #include "quantum.h"
   
 // Work Timer type enum
 typedef enum {
     TIMER_TYPE_30MIN,
     TIMER_TYPE_1HR,
     TIMER_TYPE_4HR,
     TIMER_TYPE_8HR,
     TIMER_TYPE_10HR
 } work_timer_type_t;
   
 // Work Timer state enum
 typedef enum {
     TIMER_STATE_INACTIVE,
     TIMER_STATE_ACTIVE,
     TIMER_STATE_PAUSED,
     TIMER_STATE_LUNCH,
     TIMER_STATE_MID_BREAK,
     TIMER_STATE_COMPLETED
 } work_timer_state_t;
   
 // Work Timer Color definitions - modified for more yellow/orange focus
 // Start point color (green)
 #define WORK_TIMER_START_R 0
 #define WORK_TIMER_START_G 255
 #define WORK_TIMER_START_B 0
   
 // Mid point color (orange) 
 #define WORK_TIMER_MID_R 255
 #define WORK_TIMER_MID_G 112
 #define WORK_TIMER_MID_B 0
   
 // End point color (red)
 #define WORK_TIMER_END_R 255
 #define WORK_TIMER_END_G 0
 #define WORK_TIMER_END_B 0
   
 // Lunch break color (blue)
 #define WORK_TIMER_LUNCH_R 0
 #define WORK_TIMER_LUNCH_G 0
 #define WORK_TIMER_LUNCH_B 255
   
 // Warning color (red)
 #define WORK_TIMER_WARNING_R 255
 #define WORK_TIMER_WARNING_G 0
 #define WORK_TIMER_WARNING_B 0
   
 // Standard timer durations (in milliseconds)
 // IMPORTANT: These represent actual working time (excluding breaks)
 #define TIMER_30MIN_DURATION     1800000  // 30 minutes
 #define TIMER_1HR_DURATION       3600000  // 1 hour
 #define TIMER_4HR_DURATION      14400000  // 4 hours
 #define TIMER_8HR_DURATION      28800000  // 8 hours (real world 9 hours with lunch)
 #define TIMER_10HR_DURATION     36000000  // 10 hours (real world 11 hours with lunch)
   
 // Break durations
 #define BREAK_WARNING_TIME         60000  // 60 seconds
 #define MID_BREAK_30MIN_DURATION   30000  // 30 seconds
 #define MID_BREAK_1HR_DURATION     45000  // 45 seconds
 #define MID_BREAK_4HR_DURATION     60000  // 60 seconds
 #define LUNCH_BREAK_DURATION     3600000  // 1 hour default
   
 // Function declarations for work timer
 void work_timer_init(void);
 void start_timer(work_timer_type_t timer_type);
 void toggle_pause_work_timer(void);
 void update_work_timer(void);
 void handle_work_timer(void);
 void toggle_work_timer(void);
 void work_timer_task(void);
   
 // Functions for checking timer pulse states
 bool is_timer_pulse_active(void);