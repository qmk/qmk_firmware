
#pragma once
#include "../__init__.h"

enum pr_response sturdy_pr(uint16_t, keyrecord_t*);
enum pr_response process_double_tap(uint16_t keycode, keyrecord_t *record);
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* mods);
void enqueue(int keycode);
void dequeue(void);
void print_queue(void);
void refill_queue(void);

uint32_t enqueue_space(uint32_t trigger_time, void *cb_arg);
void refresh_token(void);
bool is_ctrl_backspace(uint16_t keycode, keyrecord_t* record, uint8_t* mods);

#define record_case(symbol, keycode) \
    case symbol: \
        enqueue(keycode); \
        continue
