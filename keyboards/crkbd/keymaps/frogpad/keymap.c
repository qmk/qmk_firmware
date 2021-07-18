/* Copyright 2021 konomu 
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 
#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

enum custom_layers {
    _FROG,
    _SYM,
    _NUM,
    _EXT,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// Layer Mode aliases
#define BSP_EXT LT(_EXT,KC_BSPC)
#define OSYM OSL(_SYM)
#define ONUM OSL(_NUM)
#define OSFT OSM(MOD_LSFT)
#define OGUI OSM(MOD_LGUI)
#define ATAB LCA(KC_TAB)
#define OALT OSM(MOD_LALT)
#define OCTL OSM(MOD_LCTL)
#define CBSP C(KC_BSPC)

//This is the left-handed version.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_FROG] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_F,    KC_D,    KC_N,    KC_I,    KC_G,                         KC_G,    KC_I,    KC_N,    KC_D,    KC_F,  KC_ESC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      BSP_EXT,    KC_S,    KC_T,    KC_H,    KC_E,    KC_O,                         KC_O,    KC_E,    KC_H,    KC_T,    KC_S, BSP_EXT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         OSFT,    KC_C,    KC_W,    KC_R,    KC_A,    KC_U,                         KC_U,    KC_A,    KC_R,    KC_W,    KC_C,    OSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             ONUM,    OSYM,  KC_SPC,     KC_SPC,    OSYM,    ONUM \
                                      //`--------------------------'  `--------------------------'
    ),

    [_SYM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_LBRC, KC_LCBR, KC_LPRN,   KC_AT, KC_CIRC,                      KC_CIRC,   KC_AT, KC_LPRN, KC_LCBR, KC_LBRC,  KC_TAB,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSLS, KC_COLN, KC_SCLN, KC_QUES, KC_EXLM, KC_SLSH,                      KC_SLSH, KC_EXLM, KC_QUES, KC_SCLN, KC_COLN, KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_RBRC, KC_RCBR, KC_RPRN, KC_AMPR, KC_ASTR,                      KC_ASTR, KC_AMPR, KC_RPRN, KC_RCBR, KC_RBRC, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
    ),

    [_NUM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_EQL,    KC_6,    KC_7,    KC_8,    KC_9,  KC_DOT,                       KC_DOT,    KC_9,    KC_8,    KC_7,    KC_6,  KC_EQL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PLUS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_5,    KC_4,    KC_3,    KC_2,    KC_1, KC_PLUS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS, KC_HASH,  KC_DLR, KC_PERC,    KC_0, KC_COMM,                      KC_COMM,    KC_0, KC_PERC,  KC_DLR, KC_HASH, KC_MINS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,    OGUI,       OGUI, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
    ),

    [_EXT] = LAYOUT( \
/*I recommend adding a TO() that leads to your two-handed layer to the first and last key in the next line of code if you 
are adding this keymap to a two-handed keymap. It is left blank for this purpose.*/
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_WBAK, KC_HOME,   KC_UP,  KC_END, KC_WFWD,                      KC_WFWD, KC_HOME,   KC_UP,  KC_END, KC_WBAK, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    ATAB, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL,                       KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT,    ATAB, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V),    OALT,                         OALT, C(KC_V), C(KC_C), C(KC_X), C(KC_Z), XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             OSFT,    OCTL,    CBSP,       CBSP,    OCTL,    OSFT \
                                      //`--------------------------'  `--------------------------'
    )
};

uint8_t RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_get_mode();
    #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
	combo_disable();
    if (layer_state_cmp(state, _FROG)) {
        combo_enable();
    }
    return state;
    state = update_tri_layer_state(state, _SYM, _NUM, _EXT);
    return state;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

#    define KEYLOG_LEN 5
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _FROG:
            oled_write_P(PSTR(" Default"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Symbols"), layer_state_is(_SYM));
    oled_write_P(PSTR("Numbers"), layer_state_is(_NUM));
	oled_write_P(PSTR("Extend"), layer_state_is(_EXT));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_mod_status(get_mods());
    render_bootmagic_status();

    render_keylogger_status();
}

void oled_task_user(void) {
    update_log();
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_crkbd_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
    }
    return true;
}
#endif
