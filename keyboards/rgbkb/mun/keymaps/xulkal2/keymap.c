/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H
#include "common_oled.h"

enum keymap_layers {
    _QWERTY,
    _FUNCTION,
    _ADJUST
};

enum keymap_keycodes {
    // Disables touch processing
    TCH_TOG = SAFE_RANGE,
    MENU_BTN,
    MENU_UP,
    MENU_DN,
    RGB_RST
};

// Default Layers
#define QWERTY   DF(_QWERTY)

// Momentary Layers
#define FN       OSL(_FUNCTION)
#define ADJ      OSL(_ADJUST)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
     * .--------------------------------------------------------------.  .--------------------------------------------------------------.
     * | `~/ESC | 1      | 2      | 3      | 4      | 5      |        |  |        | 6      | 7      | 8      | 9      | 0      | Bckspc |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | Tab    | Q      | W      | E      | R      | T      |        |  |        | Y      | U      | I      | O      | P      | \      |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | Caps   | A      | S      | D      | F      | G      | Play   |  | MN BTN | H      | J      | K      | L      | :      | Enter  |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | Shft[  | Z      | X      | C      | V      | B      | {      |  | }      | N      | M      | ,      | .      | /      | Shft]  |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | Ctrl-  | Win    | Alt    | Del    | Space  |        | ADJ    |  | FN     |        | Space  | '"     | Alt    | App    | Ctrl=  |
     * '--------+--------+--------+--------|--------+--------+--------'  '--------+--------+--------+--------+--------+--------+--------'
     *      Encoder 1         Encoder 2                                                                  Encoder 3         Encoder 4
     * .-----------------------------------.                                                        .-----------------------------------.
     * | VolUp  | VolDn  | VolUp  | VolDn  |                                                        | PgUp   | PgDn   | PgUp   | PgDn   |
     * |--------+--------+--------+--------+--------.                                      .--------+--------+--------+--------+--------|
     * | VolDn  | VolUp  | Next   | Play   | Prev   | Touch Encoder          Touch Encoder | RgbHuI | RgbHuD | RgbMdD | RgbTog | RgbMdI |
     * '--------+--------+--------+--------+--------'                                      '--------+--------+--------+--------+--------'
     */
    [_QWERTY] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,      KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,      KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MPLY,    MENU_BTN,KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCBR,    KC_RCBR, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
        KC_LCPO, KC_LGUI, KC_LALT, KC_DEL,  KC_SPC,  KC_NO,   ADJ,        FN,      KC_NO,   KC_SPC,  KC_QUOTE,KC_RALT, KC_APP,  KC_RCPC,

        KC_VOLU, KC_VOLD, KC_VOLU, KC_VOLD,                                                          MENU_DN, MENU_UP, MENU_DN, MENU_UP,
        KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_MPRV,                                        RGB_HUI, RGB_HUD, RGB_RMOD,RGB_TOG, RGB_MOD
    ),

    /* Function
     * .--------------------------------------------------------------.  .--------------------------------------------------------------.
     * | F12    | F1     | F2     | F3     | F4     | F5     |        |  |        | F6     | F7     | F8     | F9     | F10    | F11    |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |        | SPDI   | SAI    | VAI    | HUI    | RGBMD  |        |  |        |        |        | PrtScr | ScrLck | PseBrk |        |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |        | SPDD   | SAD    | VAD    | HUD    | RGBRMD |        |  |        |        |        | Ins    | Home   | PgUp   |        |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |        | RGBRST |        |        |        | RGBTOG |        |  |        |        |        | Del    | End    | PgDn   |        |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |  |        |        | Play   | Prev   | Next   | VolUp  | VolDn  |
     * '--------+--------+--------+--------+--------+--------+--------'  '--------+--------+--------+--------+--------+--------+--------'
     *      Encoder 1         Encoder 2                                                                  Encoder 3         Encoder 4
     * .-----------------------------------.                                                        .-----------------------------------.
     * |        |        |        |        |                                                        |        |        |        |        |
     * |--------+--------+--------+--------+--------.                                      .--------+--------+--------+--------+--------|
     * |        |        |        |        |        | Touch Encoder          Touch Encoder |        |        |        |        |        |
     * '--------+--------+--------+--------+--------'                                      '--------+--------+--------+--------+--------'
     */
    [_FUNCTION] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, RGB_SPI, RGB_SAI, RGB_VAI, RGB_HUI, RGB_MOD, _______,    _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
        _______, RGB_SPD, RGB_SAD, RGB_VAD, RGB_HUD, RGB_RMOD,_______,    _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______,
        _______, RGB_RST, _______, _______, _______, RGB_TOG, _______,    _______, _______, _______, KC_DEL,  KC_END,  KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLU, KC_VOLD,

        _______, _______, _______, _______,                                                          _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______
    ),

    /* Adjust
     * .--------------------------------------------------------------.  .--------------------------------------------------------------.
     * |        |        |        |        |        |        |        |  |        |        | NumLck | /      | *      | -      | Del    |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |        | Home   | Up     | End    | Reset  | T_TOG  |        |  |        |        | 7      | 8      | 9      | +      |        |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |        | Left   | Down   | Right  |        |        |        |  |        |        | 4      | 5      | 6      | +      |        |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        | EepRst |        |  |        |        | 1      | 2      | 3      | Enter  |        |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |  |        |        |        | 0      | .      | Enter  |        |
     * '--------+--------+--------+--------+--------+--------+--------'  '--------+--------+--------+--------+--------+--------+--------'
     *      Encoder 1         Encoder 2                                                                  Encoder 3         Encoder 4
     * .-----------------------------------.                                                        .-----------------------------------.
     * |        |        |        |        |                                                        |        |        |        |        |
     * |--------+--------+--------+--------+--------.                                      .--------+--------+--------+--------+--------|
     * |        |        |        |        |        | Touch Encoder          Touch Encoder |        |        |        |        |        |
     * '--------+--------+--------+--------+--------'                                      '--------+--------+--------+--------+--------'
     */
    [_ADJUST] = LAYOUT(
        KC_GRV,  _______, _______, _______, _______, _______, _______,    _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_DEL,
        _______, KC_HOME, KC_UP,   KC_END,  RESET,   TCH_TOG, _______,    _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______, _______,    _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
        _______, _______, _______, _______, _______, EEP_RST, _______,    _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, KC_KP_0, KC_PDOT, KC_PENT, _______,
        
        _______, _______, _______, _______,                                                          _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______
    )
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode)
    {
        case MENU_BTN:
            if (record->event.pressed) {
                rgb_menu_selection();
            }
            return false;
        case MENU_UP:
            if (record->event.pressed) {
                rgb_menu_action(true);
            }
            return false;
        case MENU_DN:
            if (record->event.pressed) {
                rgb_menu_action(false);
            }
            return false;
        case RGB_RST:
            if (record->event.pressed) {
                eeconfig_update_rgb_matrix_default();
            }
            return false;
        case TCH_TOG:
            if (record->event.pressed) {
                touch_encoder_toggle();
            }
            return false;  // Skip all further processing of this key
        default:
            return true;
    }
}

static void render_layer(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("BASE "), false);
            break;
        case _FUNCTION:
            oled_write_ln_P(PSTR("FUNC "), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("ADJS "), false);
            break;
    }
}

static void render_leds(void)
{
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUMLK")     : PSTR("     "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPLK")    : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCRLK")  : PSTR("     "), false);
}

static void render_touch(void)
{
    // Host Touch LED Status
    oled_write_P(!touch_encoder_toggled() ? PSTR("TOUCH")  : PSTR("     "), false);
    oled_write_P(touch_encoder_calibrating() ? PSTR("CLBRT")  : PSTR("     "), false);
}

/*static uint32_t scan_counter = 0;
static uint32_t scan_value = 0;
static uint16_t scan_timer = 1000;

void do_counters(void) {
    scan_counter++;
    uint16_t now = sync_timer_read();
    if (timer_expired(now, scan_timer))
    {
        scan_timer += 1000;
        scan_value = (scan_value + scan_counter) / 2;
        scan_counter = 0;
    }
}

void matrix_scan_user(void) {
    do_counters();
}

void matrix_slave_scan_user(void) {
    do_counters();
}

void render_debug_scan(void) {
    static char buffer[6] = {0};
    snprintf(buffer, sizeof(buffer), "%5d", scan_value);
    oled_write_ln_P(buffer, false);
}*/

void oled_task_user(void) {
    if (is_keyboard_left()) {
        render_layer();
        oled_write_P(PSTR("     "), false);
        render_leds();
        oled_write_P(PSTR("     "), false);
        render_touch();
        //oled_write_P(PSTR("     "), false);
        //render_debug_scan();
        oled_set_cursor(0, 12);
        render_icon();
    }
    else {
        render_rgb_menu();
        //oled_write_P(PSTR("     "), false);
        //render_debug_scan();
        oled_set_cursor(0, 12);
        render_icon();
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}