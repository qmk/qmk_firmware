#include QMK_KEYBOARD_H

#define _BASE 0 
#define _CAPA1 1
#define _CAPA2 2
#define _CAPA3 3

layer_state_t layer_state_set_user(layer_state_t state);

void keyboard_post_init_user(void) {
    // rgblight_enable() inicia el control RGB
    // rgblight_sethsv() permite configurar el color HSV
    rgblight_enable();
    rgblight_sethsv(HSV_BLUE); // Color predeterminado al inicio
    layer_state_set_user(layer_state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);
    switch (layer) {    
        case _CAPA1:
            rgblight_sethsv(HSV_GREEN);
            break;

        case _CAPA2:
            rgblight_sethsv(HSV_RED);
            break;

        case _CAPA3:
            rgblight_sethsv(HSV_PINK);
            break;

        default:
            rgblight_sethsv(HSV_BLUE); // Color predeterminado si no está en una capa específica
            break;
    }
    
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ... Tu disposición de teclas sigue aquí ... */
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    /* ... Tu configuración de encoders sigue aquí ... */
};
#endif
