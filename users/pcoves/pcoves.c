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

__attribute__((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
#ifdef UNICODE_ENABLE
    set_unicode_input_mode(UC_LNX);
#endif
    eeconfig_init_keymap();
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AUTRUCHE:
            if (record->event.pressed) SEND_STRING("Autruche");
            return true;
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
