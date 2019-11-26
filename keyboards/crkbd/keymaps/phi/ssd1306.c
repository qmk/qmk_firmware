#ifdef SSD1306OLED

#include "ssd1306.h"
#include "i2c.h"
#include <string.h>
#include "print.h"
#ifdef ADAFRUIT_BLE_ENABLE
#include "adafruit_ble.h"
#endif
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#endif
#include "sendchar.h"
#include "timer.h"

extern const unsigned char font[] PROGMEM;

//static uint16_t last_battery_update;
//static uint32_t vbat;
//#define BatteryUpdateInterval 10000 /* milliseconds */

// 'last_flush' is declared as uint16_t,
// so this must be less than 65535
#define ScreenOffInterval 60000 /* milliseconds */
static uint16_t last_flush;

static bool overwrite_mode = false;
static bool progmem_mode = false;

static bool force_dirty = true;

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
  matrix_clear(&background);

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
  background.dirty = false;

done:
  i2c_master_stop();
}

void set_overwrite_mode (bool value) {
  overwrite_mode = value;
}

void set_progmem_mode (bool value) {
  progmem_mode = value;
}

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

void matrix_reset_cursor(struct CharacterMatrix *matrix) {
  matrix->cursor = &matrix->display[0][0];
}

static inline void _matrix_maybe_scroll(struct CharacterMatrix *matrix) {
  if (matrix->cursor - &matrix->display[0][0] == sizeof(matrix->display)) {
    // We went off the end; scroll the display upwards by one line
    memmove(&matrix->display[0], &matrix->display[1],
            DisplayWidth * (MatrixRows - 1));
    matrix->cursor = &matrix->display[MatrixRows - 1][0];
    memset(matrix->cursor, 0, DisplayWidth);
  }
}

static inline void matrix_write_byte(struct CharacterMatrix *matrix, uint8_t byte) {
  *matrix->cursor = overwrite_mode ? *matrix->cursor | byte : byte;
  ++matrix->cursor;
  _matrix_maybe_scroll(matrix);
}

static inline void matrix_write_char(struct CharacterMatrix *matrix, uint8_t c) {
  const uint8_t *glyph = font + c * FontWidth;
  for (uint8_t glyphCol = 0; glyphCol < FontWidth; ++glyphCol) {
    uint8_t colBits = pgm_read_byte(glyph + glyphCol);
    matrix_write_byte(matrix, colBits);
  }
}

static inline void matrix_write_char_delimited(struct CharacterMatrix *matrix, uint8_t c, uint8_t from, uint8_t width) {
  const uint8_t *glyph = font + c * FontWidth;
  for (; width--; ++from) {
    uint8_t colBits = pgm_read_byte(glyph + from);
    matrix_write_byte(matrix, colBits);
  }
}

void matrix_newline(struct CharacterMatrix *matrix) {
  if (overwrite_mode) {
    uint8_t cursor_row = (matrix->cursor - &matrix->display[0][0]) / DisplayWidth;
    matrix->cursor = &matrix->display[cursor_row + 1][0];
    _matrix_maybe_scroll(matrix);
  } else {
    uint8_t cursor_col = (matrix->cursor - &matrix->display[0][0]) % DisplayWidth;
    while (cursor_col++ < DisplayWidth) {
      matrix_write_byte(matrix, 0);
    }
  }
}

void matrix_return(struct CharacterMatrix *matrix) {
  uint8_t cursor_row = (matrix->cursor - &matrix->display[0][0]) / DisplayWidth;
  matrix->cursor = &matrix->display[cursor_row][0];
}

void matrix_write(struct CharacterMatrix *matrix, const char *data) {
  char ch;
  while ((ch = progmem_mode ? pgm_read_byte(data) : *data)) {
    matrix_write_char(matrix, ch);
    ++data;
  }
}

void matrix_write_range(struct CharacterMatrix *matrix, const char *data, uint8_t from, uint8_t width) {
  data += from / FontWidth;
  from %= FontWidth;

  if (from) {
    if (width <= FontWidth) {
      matrix_write_char_delimited(matrix, progmem_mode ? pgm_read_byte(data) : *data, from, width);
      return;
    } else {
      matrix_write_char_delimited(matrix, progmem_mode ? pgm_read_byte(data) : *data, from, FontWidth - from);
      width -= FontWidth - from;
      data++;
    }
  }

  while (width >= FontWidth) {
    matrix_write_char(matrix, progmem_mode ? pgm_read_byte(data) : *data);
    width -= FontWidth;
    data++;
  }

  if (width) {
    matrix_write_char_delimited(matrix, progmem_mode ? pgm_read_byte(data) : *data, 0, width);
  }
}

void matrix_write_ln(struct CharacterMatrix *matrix, const char *data) {
  matrix_write(matrix, data);
  matrix_newline(matrix);
}

void matrix_write_range_ln(struct CharacterMatrix *matrix, const char *data, uint8_t from, uint8_t width) {
  matrix_write_range(matrix, data, from, width);
  matrix_newline(matrix);
}

void matrix_clear(struct CharacterMatrix *matrix) {
  memset(matrix->display, 0, sizeof(matrix->display));
  matrix->cursor = &matrix->display[0][0];
}

void iota_gfx_clear_screen(void) {
  matrix_clear(&display);
}

void matrix_push(const struct CharacterMatrix *matrix) {
  if (memcmp(display.display, matrix->display, sizeof(display.display))) {
    memcpy(display.display, matrix->display, sizeof(display.display));
    display.dirty = true;
  }
}

void matrix_push_background(const struct CharacterMatrix *matrix) {
  if (memcmp(background.display, matrix->display, sizeof(background.display))) {
    memcpy(background.display, matrix->display, sizeof(background.display));
    background.dirty = true;
  }
}

void matrix_render(struct CharacterMatrix *fg, struct CharacterMatrix *bg) {
  last_flush = timer_read();
  iota_gfx_on();

  // Move to the home position
  send_cmd3(PageAddr, 0, MatrixRows - 1);
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
      i2c_master_write(fg->display[row][col] | bg->display[row][col]);
    }
  }

  fg->dirty = false;
  bg->dirty = false;

done:
  i2c_master_stop();
}

void iota_gfx_flush(void) {
  matrix_render(&display, &background);
}

__attribute__ ((weak))
void iota_gfx_task_user(void) {
}

void iota_gfx_task(void) {
  iota_gfx_task_user();

  if (display.dirty || background.dirty || force_dirty) {
    iota_gfx_flush();
    force_dirty = false;
  }

  if (timer_elapsed(last_flush) > ScreenOffInterval) {
    iota_gfx_off();
  }
}

bool process_record_gfx(uint16_t keycode, keyrecord_t *record) {
  force_dirty = true;
  return true;
}

#endif
