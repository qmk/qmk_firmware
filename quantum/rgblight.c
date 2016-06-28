#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "progmem.h"
#include "timer.h"
#include "rgblight.h"
#include "debug.h"

const uint8_t DIM_CURVE[] PROGMEM = {
	0, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6,
	6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8,
	8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11,
	11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
	15, 15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20,
	20, 20, 21, 21, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 26, 26,
	27, 27, 28, 28, 29, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35,
	36, 36, 37, 38, 38, 39, 40, 40, 41, 42, 43, 43, 44, 45, 46, 47,
	48, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
	63, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 78, 79, 81, 82,
	83, 85, 86, 88, 90, 91, 93, 94, 96, 98, 99, 101, 103, 105, 107, 109,
	110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
	146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
	193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};
const uint8_t RGBLED_BREATHING_TABLE[] PROGMEM = {0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,35,37,40,42,44,47,49,52,54,57,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,109,112,115,118,121,124,127,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,224,226,228,230,232,234,235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,240,238,237,235,234,232,230,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,193,190,188,185,182,179,176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,128,124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,54,52,49,47,44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0};
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {30, 20, 10, 5};
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {120, 60, 30};
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20};
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {100, 50, 20};
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {100, 50, 20};

rgblight_config_t rgblight_config;
rgblight_config_t inmem_config;
struct cRGB led[RGBLED_NUM];
uint8_t rgblight_inited = 0;


void sethsv(uint16_t hue, uint8_t sat, uint8_t val, struct cRGB *led1) {
	/* convert hue, saturation and brightness ( HSB/HSV ) to RGB
	The DIM_CURVE is used only on brightness/value and on saturation (inverted).
	This looks the most natural.
	*/
  uint8_t r = 0, g = 0, b = 0;

  val = pgm_read_byte(&DIM_CURVE[val]);
	sat = 255 - pgm_read_byte(&DIM_CURVE[255 - sat]);

	uint8_t base;

	if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
		r = val;
		g = val;
		b = val;
	} else  {
		base = ((255 - sat) * val) >> 8;

		switch (hue / 60) {
		case 0:
			r = val;
			g = (((val - base)*hue) / 60) + base;
			b = base;
			break;

		case 1:
			r = (((val - base)*(60 - (hue % 60))) / 60) + base;
			g = val;
			b = base;
			break;

		case 2:
			r = base;
			g = val;
			b = (((val - base)*(hue % 60)) / 60) + base;
			break;

		case 3:
			r = base;
			g = (((val - base)*(60 - (hue % 60))) / 60) + base;
			b = val;
			break;

		case 4:
			r = (((val - base)*(hue % 60)) / 60) + base;
			g = base;
			b = val;
			break;

		case 5:
			r = val;
			g = base;
			b = (((val - base)*(60 - (hue % 60))) / 60) + base;
			break;
		}
	}
  setrgb(r,g,b, led1);
}

void setrgb(uint8_t r, uint8_t g, uint8_t b, struct cRGB *led1) {
  (*led1).r = r;
  (*led1).g = g;
  (*led1).b = b;
}


uint32_t eeconfig_read_rgblight(void) {
  return eeprom_read_dword(EECONFIG_RGBLIGHT);
}
void eeconfig_update_rgblight(uint32_t val) {
  eeprom_update_dword(EECONFIG_RGBLIGHT, val);
}
void eeconfig_update_rgblight_default(void) {
	dprintf("eeconfig_update_rgblight_default\n");
	rgblight_config.enable = 1;
	rgblight_config.mode = 1;
	rgblight_config.hue = 200;
	rgblight_config.sat = 204;
	rgblight_config.val = 204;
	eeconfig_update_rgblight(rgblight_config.raw);
}
void eeconfig_debug_rgblight(void) {
	dprintf("rgblight_config eprom\n");
	dprintf("rgblight_config.enable = %d\n", rgblight_config.enable);
	dprintf("rghlight_config.mode = %d\n", rgblight_config.mode);
	dprintf("rgblight_config.hue = %d\n", rgblight_config.hue);
	dprintf("rgblight_config.sat = %d\n", rgblight_config.sat);
	dprintf("rgblight_config.val = %d\n", rgblight_config.val);
}

