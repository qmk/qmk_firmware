#include "seq.h"

static char buffer[32];
static uint8_t buffer_size = 0;

void seq_start(void) {
    buffer_size = 0;
    SEND_STRING(":");
}

bool seq_feed(uint16_t keycode) {
    if (keycode == KC_ENTER) {
        for (int i = 0; i < buffer_size + 1; i++) {
            tap_code(KC_BACKSPACE);
        }
        for (int i = 0; i < seq_config_size; i++) {
            seq_t item = seq_config[i];
            if (strncmp(item.sequence, buffer, buffer_size) == 0) {
                send_unicode_string(item.result);
            }
        }
        buffer_size = 0;
        return false;
    } else if (keycode == KC_BACKSPACE) {
        if (buffer_size) {
            buffer_size--;
            tap_code(keycode);
        }
        return true;
    } else {
        if (keycode >= KC_A && keycode <= KC_Z) {
            buffer[buffer_size++] = keycode - KC_A + 'a';
            tap_code(keycode);
        }
        return true;
    }
}

