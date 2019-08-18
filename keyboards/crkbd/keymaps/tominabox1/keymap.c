#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif


void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type);

#ifdef RGB_MATRIX_ENABLE

static bool is_suspended;
static bool rgb_matrix_enabled;

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
    if (!is_suspended) {
        is_suspended = true;
        rgb_matrix_enabled = (bool)rgb_matrix_config.enable;
        rgb_matrix_disable_noeeprom();
    }
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
    is_suspended = false;
    if (rgb_matrix_enabled) {
        rgb_matrix_enable_noeeprom();
    }
}

#    include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    switch (mode) {
        case 1:  // breathing
        {
            uint16_t time = scale16by8(g_rgb_counters.tick, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}
#endif


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _ARROW 4

enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  ARROW
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_ARROW MO(4)
//#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)

#define KC_SFT_CPS TD(TD_SFT_CPS)
// Left space on tap, LOWER on hold
#define KC_SPC_LOW LT(_LOWER, KC_ENT)
// Left space on tap, UPPER on hold
#define KC_SPC_RSE LT(_RAISE, KC_SPC)

#define KC_EML TD(KC_EMAIL)


enum {
    KC_EMAIL = 0,
    TD_SFT_CPS,
};

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_RSFT);
        register_code (KC_2);
    } else {
        SEND_STRING("tom.campie@gmail.com");
    }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_RSFT);
        unregister_code (KC_2);
    } else {
    }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [KC_EMAIL] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset),
    [TD_SFT_CPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};

uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case KC_SFT_CPS:
            return 100;
//        case CTL_T(KC_TAB):
//            return 100;
        case KC_SPC_RSE:
            return 300;
//        case TD(KC_EMAIL):
//            return 50;
        default:
            return TAPPING_TERM;
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GESC,     Q,     W,     F,     P,     G,                      J,     L,     U,     Y, SCLN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     R,     S,     T,     D,                      H,     N,     E,     I,     O,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    SFT_CPS,     Z,     X,     C,     V,     B,                      K,     M,  COMM,   DOT, SLSH,  SLSH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LALT,   SPC_LOW,      SPC_RSE, ARROW, ENT \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,    F1,    F2,    F3,    F4,    F5,                     F6,    MINS,    EQL,    LBRC,   RBRC, BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       SFT_CPS,   F7,   F8,   F9,   F10,   F11,                    F12,   NO,   NO,   DOT,   NO, SLSH,\
  //|------+--- ---+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LALT,   SPC_LOW,      SPC_RSE, ARROW, ENT \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  EXLM,    EML,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   XXXXX,   UNDS,  PLUS,  LCBR,  RCBR,   PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       SFT_CPS, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   XXXXX,  PLUS,  NO,  DOT,  NO, SLSH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LALT,   SPC_LOW,      SPC_RSE, ARROW, ENT \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LALT,   SPC_LOW,      SPC_RSE, XXXXX, ENT \
                              //`--------------------'  `--------------------'
  ),
  [_ARROW] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
  XXXXX,  XXXXX, UP, XXXXX, XXXXX, XXXXX,                    XXXXX, PGDN, UP, PGUP, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  XXXXX,  LEFT,  DOWN,  RIGHT, XXXXX, XXXXX,                  XXXXX, LEFT, DOWN, RGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  XXXXX,  XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LALT,   SPC_LOW,      SPC_RSE, ARROW, ENT \
                            //`--------------------'  `--------------------'
                          )
};

int RGB_current_mode;

uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    switch (biton32(state)) {
        case _LOWER:
            break;
        case _RAISE:
            break;
        case _ADJUST:
            break;

    }
    return state;
}
void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
#ifdef OLED_DRIVER_ENABLE
    oled_init(0);   // turns on the display
#endif
}

#ifdef OLED_DRIVER_ENABLE

//oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_0; }
uint16_t        oled_timer;

void matrix_scan_user(void) {
    oled_task();
}

void render_logo(void) {
    static const char PROGMEM logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(logo, false);
}

void render_status_main(void) {
    // Host Keyboard USB Status
    oled_write_P(PSTR("USB: "), false);
    switch (USB_DeviceState) {
        case DEVICE_STATE_Unattached:
            oled_write_P(PSTR("Unattached\n"), false);
            break;
        case DEVICE_STATE_Suspended:
             oled_write_P(PSTR("Suspended\n"), false);
            break;
        case DEVICE_STATE_Configured:
             oled_write_P(PSTR("Connected\n"), false);
            break;
        case DEVICE_STATE_Powered:
             oled_write_P(PSTR("Powered\n"), false);
            break;
        case DEVICE_STATE_Default:
             oled_write_P(PSTR("Default\n"), false);
            break;
        case DEVICE_STATE_Addressed:
             oled_write_P(PSTR("Addressed\n"), false);
            break;
        default:
             oled_write_P(PSTR("Invalid\n"), false);
        }
    
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (biton32(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Colemak\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        case _ARROW:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    
    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_ln_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("Caps Lock\n") : PSTR("         \n"), false);

}
    
void oled_task_user(void) {
    if (timer_elapsed(oled_timer) > 10000) {
        oled_off();
        return;
    }
        if (is_master) {
            render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        } else {
            render_logo();
        }
    }

#endif // OLED_Driver

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // add_keylog(keycode); // keep if using OLED key logger
        oled_timer = timer_read();
    }
    switch (keycode) {
        case RGBRST:
            #ifdef RGB_MATRIX_ENABLE
                if (record->event.pressed) {
                    eeconfig_update_rgb_matrix_default();
                    rgb_matrix_enable();
                    RGB_current_mode = rgb_matrix_config.mode;
                    }
            
            #endif
        break;
    }
return true;
    
}
