#include "split75.h"
#include "rgblight.h"

#include "progmem.h"
#include "i2c_master.h"

#include "action_layer.h"
#define LED_INDICATORS

extern inline void led_1_on(void);
extern inline void led_2_on(void);
extern inline void led_3_on(void);

extern inline void led_1_off(void);
extern inline void led_2_off(void);
extern inline void led_3_off(void);

void blink_all_leds(void);

uint8_t led0 = 0, led1 = 0, led2 = 0;

void indicator_init(void) {
    // D0, D1, and D6 are the indicators and D4 is the backlight
    setPinOutput(D0);
    setPinOutput(D1);
    setPinOutput(D6);
}

// for keyboard subdirectory level init functions
void matrix_init_kb(void) {
    // call user level keymaps, if any
    blink_all_leds();
    matrix_init_user();
}

void blink_all_leds(void) {
    led_3_on();
    wait_ms(50);
    led_2_on();
    wait_ms(50);
    led_1_on();
    wait_ms(50);
    led_3_off();
    wait_ms(50);
    led_2_off();
    wait_ms(50);
    led_1_off();
}

void keyboard_post_init_kb(void) {
    led_set_user(0);
    layer_state_set_user(layer_state);
    keyboard_post_init_user();
}

#if defined(LED_INDICATORS)
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        led_state.caps_lock ? led_2_on() : led_2_off();
    }
    return res;
}
#endif