void rgblight_init(void) {
  debug_enable = 1; // Debug ON!
	dprintf("rgblight_init called.\n");
  rgblight_inited = 1;
	dprintf("rgblight_init start!\n");
  if (!eeconfig_is_enabled()) {
		dprintf("rgblight_init eeconfig is not enabled.\n");
    eeconfig_init();
		eeconfig_update_rgblight_default();
  }
  rgblight_config.raw = eeconfig_read_rgblight();
	if (!rgblight_config.mode) {
		dprintf("rgblight_init rgblight_config.mode = 0. Write default values to EEPROM.\n");
		eeconfig_update_rgblight_default();
		rgblight_config.raw = eeconfig_read_rgblight();
	}
	eeconfig_debug_rgblight(); // display current eeprom values

	rgblight_timer_init(); // setup the timer

  if (rgblight_config.enable) {
    rgblight_mode(rgblight_config.mode);
  }
}

void rgblight_increase(void) {
	uint8_t mode = 0;
  if (rgblight_config.mode < RGBLIGHT_MODES) {
    mode = rgblight_config.mode + 1;
  }
	rgblight_mode(mode);
}

void rgblight_decrease(void) {
	uint8_t mode = 0;
  if (rgblight_config.mode > 1) { //mode will never < 1, if mode is less than 1, eeprom need to be initialized.
    mode = rgblight_config.mode-1;
  }
	rgblight_mode(mode);
}

void rgblight_step(void) {
	uint8_t mode = 0;
  mode = rgblight_config.mode + 1;
  if (mode > RGBLIGHT_MODES) {
    mode = 1;
  }
	rgblight_mode(mode);
}

void rgblight_mode(uint8_t mode) {
	if (!rgblight_config.enable) {
		return;
	}
  if (mode<1) {
		rgblight_config.mode = 1;
	} else if (mode > RGBLIGHT_MODES) {
		rgblight_config.mode = RGBLIGHT_MODES;
	} else {
		rgblight_config.mode = mode;
	}
  eeconfig_update_rgblight(rgblight_config.raw);
  xprintf("rgblight mode: %u\n", rgblight_config.mode);
	if (rgblight_config.mode == 1) {
		rgblight_timer_disable();
	} else if (rgblight_config.mode >=2 && rgblight_config.mode <=23) {
		// MODE 2-5, breathing
		// MODE 6-8, rainbow mood
		// MODE 9-14, rainbow swirl
		// MODE 15-20, snake
		// MODE 21-23, knight
		rgblight_timer_enable();
	}
  rgblight_sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
}

void rgblight_toggle(void) {
  rgblight_config.enable ^= 1;
  eeconfig_update_rgblight(rgblight_config.raw);
  xprintf("rgblight toggle: rgblight_config.enable = %u\n", rgblight_config.enable);
	if (rgblight_config.enable) {
		rgblight_mode(rgblight_config.mode);
	} else {
		rgblight_timer_disable();
		_delay_ms(50);
		rgblight_set();
	}
}


void rgblight_increase_hue(void){
	uint16_t hue;
  hue = (rgblight_config.hue+RGBLIGHT_HUE_STEP) % 360;
  rgblight_sethsv(hue, rgblight_config.sat, rgblight_config.val);
}
void rgblight_decrease_hue(void){
	uint16_t hue;
	if (rgblight_config.hue-RGBLIGHT_HUE_STEP <0 ) {
		hue = (rgblight_config.hue+360-RGBLIGHT_HUE_STEP) % 360;
	} else {
		hue = (rgblight_config.hue-RGBLIGHT_HUE_STEP) % 360;
	}
  rgblight_sethsv(hue, rgblight_config.sat, rgblight_config.val);
}
void rgblight_increase_sat(void) {
	uint8_t sat;
  if (rgblight_config.sat + RGBLIGHT_SAT_STEP > 255) {
    sat = 255;
  } else {
    sat = rgblight_config.sat+RGBLIGHT_SAT_STEP;
  }
  rgblight_sethsv(rgblight_config.hue, sat, rgblight_config.val);
}
void rgblight_decrease_sat(void){
	uint8_t sat;
  if (rgblight_config.sat - RGBLIGHT_SAT_STEP < 0) {
    sat = 0;
  } else {
    sat = rgblight_config.sat-RGBLIGHT_SAT_STEP;
  }
  rgblight_sethsv(rgblight_config.hue, sat, rgblight_config.val);
}
void rgblight_increase_val(void){
	uint8_t val;
  if (rgblight_config.val + RGBLIGHT_VAL_STEP > 255) {
    val = 255;
  } else {
    val = rgblight_config.val+RGBLIGHT_VAL_STEP;
  }
  rgblight_sethsv(rgblight_config.hue, rgblight_config.sat, val);
}
void rgblight_decrease_val(void) {
	uint8_t val;
  if (rgblight_config.val - RGBLIGHT_VAL_STEP < 0) {
    val = 0;
  } else {
    val = rgblight_config.val-RGBLIGHT_VAL_STEP;
  }
  rgblight_sethsv(rgblight_config.hue, rgblight_config.sat, val);
}

