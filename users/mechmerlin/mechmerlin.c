#include "mechmerlin.h"
#include "version.h"

#define TAP_CODE_DELAY 10

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t fnx_layer_timer;

    switch (keycode){
        case KC_FNX:                                    
            if(record->event.pressed){
                fnx_layer_timer = timer_read();
                layer_on(_FL);
            } else {
                layer_off(_FL);
                if (timer_elapsed(fnx_layer_timer) < 150) {  
                    layer_invert(_AL);
                }
            }
        break;
        case KC_VER:
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
            } else {
            }
        break;
    }
    return true;
}