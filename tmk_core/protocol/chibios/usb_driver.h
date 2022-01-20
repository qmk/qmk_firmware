/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    usb_driver.h
 * @brief   Usb driver suitable for both packet and serial formats
 *
 * @addtogroup SERIAL_USB
 * @{
 */

#pragma once

#include <hal_usb_cdc.h>

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if HAL_USE_USB == FALSE
#    error "The USB Driver requires HAL_USE_USB"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief Driver state machine possible states.
 */
typedef enum {
    QMKUSB_UNINIT = 0, /**< Not initialized.                   */
    QMKUSB_STOP   = 1, /**< Stopped.                           */
    QMKUSB_READY  = 2  /**< Ready.                             */
} qmkusbstate_t;

/**
 * @brief   Structure representing a serial over USB driver.
 */
typedef struct QMKUSBDriver QMKUSBDriver;

/**
 * @brief   Serial over USB Driver configuration structure.
 * @details An instance of this structure must be passed to @p sduStart()
 *          in order to configure and start the driver operations.
 */
typedef struct {
    /**
     * @brief   USB driver to use.
     */
    USBDriver *usbp;
    /**
     * @brief   Bulk IN endpoint used for outgoing data transfer.
     */
    usbep_t bulk_in;
    /**
     * @brief   Bulk OUT endpoint used for incoming data transfer.
     */
    usbep_t bulk_out;
    /**
     * @brief   Interrupt IN endpoint used for notifications.
     * @note    If set to zero then the INT endpoint is assumed to be not
     *          present, USB descriptors must be changed accordingly.
     */
    usbep_t int_in;

    /**
     * @brief The number of buffers in the queues
     */
    size_t in_buffers;
    size_t out_buffers;

    /**
     * @brief The size of each buffer in the queue, typically the same as the endpoint size
     */
    size_t in_size;
    size_t out_size;

    /**
     * @brief Always send full buffers in_size (the rest is filled with zeroes)
     */
    bool fixed_size;

    /* Input buffer
     * @note needs to be initialized with a memory buffer of the right size
     */
    uint8_t *ib;
    /* Output buffer
     * @note needs to be initialized with a memory buffer of the right size
     */
    uint8_t *ob;
} QMKUSBConfig;

/**
 * @brief   @p SerialDriver specific data.
 */
#define _qmk_usb_driver_data                           \
    _base_asynchronous_channel_data /* Driver state.*/ \
        qmkusbstate_t state;                           \
    /* Input buffers queue.*/                          \
    input_buffers_queue_t ibqueue;                     \
    /* Output queue.*/                                 \
    output_buffers_queue_t obqueue;                    \
    /* End of the mandatory fields.*/                  \
    /* Current configuration data.*/                   \
    const QMKUSBConfig *config;

/**
 * @brief   @p SerialUSBDriver specific methods.
 */
#define _qmk_usb_driver_methods _base_asynchronous_channel_methods

/**
 * @extends BaseAsynchronousChannelVMT
 *
 * @brief   @p SerialDriver virtual methods table.
 */
struct QMKUSBDriverVMT {
    _qmk_usb_driver_methods
};

/**
 * @extends BaseAsynchronousChannel
 *
 * @brief   Full duplex serial driver class.
 * @details This class extends @p BaseAsynchronousChannel by adding physical
 *          I/O queues.
 */
struct QMKUSBDriver {
    /** @brief Virtual Methods Table.*/
    const struct QMKUSBDriverVMT *vmt;
    _qmk_usb_driver_data
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void qmkusbInit(void);
void qmkusbObjectInit(QMKUSBDriver *qmkusbp, const QMKUSBConfig *config);
void qmkusbStart(QMKUSBDriver *qmkusbp, const QMKUSBConfig *config);
void qmkusbStop(QMKUSBDriver *qmkusbp);
void qmkusbSuspendHookI(QMKUSBDriver *qmkusbp);
void qmkusbWakeupHookI(QMKUSBDriver *qmkusbp);
void qmkusbConfigureHookI(QMKUSBDriver *qmkusbp);
bool qmkusbRequestsHook(USBDriver *usbp);
void qmkusbSOFHookI(QMKUSBDriver *qmkusbp);
void qmkusbDataTransmitted(USBDriver *usbp, usbep_t ep);
void qmkusbDataReceived(USBDriver *usbp, usbep_t ep);
void qmkusbInterruptTransmitted(USBDriver *usbp, usbep_t ep);
#ifdef __cplusplus
}
#endif

/** @} */
