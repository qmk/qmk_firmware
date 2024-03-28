// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2021 Purdea Andrei
// Copyright 2021 Michael Stapelberg
// Copyright 2020 Ryan (@fauxpark)
// Copyright 2016 Fredizzimo
// Copyright 2016 Giovanni Di Sirio
// SPDX-License-Identifier: GPL-3.0-or-later OR Apache-2.0

#include <hal.h>
#include <string.h>

#include "usb_driver.h"
#include "util.h"

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static void usb_start_receive(usb_endpoint_out_t *endpoint) {
    /* If the USB driver is not in the appropriate state then transactions
       must not be started.*/
    if ((usbGetDriverStateI(endpoint->config.usbp) != USB_ACTIVE)) {
        return;
    }

    /* Checking if there is already a transaction ongoing on the endpoint.*/
    if (usbGetReceiveStatusI(endpoint->config.usbp, endpoint->config.ep)) {
        return;
    }

    /* Checking if there is a buffer ready for incoming data.*/
    uint8_t *buffer = ibqGetEmptyBufferI(&endpoint->ibqueue);
    if (buffer == NULL) {
        return;
    }

    /* Buffer found, starting a new transaction.*/
    usbStartReceiveI(endpoint->config.usbp, endpoint->config.ep, buffer, endpoint->ibqueue.bsize - sizeof(size_t));
}

/**
 * @brief   Notification of empty buffer released into the input buffers queue.
 *
 * @param[in] bqp       the buffers queue pointer.
 */
static void ibnotify(io_buffers_queue_t *bqp) {
    usb_endpoint_out_t *endpoint = bqGetLinkX(bqp);
    usb_start_receive(endpoint);
}

/**
 * @brief   Notification of filled buffer inserted into the output buffers queue.
 *
 * @param[in] bqp       the buffers queue pointer.
 */
