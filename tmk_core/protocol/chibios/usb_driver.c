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

#include <hal.h>
#include "usb_driver.h"
#include <string.h>

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
static cdc_linecoding_t linecoding = {{0x00, 0x96, 0x00, 0x00}, /* 38400.                           */
                                      LC_STOP_1,
                                      LC_PARITY_NONE,
                                      8};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static bool qmkusb_start_receive(QMKUSBDriver *qmkusbp) {
    uint8_t *buf;

    /* If the USB driver is not in the appropriate state then transactions
       must not be started.*/
    if ((usbGetDriverStateI(qmkusbp->config->usbp) != USB_ACTIVE) || (qmkusbp->state != QMKUSB_READY)) {
        return true;
    }

    /* Checking if there is already a transaction ongoing on the endpoint.*/
    if (usbGetReceiveStatusI(qmkusbp->config->usbp, qmkusbp->config->bulk_in)) {
        return true;
    }

    /* Checking if there is a buffer ready for incoming data.*/
    buf = ibqGetEmptyBufferI(&qmkusbp->ibqueue);
    if (buf == NULL) {
        return true;
    }

    /* Buffer found, starting a new transaction.*/
    usbStartReceiveI(qmkusbp->config->usbp, qmkusbp->config->bulk_out, buf, qmkusbp->ibqueue.bsize - sizeof(size_t));

    return false;
}

/*
 * Interface implementation.
 */

static size_t _write(void *ip, const uint8_t *bp, size_t n) {
    return obqWriteTimeout(&((QMKUSBDriver *)ip)->obqueue, bp, n, TIME_INFINITE);
}

static size_t _read(void *ip, uint8_t *bp, size_t n) {
    return ibqReadTimeout(&((QMKUSBDriver *)ip)->ibqueue, bp, n, TIME_INFINITE);
}

static msg_t _put(void *ip, uint8_t b) {
    return obqPutTimeout(&((QMKUSBDriver *)ip)->obqueue, b, TIME_INFINITE);
}

static msg_t _get(void *ip) {
    return ibqGetTimeout(&((QMKUSBDriver *)ip)->ibqueue, TIME_INFINITE);
}

static msg_t _putt(void *ip, uint8_t b, sysinterval_t timeout) {
    return obqPutTimeout(&((QMKUSBDriver *)ip)->obqueue, b, timeout);
}

static msg_t _gett(void *ip, sysinterval_t timeout) {
    return ibqGetTimeout(&((QMKUSBDriver *)ip)->ibqueue, timeout);
}

static size_t _writet(void *ip, const uint8_t *bp, size_t n, sysinterval_t timeout) {
    return obqWriteTimeout(&((QMKUSBDriver *)ip)->obqueue, bp, n, timeout);
}

static size_t _readt(void *ip, uint8_t *bp, size_t n, sysinterval_t timeout) {
    return ibqReadTimeout(&((QMKUSBDriver *)ip)->ibqueue, bp, n, timeout);
}

static const struct QMKUSBDriverVMT vmt = {0, _write, _read, _put, _get, _putt, _gett, _writet, _readt};

/**
 * @brief   Notification of empty buffer released into the input buffers queue.
 *
 * @param[in] bqp       the buffers queue pointer.
 */
static void ibnotify(io_buffers_queue_t *bqp) {
    QMKUSBDriver *qmkusbp = bqGetLinkX(bqp);
    (void)qmkusb_start_receive(qmkusbp);
}

/**
 * @brief   Notification of filled buffer inserted into the output buffers queue.
 *
 * @param[in] bqp       the buffers queue pointer.
 */
