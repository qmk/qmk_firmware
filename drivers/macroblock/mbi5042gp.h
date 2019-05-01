/* Copyright 2019 /u/KeepItUnder
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


#ifndef MBI5024GP_DRIVER_H
#define MBI5024GP_DRIVER_H
#endif

#include <stdint.h>
#include <stdbool.h>

/* #define MBI5042GP_CFGREG_DEFAULT 0x002b0ul */
#define MBI5042GP_CFGREG_DEFAULT 0b1000010000000000u

#define MBI5042GP_GCLK_GPIO PA12
#define MBI5042GP_GCLK_SRC PWM0
#define MBI5042GP_GCLK_SPD 4000000
#define MBI5042GP_DCLK_GPIO PD4
#define MBI5042GP_LE PD3

#define MBI5042GP_ROW_COUNT 5
#define MBI5042GP_REFRESH_SPD 2000

void MBI5042GP_init( void );

void MBI5042GP_set_current_gain( uint8_t gain );
void MBI5042GP_write_config_register( uint16_t regValue );

void MBI5042GP_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void MBI5042GP_set_color_all( uint8_t red, uint8_t green, uint8_t blue );

void MBI5042GP_update_pwm_buffers( void );
void MBI5042GP_write_pwm_buffers( void );

void MBI5042GP_planar_recode( int row, int column, uint8_t red, uint8_t green, uint8_t blue);

void MBI5042GP_disable_rows( void );
void MBI5042GP_disable_row( int row );
void MBI5042GP_enable_row( int row );
