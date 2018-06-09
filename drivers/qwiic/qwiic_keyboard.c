/* Copyright 2018 Jack Humbert
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

#include "qwiic_keyboard.h"
#include "keymap.h"
#include "matrix.h"
#include "keyboard.h"
#include "twi2c.h"
#include <string.h>
#include "usb_main.h"
#include "usb_driver.h"

#define QWIIC_KEYBOARD_LAYERS 16
#define QWIIC_KEYBOARD_ROWS 8
#define QWIIC_KEYBOARD_COLS 8

#define qwiic_matrix_t uint8_t

#define QWIIC_KEYBOARD_HANDSHAKE_ADDRESS       0b01010100
#define QWIIC_KEYBOARD_LISTENING_ADDRESS_START 0b01010110
#define QWIIC_KEYBOARD_HANDSHAKE_MESSAGE_SIZE  (QWIIC_KEYBOARD_LAYERS * QWIIC_KEYBOARD_ROWS * QWIIC_KEYBOARD_COLS)
#define QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE     MATRIX_ROWS

void qwiic_keyboard_write_keymap(uint8_t * pointer);
void qwiic_keyboard_read_keymap(uint8_t * pointer);

bool qwiic_keyboard_master = false;
bool qwiic_keyboard_connected = false;
uint8_t qwiic_keyboard_handshake_message[QWIIC_KEYBOARD_HANDSHAKE_MESSAGE_SIZE] = {0};
uint8_t qwiic_keyboard_matrix_message[QWIIC_KEYBOARD_ROWS] = {0};
twi2c_message_received qwiic_keyboard_message_received_ptr = qwiic_keyboard_message_received;

uint16_t qwiic_keyboard_keymap[QWIIC_KEYBOARD_LAYERS][QWIIC_KEYBOARD_ROWS][QWIIC_KEYBOARD_COLS] = {0};
uint8_t qwiic_keyboard_new_listening_address = QWIIC_KEYBOARD_LISTENING_ADDRESS_START;
uint8_t qwiic_keyboard_listening_address = QWIIC_KEYBOARD_LISTENING_ADDRESS_START;
uint8_t qwiic_keyboard_processing_slave = false;

void qwiic_keyboard_init(void) {
  twi2c_init();
  twi2c_start();
  twi2c_start_listening(qwiic_keyboard_listening_address, qwiic_keyboard_message_received_ptr);
}

void qwiic_keyboard_set_master(void) {
  twi2c_stop();
  twi2c_start();
  qwiic_keyboard_master = true;
}

void qwiic_keyboard_task(void) {
  if (USB_DRIVER.state == USB_ACTIVE)
    qwiic_keyboard_master = true;
  else
    qwiic_keyboard_master = false;
  if (qwiic_keyboard_master) {
    if (qwiic_keyboard_connected) {
      // send empty message, expecting matrix info
      twi2c_transmit(qwiic_keyboard_listening_address, NULL, 0);
      if (MSG_OK == twi2c_receive(qwiic_keyboard_listening_address,
        qwiic_keyboard_matrix_message, QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE
      )) {
        // majority of this is pulled from keyboard.c:keyboard_task()
        static qwiic_matrix_t matrix_prev[QWIIC_KEYBOARD_ROWS];
        qwiic_matrix_t matrix_row = 0;
        qwiic_matrix_t matrix_change = 0;
        qwiic_keyboard_processing_slave = true;
        SEND_STRING("K.");
        for (uint8_t r = 0; r < QWIIC_KEYBOARD_ROWS; r++) {
          matrix_row = qwiic_keyboard_matrix_message[r];
          matrix_change = matrix_row ^ matrix_prev[r];
          if (matrix_change) {
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
              if (matrix_change & ((qwiic_matrix_t)1<<c)) {
                action_exec((keyevent_t){
                  .key = (keypos_t){ .row = r, .col = c },
                  .pressed = (matrix_row & ((qwiic_matrix_t)1<<c)),
                  .time = (timer_read() | 1) /* time should not be 0 */
                });
                // record a processed key
                matrix_prev[r] ^= ((qwiic_matrix_t)1<<c);
                #ifdef QMK_KEYS_PER_SCAN
                  // only jump out if we have processed "enough" keys.
                  if (++keys_processed >= QMK_KEYS_PER_SCAN)
                #endif
                // process a key per task call
                goto MATRIX_LOOP_END;
              }
            }
          }
        }
        // call with pseudo tick event when no real key event.
        #ifdef QMK_KEYS_PER_SCAN
          // we can get here with some keys processed now.
          if (!keys_processed)
        #endif
        action_exec(TICK);
        MATRIX_LOOP_END:
        qwiic_keyboard_processing_slave = false;
      } else {
        // disconnect
        // qwiic_keyboard_connected = false;
      }
    } else {
      // send new address to listen on, expect back keymap
      twi2c_transmit(QWIIC_KEYBOARD_HANDSHAKE_ADDRESS, &qwiic_keyboard_new_listening_address, 1);
      if (MSG_OK == twi2c_receive(QWIIC_KEYBOARD_HANDSHAKE_ADDRESS,
        qwiic_keyboard_handshake_message, QWIIC_KEYBOARD_HANDSHAKE_MESSAGE_SIZE
      )) {
        qwiic_keyboard_connected = true;
        // increment address (for future implemenations of supporting multiple devices)
        qwiic_keyboard_new_listening_address+=2;
        // load keymap into memory
        qwiic_keyboard_read_keymap(qwiic_keyboard_handshake_message);
      }
    }
  }
}

