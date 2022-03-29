
// Boolean to store LED state
bool user_led_enabled = true;
// [Matrix Scan] ------------------------------------------------------------//
void led_logics(void) {
     // Iddle timer to return to default layer if left on game layer
     if (timer_elapsed32(oled_timer) > 380000 && timer_elapsed32(oled_timer) < 479999) {
         // Reset layer in case it got left on _GAME
         // This prevents the issue where the master side sometimes wont switch off as expected
         // in the next step.
         if (get_highest_layer(layer_state) == _GAME) {
             layer_off(_GAME);
             layer_on(_NEO);
         }
         return;
     }
     // Timeout to turn off LEDs
     else if (timer_elapsed32(oled_timer) > 480000) {
         rgblight_disable_noeeprom();
         return;
     }
     // Set RGB Matrix color based on layers
     if (user_led_enabled) {
         switch (get_highest_layer(layer_state)){
            case _GAME:
                rgblight_setrgb(RGB_PURPLE);
                break;
            case _NUM:
                rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                rgblight_setrgb(RGB_ORANGE);
                break;
            case _SYM:
                rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                rgblight_setrgb(RGB_GOLD);
                break;
            case _NEO:
                rgblight_setrgb(RGB_GREEN);
                break;
            case _WEAPON:
                rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                rgblight_setrgb(RGB_MAGENTA);
                break;
            default:
                rgblight_setrgb(RGB_GREEN);
                break;

          }
     } else {
         rgblight_disable_noeeprom();
         return;
     }
}
