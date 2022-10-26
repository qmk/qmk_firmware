#include "process_record_user.h"
#include QMK_KEYBOARD_H

extern void add_keylog(uint16_t keycode);

uint8_t mods_state;

bool process_record_user(uint16_t keycode, keyrecord_t *record){
  // For OLED Key Printer
    if (record->event.pressed) {
        add_keylog(keycode);
    }

  oled_on();


  return true;
}


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // // For OLED Key Printer
    // if (record->event.pressed) {
    //     add_keylog(keycode);
    // }

    // // /* KEYBOARD PET STATUS START */
    // // switch (keycode) {
    // //     case KC_LCTL:
    // //     case KC_RCTL:
    // //         if (record->event.pressed) {
    // //             isSneaking = true;
    // //         } else {
    // //             isSneaking = false;
    // //         }
    // //         break;

    // //     case KC_SPC:
    // //         if (record->event.pressed) {
    // //             isJumping  = true;
    // //             showedJump = false;
    // //         } else {
    // //             isJumping = false;
    // //         }
    // //         break;
    // // }
    // // /* KEYBOARD PET STATUS END */


    // if (record->event.pressed) {    // On key down
    //     mods_state = get_mods();    // Store the current modifier state in the variable for later reference
        
    //     switch (keycode) {
    //         case CC_BckDel:
    //             if ( get_mods() & MOD_MASK_SHIFT ) {  // Shift pressed
    //                 del_mods(MOD_MASK_SHIFT);           // cancel the shifts so they are not applied to the keycodes
    //                 tap_code(KC_DEL);                 
    //                 set_mods(mods_state);
    //             }else {                               // No shift is pressed
    //                 tap_code(KC_BSPC);
    //             }
    //             break;
            
    //         case CC_AE:
    //             tap_code16(ALGR(KC_Q));   // tapcode16() allows you to use modifiers!
    //             break;

    //         case CC_OE:
    //             tap_code16(ALGR(KC_P));   
    //             break;

    //         case CC_UE:
    //             tap_code16(ALGR(KC_Y));   
    //             break;
                
    //         case CC_SLH:
    //             if ( get_mods() & MOD_MASK_SHIFT ) {  
    //                 del_mods(MOD_MASK_SHIFT);         
    //                 tap_code(KC_BSLS);           // backslash   
    //                 set_mods(mods_state);   
    //             }else {                               
    //                 tap_code(KC_SLSH);          // /
    //             }
    //             break;

    //         case CC_APHO:
    //             if ( get_mods() & MOD_MASK_SHIFT ) {  
    //                 del_mods(MOD_MASK_SHIFT);         
    //                 tap_code(KC_GRV);              //  ` grave 
    //                 set_mods(mods_state);    
    //             }else {                               
    //                 tap_code16(ALGR(KC_QUOT));     //  ´ aigu
    //             }
    //             break;

    //         case CC_QUOT:
    //             if ( get_mods() & MOD_MASK_SHIFT ) {  
    //                 SEND_STRING("\"");             // "      
    //             }else {                               
    //                 tap_code16(LSFT(KC_QUOT));     // '
    //             }
    //             break;

    //         case CC_COLN:
    //             if ( get_mods() & MOD_MASK_SHIFT ) {  
    //                 //del_mods(MOD_MASK_SHIFT);         
    //                 tap_code(KC_SCLN);             // :      
    //             }else {                               
    //                 tap_code(KC_DOT);              // . (dot)
    //             }
    //             break;

    //         case CC_SCOLN:
    //             if ( get_mods() & MOD_MASK_SHIFT ) {  
    //                 del_mods(MOD_MASK_SHIFT);         
    //                 tap_code(KC_SCLN);             // ; 
    //                 set_mods(mods_state);    
    //             }else {                               
    //                 tap_code(KC_COMM);             // , (comma)
    //             }
    //             break;

    //         case CC_EXLM:
    //             if ( get_mods() & MOD_MASK_SHIFT ) {  
    //                 del_mods(MOD_MASK_SHIFT);         
    //                 tap_code16(KC_EXLM);             // !     
    //                 set_mods(mods_state);
    //             }else {                               
    //                 tap_code16(KC_QUES);             // ? 
    //             }
    //             break;

    //         case KC_LPRN:   // (
    //             if ( get_mods() & MOD_MASK_SHIFT ) {
    //                 SEND_STRING("()" SS_TAP(X_LEFT));
    //             } else {
    //                 return true;    // continue with normal KC
    //             }

    //         case CC_SAVRGB:   // Saves color config to eeprom. Used to save eeprom write cycles              
    //             rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val()); 
    //             rgblight_set_speed( rgblight_get_speed() );
    //             break;
    //     }
    //     return false;   
    // }
            
//      return true;
// }
