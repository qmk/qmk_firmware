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
