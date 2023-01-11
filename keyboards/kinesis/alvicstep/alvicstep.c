#include "kinesis.h"

// begin section origin  https://github.com/alvicstep/tmk_keyboard 

void all_led_off(void)
{
        PORTD = 0b11111111;
}

void all_led_on(void)
{
        PORTD = 0b00000000;
}
void num_lock_led_on(void)
{
        PORTD = 0b11101111;
}

void caps_lock_led_on(void)
{
        PORTD = 0b01111111;
}

void scroll_lock_led_on(void)
{
        PORTD = 0b11011111;
}
void keypad_led_on(void)
{
        PORTD = 0b10111111;
}
void blink_all_leds(void)
{
        all_led_on();
        _delay_ms(500);

        all_led_off();
        _delay_ms(100);

        caps_lock_led_on();
        _delay_ms(100);

	 num_lock_led_on();
        _delay_ms(100);

        scroll_lock_led_on();
        _delay_ms(100);

         keypad_led_on();
        _delay_ms(100);

        //back

        scroll_lock_led_on();
        _delay_ms(100);

        num_lock_led_on();
        _delay_ms(100);

        caps_lock_led_on();
        _delay_ms(100);

        all_led_off();
}

// End section origin  https://github.com/alvicstep/tmk_keyboard 

 void matrix_init_kb(void) {
	  blink_all_leds();
	  matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {

//Copyright 2014 Warren Janssens <warren.janssens@gmail.com>
        uint8_t leds = 0xF0;
        if (led_state.num_lock)
                leds &= ~0x10;
        if (led_state.caps_lock)
                leds &= ~0x80;
        if (led_state.scroll_lock)
                leds &= ~0x20;
        PORTD = (PORTD & 0x0F) | leds;

    }
    return res;
}
