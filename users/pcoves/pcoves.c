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

#ifdef RAINBOW_UNICORN_ENABLE
        case RAINBOW_UNICORN_TOGGLE:
            if (record->event.pressed) rainbowUnicornToggle();
            return false;
#endif

#ifdef UNICODE_ENABLE
        case EMOTE0:
            if (record->event.pressed) emote0();
            return false;

        case EMOTE1:
            if (record->event.pressed) emote1();
            return false;

        case EMOTE2:
            if (record->event.pressed) emote2();
            return false;

        case EMOTE3:
            if (record->event.pressed) emote3();
            return false;
#endif
    }

#ifdef RAINBOW_UNICORN_ENABLE
    if (rainbowUnicornIsEnabled())
        rainbowUnicorn(keycode, record);
#endif

    return process_record_keymap(keycode, record)
#if SECRET_ENABLE
        &&
        process_record_secret(keycode, record)
#endif
        ;
}
