/*

Please see qmk_firmware/keyboards/ergodox_ez/keymaps/davidhbrown/README.md
for instructions on how to add this to your keyboard!

*/

// specify which layer will be associated with which LED
#define STATUS_LED_RED_LAYER 3
#define STATUS_LED_GREEN_LAYER 2
#define STATUS_LED_BLUE_LAYER 1

// specify which USB Host status "LED" will be associated with which LED
#define STATUS_LED_RED_USB USB_LED_CAPS_LOCK
#define STATUS_LED_GREEN_USB USB_LED_NUM_LOCK
#define STATUS_LED_BLUE_USB USB_LED_SCROLL_LOCK

// specify the PWM values for each LED at each brightness
#define STATUS_LED_RED_DIM 8
#define STATUS_LED_RED_HALF 96
#define STATUS_LED_RED_FULL 228
#define STATUS_LED_GREEN_DIM 2
#define STATUS_LED_GREEN_HALF 48
#define STATUS_LED_GREEN_FULL 160
#define STATUS_LED_BLUE_DIM 16
#define STATUS_LED_BLUE_HALF 172
#define STATUS_LED_BLUE_FULL 255

 void statusLed(void) {
    uint8_t layer = biton32(layer_state);
    uint8_t red=0,green=0,blue=0;

    if(layer==MOUS) red=STATUS_LED_RED_HALF;
    if(IS_HOST_LED_ON(STATUS_LED_RED_USB)) red=STATUS_LED_RED_DIM;
    if(IS_HOST_LED_ON(STATUS_LED_RED_USB) && layer==STATUS_LED_RED_LAYER) red=STATUS_LED_RED_FULL;

    if(layer==NMPD) green=STATUS_LED_GREEN_HALF;
    if(IS_HOST_LED_ON(STATUS_LED_GREEN_USB)) green=STATUS_LED_GREEN_DIM;
    if(IS_HOST_LED_ON(STATUS_LED_GREEN_USB) && layer==STATUS_LED_GREEN_LAYER) green=STATUS_LED_GREEN_FULL;

    if(layer==FNKY) blue=STATUS_LED_BLUE_HALF;
    if(IS_HOST_LED_ON(STATUS_LED_BLUE_USB)) blue=STATUS_LED_BLUE_DIM;
    if(IS_HOST_LED_ON(STATUS_LED_BLUE_USB) && layer==STATUS_LED_BLUE_LAYER) blue=STATUS_LED_BLUE_FULL;

    ergodox_led_all_off();
    if(red)
    {
        ergodox_board_led_on();
        ergodox_right_led_1_on();
        ergodox_right_led_1_set(red);
    }
    if(green)
    {
        ergodox_board_led_on();
        ergodox_right_led_2_on();
        ergodox_right_led_2_set(green);
    }
    if(blue) {
        ergodox_board_led_on();
        ergodox_right_led_3_on();
        ergodox_right_led_3_set(blue);
    }
};
