/* Copyright (C) 2024 koosikus
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

typedef enum {
    LPWR_NORMAL = 0,
    LPWR_PRESLEEP,
    LPWR_STOP,
    LPWR_WAKEUP,
} lpwr_state_t;

typedef enum {
    LPWR_WAKEUP_NONE = 0,
    LPWR_WAKEUP_MATRIX,
    LPWR_WAKEUP_UART,
    LPWR_WAKEUP_CABLE,
    LPWR_WAKEUP_USB,
    LPWR_WAKEUP_ONEKEY,
    LPWR_WAKEUP_ENCODER,
    LPWR_WAKEUP_SWITCH,
} lpwr_wakeupcd_t;

typedef enum {
    LPWR_MODE_TIMEOUT = 0,
} lpwr_mode_t;

lpwr_state_t lpwr_get_state(void);
lpwr_mode_t lpwr_get_mode(void);
uint32_t lpwr_timestamp_read(void);
uint32_t lpwr_timeout_value_read(void);
void lpwr_set_sleep_wakeupcd(lpwr_wakeupcd_t wakeupcd);
lpwr_wakeupcd_t lpwr_get_sleep_wakeupcd(void);
void lpwr_update_timestamp(void);
void lpwr_set_timeout_manual(bool enable);
bool lpwr_get_timeout_manual(void);
void lpwr_set_state(lpwr_state_t state);
void lpwr_set_mode(lpwr_mode_t mode);
void lpwr_task(void);
