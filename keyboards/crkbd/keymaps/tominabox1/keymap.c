#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type);

#ifdef RGB_MATRIX_ENABLE

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

#define QMK_ESC_OUTPUT F4 // usually COL
#define QMK_ESC_INPUT D4 // usually ROW
#define QMK_LED B0

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
       SFT_CPS,   F7,   F8,   F9,   F10,   F11,                    F12,   NO,   NO,   NO,   NO, SLSH,\
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
       SFT_CPS, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   XXXXX,  PLUS,  LEFT,  DOWN,  UP, RGHT,\
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
            //rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _RAISE:
            // rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _ADJUST:
            // rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        default:
            // rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
    }
    return state;
}

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
#endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);


char matrix_line_str[24];

const char *read_layer_state(void) {
    uint8_t layer = biton32(layer_state);
    
    strcpy(matrix_line_str, "Layer: ");
    
    switch (layer)
    {
        case _BASE:
            strcat(matrix_line_str, "Default");
            break;
        case _LOWER:
            strcat(matrix_line_str, "Lower");
            break;
        case _ARROW:
            strcat(matrix_line_str, "Navigation");
            break;
        case _ADJUST:
            strcat(matrix_line_str, "Adjust");
            break;
        case _RAISE:
            strcat(matrix_line_str, "Raise");
            break;
        default:
            sprintf(matrix_line_str + strlen(matrix_line_str), "Unknown (%d)", layer);
    }
    
    return matrix_line_str;
}

const char *read_usb_state(void) {
    
    strcpy(matrix_line_str, "USB  : ");
    
    switch (USB_DeviceState) {
        case DEVICE_STATE_Unattached:
            strcat(matrix_line_str, "Unattached");
            break;
        case DEVICE_STATE_Suspended:
            strcat(matrix_line_str, "Suspended");
            break;
        case DEVICE_STATE_Configured:
            strcat(matrix_line_str, "Connected");
            break;
        case DEVICE_STATE_Powered:
            strcat(matrix_line_str, "Powered");
            break;
        case DEVICE_STATE_Default:
            strcat(matrix_line_str, "Default");
            break;
        case DEVICE_STATE_Addressed:
            strcat(matrix_line_str, "Addressed");
            break;
        default:
            strcat(matrix_line_str, "Invalid");
    }
    
    return matrix_line_str;
}

void matrix_scan_user(void) {
    iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        matrix_write_ln(matrix, read_layer_state());
        matrix_write_ln(matrix, read_usb_state());
        matrix_write_ln(matrix, read_keylogs());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    
    return true;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
