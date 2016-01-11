#include "planck.h"

__attribute__ ((weak))
void * matrix_init_user(void) {

};

__attribute__ ((weak))
void * matrix_scan_user(void) {

};

void * matrix_init_kb(void) {
	#ifdef BACKLIGHT_ENABLE
    	backlight_init_ports();
	#endif

    // Turn status LED on
    DDRE |= (1<<6);
    PORTE |= (1<<6);

    init_notes();

    // play_note(((double)261.6*32)*pow(2.0,(36)/12.0), 0xF);
    // _delay_ms(50);

    // play_note(((double)261.6*32)*pow(2.0,(48)/12.0), 0xF);
    // _delay_ms(25);
    // stop_note(((double)261.6*32)*pow(2.0,(48)/12.0));

    // play_note(((double)261.6*32)*pow(2.0,(48)/12.0), 0xF);
    // _delay_ms(25);
    // stop_note(((double)261.6*32)*pow(2.0,(48)/12.0));


    // stop_note(((double)261.6*32)*pow(2.0,(36)/12.0));


    // play_note(((double)261.6*32)*pow(2.0,(62)/12.0), 0xF);
    // _delay_ms(50);
    // stop_note(((double)261.6*32)*pow(2.0,(62)/12.0));


    // play_note(((double)261.6*32)*pow(2.0,(64)/12.0), 0xF);
    // _delay_ms(50);
    // stop_note(((double)261.6*32)*pow(2.0,(64)/12.0));




	if (matrix_init_user) {
		(*matrix_init_user)();
	}
};

void * matrix_scan_kb(void) {
	if (matrix_scan_user) {
		(*matrix_scan_user)();
	}
};