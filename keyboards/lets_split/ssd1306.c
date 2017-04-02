#include "config.h"
#include "i2c.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "print.h"
#include "lets_split.h"
#include "common/glcdfont.c"
#ifdef ADAFRUIT_BLE_ENABLE
#include "adafruit_ble.h"
#endif
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#endif
#include "sendchar.h"
#include "pincontrol.h"

//assign the right code to your layers
#define _BASE 0
#define _LOWER 8
#define _RAISE 16
#define _FNLAYER 64
#define _NUMLAY 128
#define _NLOWER 136
#define _NFNLAYER 192
#define _MOUSECURSOR 256
#define _ADJUST 65560

// Set this to 1 to help diagnose early startup problems
// when testing power-on with ble.  Turn it off otherwise,
// as the latency of printing most of the debug info messes
// with the matrix scan, causing keys to drop.
#define DEBUG_TO_SCREEN 0

// Controls the SSD1306 128x32 OLED display via i2c

#define i2cAddress 0x3C

#define DisplayHeight 32
#define DisplayWidth 128

#define FontHeight 8
#define FontWidth 6

#define MatrixRows (DisplayHeight / FontHeight)
#define MatrixCols (DisplayWidth / FontWidth)

struct CharacterMatrix {
  uint8_t display[MatrixRows][MatrixCols];
  uint8_t *cursor;
  bool dirty;
};

static struct CharacterMatrix display;
//static uint16_t last_battery_update;
//static uint32_t vbat;
//#define BatteryUpdateInterval 10000 /* milliseconds */
#define ScreenOffInterval 300000 /* milliseconds */
#if DEBUG_TO_SCREEN
static uint8_t displaying;
#endif
static uint16_t last_flush;

enum ssd1306_cmds {
  DisplayOff = 0xAE,
  DisplayOn = 0xAF,

  SetContrast = 0x81,
  DisplayAllOnResume = 0xA4,

  DisplayAllOn = 0xA5,
  NormalDisplay = 0xA6,
  InvertDisplay = 0xA7,
  SetDisplayOffset = 0xD3,
  SetComPins = 0xda,
  SetVComDetect = 0xdb,
  SetDisplayClockDiv = 0xD5,
  SetPreCharge = 0xd9,
  SetMultiPlex = 0xa8,
  SetLowColumn = 0x00,
  SetHighColumn = 0x10,
  SetStartLine = 0x40,

  SetMemoryMode = 0x20,
  ColumnAddr = 0x21,
  PageAddr = 0x22,

  ComScanInc = 0xc0,
  ComScanDec = 0xc8,
  SegRemap = 0xa0,
  SetChargePump = 0x8d,
  ExternalVcc = 0x01,
  SwitchCapVcc = 0x02,

  ActivateScroll = 0x2f,
  DeActivateScroll = 0x2e,
  SetVerticalScrollArea = 0xa3,
  RightHorizontalScroll = 0x26,
  LeftHorizontalScroll = 0x27,
  VerticalAndRightHorizontalScroll = 0x29,
  VerticalAndLeftHorizontalScroll = 0x2a,
};


