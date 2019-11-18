/* Jim Lindblom @ SparkFun Electronics
 * October 26, 2014
 * https://github.com/sparkfun/Micro_OLED_Breakout/tree/master/Firmware/Arduino/libraries/SFE_MicroOLED
 *
 * Modified by:
 * Emil Varughese @ Edwin Robotics Pvt. Ltd.
 * July 27, 2015
 * https://github.com/emil01/SparkFun_Micro_OLED_Arduino_Library/
 *
 * This code was heavily based around the MicroView library, written by GeekAmmo
 * (https://github.com/geekammo/MicroView-Arduino-Library).
 *
 * Adapted for QMK by:
 * Jack Humbert <jack.humb@gmail.com>
 * October 11, 2018
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "qwiic.h"

void micro_oled_init(void);

void send_command(uint8_t command);
void send_data(uint8_t data);
void set_page_address(uint8_t address);
void set_column_address(uint8_t address);
void clear_screen(void);
void clear_buffer(void);
void send_buffer(void);
void draw_pixel(uint8_t x, uint8_t y, uint8_t color, uint8_t mode);
void draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color, uint8_t mode);
void draw_line_hori(uint8_t x, uint8_t y, uint8_t width, uint8_t color, uint8_t mode);
void draw_line_vert(uint8_t x, uint8_t y, uint8_t height, bool color, uint8_t mode);
void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode);
void draw_rect_soft(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode);
void draw_rect_filled(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode);
void draw_rect_filled_soft(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode);
void draw_char(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t mode, uint8_t font);
void draw_string(uint8_t x, uint8_t y, char* string, uint8_t color, uint8_t mode, uint8_t font);

#define I2C_ADDRESS_SA0_0 0b0111100
#ifndef I2C_ADDRESS_SA0_1
#    define I2C_ADDRESS_SA0_1 0b0111101
#endif
#define I2C_COMMAND 0x00
#define I2C_DATA 0x40
#define PIXEL_OFF 0
#define PIXEL_ON 1

#ifndef LCDWIDTH
#    define LCDWIDTH 64
#endif
#ifndef LCDWIDTH
#    define LCDHEIGHT 48
#endif
#define FONTHEADERSIZE 6

#define NORM 0
#define XOR 1

#define PAGE 0
#define ALL 1

#define WIDGETSTYLE0 0
#define WIDGETSTYLE1 1
#define WIDGETSTYLE2 2

#define SETCONTRAST 0x81
#define DISPLAYALLONRESUME 0xA4
#define DISPLAYALLON 0xA5
#define NORMALDISPLAY 0xA6
#define INVERTDISPLAY 0xA7
#define DISPLAYOFF 0xAE
#define DISPLAYON 0xAF
#define SETDISPLAYOFFSET 0xD3
#define SETCOMPINS 0xDA
#define SETVCOMDESELECT 0xDB
#define SETDISPLAYCLOCKDIV 0xD5
#define SETPRECHARGE 0xD9
#define SETMULTIPLEX 0xA8
#define SETLOWCOLUMN 0x00
#define SETHIGHCOLUMN 0x10
#define SETSTARTLINE 0x40
#define MEMORYMODE 0x20
#define COMSCANINC 0xC0
#define COMSCANDEC 0xC8
#define SEGREMAP 0xA0
#define CHARGEPUMP 0x8D
#define EXTERNALVCC 0x01
#define SWITCHCAPVCC 0x02

// Scroll
#define ACTIVATESCROLL 0x2F
#define DEACTIVATESCROLL 0x2E
#define SETVERTICALSCROLLAREA 0xA3
#define RIGHTHORIZONTALSCROLL 0x26
#define LEFT_HORIZONTALSCROLL 0x27
#define VERTICALRIGHTHORIZONTALSCROLL 0x29
#define VERTICALLEFTHORIZONTALSCROLL 0x2A

typedef enum CMD {
    CMD_CLEAR,         // 0
    CMD_INVERT,        // 1
    CMD_CONTRAST,      // 2
    CMD_DISPLAY,       // 3
    CMD_SETCURSOR,     // 4
    CMD_PIXEL,         // 5
    CMD_LINE,          // 6
    CMD_LINEH,         // 7
    CMD_LINEV,         // 8
    CMD_RECT,          // 9
    CMD_RECTFILL,      // 10
    CMD_CIRCLE,        // 11
    CMD_CIRCLEFILL,    // 12
    CMD_DRAWCHAR,      // 13
    CMD_DRAWBITMAP,    // 14
    CMD_GETLCDWIDTH,   // 15
    CMD_GETLCDHEIGHT,  // 16
    CMD_SETCOLOR,      // 17
    CMD_SETDRAWMODE    // 18
} commCommand_t;