void rgblight_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val){
	inmem_config.raw = rgblight_config.raw;
  if (rgblight_config.enable) {
    struct cRGB tmp_led;
    sethsv(hue, sat, val, &tmp_led);
		inmem_config.hue = hue;
		inmem_config.sat = sat;
		inmem_config.val = val;
    // dprintf("rgblight set hue [MEMORY]: %u,%u,%u\n", inmem_config.hue, inmem_config.sat, inmem_config.val);
    rgblight_setrgb(tmp_led.r, tmp_led.g, tmp_led.b);
  }
}
void rgblight_sethsv(uint16_t hue, uint8_t sat, uint8_t val){
  if (rgblight_config.enable) {
		if (rgblight_config.mode == 1) {
			// same static color
			rgblight_sethsv_noeeprom(hue, sat, val);
		} else {
			// all LEDs in same color
			if (rgblight_config.mode >= 2 && rgblight_config.mode <= 5) {
				// breathing mode, ignore the change of val, use in memory value instead
				val = rgblight_config.val;
			} else if (rgblight_config.mode >= 6 && rgblight_config.mode <= 14) {
				// rainbow mood and rainbow swirl, ignore the change of hue
				hue = rgblight_config.hue;
			}
		}
		rgblight_config.hue = hue;
		rgblight_config.sat = sat;
		rgblight_config.val = val;
		eeconfig_update_rgblight(rgblight_config.raw);
		xprintf("rgblight set hsv [EEPROM]: %u,%u,%u\n", rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
  }
}

void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b){
  // dprintf("rgblight set rgb: %u,%u,%u\n", r,g,b);
  for (uint8_t i=0;i<RGBLED_NUM;i++) {
    led[i].r = r;
    led[i].g = g;
    led[i].b = b;
  }
  rgblight_set();

}

void rgblight_set(void) {
	if (rgblight_config.enable) {
		ws2812_setleds(led, RGBLED_NUM);
	} else {
		for (uint8_t i=0;i<RGBLED_NUM;i++) {
	    led[i].r = 0;
	    led[i].g = 0;
	    led[i].b = 0;
	  }
		ws2812_setleds(led, RGBLED_NUM);
	}
}

// Animation timer -- AVR Timer3
void rgblight_timer_init(void) {
	static uint8_t rgblight_timer_is_init = 0;
	if (rgblight_timer_is_init) {
		return;
	}
	rgblight_timer_is_init = 1;
	/* Timer 3 setup */
	TCCR3B = _BV(WGM32) //CTC mode OCR3A as TOP
	      | _BV(CS30); //Clock selelct: clk/1
	/* Set TOP value */
	uint8_t sreg = SREG;
	cli();
	OCR3AH = (RGBLED_TIMER_TOP>>8)&0xff;
	OCR3AL = RGBLED_TIMER_TOP&0xff;
	SREG = sreg;
}
void rgblight_timer_enable(void) {
	TIMSK3 |= _BV(OCIE3A);
	dprintf("TIMER3 enabled.\n");
}
void rgblight_timer_disable(void) {
	TIMSK3 &= ~_BV(OCIE3A);
	dprintf("TIMER3 disabled.\n");
}
void rgblight_timer_toggle(void) {
	TIMSK3 ^= _BV(OCIE3A);
	dprintf("TIMER3 toggled.\n");
}

ISR(TIMER3_COMPA_vect) {
	// Mode = 1, static light, do nothing here
	if (rgblight_config.mode>=2 && rgblight_config.mode<=5) {
		// mode = 2 to 5, breathing mode
		rgblight_effect_breathing(rgblight_config.mode-2);

	} else if (rgblight_config.mode>=6 && rgblight_config.mode<=8) {
		rgblight_effect_rainbow_mood(rgblight_config.mode-6);
	} else if (rgblight_config.mode>=9 && rgblight_config.mode<=14) {
		rgblight_effect_rainbow_swirl(rgblight_config.mode-9);
	} else if (rgblight_config.mode>=15 && rgblight_config.mode<=20) {
		rgblight_effect_snake(rgblight_config.mode-15);
	} else if (rgblight_config.mode>=21 && rgblight_config.mode<=23) {
		rgblight_effect_knight(rgblight_config.mode-21);
	}
}

// effects
void rgblight_effect_breathing(uint8_t interval) {
	static uint8_t pos = 0;
	static uint16_t last_timer = 0;

	if (timer_elapsed(last_timer)<pgm_read_byte(&RGBLED_BREATHING_INTERVALS[interval])) return;
	last_timer = timer_read();

	rgblight_sethsv_noeeprom(rgblight_config.hue, rgblight_config.sat, pgm_read_byte(&RGBLED_BREATHING_TABLE[pos]));
	pos = (pos+1) % 256;
}

