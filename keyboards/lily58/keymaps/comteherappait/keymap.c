#include QMK_KEYBOARD_H

#include "cat.c"

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
    C_COMP = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, KC_ENT,  KC_BSPC, MO(_RAISE), KC_RCTL
),

 [_LOWER] = LAYOUT(
  KC_F1  ,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                   KC_F7  ,   KC_F8,   KC_F9, KC_F10,  KC_F11,  KC_F12,
  KC_BTN3, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, _______,                   _______, _______, _______, _______, _______, _______,
  KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,                   _______, _______, _______, _______, _______, _______,
  KC_BTN2, _______, _______, _______, _______, _______, QK_BOOT, QK_BOOT, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______,  KC_DEL, _______, _______
),

 [_RAISE] = LAYOUT(
  KC_F1  ,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                    KC_F7  ,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  _______, _______, _______, _______, _______, _______,                    _______, _______,   KC_UP, _______, KC_PSCR,  KC_EQL,
  _______, _______, _______, _______, _______, _______,                    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_CIRC,
  _______, _______, _______, _______, _______, _______, QK_BOOT, QK_BOOT,  _______, _______, _______, _______, KC_BACKSLASH, _______,
                             _______, _______, _______, _______, _______,   KC_DEL, _______, _______
),

  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  C_COMP,  C_COMP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);
const char *read_wpm(void); 

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    // oled_write_ln(read_keylog(), false);
    // oled_write_ln(read_keylogs(), false);
    // oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    oled_write_ln(read_host_led_state(), false);
    oled_write(read_wpm(), false);
    // oled_write_ln(read_timelog(), false);
  } else {
    // oled_write(read_logo(), false);
    render_bongo_cat();
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case C_COMP:
            if (record->event.pressed) {
                SEND_STRING("qmk flash -kb lily58 -km comteherappait -e CONVERT_TO=promicro_rp2040" SS_TAP(X_ENTER));
            }
            break;
    }
    return true;
}
