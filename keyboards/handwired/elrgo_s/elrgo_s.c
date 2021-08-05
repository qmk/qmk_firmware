#include "elrgo_s.h"

#ifdef SSD1306OLED
void led_set_kb(uint8_t usb_led) {
    // Put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    led_set_user(usb_led);
}
#endif

void matrix_init_kb(void) {
	matrix_init_user();
};
