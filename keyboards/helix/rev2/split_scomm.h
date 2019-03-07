#ifndef SPLIT_COMM_H
#define SPLIT_COMM_H

#ifdef RGBLIGHT_SPLIT
  #include <rgblight.h>
  typedef struct _rgbsync_t {
    rgblight_config_t config;
    rgblight_status_t status;
  } rgbsync_t;
#endif

#ifndef SERIAL_USE_MULTI_TRANSACTION
/* --- USE Simple API (OLD API, compatible with let's split serial.c) --- */
#include "serial.h"

#else
/* --- USE flexible API (using multi-type transaction function) --- */
// Buffers for master - slave communication
#define SERIAL_SLAVE_BUFFER_LENGTH MATRIX_ROWS/2
#define SERIAL_MASTER_BUFFER_LENGTH MATRIX_ROWS/2

extern volatile uint8_t serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH];
#ifndef RGBLIGHT_SPLIT
extern volatile uint8_t serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH];
#endif
extern uint8_t slave_buffer_change_count;

void serial_master_init(void);
void serial_slave_init(void);
int serial_update_buffers(int master_changed);
int serial_update_rgb(void);
void serial_sync_rgb(void);
#endif

#endif /* SPLIT_COMM_H */
