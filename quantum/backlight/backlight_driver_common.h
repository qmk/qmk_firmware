#pragma once

void backlight_pins_init(void);
void backlight_pins_on(void);
void backlight_pins_off(void);

void breathing_task(void);

#ifdef SPLIT_KEYBOARD
void backlight_pins_init_right(void);
void backlight_pins_on_right(void);
void backlight_pins_off_right(void);

void breathing_task_right(void);
#endif