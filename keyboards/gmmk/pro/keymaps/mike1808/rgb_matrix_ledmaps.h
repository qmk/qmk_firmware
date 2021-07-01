#pragma once

#include "quantum.h"

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

#    define RGB_MATRIX_LAYERS_MAX_SEGMENTS 4

#    define XXX \
        { 0, 0, 0 }

// clang-format off
#   define RGB_MATRIX_LAYOUT_LEDMAP( \
        k13, k26, k36, k31, k33, k07, k63, k71, k76, ka6, ka7, ka3, ka5, k97,     k01, \
        k16, k17, k27, k37, k47, k46, k56, k57, k67, k77, k87, k86, k66, ka1,     k65, \
        k11, k10, k20, k30, k40, k41, k51, k50, k60, k70, k80, k81, k61, ka2,     k15, \
        k21, k12, k22, k32, k42, k43, k53, k52, k62, k72, k82, k83,     ka4,      k25, \
        k00, k14, k24, k34, k44, k45, k55, k54, k64, k74, k85,    k91,       k35, k75, \
        k06,    k90,    k93,       k94,          k95,     k92, k04,     k03, k73, k05  \
    ) \
    { \
        k13, k16, k11, k21, k00, k06, k26, k17, \
        k10, k12, k14, k90, k36, k27, k20, k22, \
        k24, k93, k31, k37, k30, k32, k34, k33, \
        k47, k40, k42, k44, k07, k46, k41, k43, \
        k45, k94, k63, k56, k51, k53, k55, k71, \
        k57, k50, k52, k54, k76, k67, k60, k62, \
        k64, k95, ka6, k77, k70, k72, k74, k92, \
        ka7, k87, k80, k82, k85, ka3, k86, k81, \
        k83, k04, ka5, XXX, XXX, k97, XXX, XXX, \
        k65, XXX, XXX, k15, XXX, XXX, k66, k05, \
        XXX, XXX, k75, XXX, XXX, ka1, k25, XXX, \
        XXX, k61, k91, XXX, XXX, ka2, k35, k03, \
        ka4, k73 \
    }
// clang-format on

#    define RGB_MATRIX_LAYER_SEGMENTS(...) \
        { __VA_ARGS__, NULL }

#    define RGB_MATRIX_LAYER(l, s) \
        { .layout = l, }

typedef struct {
    uint8_t index;
    uint8_t count;
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
} rgb_matrix_layer_segment;

typedef struct {
    uint8_t                  layout[DRIVER_LED_TOTAL][3];
    rgb_matrix_layer_segment segments[RGB_MATRIX_LAYERS_MAX_SEGMENTS];
} rgb_matrix_layer;

extern rgb_matrix_layer ledmaps[];

void set_layer_rgb(uint8_t led_min, uint8_t led_max, int layer);

void rgb_matrix_layers_enable(void);
void rgb_matrix_layers_disable(void);

#    define RED \
        { HSV_RED }
#    define CORAL \
        { HSV_CORAL }
#    define ORANGE \
        { HSV_ORANGE }
#    define GOLDEN \
        { HSV_GOLDENROD }
#    define GOLD \
        { HSV_GOLD }
#    define YELLOW \
        { HSV_YELLOW }
#    define CHART \
        { HSV_CHARTREUSE }
#    define GREEN \
        { HSV_GREEN }
#    define SPRING \
        { HSV_SPRINGGREEN }
#    define TURQ \
        { HSV_TURQUOISE }
#    define TEAL \
        { HSV_TEAL }
#    define CYAN \
        { HSV_CYAN }
#    define AZURE \
        { HSV_AZURE }
#    define BLUE \
        { HSV_BLUE }
#    define PURPLE \
        { HSV_PURPLE }
#    define MAGENT \
        { HSV_MAGENTA }
#    define PINK \
        { HSV_PINK }
#    define BLACK \
        { HSV_BLACK }

#endif  // RGB_MATRIX_LEDMAPS_ENABLED

void rgb_matrix_indicators_keymap(void);
void rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
