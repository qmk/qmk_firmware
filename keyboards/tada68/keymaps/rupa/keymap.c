#include "rupa.h"

#define LAYOUT_65_ansi_wrapper(...) LAYOUT_65_ansi(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_65_ansi_wrapper(
        ____65_QWERTY______________ROW1,
        ____65_QWERTY______________ROW2,
        ____65_QWERTY______________ROW3,
        ____65_QWERTY______________ROW4,
        ____65_QWERTY______________ROW5
    ),
    [_RAISE] = LAYOUT_65_ansi_wrapper(
        ____65_RAISE_______________ROW1,
        ____65_RAISE_______________ROW2,
        ____65_RAISE_______________ROW3,
        ____65_RAISE_______________ROW4,
        ____65_RAISE_______________ROW5
    ),
    [_LOWER] = LAYOUT_65_ansi_wrapper(
        ____65_LOWER_______________ROW1,
        ____65_LOWER_______________ROW2,
        ____65_LOWER_______________ROW3,
        ____65_LOWER_______________ROW4,
        ____65_LOWER_______________ROW5
    ),
    [_ADJUST] = LAYOUT_65_ansi_wrapper(
        ____65_ADJUST______________ROW1,
        ____65_ADJUST___________BL_ROW2,
        ____65_ADJUST______________ROW3,
        ____65_ADJUST______________ROW4,
        ____65_ADJUST______________ROW5
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
