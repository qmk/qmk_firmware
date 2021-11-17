#include "combo.h"

enum combos {
    JK_ESC,
    YU_COM,
    UI_COM,
    IO_COM,
    QW_COM,
    COM_SLS,
    COM_DOT,
    M_COMM,
    N_M,
    OP_COM,
};

const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM yu_combo[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM com_sls[] = {KC_COMMA, KC_SLSH, COMBO_END};
const uint16_t PROGMEM com_dot[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM m_comm[] = {KC_M,KC_COMMA,  COMBO_END};
const uint16_t PROGMEM n_m[] = {KC_N, KC_M,COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [JK_ESC] = COMBO(jk_combo, KC_ESC),
    [YU_COM] = COMBO(yu_combo, KC_CIRC),
    [UI_COM] = COMBO(ui_combo, KC_DLR),
    [IO_COM] = COMBO(io_combo, KC_TILD),
    [QW_COM] = COMBO(qw_combo, KC_AT),
    [COM_SLS] = COMBO(com_sls, KC_QUES),
    [COM_DOT] = COMBO(com_dot, KC_QUES),
    [M_COMM] = COMBO(m_comm, KC_ESC),
    [N_M] = COMBO(n_m, KC_DLR),
};
