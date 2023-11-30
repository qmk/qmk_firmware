
// ....................................................................... Audio

void matrix_init_user(void)
{
#ifdef STENO_ENABLE
  steno_set_mode(STENO_MODE_BOLT);          // or STENO_MODE_GEMINI
#endif
}

#ifdef AUDIO_ENABLE
#ifdef BACKLIGHT_ENABLE
bool led_update_user(led_t led_state)
{
  static led_t old_led_state = {0};
  _delay_ms(10);                            // gets rid of tick
  if (!is_playing_notes()) {
    if (led_state.caps_lock && !old_led_state.caps_lock) {
      // if capslock LED is turning on
      PLAY_SONG(song_caps_on);
    }
    else if (!led_state.caps_lock && old_led_state.caps_lock) {
      // if capslock LED is turning off
      PLAY_SONG(song_caps_off);
    }
  }
  old_led_state = led_state;
  return false;
}
#endif
#endif
