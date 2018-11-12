#ifdef SSD1306OLED

#include "ssd1306.h"
#include "i2c.h"
#include <string.h>
#include "print.h"
#ifndef LOCAL_GLCDFONT
#include "common/glcdfont.c"
#else
#include <helixfont.h>
#endif
#ifdef ADAFRUIT_BLE_ENABLE
#include "adafruit_ble.h"
#endif
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#endif
#include "sendchar.h"
#include "timer.h"

// Set this to 1 to help diagnose early startup problems
// when testing power-on with ble.  Turn it off otherwise,
// as the latency of printing most of the debug info messes
// with the matrix scan, causing keys to drop.
#define DEBUG_TO_SCREEN 0

//static uint16_t last_battery_update;
//static uint32_t vbat;
//#define BatteryUpdateInterval 10000 /* milliseconds */
#define ScreenOffInterval 300000 /* milliseconds */
#if DEBUG_TO_SCREEN
static uint8_t displaying;
#endif
static uint16_t last_flush;

// Write command sequence.
// Returns true on success.
static inline bool _send_cmd1(uint8_t cmd) {
  bool res = false;

  if (i2c_start_write(SSD1306_ADDRESS)) {
    xprintf("failed to start write to %d\n", SSD1306_ADDRESS);
    goto done;
  }

  if (i2c_master_write(0x0 /* command byte follows */)) {
    print("failed to write control byte\n");

    goto done;
  }

  if (i2c_master_write(cmd)) {
    xprintf("failed to write command %d\n", cmd);
    goto done;
  }
  res = true;
done:
  i2c_master_stop();
  return res;
}

// Write 2-byte command sequence.
// Returns true on success
static inline bool _send_cmd2(uint8_t cmd, uint8_t opr) {
  if (!_send_cmd1(cmd)) {
    return false;
  }
  return _send_cmd1(opr);
}

// Write 3-byte command sequence.
// Returns true on success
static inline bool _send_cmd3(uint8_t cmd, uint8_t opr1, uint8_t opr2) {
  if (!_send_cmd1(cmd)) {
    return false;
  }
  if (!_send_cmd1(opr1)) {
    return false;
  }
  return _send_cmd1(opr2);
}

#define send_cmd1(c) if (!_send_cmd1(c)) {goto done;}
#define send_cmd2(c,o) if (!_send_cmd2(c,o)) {goto done;}
#define send_cmd3(c,o1,o2) if (!_send_cmd3(c,o1,o2)) {goto done;}

static void clear_display(void) {
  matrix_clear(&display);

  // Clear all of the display bits (there can be random noise
  // in the RAM on startup)
  send_cmd3(PageAddr, 0, (DisplayHeight / 8) - 1);
  send_cmd3(ColumnAddr, 0, DisplayWidth - 1);

  if (i2c_start_write(SSD1306_ADDRESS)) {
    goto done;
  }
  if (i2c_master_write(0x40)) {
    // Data mode
    goto done;
  }
  for (uint8_t row = 0; row < MatrixRows; ++row) {
    for (uint8_t col = 0; col < DisplayWidth; ++col) {
      i2c_master_write(0);
    }
  }

  display.dirty = false;

done:
  i2c_master_stop();
}

#if DEBUG_TO_SCREEN
#undef sendchar
static int8_t capture_sendchar(uint8_t c) {
  sendchar(c);
  iota_gfx_write_char(c);

  if (!displaying) {
    iota_gfx_flush();
  }
  return 0;
}
#endif

bool iota_gfx_init(bool rotate) {
  bool success = false;

  i2c_master_init();
  send_cmd1(DisplayOff);
  send_cmd2(SetDisplayClockDiv, 0x80);
  send_cmd2(SetMultiPlex, DisplayHeight - 1);

  send_cmd2(SetDisplayOffset, 0);


  send_cmd1(SetStartLine | 0x0);
  send_cmd2(SetChargePump, 0x14 /* Enable */);
  send_cmd2(SetMemoryMode, 0 /* horizontal addressing */);

  if(rotate){
    // the following Flip the display orientation 180 degrees
    send_cmd1(SegRemap);
    send_cmd1(ComScanInc);
  }else{
    // Flips the display orientation 0 degrees
    send_cmd1(SegRemap | 0x1);
    send_cmd1(ComScanDec);
  }

  send_cmd2(SetComPins, 0x2);
  send_cmd2(SetContrast, 0x8f);
  send_cmd2(SetPreCharge, 0xf1);
  send_cmd2(SetVComDetect, 0x40);
  send_cmd1(DisplayAllOnResume);
  send_cmd1(NormalDisplay);
  send_cmd1(DeActivateScroll);
  send_cmd1(DisplayOn);

  send_cmd2(SetContrast, 0); // Dim

  clear_display();

  success = true;

  iota_gfx_flush();

#if DEBUG_TO_SCREEN
  print_set_sendchar(capture_sendchar);
#endif

done:
  return success;
}

