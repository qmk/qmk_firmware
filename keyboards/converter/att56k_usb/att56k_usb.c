#include <stdbool.h>

#include "att56k_if.h"
#include "att56k.h"
#include <print.h>
#include "debug.h"
#include "util.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CLCK_CYC:
            if (record->event.pressed) {
                att56k_click_cycle();
            }
            break;
    }
    return process_record_user(keycode, record);
}
