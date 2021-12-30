#include "ericgebhart.h"
#include "layouts.h"

extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum crkbd_keycodes { RGBRST = NEW_SAFE_RANGE };

/*
 * The `LAYOUT_crkbd_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Qwerty based Base layers
    [_DVORAK]  = Crkbd_base(___DVORAK___),
    [_BEAKL]   = Crkbd_base(___BEAKL15___),
    [_COLEMAK] = Crkbd_base(___COLEMAK_DH___),
    [_QWERTY]  = Crkbd_base(___QWERTY___),

    // Bepo base layers
    [_BEAKL_BP]  = Crkbd_bepo(___BEAKL15_FR___),
    [_DVORAK_BP] = Crkbd_bepo(___DVORAK_FR___),
    [_BEPO]      = Crkbd_bepo6(___BEPO6___),

    // Transient layers.
    [_SYMB]    = Crkbd_transient(___SYMB_BEAKLB_3x12___),
    [_SYMB_BP] = Crkbd_transient(___SYMB_BEAKLB_BP_3x12___),

    [_KEYPAD]    = Crkbd_transient(___KP_C_3x12___),
    [_KEYPAD_BP] = Crkbd_transient(___KP_C_BP_3x12___),

    [_TOPROWS]    = Crkbd_transient(___TOPROWS_3x12___),
    [_TOPROWS_BP] = Crkbd_transient(___TOPROWS_BP_3x12___),

    [_NAV] = Crkbd_transient(___NAV_3x12___),

    [_LAYERS] = Crkbd_transient(___LAYERS_3x12___),
    //[_RGB] = Crkbd_transient(___RGB_3x12___),
    [_ADJUST] = Crkbd_transient(___ADJUST_3x12___),
    ///HPT_TOG, KC_NUKE, ___,        ___, TG_MODS, HPT_FBK
};



void oled_render_logo(void) {
  static const char PROGMEM crkbd_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0};
  oled_write_P(crkbd_logo, false);
}
