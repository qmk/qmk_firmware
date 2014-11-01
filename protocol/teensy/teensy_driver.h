#include "host_driver.h"

#ifndef TEENSY_DRIVER_H
#define TEENSY_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

extern host_driver_t teensy_driver;

void teensy_driver_init(void);

#ifdef __cplusplus
}
#endif

#endif // TEENSY_DRIVER_H
