#ifndef ACTION_PSEUDO_LUT_H
#define ACTION_PSEUDO_LUT_H

#define SHIFT_BIT_SIZE (0xE7 / 8 + 1) // 1bit per 1key

#define IS_LSFT(kc) ((QK_LSFT & (kc)) == QK_LSFT)

void action_pseudo_lut(keyrecord_t *, uint8_t, const uint16_t (*)[2]);
uint16_t convert_keycode(const uint16_t (*)[2], uint16_t, bool);

uint8_t get_shift_bit(uint16_t);
void add_shift_bit(uint16_t);
void del_shift_bit(uint16_t);

#endif
