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
#include "micro_oled.h"
#include <stdlib.h>
#include "util/font5x7.h"
#include "util/font8x16.h"
#include "string.h"

#define TOTALFONTS 2
const unsigned char * fonts_pointer[]= { font5x7, font8x16 };

uint8_t foreColor,drawMode,fontWidth, fontHeight, fontType, fontStartChar, fontTotalChar, cursorX, cursorY;
uint16_t fontMapWidth;

#define _BV(x) (1 << (x))
#define swap(a, b) { uint8_t t = a; a = b; b = t; }

uint8_t micro_oled_transfer_buffer[20];
static uint8_t micro_oled_screen_buffer[] = {
/* LCD Memory organised in 64 horizontal pixel and 6 rows of byte
   B  B .............B  -----
   y  y .............y        \
   t  t .............t         \
   e  e .............e          \
   0  1 .............63          \
                                  \
   D0 D0.............D0            \
   D1 D1.............D1            / ROW 0
   D2 D2.............D2           /
   D3 D3.............D3          /
   D4 D4.............D4         /
   D5 D5.............D5        /
   D6 D6.............D6       /
   D7 D7.............D7  ----
  */

// QMK Logo - generated at http://www.majer.ch/lcd/adf_bitmap.php

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00,
0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00,
0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x60,
0xF8, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE,
0xFE, 0xF8, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x8C, 0x8C, 0x8C, 0x8C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8C, 0x8C, 0x8C, 0x8C,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x31, 0x31, 0x31, 0x31, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF8, 0xF1, 0xE3, 0xE7, 0xCF,
0xCF, 0xCF, 0xCF, 0x00, 0x00, 0xCF, 0xCF, 0xCF, 0xC7, 0xE7,
0xE3, 0xF1, 0xF8, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x31, 0x31, 0x31, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06,
0x06, 0x06, 0x1F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0x7F, 0x7F, 0x1F, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00
};

void micro_oled_init(void) {

  i2c_init();
  i2c_start(I2C_ADDRESS_SA0_1);

  // Display Init sequence for 64x48 OLED module
  send_command(DISPLAYOFF);      // 0xAE

  send_command(SETDISPLAYCLOCKDIV);  // 0xD5
  send_command(0x80);          // the suggested ratio 0x80

  send_command(SETMULTIPLEX);      // 0xA8
  send_command(0x2F);

  send_command(SETDISPLAYOFFSET);    // 0xD3
  send_command(0x0);         // no offset

  send_command(SETSTARTLINE | 0x0);  // line #0

  send_command(CHARGEPUMP);      // enable charge pump
  send_command(0x14);

  send_command(NORMALDISPLAY);     // 0xA6
  send_command(DISPLAYALLONRESUME);  // 0xA4

  send_command(SEGREMAP | 0x1);
  send_command(COMSCANDEC);

  send_command(SETCOMPINS);      // 0xDA
  send_command(0x12);

  send_command(SETCONTRAST);     // 0x81
  send_command(0x8F);

  send_command(SETPRECHARGE);      // 0xd9
  send_command(0xF1);

  send_command(SETVCOMDESELECT);     // 0xDB
  send_command(0x40);

  send_command(DISPLAYON);       //--turn on oled panel
  //clear_screen();           // Erase hardware memory inside the OLED controller to avoid random data in memory.
  send_buffer();
}

void send_command(uint8_t command) {
  micro_oled_transfer_buffer[0] = I2C_COMMAND;
  micro_oled_transfer_buffer[1] = command;
  i2c_transmit(I2C_ADDRESS_SA0_1 << 1, micro_oled_transfer_buffer, 2, 100);
}

void send_data(uint8_t data) {
  micro_oled_transfer_buffer[0] = I2C_DATA;
  micro_oled_transfer_buffer[1] = data;
  i2c_transmit(I2C_ADDRESS_SA0_1 << 1, micro_oled_transfer_buffer, 2, 100);
}

/** \brief Set SSD1306 page address.
    Send page address command and address to the SSD1306 OLED controller.
*/
void set_page_address(uint8_t address) {
  address = (0xB0 | address);
  send_command(address);
}

/** \brief Set SSD1306 column address.
    Send column address command and address to the SSD1306 OLED controller.
*/
void set_column_address(uint8_t address) {
  send_command( ( 0x10 | (address >> 4) ) + 0x02 );
  send_command( 0x0f & address );
}

/** \brief Clear SSD1306's memory.
    To clear GDRAM inside the LCD controller.
*/
void clear_screen(void) {
  for (int i=0;i<8; i++) {
    set_page_address(i);
    set_column_address(0);
    for (int j=0; j<0x80; j++) {
      send_data(0);
    }
  }
}

