#ifndef BLE_H
#define BLE_H

#include <stdbool.h>
#include "host_driver.h"
#include "host.h"


typedef union {
  uint32_t raw;
  struct {
    bool init : 1;
  };
} user_config_t;

user_config_t ble_config;

host_driver_t bluefruit_driver;
host_driver_t null_driver;

void send_str(const char *str);
void usart_init(void);
void module_reset(void);

#endif