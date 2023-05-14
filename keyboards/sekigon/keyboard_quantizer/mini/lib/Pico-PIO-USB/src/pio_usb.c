/**
 * Copyright (c) 2021 sekigon-gonnoc
 */

#pragma GCC push_options
#pragma GCC optimize("-O3")

#include <stdio.h>
#include <stdint.h>
#include <string.h> // memcpy

#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/sync.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"

#include "pio_usb.h"
#include "usb_definitions.h"
#include "pio_usb_ll.h"
#include "usb_crc.h"
#include "usb_tx.pio.h"
#include "usb_rx.pio.h"

#define UNUSED_PARAMETER(x) (void)x

usb_device_t pio_usb_device[PIO_USB_DEVICE_CNT];
pio_port_t pio_port[1];
root_port_t pio_usb_root_port[PIO_USB_ROOT_PORT_CNT];
endpoint_t pio_usb_ep_pool[PIO_USB_EP_POOL_CNT];

//--------------------------------------------------------------------+
// Bus functions
//--------------------------------------------------------------------+

static void __no_inline_not_in_flash_func(send_pre)(const pio_port_t *pp) {
  uint8_t data[] = {USB_SYNC, USB_PID_PRE};

  // send PRE token in full-speed
  pio_sm_set_enabled(pp->pio_usb_tx, pp->sm_tx, false);
  for (uint i = 0; i < USB_TX_EOP_DISABLER_LEN; ++i) {
    uint16_t instr = usb_tx_fs_pre_program.instructions[i + USB_TX_EOP_OFFSET];
    pp->pio_usb_tx->instr_mem[pp->offset_tx + i + USB_TX_EOP_OFFSET] = instr;
  }

  SM_SET_CLKDIV(pp->pio_usb_tx, pp->sm_tx, pp->clk_div_fs_tx);

  dma_channel_transfer_from_buffer_now(pp->tx_ch, data, 2);

  pio_sm_set_enabled(pp->pio_usb_tx, pp->sm_tx, true);
  pp->pio_usb_tx->irq |= IRQ_TX_ALL_MASK;       // clear complete flag
  pp->pio_usb_tx->irq_force |= IRQ_TX_EOP_MASK; // disable eop

  while ((pp->pio_usb_tx->irq & IRQ_TX_COMP_MASK) == 0) {
    continue;
  }

  // change bus speed to low-speed
  pio_sm_set_enabled(pp->pio_usb_tx, pp->sm_tx, false);
  for (uint i = 0; i < USB_TX_EOP_DISABLER_LEN; ++i) {
    uint16_t instr = usb_tx_fs_program.instructions[i + USB_TX_EOP_OFFSET];
    pp->pio_usb_tx->instr_mem[pp->offset_tx + i + USB_TX_EOP_OFFSET] = instr;
  }
  SM_SET_CLKDIV(pp->pio_usb_tx, pp->sm_tx, pp->clk_div_ls_tx);

  pio_sm_set_enabled(pp->pio_usb_rx, pp->sm_rx, false);
  SM_SET_CLKDIV_MAXSPEED(pp->pio_usb_rx, pp->sm_rx);

  pio_sm_set_enabled(pp->pio_usb_rx, pp->sm_eop, false);
  SM_SET_CLKDIV(pp->pio_usb_rx, pp->sm_eop, pp->clk_div_ls_rx);
  pio_sm_set_enabled(pp->pio_usb_rx, pp->sm_eop, true);
}

void __not_in_flash_func(pio_usb_bus_usb_transfer)(const pio_port_t *pp,
                                              uint8_t *data, uint16_t len) {
  if (pp->need_pre) {
    send_pre(pp);
  }

  dma_channel_transfer_from_buffer_now(pp->tx_ch, data, len);

  pio_sm_set_enabled(pp->pio_usb_tx, pp->sm_tx, true);
  pp->pio_usb_tx->irq |= IRQ_TX_ALL_MASK; // clear complete flag

  while ((pp->pio_usb_tx->irq & IRQ_TX_ALL_MASK) == 0) {
    continue;
  }
}

