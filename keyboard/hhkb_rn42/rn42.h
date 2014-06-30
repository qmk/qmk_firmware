#ifndef RN42_H
#define RN42_H

#include <stdbool.h>

host_driver_t rn42_driver;
host_driver_t rn42_config_driver;

void rn42_init(void);
void rn42_putc(uint8_t c);
void rn42_autoconnect(void);
void rn42_disconnect(void);
bool rn42_ready(void);

#endif
