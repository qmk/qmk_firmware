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
#define QWIIC_KEYBOARD_ROWS   8
#define QWIIC_KEYBOARD_COLS   8

#if (QWIIC_KEYBOARD_COLS <= 8)
typedef uint8_t qwiic_row_t;
#elif (QWIIC_KEYBOARD_COLS <= 16)
typedef uint16_t qwiic_row_t;
#elif (QWIIC_KEYBOARD_COLS <= 32)
typedef uint32_t qwiic_row_t;
#else
#error "QWIIC_KEYBOARD_COLS: invalid value"
#endif

#define QWIIC_KEYBOARD_HANDSHAKE_ADDRESS       0b01010100
#define QWIIC_KEYBOARD_LISTENING_ADDRESS_START 0b01010110
#define QWIIC_KEYBOARD_MAX_DEVICES             1

#define QWIIC_KEYBOARD_KEYMAP_MESSAGE_SIZE     (QWIIC_KEYBOARD_LAYERS * QWIIC_KEYBOARD_ROWS * QWIIC_KEYBOARD_COLS)
#define QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE     (QWIIC_KEYBOARD_ROWS)

void qwiic_keyboard_write_keymap(uint8_t * pointer);
void qwiic_keyboard_read_keymap(uint8_t * pointer, uint8_t index);

bool qwiic_keyboard_master = false;
bool qwiic_keyboard_received_message = false;
bool qwiic_keyboard_connected[QWIIC_KEYBOARD_MAX_DEVICES] = { false };
uint8_t qwiic_keyboard_keymap_message[QWIIC_KEYBOARD_KEYMAP_MESSAGE_SIZE] = {0};
uint8_t qwiic_keyboard_matrix_message[QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE] = {0};
twi2c_message_received qwiic_keyboard_message_received_ptr = qwiic_keyboard_message_received;
float song_one_up[][2]  = SONG(ONE_UP_SOUND);
float song_zelda[][2]  = SONG(ZELDA_PUZZLE);
uint8_t first_message = 0;
uint8_t first_message_slave = 0;

uint16_t qwiic_keyboard_keymap[QWIIC_KEYBOARD_MAX_DEVICES][QWIIC_KEYBOARD_LAYERS][QWIIC_KEYBOARD_ROWS][QWIIC_KEYBOARD_COLS] = {0};
bool qwiic_keyboard_keymap_initialised[QWIIC_KEYBOARD_MAX_DEVICES] = { false };
uint8_t qwiic_keyboard_listening_address[QWIIC_KEYBOARD_MAX_DEVICES] = { 0 };
#define QWIIC_KEYBOARD_NOT_PROCESSING 255
uint8_t qwiic_keyboard_processing_slave = QWIIC_KEYBOARD_NOT_PROCESSING;

void qwiic_keyboard_init(void) {
  twi2c_init();
  twi2c_start();
  twi2c_start_listening(QWIIC_KEYBOARD_HANDSHAKE_ADDRESS, qwiic_keyboard_message_received_ptr);
}

void qwiic_keyboard_set_master(void) {
  if (!qwiic_keyboard_received_message) {
    twi2c_stop();
    twi2c_start();
    qwiic_keyboard_master = true;
    if (first_message == 0) {
      PLAY_SONG(song_one_up);
    }
    first_message += 1;
  }
}

void qwiic_keyboard_set_slave(void) {
  qwiic_keyboard_received_message = true;
  if (first_message_slave == 0) {
    PLAY_SONG(song_zelda);
  }
  first_message_slave += 1;
}

static uint8_t keymap_command[1] = { 0x01 };
static uint8_t matrix_command[1] = { 0x02 };
static uint8_t look_counter = 0;

// uint8_t get_available_device_index(void) {
//   for (uint8_t i = 0; i < QWIIC_KEYBOARD_MAX_DEVICES; i++) {
//     if (!qwiic_keyboard_connected[i])
//       return i;
//   }
//   return 255;
// }

