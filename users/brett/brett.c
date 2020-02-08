#include "brett.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool send(const char *str) {
        if (record->event.pressed) {
            send_string(str);
        }
        return false;
    }
    switch (keycode) {
        case FAT_ARROW:
            return send("=>");
        case SKINNY_ARROW:
            return send("->");
        case REVERSE_ARROW:
            return send("<-");
        case CONCAT:
            return send("<>");
        case MAP:
            return send("<$>");
        case MAP_FLIPPED:
            return send("<#>");
        case FLAP:
            return send("<@>");
        case PIPE:
            return send("|>");
        case ALT:
            return send("<|>");
        case APPLY:
            return send("<*>");
        case AND:
            return send("&&");
        case OR:
            return send("||");
        case BIND:
            return send(">>=");
        case BIND_FLIPPED:
            return send("=<<");
        case DOUBLE_COLON:
            return send("::");
        case VOID_LEFT:
            return send("<$");
        case VOID_RIGHT:
            return send("$>");
        case FLASH:
            if (record->event.pressed) {
                SEND_STRING("sudo -E make hhkb:brett:dfu");
                register_code(KC_ENTER);
                unregister_code(KC_ENTER);
                reset_keyboard();
            }
            return false;
    }
    return true;
}
