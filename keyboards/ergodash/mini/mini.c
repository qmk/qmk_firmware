#include "ergodash.h"

#ifdef AUDIO_ENABLE
    float tone_startup[][2] = SONG(STARTUP_SOUND);
    float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

#ifdef SSD1306OLED
void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    led_set_user(usb_led);
}
#endif
