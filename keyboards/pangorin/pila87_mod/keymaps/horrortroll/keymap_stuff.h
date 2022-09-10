// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE = 0,
    _FN = 1
};

// For CUSTOM_GRADIENT
HSV gradient_0          = {205, 250, 255};
HSV gradient_100        = {140, 215, 125};
bool reflected_gradient = false;
uint8_t gp_i            = 0;

typedef struct {
    HSV gradient_0;
    HSV gradient_1;
    bool reflected;
} CUSTOM_PRESETS;

enum layer_keycodes {
    //Custom Gradient control keycode
    G1_HUI = SAFE_RANGE, //Custom gradient color 1 hue increase
    G1_HUD,              //Custom gradient color 1 hue decrease
    G1_SAI,              //Custom gradient color 1 saturation increase
    G1_SAD,              //Custom gradient color 1 saturation decrease
    G1_VAI,              //Custom gradient color 1 value increase
    G1_VAD,              //Custom gradient color 1 value decrease
    G2_HUI,              //Custom gradient color 2 hue increase
    G2_HUD,              //Custom gradient color 2 hue decrease
    G2_SAI,              //Custom gradient color 2 saturation increase
    G2_SAD,              //Custom gradient color 2 saturation decrease
    G2_VAI,              //Custom gradient color 2 value increase
    G2_VAD,              //Custom gradient color 2 value decrease
    G_PRE,               //Gradient presets
    REF_G,               //Toggle between linear and reflected gradient
    G_FLIP,              //Flip the gradient colors
  
    //Custom led effect keycode
    RGB_C_E,             //Cycle user effect
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t color_adj_step = 5;

    CUSTOM_PRESETS gradient_presets[] = {
    {{41 , 255, 255}, {233, 245, 255}, false },
    {{45 , 245, 155}, {160, 255,  80}, false },
    {{173, 245,  40}, {41 , 255, 205}, true  },
    {{32 , 255, 165}, {217, 185,  70}, false },
    {{240, 255, 145}, {115, 255, 245}, true  },
    {{118, 255, 255}, {242, 255, 255}, false },
    {{212,  0 ,   0}, {223, 235, 165}, true  },
    {{205, 250, 255}, {140, 215, 125}, false },
    };

    uint8_t gp_length = sizeof(gradient_presets)/sizeof(gradient_presets[0]);

