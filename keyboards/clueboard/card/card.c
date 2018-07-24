#include "card.h"
#define BL_RED OCR1B
#define BL_GREEN OCR1A
#define BL_BLUE OCR1C

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

	led_set_user(usb_led);
}

void backlight_init_ports(void)
{
	// Set B5, B6, and B7 as output
	DDRB |= (1<<7)|(1<<6)|(1<<5);

	// Setup PWM
	ICR1 = 0xFFFF;
	TCCR1A = 0b10101010;
	TCCR1B = 0b00011001;

	BL_RED = 0xFFFF;
	BL_GREEN = 0xFFFF;
	BL_BLUE = 0xFFFF;
}

void backlight_set(uint8_t level)
{
	// Set the RGB color
	switch (level)
	{
	case 0:
		// Off
		BL_RED = 0xFFFF;
		BL_GREEN = 0xFFFF;
		BL_BLUE = 0xFFFF;
		break;
	case 1:
		// Red
		BL_RED = 0x0000;
		BL_GREEN = 0xFFFF;
		BL_BLUE = 0xFFFF;
		break;
	case 2:
		// Green
		BL_RED = 0xFFFF;
		BL_GREEN = 0x0000;
		BL_BLUE = 0xFFFF;
		break;
	case 3:
		// Blue
		BL_RED = 0xFFFF;
		BL_GREEN = 0xFFFF;
		BL_BLUE = 0x0000;
		break;
	case 4:
		// Magenta
		BL_RED = 0x4000;
		BL_GREEN = 0x4000;
		BL_BLUE = 0x4000;
		break;
	case 5:
		// Purple
		BL_RED = 0x0000;
		BL_GREEN = 0xFFFF;
		BL_BLUE = 0x0000;
		break;
	case 6:
		// Yellow
		BL_RED = 0x0000;
		BL_GREEN = 0x0000;
		BL_BLUE = 0xFFFF;
		break;
	default:
		xprintf("Unknown level: %d\n", level);
	}
}
