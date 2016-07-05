#include "lets-split.h"

#ifdef AUDIO_ENABLE
    float tone_startup[][2] = SONG(STARTUP_SOUND);
    float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void matrix_init_kb(void) {

    #ifdef AUDIO_ENABLE
        _delay_ms(20); // gets rid of tick
        PLAY_NOTE_ARRAY(tone_startup, false, 0);
    #endif

    // green led on
    DDRD |= (1<<5);
    PORTD &= ~(1<<5);

    // orange led on
    DDRB |= (1<<0);
    PORTB &= ~(1<<0);

	matrix_init_user();
};

void promicro_bootloader_jmp(bool program) {

    #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
        _delay_ms(150);
        stop_all_notes();
    #endif
    
    uint16_t *const bootKeyPtr = (uint16_t *)0x0800;

    // Value used by Caterina bootloader use to determine whether to run the
    // sketch or the bootloader programmer.
    uint16_t bootKey = program ? 0x7777 : 0;

    *bootKeyPtr = bootKey;

    // setup watchdog timeout
    wdt_enable(WDTO_60MS);

    while(1) {} // wait for watchdog timer to trigger
}


