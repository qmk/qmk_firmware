
// ....................................................................... Audio

void matrix_init_user(void)
{
#ifdef STENO_ENABLE
  steno_set_mode(STENO_MODE_BOLT);          // or STENO_MODE_GEMINI
#endif
#ifdef AUDIO_ENABLE
  startup_user();
#endif
}

#ifdef AUDIO_ENABLE
#ifdef BACKLIGHT_ENABLE
void led_set_user(uint8_t usb_led)
{
  static uint8_t old_usb_led = 0;
  _delay_ms(10);                            // gets rid of tick
  if (!is_playing_notes()) {
    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK))) {
      // if capslock LED is turning on
      PLAY_SONG(song_caps_on);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK))) {
      // if capslock LED is turning off
      PLAY_SONG(song_caps_off);
    }
  }
  old_usb_led = usb_led;
}
#endif

void startup_user(void)
{
  _delay_ms(20);                            // gets rid of tick
  PLAY_SONG(song_startup);
}

void shutdown_user(void)
{
  PLAY_SONG(song_goodbye);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}
#endif
