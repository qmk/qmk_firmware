#include "rev_a.h"

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
  init_led();
}

void init_led(void){
  // Set on match, clear on TOP
  TCCR1A  = ((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1)| (1 << COM1B0)| (1 << COM1C1)| (1 << COM1C0)); // all leds on.
  // Phase + Frequency Correct PWM, Fcpu speed
  TCCR1B  = ((1 << CS10) | (1 << WGM13));
  // define end of timer
  ICR1 = TIMER_TOP;
  // default set to lowest, will not toggle
  led_set_color(RGB_OFF);

  brightness_level = DEFAULT_BRIGHTNESS_LEVEL;
  // Set our LED pins as output
  setPinOutput(B7);
  setPinOutput(C5);
  setPinOutput(C6);
}

bool led_update_user(led_t led_state) {
/*
By convention, return true from led_update_user() to get the led_update_kb() hook to run its code,
and return false when you would prefer not to run the code in led_update_kb().
*/
  if(LOCK_INDICATORS)
    return true;
  else
    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) { // just to illustrate, make changes if needed
  if(LAYER_INDICATOR){
    switch (get_highest_layer(state)) {
    case _FN1:
        led_set_color(RGB_PINK);
        break;
    case _FN2:
        led_set_color(RGB_ORANGE);
        break;
    default:
        led_set_color(RGB_OFF);
        break;
    }
  }
  return state;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // do not indicate multiple lock statuses in current implementation,
        // sorted by most likely first (if capslock is on, it will be purple, regardless of numlock state)
        if(led_state.caps_lock)
          led_set_color(RGB_ORANGE);
        else if(led_state.num_lock)
          led_set_color(RGB_PINK);
        else if(led_state.scroll_lock)
          led_set_color(RGB_CYAN);
        else if(led_state.compose)
          led_set_color(RGB_PURPLE);
        else if(led_state.kana)
          led_set_color(RGB_YELLOW);
        else
          led_set_color(RGB_OFF);
    }
    return res;
}

void led_set_color(uint8_t r, uint8_t g, uint8_t b){
    uint32_t base_brightness = cie_lightness(TIMER_TOP * (uint32_t)brightness_level / BRIGHTNESS_LEVELS);
    OCR1C = (uint32_t)r * (uint32_t)base_brightness / 0xFF;
    OCR1B = (uint32_t)g * (uint32_t)base_brightness / 0xFF;
    OCR1A = (uint32_t)b * (uint32_t)base_brightness / 0xFF;
}
// See http://jared.geek.nz/2013/feb/linear-led-pwm
uint16_t cie_lightness(uint16_t v) {
    if (v <= 5243)     // if below 8% of max
        return v / 9;  // same as dividing by 900%
    else {
        uint32_t y = (((uint32_t)v + 10486) << 8) / (10486 + 0xFFFFUL);  // add 16% of max and compare
        // to get a useful result with integer division, we shift left in the expression above
        // and revert what we've done again after squaring.
        y = y * y * y >> 8;
        if (y > 0xFFFFUL)  // prevent overflow
            return 0xFFFFU;
        else
            return (uint16_t)y;
    }
}
