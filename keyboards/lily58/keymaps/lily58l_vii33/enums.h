#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,    //0
    _LOWER,     //1
    _UPPER,     //2
    _MOD,       //3
    _GAME       //4
};

// Custom Keycodes / Keys  https://docs.qmk.fm/#/custom_quantum_functions?id=defining-a-new-keycode
enum custom_keycodes {
    CC_AE = SAFE_RANGE,
    CC_OE,
    CC_UE,
    CC_BckDel,
    CC_SLH,
    CC_QUOT,
    CC_APHO,
    CC_SCOLN,
    CC_COLN,
    CC_EXLM,
    CC_SAVRGB,
};


// Left-hand home row mods
#define GUI_S LGUI_T(KC_S)
#define ALT_D LALT_T(KC_D)
#define CTL_F LCTL_T(KC_F)
// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define ALT_K LALT_T(KC_K)
#define GUI_L RGUI_T(KC_L)


#define SHFT_SP RSFT_T(KC_SPC)