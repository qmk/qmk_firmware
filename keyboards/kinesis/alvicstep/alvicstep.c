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


void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	
	matrix_scan_user();
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

//Copyright 2014 Warren Janssens <warren.janssens@gmail.com>
   uint8_t leds = 0xF0;
    if (usb_led & 1 << USB_LED_NUM_LOCK)
        leds &= ~0x10;
    if (usb_led & 1 << USB_LED_CAPS_LOCK)
        leds &= ~0x80;
    if (usb_led & 1 << USB_LED_SCROLL_LOCK)
        leds &= ~0x20;
    PORTD = (PORTD & 0x0F) | leds;

	led_set_user(usb_led);

}


