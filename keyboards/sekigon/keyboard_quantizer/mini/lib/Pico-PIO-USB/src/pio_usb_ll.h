/**
 * Copyright (c) 2021 sekigon-gonnoc
 *                    Ha Thach (thach@tinyusb.org)
 */

#pragma once

#include "hardware/pio.h"
#include "pio_usb_configuration.h"
#include "usb_definitions.h"

enum {
  PIO_USB_INTS_CONNECT_POS = 0,
  PIO_USB_INTS_DISCONNECT_POS,
  PIO_USB_INTS_RESET_END_POS,
  PIO_USB_INTS_SETUP_REQ_POS,
  PIO_USB_INTS_SOF_POS,

  PIO_USB_INTS_ENDPOINT_COMPLETE_POS,
  PIO_USB_INTS_ENDPOINT_ERROR_POS,
  PIO_USB_INTS_ENDPOINT_STALLED_POS,
};

#define PIO_USB_INTS_CONNECT_BITS (1u << PIO_USB_INTS_CONNECT_POS)
#define PIO_USB_INTS_DISCONNECT_BITS (1u << PIO_USB_INTS_DISCONNECT_POS)
#define PIO_USB_INTS_RESET_END_BITS (1u << PIO_USB_INTS_RESET_END_POS)
#define PIO_USB_INTS_SETUP_REQ_BITS (1u << PIO_USB_INTS_SETUP_REQ_POS)

#define PIO_USB_INTS_SOF_BITS (1u << PIO_USB_INTS_SOF_POS)

#define PIO_USB_INTS_ENDPOINT_COMPLETE_BITS                                    \
  (1u << PIO_USB_INTS_ENDPOINT_COMPLETE_POS)
#define PIO_USB_INTS_ENDPOINT_ERROR_BITS (1u << PIO_USB_INTS_ENDPOINT_ERROR_POS)
#define PIO_USB_INTS_ENDPOINT_STALLED_BITS                                     \
  (1u << PIO_USB_INTS_ENDPOINT_STALLED_POS)

typedef enum {
  PORT_PIN_SE0 = 0b00,
  PORT_PIN_FS_IDLE = 0b01,
  PORT_PIN_LS_IDLE = 0b10,
  PORT_PIN_SE1 = 0b11,
} port_pin_status_t;

typedef struct {
  uint16_t div_int;
  uint8_t div_frac;
} pio_clk_div_t;

typedef struct {
  PIO pio_usb_tx; // could not set to volatile
  uint sm_tx;
  uint offset_tx;
  uint tx_ch;

  PIO pio_usb_rx; // could not set to volatile
  uint sm_rx;
  uint offset_rx;
  uint sm_eop;
  uint offset_eop;
  uint rx_reset_instr;
  uint rx_reset_instr2;
  uint device_rx_irq_num;

  int8_t debug_pin_rx;
  int8_t debug_pin_eop;
  uint8_t error_count;
  uint8_t extra_error_retry_count;
  uint32_t total_error_count;
  uint32_t total_fatal_error_count;
  uint32_t total_transaction_count;

  pio_clk_div_t clk_div_fs_tx;
  pio_clk_div_t clk_div_fs_rx;
  pio_clk_div_t clk_div_ls_tx;
  pio_clk_div_t clk_div_ls_rx;

  bool need_pre;

  uint8_t usb_rx_buffer[128];
} pio_port_t;

//--------------------------------------------------------------------+
//
//--------------------------------------------------------------------+

enum {
  PIO_USB_MODE_INVALID = 0,
  PIO_USB_MODE_DEVICE,
  PIO_USB_MODE_HOST,
};

extern usb_device_t pio_usb_device[PIO_USB_DEVICE_CNT];

extern root_port_t pio_usb_root_port[PIO_USB_ROOT_PORT_CNT];
#define PIO_USB_ROOT_PORT(_idx) (pio_usb_root_port + (_idx))

extern endpoint_t pio_usb_ep_pool[PIO_USB_EP_POOL_CNT];
#define PIO_USB_ENDPOINT(_idx) (pio_usb_ep_pool + (_idx))

extern pio_port_t pio_port[1];
#define PIO_USB_PIO_PORT(_idx) (pio_port + (_idx))

//--------------------------------------------------------------------+
// Bus functions
//--------------------------------------------------------------------+

