// qmk flash -kb bm40hsrgb -km sigma-squared

#include "sigma-squared.h"

//game and chat layer led colors

const rgblight_segment_t PROGMEM game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 11, 1, 127, 255, 100}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    game_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, GAME));
    return state;
}

//actions to do when certain keys are pressed
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //send message when going back to game layer from chat layer
    switch (keycode) {
        case TG(CHAT):
            if (record->event.pressed) {
                tap_code(KC_ENT);
            }
            return true;
    }
    return true;
}
