#include "ansi.h"
#include <avr/io.h>

#ifdef HHKB_RN42_ENABLE
#   include "../rn42/rn42.h"
#   include "../rn42/rn42_task.h"
#endif

void keyboard_post_init_kb(void) {
#ifdef HHKB_RN42_ENABLE
    // SUART setup
    DDRD |= (1<<0);
    PORTD |= (1<<0);
    DDRD &= ~(1<<1);
    PORTD |= (1<<1);

    rn42_init();
    rn42_task_init();
#endif
    keyboard_post_init_user();
}

void matrix_scan_kb(void) {
#ifdef HHKB_RN42_ENABLE
    rn42_task();
#endif
    matrix_scan_user();
}