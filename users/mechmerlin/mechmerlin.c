#include "mechmerlin.h"

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
        return false;
    }
    return true;
}