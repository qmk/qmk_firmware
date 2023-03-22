RGB_MATRIX_EFFECT(base_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/* shorthand RGB_ colors */
  //                r     g    b
#define AZU       0x99, 0xF5, 0xFF
#define BLA       0x00, 0x00, 0x00
#define BLU       0x00, 0x00, 0xFF
#define CHA       0x80, 0xFF, 0x00
#define COR       0xFF, 0x7C, 0x4D
#define CYA       0x00, 0xFF, 0xFF
#define GOL       0xFF, 0xD9, 0x00
#define GOD       0xD9, 0xA5, 0x21
#define GRN       0x00, 0xFF, 0x00
#define MAG       0xFF, 0x00, 0xFF
#define ORA       0xFF, 0x80, 0x00
#define PIN       0xFF, 0x80, 0xBF
#define PUR       0x7A, 0x00, 0xFF
#define RED       0xFF, 0x00, 0x00
#define SPR       0x00, 0xFF, 0x80
#define TEA       0x00, 0x80, 0x80
#define TUR       0x47, 0x6E, 0x6A
#define WHI       0xFF, 0xFF, 0xFF
#define YEL       0xFF, 0xFF, 0x00
#define OFF       BLA

struct RGB_key {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct RGB_key base_rgb[56] = {
  // Left half
  // ╭────────────────────────────────────────────────────────────────────────╮
        [0]=AZU,    [7]=BLA,    [8]=CHA,    [15]=COR,   [16]=CYA,   [20]=GOL,
  // ├────────────────────────────────────────────────────────────────────────┤
        [1]=GOD,    [6]=GRN,    [9]=MAG,    [14]=ORA,   [17]=PIN,   [21]=PUR,
  // ├────────────────────────────────────────────────────────────────────────┤
        [2]=RED,    [5]=SPR,    [10]=TEA,   [13]=TUR,   [18]=WHI,   [22]=YEL,
  // ├────────────────────────────────────────────────────────────────────────┤
        [3]=OFF,    [4]=GRN,    [11]=GRN,   [12]=GRN,   [19]=GRN,   [23]=GRN,
  // ├────────────────────────────────────────────────────────────────────────┤
                                            [26]=GRN,   [27]=GRN,   [28]=GRN,
                                                        [25]=GRN,   [24]=GRN,
  // ╰────────────────────────────────────────────────────────────────────────╯

  // Right half
  // ╭────────────────────────────────────────────────────────────────────────╮
        [29]=GRN,   [36]=GRN,   [37]=GRN,   [44]=GRN,   [45]=GRN,   [49]=GRN,
  // ├────────────────────────────────────────────────────────────────────────┤
        [30]=GRN,   [35]=GRN,   [38]=GRN,   [43]=GRN,   [46]=GRN,   [50]=GRN,
  // ├────────────────────────────────────────────────────────────────────────┤
        [31]=GRN,   [34]=GRN,   [39]=GRN,   [42]=GRN,   [47]=GRN,   [51]=GRN,
  // ├────────────────────────────────────────────────────────────────────────┤
        [32]=GRN,   [33]=GRN,   [40]=GRN,   [41]=GRN,   [48]=GRN,   [52]=GRN,
  // ├────────────────────────────────────────────────────────────────────────┤
        [53]=GRN,   [54]=GRN,
        [55]=GRN
  // ╰────────────────────────────────────────────────────────────────────────╯
};

static bool base_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for(uint8_t i = 0; i < 56; i++) {
        rgb_matrix_set_color(i, base_rgb[i].r, base_rgb[i].g, base_rgb[i].b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool nav_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for(uint8_t i = 0; i < 56; i++) {
        rgb_matrix_set_color(i, base_rgb[i].r, base_rgb[i].g, base_rgb[i].b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool sym_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for(uint8_t i = 0; i < 56; i++) {
        rgb_matrix_set_color(i, base_rgb[i].r, base_rgb[i].g, base_rgb[i].b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool num_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for(uint8_t i = 0; i < 56; i++) {
        rgb_matrix_set_color(i, base_rgb[i].r, base_rgb[i].g, base_rgb[i].b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif