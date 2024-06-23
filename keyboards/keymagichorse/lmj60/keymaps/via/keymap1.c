#include "lmj60.h"
#include QMK_KEYBOARD_H
#include "joystick.h"
//#include <print.h>
#include "analog.h"


//huoqu!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "config.h"
#include "keymap.h"  // to get keymaps[][][]
#include "tmk_core/common/eeprom.h"
#include "progmem.h"  // to read default from flash
#include "quantum.h"  // for send_string()
#include "dynamic_keymap.h"
#include "via.h"  // for default VIA_EEPROM_ADDR_END



#ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif

#ifndef DYNAMIC_KEYMAP_MACRO_COUNT
#    define DYNAMIC_KEYMAP_MACRO_COUNT 16
#endif

// This is the default EEPROM max address to use for dynamic keymaps.
// The default is the ATmega32u4 EEPROM max address.
// Explicitly override it if the keyboard uses a microcontroller with
// more EEPROM *and* it makes sense to increase it.
#ifndef DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
#    if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#        define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 2047
#    else
#        define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 1023
#    endif
#endif

// Due to usage of uint16_t check for max 65535
#if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 65535
#    error DYNAMIC_KEYMAP_EEPROM_MAX_ADDR must be less than 65536
#endif

// If DYNAMIC_KEYMAP_EEPROM_ADDR not explicitly defined in config.h,
// default it start after VIA_EEPROM_CUSTOM_ADDR+VIA_EEPROM_CUSTOM_SIZE
#ifndef DYNAMIC_KEYMAP_EEPROM_ADDR
#    ifdef VIA_EEPROM_CUSTOM_CONFIG_ADDR
#        define DYNAMIC_KEYMAP_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR + VIA_EEPROM_CUSTOM_CONFIG_SIZE)
#    else
#        error DYNAMIC_KEYMAP_EEPROM_ADDR not defined
#    endif
#endif

// Dynamic macro starts after dynamic keymaps
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))
#endif

// Sanity check that dynamic keymaps fit in available EEPROM
// If there's not 100 bytes available for macros, then something is wrong.
// The keyboard should override DYNAMIC_KEYMAP_LAYER_COUNT to reduce it,
// or DYNAMIC_KEYMAP_EEPROM_MAX_ADDR to increase it, *only if* the microcontroller has
// more than the default.
#if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR < 100
#    error Dynamic keymaps are configured to use more EEPROM than is available.
#endif

