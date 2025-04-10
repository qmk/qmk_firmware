#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,-----------------------,
 * |  7  |  8  |  9  |  /  |
 * |-----+-----+-----+-----|
 * |  4  |  5  |  6  |  *  |
 * |-----+-----+-----+-----|
 * |  1  |  2  |  3  |  -  |
 * |-----+-----+-----+-----|
 * |  0  |  .  |  =  |  +  |
 * `-----------------------'
 */
LAYOUT_ortho_4x4(
		KC_P7, KC_P8,   KC_P9,      KC_PSLS,
		KC_P4, KC_P5,   KC_P6,      KC_PAST,
		KC_P1, KC_P2,   KC_P3,      KC_PMNS,
		KC_P0, KC_PDOT, KC_PEQL,    KC_PPLS
)

};


// Set led state during power-up
// There is also a LED_GREEN
// Only for Rev1 & Rev2
#ifdef LED_RED
void keyboard_post_init_user(void) {
    gpio_write_pin_high(LED_RED);
}
#endif


// Rev3 and above only
#ifdef OLED_ENABLE
bool oled_task_user(void) {
  oled_write_ln_P(PSTR("Plaid-Pad ///////////"), false);
    return false;
}
#endif


#ifdef ENCODER_MAP_ENABLE

/*
Rev1.1                      Rev1
,-----------------------,   ,-----------------------,
|  E1 |  E2 |  E3 |  E4 |   |  E1 |     |     |  E2 |
|-----+-----+-----+-----|   |-----+-----+-----+-----|
|     |     |     |  E3 |   |     |     |     |     |
|-----+-----+-----+-----|   |-----+-----+-----+-----|
|     |     |     |  E2 |   |     |     |     |     |
|-----+-----+-----+-----|   |-----+-----+-----+-----|
|     |     |     |  E1 |   |     |     |     |     |
`-----------------------'   `-----------------------'
 */
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
#ifdef KEYBOARD_keycapsss_plaid_pad_rev1
  { ENCODER_CCW_CW(KC_F18, KC_F17), ENCODER_CCW_CW(KC_F20, KC_F19) }
#else
  { ENCODER_CCW_CW(KC_F18, KC_F17), ENCODER_CCW_CW(KC_F20, KC_F19), ENCODER_CCW_CW(KC_F22, KC_F21), ENCODER_CCW_CW(KC_F24, KC_F23) }
#endif
};

#endif
