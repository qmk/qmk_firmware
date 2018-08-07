enum macro_keycodes {
  KC_CITRIX,
  KC_MPASS,
  KC_META,
  KC_RTQ6H,
  KC_DAYRN,
  KC_3DRN,
  KC_AUTODC,
  KC_EMAIL,
  KC_EMAIL2
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }

    switch (id) {
      //my login macros
      case KC_CITRIX:
        if (record->event.pressed){
          return MACRO (I(1), T(1), END);
        }
      case KC_MPASS:
        if (record->event.pressed){
          return MACRO (I(1), T(1), END);
        }
      case KC_META:
        if (record->event.pressed){
          return MACRO (I(1), T(1), END);
        }
      //my work macros
      case KC_RTQ6H:
        if (record->event.pressed){
          return MACRO (I(1), T(TAB), T(0), T (3), T(0), T(0), T(TAB), T(DOWN), T(TAB), T(0), T (9), T(0), T(0), T(TAB), T(DOWN), T(TAB), T(1), T (5), T(0), T(0), T(TAB), T(DOWN), T(TAB), T(2), T (1), T(0), T(0), T(TAB), D(LALT), T(O), U(LALT), END);
        }
      case KC_AUTODC:
        if (record->event.pressed){
          return MACRO (I(1), D(LALT), T(V), U(LALT), T(TAB), T(TAB), T(TAB), T(TAB), T(TAB), T(TAB), T(TAB), T(TAB), T(TAB), T(T), T(TAB),T(N), D(LALT), T(S), U(LALT), END);
        }
      case KC_DAYRN:
        if (record->event.pressed){
          return MACRO (I(1), T(TAB), T(TAB), T(TAB), T(TAB), T(TAB), T(1), D(LALT), T(S), U(LALT), END);
        }
      //Ops macros
      case KC_EMAIL:
        if (record->event.pressed){
          return MACRO (I(1), T(1), END);        }        
      case KC_EMAIL2:
        if (record->event.pressed){
          return MACRO (I(1), T(1), END);
        }  
    }

    return MACRO_NONE;
} 