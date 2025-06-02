#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
/*
#define _QWERTY 0
#define _FN     1
#define _NUMPAD 2
#define _SHIFT  3
*/

//Pointing Device Scrolling
enum custom_keycodes {
    DRAG_SCROLL = QK_USER_0,
    CPI_UP = QK_USER_1,
    CPI_DN = QK_USER_2,
};

bool set_scrolling = false;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        // left hand
        KC_EQL,    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   TG(2),
        KC_ESC,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_CUT,
        KC_TAB,    KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_CALC,
        KC_CAPS,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
        TG(3),     KC_GRV,  KC_LEFT, KC_RGHT,KC_LALT,
                                    KC_LCTL, KC_HOME,
                                    KC_END,
                                    KC_DEL, KC_BSPC, KC_LSFT,
                                    KC_MUTE,
        // right hand
                          KC_CALC, KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_MINS,
                          KC_COPY, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
                          KC_PSTE, KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  MO(2),
                                            KC_ESC,  KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
             KC_RSFT, KC_SPC, KC_ENT,
             KC_LGUI, MS_BTN3, DRAG_SCROLL, MS_BTN2, MS_BTN1

    ),

    [1] = LAYOUT(
        // left hand
        KC_F1,     KC_F2,     KC_F3,      KC_F4,    KC_F5,     KC_F6,    _______,
        _______,   _______,   _______,    KC_UP,    _______,   _______,  _______,
        _______,   _______,   KC_LEFT,    KC_DOWN,  KC_RGHT,   _______,  QK_BOOT,
        _______,   _______,   _______,   _______,   _______,   _______,
        TO(0),     _______,   KC_MPRV,   KC_MNXT,   _______,
                                    _______, _______,
                                    _______,
                                    _______, _______, _______,
                                    _______,
        // right hand
                          CPI_UP,    KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,
                          CPI_DN,    _______,   _______,   _______,   _______,   _______,   _______,
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                     _______,   _______,   _______,   _______,   _______,   _______,
                                                _______,   _______,   _______,   _______,   _______,
             _______, _______, _______,

             _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT(
        // left hand
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,
                                    _______, _______,
                                    _______,
                                    _______, _______, _______,
                                    _______,
        // right hand
                          _______,   _______,   KC_NUM,    KC_PSLS,   KC_PAST,   KC_PMNS,   _______,
                          _______,   _______,   KC_P7,     KC_P8,     KC_P9,     KC_PPLS,   RGB_MOD,
                          _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PPLS,   RGB_RMOD,
                                     _______,   KC_P1,     KC_P2,     KC_P3,     KC_PENT,   MO(2),
                                                KC_P0,     KC_P0,     KC_PDOT,   KC_PENT,   RGB_TOG,
             _______, KC_P0,   KC_PENT,
             _______, _______, _______, _______, _______
    ),

        [3] = LAYOUT(
        // left hand
        TO(0),_______,   _______,   _______,   _______,   _______,  _______,
        _______,    _______,   _______,   _______,   _______,   _______,  _______,
        _______,    _______,   _______,   _______,   _______,   _______,  _______,
        _______,    _______,   _______,   _______,   _______,   _______,
        _______,    _______,   _______,   _______,   _______,
                                    _______, _______,
                                    _______,
                                    _______, _______, _______,
                                    _______,
        // right hand
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                     _______,   _______,   _______,   _______,   _______,   _______,
                                                _______,   _______,   _______,   _______,   _______,

             _______, _______, _______,
             _______, _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [2] = { ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [3] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT)}
};

#endif

/*
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(_QWERTY, _RAISE, _LOWER, _ADJUST);
}
*/

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
const char *read_rgb_info(void);

const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

bool oled_task_user() {
    //rgblight_get_mode(led_state_reader(), false);
    led_t led_state = host_keyboard_led_state();
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(led_state.caps_lock ? PSTR("Caps Lock On") : PSTR("Caps Lock Off"), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);

    // Host Keyboard LED Status
    //led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(read_rgb_info(), false);
    //rgblight_get_mode(led_state_reader(), false);

    return false;
    }

#endif // OLED_ENABLE



// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 40.0
#define SCROLL_DIVISOR_V 40.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = -(int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    //set_timelog();
  }

    switch (keycode) {
        case DRAG_SCROLL:
            // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
            set_scrolling = record->event.pressed;
            break;
        default:
            break;
        case CPI_UP:
          if (record->event.pressed) {
              pointing_device_set_cpi(POINTING_DEVICE_CPI_INCREMENT); // Increase CPI
          }
          return false;
        case CPI_DN:
          if (record->event.pressed) {
              pointing_device_set_cpi(-POINTING_DEVICE_CPI_INCREMENT); // Decrease CPI
          }
          return false;
    }
    return true;
}
