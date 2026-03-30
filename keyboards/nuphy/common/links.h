#pragma once

#include <stdint.h>
#include <stdbool.h>

extern host_driver_t *m_host_driver;
extern uint8_t        host_mode;

void switch_dev_link(uint8_t mode);
