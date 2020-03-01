#include "rev3.h"
#include "led.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	led_init_ports();
};

void led_init_ports(void) {
    // * Set our LED pins as output
    DDRE |= (1 << 6);

	//Set output high, so the capslock led is off
	PORTE |= (1 << 6);
}
