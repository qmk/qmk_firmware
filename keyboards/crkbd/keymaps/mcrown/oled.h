#include QMK_KEYBOARD_H
#include <stdio.h>
#include "mcrown.h"

#define KEYLOG_LEN 19

extern void add_keylog(uint16_t keycode);
extern void update_log(void);
extern void render_keylogger_status(void);

extern char keylog_str[KEYLOG_LEN];
extern uint8_t  keylogs_str_idx;
extern uint16_t log_timer;

extern uint8_t is_master;