void __no_inline_not_in_flash_func(pio_usb_bus_send_handshake)(
    const pio_port_t *pp, uint8_t pid) {
  uint8_t data[] = {USB_SYNC, pid};
  pio_usb_bus_usb_transfer(pp, data, sizeof(data));
}

void __no_inline_not_in_flash_func(pio_usb_bus_send_token)(const pio_port_t *pp,
                                                           uint8_t token,
                                                           uint8_t addr,
                                                           uint8_t ep_num) {

  uint8_t packet[4] = {USB_SYNC, token, 0, 0};
  uint16_t dat = ((uint16_t)(ep_num & 0xf) << 7) | (addr & 0x7f);
  uint8_t crc = calc_usb_crc5(dat);
  packet[2] = dat & 0xff;
  packet[3] = (crc << 3) | ((dat >> 8) & 0x1f);

  pio_usb_bus_usb_transfer(pp, packet, sizeof(packet));
}

void __no_inline_not_in_flash_func(pio_usb_bus_prepare_receive)(const pio_port_t *pp) {
  pio_sm_set_enabled(pp->pio_usb_rx, pp->sm_rx, false);
  pio_sm_clear_fifos(pp->pio_usb_rx, pp->sm_rx);
  pio_sm_restart(pp->pio_usb_rx, pp->sm_rx);
  pio_sm_exec(pp->pio_usb_rx, pp->sm_rx, pp->rx_reset_instr);
  pio_sm_exec(pp->pio_usb_rx, pp->sm_rx, pp->rx_reset_instr2);
}

void __no_inline_not_in_flash_func(pio_usb_bus_start_receive)(const pio_port_t *pp) {
  pp->pio_usb_rx->ctrl |= (1 << pp->sm_rx);
  pp->pio_usb_rx->irq = IRQ_RX_ALL_MASK;
}

uint8_t __no_inline_not_in_flash_func(pio_usb_bus_wait_handshake)(pio_port_t* pp) {
  int16_t t = 240;
  int16_t idx = 0;

  while (t--) {
    if (pio_sm_get_rx_fifo_level(pp->pio_usb_rx, pp->sm_rx)) {
      uint8_t data = pio_sm_get(pp->pio_usb_rx, pp->sm_rx) >> 24;
      pp->usb_rx_buffer[idx++] = data;
      if (idx == 2) {
        break;
      }
    }
  }

  if (t > 0) {
    while ((pp->pio_usb_rx->irq & IRQ_RX_COMP_MASK) == 0) {
      continue;
    }
  }

  pio_sm_set_enabled(pp->pio_usb_rx, pp->sm_rx, false);

  return pp->usb_rx_buffer[1];
}

int __no_inline_not_in_flash_func(pio_usb_bus_receive_packet_and_handshake)(
    pio_port_t *pp, uint8_t handshake) {
  uint16_t crc = 0xffff;
  uint16_t crc_prev = 0xffff;
  uint16_t crc_prev2 = 0xffff;
  uint16_t crc_receive = 0xffff;
  uint16_t crc_receive_inverse;
  bool crc_match = false;
  int16_t t = 240;
  uint16_t idx = 0;

  while (t--) {
    if (pio_sm_get_rx_fifo_level(pp->pio_usb_rx, pp->sm_rx)) {
      uint8_t data = pio_sm_get(pp->pio_usb_rx, pp->sm_rx) >> 24;
      pp->usb_rx_buffer[idx++] = data;
      if (idx == 2) {
        break;
      }
    }
  }

  // timing critical start
  if (t > 0) {
    if (handshake == USB_PID_ACK) {
      while ((pp->pio_usb_rx->irq & IRQ_RX_COMP_MASK) == 0) {
        if (pio_sm_get_rx_fifo_level(pp->pio_usb_rx, pp->sm_rx)) {
          uint8_t data = pio_sm_get(pp->pio_usb_rx, pp->sm_rx) >> 24;
          crc_prev2 = crc_prev;
          crc_prev = crc;
          crc = update_usb_crc16(crc, data);
          pp->usb_rx_buffer[idx++] = data;
          crc_receive = (crc_receive >> 8) | (data << 8);
          crc_receive_inverse = crc_receive ^ 0xffff;
          crc_match = (crc_receive_inverse == crc_prev2);
        }
      }

      if (idx >= 4 && crc_match) {
        pio_usb_bus_send_handshake(pp, USB_PID_ACK);
        // timing critical end
        return idx - 4;
      }

      if (pp->usb_rx_buffer[1] == USB_PID_NAK ||
          pp->usb_rx_buffer[1] == USB_PID_STALL) {
        return 0;
      }
    } else {
      // just discard received data since we NAK/STALL anyway
      while ((pp->pio_usb_rx->irq & IRQ_RX_COMP_MASK) == 0) {
        continue;
      }
      pio_sm_clear_fifos(pp->pio_usb_rx, pp->sm_rx);

      pio_usb_bus_send_handshake(pp, handshake);
    }
  }

  return -1;
}

