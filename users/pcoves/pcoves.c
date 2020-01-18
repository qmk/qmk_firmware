#include "pcoves.h"

#ifdef RAINBOW_UNICORN_ENABLE
#include "rainbowUnicorn.h"
#endif

#ifdef UNICODE_ENABLE
#include "unicode.h"
#endif

#if SECRET_ENABLE
#include "secret.h"
#endif

void eeconfig_init_keymap(void) { return; }

void eeconfig_init_user(void) {
    set_unicode_input_mode(UC_LNX);
    eeconfig_init_keymap();
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AUTRUCHE:
            if (record->event.pressed) SEND_STRING("Autruche");
            return false;
    }

    return process_record_keymap(keycode, record)
#ifdef RAINBOW_UNICORN_ENABLE
        && process_record_rainbowUnicorn(keycode, record)
#endif
#ifdef UNICODE_ENABLE
        && process_record_unicode(keycode, record)
#endif
#if SECRET_ENABLE
        && process_record_secret(keycode, record)
#endif
        ;
}
