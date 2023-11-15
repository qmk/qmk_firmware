
#pragma once
#include "../__init__.h"

#define MAGIC_KEY_TIMEOUT 500

bool strd_process_record(uint16_t keycode, keyrecord_t *record, bool *return_value);
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods);

extern int prev_last_key;
extern int rep_key_count;
extern int alt_rep_key_count;
extern int last_key_pressed_time;
