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

#define QWIIC_KEYBOARD_LAYERS 16
#define QWIIC_KEYBOARD_ROWS 8
#define QWIIC_KEYBOARD_COLS 8

#define QWIIC_KEYBOARD_HANDSHAKE_ADDRESS 0b01010100
#define QWIIC_KEYBOARD_LISTENING_ADDRESS_START 0b01010110
#define QWIIC_KEYBOARD_HANDSHAKE_MESSAGE_SIZE (2 + (QWIIC_KEYBOARD_LAYERS * QWIIC_KEYBOARD_ROWS * QWIIC_KEYBOARD_COLS))
#define QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE MATRIX_ROWS

bool qwiic_keyboard_master = false;
bool qwiic_keyboard_connected = false;
uint8_t * qwiic_keyboard_handshake_message = {0};
uint8_t * qwiic_keyboard_matrix_message[QWIIC_KEYBOARD_ROWS] = {0};

uint16_t qwiic_keyboard_keymap[QWIIC_KEYBOARD_LAYERS][QWIIC_KEYBOARD_ROWS][QWIIC_KEYBOARD_COLS] = {0};
uint8_t qwiic_keyboard_new_listening_address = QWIIC_KEYBOARD_LISTENING_ADDRESS_START;
uint8_t qwiic_keyboard_listening_address = QWIIC_KEYBOARD_LISTENING_ADDRESS_START;
uint8_t qwiic_keyboard_matrix_rows;
uint8_t qwiic_keyboard_matrix_cols;

void qwiic_keyboard_setup(void) {
  twi2c_start_listening(qwiic_keyboard_listening_address, qwiic_keyboard_message_received);
}

void qwiic_keyboard_set_master() {
  twi2c_stop();
  qwiic_keyboard_master = true;
}

void qwiic_keyboard_task(void) {
  if (qwiic_keyboard_master) {
    if (qwiic_keyboard_connected) {
      if (MSG_OK == twi2c_transmit_receive(qwiic_keyboard_listening_address,
        NULL, 0,
        qwiic_keyboard_matrix_message, QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE
      )) {
        // process key event
      } else {
        // disconnect
      }
    }
    if (MSG_OK == twi2c_transmit_receive(QWIIC_KEYBOARD_HANDSHAKE_ADDRESS,
      qwiic_keyboard_new_listening_address, 1,
      qwiic_keyboard_handshake_message, QWIIC_KEYBOARD_HANDSHAKE_MESSAGE_SIZE
    )) {
      qwiic_keyboard_new_listening_address+=2;
      uint8_t * message_pointer = qwiic_keyboard_handshake_message;
      qwiic_keyboard_matrix_rows = *message_pointer++;
      qwiic_keyboard_matrix_cols = *message_pointer++;
      qwiic_keyboard_read_keymap(message_pointer);
    }
  }
}

twi2c_message_received qwiic_keyboard_message_received;
extern matrix_row_t matrix[MATRIX_ROWS];
uint8_t * qwiic_keyboard_reply;

void qwiic_keyboard_message_received(uint8_t * body, uint16_t size) {
  if (qwiic_keyboard_connected) {
    memcpy(qwiic_keyboard_reply, matrix, QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE);
    twi2c_reply(qwiic_keyboard_reply, QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE);
  } else {
    qwiic_keyboard_connected = true;
    qwiic_keyboard_listening_address
    uint8_t * message_pointer = qwiic_keyboard_reply;
    *message_pointer++ = MATRIX_ROWS;
    *message_pointer++ = MATRIX_COLS;
    qwiic_keyboard_write_keymap(message_pointer);
    twi2c_reply(qwiic_keyboard_reply, QWIIC_KEYBOARD_HANDSHAKE_MESSAGE_SIZE);
    twi2c_stop();
    twi2c_start_listening(qwiic_keyboard_listening_address, qwiic_keyboard_message_received);
  }
}

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
