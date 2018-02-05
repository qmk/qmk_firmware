#include "gherkin.h"
#include "keymap_steno.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  KEYMAP(
    STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
    STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
    STN_NUM, STN_NUM, STN_A,   STN_O,   STN_NUM, STN_E,   STN_U,   STN_NUM, STN_NUM, STN_NUM),
};

void matrix_init_user() {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
}