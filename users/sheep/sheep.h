
#include <stdbool.h>

enum encoder_modes {
    _PAGE = 0,
    _MOUSE = 1,
    _MUSIC = 2,
    _RGB = 3,
};

extern enum encoder_modes encoder_mode;
//extern bool new_content;
extern uint8_t base_val;
extern uint8_t base_sat;
extern uint8_t base_hue;
