#include "final80v2.h"

#ifdef RGB_MATRIX_ENABLE

#    define XX NO_LED
led_config_t g_led_config = {  //
    {
        // Key Matrix to LED Index
        {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, XX},        //
        {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, XX},  //
        {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, XX},  //
        {58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, XX, XX},  //
        {59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, XX, 70, 71, 72},  //
        {81, 80, 79, XX, XX, 78, XX, XX, XX, 77, XX, 76, 75, 74, 73},  // !! 轴灯对应矩阵的接线顺序
    },
    {
        // LED Index to Physical Position
        {214, 4},  {220, 11}, {214, 18}, {206, 11},                                                                                                                                                   // First 4 for encoder.
        {2, 3},    {19, 3},   {32, 3},   {45, 3},   {59, 3},   {76, 3},   {89, 3},   {103, 3},  {116, 3},  {133, 3},  {147, 3},  {160, 3},  {173, 3},  {191, 3},                                      // row0
        {184, 16}, {163, 16}, {150, 16}, {136, 16}, {123, 16}, {110, 16}, {96, 16},  {83, 16},  {69, 16},  {56, 16},  {42, 16},  {29, 16},  {16, 16},  {2, 16},                                       // row1
        {5, 27},   {22, 27},  {36, 27},  {49, 27},  {63, 27},  {76, 27},  {89, 27},  {103, 27}, {116, 27}, {130, 27}, {143, 27}, {157, 27}, {170, 27}, {187, 27},                                     // row2
        {182, 38}, {160, 38}, {146, 38}, {133, 38}, {119, 38}, {106, 38}, {93, 38},  {79, 38},  {66, 38},  {52, 38},  {39, 38},  {26, 38},  {7, 38},                                                  // row3
        {10, 49},  {32, 49},  {46, 49},  {59, 49},  {73, 49},  {86, 49},  {99, 49},  {113, 49}, {126, 49}, {140, 49}, {153, 49}, {178, 49}, {207, 52}, {221, 63},                                     // row4
        {207, 63}, {193, 63}, {175, 60}, {160, 60}, {145, 60}, {89, 60},  {34, 60},  {19, 60},  {3, 60},                                                                                              // row5
        {1, 64},   {43, 64},  {72, 64},  {104, 64}, {137, 64}, {180, 64}, {224, 64}, {224, 46}, {224, 29}, {224, 1},  {180, 1},  {147, 1},  {116.1},   {77, 1},   {45, 1}, {1, 1}, {1, 27}, {1, 41},  // Last 18 for backlight.
        //!! 按接线顺序排列轴灯的物理位置
    },

    {
        // LED Index to Flag
        8, 8, 8, 8,                                            //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,              //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,              //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,              //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,                 //
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4,              //
        1, 1, 1, 4, 1, 4, 1, 4, 4,                             //
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  //!! 每个灯是干啥用的

    }};

// {旋钮背光用作层指示灯} -----------------------------------------------//
void rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {  // Capslock = RED
        rgb_matrix_set_color(0, 200, 0, 0);
        rgb_matrix_set_color(1, 200, 0, 0);
        rgb_matrix_set_color(2, 200, 0, 0);
        rgb_matrix_set_color(3, 200, 0, 0);
    } else if (get_autoshift_state()) {  // AUTO_SHIFT = GREEN
        rgb_matrix_set_color(0, 0, 200, 0);
        rgb_matrix_set_color(1, 0, 200, 0);
        rgb_matrix_set_color(2, 0, 200, 0);
        rgb_matrix_set_color(3, 0, 200, 0);
    } else if (biton32(layer_state) == 1) {  // UPPER_LAYER = BLUE
        rgb_matrix_set_color(0, 0, 0, 200);
        rgb_matrix_set_color(1, 0, 0, 200);
        rgb_matrix_set_color(2, 0, 0, 200);
        rgb_matrix_set_color(3, 0, 0, 200);
    } else {
        rgb_matrix_set_color(0, 0, 0, 0);
        rgb_matrix_set_color(1, 0, 0, 0);
        rgb_matrix_set_color(2, 0, 0, 0);
        rgb_matrix_set_color(3, 0, 0, 0);
    }
}

#endif

#ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
