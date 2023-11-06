#include QMK_KEYBOARD_H
#include "hardware_id.h"
#include <stdio.h>
enum custom_keycodes {
    DUMP_ID = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(DUMP_ID)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DUMP_ID:
            if (record->event.pressed) {
                hardware_id_t id = get_hardware_id();
                char buffer[100];
                sprintf(buffer, "ID:%lu:%lu:%lu:%lu\n", id.data[0], id.data[1], id.data[2], id.data[3]);
#ifdef CONSOLE_ENABLE
                    uprintf("%s", buffer);
#else
                    send_string(buffer);
#endif
            }
            break;
    }
    return false;
};
