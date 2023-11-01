#include QMK_KEYBOARD_H


bool process_diablo_player_change(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PL_1:
            if (record->event.pressed) {
               SEND_STRING("\n/players1\n");
            }
            return false;
            break;
        case PL_2:
            if (record->event.pressed) {
               SEND_STRING("\n/players2\n");
            }
            return false;
            break;
        case PL_3:
            if (record->event.pressed) {
               SEND_STRING("\n/players3\n");
            }
            return false;
            break;
        case PL_4:
            if (record->event.pressed) {
               SEND_STRING("\n/players4\n");
            }
            return false;
            break;
        case PL_5:
            if (record->event.pressed) {
               SEND_STRING("\n/players5\n");
            }
            return false;
            break;
        case PL_6:
            if (record->event.pressed) {
               SEND_STRING("\n/players6\n");
            }
            return false;
            break;
        case PL_7:
            if (record->event.pressed) {
               SEND_STRING("\n/players7\n");
            }
            return false;
            break;
        case PL_8:
            if (record->event.pressed) {
               SEND_STRING("\n/players8\n");
            }
            return false;
            break;
    }
    return true;
}