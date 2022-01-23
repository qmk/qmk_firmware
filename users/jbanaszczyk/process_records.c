#include "quantum.h"
#include "do_not_sleep.h"

static bool process_record_debug(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) {
        dprintf("KL: kc: %u\n", keycode);
    }
#endif
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true
           && process_record_debug(keycode, record)
#ifdef DO_NOT_SLEEP
           && do_not_sleep_process(keycode, record)
#endif
        ;
}
