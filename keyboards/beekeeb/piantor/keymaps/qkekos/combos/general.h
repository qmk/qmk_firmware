
#pragma once
#include "../__init__.h"

void process_combo_event_user(uint16_t combo_index, bool pressed);
uint16_t get_combo_term(uint16_t index, combo_t *combo);
int get_combo_action(int combo_index);