static __always_inline void add_pio_host_rx_program(PIO pio,
                                             const pio_program_t *program,
                                             const pio_program_t *debug_program,
                                             uint *offset, int debug_pin) {
  if (debug_pin < 0) {
    *offset = pio_add_program(pio, program);
  } else {
    *offset = pio_add_program(pio, debug_program);
  }
}

static void __no_inline_not_in_flash_func(initialize_host_programs)(
    pio_port_t *pp, const pio_usb_configuration_t *c, root_port_t *port) {
  pp->offset_tx = pio_add_program(pp->pio_usb_tx, &usb_tx_fs_program);
  usb_tx_fs_program_init(pp->pio_usb_tx, pp->sm_tx, pp->offset_tx,
                         port->pin_dp);

  add_pio_host_rx_program(pp->pio_usb_rx, &usb_nrzi_decoder_program,
                          &usb_nrzi_decoder_debug_program, &pp->offset_rx,
                          c->debug_pin_rx);
  usb_rx_fs_program_init(pp->pio_usb_rx, pp->sm_rx, pp->offset_rx, port->pin_dp,
                         c->debug_pin_rx);
  pp->rx_reset_instr = pio_encode_jmp(pp->offset_rx);
  pp->rx_reset_instr2 = pio_encode_set(pio_x, 0);

  add_pio_host_rx_program(pp->pio_usb_rx, &usb_edge_detector_program,
                          &usb_edge_detector_debug_program, &pp->offset_eop,
                          c->debug_pin_eop);
  eop_detect_fs_program_init(pp->pio_usb_rx, c->sm_eop, pp->offset_eop,
                             port->pin_dp, true, c->debug_pin_eop);

  usb_tx_configure_pins(pp->pio_usb_tx, pp->sm_tx, port->pin_dp);

  pio_sm_set_jmp_pin(pp->pio_usb_rx, pp->sm_rx, port->pin_dp);
  pio_sm_set_jmp_pin(pp->pio_usb_rx, pp->sm_eop, port->pin_dm);
  pio_sm_set_in_pins(pp->pio_usb_rx, pp->sm_eop, port->pin_dp);
}

static void configure_tx_channel(uint8_t ch, PIO pio, uint sm) {
  dma_channel_config conf = dma_channel_get_default_config(ch);

  channel_config_set_read_increment(&conf, true);
  channel_config_set_write_increment(&conf, false);
  channel_config_set_transfer_data_size(&conf, DMA_SIZE_8);
  channel_config_set_dreq(&conf, pio_get_dreq(pio, sm, true));

  dma_channel_set_config(ch, &conf, false);
  dma_channel_set_write_addr(ch, &pio->txf[sm], false);
}

