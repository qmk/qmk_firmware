#define LAYER_LIGHT_MODE RGBLIGHT_MODE_STATIC_LIGHT

void keyboard_post_init_user(void) {
  rgblight_sethsv(C_QWERTY);
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
}

layer_state_t layer_state_set_user(layer_state_t state) {
   uint8_t layer = biton32(state);
   switch (layer) {
      case _QWERTY:
         rgblight_sethsv(C_QWERTY);
         break;
      case _RECORE:
         rgblight_sethsv(C_RECORE);
         break;
      case _DIABLO:
         rgblight_sethsv(C_DIABLO);
         break;
      case _TEMPRTY:         
         rgblight_sethsv(C_TEMPRTY);
         break;
      case _SYMB:         
         rgblight_sethsv(C_SYMB);
         break;
      case _NAV:         
         rgblight_sethsv(C_NAV);
         break;
   }
   return state;
}