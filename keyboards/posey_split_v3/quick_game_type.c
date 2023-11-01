#include QMK_KEYBOARD_H

uint8_t original_layer = 0;


bool process_quick_game_type(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
      case CTT:
         if (record->event.pressed) {
            original_layer = get_highest_layer(layer_state);
            layer_on(TEMP_TYPE_LAYER);
            layer_off(original_layer);
            register_code(KC_ENT);
         } else {
            // unregister_code(KC_Y);
            unregister_code(KC_ENT);
         }
         return false;
         break;
   case TTC:
         if (record->event.pressed) {
            layer_on(original_layer);
            layer_off(TEMP_TYPE_LAYER);
            register_code(KC_ENT);
         } else {
            // unregister_code(KC_N);
            unregister_code(KC_ENT);
         }
         return false;
         break;
   }
   return true;
}