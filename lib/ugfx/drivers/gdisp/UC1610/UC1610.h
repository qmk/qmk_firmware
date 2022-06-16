/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://chibios-gfx.com/license.html
 */

#ifndef _UC1610_H
#define _UC1610_H

  // screen dimensions
  #define UC1610_SCREEN_WIDTH			160
  #define UC1610_SCREEN_HEIGHT			104
  #define UC1610_PAGE_HEIGHT			4

  // i2c header addresses
  #define UC1610_ADDRESS_WC			0x78		// write commands
  #define UC1610_ADDRESS_RS			0x79		// read satus
  #define UC1610_ADDRESS_WD			0x7A		// write data
  #define UC1610_ADDRESS_RD			0x7B		// read data

  // hardware control commands
  #define UC1610_SYSTEM_RESET			0xE2
  #define UC1610_NOP				0xE3		// no operation
  #define UC1610_SET_TEMP_COMP			0x24		// set temperature compensation, default -0.05%/°C
  #define UC1610_SET_PANEL_LOADING		0x29		// set panel loading, default 16~21 nF
  #define UC1610_SET_PUMP_CONTROL		0x2F		// default internal Vlcd (8x pump)
  #define UC1610_SET_LCD_BIAS_RATIO		0xEB		// default 11
  #define UC1610_SET_VBIAS_POT			0x81		// 1 byte (0~255) to follow setting the contrast, default 0x81
  #define UC1610_SET_LINE_RATE			0xA0		// default 12,1 Klps
  #define UC1610_SET_DISPLAY_ENABLE		0xAE		// + 1 mask / 0 : exit sleep mode / entering sleep mode
  #define UC1610_SET_LCD_GRAY_SHADE		0xD0		// default 24% between the two gray shade levels
  #define UC1610_SET_COM_END			0xF1		// set the number of used com electrodes (lines number -1)

  // ram address control
  #define UC1610_SET_AC				0x88		// set ram addres control
  #define UC1610_AC_WA_MASK			1		// automatic column/page increment wrap arroud (1 : cycle increment)
  #define UC1610_AC_AIO_MASK			(1 << 1)	// auto increment order (0/1 : column/page increment first)
  #define UC1610_AC_PID_MASK			(1 << 2)	// page addres auto increment order (0/1 : +1/-1)

  // set cursor ram address
  #define UC1610_SET_CA_LSB			0x00		// + 4 LSB bits
  #define UC1610_SET_CA_MSB 			0x10		// + 4 MSB bits // MSB + LSB values range : 0~159
  #define UC1610_SET_PA				0x60		// + 5 bits // values range : 0~26

  // display control commands
  #define UC1610_SET_FIXED_LINES		0x90		// + 4 bits = 2xFL
  #define UC1610_SET_SCROLL_LINES_LSB		0x40		// + 4 LSB bits scroll up display by N (7 bits) lines
  #define UC1610_SET_SCROLL_LINES_MSB		0x50		// + 3 MSB bits
  #define UC1610_SET_ALL_PIXEL_ON		0xA4		// + 1 mask / 0 : set all pixel on, reverse
  #define UC1610_SET_INVERSE_DISPLAY		0xA6		// + 1 mask / 0 : inverse all data stored in ram, reverse
  #define UC1610_SET_MAPPING_CONTROL		0xC0		// control mirorring
  #define UC1610_SET_MAPPING_CONTROL_LC_MASK	1		//
  #define UC1610_SET_MAPPING_CONTROL_MX_MASK	(1 << 1)	//
  #define UC1610_SET_MAPPING_CONTROL_MY_MASK	(1 << 2)	//

  // window program mode
  #define UC1610_SET_WINDOW_PROGRAM_ENABLE	0xF8		// + 1 mask / 0 : enable / disable window programming mode,
  								// reset before changing boundaries
  #define UC1610_SET_WP_STARTING_CA		0xF4		// 1 byte to follow for column number
  #define UC1610_SET_WP_ENDING_CA		0xF6		// 1 byte to follow for column number
  #define UC1610_SET_WP_STARTING_PA		0xF5		// 1 byte to follow for page number
  #define UC1610_SET_WP_ENDING_PA		0xF7		// 1 byte to follow for page number

#endif /* _SSD1306_H */