bool iota_gfx_off(void) {
  bool success = false;

  send_cmd1(DisplayOff);
  success = true;

done:
  return success;
}

bool iota_gfx_on(void) {
  bool success = false;

  send_cmd1(DisplayOn);
  success = true;

done:
  return success;
}

void matrix_write_char_inner(struct CharacterMatrix *matrix, uint8_t c) {
  *matrix->cursor = c;
  ++matrix->cursor;

  if (matrix->cursor - &matrix->display[0][0] == sizeof(matrix->display)) {
    // We went off the end; scroll the display upwards by one line
    memmove(&matrix->display[0], &matrix->display[1],
            MatrixCols * (MatrixRows - 1));
    matrix->cursor = &matrix->display[MatrixRows - 1][0];
    memset(matrix->cursor, ' ', MatrixCols);
  }
}

void matrix_write_char(struct CharacterMatrix *matrix, uint8_t c) {
  matrix->dirty = true;

  if (c == '\n') {
    // Clear to end of line from the cursor and then move to the
    // start of the next line
    uint8_t cursor_col = (matrix->cursor - &matrix->display[0][0]) % MatrixCols;

    while (cursor_col++ < MatrixCols) {
      matrix_write_char_inner(matrix, ' ');
    }
    return;
  }

  matrix_write_char_inner(matrix, c);
}

void iota_gfx_write_char(uint8_t c) {
  matrix_write_char(&display, c);
}

void matrix_write(struct CharacterMatrix *matrix, const char *data) {
  const char *end = data + strlen(data);
  while (data < end) {
    matrix_write_char(matrix, *data);
    ++data;
  }
}

void iota_gfx_write(const char *data) {
  matrix_write(&display, data);
}

void matrix_write_P(struct CharacterMatrix *matrix, const char *data) {
  while (true) {
    uint8_t c = pgm_read_byte(data);
    if (c == 0) {
      return;
    }
    matrix_write_char(matrix, c);
    ++data;
  }
}

void iota_gfx_write_P(const char *data) {
  matrix_write_P(&display, data);
}

void matrix_clear(struct CharacterMatrix *matrix) {
  memset(matrix->display, ' ', sizeof(matrix->display));
  matrix->cursor = &matrix->display[0][0];
  matrix->dirty = true;
}

void iota_gfx_clear_screen(void) {
  matrix_clear(&display);
}

void matrix_render(struct CharacterMatrix *matrix) {
  last_flush = timer_read();
  iota_gfx_on();
#if DEBUG_TO_SCREEN
  ++displaying;
#endif

  // Move to the home position
  send_cmd3(PageAddr, 0, MatrixRows - 1);
  send_cmd3(ColumnAddr, 0, (MatrixCols * FontWidth) - 1);

  if (i2c_start_write(SSD1306_ADDRESS)) {
    goto done;
  }
  if (i2c_master_write(0x40)) {
    // Data mode
    goto done;
  }

  for (uint8_t row = 0; row < MatrixRows; ++row) {
    for (uint8_t col = 0; col < MatrixCols; ++col) {
      const uint8_t *glyph = font + (matrix->display[row][col] * FontWidth);

      for (uint8_t glyphCol = 0; glyphCol < FontWidth; ++glyphCol) {
        uint8_t colBits = pgm_read_byte(glyph + glyphCol);
        i2c_master_write(colBits);
      }

      // 1 column of space between chars (it's not included in the glyph)
      //i2c_master_write(0);
    }
  }

  matrix->dirty = false;

done:
  i2c_master_stop();
#if DEBUG_TO_SCREEN
  --displaying;
#endif
}

void iota_gfx_flush(void) {
  matrix_render(&display);
}

__attribute__ ((weak))
void iota_gfx_task_user(void) {
}

void iota_gfx_task(void) {
  iota_gfx_task_user();

  if (display.dirty) {
    iota_gfx_flush();
  }

  if (timer_elapsed(last_flush) > ScreenOffInterval) {
    iota_gfx_off();
  }
}
#endif
