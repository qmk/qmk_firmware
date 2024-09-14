// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2020 Ryan (@fauxpark)
// Copyright 2016 Fredizzimo
// Copyright 2016 Giovanni Di Sirio
// SPDX-License-Identifier: GPL-3.0-or-later OR Apache-2.0

#pragma once

#include <hal_buffers.h>
#include "usb_descriptor.h"
#include "chibios_config.h"
#include "usb_report_handling.h"
#include "string.h"
#include "timer.h"

#if HAL_USE_USB == FALSE
#    error "The USB Driver requires HAL_USE_USB"
#endif

/* USB Low Level driver specific endpoint fields */
#if !defined(usb_lld_endpoint_fields)
#    define usb_lld_endpoint_fields   \
        2,        /* IN multiplier */ \
            NULL, /* SETUP buffer (not a SETUP endpoint) */
#endif

/*
 * Implementation notes:
 *
 * USBEndpointConfig - Configured using explicit order instead of struct member name.
 *   This is due to ChibiOS hal LLD differences, which is dependent on hardware,
 *   "USBv1" devices have `ep_buffers` and "OTGv1" have `in_multiplier`.
 *   Given `USBv1/hal_usb_lld.h` marks the field as "not currently used" this code file
 *   makes the assumption this is safe to avoid littering with preprocessor directives.
 */
#define QMK_USB_ENDPOINT_IN(mode, ep_size, ep_num, _buffer_capacity, _usb_requests_cb, _report_storage) \
    {                                                                                                   \
        .usb_requests_cb = _usb_requests_cb, .report_storage = _report_storage,                         \
        .ep_config =                                                                                    \
            {                                                                                           \
                mode,                           /* EP Mode */                                           \
                NULL,                           /* SETUP packet notification callback */                \
                usb_endpoint_in_tx_complete_cb, /* IN notification callback */                          \
                NULL,                           /* OUT notification callback */                         \
                ep_size,                        /* IN maximum packet size */                            \
                0,                              /* OUT maximum packet size */                           \
                NULL,                           /* IN Endpoint state */                                 \
                NULL,                           /* OUT endpoint state */                                \
                usb_lld_endpoint_fields         /* USB driver specific endpoint fields */               \
            },                                                                                          \
        .config = {                                                                                     \
            .usbp            = &USB_DRIVER,                                                             \
            .ep              = ep_num,                                                                  \
            .buffer_capacity = _buffer_capacity,                                                        \
            .buffer_size     = ep_size,                                                                 \
            .buffer          = (_Alignas(4) uint8_t[BQ_BUFFER_SIZE(_buffer_capacity, ep_size)]){0},     \
        }                                                                                               \
    }

#if !defined(USB_ENDPOINTS_ARE_REORDERABLE)

#    define QMK_USB_ENDPOINT_OUT(mode, ep_size, ep_num, _buffer_capacity)                              \
        {                                                                                              \
            .ep_config =                                                                               \
                {                                                                                      \
                    mode,                            /* EP Mode */                                     \
                    NULL,                            /* SETUP packet notification callback */          \
                    NULL,                            /* IN notification callback */                    \
                    usb_endpoint_out_rx_complete_cb, /* OUT notification callback */                   \
                    0,                               /* IN maximum packet size */                      \
                    ep_size,                         /* OUT maximum packet size */                     \
                    NULL,                            /* IN Endpoint state */                           \
                    NULL,                            /* OUT endpoint state */                          \
                    usb_lld_endpoint_fields          /* USB driver specific endpoint fields */         \
                },                                                                                     \
            .config = {                                                                                \
                .usbp            = &USB_DRIVER,                                                        \
                .ep              = ep_num,                                                             \
                .buffer_capacity = _buffer_capacity,                                                   \
                .buffer_size     = ep_size,                                                            \
                .buffer          = (_Alignas(4) uint8_t[BQ_BUFFER_SIZE(_buffer_capacity, ep_size)]){0} \
            }                                                                                          \
        }

#else

