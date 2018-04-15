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
 * @file    hal_serial_usb.h
 * @brief   Serial over USB Driver macros and structures.
 *
 * @addtogroup SERIAL_USB
 * @{
 */

#ifndef HAL_SERIAL_USB_H
#define HAL_SERIAL_USB_H

#if (HAL_USE_SERIAL_USB == TRUE) || defined(__DOXYGEN__)

#include "hal_usb_cdc.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    SERIAL_USB configuration options
 * @{
 */
/**
 * @brief   Serial over USB buffers size.
 * @details Configuration parameter, the buffer size must be a multiple of
 *          the USB data endpoint maximum packet size.
 * @note    The default is 256 bytes for both the transmission and receive
 *          buffers.
 */
#if !defined(SERIAL_USB_BUFFERS_SIZE) || defined(__DOXYGEN__)
#define SERIAL_USB_BUFFERS_SIZE     256
#endif

/**
 * @brief   Serial over USB number of buffers.
 * @note    The default is 2 buffers.
 */
#if !defined(SERIAL_USB_BUFFERS_NUMBER) || defined(__DOXYGEN__)
#define SERIAL_USB_BUFFERS_NUMBER   2
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if HAL_USE_USB == FALSE
#error "Serial over USB Driver requires HAL_USE_USB"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief Driver state machine possible states.
 */
typedef enum {
  SDU_UNINIT = 0,                   /**< Not initialized.                   */
  SDU_STOP = 1,                     /**< Stopped.                           */
  SDU_READY = 2                     /**< Ready.                             */
} sdustate_t;

/**
 * @brief   Structure representing a serial over USB driver.
 */
typedef struct SerialUSBDriver SerialUSBDriver;

/**
 * @brief   Serial over USB Driver configuration structure.
 * @details An instance of this structure must be passed to @p sduStart()
 *          in order to configure and start the driver operations.
 */
typedef struct {
  /**
   * @brief   USB driver to use.
   */
  USBDriver                 *usbp;
  /**
   * @brief   Bulk IN endpoint used for outgoing data transfer.
   */
  usbep_t                   bulk_in;
  /**
   * @brief   Bulk OUT endpoint used for incoming data transfer.
   */
  usbep_t                   bulk_out;
  /**
   * @brief   Interrupt IN endpoint used for notifications.
   * @note    If set to zero then the INT endpoint is assumed to be not
   *          present, USB descriptors must be changed accordingly.
   */
  usbep_t                   int_in;
} SerialUSBConfig;

/**
 * @brief   @p SerialDriver specific data.
 */
#define _serial_usb_driver_data                                             \
  _base_asynchronous_channel_data                                           \
  /* Driver state.*/                                                        \
  sdustate_t                state;                                          \
  /* Input buffers queue.*/                                                 \
  input_buffers_queue_t     ibqueue;                                        \
  /* Output queue.*/                                                        \
  output_buffers_queue_t    obqueue;                                        \
  /* Input buffer.*/                                                        \
  uint8_t                   ib[BQ_BUFFER_SIZE(SERIAL_USB_BUFFERS_NUMBER,    \
                                              SERIAL_USB_BUFFERS_SIZE)];    \
  /* Output buffer.*/                                                       \
  uint8_t                   ob[BQ_BUFFER_SIZE(SERIAL_USB_BUFFERS_NUMBER,    \
                                              SERIAL_USB_BUFFERS_SIZE)];    \
  /* End of the mandatory fields.*/                                         \
  /* Current configuration data.*/                                          \
  const SerialUSBConfig     *config;

/**
 * @brief   @p SerialUSBDriver specific methods.
 */
#define _serial_usb_driver_methods                                          \
  _base_asynchronous_channel_methods

/**
 * @extends BaseAsynchronousChannelVMT
 *
 * @brief   @p SerialDriver virtual methods table.
 */
struct SerialUSBDriverVMT {
  _serial_usb_driver_methods
};

/**
 * @extends BaseAsynchronousChannel
 *
 * @brief   Full duplex serial driver class.
 * @details This class extends @p BaseAsynchronousChannel by adding physical
 *          I/O queues.
 */
struct SerialUSBDriver {
  /** @brief Virtual Methods Table.*/
  const struct SerialUSBDriverVMT *vmt;
  _serial_usb_driver_data
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
  void sduInit(void);
  void sduObjectInit(SerialUSBDriver *sdup);
  void sduStart(SerialUSBDriver *sdup, const SerialUSBConfig *config);
  void sduStop(SerialUSBDriver *sdup);
  void sduSuspendHookI(SerialUSBDriver *sdup);
  void sduWakeupHookI(SerialUSBDriver *sdup);
  void sduConfigureHookI(SerialUSBDriver *sdup);
  bool sduRequestsHook(USBDriver *usbp);
  void sduSOFHookI(SerialUSBDriver *sdup);
  void sduDataTransmitted(USBDriver *usbp, usbep_t ep);
  void sduDataReceived(USBDriver *usbp, usbep_t ep);
  void sduInterruptTransmitted(USBDriver *usbp, usbep_t ep);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_SERIAL_USB == TRUE */

#endif /* HAL_SERIAL_USB_H */

/** @} */
