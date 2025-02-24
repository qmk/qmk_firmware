#include "matrix.h"
#include "quantum.h"
#include "print.h"

#define COL_SHIFTER ((uint16_t)1)

#define ENC_ROW 5         // GP29
#define ENC_A_COL 10      // GP28
#define ENC_B_COL 9       // GP27
#define ENC_BTN_COL 8     // GP26

static bool colABPressed   = false;
static bool encoderPressed = false;

void clicked(void) {
    tap_code(KC_LEFT_SHIFT);
}

void turned(bool clockwise) {
    tap_code16(clockwise ? KC_PAGE_DOWN : KC_PAGE_UP);
    tap_code(clockwise ? KC_PAGE_DOWN : KC_PAGE_UP);

    //if (IS_LAYER_ON(6)) {
    //    tap_code(clockwise ? KC_AUDIO_VOL_UP : KC_AUDIO_VOL_DOWN);
    //} else if (IS_LAYER_ON(3)) {
    //    tap_code16(clockwise ? LCTL(KC_TAB) : LCTL(LSFT(KC_TAB)));
    //} else if (IS_LAYER_ON(5)) {
    //    tap_code16(clockwise ? LGUI(KC_Y) : LGUI(KC_Z));
    //} else {
    //    tap_code16(clockwise ? KC_PAGE_DOWN : KC_PAGE_UP);
    //}
}

void binuprintf(char* msg, int v) {
    unsigned int mask = 1 << ((sizeof(int) << 3) - 1);
    uprintf("%-20s", msg);

    while (mask) {
        uprintf("%d", (v & mask ? 1 : 0));
        mask >>= 1;
    }

    uprintf("\n");
}

void fix_encoder_action(matrix_row_t current_matrix[]) {
    matrix_row_t encoder_row = current_matrix[ENC_ROW];

    //binuprintf("encoder row", encoder_row);
    //binuprintf("encoder shift", (COL_SHIFTER << ENC_BTN_COL));

    if (encoder_row) {
        binuprintf("encoder row", encoder_row);
        //binuprintf("colA shift", (COL_SHIFTER << ENC_A_COL));
        //binuprintf("colB shift", (COL_SHIFTER << ENC_B_COL));
    }

    if (encoder_row & (COL_SHIFTER << ENC_BTN_COL)) {
        encoderPressed = true;
    } else {
        // Only trigger click on release
        if (encoderPressed) {
            encoderPressed = false;
            clicked();
        }
    }

    // Check which way the encoder is turned:
    bool colA = encoder_row & (COL_SHIFTER << ENC_A_COL);
    bool colB = encoder_row & (COL_SHIFTER << ENC_B_COL);

    if (colA && colB) {
        colABPressed = true;
    } else if (colA) {
        if (colABPressed) {
            // A+B followed by A means clockwise
            colABPressed = false;
            turned(true);
        }
    } else if (colB) {
        if (colABPressed) {
            // A+B followed by B means counter-clockwise
            colABPressed = false;
            turned(false);
        }
    }

    current_matrix[ENC_ROW] = 0;
}