#include "tap_hold.h"
#include "eeconfig.h"
#include "eeprom.h"

volatile bool tap_hold_status = false;

bool tap_hold_enabled(void){
    tap_hold_status = eeprom_read_byte(EECONFIG_TAP_HOLD_INDEX);
    return tap_hold_status;
}

void set_tap_hold(bool enabled){
    tap_hold_status = enabled;
    eeprom_update_byte(EECONFIG_TAP_HOLD_INDEX, tap_hold_status);
}

void toggle_tap_hold(void){
    set_tap_hold(!tap_hold_status);
}

void init_tap_hold(void){
    set_tap_hold(
        tap_hold_enabled()
    );
}

bool process_tap_hold(
    uint16_t keycode,
    keyrecord_t *record,
    uint16_t hold_keycode
){
    bool is_hold = record->tap.count == 0;
    if(is_hold){
        if (record->event.pressed)
        {
            register_code16(hold_keycode);
        }else {
            unregister_code16(hold_keycode);
        }
        return false;
    }else{
        return true;
    }
}

bool process_tap_hold_record(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
        // case KC_A:
        //     return true;
            // return process_tap_hold(KC_A, record, LT(ARROW_LAYER, KC_A));
            // return process_tap_hold(KC_A, record, MO(ARROW_LAYER));
            // return process_tap_hold(KC_A, record, KC_B);

        // case LT(0, KC_N):
        // // case KC_N:
        //     if (record->tap.count && record->event.pressed) {
        //         tap_code16(C(KC_C)); // Intercept tap function to send Ctrl-C
        //         // tap_code16(KC_X);
        //     } else if (record->event.pressed) {
        //         tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
        //         // tap_code16(KC_C);
        //     }
        //     return false;

        default:
            return true;
    }
}
