
#pragma once

#include "pio_usb_configuration.h"
#include "usb_definitions.h"

#ifdef __cplusplus
 extern "C" {
#endif

// Host functions
usb_device_t *pio_usb_host_init(const pio_usb_configuration_t *c);
int pio_usb_host_add_port(uint8_t pin_dp);
void pio_usb_host_task(void);
void pio_usb_host_stop(void);
void pio_usb_host_restart(void);

// Device functions
usb_device_t *pio_usb_device_init(const pio_usb_configuration_t *c,
                                  const usb_descriptor_buffers_t *buffers);
void pio_usb_device_task(void);

// Common functions
endpoint_t *pio_usb_get_endpoint(usb_device_t *device, uint8_t idx);
int pio_usb_get_in_data(endpoint_t *ep, uint8_t *buffer, uint8_t len);
int pio_usb_set_out_data(endpoint_t *ep, const uint8_t *buffer, uint8_t len);

#ifdef __cplusplus
 }
#endif
