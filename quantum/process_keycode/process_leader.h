#ifndef PROCESS_LEADER_H
#define PROCESS_LEADER_H

#include "quantum.h"

bool process_leader(uint16_t keycode, keyrecord_t *record);

void leader_start(void);
void leader_end(void);

#ifndef LEADER_TIMEOUT
  #define LEADER_TIMEOUT 200
#endif
#define SEQ_ONE_KEY(key) if (leader_sequence[0] == (key) && leader_sequence[1] == 0 && leader_sequence[2] == 0 && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_TWO_KEYS(key1, key2) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == 0 && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_THREE_KEYS(key1, key2, key3) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_FOUR_KEYS(key1, key2, key3, key4) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == (key4) && leader_sequence[4] == 0)
#define SEQ_FIVE_KEYS(key1, key2, key3, key4, key5) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == (key4) && leader_sequence[4] == (key5))

#define LEADER_EXTERNS() extern bool leading; extern uint16_t leader_time; extern uint16_t leader_sequence[5]; extern uint8_t leader_sequence_size
#define LEADER_DICTIONARY() if (leading && timer_elapsed(leader_time) > LEADER_TIMEOUT)

#endif