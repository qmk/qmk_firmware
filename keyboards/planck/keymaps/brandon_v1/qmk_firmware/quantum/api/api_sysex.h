#ifndef _API_SYSEX_H_
#define _API_SYSEX_H_

#include "api.h"

void send_bytes_sysex(uint8_t message_type, uint8_t data_type, uint8_t * bytes, uint16_t length);

#define SEND_BYTES(mt, dt, b, l) send_bytes_sysex(mt, dt, b, l)

#endif