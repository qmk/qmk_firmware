#include "csc027.h"
#include "custom_audio.h"

#if defined(AUDIO_ENABLE)

float tone_on[][2] = SONG(E__NOTE(_G6));
float tone_off[][2] = SONG(E__NOTE(_D5));

void on_usb_led_off(void) {
    PLAY_SONG(tone_off);
}

void on_usb_led_on(void) {
    PLAY_SONG(tone_on);
}

#endif