static void apply_config(pio_port_t *pp, const pio_usb_configuration_t *c,
                         root_port_t *port) {
  pp->pio_usb_tx = c->pio_tx_num == 0 ? pio0 : pio1;
  pp->sm_tx = c->sm_tx;
  pp->tx_ch = c->tx_ch;
  pp->pio_usb_rx = c->pio_rx_num == 0 ? pio0 : pio1;
  pp->sm_rx = c->sm_rx;
  pp->sm_eop = c->sm_eop;
  port->pin_dp = c->pin_dp;
  port->pin_dm = c->pin_dp + 1;

  pp->debug_pin_rx = c->debug_pin_rx;
  pp->debug_pin_eop = c->debug_pin_eop;

  pp->extra_error_retry_count = c->extra_error_retry_count;

  pio_sm_claim(pp->pio_usb_tx, pp->sm_tx);
  pio_sm_claim(pp->pio_usb_rx, pp->sm_rx);
  pio_sm_claim(pp->pio_usb_rx, pp->sm_eop);
}

static void port_pin_drive_setting(const root_port_t *port) {
  gpio_set_slew_rate(port->pin_dp, GPIO_SLEW_RATE_FAST);
  gpio_set_slew_rate(port->pin_dm, GPIO_SLEW_RATE_FAST);
  gpio_set_drive_strength(port->pin_dp, GPIO_DRIVE_STRENGTH_12MA);
  gpio_set_drive_strength(port->pin_dm, GPIO_DRIVE_STRENGTH_12MA);
}

void pio_usb_bus_init(pio_port_t *pp, const pio_usb_configuration_t *c,
                      root_port_t *root) {
  memset(root, 0, sizeof(root_port_t));

  pp->pio_usb_tx = c->pio_tx_num == 0 ? pio0 : pio1;
  dma_claim_mask(1<<c->tx_ch);
  configure_tx_channel(c->tx_ch, pp->pio_usb_tx, c->sm_tx);

  apply_config(pp, c, root);
  initialize_host_programs(pp, c, root);
  port_pin_drive_setting(root);
  root->initialized = true;
  root->dev_addr = 0;
}

//--------------------------------------------------------------------+
// Application API
//--------------------------------------------------------------------+

endpoint_t *pio_usb_get_endpoint(usb_device_t *device, uint8_t idx) {
  uint8_t ep_id = device->endpoint_id[idx];
  if (ep_id == 0) {
    return NULL;
  } else if (ep_id >= 1) {
    return &pio_usb_ep_pool[ep_id - 1];
  }
  return NULL;
}

int __no_inline_not_in_flash_func(pio_usb_get_in_data)(endpoint_t *ep,
                                                       uint8_t *buffer,
                                                       uint8_t len) {
  if (ep->has_transfer || ep->is_tx) {
    return -1;
  }

  if (ep->new_data_flag) {
    len = len < ep->actual_len ? len : ep->actual_len;
    memcpy(buffer, (void *)ep->buffer, len);

    ep->new_data_flag = false;

    return pio_usb_ll_transfer_start(ep, ep->buffer, ep->size) ? len : -1;
  }

  return -1;
}

int __no_inline_not_in_flash_func(pio_usb_set_out_data)(endpoint_t *ep,
                                                        const uint8_t *buffer,
                                                        uint8_t len) {
  if (ep->has_transfer || !ep->is_tx) {
    return -1;
  }

  return pio_usb_ll_transfer_start(ep, (uint8_t *)buffer, len) ? 0 : -1;
}

//--------------------------------------------------------------------+
// Low Level Function
//--------------------------------------------------------------------+

void __no_inline_not_in_flash_func(pio_usb_ll_configure_endpoint)(
    endpoint_t *ep, uint8_t const *desc_endpoint) {
  const endpoint_descriptor_t *d = (const endpoint_descriptor_t *)desc_endpoint;
  ep->size = d->max_size[0] | (d->max_size[1] << 8);
  ep->ep_num = d->epaddr;
  ep->attr = d->attr;
  ep->interval = d->interval;
  ep->interval_counter = 0;
  ep->data_id = 0;
}

