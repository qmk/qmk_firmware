
#include "../__init__.h"

const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_make_basic(MOD_MASK_CTRL, HK_RFCT, HK_RFAL),
    &ko_make_basic(MOD_MASK_CTRL, KC_F16, KC_F18),
    &ko_make_basic(MOD_MASK_CTRL, HK_UNDO, HK_REDO),

    &ko_make_basic(MOD_MASK_SHIFT, KC_F2, HK_RLD),
    &ko_make_basic(MOD_MASK_SHIFT, KC_CAPS, HK_GSRC),

    &ko_make_with_layers(MOD_MASK_SHIFT, KC_ENT, KC_ENT, ~NUM),
    NULL
};