void rgblight_effect_rainbow_mood(uint8_t interval) {
	static uint16_t current_hue=0;
	static uint16_t last_timer = 0;

	if (timer_elapsed(last_timer)<pgm_read_byte(&RGBLED_RAINBOW_MOOD_INTERVALS[interval])) return;
	last_timer = timer_read();
	rgblight_sethsv_noeeprom(current_hue, rgblight_config.sat, rgblight_config.val);
	current_hue = (current_hue+1) % 360;
}

void rgblight_effect_rainbow_swirl(uint8_t interval) {
	static uint16_t current_hue=0;
	static uint16_t last_timer = 0;
	uint16_t hue;
	uint8_t i;
	if (timer_elapsed(last_timer)<pgm_read_byte(&RGBLED_RAINBOW_MOOD_INTERVALS[interval/2])) return;
	last_timer = timer_read();
	for (i=0; i<RGBLED_NUM; i++) {
		hue = (360/RGBLED_NUM*i+current_hue)%360;
		sethsv(hue, rgblight_config.sat, rgblight_config.val, &led[i]);
	}
	rgblight_set();

	if (interval % 2) {
		current_hue = (current_hue+1) % 360;
	} else {
		if (current_hue -1 < 0) {
			current_hue = 359;
		} else {
			current_hue = current_hue - 1;
		}

	}
}
void rgblight_effect_snake(uint8_t interval) {
	static uint8_t pos=0;
	static uint16_t last_timer = 0;
	uint8_t i,j;
	int8_t k;
	int8_t increament = 1;
	if (interval%2) increament = -1;
	if (timer_elapsed(last_timer)<pgm_read_byte(&RGBLED_SNAKE_INTERVALS[interval/2])) return;
	last_timer = timer_read();
	for (i=0;i<RGBLED_NUM;i++) {
		led[i].r=0;
		led[i].g=0;
		led[i].b=0;
		for (j=0;j<RGBLIGHT_EFFECT_SNAKE_LENGTH;j++) {
			k = pos+j*increament;
			if (k<0) k = k+RGBLED_NUM;
			if (i==k) {
				sethsv(rgblight_config.hue, rgblight_config.sat, (uint8_t)(rgblight_config.val*(RGBLIGHT_EFFECT_SNAKE_LENGTH-j)/RGBLIGHT_EFFECT_SNAKE_LENGTH), &led[i]);
			}
		}
	}
	rgblight_set();
	if (increament == 1) {
		if (pos - 1 < 0) {
			pos = RGBLED_NUM-1;
		} else {
			pos -= 1;
		}
	} else {
		pos = (pos+1)%RGBLED_NUM;
	}

}

void rgblight_effect_knight(uint8_t interval) {
	static int8_t pos=0;
	static uint16_t last_timer = 0;
	uint8_t i,j,cur;
	int8_t k;
	struct cRGB preled[RGBLED_NUM];
	static int8_t increament = -1;
	if (timer_elapsed(last_timer)<pgm_read_byte(&RGBLED_KNIGHT_INTERVALS[interval])) return;
	last_timer = timer_read();
	for (i=0;i<RGBLED_NUM;i++) {
		preled[i].r=0;
		preled[i].g=0;
		preled[i].b=0;
		for (j=0;j<RGBLIGHT_EFFECT_KNIGHT_LENGTH;j++) {
			k = pos+j*increament;
			if (k<0) k = 0;
			if (k>=RGBLED_NUM) k=RGBLED_NUM-1;
			if (i==k) {
				sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, &preled[i]);
			}
		}
	}
	if (RGBLIGHT_EFFECT_KNIGHT_OFFSET) {
		for (i=0;i<RGBLED_NUM;i++) {
			cur = (i+RGBLIGHT_EFFECT_KNIGHT_OFFSET) % RGBLED_NUM;
			led[i].r = preled[cur].r;
			led[i].g = preled[cur].g;
			led[i].b = preled[cur].b;
		}
	}
	rgblight_set();
	if (increament == 1) {
		if (pos - 1 < 0 - RGBLIGHT_EFFECT_KNIGHT_LENGTH) {
			pos = 0- RGBLIGHT_EFFECT_KNIGHT_LENGTH;
			increament = -1;
		} else {
			pos -= 1;
		}
	} else {
		if (pos+1>RGBLED_NUM+RGBLIGHT_EFFECT_KNIGHT_LENGTH) {
			pos = RGBLED_NUM+RGBLIGHT_EFFECT_KNIGHT_LENGTH-1;
			increament = 1;
		} else {
			pos += 1;
		}
	}

}
