#include QMK_KEYBOARD_H
#include <stdio.h>
#include "mcrown.h"

#ifdef OLED_VERTICAL
#define KEYLOG_LEN (48)
#else
#define KEYLOG_LEN (20)
#endif

extern void add_keylog(uint16_t keycode);
extern void update_log(void);
extern void render_keylogger_status(void);

extern char keylog_str[KEYLOG_LEN];
extern uint8_t  keylogs_str_idx;
extern uint16_t log_timer;

extern uint8_t is_master;
