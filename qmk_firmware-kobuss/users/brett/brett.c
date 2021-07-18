#include "brett.h"

char * get_key(uint16_t keycode) {
    switch (keycode) {
        case FAT_ARROW:
            return "=>";
        case SKINNY_ARROW:
            return "->";
        case REVERSE_ARROW:
            return "<-";
        case CONCAT:
            return "<>";
        case MAP:
            return "<$>";
        case MAP_FLIPPED:
            return "<#>";
        case FLAP:
            return "<@>";
        case PIPE:
            return "|>";
        case ALT:
            return "<|>";
        case APPLY:
            return "<*>";
        case AND:
            return "&&";
        case OR:
            return "||";
        case BIND:
            return ">>=";
        case BIND_FLIPPED:
            return "=<<";
        case DOUBLE_COLON:
            return "::";
        case VOID_LEFT:
            return "<$";
        case VOID_RIGHT:
            return "$>";
        default:
            return "";
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;
    switch (keycode) {
        case FAT_ARROW ... DOUBLE_COLON:
            if (pressed) {
                send_string(get_key(keycode));
            }
            return false;
        case FLASH:
            if (!pressed) {
                SEND_STRING("make -j8 --output-sync " QMK_KEYBOARD ":" QMK_KEYMAP ":flash" SS_TAP(X_ENTER));
                reset_keyboard();
            }
            return false;
        default:
            return true;
    }
}
