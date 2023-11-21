#ifndef LAYER_LIGHT_MODE
#define LAYER_LIGHT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#endif

void keyboard_post_init_user(void) {
  rgblight_sethsv(C_QWERTY);
  rgblight_mode(LAYER_LIGHT_MODE);
}

layer_state_t layer_state_set_user(layer_state_t state) {
   uint8_t layer = biton32(state);
   switch (layer) {
      case _QWERTY:
         rgblight_sethsv(C_QWERTY);
         break;
      #ifdef C_RECORE
      case _RECORE:
         rgblight_sethsv(C_RECORE);
         break;
      #endif
      #ifdef C_DIABLO
      case _DIABLO:
         rgblight_sethsv(C_DIABLO);
         break;
      #endif
      #ifdef C_PLAYERS
      case _PLAYERS:
         rgblight_sethsv(C_PLAYERS);
         break;
      #endif
      #ifdef C_TEMPRTY
      case _TEMPRTY:         
         rgblight_sethsv(C_TEMPRTY);
         break;
      #endif
      #ifdef C_SYMB
      case _SYMB:         
         rgblight_sethsv(C_SYMB);
         break;
      #endif
      #ifdef C_NAV
      case _NAV:         
         rgblight_sethsv(C_NAV);
         break;
      #endif
   }
   return state;
}