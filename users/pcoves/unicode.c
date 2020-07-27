#include "unicode.h"
#include "pcoves.h"

bool process_record_unicode(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EMOTE0:
            if (record->event.pressed) send_unicode_string("(╯°□°）╯︵┻━┻");
            return false;
        case EMOTE1:
            if (record->event.pressed) send_unicode_string("(ヘ･_･)ヘ┳━┳");
            return false;
        case EMOTE2:
            if (record->event.pressed) send_unicode_string("¯\\_(ツ)_/¯");
            return false;
        case EMOTE3:
            if (record->event.pressed) send_unicode_string("ಠ_ಠ");
            return false;
    }
    return true;
}
