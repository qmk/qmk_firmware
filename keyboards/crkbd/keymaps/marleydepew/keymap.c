#include QMK_KEYBOARD_H
#include "../../macro.h"

enum layer_names {
    _COLEMAK_DH,
    _NUMBER,
    _SYMBOL,
    _FUNCTION,
    _NAVIGATION,
    _MOUSE,
    _RGB
};

enum custom_keycodes {
    MACRO_V = SAFE_RANGE,
    MACRO_A,
    MACRO_C,
    MACRO_1,
    MACRO_2,
    MACRO_3,
    MACRO_4,
    MACRO_5,
    MS_WHLD_SLOWEST,
    MS_WHLD_SLOW,
    MS_WHLD_FAST,
    MS_WHLU_SLOWEST,
    MS_WHLU_SLOW,
    MS_WHLU_FAST,
    DRINK_WATER,
    PRINT_WATER,
    TOGG_WATER,
    RESET_WATER
};

uint32_t scroll_encoder_timer = 0;
int8_t   scroll_encoder_mode  = 0;
enum  scroll_encoder_modes {
    DOWN_FAST = -4,
    DOWN_UNMOD = -3,
    DOWN_SLOW = -2,
    DOWN_SLOWEST = -1,
    STILL = 0,
    UP_SLOWEST = 1,
    UP_SLOW = 2,
    UP_UNMOD = 3,
    UP_FAST = 4
};

uint32_t water_reminder_timer = 0;
#define WATER_REMINDER_0_MS 15 * 60 * 1000 // 15 minutes
#define WATER_REMINDER_1_MS 16 * 60 * 1000 // 16 minutes
#define WATER_REMINDER_2_MS 17 * 60 * 1000 // 17 minutes
#define WATER_REMINDER_3_MS 18 * 60 * 1000 // 18 minutes

uint8_t water_consumed_oz = 0;
#define DRINK_AMOUNT_OZ 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK_DH] = LAYOUT_split_3x6_3_ex2(                                                        // Colemak DH Layer
    // |-------------+-------------+-------------+-------------+-------------+-------------+-------------|   |-------------+-------------+-------------+-------------+-------------+-------------+-------------|
        MACRO_1,      KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,         MACRO_1,          MACRO_3,      KC_J,         KC_L,         KC_U,         KC_Y,         DRINK_WATER,  MACRO_2,
    // |-------------+-------------+-------------+-------------+-------------+-------------+-------------|   |-------------+-------------+-------------+-------------+-------------+-------------+-------------|
        KC_CAPS,      LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G,         MACRO_2,          MACRO_4,      KC_M,         LCTL_T(KC_N), LSFT_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), KC_QUOT,
    // |-------------+-------------+-------------+-------------+-------------+-------------+-------------|   |-------------+-------------+-------------+-------------+-------------+-------------+-------------|
        KC_ESC,       KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,                                         KC_K,         KC_H,         KC_COMM,      KC_DOT,       KC_SLSH,      QK_LEAD,
    // |-------------+-------------+-------------+-------------+-------------+-------------|                               |-------------+-------------+-------------+-------------+-------------+-------------|
                                                  LT(3,KC_TAB), LT(1,KC_BSPC),LT(2,KC_DEL),                                 LT(5,KC_ENT), LT(4,KC_SPC), LT(6,KC_PSCR) 
    //                                           |-------------+-------------+-------------|                               |-------------+-------------+-------------|
    ),

    [_NUMBER] = LAYOUT_split_3x6_3(                                      // Number Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_1,       KC_2,       KC_3,       PRINT_WATER,XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        KC_MINS,    KC_4,       KC_5,       KC_6,       KC_COLN,    KC_GRV,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_UNDS,    KC_7,       KC_8,       KC_9,       KC_SLSH,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_LPRN,    KC_0,       KC_RPRN
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
    ),

    [_SYMBOL] = LAYOUT_split_3x6_3(                                      // Symbols Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_EXLM,    KC_AT,      KC_HASH,    TOGG_WATER, XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        KC_PLUS,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_SCLN,    KC_TILD,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_EQL,     KC_AMPR,    KC_ASTR,    KC_DOT,     KC_BSLS,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_LBRC,    XXXXXXX,    KC_RBRC
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  ),

    [_FUNCTION] = LAYOUT_split_3x6_3(                                   // Function Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_F1,      KC_F2,      KC_F3,      RESET_WATER, XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        XXXXXXX,    KC_F4,      KC_F5,      KC_F6,      KC_APP,     KC_PIPE,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_F7,      KC_F8,      KC_F9,      KC_PAUS,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_F11,     KC_F10,     KC_F12
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  ),

    [_NAVIGATION] = LAYOUT_split_3x6_3_ex2(                                  // Navigation Layer (with macros)
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    DM_REC1,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LEFT,    KC_UP,      KC_DOWN,    KC_RGHT,    XXXXXXX,    DM_PLY1,        XXXXXXX,    XXXXXXX,    KC_RCTL,    KC_RSFT,    KC_RALT,    KC_RGUI,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_HOME,    KC_PGUP,    KC_PGDN,    KC_END,     XXXXXXX,                                XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|                           |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,                                XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|                           |-----------+-----------+-----------|
  ),

    [_MOUSE] = LAYOUT_split_3x6_3_ex2(                                                // Mouse Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        MACRO_V,    MS_WHLL,    MS_WHLU,    MS_WHLD,    MS_WHLR,    XXXXXXX,    DM_REC2,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        MACRO_A,    MS_LEFT,    MS_UP,      MS_DOWN,    MS_RGHT,    LSFT(KC_F3),DM_PLY2,        XXXXXXX,    XXXXXXX,    KC_RCTL,    KC_RSFT,    KC_RALT,    KC_RGUI,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        MACRO_C,    XXXXXXX,    XXXXXXX,    MS_BTN2,    MS_BTN1,    MS_BTN3,                                MS_BTN3,    MS_BTN2,    MS_BTN1,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|                           |-----------+-----------+-----------+-----------+-----------+-----------|
                                            MS_ACL0,    MS_ACL1,    MS_ACL2,                                XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|                           |-----------+-----------+-----------|
  ),

    [_RGB] = LAYOUT_split_3x6_3(                                           // RGB Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    DT_PRNT,    DT_UP,      DT_DOWN,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        RM_TOGG,    RM_NEXT,    RM_HUEU,    RM_SATU,    RM_VALU,    RM_SPDU,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        RGB_M_G,    RM_PREV,    RM_HUED,    RM_SATD,    RM_VALD,    RM_SPDD,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  )
};