/** \brief Clear SSD1306's memory.
    To clear GDRAM inside the LCD controller.
*/
void clear_buffer(void) {
  memset(micro_oled_screen_buffer, 0, 384);
}

/** \brief Invert display.
    The PIXEL_ON color of the display will turn to PIXEL_OFF and the PIXEL_OFF will turn to PIXEL_ON.
*/
void invert_screen(bool invert) {
  if (invert) {
    send_command(INVERTDISPLAY);
  } else {
    send_command(NORMALDISPLAY);
  }
}

/** \brief Set contrast.
    OLED contract value from 0 to 255. Note: Contrast level is not very obvious.
*/
void set_contrast(uint8_t contrast) {
  send_command(SETCONTRAST);     // 0x81
  send_command(contrast);
}

/** \brief Transfer display buffer.
  Bulk move the screen buffer to the SSD1306 controller's memory so that images/graphics drawn on the screen buffer will be displayed on the OLED.
*/
void send_buffer(void) {
  uint8_t i, j;

  for (i=0; i<6; i++) {
    set_page_address(i);
    set_column_address(0);
    for (j=0;j<0x40;j++) {
      send_data(micro_oled_screen_buffer[i*0x40+j]);
    }
  }
}
/** \brief Draw pixel with color and mode.
  Draw color pixel in the screen buffer's x,y position with NORM or XOR draw mode.
*/
void draw_pixel(uint8_t x, uint8_t y, uint8_t color, uint8_t mode) {
  if ((x<0) ||  (x>=LCDWIDTH) || (y<0) || (y>=LCDHEIGHT))
    return;

  if (mode == XOR) {
    if (color == PIXEL_ON)
      micro_oled_screen_buffer[x + (y/8)*LCDWIDTH] ^= _BV((y%8));
  } else {
    if (color == PIXEL_ON)
      micro_oled_screen_buffer[x + (y/8)*LCDWIDTH] |= _BV((y%8));
    else
      micro_oled_screen_buffer[x + (y/8)*LCDWIDTH] &= ~_BV((y%8));
  }
}

