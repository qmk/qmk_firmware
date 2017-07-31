/* Copyright 2017 Joseph Wasson
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
#include "process_steno.h"
#include "quantum_keycodes.h"
#include "keymap_steno.h"
#include "virtser.h"

// TxBolt Codes
#define TXB_NUL 0
#define TXB_S_L 0b00000001
#define TXB_T_L 0b00000010
#define TXB_K_L 0b00000100
#define TXB_P_L 0b00001000
#define TXB_W_L 0b00010000
#define TXB_H_L 0b00100000
#define TXB_R_L 0b01000001
#define TXB_A_L 0b01000010
#define TXB_O_L 0b01000100
#define TXB_STR 0b01001000
#define TXB_E_R 0b01010000
#define TXB_U_R 0b01100000
#define TXB_F_R 0b10000001
#define TXB_R_R 0b10000010
#define TXB_P_R 0b10000100
#define TXB_B_R 0b10001000
#define TXB_L_R 0b10010000
#define TXB_G_R 0b10100000
#define TXB_T_R 0b11000001
#define TXB_S_R 0b11000010
#define TXB_D_R 0b11000100
#define TXB_Z_R 0b11001000
#define TXB_NUM 0b11010000

#define TXB_GRP0 0b00000000
#define TXB_GRP1 0b01000000
#define TXB_GRP2 0b10000000
#define TXB_GRP3 0b11000000
#define TXB_GRPMASK 0b11000000

#define TXB_GET_GROUP(code) ((code & TXB_GRPMASK) >> 6)

#define BOLT_STATE_SIZE 4
#define GEMINI_STATE_SIZE 6

uint8_t state[MAX(BOLT_STATE_SIZE, GEMINI_STATE_SIZE)] = {0};
uint8_t pressed = 0;
steno_mode_t mode;

uint8_t boltmap[64] = {
  TXB_NUL, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM,
  TXB_S_L, TXB_S_L, TXB_T_L, TXB_K_L, TXB_P_L, TXB_W_L, TXB_H_L,
  TXB_R_L, TXB_A_L, TXB_O_L, TXB_STR, TXB_STR, TXB_NUL, TXB_NUL,
  TXB_NUL, TXB_STR, TXB_STR, TXB_E_R, TXB_U_R, TXB_F_R, TXB_R_R,
  TXB_P_R, TXB_B_R, TXB_L_R, TXB_G_R, TXB_T_R, TXB_S_R, TXB_D_R,
  TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_Z_R
};

#define BOLTMAP_MASK (sizeof(boltmap) - 1)


void steno_clear_state(void) {
  memset(state, 0, sizeof(state));
}

void steno_init() {
  if (!eeconfig_is_enabled()) {
    eeconfig_init();
  }
  mode = eeprom_read_byte(EECONFIG_STENOMODE);
}

void steno_set_mode(steno_mode_t new_mode) {
  steno_clear_state();
  mode = new_mode;
  eeprom_update_byte(EECONFIG_STENOMODE, mode);
}

void send_steno_state(uint8_t size, bool send_empty) {
  for (uint8_t i = 0; i < size; ++i) {
    if (state[i] || send_empty) {
      virtser_send(state[i]);
    }
  }
  steno_clear_state();
}

bool update_state_bolt(uint8_t key) {
  uint8_t boltcode = boltmap[key];
  state[TXB_GET_GROUP(boltcode)] |= boltcode;
  return false;
}

bool send_state_bolt(void) {
  send_steno_state(BOLT_STATE_SIZE, false);
  virtser_send(0); // terminating byte
  return false;
}

bool update_state_gemini(uint8_t key) {
  state[key / 7] |= 1 << (6 - (key % 7));
  return false;
}

bool send_state_gemini(void) {
  state[0] |= 0x80; // Indicate start of packet
  send_steno_state(GEMINI_STATE_SIZE, true);
  return false;
}

bool process_steno(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QK_STENO_BOLT:
      if (IS_PRESSED(record->event)) {
        steno_set_mode(STENO_MODE_BOLT);
      }
      return false;

    case QK_STENO_GEMINI:
      if (IS_PRESSED(record->event)) {
        steno_set_mode(STENO_MODE_GEMINI);
      }
      return false;

    case STN__MIN...STN__MAX:
      if (IS_PRESSED(record->event)) {
        uint8_t key = keycode - QK_STENO;
        ++pressed;
        switch(mode) {
          case STENO_MODE_BOLT:
            return update_state_bolt(key);
          case STENO_MODE_GEMINI:
            return update_state_gemini(key);
          default:
            return false;
        }
      } else {
        --pressed;
        if (pressed <= 0) {
          pressed = 0;
          switch(mode) {
            case STENO_MODE_BOLT:
              return send_state_bolt();
            case STENO_MODE_GEMINI:
              return send_state_gemini();
            default:
              return false;
          }
        }
      }

  }
  return true;
}
