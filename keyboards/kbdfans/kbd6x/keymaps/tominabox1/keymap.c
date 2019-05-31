#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Colemak
     * ,-----------------------------------------------------------------------------------.
     * | Q    |   W  |   F  |   P  |   G  |  ESC |   DEL|   J  |   L  |   U  |   Y  | :    |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | A    |   R  |   S  |   T  |   D  |  TAB |RETURN|   H  |   N  |   E  | I    |  O   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Z    |   X  |   C  |   V  |   B  |   [  |   ]  |   K  |   M  |   ,  |   .  |   '  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | CTRL | CAD  | GUI  | BSPC | LALT | TG3  | MO3  | SHIFT| SPACE|RETURN| BSLS | UP   |
     * `-----------------------------------------------------------------------------------'
     */

    [0] = LAYOUT_ortho_4x12(
        KC_Q, KC_W, KC_F, KC_P, KC_G, KC_GESC, KC_DEL,  KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, \
        KC_A, KC_R, KC_S, KC_T, KC_D, KC_TAB,  KC_ENT,  KC_H, KC_N, KC_E,    KC_I,   KC_O, \
        LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_K, KC_M, KC_COMM, KC_DOT, KC_QUOT, \
        KC_LCTL, LCA(KC_DEL), KC_LGUI, LT(1,KC_BSPC), KC_LALT, TG(3), MO(2), KC_LSFT, KC_SPC, KC_ENT, KC_BSLS, KC_UP),

    /* Numrow
     * ,-----------------------------------------------------------------------------------.
     * | 1    |   2  |   3  |   4  |   5  |  ESC |   DEL|   6  |   7  |   8  |   9  | 0    |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | F1   |  F2  |   F3 |   F4 |   F5 |  TAB |RETURN|      |      |      | BSLS |   /  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |  F6  | F7   | F8   | F9   |  F10 |  -   |   =  |      |      |PGUP  |  UP  | PGDN |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |BSPC  |  ALT | TG3  |      | SHIFT| SPACE| LEFT |  DWN |RIGHT |
     * `-----------------------------------------------------------------------------------'
     */

	[1] = LAYOUT_ortho_4x12(
        KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_TRNS, KC_TRNS, KC_6, KC_7, KC_8, KC_9, KC_0, \
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_CAPS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_SLSH, \
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_MINS, KC_EQL, KC_NO, KC_NO, KC_PGDN, KC_UP, KC_PGUP, \
        KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Media
    * ,-----------------------------------------------------------------------------------.
    * | NEXT |  Play|      |      |      |  ESC |   DEL|      |      |      |      |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |      |      |      |  TAB |RETURN|      |      |      |      |      |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      |      |      |      |      |   -  |   =  |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      | Alt  | BSPC | GUI  | TG3  |      | SHIFT| SPACE| LEFT |  DWN |RIGHT |
    * `-----------------------------------------------------------------------------------'
    */

    [2] = LAYOUT_ortho_4x12(
        KC_MNXT,  KC_MPLY,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
        KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Numpad
     * ,-----------------------------------------------------------------------------------.
     * | NEXT |  Play|   3  |   4  |   5  |  ESC |   DEL|   /  |   *  |   P7 |   P8 | P9   |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |  TAB |RETURN|      |   -  |  P4  |  P5  |  P6  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |   -  |   =  |      |    + |P1    |  P2  |  P3  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |  ALT | BSPC | GUI  | TG3  |      | SHIFT| SPACE| P0   | PDOT | PENT |
     * `-----------------------------------------------------------------------------------'
     */

    [3] = LAYOUT_ortho_4x12(
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS, KC_TRNS, KC_PSLS, KC_PAST, KC_P7, KC_P8, KC_P9, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_PMNS, KC_P4, KC_P5, KC_P6, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_NO, KC_PPLS, KC_P1, KC_P2, KC_P3, \
        KC_NO, KC_NO, KC_TRNS, KC_BSPC, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_DOT, KC_PENT)
};

uint32_t last_state = UINT32_MAX; // Initialize to max so it resets next_tick & current_index on startup
uint32_t next_tick = 0;
uint8_t current_index = 0;

// Change these if it is too fast or too slow
#define TIME_ON 20
#define TIME_OFF 20
#define TIME_HOLD 200

uint8_t layer0_table[] = { TIME_ON };
uint8_t layer1_table[] = { TIME_ON, TIME_OFF, TIME_HOLD, TIME_OFF };
uint8_t layer2_table[] = { TIME_ON, TIME_OFF, TIME_ON, TIME_OFF, TIME_HOLD, TIME_OFF };
uint8_t layer3_table[] = { TIME_ON, TIME_OFF, TIME_ON, TIME_OFF, TIME_ON, TIME_OFF, TIME_HOLD, TIME_OFF };

void update_led_pattern(uint8_t table[], uint8_t size)
{
    uint32_t time = timer_read32();
    if (next_tick < time) {
        current_index++;
        if (current_index >= size)
            current_index = 0;
        next_tick = time + table[current_index];
    }

    bool led_off = current_index % 2;
    if (led_off)
        writePinLow(C4);
    else
        writePinHigh(C4);
}

void my_user_task(void){
    // Do CAPS LOCK status
    uint8_t usb_led = host_keyboard_leds();
    if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)){
        writePinHigh(C5);
    } else {
        writePinLow(C5);
    }

    // If we changed layers, reset tracking data
    if (last_state != layer_state) {
        last_state = layer_state;
        current_index = 0;
        next_tick = timer_read32();
    }

    switch (biton32(layer_state)) {
        case 0:
            update_led_pattern(layer0_table, sizeof(layer0_table));
            break;
        case 1:
            update_led_pattern(layer1_table, sizeof(layer1_table));
            break;
        case 2:
            update_led_pattern(layer2_table, sizeof(layer2_table));
            break;
        case 3:
            update_led_pattern(layer3_table, sizeof(layer3_table));
            break;
    }
};