/** \brief Draw line with color and mode.
Draw line using color and mode from x0,y0 to x1,y1 of the screen buffer.
*/
void draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color, uint8_t mode) {
  uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  uint8_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int8_t err = dx / 2;
  int8_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<x1; x0++) {
    if (steep) {
      draw_pixel(y0, x0, color, mode);
    } else {
      draw_pixel(x0, y0, color, mode);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

/** \brief Draw horizontal line with color and mode.
Draw horizontal line using color and mode from x,y to x+width,y of the screen buffer.
*/
void draw_line_hori(uint8_t x, uint8_t y, uint8_t width, uint8_t color, uint8_t mode) {
  draw_line(x,y,x+width,y,color,mode);
}

/** \brief Draw vertical line.
Draw vertical line using current fore color and current draw mode from x,y to x,y+height of the screen buffer.
*/
void draw_line_vert(uint8_t x, uint8_t y, uint8_t height, bool color, uint8_t mode) {
  draw_line(x,y,x,y+height,color,mode);
}

/** \brief Draw rectangle with color and mode.
Draw rectangle using color and mode from x,y to x+width,y+height of the screen buffer.
*/
void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode) {
  uint8_t tempHeight;

  draw_line_hori(x,y, width, color, mode);
  draw_line_hori(x,y+height-1, width, color, mode);

  tempHeight=height-2;

  // skip drawing vertical lines to avoid overlapping of pixel that will
  // affect XOR plot if no pixel in between horizontal lines
  if (tempHeight<1) return;

  draw_line_vert(x,y+1, tempHeight, color, mode);
  draw_line_vert(x+width-1, y+1, tempHeight, color, mode);
}

/** \brief Draw rectangle with color and mode.
Draw rectangle using color and mode from x,y to x+width,y+height of the screen buffer.
*/
void draw_rect_soft(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode) {
  uint8_t tempHeight;

  draw_line_hori(x+1,y, width-2, color, mode);
  draw_line_hori(x+1,y+height-1, width-2, color, mode);

  tempHeight=height-2;

  // skip drawing vertical lines to avoid overlapping of pixel that will
  // affect XOR plot if no pixel in between horizontal lines
  if (tempHeight<1) return;

  draw_line_vert(x,y+1, tempHeight, color, mode);
  draw_line_vert(x+width-1, y+1, tempHeight, color, mode);
}

/** \brief Draw filled rectangle with color and mode.
Draw filled rectangle using color and mode from x,y to x+width,y+height of the screen buffer.
*/
void draw_rect_filled(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode) {
  // TODO - need to optimise the memory map draw so that this function will not call pixel one by one
  for (int i=x; i<x+width;i++) {
    draw_line_vert(i,y, height, color, mode);
  }
}

/** \brief Draw filled rectangle with color and mode.
Draw filled rectangle using color and mode from x,y to x+width,y+height of the screen buffer.
*/
void draw_rect_filled_soft(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode) {
  // TODO - need to optimise the memory map draw so that this function will not call pixel one by one
  for (int i=x; i<x+width;i++) {
    if (i == x || i == (x + width - 1))
      draw_line_vert(i, y+1, height-2, color, mode);
    else
      draw_line_vert(i, y, height, color, mode);
  }
}

/** \brief Draw character with color and mode.
  Draw character c using color and draw mode at x,y.
*/
void draw_char(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t mode, uint8_t font) {
  // TODO - New routine to take font of any height, at the moment limited to font height in multiple of 8 pixels

  uint8_t rowsToDraw,row, tempC;
  uint8_t i,j,temp;
  uint16_t charPerBitmapRow,charColPositionOnBitmap,charRowPositionOnBitmap,charBitmapStartPosition;

  if ((font>=TOTALFONTS) || (font<0))
    return;

  uint8_t fontType = font;
  uint8_t fontWidth = pgm_read_byte(fonts_pointer[fontType]+0);
  uint8_t fontHeight = pgm_read_byte(fonts_pointer[fontType]+1);
  uint8_t fontStartChar = pgm_read_byte(fonts_pointer[fontType]+2);
  uint8_t fontTotalChar = pgm_read_byte(fonts_pointer[fontType]+3);
  uint16_t fontMapWidth = (pgm_read_byte(fonts_pointer[fontType]+4)*100)+pgm_read_byte(fonts_pointer[fontType]+5); // two bytes values into integer 16

  if ((c<fontStartChar) || (c>(fontStartChar+fontTotalChar-1)))   // no bitmap for the required c
    return;

  tempC=c-fontStartChar;

  // each row (in datasheet is call page) is 8 bits high, 16 bit high character will have 2 rows to be drawn
  rowsToDraw=fontHeight/8;  // 8 is LCD's page size, see SSD1306 datasheet
  if (rowsToDraw<=1) rowsToDraw=1;

  // the following draw function can draw anywhere on the screen, but SLOW pixel by pixel draw
  if (rowsToDraw==1) {
    for  (i=0;i<fontWidth+1;i++) {
      if (i==fontWidth) // this is done in a weird way because for 5x7 font, there is no margin, this code add a margin after col 5
      temp=0;
      else
      temp=pgm_read_byte(fonts_pointer[fontType]+FONTHEADERSIZE+(tempC*fontWidth)+i);

      for (j=0;j<8;j++) {     // 8 is the LCD's page height (see datasheet for explanation)
        if (temp & 0x1) {
          draw_pixel(x+i, y+j, color,mode);
        }
        else {
          draw_pixel(x+i, y+j, !color,mode);
        }

        temp >>=1;
      }
    }
    return;
  }

  // font height over 8 bit
  // take character "0" ASCII 48 as example
  charPerBitmapRow = fontMapWidth/fontWidth;  // 256/8 =32 char per row
  charColPositionOnBitmap = tempC % charPerBitmapRow;  // =16
  charRowPositionOnBitmap = (int)(tempC/charPerBitmapRow); // =1
  charBitmapStartPosition = (charRowPositionOnBitmap * fontMapWidth * (fontHeight/8)) + (charColPositionOnBitmap * fontWidth) ;

  // each row on LCD is 8 bit height (see datasheet for explanation)
  for(row=0;row<rowsToDraw;row++) {
    for (i=0; i<fontWidth;i++) {
      temp=pgm_read_byte(fonts_pointer[fontType]+FONTHEADERSIZE+(charBitmapStartPosition+i+(row*fontMapWidth)));
      for (j=0;j<8;j++) {     // 8 is the LCD's page height (see datasheet for explanation)
        if (temp & 0x1) {
          draw_pixel(x+i,y+j+(row*8), color, mode);
        }
        else {
          draw_pixel(x+i,y+j+(row*8), !color, mode);
        }
        temp >>=1;
      }
    }
  }

}

void draw_string(uint8_t x, uint8_t y, char * string, uint8_t color, uint8_t mode, uint8_t font) {

  if ((font>=TOTALFONTS) || (font<0))
    return;

  uint8_t fontType = font;
  uint8_t fontWidth = pgm_read_byte(fonts_pointer[fontType]+0);

  uint8_t cur_x = x;
  for (int i = 0; i < strlen(string); i++) {
    draw_char(cur_x, y, string[i], color, mode, font);
    cur_x += fontWidth + 1;
  }

}
