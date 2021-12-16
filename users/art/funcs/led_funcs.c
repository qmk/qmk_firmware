__attribute__ ((weak)) void num_led_on(void) {}
__attribute__ ((weak)) void num_led_off(void) {}
__attribute__ ((weak)) void caps_led_on(void) {}
__attribute__ ((weak)) void caps_led_off(void) {}
__attribute__ ((weak)) void scroll_led_on(void) {}
__attribute__ ((weak)) void scroll_led_off(void) {}

static bool hw_caps_on;

bool led_update_user(led_t led_state) {
  // only use caps LED - ignore Num & Scroll
  if (led_state.caps_lock) {
    caps_led_on();
  } else {
    caps_led_off();
  }

  hw_caps_on = led_state.caps_lock;
  return false; // 'false' prevents led_update_kb from firing
}

void blink_all_leds(void) {
  num_led_on();
  scroll_led_on();
  wait_ms(BLINKING_INTERVAL);
  num_led_off();
  scroll_led_off();
  wait_ms(BLINKING_INTERVAL);
  num_led_on();
  scroll_led_on();
  wait_ms(BLINKING_INTERVAL);
  num_led_off();
  scroll_led_off();
  wait_ms(BLINKING_INTERVAL);
  num_led_on();
  scroll_led_on();
  wait_ms(BLINKING_INTERVAL);
  num_led_off();
  scroll_led_off();
}

void led_show_variable_status(bool value) {
  if (value) {
    num_led_on();
    wait_ms(BLINKING_INTERVAL);
    num_led_off();
    wait_ms(BLINKING_INTERVAL);
    num_led_on();
    wait_ms(BLINKING_INTERVAL);
    num_led_off();
    wait_ms(BLINKING_INTERVAL);
    num_led_on();
    wait_ms(BLINKING_INTERVAL);
    num_led_off();
  } else {
    scroll_led_on();
    wait_ms(BLINKING_INTERVAL);
    scroll_led_off();
    wait_ms(BLINKING_INTERVAL);
    scroll_led_on();
    wait_ms(BLINKING_INTERVAL);
    scroll_led_off();
    wait_ms(BLINKING_INTERVAL);
    scroll_led_on();
    wait_ms(BLINKING_INTERVAL);
    scroll_led_off();
  }
}