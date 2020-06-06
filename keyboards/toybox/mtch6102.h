
/* Copyright 2020 sekigon-gonnoc
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

typedef struct {
    uint8_t  status;
    uint8_t  gesture;
    uint16_t x;
    uint16_t y;
} mtch6102_data_t;

typedef enum {
    TOUCH   = 1 << 0,
    GESTURE = 1 << 1,
} MTCH6102_STAT_BIT;

#define MTCH6102_READ_ADDR 0x25
#define MTCH6102_REG_STAT 0x10
#define MTCH6102_REG_CMD 0x04
#define MTCH6102_REG_MODE 0x05
#define MTCH6102_REG_CFG_START 0x20
#define MTCH6102_REG_CFG_END 0x43
#define MTCH6102_CFG_LEN (MTCH6102_REG_CFG_END - MTCH6102_REG_CFG_START + 1)

typedef enum { GES_TAP = 0x10, GES_DOUBLE_TAP = 0x20 } MTCH6102_GESTURE_CODE;

void pointing_device_set_button(uint8_t btn);
void pointing_device_clear_button(uint8_t btn);

uint16_t check_mtch6102(void);
int      init_mtch6102(void);
bool     read_mtch6102(mtch6102_data_t* const data);
bool     process_mtch6102(mtch6102_data_t const* const data,
                          report_mouse_t* const        rep_mouse);
int      sleep_mtch6102(void);
void     test_mtch6102(void);
