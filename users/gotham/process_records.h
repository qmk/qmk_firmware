// Stole from drashna

#pragma once

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,  // Prints QMK Firmware and board info
    KC_QWERTY,          // Sets default layer to QWERTY
    KC_COLEMAK,         // Sets default layer to COLEMAK
    KC_DVORAK,          // Sets default layer to DVORAK
    KC_WORKMAN,         // Sets default layer to WORKMAN
    KC_NORMAN,          // Sets default layer to NORMAN
    KC_MAKE,            // Run keyboard's customized make command
    KC_CCCV,            // Hold to copy, tap to paste
    NEW_SAFE_RANGE      // use this instead of SAFE_RANGE for keymap specific codes
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define TG_GAME TG(_GAME)
#define TG_GNAV TG(_GAMENAV)
#define MO_GNUM MO(_GAMENUM)

#define QWERTY KC_QWERTY
#define COLEMAK KC_COLEMAK
#define NORMAN KC_NORMAN
#define WORKMAN KC_WORKMAN
#define DVORAK KC_DVORAK

#define SF_QUOT MT(MOD_RSFT, KC_QUOT)
#define CT_MINS MT(MOD_RCTL, KC_MINS)

#define SP_LOWR LT(_LOWER, KC_SPC)
#define TB_LOWR LT(_LOWER, KC_TAB)
#define BK_LOWR LT(_LOWER, KC_BSPC)
#define EN_LOWR LT(_LOWER, KC_ENTER)

#define SP_RAIS LT(_RAISE, KC_SPC)
#define TB_RAIS LT(_RAISE, KC_TAB)
#define BK_RAIS LT(_RAISE, KC_BSPC)
#define EN_RAIS LT(_RAISE, KC_ENTER)

#define MS_DEL LT(_MOUSE, KC_DEL)

#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