static inline __force_inline void prepare_tx_data(endpoint_t *ep) {
  uint16_t const xact_len = pio_usb_ll_get_transaction_len(ep);
  ep->buffer[0] = USB_SYNC;
  ep->buffer[1] = (ep->data_id == 1)
                      ? USB_PID_DATA1
                      : USB_PID_DATA0; // USB_PID_SETUP also DATA0
  memcpy(ep->buffer + 2, ep->app_buf, xact_len);

  uint16_t const crc16 = calc_usb_crc16(ep->app_buf, xact_len);
  ep->buffer[2 + xact_len] = crc16 & 0xff;
  ep->buffer[2 + xact_len + 1] = crc16 >> 8;
}

bool __no_inline_not_in_flash_func(pio_usb_ll_transfer_start)(endpoint_t *ep,
                                                              uint8_t *buffer,
                                                              uint16_t buflen) {
  if (ep->has_transfer) {
    return false;
  }

  ep->app_buf = buffer;
  ep->total_len = buflen;
  ep->actual_len = 0;

  if (ep->is_tx) {
    prepare_tx_data(ep);
  } else {
    ep->new_data_flag = false;
  }

  ep->has_transfer = true;

  return true;
}

bool __no_inline_not_in_flash_func(pio_usb_ll_transfer_continue)(
    endpoint_t *ep, uint16_t xferred_bytes) {
  ep->app_buf += xferred_bytes;
  ep->actual_len += xferred_bytes;
  ep->data_id ^= 1;

  if ((xferred_bytes < ep->size) || (ep->actual_len >= ep->total_len)) {
    // complete if all bytes transferred or short packet
    pio_usb_ll_transfer_complete(ep, PIO_USB_INTS_ENDPOINT_COMPLETE_BITS);
    return false;
  } else {
    if (ep->is_tx) {
      prepare_tx_data(ep);
    }

    return true;
  }
}

void __no_inline_not_in_flash_func(pio_usb_ll_transfer_complete)(
    endpoint_t *ep, uint32_t flag) {
  root_port_t *rport = PIO_USB_ROOT_PORT(ep->root_idx);
  uint32_t const ep_mask = (1u << (ep - pio_usb_ep_pool));

  rport->ints |= flag;

  if (flag == PIO_USB_INTS_ENDPOINT_COMPLETE_BITS) {
    rport->ep_complete |= ep_mask;
    if (!ep->is_tx) {
      ep->new_data_flag = true;
    }
  } else if (flag == PIO_USB_INTS_ENDPOINT_ERROR_BITS) {
    rport->ep_error |= ep_mask;
  } else if (flag == PIO_USB_INTS_ENDPOINT_STALLED_BITS) {
    rport->ep_stalled |= ep_mask;
  } else {
    // something wrong
  }

  ep->has_transfer = false;
}

int pio_usb_host_add_port(uint8_t pin_dp) {
  for (int idx = 0; idx < PIO_USB_ROOT_PORT_CNT; idx++) {
    root_port_t *root = PIO_USB_ROOT_PORT(idx);
    if (!root->initialized) {
      root->pin_dp = pin_dp;
      root->pin_dm = pin_dp + 1;

      PIO_USB_ROOT_PORT(idx)->pin_dp = pin_dp;
      PIO_USB_ROOT_PORT(idx)->pin_dm = pin_dp + 1;

      gpio_pull_down(pin_dp);
      gpio_pull_down(pin_dp + 1);
      pio_gpio_init(pio_port[0].pio_usb_tx, pin_dp);
      pio_gpio_init(pio_port[0].pio_usb_tx, pin_dp + 1);
      gpio_set_inover(pin_dp, GPIO_OVERRIDE_INVERT);
      gpio_set_inover(pin_dp + 1, GPIO_OVERRIDE_INVERT);
      pio_sm_set_pindirs_with_mask(pio_port[0].pio_usb_tx, pio_port[0].sm_tx, 0,
                                   (0b11 << pin_dp));
      port_pin_drive_setting(root);
      root->initialized = true;

      return 0;
    }
  }

  return -1;
}

#pragma GCC pop_options
