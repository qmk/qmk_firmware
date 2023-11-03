#include QMK_KEYBOARD_H

static uint16_t key_timer = 0;
static bool key_pressed = false;
static bool key_repeating = false;
static uint16_t key_repeat = 0;
static uint16_t keys_to_repeat[] = { FAST_REPEAT_KEYS };
static uint16_t layers_to_check[] = { FAST_REPEAT_LAYERS };

bool check_large_layer(void){
    for (int i = 0; i < FAST_REPEAT_LAYER_COUNT; i++){
        if (IS_LAYER_ON(layers_to_check[i])){
            return true;
        }
    }
    return false;
}

bool check_if_repeat_key(uint8_t keycode){
    for (int i = 0; i < FAST_REPEAT_KEY_COUNT; i++){
        if (keys_to_repeat[i] == keycode){
            return true;
        }
    }
    return false;
}

// bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
bool process_repeat_key(uint16_t keycode, keyrecord_t *record) {
    if (check_large_layer()){
        #ifndef REPEAT_ALL_KEYS_ENABLED
        if (check_if_repeat_key(keycode)){
            if (record->event.pressed){
                    register_code(keycode);
                    unregister_code(keycode);
                    key_repeat = keycode;
                    key_pressed = true;
                    key_timer = timer_read();
                } else {
                    key_pressed = false;
                    key_repeating = false;
                }

                return false;
        }
        #endif
        #ifdef REPEAT_ALL_KEYS_ENABLED
        switch (keycode) {
            case KC_A ... KC_F24:
                if (record->event.pressed){
                            register_code(keycode);
                            unregister_code(keycode);
                            key_repeat = keycode;
                            key_pressed = true;
                            key_timer = timer_read();
                        } else {
                            key_pressed = false;
                            key_repeating = false;
                        }

                        return false;
        }
        #endif
    } else if (key_pressed) {
        key_pressed = false;
        key_repeating = false;
    }
    return true;
}

void matrix_scan_user(void) { 
    if (key_pressed) {
        if (!key_repeating && timer_elapsed(key_timer) > REPEAT_DELAY) {
            key_repeating = true;
            key_timer = timer_read();
        }
        if (key_repeating && timer_elapsed(key_timer) > REPEAT_TERM) {
            register_code(key_repeat);
            key_timer = timer_read();
            unregister_code(key_repeat);
        }
        
    }
}