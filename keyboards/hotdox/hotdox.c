#include "hotdox.h"
#include "backlight.h"
#include "quantum.h"

extern inline void ergodox_right_led_1_on(void);
extern inline void ergodox_right_led_2_on(void);
extern inline void ergodox_right_led_3_on(void);
extern inline void ergodox_right_led_on(uint8_t led);

extern inline void ergodox_right_led_1_off(void);
extern inline void ergodox_right_led_2_off(void);
extern inline void ergodox_right_led_3_off(void);
extern inline void ergodox_right_led_off(uint8_t led);

extern inline void ergodox_led_all_off(void);

void ergodox_led_init(void);
void ergodox_blink_all_leds(void);

void matrix_init_kb(void) {
  ergodox_led_init();
  //ergodox_blink_all_leds();
  matrix_init_user();
}

void ergodox_led_init(void)
 {
     DDRB  |= (1 << PB4);
     PORTB &= ~(1 << PB4);

     DDRB  |= (1 << PB5);
     PORTB &= ~(1 << PB5);

     DDRB  |= (1 << PB6);
     PORTB &= ~(1 << PB6);

     //DDRB  |=  ((1 << PB5) | (1 << PB6));
     //PORTB &= ~((1 << PB5) | (1 << PB6));
}

void ergodox_blink_all_leds(void)
{
    ergodox_led_all_off();
    ergodox_led_all_set(LED_BRIGHTNESS_HI);
    //ergodox_right_led_1_on();
    _delay_ms(50);
    //ergodox_right_led_2_on();
    _delay_ms(50);
    //ergodox_right_led_3_on();
    _delay_ms(50);
    //ergodox_right_led_1_off();
    _delay_ms(50);
    //ergodox_right_led_2_off();
    _delay_ms(50);
    //ergodox_right_led_3_off();
    //ergodox_led_all_on();
    //_delay_ms(333);
    //ergodox_led_all_off();
}
