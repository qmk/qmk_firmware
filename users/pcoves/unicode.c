#include "unicode.h"
#include "pcoves.h"

bool process_record_unicode(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EMOTE0:
            send_unicode_hex_string("0028 256f 00B0 25A1 00B0 FF09 256F FE35 253B 2501 253B");
            return false;
        case EMOTE1:
            send_unicode_hex_string("0028 30D8 FF65 005F FF65 0029 30D8 2533 2501 2533");
            return false;
        case EMOTE2:
            send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
            return false;
        case EMOTE3:
            send_unicode_hex_string("0CA0 005F 0CA0");
            return false;
    }
    return true;
}
