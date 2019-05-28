#include QMK_KEYBOARD_H
#include "brandonschlack.h"

enum alt_keycodes {
    U_T_AUTO = KEYMAP_SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,                     //USB Toggle Automatic GCR control
    DBG_TOG,                      //DEBUG Toggle On / Off
    DBG_MTRX,                     //DEBUG Toggle Matrix Prints
    DBG_KBD,                      //DEBUG Toggle Keyboard Prints
    DBG_MOU,                      //DEBUG Toggle Mouse Prints
    MD_BOOT,                      //Restart into bootloader after hold timeout
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /***********
     *  MacOS  *
     ***********/
    /* Base Layer: Mac
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backs|Pwr|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Hom|
     * |---------------------------------------------------------------|
     * |HyCap |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctl |Alt |Gui |         Space         |Gui |FnPy|  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [_MAC] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, MC_POWR, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        HY_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MM_FN_M, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    /* Function Layer: Mac
     * ,---------------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|    Del|SLP|
     * |---------------------------------------------------------------|
     * |     |   |   |   |DFU|   |   |   |   |   |F13|F14|F15|  LHP|End|
     * |---------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   | TgAdjst|VlU|
     * |---------------------------------------------------------------|
     * |        |RTO|   |   |   |   |   |MKE|Prv|Nxt|Plr|MutSft|PgU|VlD|
     * |---------------------------------------------------------------|
     * |    |    |    |                       |    |    |  |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
    [_MACFN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  MC_SLPD, \
        _______, _______, _______, _______, MD_BOOT, _______, _______, _______, _______, _______, KC_F13,  KC_F14,  KC_F15,  MC_LHPD, KC_END,  \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TG_ADJT, KC_VOLU, \
        _______, RGB_TOG, _______, _______, _______, _______, _______, MD_MAKE, KC_MRWD, KC_MFFD, MC_PLYR, MM_RSFT,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END   \
    ),

    /***********
     * Windows *
     ***********/
    /* Base Layer: Windows
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backs|Del|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Hom|
     * |---------------------------------------------------------------|
     * |HyCap |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctl |Alt |Gui |         Space         |Gui |FnPy|  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [_WIN] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        HY_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MM_FN_W, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    /* Function Layer: Windows
     * ,---------------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|    Del|LCK|
     * |---------------------------------------------------------------|
     * |     |   |   |   |DFU|   |   |   |   |   |PtS|SLk|Pau|  TSK|End|
     * |---------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   | TgAdjst|VlU|
     * |---------------------------------------------------------------|
     * |        |RTO|   |   |   |   |   |MKE|Prv|Nxt|Stp|MutSft|PgU|VlD|
     * |---------------------------------------------------------------|
     * |    |    |    |                       |    |    |  |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
    [_WINFN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  WN_LOCK, \
        _______, _______, _______, _______, MD_BOOT, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, WN_TSKM, KC_END,  \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TG_ADJT, KC_VOLU, \
        _______, RGB_TOG, _______, _______, _______, _______, _______, MD_MAKE, KC_MPRV, KC_MNXT, KC_MSTP, MM_RSFT,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END   \
    ),

    /***********
     *  Magic  *
     ***********/
    /* Keyboard Layer: Magic
     * ,---------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |
     * |---------------------------------------------------------------|
     * |     |RS-|RB+|RS+|RH+|RS+|   |UAD|GCR|   |   |   |   |     |   |
     * |---------------------------------------------------------------|
     * |      |RM-|RB-|RM+|RH-|RS-|   |   |   |   |   |   | TgAdjst|   |
     * |---------------------------------------------------------------|
     * |        |RTO|   |   |   |   |KRO|   |Mac|Win|   |      |   |   |
     * |---------------------------------------------------------------|
     * |    |    |    |                       |    |    |  |   |   |   |
     * `---------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, XXXXXXX, U_T_AUTO,U_T_AGCR,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          TG_ADJT, XXXXXXX, \
        XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_NKRO, XXXXXXX, OS_MAC,  OS_WIN,  XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    rgb_matrix_sethsv(HSV_PURPLE);
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_MODIFIER);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

void rgb_matrix_hsv_layer (uint8_t hue, uint8_t sat, uint8_t val) {
    rgb_matrix_sethsv_noeeprom(hue, sat, val);
    if (rgb_matrix_get_flags() == LED_FLAG_MODIFIER) {
        rgb_matrix_set_color(30, 0, 0, 0);
    }
}

void rgb_matrix_indicators_user(void) {
	uint8_t this_led = host_keyboard_leds();

	if (!g_suspend_state && rgb_matrix_config.enable) {
		switch (biton32(layer_state)) {
            case _MAC:
                rgb_matrix_hsv_layer(HSV_PURPLE);
                break;
            case _MACFN:
                rgb_matrix_hsv_layer(HSV_PINK);
                break;
            case _WIN:
                rgb_matrix_hsv_layer(HSV_MAGENTA);
                break;
            case _WINFN:
                rgb_matrix_hsv_layer(HSV_CYAN);
                break;
            default:
                rgb_matrix_hsv_layer(HSV_WHITE);
		}

        if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
	        rgb_matrix_set_color(30, RGB_GREEN);
	    } else {
            rgb_matrix_set_color(30, 0, 0, 0);
        }
	}
}
