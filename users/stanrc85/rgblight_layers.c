#include "stanrc85.h"

static uint8_t middle = 0;
static uint8_t bottom = 0;

layer_state_t layer_state_set_user(layer_state_t state) {
    middle = bottom = 0;
    switch (get_highest_layer(state)) {
    case _FN1_60:
        middle = 1;
        break;
    case _FN2_60:
        bottom = 1;
        break;
    case _DEFAULT:
        middle = 1;
        bottom = 1;
        break;
    default: //  for any other layers, or the default layer
        break;
    }
    return state;
}

bool led_update_user(led_t led_state) {
    writePin(INDICATOR_PIN_0, !led_state.caps_lock);
    writePin(INDICATOR_PIN_1, !middle);
    writePin(INDICATOR_PIN_2, !bottom);
    return false;
}