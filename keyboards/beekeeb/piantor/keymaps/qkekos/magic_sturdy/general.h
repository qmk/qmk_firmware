
#pragma once
#include "../__init__.h"

#define PREV_KEYS_QUEUE_SIZE 10
#define MAGIC_KEY_TIMEOUT 1500

bool strd_process_record(uint16_t keycode, keyrecord_t *record, bool *return_value);
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods);
void enqueue(int keycode);
void dequeue(void);
void remember_last_key(int prev_keycode, int key_to_remember);

extern int prev_keys_queue[];
extern int rep_key_count;
extern int alt_rep_key_count;
extern int last_key_pressed_time;

#define last_queue_key prev_keys_queue[PREV_KEYS_QUEUE_SIZE - 1]
#define queue(i) prev_keys_queue[PREV_KEYS_QUEUE_SIZE + i]
