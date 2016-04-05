#include "preonic.h"

__attribute__ ((weak))
void matrix_init_user(void) {

};

__attribute__ ((weak))
void matrix_scan_user(void) {

};

__attribute__ ((weak))
void process_action_user(keyrecord_t *record) {

};

void matrix_init_kb(void) {
	#ifdef BACKLIGHT_ENABLE
    	backlight_init_ports();
	#endif

	#ifdef RGBLIGHT_ENABLE
		rgblight_init();
	#endif


    // Turn status LED on
    DDRE |= (1<<6);
    PORTE |= (1<<6);

	matrix_init_user();
};

void matrix_scan_kb(void) {
	matrix_scan_user();
};

void process_action_kb(keyrecord_t *record) {
	process_action_user(record);
}