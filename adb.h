#ifndef ADB_H
#define ADB_H

#include <stdbool.h>

#if !(defined(ADB_PORT) && \
      defined(ADB_PIN)  && \
      defined(ADB_DDR)  && \
      defined(ADB_DATA_BIT))
#   error "ADB port setting is required in config.h"
#endif

// ADB host
void     adb_host_init(void);
bool     adb_host_psw(void);
uint16_t adb_host_kbd_recv(void);
void     adb_host_kbd_led(uint8_t led);

#endif
