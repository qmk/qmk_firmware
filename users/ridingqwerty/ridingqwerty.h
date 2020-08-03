#pragma once

#include "quantum.h"
#include "version.h"
#include "process_records.h"
#include "wrappers.h"
#ifdef TAP_DANCE_ENABLE
#    include "tapdances.h"
#endif
#if defined(UNICODEMAP_ENABLE) || defined(UNICODE_ENABLE)
#    include "unicode.h"
#endif

enum userspace_layers
{
    _QWERTY,
    _DVORAK,
    _COLEMAK,
/*
    _WORKMAN et al. go here
*/
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    _GREEK,
    _RUSSIAN,
    _RUNES,
    _HIRA1,
    _HIRA2,
#endif
    _EDITOR,
    _NUMBER,
    _SYMBOL,
    _F_KEYS,
    _DEBUG,
    _SECRET,
#if defined(MOUSEKEY_ENABLED)
    _MOUSE,
#endif
    _MEDIA,
    _FINAL
};

#define LS(kc) MT(MOD_LSFT, KC_##kc)
#define LC(kc) MT(MOD_LCTL, KC_##kc)
#define LG(kc) MT(MOD_LGUI, KC_##kc)
#define LA(kc) MT(MOD_LALT, KC_##kc)
#define RS(kc) MT(MOD_RSFT, KC_##kc)
#define RC(kc) MT(MOD_RCTL, KC_##kc)
#define RG(kc) MT(MOD_RGUI, KC_##kc)
#define RA(kc) MT(MOD_RALT, KC_##kc)

#define ED(kc) LT(_EDITOR, KC_##kc)
#define NM(kc) LT(_NUMBER, KC_##kc)
#define SM(kc) LT(_SYMBOL, KC_##kc)
#define SC(kc) LT(_SECRET, KC_##kc)
#define FK(kc) LT(_F_KEYS, KC_##kc)
#define DB(kc) LT(_DEBUG,  KC_##kc)

void matrix_init_keymap(void);
void matrix_scan_keymap(void);
void keyboard_post_init_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
