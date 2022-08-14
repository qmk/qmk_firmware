#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {LAYOUT_ortho_1x1(KC_A)};

void pointing_device_init_kb(void) {
    pmw33xx_init(0);
    pmw33xx_set_cpi(0, 1000);
    pointing_device_init_user();
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_cyan();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}

#define TEST_CHAR_COUNT ('~' - '!' + 1)

static char get_test_char(uint8_t char_index) {
    return char_index + '!';
}

// Fill the whole screen with distinct characters (if the display is large enough to show more than 94 characters
// at once, the sequence is repeated the second time with inverted characters).
static void test_characters(void) {
    uint8_t cols       = oled_max_chars();
    uint8_t rows       = oled_max_lines();
    bool    invert     = false;
    uint8_t char_index = 0;
    for (uint8_t row = 0; row < rows; ++row) {
        for (uint8_t col = 0; col < cols; ++col) {
            oled_write_char(get_test_char(char_index), invert);
            if (++char_index >= TEST_CHAR_COUNT) {
                char_index = 0;
                invert     = !invert;
            }
        }
    }
}

bool oled_task_user(void) {
    test_characters();
    return false;
}
