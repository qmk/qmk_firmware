/*
Copyright 2019 Ryan Caltabiano <https://github.com/XScorpion2>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ssd1306.h"
#include "i2c_master.h"
#include OLED_FONT_FILE
#include "timer.h"
#include "print.h"

#include <string.h>

// Used commands from spec sheet: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
// Fundamental Commands
#define CONTRAST                0x81
#define DISPLAY_ALL_ON          0xA5
#define DISPLAY_ALL_ON_RESUME   0xA4
#define NORMAL_DISPLAY          0xA6
#define DISPLAY_ON              0xAF
#define DISPLAY_OFF             0xAE

// Scrolling Commands
#define ACTIVATE_SCROLL         0x2F
#define DEACTIVATE_SCROLL       0x2E
#define SCROLL_RIGHT            0x26
#define SCROLL_LEFT             0x27
#define SCROLL_RIGHT_UP         0x29
#define SCROLL_LEFT_UP          0x2A

// Addressing Setting Commands
#define MEMORY_MODE             0x20
#define COLUMN_ADDR             0x21
#define PAGE_ADDR               0x22

// Hardware Configuration Commands
#define DISPLAY_START_LINE      0x40
#define SEGMENT_REMAP           0xA0
#define SEGMENT_REMAP_INV       0xA1
#define MULTIPLEX_RATIO         0xA8
#define COM_SCAN_INC            0xC0
#define COM_SCAN_DEC            0xC8
#define DISPLAY_OFFSET          0xD3
#define COM_PINS                0xDA

// Timing & Driving Commands
#define DISPLAY_CLOCK           0xD5
#define PRE_CHARGE_PERIOD       0xD9
#define VCOM_DETECT             0xDB

// Charge Pump Commands
#define CHARGE_PUMP             0x8D

// Misc defines
#define SSD1306_ADDRESS (0x3C << 1)
#define OLED_MATRIX_SIZE ((OLED_DISPLAY_HEIGHT / 8) * OLED_DISPLAY_WIDTH)
#define OLED_TIMEOUT 60000
#define OLED_BLOCK_COUNT 8
#define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
// TODO: block count is 8 because uint8_t is used, make this adjustable

// i2c defines
#define I2C_CMD 0x00
#define I2C_DATA 0x40
#define I2C_TIMEOUT 100
#define I2C_SEND_P(mode, data) i2c_writeReg_P(SSD1306_ADDRESS, mode, &data[0], sizeof(data), I2C_TIMEOUT)
#define I2C_SEND(mode, data) i2c_writeReg(SSD1306_ADDRESS, mode, &data[0], sizeof(data), I2C_TIMEOUT)
#define I2C_SEND_SIZE(mode, data, size) i2c_writeReg(SSD1306_ADDRESS, mode, data, size, I2C_TIMEOUT)

// Display buffer's is the same as the OLED memory layout
// this is so we don't end up with rounding errors with
// parts of the display unusable or don't get cleared correctly
// and also allows for drawing & inverting
static uint8_t  display_buffer[OLED_MATRIX_SIZE];
static uint8_t* display_cursor;
static uint8_t  display_dirty = 0;
static bool     display_initialized = false;
static bool     display_active = false;
static bool     display_scrolling = false;
static uint16_t last_activity;

// identical to i2c_writeReg, but for PROGMEM since all initialization is in PROGMEM arrays currently
// probably should move this into i2c_master...
static i2c_status_t i2c_writeReg_P(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout) {
  i2c_status_t status = i2c_start(devaddr | 0x00, timeout);
  if (status) return status;

  status = i2c_write(regaddr, timeout);
  if (status) return status;

  for (uint16_t i = 0; i < length; i++) {
    status = i2c_write(pgm_read_byte(data++), timeout);
    if (status) return status;
  }

  status = i2c_stop(timeout);
  if (status) return status;

  return I2C_STATUS_SUCCESS;
}

// Flips the rendering bits for a character at the current cursor position
static void InvertCharacter(uint8_t *cursor)
{
  const uint8_t *end = cursor + OLED_FONT_WIDTH;
  while (cursor < end) {
    *cursor = ~(*cursor);
    cursor++;
  }
}

bool oled_init(bool flip180) {
  i2c_init();
  static const uint8_t PROGMEM display_setup1[] = {
    DISPLAY_OFF,
    DISPLAY_CLOCK, 0x80,
    MULTIPLEX_RATIO, OLED_DISPLAY_HEIGHT - 1,
    DISPLAY_OFFSET, 0x00,
    DISPLAY_START_LINE | 0x00,
    CHARGE_PUMP, 0x14,
    MEMORY_MODE, 0x00, };
  if (I2C_SEND_P(I2C_CMD, display_setup1) != I2C_STATUS_SUCCESS) {
    print("oled_init cmd set 1 failed\n");
    return false;
  }

  if (!flip180) {
    static const uint8_t PROGMEM display_normal[] = {
      SEGMENT_REMAP_INV,
      COM_SCAN_DEC };
    if (I2C_SEND_P(I2C_CMD, display_normal) != I2C_STATUS_SUCCESS) {
      print("oled_init cmd normal rotation failed\n");
      return false;
    }
  } else {
    static const uint8_t PROGMEM display_flipped[] = {
      SEGMENT_REMAP,
      COM_SCAN_INC };
    if (I2C_SEND_P(I2C_CMD, display_flipped) != I2C_STATUS_SUCCESS) {
      print("display_flipped failed\n");
      return false;
    }
  }

  static const uint8_t PROGMEM display_setup2[] = {
    COM_PINS, 0x02,
    CONTRAST, 0x8F,
    PRE_CHARGE_PERIOD, 0xF1,
    VCOM_DETECT, 0x40,
    DISPLAY_ALL_ON_RESUME,
    NORMAL_DISPLAY,
    DEACTIVATE_SCROLL,
    DISPLAY_ON };
  if (I2C_SEND_P(I2C_CMD, display_setup2) != I2C_STATUS_SUCCESS) {
    print("display_setup2 failed\n");
    return false;
  }

  oled_clear();
  display_initialized = true;
  display_active = true;
  display_scrolling = false;
  return true;
}

void oled_clear(void) {
  memset(display_buffer, 0, sizeof(display_buffer));
  display_cursor = &display_buffer[0];
  display_dirty = 0xFF; // TODO: make this max value of defined type
}

void oled_render(void) {
  // Do we have work to do?
  if (!display_dirty || display_scrolling) {
    return;
  }

  // Find first dirty block
  uint8_t update_start = 0;
  while(!(display_dirty & (1 << update_start))) { ++update_start; }

  // Set column & page position
  static uint8_t display_start[] = {
    COLUMN_ADDR, 0, OLED_DISPLAY_WIDTH - 1,
    PAGE_ADDR, 0, OLED_DISPLAY_HEIGHT / 8 - 1 };
  display_start[1] = (OLED_BLOCK_SIZE * update_start) % OLED_DISPLAY_WIDTH;
  display_start[4] = (OLED_BLOCK_SIZE * update_start) / OLED_DISPLAY_WIDTH;

  // Send column & page position
  if (I2C_SEND(I2C_CMD, display_start)  != I2C_STATUS_SUCCESS ) {
    print("oled_render offset command failed\n");
    return;
  }

  // Send render data chunk
  if (I2C_SEND_SIZE(I2C_DATA, &display_buffer[OLED_BLOCK_SIZE * update_start], OLED_BLOCK_SIZE) != I2C_STATUS_SUCCESS) {
    print("oled_render data failed\n");
    return;
  }

  // Turn on display if it is off
  oled_on();

  // Clear dirty flag
  display_dirty &= ~(1 << update_start);
}

void oled_set_cursor(uint8_t col, uint8_t line) {
  uint16_t index = line * OLED_DISPLAY_WIDTH + col * OLED_FONT_WIDTH;

  // Out of bounds?
  if (index >= OLED_MATRIX_SIZE) {
    index = 0;
  }

  display_cursor = &display_buffer[index];
}

void oled_advance_page(bool clearPageRemainder) {
  uint16_t index = display_cursor - &display_buffer[0];
  uint8_t remaining = (OLED_DISPLAY_WIDTH - (index % OLED_DISPLAY_WIDTH));

  if (clearPageRemainder) {
    // Remaining Char count
    remaining = remaining / OLED_FONT_WIDTH;

    // Write empty character until next line
    while (remaining--)
      oled_write_char(' ', false);
  } else {
    // Next page index out of bounds?
    if (index + remaining >= OLED_MATRIX_SIZE) {
      index = 0;
      remaining = 0;
    }

    display_cursor = &display_buffer[index + remaining];
  }
}

void oled_advance_char(void) {
  uint16_t nextIndex = display_cursor - &display_buffer[0] + OLED_FONT_WIDTH;
  uint8_t remainingSpace = OLED_DISPLAY_WIDTH - (nextIndex % OLED_DISPLAY_WIDTH);

  // Do we have enough space on the current line for the next character
  if (remainingSpace < OLED_FONT_WIDTH) {
    nextIndex += remainingSpace;
  }

  // Did we go out of bounds
  if (nextIndex >= OLED_MATRIX_SIZE) {
    nextIndex = 0;
  }

  // Update cursor position
  display_cursor = &display_buffer[nextIndex];
}

// Main handler that writes character data to the display buffer
void oled_write_char(const char data, bool invert) {
  // Advance to the next line if newline
  if (data == '\n') {
    // Old source wrote ' ' until end of line...
    oled_advance_page(true);
    return;
  }

  // copy the current render buffer to check for dirty after
  static uint8_t oled_temp_buffer[OLED_FONT_WIDTH];
  memcpy(&oled_temp_buffer, display_cursor, OLED_FONT_WIDTH);

  // set the reder buffer data
  if (data < OLED_FONT_START || data > OLED_FONT_END) {
    memset(display_cursor, 0x00, OLED_FONT_WIDTH);
  } else {
    const uint8_t *glyph = &font[(data - OLED_FONT_START) * OLED_FONT_WIDTH];
    memcpy_P(display_cursor, glyph, OLED_FONT_WIDTH);
  }

  // Invert if needed
  if (invert) {
    InvertCharacter(display_cursor);
  }

  // Dirty check
  if (memcmp(&oled_temp_buffer, display_cursor, OLED_FONT_WIDTH)) {
    display_dirty |= (1 << ((display_cursor - &display_buffer[0]) / OLED_BLOCK_SIZE));
  }

  // Finally move to the next char
  oled_advance_char();
}

void oled_write(const char *data, bool invert) {
  const char *end = data + strlen(data);
  while (data < end) {
    oled_write_char(*data, invert);
    data++;
  }
}

void oled_write_ln(const char *data, bool invert) {
  oled_write(data, invert);
  oled_advance_page(true);
}

void oled_write_P(const char *data, bool invert) {
  uint8_t c = pgm_read_byte(data);
  while (c != 0) {
    oled_write_char(c, invert);
    c = pgm_read_byte(++data);
  }
}

void oled_write_ln_P(const char *data, bool invert) {
  oled_write_P(data, invert);
  oled_advance_page(true);
}

bool oled_ready(void) {
  return display_initialized;
}

bool oled_on(void) {
  last_activity = timer_read();

  static const uint8_t PROGMEM display_on[] = { DISPLAY_ON };
  if (!display_active) {
    if (I2C_SEND_P(I2C_CMD, display_on) != I2C_STATUS_SUCCESS) {
      print("oled_on cmd failed\n");
      return display_active;
    }
    display_active = true;
  }
  return display_active;
}

bool oled_off(void) {
  static const uint8_t PROGMEM display_off[] = { DISPLAY_OFF };
  if (display_active) {
    if (I2C_SEND_P(I2C_CMD, display_off) != I2C_STATUS_SUCCESS) {
      print("oled_off cmd failed\n");
      return display_active;
    }
    display_active = false;
  }
  return !display_active;
}

bool oled_scroll_right(void) {
  // Dont enable scrolling if we need to update the display
  // This prevents scrolling of bad data from starting the scroll too early after init
  if (!display_dirty && !display_scrolling) {
    static const uint8_t PROGMEM display_scroll_right[] = {
      SCROLL_RIGHT, 0x00, 0x00, 0x00, 0x0F, 0x00, 0xFF, ACTIVATE_SCROLL };
    if (I2C_SEND_P(I2C_CMD, display_scroll_right) != I2C_STATUS_SUCCESS) {
      print("oled_scroll_right cmd failed\n");
      return display_scrolling;
    }
    display_scrolling = true;
  }
  return display_scrolling;
}

bool oled_scroll_left(void) {
  // Dont enable scrolling if we need to update the display
  // This prevents scrolling of bad data from starting the scroll too early after init
  if (!display_dirty && !display_scrolling) {
    static const uint8_t PROGMEM display_scroll_left[] = {
      SCROLL_LEFT, 0x00, 0x00, 0x00, 0x0F, 0x00, 0xFF, ACTIVATE_SCROLL };
    if (I2C_SEND_P(I2C_CMD, display_scroll_left) != I2C_STATUS_SUCCESS) {
      print("oled_scroll_left cmd failed\n");
      return display_scrolling;
    }
    display_scrolling = true;
  }
  return display_scrolling;
}

bool oled_scroll_off(void) {
  if (display_scrolling) {
    static const uint8_t PROGMEM display_scroll_off[] = { DEACTIVATE_SCROLL };
    if (I2C_SEND_P(I2C_CMD, display_scroll_off) != I2C_STATUS_SUCCESS) {
      print("oled_scroll_off cmd failed\n");
      return display_scrolling;
    }
    display_scrolling = false;
  }
  return !display_scrolling;
}

void oled_task(void) {
  if (!oled_ready()) {
    return;
  }

  oled_set_cursor(0, 0);

#ifdef SSD1306OLED
  iota_gfx_task_user();
#endif
  oled_task_user();

  // Smart render system, no need to check for dirty
  oled_render();

  // Display timeout check
  if (display_active && timer_elapsed(last_activity) > OLED_TIMEOUT) {
    oled_off();
  }
}

__attribute__ ((weak))
void oled_task_user(void) {
}

#ifdef SSD1306OLED
__attribute__ ((weak))
void iota_gfx_task_user(void) {
}
#endif
