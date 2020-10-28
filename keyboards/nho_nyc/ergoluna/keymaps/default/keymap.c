#include QMK_KEYBOARD_H
#include "version.h"
#include <stdio.h>

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layers {
    QWERTY, // default layer
    LOWER,  // symbols
    RAISE,  // media & rgb keys
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTY] = LAYOUT_ergodox( \
  KC_PEQL,    KC_1,        KC_2,     KC_3,    KC_4,    KC_5,     TG(RAISE) ,        TG(LOWER)     ,     KC_6,    KC_7,    KC_8,    KC_9,           KC_0,      KC_MINS,
  KC_DEL,    KC_Q,        KC_W,     KC_E,    KC_R,    KC_T,LT(LOWER,KC_NO),       LT(RAISE,KC_NO),     KC_Y,    KC_U,    KC_I,    KC_O,           KC_P,      KC_BSLS,
  KC_CAPS,   KC_A,        KC_S,     KC_D,    KC_F,    KC_G,                                            KC_H,    KC_J,    KC_K,    KC_L,        KC_SCLN,      KC_QUOT,
  KC_LSFT,CTL_T(KC_Z),    KC_X,     KC_C,    KC_V,    KC_B,   ALL_T(KC_NO),          MEH_T(KC_NO),     KC_N,    KC_M, KC_COMM,  KC_DOT, CTL_T(KC_SLSH),      KC_RSFT,
  KC_GRV,  KC_QUOT,  LALT(KC_LSFT), KC_LEFT, KC_RGHT,                                                        KC_UP, KC_DOWN, KC_LBRC,         KC_RBRC,  GUI_T(KC_NO),
                                                    ALT_T(KC_APP), KC_LGUI,       KC_LALT, CTL_T(KC_ESC), 
                                                                   KC_HOME,       KC_PGUP,
                                                   KC_SPC, KC_BSPC, KC_END,       KC_PGDN, KC_TAB, KC_ENT
),
[LOWER] = LAYOUT_ergodox( \
  KC_EQL , KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,     KC_TRNS, KC_F6  , KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,     KC_TRNS, KC_UP  , KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
  KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                        KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
  KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,     KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
  XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                         KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
                                               KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                        KC_TRNS,     KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
),
[RAISE] = LAYOUT_ergodox( \
  EEP_RST, KC_SLCT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RESET  , XXXXXXX, KC_CUT , KC_COPY, KC_PSTE, XXXXXXX, KC_TRNS,     KC_TRNS, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX,                      RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_MS_L, XXXXXXX, KC_MS_R, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_BTN3, KC_MS_D, KC_BTN4,                                         KC_VOLU, KC_VOLD, KC_MUTE, KC_WBAK, XXXXXXX,

                                               KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                        KC_TRNS,     KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
)
};


int RGB_current_mode;
void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}
//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180 ;  // flips the display 180 degrees if offhand
    }
    return rotation;
}
// When you add source files to SRC in rules.mk, you can use functions.
     const char *read_layer_state(void);
     const char *read_logo(void);
     void set_keylog(uint16_t keycode, keyrecord_t *record);
     const char *read_keylogs(void);
     const char *read_host_led_state(void);
     //const char *read_keylog(void);
     //const char *read_mode_icon(bool swap);
     //void set_timelog(void);
     //const char *read_timelog(void);	 
#ifdef RGBLIGHT_ENABLE
     const char *read_rgb_info(void);
#endif
#ifdef RGB_MATRIX_ENABLE
     const char *read_rgb_matrix_info(void);
#endif
#ifdef WPM_ENABLE
     const char *wpm_state(void);
     void render_anim(void);
#endif

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_host_led_state(), false);	
  #ifdef RGBLIGHT_ENABLE
    oled_write_ln(read_rgb_info(), false);
  #endif
  #ifdef RGB_MATRIX_ENABLE
    oled_write_ln(read_rgb_matrix_info(),false);
  #endif
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_timelog(), false);
  } else {
	#ifdef WPM_ENABLE
	     oled_write(wpm_state(), false);
	     render_anim();
	#else
             oled_write(read_logo(), false);
             oled_scroll_left();  // Turns on scrolling
    #endif
  }
}
#endif
// OLED_DRIVER_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif	
