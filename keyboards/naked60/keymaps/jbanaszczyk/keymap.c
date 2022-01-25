#include QMK_KEYBOARD_H

#include "users/jbanaszczyk/jbanaszczyk_keycodes.h"

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL
};

#include "keymap_json.c"
