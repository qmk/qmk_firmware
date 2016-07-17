#include "process_leader.h"

__attribute__ ((weak))
void leader_start(void) {}

__attribute__ ((weak))
void leader_end(void) {}

// Leader key stuff
bool leading = false;
uint16_t leader_time = 0;

uint16_t leader_sequence[5] = {0, 0, 0, 0, 0};
uint8_t leader_sequence_size = 0;

bool process_leader(uint16_t keycode, keyrecord_t *record) {
  // Leader key set-up
  if (record->event.pressed) {
    if (!leading && keycode == KC_LEAD) {
      leader_start();
      leading = true;
      leader_time = timer_read();
      leader_sequence_size = 0;
      leader_sequence[0] = 0;
      leader_sequence[1] = 0;
      leader_sequence[2] = 0;
      leader_sequence[3] = 0;
      leader_sequence[4] = 0;
      return false;
    }
    if (leading && timer_elapsed(leader_time) < LEADER_TIMEOUT) {
      leader_sequence[leader_sequence_size] = keycode;
      leader_sequence_size++;
      return false;
    }
  }
  return true;
}