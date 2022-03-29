
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
         rgb_matrix_disable_noeeprom();
         return;
     }
     // Set RGB Matrix color based on layers
     if (user_led_enabled) {
         switch (get_highest_layer(layer_state)){
            case _GAME:
                rgb_matrix_set_color_all(RGB_PURPLE);
                break;
            case _NUM:
                rgb_matrix_set_color_all(RGB_ORANGE);
                break;
            case _SYM:
                rgb_matrix_set_color_all(RGB_GOLD);
                break;
            case _NEO:
                rgb_matrix_set_color_all(RGB_GREEN);
                break;
            case _WEAPON:
                rgb_matrix_set_color_all(RGB_MAGENTA);
                break;
            default:
                rgb_matrix_set_color_all(RGB_GREEN);
                break;

          }
     } else {
         rgb_matrix_disable_noeeprom();
         return;
     }
}
