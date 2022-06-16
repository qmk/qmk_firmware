/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://chibios-gfx.com/license.html
 */

#ifndef _SSD1322_H
#define _SSD1322_H

/**************************************************
*    LM320Y-256064 (SSD1322 driver)
*
*    Pin   Function     SPI connections
*    ----+------------+----------
*      1   VSS		GND
*      2   VBAT		3.3V-5V
*      3   NC
*      4   D0		SCLK	Serial Clock
*      5   D1		MOSI	Serial Data Input
*      6   D2		NC
*      7   D3 		GND
*      8   D4		GND
*      9   D5		GND
*     10   D6		GND
*     11   D7		GND
*     12   #RD		GND
*     13   #WR		GND
*     14   DC		Data / Command
*     15   #RESET
*     16   #CS		Chip select
*
*     Note: All logic pins are 3.3V max.
*
*     BS1 BS0	Mode
*     --------+---------------------
*      0   0	"4 Line SPI" 8-bit + DC pin
*      0   1	"3 Line SPI" 9-bit DC is 9th bit
*      1   0	8-bit 8080 parallel
*      1   1	8-bit 6800 parallel
*
*      Note: SPI mode is write only (MOSI)
*
**************************************************/

#define CMD_ENABLE_GRAY_SCALE_TABLE			0x00
#define CMD_SET_COLUMN_ADDR					0x15
#define CMD_WRITE_RAM						0x5C
#define CMD_READ_RAM						0x5D
#define CMD_SET_ROW_ADDR					0x75
#define CMD_SET_REMAP						0xA0
#define CMD_SET_DISPLAY_START_LINE			0xA1
#define CMD_SET_DISPLAY_OFFSET				0xA2
#define CMD_SET_DISPLAY_MODE_OFF			0xA4
#define CMD_SET_DISPLAY_MODE_ON				0xA5
#define CMD_SET_DISPLAY_MODE_NORMAL			0xA6
#define CMD_SET_DISPLAY_MODE_INVERSE		0xA7
#define CMD_ENABLE_PARTIAL_DISPLAY			0xA8
#define CMD_EXIT_PARTIAL_DISPLAY			0xA9
#define CMD_SET_FUNCTION_SELECTION			0xAB
#define CMD_SET_DISPLAY_OFF					0xAE
#define CMD_SET_DISPLAY_ON					0xAF
#define CMD_SET_PHASE_LENGTH				0xB1
#define CMD_SET_CLOCK_DIVIDER				0xB3
#define CMD_DISPLAY_ENHANCEMENT				0xB4
#define CMD_SET_GPIO						0xB5
#define CMD_SET_SECOND_PRECHARGE_PERIOD		0xB6
#define CMD_SET_GRAY_SCALE_TABLE			0xB8
#define CMD_SET_PRECHARGE_VOLTAGE			0xBB
#define CMD_SET_DEFAULT_LINEAR_GRAY_SCALE_TABLE	0xB9
#define CMD_SET_VCOMH_VOLTAGE				0xBE
#define CMD_SET_CONTRAST_CURRENT			0xC1
#define CMD_MASTER_CURRENT_CONTROL			0xC7
#define CMD_SET_MULTIPLEX_RATIO				0xCA
#define CMD_DISPLAY_ENHANCEMENT_B			0xD1
#define CMD_SET_COMMAND_LOCK				0xFD

#endif /* _SSD1322_H */