// Write command sequence.
// Returns true on success.
static inline bool _send_cmd1(uint8_t cmd) {
  bool res = false;

  if (i2c_start_write(i2cAddress)) {
    xprintf("failed to start write to %d\n", i2cAddress);
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

static void matrix_clear(struct CharacterMatrix *matrix);

static void clear_display(void) {
  matrix_clear(&display);

  // Clear all of the display bits (there can be random noise
  // in the RAM on startup)
  send_cmd3(PageAddr, 0, (DisplayHeight / 8) - 1);
  send_cmd3(ColumnAddr, 0, DisplayWidth - 1);

  if (i2c_start_write(i2cAddress)) {
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

bool iota_gfx_init(void) {
  bool success = false;

  send_cmd1(DisplayOff);
  send_cmd2(SetDisplayClockDiv, 0x80);
  send_cmd2(SetMultiPlex, DisplayHeight - 1);

  send_cmd2(SetDisplayOffset, 0);


  send_cmd1(SetStartLine | 0x0);
  send_cmd2(SetChargePump, 0x14 /* Enable */);
  send_cmd2(SetMemoryMode, 0 /* horizontal addressing */);

/// Flips the display orientation 0 degrees
  send_cmd1(SegRemap | 0x1);
  send_cmd1(ComScanDec);
/*
// the following Flip the display orientation 180 degrees
  send_cmd1(SegRemap);
  send_cmd1(ComScanInc);
// end flip */
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

static void matrix_write_char_inner(struct CharacterMatrix *matrix, uint8_t c) {
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

static void matrix_write_char(struct CharacterMatrix *matrix, uint8_t c) {
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

static void matrix_write(struct CharacterMatrix *matrix, const char *data) {
  const char *end = data + strlen(data);
  while (data < end) {
    matrix_write_char(matrix, *data);
    ++data;
  }
}

void iota_gfx_write(const char *data) {
  matrix_write(&display, data);
}

static void matrix_write_P(struct CharacterMatrix *matrix, const char *data) {
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

static void matrix_clear(struct CharacterMatrix *matrix) {
  memset(matrix->display, ' ', sizeof(matrix->display));
  matrix->cursor = &matrix->display[0][0];
  matrix->dirty = true;
}

void iota_gfx_clear_screen(void) {
  matrix_clear(&display);
}

static void matrix_render(struct CharacterMatrix *matrix) {
  last_flush = timer_read();
  iota_gfx_on();
#if DEBUG_TO_SCREEN
  ++displaying;
#endif

  // Move to the home position
  send_cmd3(PageAddr, 0, MatrixRows - 1);
  send_cmd3(ColumnAddr, 0, (MatrixCols * FontWidth) - 1);

  if (i2c_start_write(i2cAddress)) {
    goto done;
  }
  if (i2c_master_write(0x40)) {
    // Data mode
    goto done;
  }

  for (uint8_t row = 0; row < MatrixRows; ++row) {
    for (uint8_t col = 0; col < MatrixCols; ++col) {
      const uint8_t *glyph = font + (matrix->display[row][col] * (FontWidth - 1));

      for (uint8_t glyphCol = 0; glyphCol < FontWidth - 1; ++glyphCol) {
        uint8_t colBits = pgm_read_byte(glyph + glyphCol);
        i2c_master_write(colBits);
      }

      // 1 column of space between chars (it's not included in the glyph)
      i2c_master_write(0);
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

static void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

static void render_status_info(void) {
#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  matrix_write_P(&matrix, PSTR("USB: "));
#ifdef PROTOCOL_LUFA
  switch (USB_DeviceState) {
    case DEVICE_STATE_Unattached:
      matrix_write_P(&matrix, PSTR("Unattached"));
      break;
    case DEVICE_STATE_Suspended:
      matrix_write_P(&matrix, PSTR("Suspended"));
      break;
    case DEVICE_STATE_Configured:
      matrix_write_P(&matrix, PSTR("Connected"));
      break;
    case DEVICE_STATE_Powered:
      matrix_write_P(&matrix, PSTR("Powered"));
      break;
    case DEVICE_STATE_Default:
      matrix_write_P(&matrix, PSTR("Default"));
      break;
    case DEVICE_STATE_Addressed:
      matrix_write_P(&matrix, PSTR("Addressed"));
      break;
    default:
      matrix_write_P(&matrix, PSTR("Invalid"));
  }
#endif

// Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below

  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(&matrix, PSTR("\n\nLayer: "));
    switch (layer_state) {
        case _BASE:
           matrix_write_P(&matrix, PSTR("Default"));
           break;
        case _RAISE:
           matrix_write_P(&matrix, PSTR("Raise"));
           break;
        case _LOWER:
           matrix_write_P(&matrix, PSTR("Lower"));
           break;
        case _ADJUST:
           matrix_write_P(&matrix, PSTR("ADJUST"));
           break;
        default:
           matrix_write(&matrix, buf);
 }
  
  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(&matrix, led);
  matrix_update(&display, &matrix);
}

void iota_gfx_task(void) {
  render_status_info();

  if (display.dirty) {
    iota_gfx_flush();
  }

  if (timer_elapsed(last_flush) > ScreenOffInterval) {
    iota_gfx_off();
  }
}
