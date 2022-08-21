#include QMK_KEYBOARD_H

// clang-format off
#define LAYOUT_ortho_6x5( \
	K00, K01, K02, K03, K04, K05, \
	K10, K11, K12, K13, K14, K15, \
	K20, K21, K22, K23, K24, K25,  \
	K30, K31, K32, K33, K34, K35,  \
	K40, K41, K42, K43, K44, K45  \
) { \
	{ K00,   K01,   K02,   K03,   K04,    K05 }, \
	{ K10,   K11,   K12,   K13,   K14,    K15  }, \
	{ K20,   K21,   K22 ,  K23,   K24,    K25  },  \
	{ K30,   K31,   K32 ,  K33,   K34,    K35  },  \
	{ K40,   K41,   K42 ,  K43,   K44,    K45  }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {LAYOUT_ortho_6x5(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,
    KC_A, KC_S, KC_D, KC_E, KC_F, KC_G,
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N,
    KC_H, KC_J, KC_K, KC_L, KC_U, KC_P

                                                                               )};

void pointing_device_init_kb(void) {
    pmw33xx_init(0);
    pmw33xx_set_cpi(0, 1000);
    pointing_device_init_user();
}

void keyboard_post_init_user(void) {
    // rgblight_enable_noeeprom();
    // rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
}

// #define TEST_CHAR_COUNT ('~' - '!' + 1)

// static char get_test_char(uint8_t char_index) {
//     return char_index + '!';
// }

// // Fill the whole screen with distinct characters (if the display is large enough to show more than 94 characters
// // at once, the sequence is repeated the second time with inverted characters).
// static void test_characters(void) {
//     uint8_t cols       = oled_max_chars();
//     uint8_t rows       = oled_max_lines();
//     bool    invert     = false;
//     uint8_t char_index = 0;
//     for (uint8_t row = 0; row < rows; ++row) {
//         for (uint8_t col = 0; col < cols; ++col) {
//             oled_write_char(get_test_char(char_index), invert);
//             if (++char_index >= TEST_CHAR_COUNT) {
//                 char_index = 0;
//                 invert     = !invert;
//             }
//         }
//     }
// }

// bool oled_task_user(void) {
//     test_characters();
//     return false;
// }