static void obnotify(io_buffers_queue_t *bqp) {
    usb_endpoint_in_t *endpoint = bqGetLinkX(bqp);

    /* If the USB endpoint is not in the appropriate state then transactions
       must not be started.*/
    if ((usbGetDriverStateI(endpoint->config.usbp) != USB_ACTIVE)) {
        return;
    }

    /* Checking if there is already a transaction ongoing on the endpoint.*/
    if (!usbGetTransmitStatusI(endpoint->config.usbp, endpoint->config.ep)) {
        /* Trying to get a full buffer.*/
        size_t   n;
        uint8_t *buffer = obqGetFullBufferI(&endpoint->obqueue, &n);
        if (buffer != NULL) {
            /* Buffer found, starting a new transaction.*/
            usbStartTransmitI(endpoint->config.usbp, endpoint->config.ep, buffer, n);
        }
    }
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

void usb_endpoint_in_init(usb_endpoint_in_t *endpoint) {
    usb_endpoint_config_t *config = &endpoint->config;
    endpoint->ep_config.in_state  = &endpoint->ep_in_state;

#if defined(USB_ENDPOINTS_ARE_REORDERABLE)
    if (endpoint->is_shared) {
        endpoint->ep_config.out_state = &endpoint->ep_out_state;
    }
#endif
    obqObjectInit(&endpoint->obqueue, true, config->buffer, config->buffer_size, config->buffer_capacity, obnotify, endpoint);
}

void usb_endpoint_out_init(usb_endpoint_out_t *endpoint) {
    usb_endpoint_config_t *config = &endpoint->config;
    endpoint->ep_config.out_state = &endpoint->ep_out_state;
    ibqObjectInit(&endpoint->ibqueue, true, config->buffer, config->buffer_size, config->buffer_capacity, ibnotify, endpoint);
}

void usb_endpoint_in_start(usb_endpoint_in_t *endpoint) {
    osalDbgCheck(endpoint != NULL);

    osalSysLock();
    osalDbgAssert((usbGetDriverStateI(endpoint->config.usbp) == USB_STOP) || (usbGetDriverStateI(endpoint->config.usbp) == USB_READY), "invalid state");
    endpoint->config.usbp->in_params[endpoint->config.ep - 1U] = endpoint;
    endpoint->timed_out                                        = false;
    osalSysUnlock();
}

void usb_endpoint_out_start(usb_endpoint_out_t *endpoint) {
    osalDbgCheck(endpoint != NULL);

    osalSysLock();
    osalDbgAssert((usbGetDriverStateI(endpoint->config.usbp) == USB_STOP) || (usbGetDriverStateI(endpoint->config.usbp) == USB_READY), "invalid state");
    endpoint->config.usbp->out_params[endpoint->config.ep - 1U] = endpoint;
    endpoint->timed_out                                         = false;
    osalSysUnlock();
}

void usb_endpoint_in_stop(usb_endpoint_in_t *endpoint) {
    osalDbgCheck(endpoint != NULL);

    osalSysLock();
    endpoint->config.usbp->in_params[endpoint->config.ep - 1U] = NULL;

    bqSuspendI(&endpoint->obqueue);
    obqResetI(&endpoint->obqueue);
    if (endpoint->report_storage != NULL) {
        endpoint->report_storage->reset_report(endpoint->report_storage->reports);
    }
    osalOsRescheduleS();
    osalSysUnlock();
}

void usb_endpoint_out_stop(usb_endpoint_out_t *endpoint) {
    osalDbgCheck(endpoint != NULL);

    osalSysLock();
    osalDbgAssert((usbGetDriverStateI(endpoint->config.usbp) == USB_STOP) || (usbGetDriverStateI(endpoint->config.usbp) == USB_READY), "invalid state");

    bqSuspendI(&endpoint->ibqueue);
    ibqResetI(&endpoint->ibqueue);
    osalOsRescheduleS();
    osalSysUnlock();
}

void usb_endpoint_in_suspend_cb(usb_endpoint_in_t *endpoint) {
    bqSuspendI(&endpoint->obqueue);
    obqResetI(&endpoint->obqueue);

    if (endpoint->report_storage != NULL) {
        endpoint->report_storage->reset_report(endpoint->report_storage->reports);
    }
}

void usb_endpoint_out_suspend_cb(usb_endpoint_out_t *endpoint) {
    bqSuspendI(&endpoint->ibqueue);
    ibqResetI(&endpoint->ibqueue);
}

void usb_endpoint_in_wakeup_cb(usb_endpoint_in_t *endpoint) {
    bqResumeX(&endpoint->obqueue);
}

void usb_endpoint_out_wakeup_cb(usb_endpoint_out_t *endpoint) {
    bqResumeX(&endpoint->ibqueue);
}

void usb_endpoint_in_configure_cb(usb_endpoint_in_t *endpoint) {
    usbInitEndpointI(endpoint->config.usbp, endpoint->config.ep, &endpoint->ep_config);
    obqResetI(&endpoint->obqueue);
    bqResumeX(&endpoint->obqueue);
}

void usb_endpoint_out_configure_cb(usb_endpoint_out_t *endpoint) {
    /* The current assumption is that there are no standalone OUT endpoints,
     * therefore if we share an endpoint with an IN endpoint, it is already
     * initialized. */
#if !defined(USB_ENDPOINTS_ARE_REORDERABLE)
    usbInitEndpointI(endpoint->config.usbp, endpoint->config.ep, &endpoint->ep_config);
#endif
    ibqResetI(&endpoint->ibqueue);
    bqResumeX(&endpoint->ibqueue);
    (void)usb_start_receive(endpoint);
}

void usb_endpoint_in_tx_complete_cb(USBDriver *usbp, usbep_t ep) {
    usb_endpoint_in_t *endpoint = usbp->in_params[ep - 1U];
    size_t             n;
    uint8_t *          buffer;

    if (endpoint == NULL) {
        return;
    }

    osalSysLockFromISR();

    /* Sending succeded, so we can reset the timed out state. */
    endpoint->timed_out = false;

    /* Freeing the buffer just transmitted, if it was not a zero size packet.*/
    if (!obqIsEmptyI(&endpoint->obqueue) && usbp->epc[ep]->in_state->txsize > 0U) {
        /* Store the last send report in the endpoint to be retrieved by a
         * GET_REPORT request or IDLE report handling. */
        if (endpoint->report_storage != NULL) {
            buffer = obqGetFullBufferI(&endpoint->obqueue, &n);
            endpoint->report_storage->set_report(endpoint->report_storage->reports, buffer, n);
        }
        obqReleaseEmptyBufferI(&endpoint->obqueue);
    }

    /* Checking if there is a buffer ready for transmission.*/
    buffer = obqGetFullBufferI(&endpoint->obqueue, &n);

    if (buffer != NULL) {
        /* The endpoint cannot be busy, we are in the context of the callback,
           so it is safe to transmit without a check.*/
        usbStartTransmitI(usbp, ep, buffer, n);
    } else if ((usbp->epc[ep]->ep_mode == USB_EP_MODE_TYPE_BULK) && (usbp->epc[ep]->in_state->txsize > 0U) && ((usbp->epc[ep]->in_state->txsize & ((size_t)usbp->epc[ep]->in_maxsize - 1U)) == 0U)) {
        /* Transmit zero sized packet in case the last one has maximum allowed
         * size. Otherwise the recipient may expect more data coming soon and
         * not return buffered data to app. See section 5.8.3 Bulk Transfer
         * Packet Size Constraints of the USB Specification document. */
        usbStartTransmitI(usbp, ep, usbp->setup, 0);
    } else {
        /* Nothing to transmit.*/
    }

    osalSysUnlockFromISR();
}

void usb_endpoint_out_rx_complete_cb(USBDriver *usbp, usbep_t ep) {
    usb_endpoint_out_t *endpoint = usbp->out_params[ep - 1U];
    if (endpoint == NULL) {
        return;
    }

    osalSysLockFromISR();

    size_t size = usbGetReceiveTransactionSizeX(usbp, ep);
    if (size > 0) {
        /* Posting the filled buffer in the queue.*/
        ibqPostFullBufferI(&endpoint->ibqueue, usbGetReceiveTransactionSizeX(endpoint->config.usbp, endpoint->config.ep));
    }

    /* The endpoint cannot be busy, we are in the context of the callback, so a
     * packet is in the buffer for sure. Trying to get a free buffer for the
     * next transaction.*/
    usb_start_receive(endpoint);

    osalSysUnlockFromISR();
}

bool usb_endpoint_in_send(usb_endpoint_in_t *endpoint, const uint8_t *data, size_t size, sysinterval_t timeout, bool buffered) {
    osalDbgCheck((endpoint != NULL) && (data != NULL) && (size > 0U) && (size <= endpoint->config.buffer_size));

    osalSysLock();
    if (usbGetDriverStateI(endpoint->config.usbp) != USB_ACTIVE) {
        osalSysUnlock();
        return false;
    }

    /* Short circuit the waiting if this endpoint timed out before, e.g. if
     * nobody is listening on this endpoint (is disconnected) such as
     * `hid_listen`/`qmk console` or we are in an environment with a very
     * restricted USB stack. The reason is to not introduce micro lock-ups if
     * the report is send periodically. */
    if (endpoint->timed_out && timeout != TIME_INFINITE) {
        timeout = TIME_IMMEDIATE;
    }
    osalSysUnlock();

    while (true) {
        size_t sent = obqWriteTimeout(&endpoint->obqueue, data, size, timeout);

        if (sent < size) {
            osalSysLock();
            endpoint->timed_out |= sent == 0;
            bqSuspendI(&endpoint->obqueue);
            obqResetI(&endpoint->obqueue);
            bqResumeX(&endpoint->obqueue);
            osalOsRescheduleS();
            osalSysUnlock();
            continue;
        }

        if (!buffered) {
            obqFlush(&endpoint->obqueue);
        }

        return true;
    }
}

void usb_endpoint_in_flush(usb_endpoint_in_t *endpoint, bool padded) {
    osalDbgCheck(endpoint != NULL);

    output_buffers_queue_t *obqp = &endpoint->obqueue;

    if (padded && obqp->ptr != NULL) {
        ptrdiff_t bytes_left = (size_t)obqp->top - (size_t)obqp->ptr;
        while (bytes_left > 0) {
            // Putting bytes into a buffer that has space left should never
            // fail and be instant, therefore we don't check the return value
            // for errors here.
            obqPutTimeout(obqp, 0, TIME_IMMEDIATE);
            bytes_left--;
        }
    }

    obqFlush(obqp);
}

bool usb_endpoint_in_is_inactive(usb_endpoint_in_t *endpoint) {
    osalDbgCheck(endpoint != NULL);

    osalSysLock();
    bool inactive = obqIsEmptyI(&endpoint->obqueue) && !usbGetTransmitStatusI(endpoint->config.usbp, endpoint->config.ep);
    osalSysUnlock();

    return inactive;
}

bool usb_endpoint_out_receive(usb_endpoint_out_t *endpoint, uint8_t *data, size_t size, sysinterval_t timeout) {
    osalDbgCheck((endpoint != NULL) && (data != NULL) && (size > 0U));

    osalSysLock();
    if (usbGetDriverStateI(endpoint->config.usbp) != USB_ACTIVE) {
        osalSysUnlock();
        return false;
    }

    if (endpoint->timed_out && timeout != TIME_INFINITE) {
        timeout = TIME_IMMEDIATE;
    }
    osalSysUnlock();

    const size_t received = ibqReadTimeout(&endpoint->ibqueue, data, size, timeout);
    endpoint->timed_out   = received == 0;

    return received == size;
}
