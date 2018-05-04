#include "tanuki.h"
#include "rgblight.h"
#include "config.h"
//#include "led.h"
#include "rgblight.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	//LED_TYPE led[RGBLED_NUM];
	//setrgb(255, 255, 255, led);
	//rgblight_show_solid_color(255,255,255);
	rgblight_enable();
  	rgblight_mode(1);
	rgblight_sethsv(0,10,255);

};
