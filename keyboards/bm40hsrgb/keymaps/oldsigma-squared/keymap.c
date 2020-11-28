// qmk flash -kb bm40hsrgb -km sigma-squared

#include "sigma-squared.h"

//game and chat layer led colors
const rgblight_segment_t PROGMEM game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 11, 1, 127, 255, 100}
);

const rgblight_segment_t PROGMEM chat_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 11, 1, 85, 255, 100}
);

const rgblight_segment_t PROGMEM secgame_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 11, 1, 0, 255, 100}
);
const rgblight_segment_t PROGMEM navr_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 40, 1, 127, 255, 100}
);

const rgblight_segment_t PROGMEM medr_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 39, 1, 201, 255, 100}
);

const rgblight_segment_t PROGMEM funl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 43, 1, 0, 255, 100}
);
const rgblight_segment_t PROGMEM nsl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 42, 1, 169, 255, 100}
);

const rgblight_segment_t PROGMEM nssl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 41, 1, 85, 255, 100}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    game_layer, chat_layer, secgame_layer, navr_layer, medr_layer, funl_layer, nsl_layer, nssl_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, GAME));
    rgblight_set_layer_state(1, layer_state_cmp(state, CHAT));
    rgblight_set_layer_state(2, layer_state_cmp(state, SECGAME));
    rgblight_set_layer_state(3, layer_state_cmp(state, NAVR));
    rgblight_set_layer_state(4, layer_state_cmp(state, MEDR));
    rgblight_set_layer_state(5, layer_state_cmp(state, FUNL));
    rgblight_set_layer_state(6, layer_state_cmp(state, NSL));
    rgblight_set_layer_state(7, layer_state_cmp(state, NSSL));
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
    //macro strings
    if (record->event.pressed) {
      switch(keycode) {
        case M_EMAIL1:
          SEND_STRING("vincenzo.barroso@gmail.com");
          return false; break;
        case M_EMAIL2:
          SEND_STRING("undercoverdemigod@gmail.com");
          return false; break;
        case M_MATRIKEL:
          SEND_STRING("7362341");
          return false; break;
        case M_PHONE:
          SEND_STRING("+49 163 1775393");
          return false; break;
        case M_ADDRESS:
          SEND_STRING("Melatengürtel 113");
          return false; break;
      }
    }
    return true;
}
