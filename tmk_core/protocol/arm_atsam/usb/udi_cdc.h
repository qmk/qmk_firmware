/**
 * \file
 *
 * \brief USB Device Communication Device Class (CDC) interface definitions.
 *
 * Copyright (c) 2009-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _UDI_CDC_H_
#define _UDI_CDC_H_

#ifdef CDC

#include "conf_usb.h"
#include "usb_protocol.h"
#include "usb_protocol_cdc.h"
#include "udd.h"
#include "udc_desc.h"
#include "udi.h"

// Check the number of port
#ifndef UDI_CDC_PORT_NB
# define UDI_CDC_PORT_NB 1
#endif
#if (UDI_CDC_PORT_NB > 1)
# error UDI_CDC_PORT_NB must be at most 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup udi_cdc_group_udc
 * @{
 */

//! Global structure which contains standard UDI API for UDC
extern UDC_DESC_STORAGE udi_api_t udi_api_cdc_comm;
extern UDC_DESC_STORAGE udi_api_t udi_api_cdc_data;
//@}

//#define CDC_ACM_SIZE  64  see usb_protocol_cdc.h
//#define CDC_RX_SIZE   64

//! CDC communication endpoints size for all speeds
#define UDI_CDC_COMM_EP_SIZE        CDC_ACM_SIZE
//! CDC data endpoints size for FS speed (8B, 16B, 32B, 64B)
#define UDI_CDC_DATA_EPS_FS_SIZE    CDC_RX_SIZE

//@}

/**
 * \ingroup udi_group
 * \defgroup udi_cdc_group USB Device Interface (UDI) for Communication Class Device (CDC)
 *
 * Common APIs used by high level application to use this USB class.
 *
 * These routines are used to transfer and control data
 * to/from USB CDC endpoint.
 *
 * See \ref udi_cdc_quickstart.
 * @{
 */

/**
 * \name Interface for application with single CDC interface support
 */
//@{

/**
 * \brief Notify a state change of DCD signal
 *
 * \param b_set      DCD is enabled if true, else disabled
 */
void udi_cdc_ctrl_signal_dcd(bool b_set);

/**
 * \brief Notify a state change of DSR signal
 *
 * \param b_set      DSR is enabled if true, else disabled
 */
void udi_cdc_ctrl_signal_dsr(bool b_set);

/**
 * \brief Notify a framing error
 */
void udi_cdc_signal_framing_error(void);

/**
 * \brief Notify a parity error
 */
void udi_cdc_signal_parity_error(void);

/**
 * \brief Notify a overrun
 */
void udi_cdc_signal_overrun(void);

/**
 * \brief Gets the number of byte received
 *
 * \return the number of data available
 */
iram_size_t udi_cdc_get_nb_received_data(void);

/**
 * \brief This function checks if a character has been received on the CDC line
 *
 * \return \c 1 if a byte is ready to be read.
 */
bool udi_cdc_is_rx_ready(void);

/**
 * \brief Waits and gets a value on CDC line
 *
 * \return value read on CDC line
 */
int udi_cdc_getc(void);

/**
 * \brief Reads a RAM buffer on CDC line
 *
 * \param buf       Values read
 * \param size      Number of value read
 *
 * \return the number of data remaining
 */
iram_size_t udi_cdc_read_buf(void* buf, iram_size_t size);

/**
 * \brief Non polling reads of a up to 'size' data from CDC line
 *
 * \param port      Communication port number to manage
 * \param buf       Buffer where to store read data
 * \param size      Maximum number of data to read (size of buffer)
 *
 * \return the number of data effectively read
 */
iram_size_t udi_cdc_read_no_polling(void* buf, iram_size_t size);

/**
 * \brief Gets the number of free byte in TX buffer
 *
 * \return the number of free byte in TX buffer
 */
iram_size_t udi_cdc_get_free_tx_buffer(void);

/**
 * \brief This function checks if a new character sent is possible
 * The type int is used to support scanf redirection from compiler LIB.
 *
 * \return \c 1 if a new character can be sent
 */
bool udi_cdc_is_tx_ready(void);

/**
 * \brief Puts a byte on CDC line
 * The type int is used to support printf redirection from compiler LIB.
 *
 * \param value      Value to put
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
int udi_cdc_putc(int value);

/**
 * \brief Writes a RAM buffer on CDC line
 *
 * \param buf       Values to write
 * \param size      Number of value to write
 *
 * \return the number of data remaining
 */
