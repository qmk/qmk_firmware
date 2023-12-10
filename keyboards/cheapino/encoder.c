#include "matrix.h"
#include "quantum.h"

#define COL_SHIFTER ((uint16_t)1)

#define ENC_ROW 3
#define ENC_A_COL 3
#define ENC_B_COL 5
#define ENC_BUTTON_COL 1

static bool colABpressed   = false;
static bool encoderPressed = false;

void clicked(void) {
    tap_code(KC_MPLY);
}

void turned(bool clockwise) {
    if (IS_LAYER_ON(6)) {
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } else if (IS_LAYER_ON(3)) {
        tap_code16(clockwise ? LCTL(KC_TAB) : LCTL(LSFT(KC_TAB)));
    } else if (IS_LAYER_ON(5)) {
        tap_code(clockwise ? KC_MS_WH_DOWN : KC_MS_WH_UP);
    } else {
        tap_code16(clockwise ? LGUI(KC_Y) : LGUI(KC_Z));
    }
}

// Dead code for now, not sure if there's edge cases that needed it
void blank_column(matrix_row_t current_matrix[], uint8_t col) {
    uint16_t column_index_bitmask = COL_SHIFTER << col;
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        current_matrix[row_index] &= ~column_index_bitmask;
    }
}

// Dead code for now, not sure if there's edge cases that needed it
bool is_entire_column_held(matrix_row_t current_matrix[], uint8_t col) {
    uint16_t column_index_bitmask = COL_SHIFTER << col;
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        if (!(current_matrix[row_index] & column_index_bitmask)) return false;
    }
    return true;
}

// Because of a bug in the routing of the cheapino, encoder action
// triggers entire columns... fix it in software here, assumption is that
// you never press an entire column, sounds safe?
void fix_encoder_action(matrix_row_t current_matrix[]) {
    matrix_row_t encoder_row = current_matrix[ENC_ROW];

    // 7th column means encoder was pressed
    if (encoder_row & (COL_SHIFTER << ENC_BUTTON_COL)) {
        encoderPressed = true;
        // blank_column(current_matrix, 7);
        current_matrix[3] |= COL_SHIFTER << 1;
    } else {
        current_matrix[3] &= ~COL_SHIFTER << 1;
        // Only trigger click on release
        if (encoderPressed) {
            encoderPressed = false;
            clicked();
        }
    }

    // Check if the pin is pressed, as from observation when encoder is spun
    // it doesn't result in all of the columns to turn on anymore
    bool colA = encoder_row & (COL_SHIFTER << ENC_A_COL);
    bool colB = encoder_row & (COL_SHIFTER << ENC_B_COL);

    if (colA && colB) {
        colABpressed = true;
    } else if (colA) {
        if (colABpressed) {
            colABpressed = false;
            turned(true);
        }
    } else if (colB) {
        if (colABpressed) {
            colABpressed = false;
            turned(false);
        }
    }
}
