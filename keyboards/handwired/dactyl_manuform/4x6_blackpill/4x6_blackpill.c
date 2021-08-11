#include "4x6_blackpill.h"

void keyboard_pre_init_kb(void) {
    keyboard_pre_init_user();
}

#ifdef SSD1306OLED
void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    led_set_user(usb_led);
}
#endif

void matrix_init_kb(void) {
	matrix_init_user();
};

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Indexccxxz
  {0, NO_LED, NO_LED,NO_LED,NO_LED,NO_LED },
  {NO_LED, NO_LED, NO_LED,NO_LED,NO_LED,NO_LED },
  {NO_LED, NO_LED, NO_LED,NO_LED,NO_LED,NO_LED },
  {NO_LED, NO_LED, NO_LED,NO_LED,NO_LED,NO_LED },
  {NO_LED, NO_LED, NO_LED,NO_LED,NO_LED,NO_LED },
  {NO_LED, NO_LED, NO_LED,NO_LED,NO_LED,NO_LED },
  {NO_LED, NO_LED, NO_LED,NO_LED,NO_LED,NO_LED },
  {NO_LED, NO_LED, NO_LED,NO_LED,NO_LED,NO_LED }
}, {
  //LED Index to Physical Positon
  {0,   0}
}, {
  4          
} };
#endif