iram_size_t udi_cdc_write_buf(const void* buf, iram_size_t size);
//@}

/**
 * \name Interface for application with multi CDC interfaces support
 */
//@{

/**
 * \brief Notify a state change of DCD signal
 *
 * \param port       Communication port number to manage
 * \param b_set      DCD is enabled if true, else disabled
 */
void udi_cdc_multi_ctrl_signal_dcd(uint8_t port, bool b_set);

/**
 * \brief Notify a state change of DSR signal
 *
 * \param port       Communication port number to manage
 * \param b_set      DSR is enabled if true, else disabled
 */
void udi_cdc_multi_ctrl_signal_dsr(uint8_t port, bool b_set);

/**
 * \brief Notify a framing error
 *
 * \param port       Communication port number to manage
 */
void udi_cdc_multi_signal_framing_error(uint8_t port);

/**
 * \brief Notify a parity error
 *
 * \param port       Communication port number to manage
 */
void udi_cdc_multi_signal_parity_error(uint8_t port);

/**
 * \brief Notify a overrun
 *
 * \param port       Communication port number to manage
 */
void udi_cdc_multi_signal_overrun(uint8_t port);

/**
 * \brief Gets the number of byte received
 *
 * \param port       Communication port number to manage
 *
 * \return the number of data available
 */
iram_size_t udi_cdc_multi_get_nb_received_data(uint8_t port);

/**
 * \brief This function checks if a character has been received on the CDC line
 *
 * \param port       Communication port number to manage
 *
 * \return \c 1 if a byte is ready to be read.
 */
bool udi_cdc_multi_is_rx_ready(uint8_t port);

/**
 * \brief Waits and gets a value on CDC line
 *
 * \param port       Communication port number to manage
 *
 * \return value read on CDC line
 */
int udi_cdc_multi_getc(uint8_t port);

/**
 * \brief Reads a RAM buffer on CDC line
 *
 * \param port       Communication port number to manage
 * \param buf       Values read
 * \param size      Number of values read
 *
 * \return the number of data remaining
 */
iram_size_t udi_cdc_multi_read_buf(uint8_t port, void* buf, iram_size_t size);

/**
 * \brief Gets the number of free byte in TX buffer
 *
 * \param port       Communication port number to manage
 *
 * \return the number of free byte in TX buffer
 */
iram_size_t udi_cdc_multi_get_free_tx_buffer(uint8_t port);

/**
 * \brief This function checks if a new character sent is possible
 * The type int is used to support scanf redirection from compiler LIB.
 *
 * \param port       Communication port number to manage
 *
 * \return \c 1 if a new character can be sent
 */
bool udi_cdc_multi_is_tx_ready(uint8_t port);

/**
 * \brief Puts a byte on CDC line
 * The type int is used to support printf redirection from compiler LIB.
 *
 * \param port       Communication port number to manage
 * \param value      Value to put
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
int udi_cdc_multi_putc(uint8_t port, int value);

/**
 * \brief Writes a RAM buffer on CDC line
 *
 * \param port       Communication port number to manage
 * \param buf       Values to write
 * \param size      Number of value to write
 *
 * \return the number of data remaining
 */
iram_size_t udi_cdc_multi_write_buf(uint8_t port, const void* buf, iram_size_t size);
//@}

#define CDC_PRINTBUF_SIZE  256
extern char printbuf[CDC_PRINTBUF_SIZE];

#define CDC_INBUF_SIZE 256

typedef struct {
    uint32_t count;
    uint32_t lastcount;
    char buf[CDC_INBUF_SIZE];
} inbuf_t;

#else //CDC

// keep these to accommodate calls if remaining
#define CDC_PRINTBUF_SIZE  1
extern char printbuf[CDC_PRINTBUF_SIZE];

#define CDC_INBUF_SIZE 1

typedef struct {
    uint32_t count;
    uint32_t lastcount;
    char buf[CDC_INBUF_SIZE];
} inbuf_t;

extern inbuf_t inbuf;

#endif //CDC

uint32_t CDC_print(char *printbuf);
int CDC_printf(const char *_Format, ...);
uint32_t CDC_input(void);
void CDC_init(void);

#ifdef __cplusplus
}
#endif

#endif // _UDI_CDC_H_
