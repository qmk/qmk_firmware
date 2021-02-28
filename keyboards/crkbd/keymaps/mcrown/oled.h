#include QMK_KEYBOARD_H
#include <stdio.h>
#include "mcrown.h"

#ifdef OLED_VERTICAL
#define KEYLOG_LEN (49)
#else
#define KEYLOG_LEN (20)
#endif

extern void add_keylog(uint16_t keycode);
extern void update_log(void);
extern void render_keylogger_status(void);

extern uint8_t is_master;