#define IRQ_TX_EOP_MASK (1 << usb_tx_fs_IRQ_EOP)
#define IRQ_TX_COMP_MASK (1 << usb_tx_fs_IRQ_COMP)
#define IRQ_TX_ALL_MASK (IRQ_TX_EOP_MASK | IRQ_TX_COMP_MASK)
#define IRQ_RX_COMP_MASK (1 << IRQ_RX_EOP)
#define IRQ_RX_ALL_MASK                                             \
  ((1 << IRQ_RX_EOP) | (1 << IRQ_RX_BS_ERR) | (1 << IRQ_RX_START) | \
   (1 << DECODER_TRIGGER))

#define SM_SET_CLKDIV(pio, sm, div)                                            \
  pio_sm_set_clkdiv_int_frac(pio, sm, div.div_int, div.div_frac)
#define SM_SET_CLKDIV_MAXSPEED(pio, sm)                                        \
  pio_sm_set_clkdiv_int_frac(pio, sm, 1, 0)

void pio_usb_bus_init(pio_port_t *pp, const pio_usb_configuration_t *c,
                      root_port_t *root);

void pio_usb_bus_start_receive(const pio_port_t *pp);
void pio_usb_bus_prepare_receive(const pio_port_t *pp);
int pio_usb_bus_receive_packet_and_handshake(pio_port_t *pp, uint8_t handshake);
void pio_usb_bus_usb_transfer(const pio_port_t *pp, uint8_t *data,
                              uint16_t len);

uint8_t pio_usb_bus_wait_handshake(pio_port_t *pp);
void pio_usb_bus_send_handshake(const pio_port_t *pp, uint8_t pid);
void pio_usb_bus_send_token(const pio_port_t *pp, uint8_t token, uint8_t addr,
                            uint8_t ep_num);

static __always_inline port_pin_status_t
pio_usb_bus_get_line_state(root_port_t *root) {
  uint8_t dp = gpio_get(root->pin_dp) ? 0 : 1;
  uint8_t dm = gpio_get(root->pin_dm) ? 0 : 1;

  return (dm << 1) | dp;
}

//--------------------------------------------------------------------+
// Low Level functions
//--------------------------------------------------------------------+

void pio_usb_ll_configure_endpoint(endpoint_t *ep,
                                   uint8_t const *desc_endpoint);
bool pio_usb_ll_transfer_start(endpoint_t *ep, uint8_t *buffer,
                               uint16_t buflen);
bool pio_usb_ll_transfer_continue(endpoint_t *ep, uint16_t xferred_bytes);
void pio_usb_ll_transfer_complete(endpoint_t *ep, uint32_t flag);

static inline __force_inline uint16_t
pio_usb_ll_get_transaction_len(endpoint_t *ep) {
  uint16_t remaining = ep->total_len - ep->actual_len;
  return (remaining < ep->size) ? remaining : ep->size;
}

//--------------------------------------------------------------------
// Host Controller functions
//--------------------------------------------------------------------

// Host IRQ Handler
void pio_usb_host_irq_handler(uint8_t root_idx);

void pio_usb_host_port_reset_start(uint8_t root_idx);
void pio_usb_host_port_reset_end(uint8_t root_idx);

void pio_usb_host_close_device(uint8_t root_idx, uint8_t device_address);

bool pio_usb_host_endpoint_open(uint8_t root_idx, uint8_t device_address,
                                uint8_t const *desc_endpoint, bool need_pre);
bool pio_usb_host_send_setup(uint8_t root_idx, uint8_t device_address,
                             uint8_t const setup_packet[8]);
bool pio_usb_host_endpoint_transfer(uint8_t root_idx, uint8_t device_address,
                                    uint8_t ep_address, uint8_t *buffer,
                                    uint16_t buflen);

//--------------------------------------------------------------------
// Device Controller functions
//--------------------------------------------------------------------

// Device IRQ Handler
void pio_usb_device_irq_handler(uint8_t root_idx);

void pio_usb_device_set_address(uint8_t dev_addr);
bool pio_usb_device_endpoint_open(uint8_t const *desc_endpoint);
bool pio_usb_device_transfer(uint8_t ep_address, uint8_t *buffer,
                             uint16_t buflen);

static inline __force_inline endpoint_t *
pio_usb_device_get_endpoint_by_address(uint8_t ep_address) {
  // index = 2*num + dir e.g out1, in1, out2, in2
  uint8_t const ep_idx = ((ep_address & 0x7f) << 1) | (ep_address >> 7);
  return PIO_USB_ENDPOINT(ep_idx);
}