#    define QMK_USB_ENDPOINT_IN_SHARED(mode, ep_size, ep_num, _buffer_capacity, _usb_requests_cb, _report_storage) \
        {                                                                                                          \
            .usb_requests_cb = _usb_requests_cb, .is_shared = true, .report_storage = _report_storage,             \
            .ep_config =                                                                                           \
                {                                                                                                  \
                    mode,                            /* EP Mode */                                                 \
                    NULL,                            /* SETUP packet notification callback */                      \
                    usb_endpoint_in_tx_complete_cb,  /* IN notification callback */                                \
                    usb_endpoint_out_rx_complete_cb, /* OUT notification callback */                               \
                    ep_size,                         /* IN maximum packet size */                                  \
                    ep_size,                         /* OUT maximum packet size */                                 \
                    NULL,                            /* IN Endpoint state */                                       \
                    NULL,                            /* OUT endpoint state */                                      \
                    usb_lld_endpoint_fields          /* USB driver specific endpoint fields */                     \
                },                                                                                                 \
            .config = {                                                                                            \
                .usbp            = &USB_DRIVER,                                                                    \
                .ep              = ep_num,                                                                         \
                .buffer_capacity = _buffer_capacity,                                                               \
                .buffer_size     = ep_size,                                                                        \
                .buffer          = (_Alignas(4) uint8_t[BQ_BUFFER_SIZE(_buffer_capacity, ep_size)]){0},            \
            }                                                                                                      \
        }

/* The current assumption is that there are no standalone OUT endpoints, so the
 * OUT endpoint is always initialized by the IN endpoint. */
#    define QMK_USB_ENDPOINT_OUT(mode, ep_size, ep_num, _buffer_capacity)                              \
        {                                                                                              \
            .ep_config =                                                                               \
                {                                                                                      \
                    0 /* Already defined in the IN endpoint */                                         \
                },                                                                                     \
            .config = {                                                                                \
                .usbp            = &USB_DRIVER,                                                        \
                .ep              = ep_num,                                                             \
                .buffer_capacity = _buffer_capacity,                                                   \
                .buffer_size     = ep_size,                                                            \
                .buffer          = (_Alignas(4) uint8_t[BQ_BUFFER_SIZE(_buffer_capacity, ep_size)]){0} \
            }                                                                                          \
        }

#endif

typedef struct {
    /**
     * @brief   USB driver to use.
     */
    USBDriver *usbp;

    /**
     * @brief   Endpoint used for data transfer
     */
    usbep_t ep;

    /**
     * @brief The number of buffers in the queue
     */
    size_t buffer_capacity;

    /**
     * @brief The size of each buffer in the queue, same as the endpoint size
     */
    size_t buffer_size;

    /**
     * @brief Buffer backing storage
     */
    uint8_t *buffer;
} usb_endpoint_config_t;

typedef struct {
    output_buffers_queue_t obqueue;
    USBEndpointConfig      ep_config;
    USBInEndpointState     ep_in_state;
#if defined(USB_ENDPOINTS_ARE_REORDERABLE)
    USBOutEndpointState ep_out_state;
    bool                is_shared;
#endif
    usb_endpoint_config_t config;
    usbreqhandler_t       usb_requests_cb;
    bool                  timed_out;
    usb_report_storage_t *report_storage;
} usb_endpoint_in_t;

typedef struct {
    input_buffers_queue_t ibqueue;
    USBEndpointConfig     ep_config;
    USBOutEndpointState   ep_out_state;
    usb_endpoint_config_t config;
    bool                  timed_out;
} usb_endpoint_out_t;

#ifdef __cplusplus
extern "C" {
#endif

void usb_endpoint_in_init(usb_endpoint_in_t *endpoint);
void usb_endpoint_in_start(usb_endpoint_in_t *endpoint);
void usb_endpoint_in_stop(usb_endpoint_in_t *endpoint);

bool usb_endpoint_in_send(usb_endpoint_in_t *endpoint, const uint8_t *data, size_t size, sysinterval_t timeout, bool buffered);
void usb_endpoint_in_flush(usb_endpoint_in_t *endpoint, bool padded);
bool usb_endpoint_in_is_inactive(usb_endpoint_in_t *endpoint);

void usb_endpoint_in_suspend_cb(usb_endpoint_in_t *endpoint);
void usb_endpoint_in_wakeup_cb(usb_endpoint_in_t *endpoint);
void usb_endpoint_in_configure_cb(usb_endpoint_in_t *endpoint);
void usb_endpoint_in_tx_complete_cb(USBDriver *usbp, usbep_t ep);

void usb_endpoint_out_init(usb_endpoint_out_t *endpoint);
void usb_endpoint_out_start(usb_endpoint_out_t *endpoint);
void usb_endpoint_out_stop(usb_endpoint_out_t *endpoint);

bool usb_endpoint_out_receive(usb_endpoint_out_t *endpoint, uint8_t *data, size_t size, sysinterval_t timeout);

void usb_endpoint_out_suspend_cb(usb_endpoint_out_t *endpoint);
void usb_endpoint_out_wakeup_cb(usb_endpoint_out_t *endpoint);
void usb_endpoint_out_configure_cb(usb_endpoint_out_t *endpoint);
void usb_endpoint_out_rx_complete_cb(USBDriver *usbp, usbep_t ep);

#ifdef __cplusplus
}
#endif

/** @} */
