#include <string.h>
#include <stddef.h>

#include "config.h"
#include "matrix.h"
#include "quantum.h"

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

#ifdef RGBLIGHT_ENABLE
#  include "rgblight.h"
#endif

#ifdef BACKLIGHT_ENABLE
#  include "backlight.h"
extern backlight_config_t backlight_config;
#endif

#ifdef ENCODER_ENABLE
#  include "encoder.h"
#endif

#if defined(USE_I2C) || defined(EH)

#  include "i2c_master.h"
#  include "i2c_slave.h"

typedef struct __attribute__ ((__packed__)) {
#ifdef BACKLIGHT_ENABLE
  uint8_t backlight_level;
#endif
#ifdef RGBLIGHT_ENABLE
  uint32_t rgb_settings;
#endif
#ifdef ENCODER_ENABLE
  uint8_t encoder_state[NUMBER_OF_ENCODERS];
#endif
  // Keep matrix last, we are only using this for it's offset
  uint8_t matrix_start[0];
} transport_values_t;

__attribute__ ((unused))
static transport_values_t transport_values;

#ifdef BACKLIGHT_ENABLE
#  define I2C_BACKLIT_START (uint8_t)offsetof(transport_values_t, backlight_level)
#endif

#ifdef RGBLIGHT_ENABLE
#  define I2C_RGB_START (uint8_t)offsetof(transport_values_t, rgb_settings)
#endif

#ifdef ENCODER_ENABLE
#  define I2C_ENCODER_START (uint8_t)offsetof(transport_values_t, encoder_state)
#endif

#define I2C_KEYMAP_START (uint8_t)offsetof(transport_values_t, matrix_start)

#  define TIMEOUT 100

#  ifndef SLAVE_I2C_ADDRESS
#    define SLAVE_I2C_ADDRESS 0x32
#  endif

// Get rows from other half over i2c
bool transport_master(matrix_row_t matrix[]) {
  i2c_readReg(SLAVE_I2C_ADDRESS, I2C_KEYMAP_START, (void *)matrix, ROWS_PER_HAND * sizeof(matrix_row_t), TIMEOUT);

  // write backlight info
#  ifdef BACKLIGHT_ENABLE
  uint8_t level = get_backlight_level();
  if (level != transport_values.backlight_level) {
    if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_BACKLIT_START, (void *)&level, sizeof(level), TIMEOUT) >= 0) {
      transport_values.backlight_level = level;
    }
  }
#  endif

#  ifdef RGBLIGHT_ENABLE
  uint32_t rgb = rgblight_read_dword();
  if (rgb != transport_values.rgb_settings) {
    if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_RGB_START, (void *)&rgb, sizeof(rgb), TIMEOUT) >= 0) {
      transport_values.rgb_settings = rgb;
    }
  }
#  endif

#  ifdef ENCODER_ENABLE
  i2c_readReg(SLAVE_I2C_ADDRESS, I2C_ENCODER_START, (void *)transport_values.encoder_state, sizeof(transport_values.encoder_state), TIMEOUT);
  encoder_update_raw(&transport_values.encoder_state[0]);
#  endif

  return true;
}

void transport_slave(matrix_row_t matrix[]) {
  // Copy matrix to I2C buffer
  memcpy((void*)(i2c_slave_reg + I2C_KEYMAP_START), (void *)matrix, ROWS_PER_HAND * sizeof(matrix_row_t) );

// Read Backlight Info
#  ifdef BACKLIGHT_ENABLE
  backlight_set(i2c_slave_reg[I2C_BACKLIT_START]);
#  endif

#  ifdef RGBLIGHT_ENABLE
  uint32_t rgb = *(uint32_t *)(i2c_slave_reg + I2C_RGB_START);
  // Update the RGB with the new data
  rgblight_update_dword(rgb);
#  endif

#  ifdef ENCODER_ENABLE
  encoder_state_raw((uint8_t*)(i2c_slave_reg + I2C_ENCODER_START));
#  endif
}

void transport_master_init(void) { i2c_init(); }

void transport_slave_init(void) { i2c_slave_init(SLAVE_I2C_ADDRESS); }

#else  // USE_SERIAL

#  include "serial.h"

typedef struct __attribute__ ((__packed__)) {
#  ifdef ENCODER_ENABLE
  uint8_t encoder_state[NUMBER_OF_ENCODERS];
#  endif
  // TODO: if MATRIX_COLS > 8 change to uint8_t packed_matrix[] for pack/unpack
  matrix_row_t smatrix[ROWS_PER_HAND];
} Serial_s2m_buffer_t;

typedef struct __attribute__ ((__packed__)) {
#  ifdef BACKLIGHT_ENABLE
  uint8_t           backlight_level;
#  endif
#  if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
  rgblight_config_t rgblight_config;  // not yet use
  //
  // When MCUs on both sides drive their respective RGB LED chains,
  // it is necessary to synchronize, so it is necessary to communicate RGB
  // information. In that case, define RGBLED_SPLIT with info on the number
  // of LEDs on each half.
  //
  // Otherwise, if the master side MCU drives both sides RGB LED chains,
  // there is no need to communicate.
#  endif
} Serial_m2s_buffer_t;

volatile Serial_s2m_buffer_t serial_s2m_buffer = {};
volatile Serial_m2s_buffer_t serial_m2s_buffer = {};
uint8_t volatile status0                       = 0;

SSTD_t transactions[] = {
    {
        (uint8_t *)&status0,
        sizeof(serial_m2s_buffer),
        (uint8_t *)&serial_m2s_buffer,
        sizeof(serial_s2m_buffer),
        (uint8_t *)&serial_s2m_buffer,
    },
};

void transport_master_init(void) { soft_serial_initiator_init(transactions, TID_LIMIT(transactions)); }

void transport_slave_init(void) { soft_serial_target_init(transactions, TID_LIMIT(transactions)); }

bool transport_master(matrix_row_t matrix[]) {
  if (soft_serial_transaction()) {
    return false;
  }

  // TODO:  if MATRIX_COLS > 8 change to unpack()
  for (int i = 0; i < ROWS_PER_HAND; ++i) {
    matrix[i] = serial_s2m_buffer.smatrix[i];
  }

#  ifdef BACKLIGHT_ENABLE
  // Write backlight level for slave to read
  serial_m2s_buffer.backlight_level = backlight_config.enable ? backlight_config.level : 0;
#  endif

#  if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
  static rgblight_config_t prev_rgb = {~0};
  uint32_t rgb = rgblight_read_dword();
  if (rgb != prev_rgb.raw) {
    serial_m2s_buffer.rgblight_config.raw = rgb;
    prev_rgb.raw = rgb;
  }
#  endif

#  ifdef ENCODER_ENABLE
  encoder_update_raw((uint8_t*)&serial_s2m_buffer.encoder_state);
#  endif

  return true;
}

void transport_slave(matrix_row_t matrix[]) {
  // TODO: if MATRIX_COLS > 8 change to pack()
  for (int i = 0; i < ROWS_PER_HAND; ++i) {
    serial_s2m_buffer.smatrix[i] = matrix[i];
  }
#  ifdef BACKLIGHT_ENABLE
  backlight_set(serial_m2s_buffer.backlight_level);
#  endif
#  if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
  // Update RGB config with the new data
  rgblight_update_dword(serial_m2s_buffer.rgblight_config.raw);
#  endif

#  ifdef ENCODER_ENABLE
  encoder_state_raw((uint8_t*)&serial_s2m_buffer.encoder_state);
#  endif
}

#endif
