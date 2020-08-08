#pragma once
#include "boboysdadda.h"

#if defined(KEYMAP_SAFE_RANGE)
#    define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#    define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
    UC_DISA = SAFE_RANGE,
    UC_FLIP,
    UC_SHRG,
    UC_TABL,
    CP_PST,
    KC_QWERTY,
    KC_DVORAK,
    KC_DT1,
    KC_DT2,
    KC_DT3,
    KC_DT4,
    KC_MAKE,            // Run keyboard's customized make command
    KC_RGB_T,           // Toggles RGB Layer Indication mode
    RGB_IDL, 
    KC_SEC1, 
    KC_SEC2, 
    KC_SEC3, 
    KC_SEC4, 
    KC_SEC5,
    KC_RST,
    VRSN,
    NEW_SAFE_RANGE
};
bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define TG_MODS TG(_MODS)
#define ADJUST MO(_ADJUST)



#define QWERTY KC_QWERTY
#define DVORAK KC_DVORAK

#if defined(SWAP_HANDS_ENABLE)
#    define KC_C1R3 SH_T(KC_TAB)
#else  // SWAP_HANDS_ENABLE
#    define KC_C1R3 KC_TAB
#endif  // SWAP_HANDS_ENABLE

#define SP_LWER LT(_LOWER, KC_SPC)
#define ET_RAIS LT(_RAISE, KC_ENTER)

/* OSM keycodes, to keep things clean and easy to change */
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_MEH OSM(MOD_MEH)
#define OS_HYPR OSM(MOD_HYPR)

#define MT_TAB MT(MOD_LCTL, KC_TAB)

#define ALT_APP ALT_T(KC_APP)

#define MG_NKRO MAGIC_TOGGLE_NKRO

#define UC_IRNY UC(0x2E2E)
#define UC_CLUE UC(0x203D)

// KWin Window Switching
#define KC_DT1 LCTL(KC_F1)
#define KC_DT2 LCTL(KC_F2)
#define KC_DT3 LCTL(KC_F3)
#define KC_DT4 LCTL(KC_F4)
