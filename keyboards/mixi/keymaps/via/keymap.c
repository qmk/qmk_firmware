#include QMK_KEYBOARD_H

// please change this value to the desired layer definitions
#define LAYERNUM 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * | Knob: Layer +/-                       |
     * .---------------------------------------.
     * | Mute     | Play/Pause | Hold: Layer 2 |
     * |----------|------------|---------------|
     * | Previous | Up         | Next          |
     * |----------|------------|---------------|
     * | Left     | Down       | Right         |
     * '---------------------------------------'
     */
    [0] =
        LAYOUT(
                KC_MUTE,  KC_MPLY, MO(2), 
                KC_MNXT,  KC_UP  , KC_MPRV     , 
                KC_LEFT, KC_DOWN , KC_RGHT
              ),

    /*
     * .-----------------------.
     * | NUM 7 | NUM 8 | NUM 9 |
     * |-------|-------|-------|
     * | NUM 4 | NUM 5 | NUM 6 |
     * |-------|-------|-------|
     * | NUM 1 | NUM 2 | NUM 3 |
     * '-----------------------'
     */
    [1] =
        LAYOUT(
                KC_P7, KC_P8, KC_P8,
                KC_P4, KC_P5, KC_P6,
                KC_P1, KC_P2, KC_P3
              ),

    /*
     * | Knob: Volume +/-                     |
     * .--------------------------------------.
     * | N/A          | N/A   | Hold: Layer 2 |
     * |--------------|-------|---------------|
     * | RESET EEPROM | RESET | DEBUG MODE    |
     * |--------------|-------|---------------|
     * | N/A          | N/A   | N/A           |
     * '--------------------------------------'
     */
    [2] =
        LAYOUT(
                KC_NO  , KC_NO, KC_TRNS, 
                EEP_RST, RESET, DEBUG  , 
                KC_NO  , KC_NO, KC_NO
              )

};

const rgblight_segment_t PROGMEM _base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, RGBLED_NUM, HSV_WHITE}
        );
const rgblight_segment_t PROGMEM _middle_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, RGBLED_NUM, HSV_GREEN}
        );
const rgblight_segment_t PROGMEM _top_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, RGBLED_NUM, HSV_RED}
        );

const rgblight_segment_t* const PROGMEM _rgb_layers[] =
RGBLIGHT_LAYERS_LIST(
        _base_layer,
        _middle_layer,
        _top_layer
        );

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
        case 0:
            rgblight_blink_layer(0, 500);
            break;
        case 1:
            rgblight_blink_layer(1, 500);
            break;
        case 2:
            rgblight_blink_layer(2, 500);
            break;
    }
    return state;
}

uint8_t selected_layer = 0;
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (layer_state_is(2)) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        } else {
            if (clockwise && selected_layer < (LAYERNUM-2)) { /* Prevent switch to layer 2 using encoder */
                selected_layer++;
                layer_move(selected_layer);
            } else if (!clockwise && selected_layer > 0) {
                selected_layer--;
                layer_move(selected_layer);
            }
        }
    }
}