// These are my custom overrides for the shift keys
#ifdef KEY_OVERRIDE_ENABLE

// Shift + ( = < on the number layer
const key_override_t left_parenth_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LPRN, KC_LABK, 1 << _NUMBER);

// Shift + ) = > on the number layer
const key_override_t right_parenth_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_RPRN, KC_RABK, 1 << _NUMBER);

// Shift + 9 = . on the number layer
const key_override_t nine_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_9, KC_DOT, 1 << _NUMBER);

// This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
const key_override_t *key_overrides[] = {
    &left_parenth_override,
    &right_parenth_override,
    &nine_override,
    NULL // Null terminate the array of overrides
};

#endif // End KEY_OVERRIDE_ENABLE

// This gets called for each key.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {d

    // This is for the macros
    switch (keycode) {
        
        case MACRO_V:
            if (record->event.pressed) {
                // when keycode MACRO_V is pressed
                // The string is defined in "../../macro.h"
                SEND_STRING(MV_STRING);
            } else {
                // when keycode MACRO_V is released
            }
            break;

        case MACRO_A:
            if (record->event.pressed) {
                // when keycode MACRO_A is pressed
                // The string is defined in "../../macro.h"
                SEND_STRING(MA_STRING);
            } else {
                // when keycode MACRO_A is released
            }
            break;

        case MACRO_C:
            if (record->event.pressed) {
                // when keycode MACRO_C is pressed
                // The string is defined in "../../macro.h"
                SEND_STRING(MC_STRING);
            } else {
                // when keycode MACRO_C is released
            }
            break;

        case MACRO_1:
            if (record->event.pressed) {
                // when keycode MACRO_1 is pressed
                SEND_STRING(SS_RGUI("r") SS_DELAY(500) "cmd.exe" SS_TAP(X_ENT));
            }
            break;

        case MACRO_2:
            if (record->event.pressed) {
                // when keycode MACRO_2 is pressed
                SEND_STRING(SS_RGUI("r") SS_DELAY(500) "calc.exe" SS_TAP(X_ENT));
            }
            break;

        case MACRO_3:
            if (record->event.pressed) {
                SEND_STRING(TEMPLATE_STRING);
            }
            break;

        case MACRO_4:
            if (record->event.pressed) {
                SEND_STRING(CLOSURE_STRING);
            }
            break;

        case DRINK_WATER:
            if (record->event.pressed) {
                water_consumed_oz += 4;
                water_reminder_timer = timer_read32();
            }
            break;

        case PRINT_WATER:
            if (record->event.pressed) {
                SEND_STRING("So far, I had ");
                send_string(get_u8_str(water_consumed_oz, ' '));
                SEND_STRING(" oz of water.");
            }
            break;

        case TOGG_WATER:
            if (record->event.pressed) {
                // If the timer is 0, its not tracking the water intake.
                if (water_reminder_timer == 0) {
                    water_reminder_timer = timer_read32();
                } else {
                    water_reminder_timer = 0;
                }
            }
            break;

        case RESET_WATER:
            if (record->event.pressed) {
                water_consumed_oz = 0;
                SEND_STRING("So far, I had 0 oz of water.");
            }
            break;
    }
    return true;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_COLEMAK_DH] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), },
  [_NUMBER] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), },
  [_SYMBOL] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), },
  [_FUNCTION] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), },
  [_NAVIGATION] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), },
  [_MOUSE] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), },
  [_RGB] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), },
};
#endif

// This function alternates the keyboard between the current hue, 
// and an offset hue determined by the RGB Matrix Speed setting. 
// The flashing period is determined by the provided period in milliseconds.
void alternate_colors(uint16_t period_ms) {

    hsv_t hsv = rgb_matrix_get_hsv();

    // Increase the hue for the first half of the period.
    if (timer_elapsed32(water_reminder_timer) % period_ms < period_ms / 2) {
    
        // The degree of the change is determined by the RGB Matrix Speed setting.
        // To align with the RGB Matrix Vertical Gradient effect, it's scaled to 3/4.
        // The hsv hue value is between 0 and 255, so we use modulo to wrap around if it goes over 255.
        hsv.h += rgb_matrix_get_speed() * 3/4;
        hsv.h %= 255;
    }
    
    rgb_t rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_user(void) {

    if (water_reminder_timer == 0) return true;

    if (timer_elapsed32(water_reminder_timer) > WATER_REMINDER_3_MS) {
        alternate_colors(200);
        return false;
    }

    if (timer_elapsed32(water_reminder_timer) > WATER_REMINDER_2_MS) {
        alternate_colors(1000);
        return false;
    }

    if (timer_elapsed32(water_reminder_timer) > WATER_REMINDER_1_MS) {
        alternate_colors(4000);
        return false;
    }

    if (timer_elapsed32(water_reminder_timer) > WATER_REMINDER_0_MS) {
        alternate_colors(10000);
        return false;
    }

    return true;
}