#pragma once

#ifdef SLEEP_LED_ENABLE

void sleep_led_init(void);
void sleep_led_enable(void);
void sleep_led_disable(void);
void sleep_led_toggle(void);

#else

#    define sleep_led_init()
#    define sleep_led_enable()
#    define sleep_led_disable()
#    define sleep_led_toggle()

#endif
