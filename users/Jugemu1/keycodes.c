#include "keycodes.h"
#include "custom_combo.h"

#ifdef TAP_HOLD_ENABLE
    #include "tap_hold.h"
#endif

uint16_t get_main_mod(void){
    modes current_mode = get_mode();
    switch(current_mode){
        case MODE_WINDOWS:
            return KC_LCTL;
        case MODE_MAC:
            return KC_LGUI;
        default:
            return KC_LCTL;
    }
}

uint16_t get_second_mod(void){
    modes current_mode = get_mode();
    switch(current_mode){
        case MODE_WINDOWS:
            return KC_LGUI;
        case MODE_MAC:
            return KC_LCTL;
        default:
            return KC_LGUI;
    }
}

void press_release(uint16_t keycode, const keyrecord_t *record){
    if (record->event.pressed) {
        register_code16(keycode);
    }else{
        unregister_code16(keycode);
    }
}

void switch_language(bool is_pressed){
    if (is_pressed){
        register_code16(get_second_mod());
        register_code16(KC_SPACE);
    } else{
        unregister_code16(KC_SPACE);
        unregister_code16(get_second_mod());
    }
}

void tap_switch_language(void){
    switch_language(true);
    switch_language(false);
}

void switch_language_key_press(const keyrecord_t *record){
    switch_language(record->event.pressed);
}

void print_full_screen_key_press(const keyrecord_t *record){
    modes current_mode = get_mode();
    switch(current_mode){
        case MODE_WINDOWS:
            if (record->event.pressed)
            {
                register_code16(KC_LGUI);
                register_code16(KC_PSCR);
            }else {
                unregister_code16(KC_PSCR);
                unregister_code16(KC_LGUI);
            }
            break;
        case MODE_MAC:
            if (record->event.pressed)
            {
                register_code16(KC_LGUI);
                register_code16(KC_LSFT);
                register_code16(KC_4);
            }else {
                unregister_code16(KC_4);
                unregister_code16(KC_LSFT);
                unregister_code16(KC_LGUI);
            }
            break;
        default:
            if (record->event.pressed)
            {
                tap_code(KC_PSCR);
            }
            break;
    }
}

void print_partial_screen_key_press(const keyrecord_t *record){
    modes current_mode = get_mode();
    switch(current_mode){
        case MODE_WINDOWS:
            if (record->event.pressed)
            {
                register_code16(KC_LGUI);
                register_code16(KC_LSFT);
                register_code16(KC_S);
            }else {
                unregister_code16(KC_S);
                unregister_code16(KC_LSFT);
                unregister_code16(KC_LGUI);
            }
            break;
        case MODE_MAC:
            if (record->event.pressed)
            {
                register_code16(KC_LGUI);
                register_code16(KC_LCTL);
                register_code16(KC_LSFT);
                register_code16(KC_4);
            }else {
                unregister_code16(KC_4);
                unregister_code16(KC_LCTL);
                unregister_code16(KC_LSFT);
                unregister_code16(KC_LGUI);
            }
            break;
        default:
            if (record->event.pressed)
            {
                tap_code(KC_PSCR);
            }
            break;
    }
}

bool process_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_MAIN_MOD:
            press_release(get_main_mod(), record);
            return false;
        case CK_SWITCH_LANGUAGE:
            switch_language_key_press(record);
            return false;
        case CK_FULL_PRINT_SCREEN:
            print_full_screen_key_press(record);
            return false;
        case CK_TG_COMBO:
            custom_combo_toggle();
            return false;
        case CK_PARTIAL_PRINT_SCREEN:
            print_partial_screen_key_press(record);
            return false;
        default:
            return true;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!pre_process_record_user(keycode, record)){
        return false;
    }

#ifdef TAP_DANCE_ENABLE
    if(tap_hold_enabled() && !process_tap_hold_record(keycode, record)){
        return false;
    }
#endif

    if (!process_keycodes(keycode, record)){
        return false;
    }

    return true;
}
