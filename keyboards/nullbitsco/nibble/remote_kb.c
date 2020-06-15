#include "remote_kb.h"

uint8_t
 msg[UART_MSG_LEN],
 msg_idx = 0;

bool
 is_master = true;

bool vbus_detect(void) {
  //returns true if VBUS is present, false otherwise.
   USBCON |= (1 << OTGPADE); //enables VBUS pad
   _delay_us(10);
   return (USBSTA & (1<<VBUS));  //checks state of VBUS
}

uint8_t chksum8(const unsigned char *buf, size_t len) {
  unsigned int sum;
  for (sum = 0 ; len != 0 ; len--)
      sum += *(buf++);
  return (uint8_t)sum;
}

void send_msg(uint16_t keycode, bool pressed) {
  msg[IDX_PREAMBLE] = UART_PREAMBLE;
  msg[IDX_KCLSB] = (keycode & 0xFF);
  msg[IDX_KCMSB] = (keycode >> 8) & 0xFF;
  msg[IDX_PRESSED] = pressed;
  msg[IDX_CHECKSUM] = chksum8(msg, UART_MSG_LEN-1);

  for (int i=0; i<UART_MSG_LEN; i++) {
    uart_putchar(msg[i]);
  }
}

void get_msg(void) {
  while (uart_available()) {
    msg[msg_idx] = uart_getchar();
    //dprintf("idx: %u, recv: %u\n", msg_idx, msg[msg_idx]);
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

void _print_message_buffer(void) {
  for (int i=0; i<UART_MSG_LEN; i++) {
    dprintf("msg[%u]: %u\n", i, msg[i]);
  }
}

void process_uart(void) {
  uint8_t chksum = chksum8(msg, UART_MSG_LEN-1);
  if (msg[IDX_PREAMBLE] != UART_PREAMBLE || msg[IDX_CHECKSUM] != chksum) {
     dprintf("UART checksum mismatch!\n");
     _print_message_buffer();
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

void matrix_init_remote_kb(void) {
  uart_init(SERIAL_UART_BAUD);
  is_master = vbus_detect();
}

void process_record_remote_kb(uint16_t keycode, keyrecord_t *record) {
  #if defined (KEYBOARD_MASTER)
  // for future reverse link use

  #elif defined(KEYBOARD_SLAVE)
  if (IS_HID_KC(keycode) || IS_RM_KC(keycode)) {
    dprintf("Remote: send [%u]\n", keycode);
    send_msg(keycode, record->event.pressed);
  }

  #else //auto check with VBUS
  if (is_master) {
    // for future reverse link use
  }
  else {
    if (IS_HID_KC(keycode) || IS_RM_KC(keycode)) {
      dprintf("Remote: send [%u]\n", keycode);
      send_msg(keycode, record->event.pressed);
    }
  }
  #endif
}

void matrix_scan_remote_kb(void) {
  #if defined(KEYBOARD_MASTER)
  get_msg();

  #elif defined (KEYBOARD_SLAVE)
  // for future reverse link use

  #else //auto check with VBUS
  if (is_master) {
    get_msg();
  }
  else {
    // for future reverse link use
  }
  #endif
}