#include "layers.h" 
#include "rgbFunctions.h"
#include "rgb_matrix.h"
#include "host.h"        // Required for `host_keyboard_led_state()`

const led_color_t fn_keys[] = {
    {12, RGB_UNSET},  // KC_MYCM  (Media: My Computer)
    {11, RGB_UNSET},  // KC_WSCH  (Web Search)
    {10, RGB_UNSET},  // KC_MAIL  (Email)
    {9, RGB_UNSET},  // KC_CALC  (Calculator)
    {8, RGB_UNSET},  // KC_MSEL  (Media Select)
    {7, RGB_UNSET},  // KC_MSTP  (Media Stop)
    {6, RGB_UNSET},  // KC_MPRV  (Media Previous)
    {5, RGB_UNSET},  // KC_MPLY  (Media play pause)
    {4, RGB_UNSET},  // KC_MNXT  (Media Next)
    {3, RGB_UNSET},  // KC_MUTE  (Mute)
    {2, RGB_UNSET},  // KC_VOLU  (media volume up)
    {1, RGB_UNSET},  // KC_VOLD  (Volume Down)
};

const led_color_t rgb_keys[] = {
    {2,  RGB_UNSET},   // RM_SPDD (Speed Down)
    {1,  RGB_UNSET},  // RM_SPDU (Speed Up)
    {25, RGB_UNSET}, // RM_VALD (Brightness Down)
    {26, RGB_UNSET},  // RM_VALU (Brightness Up)
    {27, {RGB_RED}}, // RM_TOGG (Toggle RGB)
    {30, RGB_UNSET}, // RM_PREV (Previous Effect)
    {29, RGB_UNSET}  // RM_NEXT (Next Effect)
};

const led_color_t nav_keys[] = {
    {50, {RGB_BLUE}}, // .
    {51, RGB_UNSET}, // ?
    {52, {RGB_BLUE}}, // right shift
    {56, RGB_UNSET}, // right alt   
    {55, RGB_UNSET}, // app key 
    {54, RGB_UNSET} // right control
};

const led_color_t media_keys[] = {
    {12, RGB_UNSET},  // KC_MYCM  (Media: My Computer)
    {11, RGB_UNSET},  // KC_WSCH  (Web Search)
    {10, RGB_UNSET},  // KC_MAIL  (Email)
    {9, RGB_UNSET},  // KC_CALC  (Calculator)
    {8, RGB_UNSET},  // KC_MSEL  (Media Select)
    {7, {RGB_RED}},  // KC_MSTP  (Media Stop)
    {6, {RGB_BLUE}},  // KC_MPRV  (Media Previous)
    {5, {RGB_BLUE}},  // KC_MPLY  (Media play pause)
    {4, {RGB_BLUE}},  // KC_MNXT  (Media Next)
    {3, {RGB_RED}},  // KC_MUTE  (Mute)
    {2, RGB_UNSET},  // KC_VOLU  (media volume up)
    {1, RGB_UNSET},  // KC_VOLD  (Volume Down)
};

void setRgbForKeys(layer_state_t layer, const led_color_t *keys, uint8_t key_count, RGB default_color) {
    if (!layer_state_is(layer)) return;

    for (uint8_t i = 0; i < key_count; i++) {
        //when not having RGB UNSET in the array use the argument color
        RGB final_color = (memcmp(&keys[i].color, &RGB_UNSET, sizeof(RGB)) == 0)
                        ? default_color  
                        : keys[i].color;

        rgb_matrix_set_color(keys[i].index, final_color.r, final_color.g, final_color.b);
    }
}

void setRgbForWinKeyIndicator(void){
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(40, RGB_RED);
    }
}

void setRgbForCapsLockIndicator(void){
    if (layer_state_is(WIN_DIS_LAYER)) {
        rgb_matrix_set_color(59, RGB_RED);
	}
}

void setRgbForFnLayer(void){
    if (!layer_state_is(FN_LAYER)) return;
    //to check wich int corresponds with each key check the rk61.c file
    rgb_matrix_set_color(40, RGB_YELLOW); // caps lock key
    rgb_matrix_set_color(53, RGB_YELLOW); // FN key
    rgb_matrix_set_color(14, RGB_YELLOW); // TAB key
    rgb_matrix_set_color(27, RGB_RED); // back slash key (for qk boot)

    rgb_matrix_set_color(41, RGB_YELLOW); //left shift key
    rgb_matrix_set_color(57, RGB_YELLOW); // space bar
    rgb_matrix_set_color(60, RGB_YELLOW); // left ctrl key
    rgb_matrix_set_color(59, RGB_WHITE); // windows key to deactivate every layer and switch to base layer
}