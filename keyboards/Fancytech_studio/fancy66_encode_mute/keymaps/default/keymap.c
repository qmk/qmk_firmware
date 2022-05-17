#include "kb.h"
#include "ws2812.h"

typedef union {
  uint32_t raw;
  struct {
    bool top_rgb_change :1;
    bool bottom_rgb_change :1;
    bool mute :1;
  };
} user_config_t;

user_config_t user_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = KEYMAP(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
		KC_LCTL, KC_LALT, KC_SPC, MO(1), KC_SPC, KC_RALT, KC_VOLU, KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT),

	[1] = KEYMAP(
		KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, RESET, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SAI, RGB_SAD, RGB_TOG, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUI, RGB_HUD, USER00, KC_PSCR,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, USER01, RGB_VAI,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD, KC_TRNS),

	[2] = KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[3] = KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13, NO_LED,     14},
    { 15,     16,     17,     18,     19,     20, NO_LED,     21,     22,     23,     24,     25,     26,     27,     28,     29},
    { 30,     31,     32,     33,     34,     35, NO_LED,     36,     37,     38,     39,     40,     41,     42, NO_LED,     43},
    { 44,     45,     46,     47,     48,     49, NO_LED,     50,     51,     52,     53,     54,     55, NO_LED,     56, NO_LED},
    { 57, NO_LED,     58,     59, NO_LED, NO_LED,     60,     61, NO_LED, NO_LED,     62, NO_LED, NO_LED,     63,     64,     65}
}, {
    //Underglow (0 -> 15)
    {207, 41},{207, 28},{207, 14},{175, 11},{140, 4},{105, 9},{72, 4},{42, 6},{3, 7},{3, 33},{3, 44},{38, 50},{78, 52},{105, 57},{136, 56},{177, 50},

    // LED 对应到物理位置，可以参考下面这个公式
    // x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION           14*?
    // y = 64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION            16*?

    //Key matrix (16 -> 82)
    {195,  10}, {185,  10}, {171,   9}, {161,  12}, {149,  14}, {138,  16}, {126,  18}, {108,  18}, { 97,  16}, { 86,  14}, { 73,  12}, { 63,   9}, { 51,  10}, { 32,  10},                   { 12,   7},
    {195,  20}, {180,  20}, {169,  20}, {157,  22}, {146,  26}, {134,  28},                 {112,  30}, {100,  28}, { 90,  26}, { 77,  22}, { 66,  20}, { 54,  20}, { 42,  20}, { 28,  20}, {  8,  18},
    {197,  31}, {180,  31}, {168,  32}, {157,  34}, {146,  36}, {135,  37},                 {106,  38}, { 95,  37}, { 84,  35}, { 72,  32}, { 58,  30}, { 45,  30}, { 28,  30},                 {  6,  28},
    {197,  41}, {177,  41}, {163,  43}, {154,  45}, {143,  47}, {130,  49},                 {101,  49}, { 90,  46}, { 78,  44}, { 67,  42}, { 52,  41}, { 36,  41},                  { 17,  44},
    {201,  50},                  {168,  52}, {146,  56},                                  {128,  60}, { 91,  57},                             { 67,  52},                                     { 29,  54}, { 17,  54}, {  6,  54}
}, {
    //Underglow (0 -> 15)
    0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,

    //Key matrix (16 -> 82)
	0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,
	0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,
	0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,
	0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,
	0xFF,                 0xFF,      0xFF,                            0xFF,      0xFF,                            0xFF,                            0xFF,      0xFF,      0xFF
}

};

#endif


void keyboard_post_init_user(void) {
  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case USER00:
      if (record->event.pressed) {
        // Do something when pressed
        user_config.top_rgb_change ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case USER01:
      if (record->event.pressed) {
        // Do something when pressed
        user_config.bottom_rgb_change ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (user_config.top_rgb_change)
    {
        for (size_t i = 0; i < 66; i++)
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        }
    }

/*     if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(52, 0, 255, 255); // assuming caps lock is at led #5
    } */

    if (user_config.bottom_rgb_change)
    {
        for (size_t i = 66; i < 82; i++)
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        }
    }
}

// 编码器回调函数（官网）
/* bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { //First encoder
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { //Second encoder
        if (clockwise) {
            tap_code_delay(KC_MUTE, 10);
        } else {

        }
    }
    return false;
} */

// 旋钮支持VIA
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { //First encoder
        if (clockwise) {
            tap_code(dynamic_keymap_get_keycode(biton32(layer_state), 4, 11));
        } else {
            tap_code(dynamic_keymap_get_keycode(biton32(layer_state), 4, 12));
        }
    }
    return false;
}


// 大小写锁定灯
void rgb_matrix_indicators_kb(void){
    if (host_keyboard_led_state().caps_lock){
        rgb_matrix_set_color(43, 255, 255, 255);
    }
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
} */

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