uint8_t qwiic_keyboard_reply[MATRIX_ROWS];

void qwiic_keyboard_message_received(I2CDriver *i2cp, uint8_t * body, uint16_t size) {
  if (qwiic_keyboard_connected) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      qwiic_keyboard_reply[row] = matrix_get_row(row);
    }
    twi2c_reply(i2cp, qwiic_keyboard_reply, QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE);
  } else {
    qwiic_keyboard_connected = true;
    qwiic_keyboard_master = false;
    qwiic_keyboard_listening_address = body[0];
    qwiic_keyboard_write_keymap(qwiic_keyboard_reply);
    twi2c_reply(i2cp, qwiic_keyboard_reply, QWIIC_KEYBOARD_HANDSHAKE_MESSAGE_SIZE);
    twi2c_stop();
    twi2c_start();
    twi2c_start_listening(qwiic_keyboard_listening_address, qwiic_keyboard_message_received_ptr);
  }
}

// qwiic_keyboard_message_received_ptr = qwiic_keyboard_message_received;

__attribute__((optimize("O0")))
void qwiic_keyboard_write_keymap(uint8_t * pointer) {
  for (uint8_t layer = 0; layer < QWIIC_KEYBOARD_LAYERS; layer++) {
    for (uint8_t row = 0; row < QWIIC_KEYBOARD_ROWS; row++) {
      for (uint8_t col = 0; col < QWIIC_KEYBOARD_COLS; col++) {
        uint16_t keycode = pgm_read_word(&keymaps[layer][row][col]);
        *pointer++ = (keycode >> 8);
        *pointer++ = (keycode & 0xFF);
      }
    }
  }
}

void qwiic_keyboard_read_keymap(uint8_t * pointer) {
  for (uint8_t layer = 0; layer < QWIIC_KEYBOARD_LAYERS; layer++) {
    for (uint8_t row = 0; row < QWIIC_KEYBOARD_ROWS; row++) {
      for (uint8_t col = 0; col < QWIIC_KEYBOARD_COLS; col++) {
        uint16_t keycode = *pointer++;
        keycode |= (*pointer++) << 8;
        qwiic_keyboard_keymap[layer][row][col] = keycode;
      }
    }
  }
}

// overwrite the built-in function - slaves don't need to process keycodes
bool is_keyboard_master(void) {
  return qwiic_keyboard_master;
}

// overwrite the built-in function
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
  if (qwiic_keyboard_processing_slave) {
    // trick the built-in handling to accept our replacement keymap
    return qwiic_keyboard_keymap[(layer)][(key.row)][(key.col)];
  } else {
    // Read entire word (16bits)
    return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
  }
}
