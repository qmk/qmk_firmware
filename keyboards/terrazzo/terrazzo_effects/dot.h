#ifndef DISABLE_TERRAZZO_EFFECT_DOT
TERRAZZO_EFFECT(DOT)
#   ifdef TERRAZZO_EFFECT_IMPLS
// Animation for debugging. Ligths one pixel according to animation index
void DOT(uint8_t i, bool dir) {
    led_matrix_set_index_value_all(0);
    led_matrix_set_index_value(i, 10);
}

#   endif
#endif