#include "process_plover_hid.h" 
#include "keymap_plover_hid.h"
#include "plover_hid.h"

bool process_plover_hid(uint16_t keycode, keyrecord_t *record) {
    if (keycode < PLV__MIN || keycode > PLV__MAX) {
        return true;
    }
    plover_hid_update(keycode - PLV__MIN, record->event.pressed);
    return false;
}
