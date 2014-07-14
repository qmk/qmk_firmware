#ifndef RN42_H
#define RN42_H

#include <stdbool.h>

// RN-42 CTS pin
#define CTS_INIT()  (DDRD  |=  (1<<5))
#define CTS_HI()    (PORTD |=  (1<<5))
#define CTS_LO()    (PORTD &= ~(1<<5))

host_driver_t rn42_driver;
host_driver_t rn42_config_driver;

void rn42_init(void);
void rn42_putc(uint8_t c);
void rn42_autoconnect(void);
void rn42_disconnect(void);
bool rn42_ready(void);

#endif