    switch (keycode) {
        case G1_HUI:
            if (record->event.pressed) {
                gradient_0.h += color_adj_step;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_HUD:
            if (record->event.pressed) {
                gradient_0.h -= color_adj_step;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_SAI:
            if (record->event.pressed) {
                gradient_0.s = (gradient_0.s + color_adj_step * 2 <= 255) ? gradient_0.s + color_adj_step * 2 : 255;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_SAD:
            if (record->event.pressed) {
                gradient_0.s = (gradient_0.s - color_adj_step * 2 >= 0) ? gradient_0.s - color_adj_step * 2 : 0;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_VAI:
            if (record->event.pressed) {
                gradient_0.v = (gradient_0.v + color_adj_step * 2 <= 255) ? gradient_0.v + color_adj_step * 2 : 255;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_VAD:
            if (record->event.pressed) {
                gradient_0.v = (gradient_0.v - color_adj_step * 2 >= 0) ? gradient_0.v - color_adj_step * 2 : 0;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G2_HUI:
            if (record->event.pressed) {
                gradient_100.h += color_adj_step;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_HUD:
            if (record->event.pressed) {
                gradient_100.h -= color_adj_step;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_SAI:
            if (record->event.pressed) {
                gradient_100.s = (gradient_100.s + color_adj_step * 2 <= 255) ? gradient_100.s + color_adj_step * 2 : 255;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_SAD:
            if (record->event.pressed) {
                gradient_100.s = (gradient_100.s - color_adj_step * 2 >= 0) ? gradient_100.s - color_adj_step * 2 : 0;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_VAI:
            if (record->event.pressed) {
                gradient_100.v = (gradient_100.v + color_adj_step * 2 <= 255) ? gradient_100.v + color_adj_step * 2 : 255;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_VAD:
            if (record->event.pressed) {
                gradient_100.v = (gradient_100.v - color_adj_step * 2 >= 0) ? gradient_100.v - color_adj_step * 2 : 0;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G_PRE:
            if (record->event.pressed) {
                gp_i = (gp_i + gp_length ) % gp_length;

                gradient_0 = gradient_presets[gp_i].gradient_0;
                gradient_100 = gradient_presets[gp_i].gradient_1;
                reflected_gradient = gradient_presets[gp_i].reflected;

                gp_i += 1;
            }
            return false;
        case REF_G:
            if (record->event.pressed) {
                reflected_gradient = !reflected_gradient;
            }
            return false;
        case G_FLIP:
            if (record->event.pressed) {
                HSV temp_color = gradient_0;
                gradient_0 = gradient_100;
                gradient_100 = temp_color;
            }
            return false;
        case RGB_C_E:
            if (record->event.pressed) {
                switch (rgb_matrix_get_mode()) {
                    case RGB_MATRIX_CUSTOM_CUSTOM_GRADIENT:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_DIAGONAL);
                        return false;
                    case RGB_MATRIX_CUSTOM_DIAGONAL:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_COOL_DIAGONAL);
                        return false;
                    case RGB_MATRIX_CUSTOM_COOL_DIAGONAL:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_RAINBOW_REACTIVE_SIMPLE);
                        return false;
                    case RGB_MATRIX_CUSTOM_RAINBOW_REACTIVE_SIMPLE:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_KITT);
                        return false;
                    case RGB_MATRIX_CUSTOM_KITT:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_RANDOM_BREATH_RAINBOW);
                        return false;
                    default:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_CUSTOM_GRADIENT);
                        return false;
                }
            }
            return false;
	    }
    return true;
}

void rgb_matrix_indicators_user(void) {
    switch (biton32(layer_state)) {
        case _FN:
            rgb_matrix_set_color( 3, 0, 0, 0); rgb_matrix_set_color( 4, 0, 0, 0); rgb_matrix_set_color( 6, 0, 0, 0); rgb_matrix_set_color( 7, 0, 0, 0);
            rgb_matrix_set_color( 8, 0, 0, 0); rgb_matrix_set_color( 9, 0, 0, 0); rgb_matrix_set_color(10, 0, 0, 0); rgb_matrix_set_color(11, 0, 0, 0);
            rgb_matrix_set_color(12, 0, 0, 0); rgb_matrix_set_color(13, 0, 0, 0); rgb_matrix_set_color(14, 0, 0, 0); rgb_matrix_set_color(15, 0, 0, 0);
            rgb_matrix_set_color(19, 0, 0, 0); rgb_matrix_set_color(20, 0, 0, 0); rgb_matrix_set_color(21, 0, 0, 0); rgb_matrix_set_color(22, 0, 0, 0);
            rgb_matrix_set_color(23, 0, 0, 0); rgb_matrix_set_color(24, 0, 0, 0); rgb_matrix_set_color(25, 0, 0, 0); rgb_matrix_set_color(26, 0, 0, 0);
            rgb_matrix_set_color(28, 0, 0, 0); rgb_matrix_set_color(29, 0, 0, 0); rgb_matrix_set_color(30, 0, 0, 0); rgb_matrix_set_color(31, 0, 0, 0);
            rgb_matrix_set_color(32, 0, 0, 0); rgb_matrix_set_color(33, 0, 0, 0); rgb_matrix_set_color(40, 0, 0, 0); rgb_matrix_set_color(41, 0, 0, 0);
            rgb_matrix_set_color(48, 0, 0, 0); rgb_matrix_set_color(49, 0, 0, 0); rgb_matrix_set_color(50, 0, 0, 0); rgb_matrix_set_color(51, 0, 0, 0);
            rgb_matrix_set_color(52, 0, 0, 0); rgb_matrix_set_color(53, 0, 0, 0); rgb_matrix_set_color(54, 0, 0, 0); rgb_matrix_set_color(55, 0, 0, 0);
            rgb_matrix_set_color(56, 0, 0, 0); rgb_matrix_set_color(57, 0, 0, 0); rgb_matrix_set_color(58, 0, 0, 0); rgb_matrix_set_color(59, 0, 0, 0);
            rgb_matrix_set_color(61, 0, 0, 0); rgb_matrix_set_color(64, 0, 0, 0); rgb_matrix_set_color(65, 0, 0, 0); rgb_matrix_set_color(66, 0, 0, 0);
            rgb_matrix_set_color(67, 0, 0, 0); rgb_matrix_set_color(68, 0, 0, 0); rgb_matrix_set_color(69, 0, 0, 0); rgb_matrix_set_color(70, 0, 0, 0);
            rgb_matrix_set_color(71, 0, 0, 0); rgb_matrix_set_color(72, 0, 0, 0); rgb_matrix_set_color(73, 0, 0, 0);
            break;
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(40, 217, 71, 115); // assuming caps lock is at led #40
    }

    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(89, 217, 71, 115); // assuming scroll lock is at led #89
    }
}