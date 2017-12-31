!!works but goes backwards after function release

 switch (keycode) {
    case MO(1):
       if (record->event.pressed) {
        layer_on(_FUNCTION);
        rgblight_mode(1);
        rgblight_set_caps;
        //rgblight_set_caps;
    }
      else {
       layer_off(_FUNCTION);
        rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
           }


      return true;
      break;

 case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
       rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
        rgblight_step();
       // rgblight_mode(RGB_current_mode);
     //RGB_current_mode = rgblight_config.mode;
        // _delay_ms(50);
       // rgblight_set();
        RGB_current_mode = rgblight_config.mode;
    }
      else //if (rgblight_config.enable)
      {
        _delay_ms(50);
        rgblight_set();
        //rgblight_mode(rgblight_config.mode);
      // eeconfig_update_rgblight(rgblight_config.raw);
      }

     return true;
      break;

!!works better, returns back to indicated rgb mode, but when MO(1) pressed it toggles to the MO(1) rgblight mode. When changed via RGB_TOG it stays after release of MO(1)

  switch (keycode) {
    case MO(1):
       if (record->event.pressed) {
        layer_on(_FUNCTION);
        rgblight_mode(1);
        rgblight_set_caps;
        //rgblight_set_caps;
    }
      else {
       layer_off(_FUNCTION);
        //rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
           }


      return true;
      break;

    case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
       rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
        rgblight_step();
       // rgblight_mode(RGB_current_mode);
     //RGB_current_mode = rgblight_config.mode;
        // _delay_ms(50);
       // rgblight_set();
        RGB_current_mode = rgblight_config.mode;
    }
      else //if (rgblight_config.enable)
      {
        _delay_ms(50);
        rgblight_set();
        //rgblight_mode(rgblight_config.mode);
      // eeconfig_update_rgblight(rgblight_config.raw);
      }

!!settings #define rgblight_set_caps       rgblight_sethsv_noeeprom(255, 0, 0) turns RGB light off (momentary flash of red light) but returns back to normal after change.  KC_CAPS turns off light but reverts back to mode set

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MO(1):
       if (record->event.pressed) {
        layer_on(_FUNCTION);
        rgblight_mode(1);
        rgblight_set_caps;
        //rgblight_set_caps;
    }
      else {
       layer_off(_FUNCTION);
        //rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
           }


      return true;
      break;

    case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
       rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
        rgblight_step();
       // rgblight_mode(RGB_current_mode);
     //RGB_current_mode = rgblight_config.mode;
        // _delay_ms(50);
       // rgblight_set();
        RGB_current_mode = rgblight_config.mode;
    }
      else //if (rgblight_config.enable)
      {
        _delay_ms(50);
        rgblight_set();
        //rgblight_mode(rgblight_config.mode);
      // eeconfig_update_rgblight(rgblight_config.raw);
      }

     return true;
      break;

    //case MO(1):
       //if (record->event.realeased) {
        //rgblight_mode(1);
        //rgblight_set_red;
     // }
    //  return true;
     // break;

    case KC_CAPS:
     if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
       register_code(KC_CAPS);
        rgblight_mode(1);
        rgblight_set_caps;
      }
      else {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);

      }
      return false;
       break;

!!works but changes the set rgb mode back one when release of MO(1)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MO(1):
       if (record->event.pressed) {
        layer_on(_FUNCTION);
        rgblight_mode(1);
        rgblight_set_caps;
        //rgblight_set_caps;
    }
      else {
       layer_off(_FUNCTION);
        //rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
           }


      return true;
      break;

    case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
       rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
        rgblight_step();
       // rgblight_mode(RGB_current_mode);
     //RGB_current_mode = rgblight_config.mode;
        // _delay_ms(50);
       // rgblight_set();
        RGB_current_mode = rgblight_config.mode;
    }
      else //if (rgblight_config.enable)
      {
        _delay_ms(50);
        rgblight_set();
        //rgblight_mode(rgblight_config.mode);
      // eeconfig_update_rgblight(rgblight_config.raw);
      }

     return true;
      break;

    //case MO(1):
       //if (record->event.realeased) {
        //rgblight_mode(1);
        //rgblight_set_red;
     // }
    //  return true;
     // break;

    case KC_CAPS:
     if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
       register_code(KC_CAPS);
        rgblight_mode(1);
        rgblight_set_caps;
      }
      else {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);

      }
      return false;
       break;
    case KC_RESET:
      if (record->event.pressed) {
      layer_off(_FUNCTION);
      rgblight_mode(RGB_current_mode);
     RGB_current_mode = rgblight_config.mode;
      layer_clear();
      _delay_ms(1000);
        reset_keyboard();
     }
     else{
      //layer_off(_FUNCTION);
     _delay_ms(1000);
     rgblight_mode(RGB_current_mode);
     RGB_current_mode = rgblight_config.mode;

     //eeconfig_update_rgblight_default();
      }

      return false;
      break;
    }


      return true;
