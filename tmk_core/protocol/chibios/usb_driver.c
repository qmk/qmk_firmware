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
 * @file    hal_serial_usb.c
 * @brief   Serial over USB Driver code.
 *
 * @addtogroup SERIAL_USB
 * @{
 */

#include "hal.h"

#if (HAL_USE_SERIAL_USB == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*
 * Current Line Coding.
 */
static cdc_linecoding_t linecoding = {
  {0x00, 0x96, 0x00, 0x00},             /* 38400.                           */
  LC_STOP_1, LC_PARITY_NONE, 8
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static bool sdu_start_receive(SerialUSBDriver *sdup) {
  uint8_t *buf;

  /* If the USB driver is not in the appropriate state then transactions
     must not be started.*/
  if ((usbGetDriverStateI(sdup->config->usbp) != USB_ACTIVE) ||
      (sdup->state != SDU_READY)) {
    return true;
  }

  /* Checking if there is already a transaction ongoing on the endpoint.*/
  if (usbGetReceiveStatusI(sdup->config->usbp, sdup->config->bulk_in)) {
    return true;
  }

  /* Checking if there is a buffer ready for incoming data.*/
  buf = ibqGetEmptyBufferI(&sdup->ibqueue);
  if (buf == NULL) {
    return true;
  }

  /* Buffer found, starting a new transaction.*/
  usbStartReceiveI(sdup->config->usbp, sdup->config->bulk_out,
                   buf, sdup->ibqueue.bsize - sizeof(size_t));

  return false;
}

/*
 * Interface implementation.
 */

static size_t _write(void *ip, const uint8_t *bp, size_t n) {

  return obqWriteTimeout(&((SerialUSBDriver *)ip)->obqueue, bp,
                         n, TIME_INFINITE);
}

static size_t _read(void *ip, uint8_t *bp, size_t n) {

  return ibqReadTimeout(&((SerialUSBDriver *)ip)->ibqueue, bp,
                        n, TIME_INFINITE);
}

static msg_t _put(void *ip, uint8_t b) {

  return obqPutTimeout(&((SerialUSBDriver *)ip)->obqueue, b, TIME_INFINITE);
}

static msg_t _get(void *ip) {

  return ibqGetTimeout(&((SerialUSBDriver *)ip)->ibqueue, TIME_INFINITE);
}

static msg_t _putt(void *ip, uint8_t b, systime_t timeout) {

  return obqPutTimeout(&((SerialUSBDriver *)ip)->obqueue, b, timeout);
}

static msg_t _gett(void *ip, systime_t timeout) {

  return ibqGetTimeout(&((SerialUSBDriver *)ip)->ibqueue, timeout);
}

static size_t _writet(void *ip, const uint8_t *bp, size_t n, systime_t timeout) {

  return obqWriteTimeout(&((SerialUSBDriver *)ip)->obqueue, bp, n, timeout);
}

static size_t _readt(void *ip, uint8_t *bp, size_t n, systime_t timeout) {

  return ibqReadTimeout(&((SerialUSBDriver *)ip)->ibqueue, bp, n, timeout);
}

static const struct SerialUSBDriverVMT vmt = {
  _write, _read, _put, _get,
  _putt, _gett, _writet, _readt
};

/**
 * @brief   Notification of empty buffer released into the input buffers queue.
 *
 * @param[in] bqp       the buffers queue pointer.
 */
static void ibnotify(io_buffers_queue_t *bqp) {
  SerialUSBDriver *sdup = bqGetLinkX(bqp);
  (void) sdu_start_receive(sdup);
}

/**
 * @brief   Notification of filled buffer inserted into the output buffers queue.
 *
 * @param[in] bqp       the buffers queue pointer.
 */
static void obnotify(io_buffers_queue_t *bqp) {
  size_t n;
  SerialUSBDriver *sdup = bqGetLinkX(bqp);

  /* If the USB driver is not in the appropriate state then transactions
     must not be started.*/
  if ((usbGetDriverStateI(sdup->config->usbp) != USB_ACTIVE) ||
      (sdup->state != SDU_READY)) {
    return;
  }

  /* Checking if there is already a transaction ongoing on the endpoint.*/
  if (!usbGetTransmitStatusI(sdup->config->usbp, sdup->config->bulk_in)) {
    /* Trying to get a full buffer.*/
    uint8_t *buf = obqGetFullBufferI(&sdup->obqueue, &n);
    if (buf != NULL) {
      /* Buffer found, starting a new transaction.*/
      usbStartTransmitI(sdup->config->usbp, sdup->config->bulk_in, buf, n);
    }
  }
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Serial Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void sduInit(void) {
}

/**
 * @brief   Initializes a generic full duplex driver object.
 * @details The HW dependent part of the initialization has to be performed
 *          outside, usually in the hardware initialization code.
 *
 * @param[out] sdup     pointer to a @p SerialUSBDriver structure
 *
 * @init
 */
void sduObjectInit(SerialUSBDriver *sdup) {

  sdup->vmt = &vmt;
  osalEventObjectInit(&sdup->event);
  sdup->state = SDU_STOP;
  ibqObjectInit(&sdup->ibqueue, true, sdup->ib,
                SERIAL_USB_BUFFERS_SIZE, SERIAL_USB_BUFFERS_NUMBER,
                ibnotify, sdup);
  obqObjectInit(&sdup->obqueue, true, sdup->ob,
                SERIAL_USB_BUFFERS_SIZE, SERIAL_USB_BUFFERS_NUMBER,
                obnotify, sdup);
}

/**
 * @brief   Configures and starts the driver.
 *
 * @param[in] sdup      pointer to a @p SerialUSBDriver object
 * @param[in] config    the serial over USB driver configuration
 *
 * @api
 */
void sduStart(SerialUSBDriver *sdup, const SerialUSBConfig *config) {
  USBDriver *usbp = config->usbp;

  osalDbgCheck(sdup != NULL);

  osalSysLock();
  osalDbgAssert((sdup->state == SDU_STOP) || (sdup->state == SDU_READY),
                "invalid state");
  usbp->in_params[config->bulk_in - 1U]   = sdup;
  usbp->out_params[config->bulk_out - 1U] = sdup;
  if (config->int_in > 0U) {
    usbp->in_params[config->int_in - 1U]  = sdup;
  }
  sdup->config = config;
  sdup->state = SDU_READY;
  osalSysUnlock();
}

/**
 * @brief   Stops the driver.
 * @details Any thread waiting on the driver's queues will be awakened with
 *          the message @p MSG_RESET.
 *
 * @param[in] sdup      pointer to a @p SerialUSBDriver object
 *
 * @api
 */
void sduStop(SerialUSBDriver *sdup) {
  USBDriver *usbp = sdup->config->usbp;

  osalDbgCheck(sdup != NULL);

  osalSysLock();

  osalDbgAssert((sdup->state == SDU_STOP) || (sdup->state == SDU_READY),
                "invalid state");

  /* Driver in stopped state.*/
  usbp->in_params[sdup->config->bulk_in - 1U]   = NULL;
  usbp->out_params[sdup->config->bulk_out - 1U] = NULL;
  if (sdup->config->int_in > 0U) {
    usbp->in_params[sdup->config->int_in - 1U]  = NULL;
  }
  sdup->config = NULL;
  sdup->state  = SDU_STOP;

  /* Enforces a disconnection.*/
  chnAddFlagsI(sdup, CHN_DISCONNECTED);
  ibqResetI(&sdup->ibqueue);
  obqResetI(&sdup->obqueue);
  osalOsRescheduleS();

  osalSysUnlock();
}

/**
 * @brief   USB device suspend handler.
 * @details Generates a @p CHN_DISCONNECT event and puts queues in
 *          non-blocking mode, this way the application cannot get stuck
 *          in the middle of an I/O operations.
 * @note    If this function is not called from an ISR then an explicit call
 *          to @p osalOsRescheduleS() in necessary afterward.
 *
 * @param[in] sdup      pointer to a @p SerialUSBDriver object
 *
 * @iclass
 */
void sduSuspendHookI(SerialUSBDriver *sdup) {

  chnAddFlagsI(sdup, CHN_DISCONNECTED);
  bqSuspendI(&sdup->ibqueue);
  bqSuspendI(&sdup->obqueue);
}

/**
 * @brief   USB device wakeup handler.
 * @details Generates a @p CHN_CONNECT event and resumes normal queues
 *          operations.
 *
 * @note    If this function is not called from an ISR then an explicit call
 *          to @p osalOsRescheduleS() in necessary afterward.
 *
 * @param[in] sdup      pointer to a @p SerialUSBDriver object
 *
 * @iclass
 */
void sduWakeupHookI(SerialUSBDriver *sdup) {

  chnAddFlagsI(sdup, CHN_CONNECTED);
  bqResumeX(&sdup->ibqueue);
  bqResumeX(&sdup->obqueue);
}

/**
 * @brief   USB device configured handler.
 *
 * @param[in] sdup      pointer to a @p SerialUSBDriver object
 *
 * @iclass
 */
void sduConfigureHookI(SerialUSBDriver *sdup) {

  ibqResetI(&sdup->ibqueue);
  bqResumeX(&sdup->ibqueue);
  obqResetI(&sdup->obqueue);
  bqResumeX(&sdup->obqueue);
  chnAddFlagsI(sdup, CHN_CONNECTED);
  (void) sdu_start_receive(sdup);
}

/**
 * @brief   Default requests hook.
 * @details Applications wanting to use the Serial over USB driver can use
 *          this function as requests hook in the USB configuration.
 *          The following requests are emulated:
 *          - CDC_GET_LINE_CODING.
 *          - CDC_SET_LINE_CODING.
 *          - CDC_SET_CONTROL_LINE_STATE.
 *          .
 *
 * @param[in] usbp      pointer to the @p USBDriver object
 * @return              The hook status.
 * @retval true         Message handled internally.
 * @retval false        Message not handled.
 */
bool sduRequestsHook(USBDriver *usbp) {

  if ((usbp->setup[0] & USB_RTYPE_TYPE_MASK) == USB_RTYPE_TYPE_CLASS) {
    switch (usbp->setup[1]) {
    case CDC_GET_LINE_CODING:
      usbSetupTransfer(usbp, (uint8_t *)&linecoding, sizeof(linecoding), NULL);
      return true;
    case CDC_SET_LINE_CODING:
      usbSetupTransfer(usbp, (uint8_t *)&linecoding, sizeof(linecoding), NULL);
      return true;
    case CDC_SET_CONTROL_LINE_STATE:
      /* Nothing to do, there are no control lines.*/
      usbSetupTransfer(usbp, NULL, 0, NULL);
      return true;
    default:
      return false;
    }
  }
  return false;
}

/**
 * @brief   SOF handler.
 * @details The SOF interrupt is used for automatic flushing of incomplete
 *          buffers pending in the output queue.
 *
 * @param[in] sdup      pointer to a @p SerialUSBDriver object
 *
 * @iclass
 */
void sduSOFHookI(SerialUSBDriver *sdup) {

  /* If the USB driver is not in the appropriate state then transactions
     must not be started.*/
  if ((usbGetDriverStateI(sdup->config->usbp) != USB_ACTIVE) ||
      (sdup->state != SDU_READY)) {
    return;
  }

  /* If there is already a transaction ongoing then another one cannot be
     started.*/
  if (usbGetTransmitStatusI(sdup->config->usbp, sdup->config->bulk_in)) {
    return;
  }

  /* Checking if there only a buffer partially filled, if so then it is
     enforced in the queue and transmitted.*/
  if (obqTryFlushI(&sdup->obqueue)) {
    size_t n;
    uint8_t *buf = obqGetFullBufferI(&sdup->obqueue, &n);

    osalDbgAssert(buf != NULL, "queue is empty");

    usbStartTransmitI(sdup->config->usbp, sdup->config->bulk_in, buf, n);
  }
}

/**
 * @brief   Default data transmitted callback.
 * @details The application must use this function as callback for the IN
 *          data endpoint.
 *
 * @param[in] usbp      pointer to the @p USBDriver object
 * @param[in] ep        IN endpoint number
 */
void sduDataTransmitted(USBDriver *usbp, usbep_t ep) {
  uint8_t *buf;
  size_t n;
  SerialUSBDriver *sdup = usbp->in_params[ep - 1U];

  if (sdup == NULL) {
    return;
  }

  osalSysLockFromISR();

  /* Signaling that space is available in the output queue.*/
  chnAddFlagsI(sdup, CHN_OUTPUT_EMPTY);

  /* Freeing the buffer just transmitted, if it was not a zero size packet.*/
  if (usbp->epc[ep]->in_state->txsize > 0U) {
    obqReleaseEmptyBufferI(&sdup->obqueue);
  }

  /* Checking if there is a buffer ready for transmission.*/
  buf = obqGetFullBufferI(&sdup->obqueue, &n);

  if (buf != NULL) {
    /* The endpoint cannot be busy, we are in the context of the callback,
       so it is safe to transmit without a check.*/
    usbStartTransmitI(usbp, ep, buf, n);
  }
  else if ((usbp->epc[ep]->in_state->txsize > 0U) &&
           ((usbp->epc[ep]->in_state->txsize &
            ((size_t)usbp->epc[ep]->in_maxsize - 1U)) == 0U)) {
    /* Transmit zero sized packet in case the last one has maximum allowed
       size. Otherwise the recipient may expect more data coming soon and
       not return buffered data to app. See section 5.8.3 Bulk Transfer
       Packet Size Constraints of the USB Specification document.*/
    usbStartTransmitI(usbp, ep, usbp->setup, 0);

  }
  else {
    /* Nothing to transmit.*/
  }

  osalSysUnlockFromISR();
}

/**
 * @brief   Default data received callback.
 * @details The application must use this function as callback for the OUT
 *          data endpoint.
 *
 * @param[in] usbp      pointer to the @p USBDriver object
 * @param[in] ep        OUT endpoint number
 */
void sduDataReceived(USBDriver *usbp, usbep_t ep) {
  SerialUSBDriver *sdup = usbp->out_params[ep - 1U];
  if (sdup == NULL) {
    return;
  }

  osalSysLockFromISR();

  /* Signaling that data is available in the input queue.*/
  chnAddFlagsI(sdup, CHN_INPUT_AVAILABLE);

  /* Posting the filled buffer in the queue.*/
  ibqPostFullBufferI(&sdup->ibqueue,
                     usbGetReceiveTransactionSizeX(sdup->config->usbp,
                                                   sdup->config->bulk_out));

  /* The endpoint cannot be busy, we are in the context of the callback,
     so a packet is in the buffer for sure. Trying to get a free buffer
     for the next transaction.*/
  (void) sdu_start_receive(sdup);

  osalSysUnlockFromISR();
}

/**
 * @brief   Default data received callback.
 * @details The application must use this function as callback for the IN
 *          interrupt endpoint.
 *
 * @param[in] usbp      pointer to the @p USBDriver object
 * @param[in] ep        endpoint number
 */
void sduInterruptTransmitted(USBDriver *usbp, usbep_t ep) {

  (void)usbp;
  (void)ep;
}

#endif /* HAL_USE_SERIAL_USB == TRUE */

/** @} */
