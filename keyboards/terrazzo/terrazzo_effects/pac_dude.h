#ifndef DISABLE_TERRAZZO_EFFECT_PAC_DUDE
TERRAZZO_EFFECT(PAC_DUDE)
#   ifdef TERRAZZO_EFFECT_IMPLS

static uint8_t pac_frames[3][25] = {
{ // up
    0, 0, 0, 0, 0,
    9, 0, 0, 0, 9,
    9, 9, 0, 9, 9,
    9, 9, 9, 9, 9,
    0, 9, 9, 9, 0
},
{ // closed
    0, 9, 9, 9, 0,
    9, 9, 9, 9, 9,
    9, 9, 9, 9, 9,
    9, 9, 9, 9, 9,
    0, 9, 9, 9, 0
},
{ // down
    0, 9, 9, 9, 0,
    9, 9, 9, 9, 9,
    9, 9, 0, 9, 9,
    9, 0, 0, 0, 9,
    0, 0, 0, 0, 0
}
};

static uint8_t pac_ghost[20] = {
    0, 4, 4, 4, 0,
    4, 0, 4, 0, 4,
    4, 4, 4, 4, 4,
    4, 0, 4, 0, 4
};


void PAC_DUDE(uint8_t i, bool dir) {
    led_matrix_set_index_value_all(0);
    if (dir) {
        terrazzo_draw_at(1, 4, 5, 5, pac_frames[i % 2]);
        terrazzo_set_pixel(3, 0 + i % 3, 5);
        terrazzo_set_pixel(3, 3 + i % 3, 5);
    } else {
        terrazzo_draw_at(1, 4, 5, 5, pac_frames[1 + i % 2]);
        terrazzo_draw_at(1, 8 + i % 8, 5, 4, pac_ghost);
    }
    
}

#   endif
#endif