static void obnotify(io_buffers_queue_t *bqp) {
    size_t        n;
    QMKUSBDriver *qmkusbp = bqGetLinkX(bqp);

    /* If the USB driver is not in the appropriate state then transactions
       must not be started.*/
    if ((usbGetDriverStateI(qmkusbp->config->usbp) != USB_ACTIVE) || (qmkusbp->state != QMKUSB_READY)) {
        return;
    }

    /* Checking if there is already a transaction ongoing on the endpoint.*/
    if (!usbGetTransmitStatusI(qmkusbp->config->usbp, qmkusbp->config->bulk_in)) {
        /* Trying to get a full buffer.*/
        uint8_t *buf = obqGetFullBufferI(&qmkusbp->obqueue, &n);
        if (buf != NULL) {
            /* Buffer found, starting a new transaction.*/
            usbStartTransmitI(qmkusbp->config->usbp, qmkusbp->config->bulk_in, buf, n);
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
void qmkusbInit(void) {}

/**
 * @brief   Initializes a generic full duplex driver object.
 * @details The HW dependent part of the initialization has to be performed
 *          outside, usually in the hardware initialization code.
 *
 * @param[out] qmkusbp     pointer to a @p QMKUSBDriver structure
 *
 * @init
 */
void qmkusbObjectInit(QMKUSBDriver *qmkusbp, const QMKUSBConfig *config) {
    qmkusbp->vmt = &vmt;
    osalEventObjectInit(&qmkusbp->event);
    qmkusbp->state = QMKUSB_STOP;
    // Note that the config uses the USB direction naming
    ibqObjectInit(&qmkusbp->ibqueue, true, config->ob, config->out_size, config->out_buffers, ibnotify, qmkusbp);
    obqObjectInit(&qmkusbp->obqueue, true, config->ib, config->in_size, config->in_buffers, obnotify, qmkusbp);
}

/**
 * @brief   Configures and starts the driver.
 *
 * @param[in] qmkusbp      pointer to a @p QMKUSBDriver object
 * @param[in] config    the serial over USB driver configuration
 *
 * @api
 */
void qmkusbStart(QMKUSBDriver *qmkusbp, const QMKUSBConfig *config) {
    USBDriver *usbp = config->usbp;

    osalDbgCheck(qmkusbp != NULL);

    osalSysLock();
    osalDbgAssert((qmkusbp->state == QMKUSB_STOP) || (qmkusbp->state == QMKUSB_READY), "invalid state");
    usbp->in_params[config->bulk_in - 1U]   = qmkusbp;
    usbp->out_params[config->bulk_out - 1U] = qmkusbp;
    if (config->int_in > 0U) {
        usbp->in_params[config->int_in - 1U] = qmkusbp;
    }
    qmkusbp->config = config;
    qmkusbp->state  = QMKUSB_READY;
    osalSysUnlock();
}

/**
 * @brief   Stops the driver.
 * @details Any thread waiting on the driver's queues will be awakened with
 *          the message @p MSG_RESET.
 *
 * @param[in] qmkusbp      pointer to a @p QMKUSBDriver object
 *
 * @api
 */
void qmkusbStop(QMKUSBDriver *qmkusbp) {
    USBDriver *usbp = qmkusbp->config->usbp;

    osalDbgCheck(qmkusbp != NULL);

    osalSysLock();

    osalDbgAssert((qmkusbp->state == QMKUSB_STOP) || (qmkusbp->state == QMKUSB_READY), "invalid state");

    /* Driver in stopped state.*/
    usbp->in_params[qmkusbp->config->bulk_in - 1U]   = NULL;
    usbp->out_params[qmkusbp->config->bulk_out - 1U] = NULL;
    if (qmkusbp->config->int_in > 0U) {
        usbp->in_params[qmkusbp->config->int_in - 1U] = NULL;
    }
    qmkusbp->config = NULL;
    qmkusbp->state  = QMKUSB_STOP;

    /* Enforces a disconnection.*/
    chnAddFlagsI(qmkusbp, CHN_DISCONNECTED);
    ibqResetI(&qmkusbp->ibqueue);
    obqResetI(&qmkusbp->obqueue);
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
 * @param[in] qmkusbp      pointer to a @p QMKUSBDriver object
 *
 * @iclass
 */
void qmkusbSuspendHookI(QMKUSBDriver *qmkusbp) {
    chnAddFlagsI(qmkusbp, CHN_DISCONNECTED);
    bqSuspendI(&qmkusbp->ibqueue);
    bqSuspendI(&qmkusbp->obqueue);
}

/**
 * @brief   USB device wakeup handler.
 * @details Generates a @p CHN_CONNECT event and resumes normal queues
 *          operations.
 *
 * @note    If this function is not called from an ISR then an explicit call
 *          to @p osalOsRescheduleS() in necessary afterward.
 *
 * @param[in] qmkusbp      pointer to a @p QMKUSBDriver object
 *
 * @iclass
 */
void qmkusbWakeupHookI(QMKUSBDriver *qmkusbp) {
    chnAddFlagsI(qmkusbp, CHN_CONNECTED);
    bqResumeX(&qmkusbp->ibqueue);
    bqResumeX(&qmkusbp->obqueue);
}

/**
 * @brief   USB device configured handler.
 *
 * @param[in] qmkusbp      pointer to a @p QMKUSBDriver object
 *
 * @iclass
 */
void qmkusbConfigureHookI(QMKUSBDriver *qmkusbp) {
    ibqResetI(&qmkusbp->ibqueue);
    bqResumeX(&qmkusbp->ibqueue);
    obqResetI(&qmkusbp->obqueue);
    bqResumeX(&qmkusbp->obqueue);
    chnAddFlagsI(qmkusbp, CHN_CONNECTED);
    (void)qmkusb_start_receive(qmkusbp);
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
bool qmkusbRequestsHook(USBDriver *usbp) {
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
 * @param[in] qmkusbp      pointer to a @p QMKUSBDriver object
 *
 * @iclass
 */
void qmkusbSOFHookI(QMKUSBDriver *qmkusbp) {
    /* If the USB driver is not in the appropriate state then transactions
       must not be started.*/
    if ((usbGetDriverStateI(qmkusbp->config->usbp) != USB_ACTIVE) || (qmkusbp->state != QMKUSB_READY)) {
        return;
    }

    /* If there is already a transaction ongoing then another one cannot be
       started.*/
    if (usbGetTransmitStatusI(qmkusbp->config->usbp, qmkusbp->config->bulk_in)) {
        return;
    }

    /* Checking if there only a buffer partially filled, if so then it is
       enforced in the queue and transmitted.*/
    if (obqTryFlushI(&qmkusbp->obqueue)) {
        size_t   n;
        uint8_t *buf = obqGetFullBufferI(&qmkusbp->obqueue, &n);

        /* For fixed size drivers, fill the end with zeros */
        if (qmkusbp->config->fixed_size) {
            memset(buf + n, 0, qmkusbp->config->in_size - n);
            n = qmkusbp->config->in_size;
        }

        osalDbgAssert(buf != NULL, "queue is empty");

        usbStartTransmitI(qmkusbp->config->usbp, qmkusbp->config->bulk_in, buf, n);
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
void qmkusbDataTransmitted(USBDriver *usbp, usbep_t ep) {
    uint8_t *     buf;
    size_t        n;
    QMKUSBDriver *qmkusbp = usbp->in_params[ep - 1U];

    if (qmkusbp == NULL) {
        return;
    }

    osalSysLockFromISR();

    /* Signaling that space is available in the output queue.*/
    chnAddFlagsI(qmkusbp, CHN_OUTPUT_EMPTY);

    /* Freeing the buffer just transmitted, if it was not a zero size packet.*/
    if (usbp->epc[ep]->in_state->txsize > 0U) {
        obqReleaseEmptyBufferI(&qmkusbp->obqueue);
    }

    /* Checking if there is a buffer ready for transmission.*/
    buf = obqGetFullBufferI(&qmkusbp->obqueue, &n);

    if (buf != NULL) {
        /* The endpoint cannot be busy, we are in the context of the callback,
           so it is safe to transmit without a check.*/
        usbStartTransmitI(usbp, ep, buf, n);
    } else if ((usbp->epc[ep]->in_state->txsize > 0U) && ((usbp->epc[ep]->in_state->txsize & ((size_t)usbp->epc[ep]->in_maxsize - 1U)) == 0U)) {
        /* Transmit zero sized packet in case the last one has maximum allowed
           size. Otherwise the recipient may expect more data coming soon and
           not return buffered data to app. See section 5.8.3 Bulk Transfer
           Packet Size Constraints of the USB Specification document.*/
        if (!qmkusbp->config->fixed_size) {
            usbStartTransmitI(usbp, ep, usbp->setup, 0);
        }

    } else {
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
void qmkusbDataReceived(USBDriver *usbp, usbep_t ep) {
    QMKUSBDriver *qmkusbp = usbp->out_params[ep - 1U];
    if (qmkusbp == NULL) {
        return;
    }

    osalSysLockFromISR();

    /* Signaling that data is available in the input queue.*/
    chnAddFlagsI(qmkusbp, CHN_INPUT_AVAILABLE);

    /* Posting the filled buffer in the queue.*/
    ibqPostFullBufferI(&qmkusbp->ibqueue, usbGetReceiveTransactionSizeX(qmkusbp->config->usbp, qmkusbp->config->bulk_out));

    /* The endpoint cannot be busy, we are in the context of the callback,
       so a packet is in the buffer for sure. Trying to get a free buffer
       for the next transaction.*/
    (void)qmkusb_start_receive(qmkusbp);

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
void qmkusbInterruptTransmitted(USBDriver *usbp, usbep_t ep) {
    (void)usbp;
    (void)ep;
}

/** @} */
