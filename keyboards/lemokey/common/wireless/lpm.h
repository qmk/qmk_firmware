/* Copyright 2022~2024 @ lokher (https://www.keychron.com)
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

#ifndef RUN_MODE_PROCESS_TIME
#    define RUN_MODE_PROCESS_TIME 1000
#endif

typedef enum {
    PM_RUN,
    PM_SLEEP,
    PM_STOP,
    PM_STANDBY,
} pm_t;

void lpm_init(void);
void lpm_timer_reset(void);
void lpm_timer_stop(void);
void select_all_cols(void);
void matrix_enter_low_power(void);
void matrix_exit_low_power(void);
void lpm_pre_enter_low_power(void);
void lpm_enter_low_power(void);
void lpm_enter_low_power_kb(void);
void lpm_post_enter_low_power(void) ;
void lpm_standby(pm_t mode);
void lpm_early_wakeup(void);
void lpm_wakeup_init(void);
void lpm_pre_wakeup(void);
void lpm_wakeup(void);
void lpm_post_wakeup(void);
bool usb_power_connected(void);
bool lpm_is_kb_idle(void);
void enter_power_mode(pm_t mode);
void lpm_task(void);
