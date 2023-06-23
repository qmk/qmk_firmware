#pragma once

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,  // Prints QMK Firmware and board info
    KC_QWERTY,          // Sets default layer to QWERTY
    KC_COLEMAK,         // Sets default layer to COLEMAK
    KC_DVORAK,          // Sets default layer to DVORAK
    KC_WORKMAN,         // Sets default layer to WORKMAN
    KC_MAKE,            // Run keyboard's customized make command
    KC_RGB_T,           // Toggles RGB Layer Indication mode
    RGB_IDL,            // RGB Idling animations
    KC_SECRET_1,        // test1
    KC_SECRET_2,        // test2
    KC_SECRET_3,        // test3
    KC_SECRET_4,        // test4
    KC_SECRET_5,        // test5
    KC_CCCV,            // Hold to copy, tap to paste
    UC_FLIP,            // (ಠ痊ಠ)┻━┻
    UC_TABL,            // ┬─┬ノ( º _ ºノ)
    UC_SHRG,            // ¯\_(ツ)_/¯
    UC_DISA,            // ಠ_ಠ
    KC_DT1,
    KC_DT2,
    KC_DT3,
    KC_DT4,
    NEW_SAFE_RANGE  // use "NEWPLACEHOLDER for keymap specific codes
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define TG_MODS TG(_MODS)
#define OS_LWR OSL(_LOWER)
#define OS_RSE OSL(_RAISE)

#define KC_SEC1 KC_SECRET_1
#define KC_SEC2 KC_SECRET_2
#define KC_SEC3 KC_SECRET_3
#define KC_SEC4 KC_SECRET_4
#define KC_SEC5 KC_SECRET_5

#define QWERTY KC_QWERTY
#define DVORAK KC_NO
#define COLEMAK KC_NO
#define WORKMAN KC_NO

#if defined(ENABLE_DVORAK)
#   undef DVORAK
#   define DVORAK KC_DVORAK
#endif

#if defined(ENABLE_COLEMAK)
#   undef COLEMAK
#   define COLEMAK KC_COLEMAK
#endif

#if defined(ENABLE_WORKMAN)
#   undef WORKMAN
#   define WORKMAN KC_WORKMAN
#endif

#define KC_RST QK_BOOT

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