void qwiic_keyboard_get_matrix(uint8_t device_i) {
  // msg_t ret = twi2c_transmit_receive(qwiic_keyboard_listening_address[device_i],
  //   matrix_command, 1,
  //   qwiic_keyboard_matrix_message, QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE
  // );
  twi2c_transmit(qwiic_keyboard_listening_address[device_i], matrix_command, 1);
  msg_t ret = twi2c_receive(qwiic_keyboard_listening_address[device_i],
    qwiic_keyboard_matrix_message, QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE
  );
  switch (ret) {
    // majority of this is pulled from keyboard.c:keyboard_task()
    case I2C_OK:
      qwiic_keyboard_processing_slave = device_i;
      static qwiic_row_t matrix_prev[QWIIC_KEYBOARD_ROWS];
      qwiic_row_t matrix_row = 0;
      qwiic_row_t matrix_change = 0;
      #ifdef QMK_KEYS_PER_SCAN
        uint8_t keys_processed = 0;
      #endif
      for (uint8_t r = 0; r < QWIIC_KEYBOARD_ROWS; r++) {
        matrix_row = qwiic_keyboard_matrix_message[r];
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
          for (uint8_t c = 0; c < QWIIC_KEYBOARD_COLS; c++) {
            if (matrix_change & ((qwiic_row_t)1<<c)) {
              action_exec((keyevent_t){
                .key = (keypos_t){ .row = r, .col = c },
                .pressed = (matrix_row & ((qwiic_row_t)1<<c)),
                .time = (timer_read() | 1) /* time should not be 0 */
              });
              // record a processed key
              matrix_prev[r] ^= ((qwiic_row_t)1<<c);
              #ifdef QMK_KEYS_PER_SCAN
                // only jump out if we have processed "enough" keys.
                if (++keys_processed >= QMK_KEYS_PER_SCAN)
              #endif
              // process a key per task call
              goto QWIIC_MATRIX_LOOP_END;
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
      QWIIC_MATRIX_LOOP_END:
      qwiic_keyboard_processing_slave = QWIIC_KEYBOARD_NOT_PROCESSING;
    // if (first_message == 100) {
    //   PLAY_SONG(song_one_up);
    // }
    // first_message += 1;
      break;
    case I2C_ERROR:
      break;
    default:
      twi2c_start();
      break;
  }
}

void qwiic_keyboard_task(void) {
  if (USB_DRIVER.state == USB_ACTIVE)
    qwiic_keyboard_set_master();
  if (qwiic_keyboard_master) {
    for (uint8_t device_i = 0; device_i < QWIIC_KEYBOARD_MAX_DEVICES; device_i++) {
      if (qwiic_keyboard_connected[device_i]) {
        // send empty message, expecting matrix info
        if (!qwiic_keyboard_keymap_initialised[device_i]) {
          // if (MSG_OK == twi2c_transmit_receive(qwiic_keyboard_listening_address[device_i],
          //   keymap_command, 1,
          //   qwiic_keyboard_keymap_message, QWIIC_KEYBOARD_KEYMAP_MESSAGE_SIZE
          // )) {
          twi2c_transmit(qwiic_keyboard_listening_address[device_i], keymap_command, 1);
          if (MSG_OK == twi2c_receive(qwiic_keyboard_listening_address[device_i],
            qwiic_keyboard_keymap_message, QWIIC_KEYBOARD_KEYMAP_MESSAGE_SIZE
          )) {
            // load keymap into memory
            qwiic_keyboard_keymap_initialised[device_i] = true;
            qwiic_keyboard_read_keymap(qwiic_keyboard_keymap_message, device_i);
            qwiic_keyboard_get_matrix(device_i);
          }
        } else {
          qwiic_keyboard_get_matrix(device_i);
        } // end else - not init
      } else { // if not connected
        //if (look_counter == 0) {
          // send new address to listen on, expect back keymap
          uint8_t new_address = QWIIC_KEYBOARD_LISTENING_ADDRESS_START + (device_i*2);
          uint8_t address_copy = 0;
          twi2c_transmit(QWIIC_KEYBOARD_HANDSHAKE_ADDRESS, &new_address, 1);
          if (MSG_OK == twi2c_receive(QWIIC_KEYBOARD_HANDSHAKE_ADDRESS,
            &address_copy, 1
          )) {
          // if (MSG_OK == twi2c_transmit_receive(QWIIC_KEYBOARD_HANDSHAKE_ADDRESS,
          //   &new_address, 1,
          //   &address_copy, 1
          // )) {
            send_byte(address_copy);
            //if (address_copy == new_address) {
              PLAY_SONG(song_one_up);
              qwiic_keyboard_connected[device_i] = true;
              qwiic_keyboard_listening_address[device_i] = new_address;
            //}
          }
        //} // end if - look for new
      } // end else - connected
    } // end for - devices
    look_counter = ((look_counter + 1) % 150);
  } // end if - master
}

void qwiic_keyboard_message_received(I2CDriver *i2cp, uint8_t * body, uint16_t size) {
  qwiic_keyboard_set_slave();
  switch (body[0]) {
    // send keymap
    case 0x01:
      qwiic_keyboard_write_keymap(qwiic_keyboard_keymap_message);
      twi2c_reply(i2cp, qwiic_keyboard_keymap_message, QWIIC_KEYBOARD_KEYMAP_MESSAGE_SIZE);
      break;
    // send matrix
    case 0x02:
    case 0x00:
      for (uint8_t row = 0; row < QWIIC_KEYBOARD_ROWS; row++) {
        if (row < MATRIX_ROWS) {
          qwiic_keyboard_matrix_message[row] = matrix_get_row(row);
        } else {
          qwiic_keyboard_matrix_message[row] = 0;
        }
      }
      twi2c_reply(i2cp, qwiic_keyboard_matrix_message, QWIIC_KEYBOARD_MATRIX_MESSAGE_SIZE);
      break;
    default:
      qwiic_keyboard_listening_address[0] = body[0];
      twi2c_add_listening(body[0]);
      twi2c_remove_listening(QWIIC_KEYBOARD_HANDSHAKE_ADDRESS);
      qwiic_keyboard_connected[0] = true;
      qwiic_keyboard_master = false;
      twi2c_reply(i2cp, qwiic_keyboard_listening_address, 1);
      break;
  }
}

// qwiic_keyboard_message_received_ptr = qwiic_keyboard_message_received;

__attribute__((optimize("O0")))
void qwiic_keyboard_write_keymap(uint8_t * pointer) {
  for (uint8_t layer = 0; layer < QWIIC_KEYBOARD_LAYERS; layer++) {
    for (uint8_t row = 0; row < QWIIC_KEYBOARD_ROWS; row++) {
      for (uint8_t col = 0; col < QWIIC_KEYBOARD_COLS; col++) {
        uint16_t keycode = 0;
        keycode = pgm_read_word(&keymaps[layer][row][col]);
        *pointer++ = (keycode >> 8);
        *pointer++ = (keycode & 0xFF);
      }
    }
  }
}

void qwiic_keyboard_read_keymap(uint8_t * pointer, uint8_t index) {
  for (uint8_t layer = 0; layer < QWIIC_KEYBOARD_LAYERS; layer++) {
    for (uint8_t row = 0; row < QWIIC_KEYBOARD_ROWS; row++) {
      for (uint8_t col = 0; col < QWIIC_KEYBOARD_COLS; col++) {
        uint16_t keycode = ((*pointer++) << 8);
        keycode |= (*pointer++);
        qwiic_keyboard_keymap[index][layer][row][col] = keycode;
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
  if (qwiic_keyboard_processing_slave == QWIIC_KEYBOARD_NOT_PROCESSING) {
    // Read entire word (16bits)
    return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
  } else {
    // trick the built-in handling to accept our replacement keymap
    return qwiic_keyboard_keymap[qwiic_keyboard_processing_slave][(layer)][(key.row)][(key.col)];
  }
}
