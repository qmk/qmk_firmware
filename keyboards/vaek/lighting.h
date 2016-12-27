#ifndef LIGHTING_H
#define LIGHTING_H

void led_test(void);
void force_issi_refresh(void);
void set_backlight(uint8_t level);
void set_underglow(uint8_t red, uint8_t green, uint8_t blue);
void set_rgb(uint8_t rgb_led, uint8_t red, uint8_t green, uint8_t blue);
void set_backlight_by_keymap(uint8_t col, uint8_t row);

#endif