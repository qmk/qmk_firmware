#define MINIMAL_BASEx(hue,sat) \
    rgblight_sethsv_range(hue, sat, 0, 0, 12); \
    rgblight_sethsv_range(hue, sat, 100, 5, 7)

#define MINIMAL_BASE(hue, sat) \
    {0, 12, hue, sat, 0}, \
    {5, 2, hue, sat, 100}

#define MINIMAL(hue, sat) \
    {0, 12, hue, sat, 0}, \
    {3, 1, hue, sat, 100}, \
    {8, 1, hue, sat, 100}

const int yellow = 30;
const int green = 99;
const int red = 252;
const int base_sat = 120;

const rgblight_segment_t PROGMEM _BL_rgblayer[] = RGBLIGHT_LAYER_SEGMENTS(
    MINIMAL_BASE(yellow,250)
);
const rgblight_segment_t PROGMEM _FN_rgblayer[] = RGBLIGHT_LAYER_SEGMENTS(
    MINIMAL(green,255)
);
const rgblight_segment_t PROGMEM _SL_rgblayer[] = RGBLIGHT_LAYER_SEGMENTS(
    MINIMAL(red,255)
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    _BL_rgblayer,
    _FN_rgblayer,
    _SL_rgblayer
);

void keyboard_post_init_user(void) {
    MINIMAL_BASEx(yellow,200);
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BL));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SL));
    return state;
}
