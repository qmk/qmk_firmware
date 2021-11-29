#include QMK_KEYBOARD_H
bool clearBackLight=false;
bool clearAllLight=false;
enum alt_keycodes {
    U_T_AGCR = SAFE_RANGE, //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    RBG_CLR,               //Restart into bootloader after hold timeout
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode
// bool has_layer_changed = false;
// static uint8_t current_layer;
keymap_config_t keymap_config;
// #include "quantum.h" 
// extern keymap_config_t keymap_config;
enum my_layers {
    _QWERTY = 0,
    _FNROW,
    _CTRL,
    _ALT
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        LM(_CTRL,MOD_LCTL), KC_LGUI,  LM(_ALT,MOD_LALT),                            KC_SPC,                             KC_RALT, MO(_FNROW),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_FNROW] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI,  LGUI(LSFT(KC_S)), RGB_SAI, _______, _______,_______, KC_PSCR, _______, _______, _______, KC_END, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD,_______ ,RGB_SAD ,_______ , _______, LGUI(KC_L), _______, _______,          KC_WSCH, _______, \
        _______, RGB_TOG, RBG_CLR, _______, _______, MD_BOOT, _______, KC_MAIL, _______, _______, _______, _______,          KC_VOLU, _______, \
        _______, _______, _______,                            KC_MPLY,                            _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
    ),
    [_CTRL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    [_ALT] = LAYOUT(
        _______, _______, _______, _______, LALT(KC_F4), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_VOLU, _______, \
        _______, _______, _______,                            KC_MPLY,                            _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
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

void clearBKLT(void){
    for (int i = 67; i < 67+38; ++i)
        {
            rgb_matrix_set_color( i,0,0,0 );
        }
}
void clear67(void){
    for (int i = 0; i < 67; ++i)
        {
            rgb_matrix_set_color( i,0,0,0 );
        }
}


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    clearBackLight=true;
    clearAllLight=false;
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};
void rgb_matrix_indicators_user(void) {
    uint8_t this_led = host_keyboard_leds();
    int R = 255;
    int G = 128;
    int B = 0;

        switch (biton32(layer_state)) {
            case _FNROW:
                R = 255;
                G = 128;
                B = 0;

                rgb_matrix_set_color(20,R,G,B );
                rgb_matrix_set_color(25,R,G,B );           
                rgb_matrix_set_color(39,R,G,B );
                rgb_matrix_set_color(45,R,G,B );
                rgb_matrix_set_color(46,R,G,B );
                rgb_matrix_set_color(56,R,G,B );
                rgb_matrix_set_color(61,R,G,B );
                rgb_matrix_set_color(64,R,G,B );
                rgb_matrix_set_color(65,R,G,B );
                rgb_matrix_set_color(66,R,G,B );

                R = 255;
                G = 0;
                B = 128;
                rgb_matrix_set_color(19,R,G,B);
                rgb_matrix_set_color(34,R,G,B);
                rgb_matrix_set_color(17,R,G,B);
                rgb_matrix_set_color(32,R,G,B);
                rgb_matrix_set_color(21,R,G,B);
                rgb_matrix_set_color(36,R,G,B);
                
                R = 0;
                G = 0;
                B = 255;
                rgb_matrix_set_color(31,R,G,B);
                rgb_matrix_set_color(33,R,G,B);
   

                //Meida Keys
                R = 255;
                G = 0;
                B = 0;
                rgb_matrix_set_color(20,R,G,B );
                rgb_matrix_set_color(25,R,G,B );
                rgb_matrix_set_color(29,R,G,B );           
                rgb_matrix_set_color(39,R,G,B );
                rgb_matrix_set_color(42,R,G,B );
                rgb_matrix_set_color(51,R,G,B );
                rgb_matrix_set_color(56,R,G,B );
                rgb_matrix_set_color(61,R,G,B );
                rgb_matrix_set_color(64,R,G,B );
                rgb_matrix_set_color(65,R,G,B );
                rgb_matrix_set_color(66,R,G,B );


                if(clearBackLight)
                    clearBKLT();
                if(clearAllLight)
                    clear67();
                break;
                default:
                    if(clearBackLight)
                        clearBKLT();
                    if(clearAllLight)
                        clear67();
        }

	  if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
            // R = 168;
            // G = 76;
            // B = 0;
            R = 255;
            G = 0;
            B = 0;
               for (int i = 0; i < 67; ++i)
        {
            rgb_matrix_set_color(i,R,G,B );
        }
  
	        // rgb_matrix_set_color(30,R,G,B); //light the capslock key when capslock is enabled
	  }

}
#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
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
                if(clearBackLight)
                    clearBackLight=false;
                else
                    clearBackLight=true;
            }
            return false;
        case RBG_CLR:
            if (record->event.pressed) {
                if(clearAllLight)
                    clearAllLight=false;
                else
                    clearAllLight=true;
            }
            return false;
            
        default:
            return true; //Process all other keycodes normally
    }
}
// #define RGB_MATRIX_STARTUP_HUE 170