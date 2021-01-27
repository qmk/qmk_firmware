/* Copyright 2020 Jay Greco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
Remote keyboard is an experimental feature that allows for connecting another
keyboard, macropad, numpad, or accessory without requiring an additional USB connection.
The "remote keyboard" forwards its keystrokes using UART serial over TRRS. Dynamic VUSB 
detect allows the keyboard automatically switch to host or remote mode depending on
which is connected to the USB port.

Possible functionality includes the ability to send data from the host to the remote using
a reverse link, allowing for LED sync, configuration, and more data sharing between devices.
This will require a new communication protocol, as the current one is limited.
*/

#include "remote_kb.h"

uint8_t
 msg[UART_MSG_LEN],
 msg_idx = 0;

bool
 is_host = true;

// Private functions

static bool vbus_detect(void) {
  #if defined(__AVR_ATmega32U4__)
    //returns true if VBUS is present, false otherwise.
    USBCON |= (1 << OTGPADE); //enables VBUS pad
    _delay_us(10);
    return (USBSTA & (1<<VBUS));  //checks state of VBUS
  #else
    #error vbus_detect is not implemented for this architecure!
  #endif
}

static uint8_t chksum8(const unsigned char *buf, size_t len) {
  unsigned int sum;
  for (sum = 0 ; len != 0 ; len--)
    sum += *(buf++);
  return (uint8_t)sum;
}

static void send_msg(uint16_t keycode, bool pressed) {
  msg[IDX_PREAMBLE] = UART_PREAMBLE;
  msg[IDX_KCLSB] = (keycode & 0xFF);
  msg[IDX_KCMSB] = (keycode >> 8) & 0xFF;
  msg[IDX_PRESSED] = pressed;
  msg[IDX_CHECKSUM] = chksum8(msg, UART_MSG_LEN-1);

  for (int i=0; i<UART_MSG_LEN; i++) {
    uart_putchar(msg[i]);
  }
}

static void print_message_buffer(void) {
  for (int i=0; i<UART_MSG_LEN; i++) {
    dprintf("msg[%u]: %u\n", i, msg[i]);
  }
}

static void process_uart(void) {
  uint8_t chksum = chksum8(msg, UART_MSG_LEN-1);
  if (msg[IDX_PREAMBLE] != UART_PREAMBLE || msg[IDX_CHECKSUM] != chksum) {
     dprintf("UART checksum mismatch!\n");
     print_message_buffer();
     dprintf("calc checksum: %u\n", chksum);
  } else {
    uint16_t keycode = (uint16_t)msg[IDX_KCLSB] | ((uint16_t)msg[IDX_KCMSB] << 8);
    bool pressed = (bool)msg[IDX_PRESSED];
    if (IS_RM_KC(keycode)) {
      keyrecord_t record;
      record.event.pressed = pressed;
      if (pressed) dprintf("Remote macro: press [%u]\n", keycode);
      else dprintf("Remote macro: release [%u]\n", keycode);
      process_record_user(keycode, &record);
    } else {
      if (pressed) {
        dprintf("Remote: press [%u]\n", keycode);
        register_code(keycode);
    } else {
        dprintf("Remote: release [%u]\n", keycode);
        unregister_code(keycode);
      }
    }
  }
}

static void get_msg(void) {
  while (uart_available()) {
    msg[msg_idx] = uart_getchar();
    dprintf("idx: %u, recv: %u\n", msg_idx, msg[msg_idx]);
    if (msg_idx == 0 && (msg[msg_idx] != UART_PREAMBLE)) {
      dprintf("Byte sync error!\n");
      msg_idx = 0;
    } else if (msg_idx == (UART_MSG_LEN-1)) {
      process_uart();
      msg_idx = 0;
    } else {
      msg_idx++;
    }
  }
}

static void handle_host_incoming(void) {
  get_msg();
}

static void handle_host_outgoing(void) {
  // for future reverse link use
}

static void handle_remote_incoming(void) {
  // for future reverse link use
}

static void handle_remote_outgoing(uint16_t keycode, keyrecord_t *record) {
  if (IS_HID_KC(keycode) || IS_RM_KC(keycode)) {
    dprintf("Remote: send [%u]\n", keycode);
    send_msg(keycode, record->event.pressed);
  }
}

// Public functions

void matrix_init_remote_kb(void) {
  uart_init(SERIAL_UART_BAUD);
  is_host = vbus_detect();
}

void process_record_remote_kb(uint16_t keycode, keyrecord_t *record) {
  #if defined (KEYBOARD_HOST)
  handle_host_outgoing();

  #elif defined(KEYBOARD_REMOTE)
  handle_remote_outgoing(keycode, record);

  #else //auto check with VBUS
  if (is_host) {
    handle_host_outgoing();
  }
  else {
    handle_remote_outgoing(keycode, record);
  }
  #endif
}

void matrix_scan_remote_kb(void) {
  #if defined(KEYBOARD_HOST)
  handle_host_incoming();

  #elif defined (KEYBOARD_REMOTE)
  handle_remote_incoming();

  #else //auto check with VBUS
  if (is_host) {
    handle_host_incoming();
  }
  else {
    handle_remote_incoming();
  }
  #endif
}
