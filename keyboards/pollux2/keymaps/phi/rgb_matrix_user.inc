RGB_MATRIX_EFFECT(my_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#define LAYOUT(                                                 \
    L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
    /*               */ L34, L35, R30, R31                      \
) {                                                             \
      L00, L01, L02, L03, L04, L05,                             \
          L10, L11, L12, L13, L14, L15,                         \
          L20, L21, L22, L23, L24, L25,                         \
          L34, L35,                                             \
          0, 0, 0, 0, 0, 0,                                     \
          R05, R04, R03, R02, R01, R00,                         \
          R15, R14, R13, R12, R11, R10,                         \
          R25, R24, R23, R22, R21, R20,                         \
          R31, R30,                                             \
          0, 0, 0, 0, 0, 0                                      \
          }

uint8_t layer_image [][DRIVER_LED_TOTAL] = {
    [0] = LAYOUT(
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 2, 2, 3
    ),
    [1] = LAYOUT(
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
        1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2,
        4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        1, 1, 4, 4
    ),
    [2] = LAYOUT(
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4,
        4, 1, 1, 1, 1, 3, 4, 4, 4, 4, 1, 4,
        4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1,
        4, 4, 4, 4
    ),
};

static void set_color_internal (uint8_t index, uint8_t color_index) {
    switch (color_index) {
      case 0:
        rgb_matrix_set_color(index, 0x10, 0x10, 0x10);
        break;
      case 1:
        rgb_matrix_set_color(index, 0x30, 0x08, 0x08);
        break;
      case 2:
        rgb_matrix_set_color(index, 0x08, 0x30, 0x08);
        break;
      case 3:
        rgb_matrix_set_color(index, 0x08, 0x08, 0x30);
        break;
      case 4:
        rgb_matrix_set_color(index, 0x00, 0x00, 0x00);
        break;
    }
}

static bool my_effect (effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        if (layer_state & 2) {
            set_color_internal(i, layer_image[1][i]);
        } else if (layer_state & 4) {
            set_color_internal(i, layer_image[2][i]);
        } else {
            set_color_internal(i, layer_image[0][i]);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif
