#include "lmj60.h"
#include QMK_KEYBOARD_H
#include "joystick.h"
#include <print.h>
#include "analog.h"

//摇杆
char arrow_keys[4] = {KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT}; // up, left, down, right
static int actuation = 200; // actuation point for arrows (0-511)
bool arrows[4];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        //0层
		keyCheng(
            KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
            LT(MO(1),KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
            LT(MO(2),KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, KC_DEL,
            KC_LCTL, KC_LGUI, KC_LALT, KC_UP,KC_DOWN, KC_SPC, KC_LEFT,KC_RIGHT,KC_LALT, MO(1), LT(MO(2),KC_LCTL)),
//         1层
        keyCheng(
            RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
            LT(MO(1),KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
            LT(MO(2),KC_CAPS),KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,RGB_TOG, RGB_MOD, RGB_HUI, KC_LSFT, KC_DEL,
            KC_LCTL, KC_LGUI, KC_LALT, KC_BRIU,KC_BRID, KC_SPC, KC_VOLD,KC_VOLU,KC_LALT, MO(1),  LT(MO(2),KC_LCTL)),
//         2层
        keyCheng(
            KC_ACL0,KC_ACL1, KC_ACL2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
            LT(MO(1),KC_TAB), KC_MS_BTN1, KC_MS_BTN2, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
            LT(MO(2),KC_CAPS),KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MS_BTN1, KC_DEL,
           KC_LCTL, KC_LGUI, KC_LALT, KC_MS_U,KC_MS_D, KC_SPC, KC_MS_L,KC_MS_R,KC_LALT, MO(1),  LT(MO(2),KC_LCTL)),
};

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4, 3);
        if (keycode >= MACRO00 && keycode <= MACRO15) {
            dynamic_keymap_macro_send(keycode - MACRO00);
        } else {
            register_code16(keycode);
            wait_ms(10);
            unregister_code16(keycode);
        }
    } else {
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4, 4);
        if (keycode >= MACRO00 && keycode <= MACRO15) {
            dynamic_keymap_macro_send(keycode - MACRO00);
        } else {
            register_code16(keycode);
            wait_ms(10);
            unregister_code16(keycode);
        }
    }
}
#endif

void matrix_scan_user(void){

            if (!arrows[0] && analogReadPin(D7) - 512 > actuation){
            arrows[0] = true;
            //register_code16(KC_UP);'
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4,3);
            register_code16(keycode);

            }
            else if (arrows[0] &&  analogReadPin(D7) - 512 < actuation){
            arrows[0] = false;
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4,3);
            unregister_code16(keycode);

            }
            //下
            if (!arrows[1] && analogReadPin(D7) - 512 < -actuation){
            arrows[1] = true;
            //register_code16(KC_DOWN);
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4,4);
            register_code16(keycode);
            // register_code16(keymaps[0][4][4]);
            //register_code16(dynamic_keymap_get_keycode(0,4,4));
            }
            else if (arrows[1] && analogReadPin(D7) - 512 > -actuation){
            arrows[1] = false;
            //unregister_code16(KC_DOWN);
            //                     unregister_code16(keymaps[0][4][4]);
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4,4);
            unregister_code16(keycode);
            // unregister_code16(dynamic_keymap_get_keycode(0,4,4));
            }
            //左
            if (!arrows[2] && analogReadPin(D6) - 512 > actuation){
            arrows[2] = true;
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4,6);
            register_code16(keycode);
            //register_code16(KC_LEFT);
            //                    register_code16(keymaps[0][4][6]);
            }
            else if (arrows[2] &&  analogReadPin(D6) - 512 < actuation){
            arrows[2] = false;
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4,6);
            unregister_code16(keycode);
            //unregister_code16(KC_LEFT);
            //                     unregister_code16(keymaps[0][4][6]);
            }

            //右
            if (!arrows[3] && analogReadPin(D6) - 512 < -actuation){
            arrows[3] = true;
            //register_code16(KC_RIGHT);
            //                     register_code16(keymaps[0][4][7]);
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4,7);
            register_code16(keycode);
            }
            else if (arrows[3] && analogReadPin(D6) - 512 > -actuation){
            arrows[3] = false;
            // unregister_code16(KC_RIGHT );
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4,7);
            unregister_code16(keycode);

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
