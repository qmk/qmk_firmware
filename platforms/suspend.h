#pragma once

#include <stdint.h>
#include <stdbool.h>

void suspend_power_down(void);
bool suspend_wakeup_condition(void);
void suspend_wakeup_init(void);

void suspend_wakeup_init_user(void);
void suspend_wakeup_init_kb(void);
void suspend_wakeup_init_quantum(void);
void suspend_power_down_user(void);
void suspend_power_down_kb(void);
void suspend_power_down_quantum(void);

bool keypress_is_wakeup_key(uint8_t row, uint8_t col);
void update_matrix_state_after_wakeup(void);
void wakeup_matrix_handle_key_event(uint8_t row, uint8_t col, bool pressed);

#ifndef USB_SUSPEND_WAKEUP_DELAY
#    define USB_SUSPEND_WAKEUP_DELAY 0
#endif
