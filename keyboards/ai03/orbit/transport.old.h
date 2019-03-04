#pragma once

#include <common/matrix.h>
#define ROWS_PER_HAND (MATRIX_ROWS/2)

void transport_master_init(void);
void transport_slave_init(void);

typedef struct _Serial_s2m_buffer_t {
  // TODO: if MATRIX_COLS > 8 change to uint8_t packed_matrix[] for pack/unpack
  matrix_row_t smatrix[ROWS_PER_HAND];
} Serial_s2m_buffer_t;

typedef struct _Serial_m2s_buffer_t {
#ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#endif
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    rgblight_config_t rgblight_config; //not yet use
    //
    // When MCUs on both sides drive their respective RGB LED chains,
    // it is necessary to synchronize, so it is necessary to communicate RGB information.
    // In that case, define the RGBLIGHT_SPLIT macro.
    //
    // Otherwise, if the master side MCU drives both sides RGB LED chains,
    // there is no need to communicate.
#endif
	// Sync Layer and LED status to slave for the sake of LED indicators
	uint8_t active_layer;
	uint8_t clock_led_status;
	uint8_t slock_led_status;
	uint8_t nlock_led_status;
	
} Serial_m2s_buffer_t;

volatile Serial_s2m_buffer_t serial_s2m_buffer;
volatile Serial_m2s_buffer_t serial_m2s_buffer;

// returns false if valid data not received from slave
bool transport_master(matrix_row_t matrix[]);
void transport_slave(matrix_row_t matrix[]);
