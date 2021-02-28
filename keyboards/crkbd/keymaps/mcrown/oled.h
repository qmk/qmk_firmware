#include QMK_KEYBOARD_H
#include <stdio.h>
#include "mcrown.h"

#ifdef OLED_VERTICAL
#define KEYLOG_LEN (48)
#else
#define KEYLOG_LEN (19)
#endif

#define KEYLOG_EOL_LEN (KEYLOG_LEN+1)

extern void add_keylog(uint16_t keycode);
extern void update_log(void);
extern void render_keylogger_status(void);

extern uint8_t is_master;
