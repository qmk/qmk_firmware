#include QMK_KEYBOARD_H

#ifndef REPEAT_DELAY
    #define REPEAT_DELAY 150
#endif
#ifndef REPEAT_TERM
    #define REPEAT_TERM 6
#endif

static uint16_t key_timer = 0;
static bool key_pressed = false;
static bool key_repeating = false;
static uint16_t repeat_delay = REPEAT_DELAY;
static uint8_t repeat_term = REPEAT_TERM;
static uint16_t key_repeat = 0;
#ifndef REPEAT_ALL_KEYS_ENABLED
static uint16_t keys_to_repeat[] = { FAST_REPEAT_KEYS };
#endif
#ifdef BOOSTED_REPEAT_ENABLED
    #ifndef BOOSTED_REPEAT_DELAY
    #define BOOSTED_REPEAT_DELAY REPEAT_DELAY
    #endif
static uint16_t keys_to_boost[] = { BOOSTED_REPEAT_KEYS };
#endif
static uint16_t layers_to_check[] = { FAST_REPEAT_LAYERS };

bool check_large_layer(void){
    for (int i = 0; i < FAST_REPEAT_LAYER_COUNT; i++){
        if (IS_LAYER_ON(layers_to_check[i])){
            return true;
        }
    }
    return false;
}

#ifdef BOOSTED_REPEAT_ENABLED
bool check_if_boosted_key(uint8_t keycode){
    for (int i = 0; i < BOOSTED_REPEAT_KEY_COUNT; i++){
        if (keys_to_boost[i] == keycode){
            return true;
        }
    }
    return false;
}
#endif

#ifndef REPEAT_ALL_KEYS_ENABLED
bool check_if_repeat_key(uint8_t keycode){
    for (int i = 0; i < FAST_REPEAT_KEY_COUNT; i++){
        if (keys_to_repeat[i] == keycode){
            return true;
        }
    }
    return false;
}
#endif

bool process_repeat_key(uint16_t keycode, keyrecord_t *record) {
    if (check_large_layer()){
        #ifndef REPEAT_ALL_KEYS_ENABLED
        if (check_if_repeat_key(keycode)){
            if (record->event.pressed){
                    if (keycode!=key_repeat) {
                        key_repeating = false;
                    }
                    register_code(keycode);
                    unregister_code(keycode);
                    #ifdef BOOSTED_REPEAT_ENABLED
                    boosted = check_if_boosted_key(keycode);
                    #endif
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
                            if (keycode!=key_repeat) {
                                key_repeating = false;
                            }
                            register_code(keycode);
                            unregister_code(keycode);
                            #ifdef BOOSTED_REPEAT_ENABLED
                            if (check_if_boosted_key(keycode)) {
                                repeat_delay = BOOSTED_REPEAT_DELAY;
                                repeat_term = BOOSTED_REPEAT_TERM;
                            } else {
                                repeat_delay = REPEAT_DELAY;
                                repeat_term = REPEAT_TERM;
                            }
                            #endif
                            key_repeat = keycode;
                            key_pressed = true;
                            key_timer = timer_read();
                } else if (keycode==key_repeat) {
                    key_pressed = false;
                    key_repeating = false;
                    repeat_delay = REPEAT_DELAY;
                    repeat_term = REPEAT_TERM;
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
        if (!key_repeating && timer_elapsed(key_timer) > repeat_delay) {
            key_repeating = true;
            key_timer = timer_read();
        }
        if (key_repeating && timer_elapsed(key_timer) > repeat_term) {
            register_code(key_repeat);
            key_timer = timer_read();
            unregister_code(key_repeat);
        }
        
    }
}