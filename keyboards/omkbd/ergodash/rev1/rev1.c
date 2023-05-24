#include "ergodash.h"

#ifdef AUDIO_ENABLE
    float tone_startup[][2] = SONG(STARTUP_SOUND);
    float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void matrix_init_kb(void) {

    #ifdef AUDIO_ENABLE
        _delay_ms(20); // gets rid of tick
        PLAY_SONG(tone_startup);
    #endif

    // // green led on
    // DDRD |= (1<<5);
    // PORTD &= ~(1<<5);

    // // orange led on
    // DDRB |= (1<<0);
    // PORTB &= ~(1<<0);

	matrix_init_user();
};

void shutdown_user(void) {
    #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_goodbye);
	_delay_ms(150);
	stop_all_notes();
    #endif
}
