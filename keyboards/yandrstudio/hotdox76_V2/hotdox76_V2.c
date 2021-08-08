#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        { NO_LED, 34, 33, 32, 35, 37, 36     },
        { 27, 28, 29, 30, 31, NO_LED, NO_LED },
        { 26, 25, 24, 23, 22, 21, 20         },
        { 14, 15, 16, 17, 18, 19, NO_LED     },
        { 13, 12, 11, 10,  9,  8,  7         },
        {   0, 1,  2,   3, 4,  5,  6         },
        /*right*/
        { NO_LED, 72, 71, 70, 73, 75, 74     },
        { 65, 66, 67, 68, 69, NO_LED, NO_LED },
        { 64, 63, 62, 61, 60, 59, 58         },
        { 52, 53, 54, 55, 56, 57, NO_LED     },
        { 51, 50, 49, 48, 47, 46, 45         },
        { 38, 39, 40, 41, 42, 43, 44         }
    },
    {
        // LED Index to Physical Position
        {0,0},    {17,0},  {34,0},  {52,0},  {69,0},  {86,0},  {103,0}, \
        {103,13}, {86,13}, {69,13}, {52,13}, {34,13}, {17,13}, {0,13}, \
        {0,26},   {17,26}, {34,26}, {52,26}, {69,26}, {86,26}, \
        {103,38}, {86,38}, {69,38}, {52,38}, {34,38}, {17,38}, {0,38}, \
        {0,51},   {17,51}, {34,51}, {52,51}, {69,51},  \
                  {86,64}, {69,64}, {52,64}, {34,64}, {17,64}, {0,64}, \
                                                                                    \
        {224,0},  {207,0},  {190,0},  {172,0},  {155,0},  {138,0},  {121,0}, \
        {121,13}, {138,13}, {155,13}, {172,13}, {190,13}, {207,13}, {224,13}, \
        {224,26}, {207,26}, {190,26}, {172,26}, {155,26}, {138,26}, \
        {121,38}, {138,38}, {155,38}, {172,38}, {190,38}, {207,38}, {224,38}, \
        {224,51}, {207,51}, {190,51}, {172,51}, {155,51},  \
                  {138,64}, {155,64}, {172,64}, {190,64}, {207,64}, {224,64}\

    },
    {
      // LED Index to Flag
      4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,\
      4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
    }
};


#endif

#ifdef OLED_DRIVER_ENABLE
char wpm_str[10];  // limit WPM string length.

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    //   oled_scroll_set_area(0,2);
    // oled_scroll_set_speed(4);
    // oled_scroll_right();
#   ifdef I_AM_LEFT
        return OLED_ROTATION_0;
#   else
        return OLED_ROTATION_180;
#   endif
}

void render_logo(void) {

}

void oled_task_user(void) {

#   ifdef I_AM_LEFT


    switch (biton32(layer_state)) {
        case 0:
            oled_write_ln("Layer: Base", false);
            break;
        case 1:
            oled_write_ln("Layer: Function", false);
            break;
        case 2:
            oled_write_ln("Layer: System", false);
            break;
        case 3:
            oled_write_ln("Layer: User", false);
            break;
        default:
            oled_write_ln("Layer: Undefine", false);
    }
    oled_write_P((get_mods() & MOD_MASK_SHIFT) ? "SF>* " : "SF>x ", false);
    oled_write_P((get_mods() & MOD_MASK_CTRL) ? "CT>* " : "CT>x ", false);
    oled_write_P((get_mods() & MOD_MASK_ALT) ? "AL>* " : "AL>x ", false);
    oled_write_ln((get_mods() & MOD_MASK_GUI) ? "GU>*" : "GU>x", false);

#   else



#   endif
}
#endif


bool is_keyboard_left(void) {

#ifdef I_AM_LEFT
    return true;
#else
    return false;
#endif

}
