#include "kanagawa.h"

#ifdef SSD1306OLED
void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    led_set_user(usb_led);
}
#endif


#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) { return encoder_update_user(index, clockwise); }
#endif

void matrix_init_kb(void) {	matrix_init_user(); };

void shutdown_user(void) { }