// Dynamic macros are stored after the keymaps and use what is available
// up to and including DYNAMIC_KEYMAP_EEPROM_MAX_ADDR.
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 1)
#endif
//huoqu!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//摇杆
char arrow_keys[4] = {KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT}; // up, left, down, right
static int actuation = 256; // actuation point for arrows (0-511)
bool arrows[4];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        //0moren
		keyCheng(
            KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
            LT(MO(1),KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
            LT(MO(2),KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, KC_DEL,
            KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_LALT, MO(1), KC_LCTL),

        //1meiti
        keyCheng(
            RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
            LT(MO(1),KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
            LT(MO(2),KC_CAPS),KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,RGB_TOG, RGB_MOD, RGB_HUI, KC_LSFT, KC_DEL,
            KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_LALT, MO(1), KC_LCTL),
        //2 shubiao
        keyCheng(
            KC_ACL0,KC_ACL1, KC_ACL2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
            LT(MO(1),KC_TAB), KC_MS_BTN1, KC_MS_BTN2, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
            LT(MO(2),KC_CAPS),KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, KC_DEL,
            KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_LALT, MO(1), KC_LCTL),
};
uint8_t dynamic_keymap_get_layer_count(void) { return DYNAMIC_KEYMAP_LAYER_COUNT; }

void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column) {
    // TODO: optimize this with some left shifts
    return ((void *)DYNAMIC_KEYMAP_EEPROM_ADDR) + (layer * MATRIX_ROWS * MATRIX_COLS * 2) + (row * MATRIX_COLS * 2) + (column * 2);
}

uint16_t dynamic_keymap_get_keycode1(uint8_t layer, uint8_t row, uint8_t column) {
    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    uint16_t keycode = eeprom_read_byte(address) << 8;
    keycode |= eeprom_read_byte(address + 1);
    return keycode;
}

void matrix_scan_user(void){

   switch (biton32(layer_state))
        {
            //方向
            case 0:
                //up
                if (!arrows[0] && analogReadPin(D7) - 512 > actuation){
                    arrows[0] = true;
                    //register_code16(KC_UP);
                    register_code16(dynamic_keymap_get_keycode1(0,0,0));
                   // unregister_code16(dynamic_keymap_get_keycode(0,0,0));
                    //register_code16(KC_UP);
                //    register_code16(dynamic_keymap_get_keycode(0,2,2));
                }
                else if (arrows[0] &&  analogReadPin(D7) - 512 < actuation){
                    arrows[0] = false;
                    //unregister_code16(KC_UP);
                    unregister_code16(dynamic_keymap_get_keycode1(0,0,0));
                    //unregister_code16(dynamic_keymap_get_keycode(0,0,0));
                    // unregister_code16(KC_UP);
                }
                //下
                if (!arrows[1] && analogReadPin(D7) - 512 < -actuation){
                    arrows[1] = true;
                    register_code16(KC_DOWN);
                }
                else if (arrows[1] && analogReadPin(D7) - 512 > -actuation){
                    arrows[1] = false;
                    unregister_code16(KC_DOWN);
                }


                //左
                if (!arrows[2] && analogReadPin(D6) - 512 > actuation){
                    arrows[2] = true;
                   // register_code16(KC_RIGHT);
                   register_code16(KC_LEFT);
                }
                else if (arrows[2] &&  analogReadPin(D6) - 512 < actuation){
                    arrows[2] = false;
                   // unregister_code16(KC_RIGHT);
                    unregister_code16(KC_LEFT);
                }

                //右
                if (!arrows[3] && analogReadPin(D6) - 512 < -actuation){
                    arrows[3] = true;
                   // register_code16(KC_LEFT);
                   register_code16(KC_RIGHT);
                }
                else if (arrows[3] && analogReadPin(D6) - 512 > -actuation){
                    arrows[3] = false;
                   // unregister_code16(KC_LEFT );
                   unregister_code16(KC_RIGHT );
                }
            break;
            //鼠标上下左右
            case 2:
                    //up
                if (!arrows[0] && analogReadPin(D7) - 512 > actuation){
                    arrows[0] = true;
                    register_code16(KC_MS_UP);
                }
                else if (arrows[0] &&  analogReadPin(D7) - 512 < actuation){
                    arrows[0] = false;
                    unregister_code16(KC_MS_UP);
                }
                //下
                if (!arrows[1] && analogReadPin(D7) - 512 < -actuation){
                    arrows[1] = true;
                    register_code16(KC_MS_DOWN);
                }
                else if (arrows[1] && analogReadPin(D7) - 512 > -actuation){
                    arrows[1] = false;
                    unregister_code16(KC_MS_DOWN);
                }
                //左
                if (!arrows[2] && analogReadPin(D6) - 512 > actuation){
                    arrows[2] = true;
                    register_code16(KC_MS_LEFT);
                    // register_code16(KC_MS_RIGHT);
                }
                else if (arrows[2] &&  analogReadPin(D6) - 512 < actuation){
                    arrows[2] = false;
                    unregister_code16(KC_MS_LEFT);
                    // unregister_code16(KC_MS_RIGHT);
                }
                //右
                if (!arrows[3] && analogReadPin(D6) - 512 < -actuation){
                    arrows[3] = true;
                    register_code16(KC_MS_RIGHT);
                    // register_code16(KC_MS_LEFT);
                }
                else if (arrows[3] && analogReadPin(D6) - 512 > -actuation){
                    arrows[3] = false;
                    unregister_code16(KC_MS_RIGHT );
                    // unregister_code16(KC_MS_LEFT );
                }
            break;
            //左右声音和上下亮度
            case 1:
                //up加亮度
                if (!arrows[0] && analogReadPin(D7) - 512 > actuation){
                    arrows[0] = true;
                    register_code16(KC_BRIGHTNESS_UP);
                }
                else if (arrows[0] &&  analogReadPin(D7) - 512 < actuation){
                    arrows[0] = false;
                    unregister_code16(KC_BRIGHTNESS_UP);
                }
                //下减亮度
                if (!arrows[1] && analogReadPin(D7) - 512 < -actuation){
                    arrows[1] = true;
                    register_code16(KC_BRIGHTNESS_DOWN);
                }
                else if (arrows[1] && analogReadPin(D7) - 512 > -actuation){
                    arrows[1] = false;
                    unregister_code16(KC_BRIGHTNESS_DOWN);
                }
                //右加大声音
                if (!arrows[2] && analogReadPin(D6) - 512 > actuation){
                    arrows[2] = true;
                    register_code16(KC_VOLD);
                    // register_code16(KC_VOLU);
                }
                else if (arrows[2] &&  analogReadPin(D6) - 512 < actuation){
                    arrows[2] = false;
                    unregister_code16(KC_VOLD);
                    // unregister_code16(KC_VOLU);
                }
                //左减小声音
                if (!arrows[3] && analogReadPin(D6) - 512 < -actuation){
                    arrows[3] = true;
                    register_code16(KC_VOLU);
                    // register_code16(KC_VOLD);
                }
                else if (arrows[3] && analogReadPin(D6) - 512 > -actuation){
                    arrows[3] = false;
                    unregister_code16(KC_VOLU );
                    // unregister_code16(KC_VOLD );
                }
            break;

        }

}
//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL
};
// 以下为RGB灯效分层设置：
// Light LEDs 0 to 4 in red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({7,2, HSV_WHITE  });

// Light LEDs 0 to 4 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({7,2, HSV_CYAN});

// Light LEDs 0 to 4 in green when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({7,2, HSV_YELLOW});


const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer, my_layer1_layer,
    my_layer2_layer // Overrides other layers
);

void keyboard_post_init_user(void)
{
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}

bool led_update_user(led_t led_state)
{
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
