#include "process_steno.h"
#include "quantum_keycodes.h"
#include "keymap_steno.h"
#include "virtser.h"

uint8_t state[4] = {0};
uint8_t pressed = 0;


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

uint8_t boltmap[64] = {
  TXB_NUL, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM,
  TXB_S_L, TXB_S_L, TXB_T_L, TXB_K_L, TXB_P_L, TXB_W_L, TXB_H_L,
  TXB_R_L, TXB_A_L, TXB_O_L, TXB_STR, TXB_STR, TXB_NUL, TXB_NUL,
  TXB_NUL, TXB_STR, TXB_STR, TXB_E_R, TXB_U_R, TXB_F_R, TXB_R_R,
  TXB_P_R, TXB_B_R, TXB_L_R, TXB_G_R, TXB_T_R, TXB_S_R, TXB_D_R,
  TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_Z_R
};

#define BOLTMAP_MASK (sizeof(boltmap) - 1)

void send_steno_state(void) {
  for (uint8_t i = 0; i < 4; ++i) {
    if (state[i]) {
      virtser_send(state[i]);
      state[i] = 0;
    }
  }
  virtser_send(0);
}

bool process_steno(uint16_t keycode, keyrecord_t *record) {
  if(keycode >= QK_STENO && keycode <= QK_STENO_MAX) {
    if(IS_PRESSED(record->event)) {
      uint8_t boltcode = boltmap[keycode & BOLTMAP_MASK];
      ++pressed;
      state[TXB_GET_GROUP(boltcode)] |= boltcode;
    } else {
      --pressed;
      if (pressed <= 0) {
        pressed = 0; // protect against spurious up keys
        send_steno_state();
      }
    }
    return false;
  }

  return true;
}
