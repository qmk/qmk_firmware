// This is a game-pad gherkin layout with RGB and LED lights

#include QMK_KEYBOARD_H

backlight_config_t backlight_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Game pad
 * ,-----------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  | Ctl | Alt |  ~  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | Tab |  Q  |  W  |  E  |  R  |  T  | |^| |  ;  |  '  |  /  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | Shf |  A  |  S  |  D  |  F  | <-- | |v| | --> |  ,  |  .  |
 * `-----------------------------------------------------------'
 */
    LAYOUT_ortho_3x10(
        KC_ESCAPE, KC_1, KC_2, KC_3, KC_4, KC_5,    KC_6,    KC_LCTRL, KC_LALT,  KC_GRAVE,
        KC_TAB,    KC_Q, KC_W, KC_E, KC_R, KC_T,    KC_UP,   KC_SCLN,  KC_QUOTE, KC_SLASH,
        KC_LSHIFT, KC_A, KC_S, KC_D, KC_F, KC_LEFT, KC_DOWN, KC_RIGHT, KC_COMMA, KC_DOT
    )
};

void matrix_init_user(void) {
    // Set LED's to max
    _delay_us(300);
    backlight_config.level = 2;
    backlight_config.enable = 1;
    eeconfig_update_backlight(backlight_config.raw);
    backlight_set(backlight_config.level);
    // Set RGB to rainbow mood light
    rgblight_enable();
    rgblight_mode(1);
    rgblight_sethsv(120,255,255);
    rgblight_mode(6);
}
